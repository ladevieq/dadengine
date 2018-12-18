#ifndef __VULKAN_SHADER_HPP_
#define __VULKAN_SHADER_HPP_

#include <vulkan/vulkan.hpp>

#include "../../Shader/Shader.hpp"


namespace DadEngine::Rendering
{
    class VulkanSwapchain;

	class VulkanUBO
	{

	public:
        VulkanUBO(VkDevice _InDevice, VkPhysicalDevice _InPhysicalDevice);

		void UpdateUBO(VkDevice _InDevice, VkDescriptorSet _InDescriptorSet);


		VkDescriptorBufferInfo m_bufferInfo = {};
		VkBuffer m_buffer = VK_NULL_HANDLE;
		VkDeviceMemory m_memory = VK_NULL_HANDLE;
		VkDeviceSize m_bufferSize = 0U;
	};


	// Pipeline object
	class VulkanShader : public Shader
	{
	public:

		VulkanShader(VertexShader *_InVertexShader,
                 GeometryShader *_InGeometryShader,
                 FragmentShader *_InFragmentShader,
                 VkDevice _InDevice,
                 VkPhysicalDevice _InPhysicalDevice,
                 VkRenderPass _InRenderPass,
                 VkPipelineCache _InPipelineCache,
                 VulkanSwapchain &_InSwapchain,
                 VkDescriptorPool _InDescriptorPool);


		~VulkanShader();

		void AddShaderBinding(VkDescriptorType _InDescriptorType, VkShaderStageFlags _InShaderStagesFlag);

		void createDescriptorSetLayout();

		void createDescriptorSet(VkDescriptorPool _InDescritptorPool);

		void UpdateUBO();


		// Parameters array
		VulkanUBO m_ShaderUBO;

		TArray<VkDescriptorSetLayoutBinding> m_PipelineParameters; // Basic shader currently use one UBO with basic matrices

		VkDescriptorSetLayout m_DescriptorSetLayout = VK_NULL_HANDLE;

		VkDescriptorSet m_DescriptorSet = VK_NULL_HANDLE;

		VkPipelineLayout m_PipelineLayout = VK_NULL_HANDLE;

		VkPipeline m_GraphicsPipeline = VK_NULL_HANDLE;

		VkDevice m_Device = VK_NULL_HANDLE;
	};
}


#endif // !__VULKAN_SHADER_HPP_