#include "VulkanRenderContext.hpp"

#include "VulkanDebug.hpp"

namespace DadEngine::Rendering
{
	VulkanRenderContext::VulkanRenderContext(PlatformWindow& _InWindow)
	{
		//VulkanHelper::EnumerateInstanceLayersAndExtensions();

 		m_WindowExtent = { (uint32)_InWindow.GetRect().right, (uint32)_InWindow.GetRect().bottom };

		CreateInstance(_InWindow);

		VulkanDebug::InitializeVulkanDebug(m_Instance);


		// Rework to manage multiple device
		TArray<VkPhysicalDevice> physicalDevices;
		VulkanHelper::EnumerateDevices(m_Instance, physicalDevices);

		m_PhysicalDevice = physicalDevices[0];

		//VulkanHelper::EnumerateDeviceLayersAndExtensions(m_PhysicalDevice);

		m_uiGraphicsQueueFamilyIndex = VulkanHelper::CheckDeviceQueueFamilyProperties(m_PhysicalDevice, VK_QUEUE_GRAPHICS_BIT);

		CreatePresentationSurface(_InWindow);
		GetPresentationMode(_InWindow);

		vkGetPhysicalDeviceMemoryProperties(m_PhysicalDevice, &m_PhysicalDeviceMemoryProperties);

		CreateDevice();
		GetQueues();

		CreateCommandPool();
		CreateSetupCommandBuffer();

		m_Swapchain = new VulkanSwapchain();
		m_Swapchain->Initialize(m_Device, m_PhysicalDevice, m_PresentationSurface, m_PresentationMode, _InWindow);

		CreateDescriptorPool();
		CreateDepthStencilBuffer();
		DestroySetupCommandBuffer();

		CreateRenderpass();
		CreatePipelineCache();
		CreateFramebuffers();
		CreateSemaphores();
		CreateFences();
	}

	VulkanRenderContext::~VulkanRenderContext()
	{
		vkDeviceWaitIdle(m_Device);

		vkDestroyCommandPool(m_Device, m_GraphicsCommandPool, VK_NULL_HANDLE);
		vkDestroyCommandPool(m_Device, m_PresentationCommandPool, VK_NULL_HANDLE);

		vkDestroyDescriptorPool(m_Device, m_UBODescriptorPool, VK_NULL_HANDLE);

		delete m_Swapchain;

		for (VkFence currentFence : m_CommandBufferAvailables)
		{
			vkDestroyFence(m_Device, currentFence, VK_NULL_HANDLE);
		}

		vkDestroySemaphore(m_Device, m_ImageAvailableSemaphore, VK_NULL_HANDLE);
		vkDestroySemaphore(m_Device, m_RenderingFinishedSemaphore, VK_NULL_HANDLE);

		vkDestroyDevice(m_Device, VK_NULL_HANDLE);

		vkDestroySurfaceKHR(m_Instance, m_PresentationSurface, VK_NULL_HANDLE);

		VulkanDebug::DestroyVulkanDebug(m_Instance);
		vkDestroyInstance(m_Instance, VK_NULL_HANDLE);
	}



	void VulkanRenderContext::ClearColorBuffer(Color& _InClearColor, CommandBuffer* _InCommandBuffer)
	{
		VkImageMemoryBarrier image_memory_barrier_from_color_to_clear = {};
		image_memory_barrier_from_color_to_clear.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		image_memory_barrier_from_color_to_clear.image = m_BackBuffer->m_Image;
		image_memory_barrier_from_color_to_clear.pNext = VK_NULL_HANDLE;
		image_memory_barrier_from_color_to_clear.srcAccessMask = 0U; //VK_ACCESS_MEMORY_READ_BIT;
		image_memory_barrier_from_color_to_clear.dstAccessMask = /*VK_ACCESS_MEMORY_READ_BIT;//*/VK_ACCESS_TRANSFER_WRITE_BIT;
		image_memory_barrier_from_color_to_clear.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		image_memory_barrier_from_color_to_clear.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		image_memory_barrier_from_color_to_clear.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;//m_BackBuffer->m_CurrentLayout; // Swapchain image is supposed to be undefined after being acquired
		image_memory_barrier_from_color_to_clear.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		image_memory_barrier_from_color_to_clear.subresourceRange = m_BackBuffer->m_ImageSubresourceRange;


		VkClearColorValue color = { _InClearColor.r, _InClearColor.g, _InClearColor.b, _InClearColor.a };

		m_BackBuffer->m_CurrentLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;

		vkCmdPipelineBarrier(((VulkanCommandBuffer*)_InCommandBuffer)->m_CmdBuffer,
			VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
			0, 0, NULL, 0, NULL, 1, &image_memory_barrier_from_color_to_clear);

		vkCmdClearColorImage(((VulkanCommandBuffer*)_InCommandBuffer)->m_CmdBuffer, m_BackBuffer->m_Image,
			m_BackBuffer->m_CurrentLayout, &color, 1U, &m_BackBuffer->m_ImageSubresourceRange);
	}

	void VulkanRenderContext::ClearDepthStencilBuffer(float _InDepthValue, uint32 _InStencilValue, CommandBuffer* _InCommandBuffer)
	{
		VkImageMemoryBarrier image_memory_barrier_from_depth_to_clear = {};
		image_memory_barrier_from_depth_to_clear.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		image_memory_barrier_from_depth_to_clear.image = m_DepthStencilBuffer.m_Image;
		image_memory_barrier_from_depth_to_clear.pNext = VK_NULL_HANDLE;
		image_memory_barrier_from_depth_to_clear.srcAccessMask = 0U;
		image_memory_barrier_from_depth_to_clear.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		image_memory_barrier_from_depth_to_clear.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		image_memory_barrier_from_depth_to_clear.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		image_memory_barrier_from_depth_to_clear.oldLayout = m_DepthStencilBuffer.m_CurrentLayout;
		image_memory_barrier_from_depth_to_clear.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		image_memory_barrier_from_depth_to_clear.subresourceRange = m_DepthStencilBuffer.m_ImageSubresourceRange;


		VkClearDepthStencilValue depthStencil = { _InDepthValue, _InStencilValue };


		vkCmdPipelineBarrier(((VulkanCommandBuffer*)_InCommandBuffer)->m_CmdBuffer,
			VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
			0, 0, NULL, 0, NULL, 1, &image_memory_barrier_from_depth_to_clear);

		m_DepthStencilBuffer.m_CurrentLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;


		vkCmdClearDepthStencilImage(((VulkanCommandBuffer*)_InCommandBuffer)->m_CmdBuffer, m_DepthStencilBuffer.m_Image,
			m_DepthStencilBuffer.m_CurrentLayout, &depthStencil, 1U, &m_DepthStencilBuffer.m_ImageSubresourceRange);
	}

	void VulkanRenderContext::Present(CommandBuffer* _InCommandBuffer)
	{
		VkImageMemoryBarrier image_memory_barrier_from_anything_to_present = {};
		image_memory_barrier_from_anything_to_present.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		image_memory_barrier_from_anything_to_present.image = m_BackBuffer->m_Image;
		image_memory_barrier_from_anything_to_present.pNext = VK_NULL_HANDLE;
		image_memory_barrier_from_anything_to_present.srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;//VK_ACCESS_TRANSFER_WRITE_BIT;
		image_memory_barrier_from_anything_to_present.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
		image_memory_barrier_from_anything_to_present.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		image_memory_barrier_from_anything_to_present.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		image_memory_barrier_from_anything_to_present.oldLayout = m_BackBuffer->m_CurrentLayout;
		image_memory_barrier_from_anything_to_present.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		image_memory_barrier_from_anything_to_present.subresourceRange = m_BackBuffer->m_ImageSubresourceRange;


		vkCmdPipelineBarrier(((VulkanCommandBuffer*)_InCommandBuffer)->m_CmdBuffer,
			VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT/*VK_PIPELINE_STAGE_TRANSFER_BIT*/, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
			0, 0, NULL, 0, NULL, 1, &image_memory_barrier_from_anything_to_present);
	}

	void VulkanRenderContext::Draw(VertexBuffer* _InVertexBuffer, CommandBuffer* _InCommandBuffer)
	{
		vkCmdDraw(((VulkanCommandBuffer*)_InCommandBuffer)->m_CmdBuffer, _InVertexBuffer->m_uiVertexCount, 1U, 0U, 0U);
	}

	void VulkanRenderContext::BindVertexBuffer(VertexBuffer* _InVertexBuffer, CommandBuffer* _InCommandBuffer)
	{
		VkDeviceSize deviceSize = 0U;

		vkCmdBindVertexBuffers(
			((VulkanCommandBuffer*)_InCommandBuffer)->m_CmdBuffer,
			0U,
			1U,
			&((VulkanVertexBuffer*)_InVertexBuffer)->m_Buffer,
			&deviceSize);
	}

	void VulkanRenderContext::BindShaderProgram(Shader* _InShader, CommandBuffer* _InCommandBuffer)
	{
		vkCmdBindPipeline(((VulkanCommandBuffer*)_InCommandBuffer)->m_CmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, ((VulkanShader*)_InShader)->m_GraphicsPipeline);

		((VulkanShader*)_InShader)->UpdateUBO();

		// Also bind shaders params ?
		vkCmdBindDescriptorSets(
			((VulkanCommandBuffer*)_InCommandBuffer)->m_CmdBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			((VulkanShader*)_InShader)->m_PipelineLayout,
			0U,
			1U,
			&((VulkanShader*)_InShader)->m_DescriptorSet,
			0U,
			VK_NULL_HANDLE);
	}

	void VulkanRenderContext::BeginRenderPass(RenderPass * _InRenderPass, Framebuffer* _InFrameBuffer, CommandBuffer* _InCommandBuffer)
	{
		TArray<VkClearValue> clearValues(((VulkanFramebuffer*)_InFrameBuffer)->m_Attachements.Size());
		
		// ------------------------------------------
		//!\ All the attachments may not be clearable
		// ------------------------------------------
		clearValues[0U].color = VkClearColorValue{ 0.f, 0.1f, 1.0f, 1.f };
		clearValues[1U].depthStencil = VkClearDepthStencilValue{ 1.f, 0U };

		VkRenderPassBeginInfo render_pass_begin_info = {};
		render_pass_begin_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		render_pass_begin_info.pNext = VK_NULL_HANDLE;
		render_pass_begin_info.framebuffer = ((VulkanFramebuffer*)_InFrameBuffer)->m_Framebuffer;
		render_pass_begin_info.renderPass = ((VulkanRenderPass*)_InRenderPass)->m_Renderpass;
		render_pass_begin_info.renderArea = VkRect2D{ { 0, 0 }, m_Swapchain->m_SwapchainExtent };

		render_pass_begin_info.clearValueCount = (uint32)clearValues.Size();
		render_pass_begin_info.pClearValues = clearValues.GetData();

		vkCmdBeginRenderPass(((VulkanCommandBuffer*)_InCommandBuffer)->m_CmdBuffer, &render_pass_begin_info, VK_SUBPASS_CONTENTS_INLINE);
	}

	void VulkanRenderContext::EndRenderPass(CommandBuffer * _InCommandBuffer)
	{
		vkCmdEndRenderPass(((VulkanCommandBuffer*) _InCommandBuffer)->m_CmdBuffer);
	}


	void VulkanRenderContext::SetViewport(Viewport& _InViewport, CommandBuffer* _InCommandBuffer)
	{
		VkCommandBuffer currentCommandBuffer = nullptr;

		//vkCmdSetViewport(currentCommandBuffer, 0U, 1U, )
	}

	void VulkanRenderContext::SetCullingMode(CullingMode _InCullingMode, CommandBuffer* _InCommandBuffer)
	{
		// Pipeline related
	}

	void VulkanRenderContext::SetFillMode(FillMode _InFillMode, CommandBuffer* _InCommandBuffer)
	{
		// Pipeline related
	}


	Image* VulkanRenderContext::GetBackBuffer()
	{
		return m_BackBuffer;
	}

	Image* VulkanRenderContext::GetDepthStencilBuffer()
	{
		return &m_DepthStencilBuffer;
	}

	Framebuffer *VulkanRenderContext::GetBackFramebuffer()
	{
		return &m_Framebuffers[(uint32)m_uiNextImage];
	}

	RenderPass * VulkanRenderContext::GetRenderPass()
	{
		return &m_Renderpass;
	}


	
	void VulkanRenderContext::BeginFrame()
	{
		m_uiNextImage = m_Swapchain->GetNextImageIndex(m_ImageAvailableSemaphore);
		m_BackBuffer = &m_Swapchain->m_SwapchainImages[m_uiNextImage];


		// Wait for the command buffer to be available
		vkResetFences(m_Device, 1U, &m_CommandBufferAvailables[m_uiNextImage]);
	}

	void VulkanRenderContext::EndFrame()
	{
		VkPipelineStageFlags wait_pipelinestage_flag = /*VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;*/VK_PIPELINE_STAGE_TRANSFER_BIT;

		//m_SubmittedCommandBuffers.Add(m_FinalCommandBuffers[m_uiNextImage].m_CmdBuffer);

		VkSubmitInfo submit_info = {};
		submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submit_info.pNext = VK_NULL_HANDLE;
		submit_info.pCommandBuffers = m_SubmittedCommandBuffers.GetData();
		submit_info.commandBufferCount = (uint32)m_SubmittedCommandBuffers.Size();
		submit_info.waitSemaphoreCount = 1U;
		submit_info.pWaitSemaphores = &m_ImageAvailableSemaphore;
		submit_info.signalSemaphoreCount = 1U;
		submit_info.pSignalSemaphores = &m_RenderingFinishedSemaphore;
		submit_info.pWaitDstStageMask = &wait_pipelinestage_flag;

		VK_CHECK_RESULT(vkQueueSubmit(m_GraphicsQueue, 1U, &submit_info, m_CommandBufferAvailables[m_uiNextImage]));

		m_Swapchain->Present(m_GraphicsQueue, m_RenderingFinishedSemaphore, m_uiNextImage);


		m_SubmittedCommandBuffers.Clear();


		// Waiting for the command buffers to be executed
		vkWaitForFences(m_Device, 1U, &m_CommandBufferAvailables[m_uiNextImage], VK_FALSE, INFINITE);
	}

	void VulkanRenderContext::SubmitCommandBuffer(CommandBuffer * _InCommandBuffer)
	{
		m_SubmittedCommandBuffers.Add(((VulkanCommandBuffer*)_InCommandBuffer)->m_CmdBuffer);
	}
	


	VertexBuffer * VulkanRenderContext::CreateVertexBuffer(uint32 _InVertexCount, TArray<float>& _InData, TArray<VertexInput>& _InVertexLayout, uint32 _InVerticesStride)
	{
		return new VulkanVertexBuffer(_InVertexCount, _InVertexLayout, _InData, _InVerticesStride, m_Device, m_PhysicalDevice);
	}

	VertexShader * VulkanRenderContext::CreateVertexShader(const char * _InShaderCode, size_t _InShaderCodeSize, TArray<VertexInput>& _InVertexInputLayout)
	{
		return new VulkanVertexShader(_InShaderCode, _InShaderCodeSize, _InVertexInputLayout, m_Device);
	}

	GeometryShader * VulkanRenderContext::CreateGeometryShader(const char * _InShaderCode, size_t _InShaderCodeSize)
	{
		return new VulkanGeometryShader(_InShaderCode, _InShaderCodeSize, m_Device);
	}

	FragmentShader * VulkanRenderContext::CreateFragmentShader(const char * _InShaderCode, size_t _InShaderCodeSize)
	{
		return new VulkanFragmentShader(_InShaderCode, _InShaderCodeSize, m_Device);
	}

	Shader * VulkanRenderContext::CreateShader(VertexShader * _InVertexShader, GeometryShader * _InGeometryShader, FragmentShader * _InFragmentShader, RenderPass* _InRenderpass)
	{
		return new VulkanShader(_InVertexShader, _InGeometryShader, _InFragmentShader, m_Device, m_PhysicalDevice, ((VulkanRenderPass*)_InRenderpass)->m_Renderpass, m_PipelineCache, *m_Swapchain, m_UBODescriptorPool);
	}

	CommandBuffer * VulkanRenderContext::CreateCommandBuffer()
	{
		return new VulkanCommandBuffer(m_Device, m_GraphicsCommandPool, this);
	}

	RenderPass * VulkanRenderContext::CreateRenderPass(TArray<Image*>& _InImage)
	{
		return new VulkanRenderPass(m_Device, ((VulkanImage*)*_InImage.GetData()), _InImage.Size());
	}

	Framebuffer * VulkanRenderContext::CreateFramebuffer(Extent2D& _InFramebufferSize, RenderPass* _InRenderPass)
	{
		// Image representation render context independant
		//		---------Image -------
		//		|					  |
		//	OpenGLImage			VulkanImage
		TArray<VkImageView> views(((VulkanRenderPass*)_InRenderPass)->m_Attachments.Size());

		for (size_t i = 0U; i < ((VulkanRenderPass*)_InRenderPass)->m_Attachments.Size(); i++)
		{
			views[(uint32)i] = ((VulkanRenderPass*)_InRenderPass)->m_Attachments[(uint32)i]->m_View;
		}

		return new VulkanFramebuffer(m_Device, *((VkExtent2D*)&_InFramebufferSize), *(VulkanRenderPass*)_InRenderPass,
			views.GetData(), views.Size());
	}



	void VulkanRenderContext::CreateInstance(PlatformWindow& _InWindow)
	{
		VkApplicationInfo app_info = {};
		app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		app_info.pNext = VK_NULL_HANDLE;
		app_info.apiVersion = VK_MAKE_VERSION(1, 0, 65); // VK_API_VERSION_1_0
		app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0); // Add macro
		app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		app_info.pApplicationName = _InWindow.GetWindowName();
		app_info.pEngineName = "DadEngine";

		TArray<const char*> layersNames;
		// layersNames.Add("VK_LAYER_LUNARG_standard_validation");
		// layersNames.Add("VK_LAYER_LUNARG_core_validation");
		// layersNames.Add("VK_LAYER_LUNARG_object_tracker");
		// layersNames.Add("VK_LAYER_GOOGLE_threading");

		TArray<const char*> extensionsNames;
		extensionsNames.Add("VK_KHR_surface");
		extensionsNames.Add("VK_KHR_win32_surface");
		extensionsNames.Add(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

		VkInstanceCreateInfo instance_create_info = {};
		instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instance_create_info.pNext = VK_NULL_HANDLE;
		instance_create_info.enabledLayerCount = (uint32)layersNames.Size();
		instance_create_info.ppEnabledLayerNames = layersNames.GetData();
		instance_create_info.enabledExtensionCount = (uint32)extensionsNames.Size();
		instance_create_info.ppEnabledExtensionNames = extensionsNames.GetData();
		instance_create_info.pApplicationInfo = &app_info;
		instance_create_info.flags = 0U;

		VK_CHECK_RESULT(vkCreateInstance(&instance_create_info, VK_NULL_HANDLE, &m_Instance));
	}

	void VulkanRenderContext::CreateDevice()
	{
		TArray<const char*> extensionsNames;
		extensionsNames.Add("VK_KHR_swapchain");

		TArray<const char*> layersNames;
		layersNames.Add("VK_LAYER_LUNARG_standard_validation");
		layersNames.Add("VK_LAYER_LUNARG_object_tracker");
		layersNames.Add("VK_LAYER_LUNARG_core_validation");
		layersNames.Add("VK_LAYER_LUNARG_parameter_validation");
		layersNames.Add("VK_LAYER_GOOGLE_threading");
		layersNames.Add("VK_LAYER_GOOGLE_unique_objects");

		// Queue submiting priority nirmalized float 1.0f = MAX  0.0f = MIN
		TArray<float> queuePriorities;
		queuePriorities.Add(1.0f);

		TArray<VkDeviceQueueCreateInfo> device_queue_create_info;
		device_queue_create_info.Add({
			VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
			VK_NULL_HANDLE,
			NULL,
			m_uiGraphicsQueueFamilyIndex,
			1U,
			queuePriorities.GetData()
		});

		if(m_uiGraphicsQueueFamilyIndex != m_uiPresentationsQueueFamilyIndex)
			device_queue_create_info.Add({
				VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
				VK_NULL_HANDLE,
				NULL,
				m_uiPresentationsQueueFamilyIndex,
				1U,
				queuePriorities.GetData()
			});

		VkPhysicalDeviceFeatures physical_device_features;
		vkGetPhysicalDeviceFeatures(m_PhysicalDevice, &physical_device_features);

		VkDeviceCreateInfo device_create_info = {};
		device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		device_create_info.pNext = VK_NULL_HANDLE;
		device_create_info.queueCreateInfoCount = (uint32)device_queue_create_info.Size();
		device_create_info.pQueueCreateInfos = device_queue_create_info.GetData();
		device_create_info.enabledExtensionCount = (uint32)extensionsNames.Size();
		device_create_info.ppEnabledExtensionNames = extensionsNames.GetData();
		device_create_info.enabledLayerCount = (uint32)layersNames.Size();
		device_create_info.ppEnabledLayerNames = layersNames.GetData();
		device_create_info.pEnabledFeatures = &physical_device_features;
		device_create_info.flags = NULL;

		VK_CHECK_RESULT(vkCreateDevice(m_PhysicalDevice, &device_create_info, VK_NULL_HANDLE, &m_Device));
	}

	void VulkanRenderContext::CreateCommandPool()
	{
		VkCommandPoolCreateInfo graphics_command_pool_create_info = {};
		graphics_command_pool_create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		graphics_command_pool_create_info.pNext = VK_NULL_HANDLE;
		graphics_command_pool_create_info.queueFamilyIndex = m_uiGraphicsQueueFamilyIndex;
		graphics_command_pool_create_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

		VK_CHECK_RESULT(vkCreateCommandPool(m_Device, &graphics_command_pool_create_info, VK_NULL_HANDLE, &m_GraphicsCommandPool));


		VkCommandPoolCreateInfo presentation_command_pool_create_info = {};
		presentation_command_pool_create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		presentation_command_pool_create_info.pNext = VK_NULL_HANDLE;
		presentation_command_pool_create_info.queueFamilyIndex = m_uiPresentationsQueueFamilyIndex;
		presentation_command_pool_create_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

		VK_CHECK_RESULT(vkCreateCommandPool(m_Device, &presentation_command_pool_create_info, VK_NULL_HANDLE, &m_PresentationCommandPool));
	}

	void VulkanRenderContext::CreateDescriptorPool()
	{
		VkDescriptorPoolSize descriptor_pool_size = {};
		descriptor_pool_size.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptor_pool_size.descriptorCount = m_Swapchain->m_SwapchainImages.Size();

		VkDescriptorPoolCreateInfo descriptor_pool_create_info = {};
		descriptor_pool_create_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		descriptor_pool_create_info.pNext = VK_NULL_HANDLE;
		descriptor_pool_create_info.poolSizeCount = 1U;
		descriptor_pool_create_info.pPoolSizes = &descriptor_pool_size;
		descriptor_pool_create_info.maxSets = m_Swapchain->m_SwapchainImages.Size();
		descriptor_pool_create_info.flags = 0U;

		VK_CHECK_RESULT(vkCreateDescriptorPool(m_Device, &descriptor_pool_create_info, VK_NULL_HANDLE, &m_UBODescriptorPool));
	}

	void VulkanRenderContext::CreateSetupCommandBuffer()
	{
		VulkanHelper::CreateCommandBuffer(m_Device, m_GraphicsCommandPool, 1U, &m_SetupCommandBuffer);

		VkCommandBufferBeginInfo command_buffer_begin_info = {};
		command_buffer_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		command_buffer_begin_info.pNext = VK_NULL_HANDLE;
		command_buffer_begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		command_buffer_begin_info.pInheritanceInfo = VK_NULL_HANDLE;

		vkBeginCommandBuffer(m_SetupCommandBuffer, &command_buffer_begin_info);
	}

	void VulkanRenderContext::GetQueues()
	{
		vkGetDeviceQueue(m_Device, m_uiGraphicsQueueFamilyIndex, 0U, &m_GraphicsQueue);
		vkGetDeviceQueue(m_Device, m_uiPresentationsQueueFamilyIndex, 0U, &m_PresentationQueue);
	}

	void VulkanRenderContext::GetPresentationMode(PlatformWindow& _InWindow)
	{
		// Check present modes
		TArray<VkPresentModeKHR> presentModes;

		if (_InWindow.GetVerticalSync() == TRUE)
		{
			presentModes.Add(VK_PRESENT_MODE_FIFO_KHR);
		}

		else
		{
			presentModes.Add(VK_PRESENT_MODE_MAILBOX_KHR);
			presentModes.Add(VK_PRESENT_MODE_IMMEDIATE_KHR);
		}

		uint32 queueFamilyPropertyCount = 0U;
		vkGetPhysicalDeviceQueueFamilyProperties(m_PhysicalDevice, &queueFamilyPropertyCount, VK_NULL_HANDLE);

		TArray<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyPropertyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(m_PhysicalDevice, &queueFamilyPropertyCount, queueFamilyProperties.GetData());

		for (size_t i = 0U; i < presentModes.Size(); i++)
		{
			for (size_t j = 0U; i < queueFamilyProperties.Size(); j++)
			{
				VkBool32 presentationSupported = VK_FALSE;

				vkGetPhysicalDeviceSurfaceSupportKHR(m_PhysicalDevice, (uint32)j, m_PresentationSurface, &presentationSupported);

				if (presentationSupported == VK_TRUE)
				{
					m_uiPresentationsQueueFamilyIndex = (uint32)j;
					m_PresentationMode = presentModes[(uint32)i];
					return;
				}
			}
		}
	}

	void VulkanRenderContext::DestroySetupCommandBuffer()
	{
		vkEndCommandBuffer(m_SetupCommandBuffer);

		VkSubmitInfo submit_info = {};
		submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submit_info.pNext = VK_NULL_HANDLE;

		vkQueueSubmit(m_GraphicsQueue, 1U, &submit_info, VK_NULL_HANDLE);
		vkQueueWaitIdle(m_GraphicsQueue); // To not destroy before the end of submition

		vkFreeCommandBuffers(m_Device, m_GraphicsCommandPool, 1U, &m_SetupCommandBuffer);
	}

	void VulkanRenderContext::CreatePresentationSurface(PlatformWindow& _InWindow)
	{
		VkWin32SurfaceCreateInfoKHR win32_surface_create_info = {};
		win32_surface_create_info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		win32_surface_create_info.pNext = VK_NULL_HANDLE;
		win32_surface_create_info.hinstance = _InWindow.GetWindowHInstance();
		win32_surface_create_info.hwnd = _InWindow.GetWindowHandle();
		win32_surface_create_info.flags = 0U;

		VK_CHECK_RESULT(vkCreateWin32SurfaceKHR(m_Instance, &win32_surface_create_info, VK_NULL_HANDLE, &m_PresentationSurface));
	}

	void VulkanRenderContext::CreateDepthStencilBuffer()
	{
		VkFormat format = VulkanHelper::GetSupportDepthStencilFormats(m_PhysicalDevice);

		m_DepthStencilBuffer = VulkanDepthStencilBuffer(m_Device, format,
			m_Swapchain->m_SwapchainExtent, m_PhysicalDevice,
			VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT, m_SetupCommandBuffer);
	}

	void VulkanRenderContext::CreateRenderpass()
	{
		VulkanImage images[2U] = { m_Swapchain->m_SwapchainImages[0U], m_DepthStencilBuffer };

		m_Renderpass = VulkanRenderPass(m_Device, images, 2U);
	}

	void VulkanRenderContext::CreateSemaphores()
	{
		VkSemaphoreCreateInfo semaphore_create_info = {};
		semaphore_create_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		semaphore_create_info.pNext = VK_NULL_HANDLE;
		semaphore_create_info.flags = 0U;

		VK_CHECK_RESULT(vkCreateSemaphore(m_Device, &semaphore_create_info, VK_NULL_HANDLE, &m_ImageAvailableSemaphore));
		VK_CHECK_RESULT(vkCreateSemaphore(m_Device, &semaphore_create_info, VK_NULL_HANDLE, &m_RenderingFinishedSemaphore));
	}

	void VulkanRenderContext::CreateFences()
	{
		m_CommandBufferAvailables.Resize(m_Swapchain->GetImageCount());

		for (VkFence& fence : m_CommandBufferAvailables)
		{
			VkFenceCreateInfo fence_create_info = {};
			fence_create_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
			fence_create_info.pNext = VK_NULL_HANDLE;
			fence_create_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;

			VK_CHECK_RESULT(vkCreateFence(m_Device, &fence_create_info, VK_NULL_HANDLE, &fence));
		}
	}

	void VulkanRenderContext::CreatePipelineCache()
	{
		VkPipelineCacheCreateInfo pipeline_cache_create_info = {};
		pipeline_cache_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
		pipeline_cache_create_info.pNext = VK_NULL_HANDLE;
		//pipeline_cache_create_info.initialDataSize
		pipeline_cache_create_info.flags = 0U;

		VK_CHECK_RESULT(vkCreatePipelineCache(m_Device, &pipeline_cache_create_info, VK_NULL_HANDLE, &m_PipelineCache));
	}

	void VulkanRenderContext::CreateFramebuffers()
	{
		m_Framebuffers.Resize(m_Swapchain->GetImageCount());

		TArray<VkImageView> attachments(2U);
		attachments[1U] = m_DepthStencilBuffer.m_View;

		for (size_t i = 0U; i < m_Framebuffers.Size(); i++)
		{
			attachments[0U] = m_Swapchain->m_SwapchainImages[(uint32)i].m_View;
			m_Framebuffers[(uint32)i] = VulkanFramebuffer(m_Device, m_Swapchain->m_SwapchainExtent, m_Renderpass, attachments.GetData(), attachments.Size());
		}
	}
}