#ifndef __VULKAN_FRAGMENT_SHADER_HPP_
#define __VULKAN_FRAGMENT_SHADER_HPP_

#include <vulkan/vulkan.hpp>

#include "../../shader/shader.hpp"

namespace DadEngine::Rendering
{
	class VulkanFragmentShader: public FragmentShader
	{
	public:

		VulkanFragmentShader(const char* _InCompiledShaderCode, size_t _InShaderCodeSize, VkDevice _InDevice);

		~VulkanFragmentShader();


		VkDevice m_Device = VK_NULL_HANDLE;

		VkShaderModule m_ShaderModule = VK_NULL_HANDLE;
	};
}

#endif // !__VULKAN_FRAGMENT_SHADER_HPP_