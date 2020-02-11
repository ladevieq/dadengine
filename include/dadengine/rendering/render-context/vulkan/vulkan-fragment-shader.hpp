#ifndef __VULKAN_FRAGMENT_SHADER_HPP_
#define __VULKAN_FRAGMENT_SHADER_HPP_

#include <vulkan/vulkan.h>

#include "../../shader/shader.hpp"

namespace DadEngine
{
	class VulkanFragmentShader: public FragmentShader
	{
	public:

		VulkanFragmentShader(const char* _compiledShaderCode, size_t _shaderCodeSize, VkDevice _device);

		~VulkanFragmentShader();


		VkDevice m_device = nullptr;

		VkShaderModule m_shaderModule = nullptr;
	};
}

#endif // !__VULKAN_FRAGMENT_SHADER_HPP_
