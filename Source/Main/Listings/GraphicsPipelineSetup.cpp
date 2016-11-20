//
// Pipeline Shader Stages
//
VkPipelineShaderStageCreateInfo ShaderStages[2]{};
ShaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
ShaderStages[0].module = CreateModuleFromFile("Shader.vert.spv");
ShaderStages[0].pName = "main";
ShaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
ShaderStages[1].module = CreateModuleFromFile("Shader.frag.spv");
ShaderStages[1].pName = "main";

//
// Pipeline Vertex Input State
//
VkVertexInputBindingDescription VertexBinding{};
VertexBinding.binding = 0;
VertexBinding.stride = (3 + 2) * sizeof(float);

VkVertexInputAttributeDescription VertexAttribute{};
VertexAttribute.binding = 0;
VertexAttribute.location = 0;
VertexAttribute.format = VK_FORMAT_R32G32B32_SFLOAT;
VertexAttribute.offset = 0;

VkPipelineVertexInputStateCreateInfo VertexInputState{};
VertexInputState.vertexBindingDescriptionCount = 1;
VertexInputState.pVertexBindingDescriptions = &VertexBinding;
VertexInputState.vertexAttributeDescriptionCount = 1;
VertexInputState.pVertexAttributeDescriptions = &VertexAttribute;

//
// Input Assembly State
//
VkPipelineInputAssemblyStateCreateInfo InputAssemblyState{};
InputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

//
// Viewport and Dynamic State
//
VkDynamicState DynamicState[2];
DynamicState[0] = VK_DYNAMIC_STATE_VIEWPORT;
DynamicState[1] = VK_DYNAMIC_STATE_SCISSOR;

VkPipelineDynamicStateCreateInfo DynamicPipelineState{};
DynamicPipelineState.dynamicStateCount = 2;
DynamicPipelineState.pDynamicStates = &DynamicState[0];

VkPipelineViewportStateCreateInfo ViewportState{};
ViewportState.viewportCount = 1;
ViewportState.scissorCount = 1;

//
// Rasterization State
//
VkPipelineRasterizationStateCreateInfo RasterizationState{};
RasterizationState.polygonMode = VK_POLYGON_MODE_FILL;
RasterizationState.cullMode = VK_CULL_MODE_NONE;

//
// Multisample State
//
VkPipelineMultisampleStateCreateInfo MultisampleState{};
MultisampleState.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

//
// Depth Stencil State
//
VkPipelineDepthStencilStateCreateInfo DepthStencilState{};
DepthStencilState.depthTestEnable = VK_TRUE;
DepthStencilState.depthWriteEnable = VK_TRUE;
DepthStencilState.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
DepthStencilState.stencilTestEnable = VK_FALSE;

//
// Color Blend State
//
VkPipelineColorBlendAttachmentState ColorBlendAttachmentState{};
ColorBlendAttachmentState.blendEnable = VK_FALSE;
ColorBlendAttachmentState.colorWriteMask = 0b1111; // 0bRGBA

VkPipelineColorBlendStateCreateInfo ColorBlendState{};
ColorBlendState.attachmentCount = 1;
ColorBlendState.pAttachments = &ColorBlendAttachmentState;

//
// Render Pass
//
VkAttachmentDescription Attachment[2]{};
Attachment[0].format = surfaceFormat;
Attachment[0].samples = VK_SAMPLE_COUNT_1_BIT;
Attachment[0].loadOp  = VK_ATTACHMENT_LOAD_OP_CLEAR;
Attachment[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
Attachment[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
Attachment[0].finalLayout   = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

Attachment[1].format = depthFormat;
Attachment[1].samples = VK_SAMPLE_COUNT_1_BIT;
Attachment[1].loadOp  = VK_ATTACHMENT_LOAD_OP_CLEAR
Attachment[1].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
Attachment[1].initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
Attachment[1].finalLayout   = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

VkAttachmentReference ColorReference{};
ColorReference.attachment = 0;
ColorReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

VkAttachmentReference DepthReference{};
DepthReference.attachment = 1;
DepthReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

VkSubpassDescription SubpassDesc{};
SubpassDesc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
SubpassDesc.colorAttachmentCount = 1;
SubpassDesc.pColorAttachments = &ColorReference;
SubpassDesc.pDepthStencilAttachment = &DepthReference;

VkRenderPassCreateInfo RenderPassCreateInfo{};
RenderPassCreateInfo.attachmentCount = 2;
RenderPassCreateInfo.pAttachments = &Attachment[0];
RenderPassCreateInfo.subpassCount = 1;
RenderPassCreateInfo.pSubpasses = &SubpassDesc;

VkRenderPass RenderPass;
vkCreateRenderPass(Device, &RenderPassCreateInfo, nullptr, &RenderPass);

//
// Graphics Pipeline Creation
//
VkGraphicsPipelineCreateInfo GraphicsPipelineInfo{};
GraphicsPipelineInfo.stageCount = 2;
GraphicsPipelineInfo.pStages = &ShaderStages[0];
GraphicsPipelineInfo.pVertexInputState = &VertexInputState;
GraphicsPipelineInfo.pInputAssemblyState = &InputAssemblyState;
GraphicsPipelineInfo.pViewportState = &ViewportState;
GraphicsPipelineInfo.pRasterizationState = &RasterizationState;
GraphicsPipelineInfo.pMultisampleState = &MultisampleState;
GraphicsPipelineInfo.pDepthStencilState = &DepthStencilState;
GraphicsPipelineInfo.pColorBlendState = &ColorBlendState;
GraphicsPipelineInfo.pDynamicState = &DynamicState;
GraphicsPipelineInfo.layout = PipelineLayout;
GraphicsPipelineInfo.RenderPass = RenderPass;
GraphicsPipelineInfo.subpass = 0;
vkCreateGraphicsPipelines(Device, VK_NULL_HANDLE,
                          1, &GraphicsPipelineCreateInfo,
                          nullptr, &GraphicsPipeline);
