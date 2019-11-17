#pragma once

#define VK_USE_PLATFORM_WAYLAND_KHR

#include <iostream>
#include <vector>
#include <vulkan/vulkan.h>
#include "Toolkit/VulkanToolkit.cpp"

#ifdef NDEBUG
const bool DEBUG_MODE = false;
#else
const bool DEBUG_MODE = true;
#endif

class Vulkan
{
    private:
        VkInstance instance_;
        VkDebugReportCallbackEXT validationReportCallback_;

        VkInstance InitInstance(
            std::string applicationName,
            std::string engineName,
            std::vector<const char*> extensionRaquired,
            std::vector<const char*> validationLayersRaquired
            );

        void DeinitInstance(VkInstance *vkInstance);

    public:
        Vulkan();
        ~Vulkan();
};