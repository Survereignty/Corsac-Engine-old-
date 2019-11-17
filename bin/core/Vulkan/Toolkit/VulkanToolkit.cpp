#include "VulkanToolkit.h"

bool vktoolkit::CheckInstanceExtensionsSupported(std::vector<const char*> instanceExtensionsNames)
{
    std::vector<VkExtensionProperties> availableExtensions;

    unsigned int instanceExtensionsCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionsCount, nullptr);

    if (instanceExtensionsCount == 0) {
        return false;
    }

    availableExtensions.resize(instanceExtensionsCount);
    vkEnumerateInstanceExtensionProperties(
        nullptr,
        &instanceExtensionsCount,
        availableExtensions.data()
    );

    for (const char* requiredExtName : instanceExtensionsNames) {
        bool found = false;
        for (const VkExtensionProperties &extProperties : availableExtensions) {
            if (strcmp(requiredExtName, extProperties.extensionName) == 0) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }

    return true;
}

bool vktoolkit::CheckValidationsLayersSupported(std::vector<const char*> validationsLayersNames)
{
    std::vector<VkLayerProperties> availableLayers;

    unsigned int layersCount = 0;
    vkEnumerateInstanceLayerProperties(&layersCount, nullptr);

    if (layersCount == 0) {
        return false;
    }

    availableLayers.resize(layersCount);
    vkEnumerateInstanceLayerProperties(&layersCount, availableLayers.data());

    for (const char* requiredName : validationsLayersNames) {
        std::cout << requiredName << std::endl;
        std::cout << " " << std::endl;
        bool found = false;
        for (const VkLayerProperties &properties : availableLayers) {
            std::cout << properties.layerName << std::endl;
            if (strcmp(requiredName, properties.layerName) == 0) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

VKAPI_ATTR VkBool32 VKAPI_CALL vktoolkit::DebugVulkanCallback(
        VkDebugReportFlagsEXT flags,
        VkDebugReportObjectTypeEXT objType,
        uint64_t obj,
        size_t location,
        int32_t code,
        const char* layersPrefix,
        const char* msg,
        void* userData)
{
    std::cout << "Vulkan validation layer : " << msg << std::endl;
    return VK_FALSE;
}