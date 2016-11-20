uint32_t GraphicsAndPresentQueueIndex;
uint32_t NumberOfQueueFamilies = /* Determine number of queue families */;
for (uint32_t Index = 0; Index < NumberOfQueueFamilies; ++Index) {
    if(/* Queue family supports both graphics and presenting */) {
        GraphicsAndPresentQueueIndex = Index;
        break;
    }
}

VkDeviceQueueCreateInfo QueueInfo{};
QueueInfo.queueFamilyIndex = GraphicsAndPresentQueueIndex;
float QueuePriority = 1.0f;
QueueInfo.queueCount = 1;
QueueInfo.pQueuePriorities = &QueuePriority;

const char* SwapchainExtension = "VK_KHR_swapchain";
VkDeviceCreateInfo DeviceInfo{};
DeviceInfo.queueCreateInfoCount = 1;
DeviceInfo.pQueueCreateInfos = &QueueInfo;
DeviceInfo.enabledExtensionCount = 1;
DeviceInfo.ppEnabledExtensionNames = &SwapchainExtension;
VkDevice Device;
vkCreateDevice(GPU, &DeviceInfo, nullptr, &Device);

vkGetDeviceQueue(Device, GraphicsAndPresentQueueIndex, 0, &Queue);
