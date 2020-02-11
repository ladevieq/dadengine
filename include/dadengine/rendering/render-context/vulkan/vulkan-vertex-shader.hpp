#ifndef __VULKAN_VERTEX_SHADER_HPP_
#define __VULKAN_VERTEX_SHADER_HPP_

#include <vulkan/vulkan.h>

#include "../../../core/core.hpp"

#include "../../shader/shader.hpp"

namespace DadEngine
{
	class VulkanVertexShader : public VertexShader
	{
	public:

		VulkanVertexShader(const char *_InCompiledShaderCode,
                       size_t _InShaderCodeSize,
                       std::vector<VertexInput> &_InVertexLayout,
                       VkDevice _InDevice);


		~VulkanVertexShader();


		VkDevice m_device = nullptr;

		VkShaderModule m_shaderModule = nullptr;
	};
}

#endif //!__VULKAN_VERTEX_SHADER_HPP_
