#include "VulkanShader.hpp"

#include "../../../Gameplay/Gameplay.hpp"
#include "../../../Math/Math.hpp"

#include "../../Mesh/VertexInputLayout.hpp"
#include "VulkanSwapchain.hpp"
#include "VulkanVertexInputLayout.hpp"
#include "VulkanHelper.hpp"
#include "VulkanDebug.hpp"
#include "VulkanVertexShader.hpp"
#include "VulkanGeometryShader.hpp"
#include "VulkanFragmentShader.hpp"

namespace DadEngine::Rendering
{
    VulkanUBO::VulkanUBO(VkDevice _InDevice, VkPhysicalDevice _InPhysicalDevice)
        : m_bufferSize(sizeof(Matrix4x4))
    {
        VulkanHelper::CreateBuffer(_InDevice, m_bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, m_buffer);

        VulkanHelper::AllocateBufferMemory(_InDevice, _InPhysicalDevice, m_buffer,
                                           VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                                           m_memory);

        vkBindBufferMemory(_InDevice, m_buffer, m_memory, 0U);

        m_bufferInfo.buffer = m_buffer;
        m_bufferInfo.offset = 0;
        m_bufferInfo.range = VK_WHOLE_SIZE;
    }

    void VulkanUBO::UpdateUBO(VkDevice _InDevice, VkDescriptorSet _InDescriptorSet)
    {
        Matrix4x4 pers = Gameplay::CameraManager::GetCameraManager()->GetMainCamera()->GetProjectionMatrix();
        pers.m_22 *= -1;
        Matrix4x4 view;
        Vector3f eyePos =
            Gameplay::CameraManager::GetCameraManager()->GetMainCamera()->m_Owner->GetRelativeLocation();
        Vector3f targetPosition = Vector3f{ eyePos.x, eyePos.y, -1.f };
        Vector3f up = Vector3f{ 0.f, 1.f, 0.f };
        view.LookAt(eyePos, targetPosition, up);
        Matrix4x4 vp = pers * view;

        // Update UBO content
        void *data = nullptr;
        vkMapMemory(_InDevice, m_memory, 0U, m_bufferSize, 0U, &data);
        DadEngine::Core::MemoryManager::Copy(&vp, data, sizeof(Matrix4x4));
        vkUnmapMemory(_InDevice, m_memory);


        // Update descriptor set content
        VkWriteDescriptorSet write_descriptor_set = {};
        write_descriptor_set.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        write_descriptor_set.pNext = VK_NULL_HANDLE;
        write_descriptor_set.dstSet = _InDescriptorSet;
        write_descriptor_set.dstBinding = 0U;
        write_descriptor_set.dstArrayElement = 0U;
        write_descriptor_set.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        write_descriptor_set.descriptorCount = 1U;
        write_descriptor_set.pBufferInfo = &m_bufferInfo;
        write_descriptor_set.pImageInfo = VK_NULL_HANDLE;
        write_descriptor_set.pTexelBufferView = VK_NULL_HANDLE;

        vkUpdateDescriptorSets(_InDevice, 1U, &write_descriptor_set, 0U, VK_NULL_HANDLE);
    }


	VulkanShader::VulkanShader(VertexShader *_InVertexShader,
                 GeometryShader *_InGeometryShader,
                 FragmentShader *_InFragmentShader,
                 VkDevice _InDevice,
                 VkPhysicalDevice _InPhysicalDevice,
                 VkRenderPass _InRenderPass,
                 VkPipelineCache _InPipelineCache,
                 VulkanSwapchain &_InSwapchain,
                 VkDescriptorPool _InDescriptorPool)
        : Shader(_InVertexShader, _InGeometryShader, _InFragmentShader), m_Device(_InDevice),
          m_ShaderUBO(_InDevice, _InPhysicalDevice)
    {
        // Temporary code -------------
        AddShaderBinding(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT);

        createDescriptorSetLayout();
        createDescriptorSet(_InDescriptorPool);

        // !Temporary code -------------


        TArray<VkPipelineShaderStageCreateInfo> shader_stage_create_infos;

        if (m_ptrVertexShader != nullptr)
        {
            shader_stage_create_infos.AddCapacity(1U);
            VkPipelineShaderStageCreateInfo &shader_stage_create_info = shader_stage_create_infos.Last();
            shader_stage_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            shader_stage_create_info.pNext = VK_NULL_HANDLE;
            shader_stage_create_info.module = ((VulkanVertexShader *)m_ptrVertexShader)->m_ShaderModule;
            shader_stage_create_info.pName = "main";
            shader_stage_create_info.pSpecializationInfo = VK_NULL_HANDLE;
            shader_stage_create_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
            shader_stage_create_info.flags = 0U;
        }

        if (m_ptrGeometryShader != nullptr)
        {
            shader_stage_create_infos.AddCapacity(1U);
            VkPipelineShaderStageCreateInfo &shader_stage_create_info = shader_stage_create_infos.Last();
            shader_stage_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            shader_stage_create_info.pNext = VK_NULL_HANDLE;
            shader_stage_create_info.module = ((VulkanGeometryShader *)m_ptrGeometryShader)->m_ShaderModule;
            shader_stage_create_info.pName = "main";
            shader_stage_create_info.pSpecializationInfo = VK_NULL_HANDLE;
            shader_stage_create_info.stage = VK_SHADER_STAGE_GEOMETRY_BIT;
            shader_stage_create_info.flags = 0U;
        }

        if (m_ptrFragmentShader != nullptr)
        {
            shader_stage_create_infos.AddCapacity(1U);
            VkPipelineShaderStageCreateInfo &shader_stage_create_info = shader_stage_create_infos.Last();
            shader_stage_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            shader_stage_create_info.pNext = VK_NULL_HANDLE;
            shader_stage_create_info.module = ((VulkanFragmentShader *)m_ptrFragmentShader)->m_ShaderModule;
            shader_stage_create_info.pName = "main";
            shader_stage_create_info.pSpecializationInfo = VK_NULL_HANDLE;
            shader_stage_create_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
            shader_stage_create_info.flags = 0U;
        }


        // Vertex input layout state
        VkVertexInputBindingDescription vertices_input_binding;
        TArray<VkVertexInputAttributeDescription> vertices_input_attribute(
            m_ptrVertexShader->m_vertexInputLayout.Size());
        size_t offset = 0U;
        uint32_t stride;

        VertexInput::GetLayoutStride(m_ptrVertexShader->m_vertexInputLayout, stride);

        // Bindings
        vertices_input_binding.binding = 0U;
        vertices_input_binding.stride = stride;
        vertices_input_binding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX; // Per vertex data

        for (size_t i = 0U; i < m_ptrVertexShader->m_vertexInputLayout.Size(); i++)
        {
            size_t size;
            uint32_t count;

            m_ptrVertexShader->m_vertexInputLayout[(uint32_t)i].GetInputTypeInfo(size, count);

            // Attributes
            vertices_input_attribute[(uint32_t)i].binding = 0U;
            vertices_input_attribute[(uint32_t)i].location =
                m_ptrVertexShader->m_vertexInputLayout[(uint32_t)i].uiIndex;
            vertices_input_attribute[(uint32_t)i].format =
                VertexInputTypeFormat(m_ptrVertexShader->m_vertexInputLayout[(uint32_t)i].uiVertexInputType);
            vertices_input_attribute[(uint32_t)i].offset = (uint32_t)offset;

            offset += size;
        }


        VkPipelineVertexInputStateCreateInfo vertex_input_state_create_info = {};
        vertex_input_state_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vertex_input_state_create_info.pNext = VK_NULL_HANDLE;
        vertex_input_state_create_info.vertexBindingDescriptionCount = 1U;
        vertex_input_state_create_info.pVertexBindingDescriptions = &vertices_input_binding;
        vertex_input_state_create_info.vertexAttributeDescriptionCount =
            (uint32_t)vertices_input_attribute.Size();
        vertex_input_state_create_info.pVertexAttributeDescriptions = vertices_input_attribute.GetData();
        vertex_input_state_create_info.flags = 0U;


        // Dynamic states
        TArray<VkDynamicState> dynamic_states;
        // dynamic_states.Add(VK_DYNAMIC_STATE_SCISSOR);
        // dynamic_states.Add(VK_DYNAMIC_STATE_VIEWPORT);
        // Dynamic scissor and viewport if more than 1 camera
        VkViewport viewport;
        viewport.x = 0.f;
        viewport.y = 0.f;
        viewport.width = (float)_InSwapchain.m_SwapchainExtent.width;
        viewport.height = (float)_InSwapchain.m_SwapchainExtent.height;
        viewport.minDepth = 0.f;
        viewport.maxDepth = 1.f;

        VkRect2D scissor;
        scissor.extent = _InSwapchain.m_SwapchainExtent;
        scissor.offset = { 0, 0 };

        // Input assembly state
        VkPipelineInputAssemblyStateCreateInfo input_assembly_state_create_info = {};
        input_assembly_state_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        input_assembly_state_create_info.pNext = VK_NULL_HANDLE;
        input_assembly_state_create_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        input_assembly_state_create_info.primitiveRestartEnable = VK_FALSE;
        input_assembly_state_create_info.flags = 0U;

        // Viewport state
        VkPipelineViewportStateCreateInfo viewport_state_create_info = {};
        viewport_state_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewport_state_create_info.pNext = VK_NULL_HANDLE;
        viewport_state_create_info.viewportCount = 1U;
        viewport_state_create_info.pViewports = &viewport;
        viewport_state_create_info.scissorCount = 1U;
        viewport_state_create_info.pScissors = &scissor;
        viewport_state_create_info.flags = 0U;


        VkPipelineDynamicStateCreateInfo dynamic_state_create_info = {};

        if (dynamic_states.Size() > 0U)
        {
            dynamic_state_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
            dynamic_state_create_info.pNext = VK_NULL_HANDLE;
            dynamic_state_create_info.dynamicStateCount = (uint32_t)dynamic_states.Size();
            dynamic_state_create_info.pDynamicStates = dynamic_states.GetData();
            dynamic_state_create_info.flags = 0U;
        }

        // Rasterization state
        VkPipelineRasterizationStateCreateInfo rasterization_state_create_info = {};
        rasterization_state_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterization_state_create_info.pNext = VK_NULL_HANDLE;
        rasterization_state_create_info.depthClampEnable = VK_FALSE;
        rasterization_state_create_info.rasterizerDiscardEnable = VK_FALSE;
        rasterization_state_create_info.polygonMode = VK_POLYGON_MODE_FILL;
        rasterization_state_create_info.cullMode = VK_CULL_MODE_NONE; // VK_CULL_MODE_BACK_BIT;
        rasterization_state_create_info.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        rasterization_state_create_info.depthBiasEnable = VK_FALSE;
        rasterization_state_create_info.depthBiasConstantFactor = 0.f;
        rasterization_state_create_info.depthBiasClamp = 0.f;
        rasterization_state_create_info.depthBiasSlopeFactor = 0.f;
        rasterization_state_create_info.lineWidth = 1.f;
        rasterization_state_create_info.flags = 0U;

        // Depth stencil state
        VkPipelineDepthStencilStateCreateInfo depth_stencil_state_create_info = {};
        depth_stencil_state_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        depth_stencil_state_create_info.pNext = VK_NULL_HANDLE;
        depth_stencil_state_create_info.depthTestEnable = VK_TRUE;
        depth_stencil_state_create_info.depthWriteEnable = VK_TRUE;
        depth_stencil_state_create_info.depthCompareOp = VK_COMPARE_OP_LESS; // VK_COMPARE_OP_LESS_OR_EQUAL
        depth_stencil_state_create_info.depthBoundsTestEnable = VK_FALSE;
        depth_stencil_state_create_info.stencilTestEnable = VK_FALSE;
        depth_stencil_state_create_info.front = {};
        depth_stencil_state_create_info.back = {};
        depth_stencil_state_create_info.minDepthBounds = 0.f;
        depth_stencil_state_create_info.minDepthBounds = 1.f;
        depth_stencil_state_create_info.flags = 0U;

        // Multisampling state
        VkPipelineMultisampleStateCreateInfo multisample_state_create_info = {};
        multisample_state_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisample_state_create_info.pNext = VK_NULL_HANDLE;
        multisample_state_create_info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        multisample_state_create_info.sampleShadingEnable = VK_FALSE;
        multisample_state_create_info.minSampleShading = 1.f;
        multisample_state_create_info.pSampleMask = VK_NULL_HANDLE;
        multisample_state_create_info.alphaToCoverageEnable = VK_FALSE;
        multisample_state_create_info.alphaToOneEnable = VK_FALSE;
        multisample_state_create_info.flags = 0U;

        // Color blending state
        VkPipelineColorBlendAttachmentState color_blend_attachement_state = {};
        color_blend_attachement_state.blendEnable = VK_FALSE;
        color_blend_attachement_state.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
        color_blend_attachement_state.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
        color_blend_attachement_state.colorBlendOp = VK_BLEND_OP_ADD;
        color_blend_attachement_state.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        color_blend_attachement_state.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        color_blend_attachement_state.alphaBlendOp = VK_BLEND_OP_ADD;
        color_blend_attachement_state.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                                                       VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

        VkPipelineColorBlendStateCreateInfo color_blend_state_create_info = {};
        color_blend_state_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        color_blend_state_create_info.pNext = VK_NULL_HANDLE;
        color_blend_state_create_info.logicOpEnable = VK_FALSE;
        color_blend_state_create_info.logicOp = VK_LOGIC_OP_COPY;
        color_blend_state_create_info.attachmentCount = 1U;
        color_blend_state_create_info.pAttachments = &color_blend_attachement_state;
        color_blend_state_create_info.blendConstants[0] = 0.f;
        color_blend_state_create_info.blendConstants[1] = 0.f;
        color_blend_state_create_info.blendConstants[2] = 0.f;
        color_blend_state_create_info.blendConstants[3] = 0.f;
        color_blend_state_create_info.flags = 0U;

        // Pipeline layout
        VkPipelineLayoutCreateInfo pipeline_layout_create_info = {};
        pipeline_layout_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipeline_layout_create_info.pNext = VK_NULL_HANDLE;
        pipeline_layout_create_info.setLayoutCount = 1U;
        pipeline_layout_create_info.pSetLayouts = &m_DescriptorSetLayout;
        pipeline_layout_create_info.pushConstantRangeCount = 0U;
        pipeline_layout_create_info.pPushConstantRanges = VK_NULL_HANDLE;
        pipeline_layout_create_info.flags = 0U;

        vkCreatePipelineLayout(_InDevice, &pipeline_layout_create_info, VK_NULL_HANDLE, &m_PipelineLayout);


        // Graphics pipeline
        VkGraphicsPipelineCreateInfo graphics_pipeline_create_info = {};
        graphics_pipeline_create_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        graphics_pipeline_create_info.pNext = VK_NULL_HANDLE;
        graphics_pipeline_create_info.stageCount = (uint32_t)shader_stage_create_infos.Size();
        graphics_pipeline_create_info.pStages = shader_stage_create_infos.GetData();
        graphics_pipeline_create_info.pVertexInputState = &vertex_input_state_create_info;
        graphics_pipeline_create_info.pInputAssemblyState = &input_assembly_state_create_info;
        graphics_pipeline_create_info.pTessellationState = VK_NULL_HANDLE;
        graphics_pipeline_create_info.pViewportState = &viewport_state_create_info;
        graphics_pipeline_create_info.pRasterizationState = &rasterization_state_create_info;
        graphics_pipeline_create_info.pMultisampleState = &multisample_state_create_info;
        graphics_pipeline_create_info.pDepthStencilState = &depth_stencil_state_create_info;
        graphics_pipeline_create_info.pColorBlendState = &color_blend_state_create_info;
        graphics_pipeline_create_info.pDynamicState =
            (dynamic_states.Size() > 0U) ? &dynamic_state_create_info : VK_NULL_HANDLE;
        graphics_pipeline_create_info.layout = m_PipelineLayout;
        graphics_pipeline_create_info.renderPass = _InRenderPass;
        graphics_pipeline_create_info.subpass = 0U;
        graphics_pipeline_create_info.basePipelineHandle = VK_NULL_HANDLE;
        graphics_pipeline_create_info.basePipelineIndex = -1;
        graphics_pipeline_create_info.flags = 0U;

        VK_CHECK_RESULT(vkCreateGraphicsPipelines(_InDevice, _InPipelineCache, 1U, &graphics_pipeline_create_info,
                                                  VK_NULL_HANDLE, &m_GraphicsPipeline));
    }


    VulkanShader::~VulkanShader()
    {
        vkDestroyPipelineLayout(m_Device, m_PipelineLayout, VK_NULL_HANDLE);
        vkDestroyPipeline(m_Device, m_GraphicsPipeline, VK_NULL_HANDLE);

        vkDestroyDescriptorSetLayout(m_Device, m_DescriptorSetLayout, VK_NULL_HANDLE);
    }

    void VulkanShader::AddShaderBinding(VkDescriptorType _InDescriptorType, VkShaderStageFlags _InShaderStagesFlag)
    {
        // One binding of the descriptor set
        VkDescriptorSetLayoutBinding layoutBinding = {};
        layoutBinding.binding = 0;
        layoutBinding.descriptorType = _InDescriptorType; // TODO: Rewrite every descriptor type ?
        layoutBinding.descriptorCount = (uint32_t)m_PipelineParameters.Size() + 1U;
        layoutBinding.stageFlags = _InShaderStagesFlag;
        layoutBinding.pImmutableSamplers = VK_NULL_HANDLE;

        m_PipelineParameters.Add(layoutBinding);
    }

    void VulkanShader::createDescriptorSetLayout()
    {
        VkDescriptorSetLayoutCreateInfo layout_create_info = {};
        layout_create_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layout_create_info.pNext = VK_NULL_HANDLE;
        layout_create_info.bindingCount = (uint32_t)m_PipelineParameters.Size();
        layout_create_info.pBindings = m_PipelineParameters.GetData();
        layout_create_info.flags = 0U;

        VK_CHECK_RESULT(vkCreateDescriptorSetLayout(m_Device, &layout_create_info, VK_NULL_HANDLE,
                                                    &m_DescriptorSetLayout));
    }

    void VulkanShader::createDescriptorSet(VkDescriptorPool _InDescritptorPool)
    {
        VkDescriptorSetAllocateInfo descriptor_set_allocate_info = {};
        descriptor_set_allocate_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        descriptor_set_allocate_info.pNext = VK_NULL_HANDLE;
        descriptor_set_allocate_info.descriptorPool = _InDescritptorPool;
        descriptor_set_allocate_info.descriptorSetCount = 1U;
        descriptor_set_allocate_info.pSetLayouts = &m_DescriptorSetLayout;

        VK_CHECK_RESULT(vkAllocateDescriptorSets(m_Device, &descriptor_set_allocate_info, &m_DescriptorSet));
    }

    void VulkanShader::UpdateUBO()
    {
        m_ShaderUBO.UpdateUBO(m_Device, m_DescriptorSet);
    }
}