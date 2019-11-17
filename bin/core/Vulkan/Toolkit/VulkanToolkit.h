#pragma once


#include <vector>
#include <iostream>
#include <vulkan/vulkan.h>
#include <cstring>

namespace vktoolkit
{
    bool CheckInstanceExtensionsSupported(std::vector<const char*> instanceExtensionsNames);

    bool CheckValidationsLayersSupported(std::vector<const char*> validationsLayersNames);

    VKAPI_ATTR VkBool32 VKAPI_CALL DebugVulkanCallback(
        VkDebugReportFlagsEXT flags,
        VkDebugReportObjectTypeEXT objType,
        uint64_t obj,
        size_t location,
        int32_t code,
        const char* layersPrefix,
        const char* msg,
        void* userData);
}