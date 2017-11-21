#include "VulkanRenderContext.hpp"

#include "VulkanDebug.hpp"

namespace DadEngine::Rendering
{
	VulkanRenderContext::VulkanRenderContext(PlatformWindow& _InWindow)
	{
		//VulkanHelper::EnumerateInstanceLayersAndExtensions();

		m_windowExtent = { (uint32)_InWindow.GetRect().right, (uint32)_InWindow.GetRect().bottom };

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

		m_Swapchain.Initialize(m_Device, m_PhysicalDevice, m_PresentationSurface, m_PresentationMode, _InWindow);

		CreateDepthStencilBuffer();
		DestroySetupCommandBuffer();

		CreateRenderpass();
		CreatePipelineCache();
		CreateFramebuffers();
		CreateSemaphores();
		CreateFences();
		CreateCommandBuffers();
	}

	VulkanRenderContext::~VulkanRenderContext()
	{
		vkFreeCommandBuffers(m_Device, m_GraphicsCommandPool, 1U, &m_setupCommandBuffer);
		vkDestroyCommandPool(m_Device, m_GraphicsCommandPool, VK_NULL_HANDLE);
		vkDestroyDevice(m_Device, VK_NULL_HANDLE);
		VulkanDebug::DestroyVulkanDebug(m_Instance);
		vkDestroyInstance(m_Instance, VK_NULL_HANDLE);
	}


	void VulkanRenderContext::ClearBuffer(Color& _InClearColor)
	{
		VkImageSubresourceRange image_subresource_range = {};
		image_subresource_range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		image_subresource_range.baseArrayLayer = 0U;
		image_subresource_range.baseMipLevel = 0U;
		image_subresource_range.layerCount = 1U;
		image_subresource_range.levelCount = 1U;

		VkClearColorValue color = { _InClearColor.r, _InClearColor.g, _InClearColor.b, _InClearColor.a };
		VkClearDepthStencilValue depthStencil = { 1.0f, 0.0f };


		vkCmdClearColorImage(m_GraphicCommandBuffers[m_uiNextImage].m_cmdBuffer, m_Swapchain.m_SwapchainImages[m_uiNextImage].image,
			VK_IMAGE_LAYOUT_UNDEFINED, &color, 1U, &image_subresource_range);

		vkCmdClearDepthStencilImage(m_GraphicCommandBuffers[m_uiNextImage].m_cmdBuffer, m_Swapchain.m_SwapchainImages[m_uiNextImage].image,
			VK_IMAGE_LAYOUT_UNDEFINED, &depthStencil, 1U, &image_subresource_range);
	}

	void VulkanRenderContext::BeginFrame()
	{
		m_uiNextImage = m_Swapchain.GetNextImageIndex(m_ImageAvailableSemaphore);

		VkClearColorValue color = { 0.f, 1.f, 0.f, 1.f };
		VkClearValue clearValues[2U] = { { color },{ 1.0f, 0.0f } };
		VkRect2D renderArea = { { 0, 0 }, m_Swapchain.m_SwapchainExtent };

		VkRenderPassBeginInfo render_pass_begin_info = {};
		render_pass_begin_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		render_pass_begin_info.pNext = VK_NULL_HANDLE;
		render_pass_begin_info.framebuffer = m_Framebuffers[m_uiNextImage];
		render_pass_begin_info.renderPass = m_Renderpass;
		render_pass_begin_info.renderArea = renderArea;
		render_pass_begin_info.clearValueCount = 2U;
		render_pass_begin_info.pClearValues = clearValues;


		// Wait for the command buffer to be available
		vkWaitForFences(m_Device, 1U, &m_CommandBufferAvailables[m_uiNextImage], VK_FALSE, INFINITE);
		vkResetFences(m_Device, 1U, &m_CommandBufferAvailables[m_uiNextImage]);

		m_GraphicCommandBuffers[m_uiNextImage].BeginRecord();
		vkCmdBeginRenderPass(m_GraphicCommandBuffers[m_uiNextImage].m_cmdBuffer, &render_pass_begin_info, VK_SUBPASS_CONTENTS_INLINE);
	}

	void VulkanRenderContext::Present()
	{
		vkCmdEndRenderPass(m_GraphicCommandBuffers[m_uiNextImage].m_cmdBuffer);
		m_GraphicCommandBuffers[m_uiNextImage].EndRecord();

		VkPipelineStageFlags wait_pipelinestage_flag = VK_PIPELINE_STAGE_TRANSFER_BIT;

		VkSubmitInfo submit_info = {};
		submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submit_info.pNext = VK_NULL_HANDLE;
		submit_info.commandBufferCount = 1U;
		submit_info.pCommandBuffers = &m_GraphicCommandBuffers[m_uiNextImage].m_cmdBuffer;
		submit_info.waitSemaphoreCount = 1U;
		submit_info.pWaitSemaphores = &m_ImageAvailableSemaphore;
		submit_info.signalSemaphoreCount = 1U;
		submit_info.pSignalSemaphores = &m_RenderingFinishedSemaphore;
		submit_info.pWaitDstStageMask = &wait_pipelinestage_flag;

		VK_CHECK_RESULT(vkQueueSubmit(m_GraphicsQueue, 1U, &submit_info, m_CommandBufferAvailables[m_uiNextImage]));

		m_Swapchain.Present(m_GraphicsQueue, m_RenderingFinishedSemaphore, m_uiNextImage);
	}



	void VulkanRenderContext::DrawPrimitives()
	{

	}

	void VulkanRenderContext::Draw(VertexBuffer* _InVertexBuffer)
	{
		// Rethink vulkan command buffers
		vkCmdDraw(m_GraphicCommandBuffers[m_uiNextImage].m_cmdBuffer, _InVertexBuffer->m_uiVertexCount, 1U, 0U, 0U);
	}

	void VulkanRenderContext::BindVertexBuffer(VertexBuffer* _InVertexBuffer)
	{
		VkDeviceSize deviceSize = 0U;

		vkCmdBindVertexBuffers(
			m_GraphicCommandBuffers[m_uiNextImage].m_cmdBuffer,
			0U,
			1U,
			&((VulkanVertexBuffer*)_InVertexBuffer)->m_buffer,
			&deviceSize);
	}

	void VulkanRenderContext::BindShaderProgram(Shader* _InShader)
	{
		vkCmdBindPipeline(m_GraphicCommandBuffers[m_uiNextImage].m_cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, ((VulkanShader*)_InShader)->m_graphics_pipeline);
	}


	void VulkanRenderContext::SetViewport(Viewport& _InViewport)
	{
		VkCommandBuffer currentCommandBuffer = nullptr;

		//vkCmdSetViewport(currentCommandBuffer, 0U, 1U, )
	}

	void VulkanRenderContext::SetCullingMode(CullingMode _InCullingMode)
	{
		// Pipeline related
	}

	void VulkanRenderContext::SetFillMode(FillMode _InFillMode)
	{
		// Pipeline related
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

	Shader * VulkanRenderContext::CreateShader(VertexShader * _InVertexShader, GeometryShader * _InGeometryShader, FragmentShader * _InFragmentShader)
	{
		return new VulkanShader(_InVertexShader, _InGeometryShader, _InFragmentShader, m_Device, m_Renderpass, m_PipelineCache, m_Swapchain);
	}


	void VulkanRenderContext::CreateInstance(PlatformWindow& _InWindow)
	{
		VkApplicationInfo app_info = {};
		app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		app_info.pNext = VK_NULL_HANDLE;
		app_info.apiVersion = VK_MAKE_VERSION(1, 0, 51); // VK_API_VERSION_1_0
		app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0); // Add macro
		app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		app_info.pApplicationName = _InWindow.GetWindowName();
		app_info.pEngineName = "DadEngine";

		TArray<const char*> layersNames;
		layersNames.Add("VK_LAYER_LUNARG_standard_validation");
		layersNames.Add("VK_LAYER_LUNARG_core_validation");
		layersNames.Add("VK_LAYER_LUNARG_object_tracker");
		layersNames.Add("VK_LAYER_GOOGLE_threading");

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

	void VulkanRenderContext::CreateCommandBuffers()
	{
		uint32 uiSwapchainImageCount = m_Swapchain.GetImageCount();

		m_GraphicCommandBuffers.Resize(uiSwapchainImageCount);
		//VulkanHelper::CreateCommandBuffer(m_Device, m_GraphicsCommandPool, uiSwapchainImageCount, m_GraphicCommandBuffers.GetData());
		for (VulkanCommandBuffer& cmdbuffer : m_GraphicCommandBuffers)
		{
			cmdbuffer.Initialize(m_Device, m_GraphicsCommandPool);
		}

		m_PresentationCommandBuffers.Resize(uiSwapchainImageCount);
		//VulkanHelper::CreateCommandBuffer(m_Device, m_PresentationCommandPool, uiSwapchainImageCount, m_PresentationCommandBuffers.GetData());
		for (VulkanCommandBuffer& cmdbuffer : m_PresentationCommandBuffers)
		{
			cmdbuffer.Initialize(m_Device, m_PresentationCommandPool);
		}
	}

	void VulkanRenderContext::CreateSetupCommandBuffer()
	{
		VulkanHelper::CreateCommandBuffer(m_Device, m_GraphicsCommandPool, 1U, &m_setupCommandBuffer);

		VkCommandBufferBeginInfo command_buffer_begin_info = {};
		command_buffer_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		command_buffer_begin_info.pNext = VK_NULL_HANDLE;
		command_buffer_begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		command_buffer_begin_info.pInheritanceInfo = VK_NULL_HANDLE;

		vkBeginCommandBuffer(m_setupCommandBuffer, &command_buffer_begin_info);
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
		vkEndCommandBuffer(m_setupCommandBuffer);

		VkSubmitInfo submit_info = {};
		submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submit_info.pNext = VK_NULL_HANDLE;

		vkQueueSubmit(m_GraphicsQueue, 1U, &submit_info, VK_NULL_HANDLE);
		vkQueueWaitIdle(m_GraphicsQueue); // To not destroy before the end of submition

		vkFreeCommandBuffers(m_Device, m_GraphicsCommandPool, 1U, &m_setupCommandBuffer);
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
		m_depthStencilBuffer.format = VulkanHelper::GetSupportDepthStencilFormats(m_PhysicalDevice);

		VkImageCreateInfo image_create_info = {};
		image_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		image_create_info.pNext = VK_NULL_HANDLE;
		image_create_info.arrayLayers = 1U;
		image_create_info.format = m_depthStencilBuffer.format;
		image_create_info.mipLevels = 1U;
		image_create_info.samples = VK_SAMPLE_COUNT_1_BIT;
		image_create_info.queueFamilyIndexCount = 0U;
		image_create_info.pQueueFamilyIndices = VK_NULL_HANDLE;
		image_create_info.tiling = VK_IMAGE_TILING_OPTIMAL;
		image_create_info.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
		image_create_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;//VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		image_create_info.imageType = VK_IMAGE_TYPE_2D;
		image_create_info.extent = { m_Swapchain.m_SwapchainExtent.width, m_Swapchain.m_SwapchainExtent.height, 1U };
		image_create_info.flags = 0U;

		VK_CHECK_RESULT(vkCreateImage(m_Device, &image_create_info, VK_NULL_HANDLE, &m_depthStencilBuffer.image));

		VkMemoryRequirements memory_requierements = {};

		vkGetImageMemoryRequirements(m_Device, m_depthStencilBuffer.image, &memory_requierements);

		VkMemoryAllocateInfo memory_allocation_info = {};
		memory_allocation_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		memory_allocation_info.pNext = VK_NULL_HANDLE;
		memory_allocation_info.memoryTypeIndex = VulkanHelper::CheckMemoryType(memory_requierements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_PhysicalDeviceMemoryProperties);
		memory_allocation_info.allocationSize = memory_requierements.size;

		VK_CHECK_RESULT(vkAllocateMemory(m_Device, &memory_allocation_info, VK_NULL_HANDLE, &m_depthStencilBuffer.memory));
		VK_CHECK_RESULT(vkBindImageMemory(m_Device, m_depthStencilBuffer.image, m_depthStencilBuffer.memory, 0U));

		VkImageViewCreateInfo image_view_create_info = {};
		image_view_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		image_view_create_info.pNext = VK_NULL_HANDLE;
		image_view_create_info.format = m_depthStencilBuffer.format;
		image_view_create_info.image = m_depthStencilBuffer.image;
		image_view_create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
		image_view_create_info.subresourceRange.baseArrayLayer = 0U;
		image_view_create_info.subresourceRange.layerCount = 1U;
		image_view_create_info.subresourceRange.baseMipLevel = 0U;
		image_view_create_info.subresourceRange.levelCount = 1U;
		image_view_create_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
		//image_view_create_info.components = { VK_COMPONENT_SWIZZLE_R };
		image_view_create_info.flags = 0U;

		// Need the image to be allocated in memory
		VK_CHECK_RESULT(vkCreateImageView(m_Device, &image_view_create_info, VK_NULL_HANDLE, &m_depthStencilBuffer.view));

		VulkanHelper::SetImageLayout(m_setupCommandBuffer, m_depthStencilBuffer.image, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT);
	}

	void VulkanRenderContext::CreateRenderpass()
	{
		VkAttachmentDescription attachments[2] = {};
		attachments[0].format = m_Swapchain.GetFormat();
		attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
		attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		attachments[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;


		attachments[1].format = m_depthStencilBuffer.format;
		attachments[1].samples = VK_SAMPLE_COUNT_1_BIT;
		attachments[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		attachments[1].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		attachments[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachments[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attachments[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		attachments[1].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentReference color_attachement_reference = {};
		color_attachement_reference.attachment = 0U;
		color_attachement_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkAttachmentReference depth_stencil_attachement_reference = {};
		depth_stencil_attachement_reference.attachment = 1U;
		depth_stencil_attachement_reference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;


		VkSubpassDescription subpass_description = {};
		subpass_description.flags = 0U;
		subpass_description.colorAttachmentCount = 1U;
		subpass_description.pColorAttachments = &color_attachement_reference;
		subpass_description.pDepthStencilAttachment = &depth_stencil_attachement_reference;
		subpass_description.inputAttachmentCount = 0U;
		subpass_description.pInputAttachments = VK_NULL_HANDLE;
		subpass_description.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass_description.preserveAttachmentCount = 0U;
		subpass_description.pPreserveAttachments = VK_NULL_HANDLE;


		// Dependency to prepare implicit barrier
		TArray<VkSubpassDependency> dependencies(2U);
		dependencies[0U].srcSubpass = VK_SUBPASS_EXTERNAL;
		dependencies[0U].dstSubpass = 0;
		dependencies[0U].srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
		dependencies[0U].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependencies[0U].srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
		dependencies[0U].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		dependencies[0U].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

		dependencies[1U].srcSubpass = 0;
		dependencies[1U].dstSubpass = VK_SUBPASS_EXTERNAL;
		dependencies[1U].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependencies[1U].dstStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
		dependencies[1U].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		dependencies[1U].dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
		dependencies[1U].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;


		VkRenderPassCreateInfo renderpass_create_info = {};
		renderpass_create_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderpass_create_info.pNext = VK_NULL_HANDLE;
		renderpass_create_info.attachmentCount = 2U;
		renderpass_create_info.pAttachments = attachments;
		renderpass_create_info.subpassCount = 1U;
		renderpass_create_info.pSubpasses = &subpass_description;
		renderpass_create_info.dependencyCount = 2U;
		renderpass_create_info.pDependencies = dependencies.GetData();
		renderpass_create_info.flags = 0U;

		VK_CHECK_RESULT(vkCreateRenderPass(m_Device, &renderpass_create_info, VK_NULL_HANDLE, &m_Renderpass));
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
		m_CommandBufferAvailables.Resize(m_Swapchain.GetImageCount());

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
		VkImageView attachments [2U]  = {};
		attachments[1U] = m_depthStencilBuffer.view;

		VkFramebufferCreateInfo framebuffer_create_info = {};
		framebuffer_create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebuffer_create_info.pNext = VK_NULL_HANDLE;
		framebuffer_create_info.attachmentCount = 2U;
		framebuffer_create_info.pAttachments = attachments;
		framebuffer_create_info.renderPass = m_Renderpass;
		framebuffer_create_info.width = m_Swapchain.m_SwapchainExtent.width;
		framebuffer_create_info.height = m_Swapchain.m_SwapchainExtent.height;
		framebuffer_create_info.layers = 1U;
		framebuffer_create_info.flags = 0U;

		m_Framebuffers.Resize(m_Swapchain.GetImageCount());

		for (size_t i = 0U; i < m_Framebuffers.Size(); i++)
		{

			attachments[0U] = m_Swapchain.m_SwapchainImages[(uint32)i].view;

			VK_CHECK_RESULT(vkCreateFramebuffer(m_Device, &framebuffer_create_info, VK_NULL_HANDLE, &m_Framebuffers[(uint32)i]));
		}
	}
}