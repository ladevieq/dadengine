#ifndef __VULKAN_VERTEX_SHADER_HPP_
#define __VULKAN_VERTEX_SHADER_HPP_

#include <vulkan/vulkan.h>

#include "../../../core/core.hpp"

#include "../../shader/shader.hpp"

namespace DadEngine::Rendering
{
	class VulkanVertexShader : public VertexShader
	{
	public:

		VulkanVertexShader(const char *_InCompiledShaderCode,
                       size_t _InShaderCodeSize,
                       TArray<VertexInput> &_InVertexLayout,
                       VkDevice _InDevice);


		~VulkanVertexShader();


		VkDevice m_Device = VK_NULL_HANDLE;

		VkShaderModule m_ShaderModule = VK_NULL_HANDLE;
	};
}

#endif //!__VULKAN_VERTEX_SHADER_HPP_