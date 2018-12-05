#include "VulkanDebug.hpp"


namespace DadEngine::Rendering::VulkanDebug
{
	PFN_vkCreateDebugReportCallbackEXT CreateDebugReportCallback = VK_NULL_HANDLE;
	PFN_vkDestroyDebugReportCallbackEXT DestroyDebugReportCallback = VK_NULL_HANDLE;
	PFN_vkDebugReportMessageEXT DebugReportMessage = VK_NULL_HANDLE;

	VkDebugReportCallbackEXT DebugReportCallback;

	VkBool32 VKAPI_PTR MessageCallback(VkDebugReportFlagsEXT _InFlag, VkDebugReportObjectTypeEXT _InObjectType, uint64 _InSrcObject, size_t _InMemoryLocation, int32 _InMessageCode, const char* _inPrefixLayer, const char * _InMessage, void * _InUserData)
	{
		DebugReport report;

		if (_InFlag & VK_DEBUG_REPORT_ERROR_BIT_EXT) {
			report.m_uiContextFlag = DEBUG_REPORT_CONTEXT_VULKAN;
			report.m_uiReportTypeFlag = DEBUG_REPORT_TYPE_ERROR;
			report.m_uiReportCode = _InMessageCode;
			report.m_sMessage = _InMessage;
			//printf("%s%s%s%d%s%s\n", "ERROR: [", _inPrefixLayer, "] Code ", _InMessageCode, " : ", _InMessage);
			LogDebugReport(report);
		}
		else if (_InFlag & VK_DEBUG_REPORT_WARNING_BIT_EXT) {
			report.m_uiContextFlag = DEBUG_REPORT_CONTEXT_VULKAN;
			report.m_uiReportTypeFlag = DEBUG_REPORT_TYPE_WARNING;
			report.m_uiReportCode = _InMessageCode;
			report.m_sMessage = _InMessage;
			//printf("%s%s%s%d%s%s\n", "WARNING: [", _inPrefixLayer, "] Code ", _InMessageCode, " : ", _InMessage);
			LogDebugReport(report);
		}
		else if (_InFlag & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT) {
			printf("%s%s%s%d%s%s\n", "PERFORMANCE WARNING: [", _inPrefixLayer, "] Code ", _InMessageCode, " : ", _InMessage);
		}
		else if (_InFlag & VK_DEBUG_REPORT_INFORMATION_BIT_EXT) {
			report.m_uiContextFlag = DEBUG_REPORT_CONTEXT_VULKAN;
			report.m_uiReportTypeFlag = DEBUG_REPORT_TYPE_INFORMATION;
			report.m_uiReportCode = _InMessageCode;
			report.m_sMessage = _InMessage;
			//printf("%s%s%s%d%s%s\n", "INFO: [", _inPrefixLayer, "] Code ", _InMessageCode, " : ", _InMessage);
			LogDebugReport(report);
		}
		else if (_InFlag & VK_DEBUG_REPORT_DEBUG_BIT_EXT) {
			printf("%s%s%s%d%s%s\n", "DEBUG: [", _inPrefixLayer, "] Code ", _InMessageCode, " : ", _InMessage);
		}

		/*
		* false indicates that layer should not bail-out of an
		* API call that had validation failures. This may mean that the
		* app dies inside the driver due to invalid parameter(s).
		* That's what would happen without validation layers, so we'll
		* keep that behavior here.
		*/

		return VK_FALSE;
	}

	void InitializeVulkanDebug(VkInstance& _InInstance)
	{
		CreateDebugReportCallback = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(_InInstance, "vkCreateDebugReportCallbackEXT");
		DestroyDebugReportCallback = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(_InInstance, "vkDestroyDebugReportCallbackEXT");
		DebugReportMessage = (PFN_vkDebugReportMessageEXT)vkGetInstanceProcAddr(_InInstance, "vkDebugReportMessageEXT");

		VkDebugReportCallbackCreateInfoEXT debug_report_callback_create_info = {};
		debug_report_callback_create_info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
		debug_report_callback_create_info.pNext = VK_NULL_HANDLE;
		debug_report_callback_create_info.pfnCallback = (PFN_vkDebugReportCallbackEXT)&MessageCallback;
		debug_report_callback_create_info.pUserData = NULL;
		debug_report_callback_create_info.flags = VK_DEBUG_REPORT_DEBUG_BIT_EXT | VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_INFORMATION_BIT_EXT;

		VK_CHECK_RESULT(CreateDebugReportCallback(_InInstance, &debug_report_callback_create_info, VK_NULL_HANDLE, &DebugReportCallback));
	}

	void DestroyVulkanDebug(VkInstance& _InInstance)
	{
		DestroyDebugReportCallback(_InInstance, DebugReportCallback, VK_NULL_HANDLE);
	}
}