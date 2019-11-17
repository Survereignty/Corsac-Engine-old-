#include "Vulkan.h"

VkInstance Vulkan::InitInstance(
    std::string applicationName,
    std::string engineName,
    std::vector<const char*> extensionRaquired,
    std::vector<const char*> validationLayersRaquired
)
{
    VkApplicationInfo applicationInfo = {};
    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.pApplicationName = applicationName.c_str();
    applicationInfo.pEngineName = engineName.c_str();
    applicationInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
    applicationInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
    applicationInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo instanceCreateInfo = {};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pApplicationInfo = &applicationInfo;

    bool validationQueried = false;

    if (!extensionRaquired.empty()) {
        if (!vktoolkit::CheckInstanceExtensionsSupported(extensionRaquired)) {
            throw std::runtime_error("Vulkan: Not supported required instance extensions!");
        }

        instanceCreateInfo.ppEnabledExtensionNames = extensionRaquired.data();
        instanceCreateInfo.enabledExtensionCount = (uint32_t)extensionRaquired.size();

        bool debugReportExtensionQueried = false;

        for (const char* extensionName : extensionRaquired) {
            if (strcmp(VK_EXT_DEBUG_REPORT_EXTENSION_NAME, extensionName) == 0) {
                debugReportExtensionQueried = true;
                break;
            }
        }

        if (debugReportExtensionQueried && !validationLayersRaquired.empty()) {
            if (!vktoolkit::CheckValidationsLayersSupported(validationLayersRaquired)) {
                throw std::runtime_error("Vulkan: Not all required validation layers supported!");
            }

            instanceCreateInfo.enabledLayerCount = (uint32_t)validationLayersRaquired.size();
            instanceCreateInfo.ppEnabledLayerNames = validationLayersRaquired.data();

            validationQueried = true;
            std::cout << "Vulkan Validation enable" << std::endl;
        }
    }

    VkInstance vkInstance;

    if (vkCreateInstance(&instanceCreateInfo, nullptr, &(vkInstance)) != VK_SUCCESS) {
        throw std::runtime_error("Vulkan: Error in the 'vkCreateInstance' function!");
    }

    std::cout << "Vulkan: Instance sucessfully created" << std::endl;

    if (validationQueried) {
        VkDebugReportCallbackCreateInfoEXT debugReportCallbackcreateInfo = {};
        debugReportCallbackcreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
        debugReportCallbackcreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
        debugReportCallbackcreateInfo.pfnCallback = vktoolkit::DebugVulkanCallback;

        PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT =
            (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(
                vkInstance, "vkCreateDebugReportCallbackEXT"
            );

        if (vkCreateDebugReportCallbackEXT(
            vkInstance,
            &debugReportCallbackcreateInfo,
            nullptr, &(this->validationReportCallback_)) != VK_SUCCESS) {
                throw std::runtime_error("Vulkan: Error in the 'vkCreateDebugReportCallbackEXT' function!");
            }

        std::cout << "Vulkan: Report callback sucessfully created" << std::endl;
    }

    return vkInstance;
}

void Vulkan::DeinitInstance(VkInstance* vkInstance)
{
    if (this->validationReportCallback_ != VK_NULL_HANDLE) {

        PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT =
            (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(
                *vkInstance, "vkDestroyDebugReportCallbackEXT"
            );

        vkDestroyDebugReportCallbackEXT(
            *vkInstance,
            this->validationReportCallback_,
            nullptr
        );

        this->validationReportCallback_ = VK_NULL_HANDLE;

        std::cout << "Vulkan: Report callback sucessfully destriyed" << std::endl;
    }

    if (*vkInstance != VK_NULL_HANDLE) {
        vkDestroyInstance(*vkInstance, nullptr);
        *vkInstance = VK_NULL_HANDLE;

        std::cout << "Vulkan: Instance sucessfully destriyed" << std::endl;
    }
}

Vulkan::Vulkan() :
    instance_(VK_NULL_HANDLE),
    validationReportCallback_(VK_NULL_HANDLE)
{
    this->instance_ = this->InitInstance(
        "TestGame",
        "Corsac Engine",
        {VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME, VK_EXT_DEBUG_REPORT_EXTENSION_NAME},
        { "VK_LAYER_LUNARG_standard_validatin" }
    );
}

Vulkan::~Vulkan()
{
    this->DeinitInstance(&(this->instance_));
}
