#ifndef __VULKAN_GEOMETRY_SHADER_HPP_
#define __VULKAN_GEOMETRY_SHADER_HPP_


#include <vulkan/vulkan.h>

#include "../../shader/shader.hpp"


namespace DadEngine
{
    class VulkanGeometryShader : public GeometryShader
    {
        public:
        VulkanGeometryShader(const char *_InCompiledShaderCode, size_t _shaderCodeSize, VkDevice _device);

        ~VulkanGeometryShader();


        VkDevice m_device = nullptr;

        VkShaderModule m_dhaderModule = nullptr;
    };
} // namespace DadEngine

#endif // !__VULKAN_GEOMETRY_SHADER_HPP_
