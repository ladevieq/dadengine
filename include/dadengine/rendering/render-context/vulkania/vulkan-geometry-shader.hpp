#ifndef __VULKAN_GEOMETRY_SHADER_HPP_
#define __VULKAN_GEOMETRY_SHADER_HPP_


#include <vulkan/vulkan.hpp>

#include "../../shader/shader.hpp"


namespace DadEngine::Rendering
{
    class VulkanGeometryShader : public GeometryShader
    {
        public:
        VulkanGeometryShader(const char *_InCompiledShaderCode, size_t _InShaderCodeSize, VkDevice _InDevice);

        ~VulkanGeometryShader();


        VkDevice m_Device = VK_NULL_HANDLE;

        VkShaderModule m_ShaderModule = VK_NULL_HANDLE;
    };
} // namespace DadEngine::Rendering

#endif // !__VULKAN_GEOMETRY_SHADER_HPP_