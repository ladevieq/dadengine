#ifndef __VULKAN_DEBUG_HPP_
#define __VULKAN_DEBUG_HPP_


#include <vulkan/vulkan.h>

#include "../../Core/Core.hpp"

#define VK_CHECK_RESULT(result) if (result != VK_SUCCESS)	\
									throw

namespace DadEngine::Rendering::VulkanDebug
{
	VkBool32 VKAPI_PTR MessageCallback(VkDebugReportFlagsEXT _InFlag, VkDebugReportObjectTypeEXT _InObjectType,
		uint64 _InSrcObject, size_t _InMemoryLocation,
		int32 _InMessageCode, const char* _inPrefixLayer,
		const char* _InMessage, void* _InUserData);

	void InitializeVulkanDebug(VkInstance& _InInstance);

	void DestroyVulkanDebug(VkInstance& _InInstance);
}

#endif //__VULKAN_DEBUG_HPP_