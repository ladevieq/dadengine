#ifndef __VULKAN_GEOMETRY_SHADER_HPP_
#define __VULKAN_GEOMETRY_SHADER_HPP_


namespace DadEngine::Rendering
{
	class VulkanGeometryShader : public GeometryShader
	{
	public:

		VulkanGeometryShader(const char* _InCompiledShaderCode, size_t _InShaderCodeSize, VkDevice _InDevice)
			: GeometryShader(_InCompiledShaderCode), m_Device(_InDevice)
		{
			VkShaderModuleCreateInfo shaderModuleCreateInfo = {};
			shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			shaderModuleCreateInfo.pNext = VK_NULL_HANDLE;
			shaderModuleCreateInfo.pCode = (uint32*)_InCompiledShaderCode;
			shaderModuleCreateInfo.codeSize = _InShaderCodeSize;
			shaderModuleCreateInfo.flags = 0U;

			vkCreateShaderModule(_InDevice, &shaderModuleCreateInfo, VK_NULL_HANDLE, &m_ShaderModule);
		}

		~VulkanGeometryShader()
		{
			vkDestroyShaderModule(m_Device, m_ShaderModule, VK_NULL_HANDLE);
		}


		VkDevice m_Device = VK_NULL_HANDLE;

		VkShaderModule m_ShaderModule = VK_NULL_HANDLE;
	};
}

#endif // !__VULKAN_GEOMETRY_SHADER_HPP_