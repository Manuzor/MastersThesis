VkCommandBufferBeginInfo CmdBufferBeginInfo{};
vkBeginCommandBuffer(CmdBuffer, &CmdBufferBeginInfo);

VkViewport Viewport{};
Viewport.width = FramebufferWidth;
Viewport.height = FramebufferHeight;
Viewport.minDepth = 0.0f;
Viewport.maxDepth = 1.0f;
vkCmdSetViewport(CmdBuffer, 0, 1, &Viewport);

VkRect2D Scissor{};
Scissor.extent = { Viewport.width, Viewport.height };
vkCmdSetScissor(CmdBuffer, 0, 1, &Scissor);

VkClearValue ClearValues[2]{};
ClearValues[0].color.float32 = { 1.0f, 0.0f, 0.0f, 1.0f }; // Solid red
ClearValues[1].depthStencil.depth = 1.0f;

VkRenderPassBeginInfo PassBeginInfo{};
PassBeginInfo.renderPass = RenderPass;
PassBeginInfo.framebuffer = Framebuffer;
PassBeginInfo.renderArea = Scissor;
PassBeginInfo.clearValueCount = 2;
PassBeginInfo.pClearValues = &ClearValues[0];
vkCmdBeginRenderPass(CmdBuffer, &PassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

for(auto Obj : /* List of objects */)
{
  vkCmdBindDescriptorSets(CmdBuffer,
                          VK_PIPELINE_BIND_POINT_GRAPHICS,
                          PipelineLayout,
                          0, // Descriptor set offset
                          1, &DescriptorSet,
                          0, nullptr); // Dynamic offsets
  vkCmdBindPipeline(CmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, Pipeline);
  VkDeviceSize Offset = 0;
  vkCmdBindVertexBuffers(CmdBuffer, 0, 1, &Obj.VertexBuffer, &Offset);
  vkCmdBindIndexBuffer(CmdBuffer, Obj.IndexBuffer, 0, VK_INDEX_TYPE_UINT32);
  vkCmdDrawIndexed(CmdBuffer, Obj.IndexCount, 1, 0, 0, 0);
}

vkCmdEndRenderPass(CmdBuffer);
vkEndCommandBuffer(CmdBuffer);
