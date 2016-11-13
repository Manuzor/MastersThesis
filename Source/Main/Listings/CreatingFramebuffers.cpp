VkFramebuffer* Framebuffers = new VkFramebuffer[NumberOfSwapchainImages];
for(uint32_t Index = 0; Index < NumberOfSwapchainImages; ++Index)
{
  VkImageView Attachments[2] = { VK_NULL_HANDLE, DepthImageView };
  Attachments[0] = SwapchainImageViews[Index];
  Attachments[1] = DepthImageView;

  VkFramebufferCreateInfo FramebufferInfo{};
  FramebufferInfo.renderPass = RenderPass;
  FramebufferInfo.attachmentCount = 2;
  FramebufferInfo.pAttachments = &Attachments[0];
  FramebufferInfo.width = FramebufferWidth;
  FramebufferInfo.height = FramebufferHeight;
  FramebufferInfo.layers = 1;
  vkCreateFramebuffer(Device, &FramebufferInfo, nullptr, &Framebuffers[Index]);
}
