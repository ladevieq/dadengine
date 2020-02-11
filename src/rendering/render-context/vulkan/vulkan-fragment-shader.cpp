#include "vulkan-fragment-shader.hpp"

namespace DadEngine
{
    VulkanFragmentShader::VulkanFragmentShader(const char *_compiledShaderCode, size_t _shaderCodeSize, VkDevice _device)
        : FragmentShader(_compiledShaderCode), m_device(_device)
    {
        VkShaderModuleCreateInfo shaderModuleCreateInfo = {};
        shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        shaderModuleCreateInfo.pNext = nullptr;
        shaderModuleCreateInfo.pCode = (uint32_t *)_compiledShaderCode;
        shaderModuleCreateInfo.codeSize = _shaderCodeSize;
        shaderModuleCreateInfo.flags = 0U;

        vkCreateShaderModule(_device, &shaderModuleCreateInfo, VK_NULL_HANDLE, &m_shaderModule);
    }

    VulkanFragmentShader::~VulkanFragmentShader()
    {
        // vkDestroyShaderModule(m_Device, m_ShaderModule, VK_NULL_HANDLE);
    }
}
