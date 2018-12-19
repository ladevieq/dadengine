#include "VulkanFragmentShader.hpp"

namespace DadEngine::Rendering
{
    VulkanFragmentShader::VulkanFragmentShader(const char *_InCompiledShaderCode, size_t _InShaderCodeSize, VkDevice _InDevice)
        : FragmentShader(_InCompiledShaderCode), m_Device(_InDevice)
    {
        VkShaderModuleCreateInfo shaderModuleCreateInfo = {};
        shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        shaderModuleCreateInfo.pNext = VK_NULL_HANDLE;
        shaderModuleCreateInfo.pCode = (uint32_t *)_InCompiledShaderCode;
        shaderModuleCreateInfo.codeSize = _InShaderCodeSize;
        shaderModuleCreateInfo.flags = 0U;

        vkCreateShaderModule(_InDevice, &shaderModuleCreateInfo, VK_NULL_HANDLE, &m_ShaderModule);
    }

    VulkanFragmentShader::~VulkanFragmentShader()
    {
        // vkDestroyShaderModule(m_Device, m_ShaderModule, VK_NULL_HANDLE);
    }
}