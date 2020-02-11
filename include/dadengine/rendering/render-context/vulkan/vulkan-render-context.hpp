#ifndef __VULKAN_RENDER_CONTEXT_HPP_
#define __VULKAN_RENDER_CONTEXT_HPP_

#include <vulkan/vulkan.hpp>

#include "../../../core/core.hpp"
#include "../../../window/windows-window.hpp"
#include "../render-context.hpp"

#include "vulkan-depth-stencil-buffer.hpp"
#include "vulkan-renderpass.hpp"

namespace DadEngine
{
    class VulkanSwapchain;
    class VulkanImage;
	class VulkanFramebuffer;

	class VulkanRenderContext : public RenderContext
	{

	public:

		VulkanRenderContext(Window& _window);
		~VulkanRenderContext();

		void ClearColorBuffer(Color& _clearColor, CommandBuffer* _commandBuffer) override final;

		void ClearDepthStencilBuffer(float _depthValue,
                                     uint32_t _stencilValue,
                                     CommandBuffer *_commandBuffer) override final;

		void Present(CommandBuffer* _commandBuffer) override final;

		void Draw(VertexBuffer* _vertexBuffer, CommandBuffer* _commandBuffer) override final;

		void DrawMultiples(VertexBuffer* _vertexBuffer, int32_t _instanceCount, CommandBuffer* _commandBuffer) override final;

		void BindVertexBuffer(VertexBuffer* _InVertexBuffer, CommandBuffer* _InCommandBuffer) override final;

		void BindShaderProgram(Shader* _InShader, CommandBuffer* _InCommandBuffer) override final;

		void BeginRenderPass(RenderPass* _InRenderPass, Framebuffer* _InFrameBuffer, CommandBuffer* _InCommandBuffer) override final;

		void EndRenderPass(CommandBuffer* _InCommandBuffer) override final;


		void SetViewport(Viewport& _InViewport, CommandBuffer* _InCommandBuffer) override final;

		void SetCullingMode(CullingMode _InCullingMode, CommandBuffer* _InCommandBuffer) override final;

		void SetFillMode(FillMode _InFillMode, CommandBuffer* _InCommandBuffer) override final;


		Image* GetBackBuffer() override final;

		Image* GetDepthStencilBuffer() override final;

		Framebuffer* GetBackFramebuffer() override final;

		RenderPass* GetRenderPass() override final;


		void BeginFrame() override final;

		void EndFrame() override final;

		void SubmitCommandBuffer(CommandBuffer* _InCommandBuffer) override final;


		VertexBuffer *CreateVertexBuffer(uint32_t _InVertexCount,
                                         TArray<float> &_InData,
                                         TArray<VertexInput> &_InVertexLayout,
                                         uint32_t _InVerticesStride) override final;
		VertexShader* CreateVertexShader(const char* _InShaderCode, size_t _InShaderCodeSize, TArray<VertexInput>& _InVertexInputLayout) override final;
		GeometryShader* CreateGeometryShader(const char* _InShaderCode, size_t _InShaderCodeSize) override final;
		FragmentShader* CreateFragmentShader(const char* _InShaderCode, size_t _InShaderCodeSize) override final;
		Shader* CreateShader(VertexShader* _InVertexShader, GeometryShader* _InGeometryShader, FragmentShader* _InFragmentShader, RenderPass* _InRenderpass) override final;
		CommandBuffer* CreateCommandBuffer() override final;
		RenderPass* CreateRenderPass(TArray<Image*>& _InImage) override final;
		Framebuffer* CreateFramebuffer(Extent2D& _InFramebufferSize, RenderPass* _InRenderPass) override final;


	private:

		void CreateInstance(Window& _InWindow);

		void CreateDevice();

		void CreateCommandPool();

		void CreateDescriptorPool();

		void CreateSetupCommandBuffer();

		void GetQueues(); // Present and Graphics

		void GetPresentationMode(Window& _window);

		void DestroySetupCommandBuffer();

		void CreatePresentationSurface(Window& _window);

		void CreateDepthStencilBuffer();

		void CreateRenderpass();

		void CreateSemaphores();

		void CreateFences();

		void CreatePipelineCache();

		void CreateFramebuffers();


		uint32_t m_uiGraphicsQueueFamilyIndex = 0U;
        uint32_t m_uiPresentationsQueueFamilyIndex = 0U;

		VkInstance m_Instance = nullptr;
		VkDevice m_Device = nullptr; // Logical device
		VkPhysicalDevice m_PhysicalDevice = nullptr;
		VkPhysicalDeviceMemoryProperties m_PhysicalDeviceMemoryProperties;

		VkQueue m_GraphicsQueue = nullptr;
		VkQueue m_PresentationQueue = nullptr;

		VkSemaphore m_ImageAvailableSemaphore = nullptr;
		VkSemaphore m_RenderingFinishedSemaphore = nullptr;

                std::vector<VkFence> m_CommandBufferAvailables;

		VkCommandPool m_GraphicsCommandPool = nullptr;
		VkCommandPool m_PresentationCommandPool = nullptr;

		VkDescriptorPool m_UBODescriptorPool = nullptr;

		VkCommandBuffer m_SetupCommandBuffer = nullptr;
		//TArray<VulkanCommandBuffer> m_FinalCommandBuffers;

                std::vector<VkCommandBuffer> m_SubmittedCommandBuffers;

		VulkanSwapchain* m_Swapchain = nullptr;

		VkSurfaceKHR m_PresentationSurface = nullptr;

		VkExtent2D m_WindowExtent;

		VulkanImage* m_BackBuffer = nullptr;
		VulkanDepthStencilBuffer m_DepthStencilBuffer;

		VulkanRenderPass m_Renderpass;
		//VkRenderPass m_Renderpass = VK_NULL_HANDLE;
		//TArray<VkRenderPass> m_Renderpasses;

		VkPipelineCache m_PipelineCache = nullptr;

		VkPresentModeKHR m_PresentationMode;

                std::vector<VulkanFramebuffer> m_Framebuffers;

		uint32_t m_uiNextImage = 0U;
	};
}

#endif //__VULKAN_RENDER_CONTEXT_HPP_
