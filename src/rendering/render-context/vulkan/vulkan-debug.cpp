#include "vulkan-debug.hpp"

#include <cstdio.h>

#include "../../../core/debug.hpp"

using namespace DadEngine;

namespace DadEngine
{
    PFN_vkCreateDebugReportCallbackEXT CreateDebugReportCallback = VK_NULL_HANDLE;
    PFN_vkDestroyDebugReportCallbackEXT DestroyDebugReportCallback = VK_NULL_HANDLE;
    PFN_vkDebugReportMessageEXT DebugReportMessage = VK_NULL_HANDLE;

    VkDebugReportCallbackEXT DebugReportCallback;

    VkBool32 VKAPI_PTR MessageCallback (VkDebugReportFlagsEXT _flag,
                                        VkDebugReportObjectTypeEXT _objectType,
                                        uint64_t _srcObject,
                                        size_t _memoryLocation,
                                        int32_t _messageCode,
                                        const char *_prefixLayer,
                                        const char *_message,
                                        void *_userData)
    {
        DebugReport report;

        if (_flag & VK_DEBUG_REPORT_ERROR_BIT_EXT)
        {
            report.m_contextFlag = DEBUG_REPORT_CONTEXT_VULKAN;
            report.m_reportTypeFlag = DEBUG_REPORT_TYPE_ERROR;
            report.m_reportCode = _messageCode;
            report.m_message = _message;
            // printf("%s%s%s%d%s%s\n", "ERROR: [", _inPrefixLayer, "] Code ", _InMessageCode, " : ", _InMessage);
            LogDebugReport (report);
        }
        else if (_flag & VK_DEBUG_REPORT_WARNING_BIT_EXT)
        {
            report.m_contextFlag = DEBUG_REPORT_CONTEXT_VULKAN;
            report.m_reportTypeFlag = DEBUG_REPORT_TYPE_WARNING;
            report.m_reportCode = _messageCode;
            report.m_message = _message;
            // printf("%s%s%s%d%s%s\n", "WARNING: [", _inPrefixLayer, "] Code ", _InMessageCode, " : ", _InMessage);
            LogDebugReport (report);
        }
        else if (_flag & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT)
        {
            printf ("%s%s%s%d%s%s\n", "PERFORMANCE WARNING: [", _prefixLayer,
                    "] Code ", _messageCode, " : ", _message);
        }
        else if (_flag & VK_DEBUG_REPORT_INFORMATION_BIT_EXT)
        {
            report.m_contextFlag = DEBUG_REPORT_CONTEXT_VULKAN;
            report.m_reportTypeFlag = DEBUG_REPORT_TYPE_INFORMATION;
            report.m_reportCode = _messageCode;
            report.m_message = _message;
            // printf("%s%s%s%d%s%s\n", "INFO: [", _inPrefixLayer, "] Code ", _InMessageCode, " : ", _InMessage);
            LogDebugReport (report);
        }
        else if (_flag & VK_DEBUG_REPORT_DEBUG_BIT_EXT)
        {
            printf ("%s%s%s%d%s%s\n", "DEBUG: [", _prefixLayer, "] Code ",
                    _messageCode, " : ", _message);
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

    void InitializeVulkanDebug (VkInstance &_instance)
    {
        CreateDebugReportCallback = (PFN_vkCreateDebugReportCallbackEXT)
        vkGetInstanceProcAddr (_instance, "vkCreateDebugReportCallbackEXT");
        DestroyDebugReportCallback = (PFN_vkDestroyDebugReportCallbackEXT)
        vkGetInstanceProcAddr (_instance, "vkDestroyDebugReportCallbackEXT");
        DebugReportMessage = (PFN_vkDebugReportMessageEXT)
        vkGetInstanceProcAddr (_instance, "vkDebugReportMessageEXT");

        VkDebugReportCallbackCreateInfoEXT debug_report_callback_create_info = {};
        debug_report_callback_create_info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
        debug_report_callback_create_info.pNext = VK_NULL_HANDLE;
        debug_report_callback_create_info.pfnCallback =
        (PFN_vkDebugReportCallbackEXT)&MessageCallback;
        debug_report_callback_create_info.pUserData = NULL;
        debug_report_callback_create_info.flags =
        VK_DEBUG_REPORT_DEBUG_BIT_EXT | VK_DEBUG_REPORT_ERROR_BIT_EXT |
        VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
        VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_INFORMATION_BIT_EXT;

        VK_CHECK_RESULT (CreateDebugReportCallback (_instance, &debug_report_callback_create_info,
                                                    VK_NULL_HANDLE, &DebugReportCallback));
    }

    void DestroyVulkanDebug (VkInstance &_instance)
    {
        DestroyDebugReportCallback (_instance, DebugReportCallback, VK_NULL_HANDLE);
    }
} // namespace DadEngine
