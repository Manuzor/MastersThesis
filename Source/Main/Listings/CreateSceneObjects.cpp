VkBufferCreateInfo BufferCreateInfo{};
BufferCreateInfo.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
BufferCreateInfo.size = sizeof(mat4x4);
vkCreateBuffer(Device, &BufferCreateInfo, nullptr, &Obj->UniformBuffer);

VkDeviceMemory Obj->UniformBufferMemory = /* Determine memory requirements
                                             and allocate device memory. */;

vkBindBufferMemory(Device, Obj->UniformBuffer, Obj->UniformBufferMemory, 0);

VkDescriptorPoolSize DescriptorType;
DescriptorType.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
DescriptorType.descriptorCount = 1;

VkDescriptorPoolCreateInfo DescPoolInfo{};
DescPoolInfo.maxSets = 1;
DescPoolInfo.poolSizeCount = 1;
DescPoolInfo.pPoolSizes = &DescriptorType;
vkCreateDescriptorPool(Device, &DescPoolInfo, nullptr, &DescriptorPool);

VkDescriptorSetAllocateInfo DescSetAllocInfo;
DescSetAllocInfo.descriptorPool = DescriptorPool;
DescSetAllocInfo.descriptorSetCount = 1;
DescSetAllocInfo.pSetLayouts = &DescriptorSetLayout;
VkDescriptorSet DescriptorSet;
vkAllocateDescriptorSets(Device, &DescSetAllocInfo, &DescriptorSet);

VkDescriptorBufferInfo DescBufferInfo{};
DescBufferInfo.buffer = Obj->UniformBuffer;
DescBufferInfo.range = sizeof(mat4x4);

VkWriteDescriptorSet DescWrite{};
DescWrite.dstSet = info.desc_set[0];
DescWrite.descriptorCount = 1;
DescWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
DescWrite.pBufferInfo = &DescBufferInfo;
vkUpdateDescriptorSets(Device, 1, DescWrite, 0, nullptr);
