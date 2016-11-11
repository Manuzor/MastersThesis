VkDescriptorSetLayoutBinding DescSetLayoutBinding{};
DescSetLayoutBinding.binding = 0;
DescSetLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
DescSetLayoutBinding.descriptorCount = 1;
DescSetLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

VkDescriptorSetLayoutCreateInfo DescLayoutInfo{};
DescLayoutInfo.bindingCount = 1;
DescLayoutInfo.pBindings = &DescSetLayoutBinding;
vkCreateDescriptorSetLayout(Device, &DescLayoutInfo, NULL, &DescriptorSet);

VkPipelineLayoutCreateInfo PipelineLayoutInfo{};
PipelineLayoutInfo.setLayoutCount = 1;
PipelineLayoutInfo.pSetLayouts = DescriptorSet;
vkCreatePipelineLayout(Device, &PipelineLayoutInfo, NULL, &PipelineLayout);
