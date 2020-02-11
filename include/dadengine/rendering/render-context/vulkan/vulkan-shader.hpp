#ifndef __VULKAN_SHADER_HPP_
#define __VULKAN_SHADER_HPP_

#include <vulkan/vulkan.h>
#include <vector>

#include "../../shader/shader.hpp"


namespace DadEngine
{
    class VulkanSwapchain;

	class VulkanUBO
	{

	public:
        VulkanUBO(VkDevice _InDevice, VkPhysicalDevice _InPhysicalDevice);

		void UpdateUBO(VkDevice _device, VkDescriptorSet _descriptorSet);


		VkDescriptorBufferInfo m_bufferInfo = {};
		VkBuffer m_buffer = nullptr;
		VkDeviceMemory m_memory = nullptr;
		VkDeviceSize m_bufferSize = 0U;
	};


	// Pipeline object
	class VulkanShader : public Shader
	{
	public:

		VulkanShader(VertexShader *_vertexShader,
                 GeometryShader *_geometryShader,
                 FragmentShader *_fragmentShader,
                 VkDevice _device,
                 VkPhysicalDevice _physicalDevice,
                 VkRenderPass _renderPass,
                 VkPipelineCache _pipelineCache,
                 VulkanSwapchain &_swapchain,
                 VkDescriptorPool _descriptorPool);


		~VulkanShader();

		void AddShaderBinding(VkDescriptorType _descriptorType, VkShaderStageFlags _shaderStagesFlag);

		void createDescriptorSetLayout();

		void createDescriptorSet(VkDescriptorPool _descritptorPool);

		void UpdateUBO();


		// Parameters array
		VulkanUBO m_ShaderUBO;

                std::vector<VkDescriptorSetLayoutBinding> m_pipelineParameters; // Basic shader currently use one UBO with basic matrices

		VkDescriptorSetLayout m_descriptorSetLayout = nullptr;

		VkDescriptorSet m_descriptorSet = nullptr;

		VkPipelineLayout m_pipelineLayout = nullptr;

		VkPipeline m_graphicsPipeline = nullptr;

		VkDevice m_device = nullptr;
	};
}


#endif // !__VULKAN_SHADER_HPP_
