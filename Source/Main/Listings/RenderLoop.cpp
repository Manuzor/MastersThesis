VkSemaphoreCreateInfo SemaphoreInfo{};
vkCreateSemaphore(Device, &SemaphoreInfo, nullptr, &PresentedSemaphore);
vkCreateSemaphore(Device, &SemaphoreInfo, nullptr, &RenderedSemaphore);

while(/* application is running */) {
  /* Window event handling */
  /* Input handling */
  /* Camera update */
  mat4x4 ViewProjectionMatrix = /* ... */;
  for(auto Obj : /* List of objects */)
  {
    mat4x4 MVP = Obj->ModelMatrix * ViewProjectionMatrix;
    void* Ptr;
    vkMapMemory(Device, Obj->UniformBufferMemory, 0, VK_WHOLE_SIZE, 0, &Ptr);
    memcpy(Ptr, &MVP, sizeof(mat4x4));
    vkUnmapMemory(Device, Obj->UniformBufferMemory);
  }
  /* ... */
}

while(/* application is running */) {
  /* ... */
  vkAcquireNextImageKHR(Device, Swapchain, -1,
                        PresentedSemaphore, VK_NULL_HANDLE,
                        &PresentIndex);
  /* ... */
}

// Submit command buffer
while(/* application is running */) {
  /* ... */
  VkPipelineStageFlags SubmitPipelineStages = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
  auto SubmitInfo = InitStruct<VkSubmitInfo>();
  SubmitInfo.pWaitDstStageMask = &SubmitPipelineStages;
  SubmitInfo.waitSemaphoreCount = 1;
  SubmitInfo.pWaitSemaphores = &PresentedSemaphore;
  SubmitInfo.signalSemaphoreCount = 1;
  SubmitInfo.pSignalSemaphores = &RenderedSemaphore;
  SubmitInfo.commandBufferCount = 1;
  SubmitInfo.pCommandBuffers = &CmdBuffer;
  vkQueueSubmit(Queue, 1, &SubmitInfo, VK_NULL_HANDLE);
  /* ... */
}

while(/* application is running */) {
  /* ... */
  VkPresentInfoKHR PresentInfo{};
  PresentInfo.swapchainCount = 1;
  PresentInfo.pSwapchains = &Swapchain;
  PresentInfo.pImageIndices = &PresentIndex;
  PresentInfo.waitSemaphoreCount = 1;
  PresentInfo.pWaitSemaphores = &RenderedSemaphore;
  vkQueuePresentKHR(Queue, &PresentInfo);
  /* ... */
}

while(/* application is running */) {
  /* ... */
  vkQueueWaitIdle(Queue);
  /* ... */
}
