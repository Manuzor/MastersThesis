VkCommandPoolCreateInfo CmdPoolInfo{};
CmdPoolInfo.queueFamilyIndex = GraphicsAndPresentQueueIndex;
vkCreateCommandPool(Device, &CmdPoolInfo, nullptr, &CmdPool);

VkCommandBufferAllocateInfo CmdBufferAllocInfo{};
CmdBufferAllocInfo.commandPool = CmdPool;
CmdBufferAllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
CmdBufferAllocInfo.commandBufferCount = 1;
vkAllocateCommandBuffers(Device, &CmdBufferAllocInfo, &CmdBuffer);
