#include "Vulkan.h"

VkInstance Vulkan::InitInstance(
    std::string applicationName,
    std::string engineName,
    std::vector<const char*> extensionRaquired,
    std::vector<const char*> validationLayersRaquired
)
{

    VkApplicationInfo applicationInfo = {};                         // Создаем объект приложения

    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;     // Указываем тип
    applicationInfo.pApplicationName = applicationName.c_str();     // Указываем название игры
    applicationInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);  // Указываем версию игры
    applicationInfo.pEngineName = engineName.c_str();               // Указываем название движка
    applicationInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);       // Указываем версию движка
    applicationInfo.apiVersion = VK_API_VERSION_1_0;                // Указываем версию вулкана

    VkInstanceCreateInfo instanceCreateInfo = {};                   // Создаем объект инстанса

    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;  // Указываем тип
    instanceCreateInfo.pApplicationInfo = &applicationInfo;             // Указываем объект приложения

    bool validationQueried = false;

    // Проверяем расширения
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

        // Проверяем слои валидации
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

    // Создаем иснтанс вулкана
    VkInstance vkInstance;

    if (vkCreateInstance(&instanceCreateInfo, nullptr, &(vkInstance)) != VK_SUCCESS) {
        throw std::runtime_error("Vulkan: Error in the 'vkCreateInstance' function!");
    }

    std::cout << "Vulkan: Instance sucessfully created" << std::endl;

    // Включаем обработчик ошибок вулкана
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

    // Отдаем готовый инстанс
    return vkInstance;
}

// Удаление обработчика ошибок и инстинса вулкана
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

// VkSurfaceKHR Vulkan::InitWindowSurfase(kInstance vkInstance, HINSTANCE hInstance, HWND hWnd)
// {
//     VkWaylandSurfaceCreateInfoKHR waylandSurfaceCreateInfoKhr;
//     waylandSurfaceCreateInfoKhr.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
//     waylandSurfaceCreateInfoKhr.hWnd = hWnd;
//     waylandSurfaceCreateInfoKhr.hinstance = hInstance;
//     waylandSurfaceCreateInfoKhr.flags = 0;
//     waylandSurfaceCreateInfoKhr.pNext = nullptr;
//}

Vulkan::Vulkan() :
    instance_(VK_NULL_HANDLE),
    validationReportCallback_(VK_NULL_HANDLE)
    //surface_(VK_NULL_HANDLE);
{
    // Создание инстанса вулкана
    this->instance_ = this->InitInstance(
        "TestGame",         // Название игры
        "Corsac Engine",    // Названия движка
        { // Расширения
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME,
        VK_EXT_DEBUG_REPORT_EXTENSION_NAME
        },
        {  // Слои валидации
        "VK_LAYER_LUNARG_standard_validation"
        }
    );
}

Vulkan::~Vulkan()
{
    // Удаление обработчика ошибок и инстинса вулкана
    this->DeinitInstance(&(this->instance_));
}
