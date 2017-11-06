#ifndef __VULKAN_VERTEX_SHADER_HPP_
#define __VULKAN_VERTEX_SHADER_HPP_


namespace DadEngine::Rendering
{
	class VulkanVertexShader : public VertexShader
	{
	public:

		VulkanVertexShader(const char* _InCompiledShaderCode, size_t _InShaderCodeSize, TArray<VertexInput>& _InVertexLayout, VkDevice _InDevice)
			: VertexShader(_InCompiledShaderCode, _InVertexLayout)
		{
			VkShaderModuleCreateInfo shaderModuleCreateInfo = {};
			shaderModuleCreateInfo.sType	= VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			shaderModuleCreateInfo.pNext	= VK_NULL_HANDLE;
			shaderModuleCreateInfo.pCode	= (uint32*)_InCompiledShaderCode;
			shaderModuleCreateInfo.codeSize = _InShaderCodeSize;
			shaderModuleCreateInfo.flags	= 0U;

			vkCreateShaderModule(_InDevice, &shaderModuleCreateInfo, VK_NULL_HANDLE, &m_ShaderModule);
		}


		VkShaderModule m_ShaderModule = VK_NULL_HANDLE;
	};
}

#endif //!__VULKAN_VERTEX_SHADER_HPP_