#ifndef __VULKAN_SHADER_HPP_
#define __VULKAN_SHADER_HPP_

#include "../../Mesh/VertexInputLayout.hpp"
#include "VulkanVertexShader.hpp"
#include "VulkanGeometryShader.hpp"
#include "VulkanFragmentShader.hpp"

namespace DadEngine::Rendering
{
	// Pipeline object
	class VulkanShader : public Shader
	{
	public:

		VulkanShader(VertexShader* _InVertexShader, GeometryShader* _InGeometryShader, FragmentShader* _InFragmentShader, VkDevice _InDevice, VkRenderPass _InRenderPass, VkPipelineCache _InPipelineCache)
			: Shader(_InVertexShader, _InGeometryShader, _InFragmentShader)
		{
			TArray<VkPipelineShaderStageCreateInfo> shader_stage_create_infos;

			if (m_ptrVertexShader != nullptr)
			{
				shader_stage_create_infos.AddCapacity(1U);
				VkPipelineShaderStageCreateInfo& shader_stage_create_info = shader_stage_create_infos.Last();
				shader_stage_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				shader_stage_create_info.pNext = VK_NULL_HANDLE;
				shader_stage_create_info.module = ((VulkanVertexShader*)m_ptrVertexShader)->m_ShaderModule;
				shader_stage_create_info.pName = "main";
				shader_stage_create_info.pSpecializationInfo = VK_NULL_HANDLE;
				shader_stage_create_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
				shader_stage_create_info.flags = 0U;
			}

			if (m_ptrGeometryShader != nullptr)
			{
				shader_stage_create_infos.AddCapacity(1U);
				VkPipelineShaderStageCreateInfo& shader_stage_create_info = shader_stage_create_infos.Last();
				shader_stage_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				shader_stage_create_info.pNext = VK_NULL_HANDLE;
				shader_stage_create_info.module = ((VulkanGeometryShader*)m_ptrGeometryShader)->m_ShaderModule;
				shader_stage_create_info.pName = "main";
				shader_stage_create_info.pSpecializationInfo = VK_NULL_HANDLE;
				shader_stage_create_info.stage = VK_SHADER_STAGE_GEOMETRY_BIT;
				shader_stage_create_info.flags = 0U;
			}

			if (m_ptrFragmentShader != nullptr)
			{
				shader_stage_create_infos.AddCapacity(1U);
				VkPipelineShaderStageCreateInfo& shader_stage_create_info = shader_stage_create_infos.Last();
				shader_stage_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				shader_stage_create_info.pNext = VK_NULL_HANDLE;
				shader_stage_create_info.module = ((VulkanFragmentShader*)m_ptrFragmentShader)->m_ShaderModule;
				shader_stage_create_info.pName = "main";
				shader_stage_create_info.pSpecializationInfo = VK_NULL_HANDLE;
				shader_stage_create_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
				shader_stage_create_info.flags = 0U;
			}


			// Vertex input layout state
			TArray<VkVertexInputBindingDescription> vertices_input_binding(m_ptrVertexShader->m_vertexInputLayout.Size());
			TArray<VkVertexInputAttributeDescription> vertices_input_attribute(m_ptrVertexShader->m_vertexInputLayout.Size());

			for (size_t i = 0U; i < m_ptrVertexShader->m_vertexInputLayout.Size(); i++)
			{
				size_t size;
				uint32 count, stride;

				VertexInput::GetLayoutStride(m_ptrVertexShader->m_vertexInputLayout, stride);
				m_ptrVertexShader->m_vertexInputLayout[(uint32)i].GetInputTypeInfo(size, count);

				// Bindings
				vertices_input_binding[(uint32)i].binding = m_ptrVertexShader->m_vertexInputLayout[(uint32)i].uiIndex;
				vertices_input_binding[(uint32)i].stride = stride;
				vertices_input_binding[(uint32)i].inputRate = VK_VERTEX_INPUT_RATE_VERTEX; // Per vertex data

																				   // Attributes
				vertices_input_attribute[(uint32)i].binding = m_ptrVertexShader->m_vertexInputLayout[(uint32)i].uiIndex;
				vertices_input_attribute[(uint32)i].location = m_ptrVertexShader->m_vertexInputLayout[(uint32)i].uiIndex;
				vertices_input_attribute[(uint32)i].format = VertexInputTypeFormat(m_ptrVertexShader->m_vertexInputLayout[(uint32)i].uiVertexInputType);
				vertices_input_attribute[(uint32)i].offset = 0U; // Probably an error
			}


			VkPipelineVertexInputStateCreateInfo vertex_input_state_create_info = {};
			vertex_input_state_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
			vertex_input_state_create_info.pNext = VK_NULL_HANDLE;
			vertex_input_state_create_info.vertexBindingDescriptionCount = (uint32)vertices_input_binding.Size();
			vertex_input_state_create_info.pVertexBindingDescriptions = vertices_input_binding.GetData();
			vertex_input_state_create_info.vertexAttributeDescriptionCount = (uint32)vertices_input_attribute.Size();
			vertex_input_state_create_info.pVertexAttributeDescriptions = vertices_input_attribute.GetData();
			vertex_input_state_create_info.flags = 0U;


			// Dynamic states
			TArray<VkDynamicState> dynamic_states;
			dynamic_states.Add(VK_DYNAMIC_STATE_SCISSOR);
			dynamic_states.Add(VK_DYNAMIC_STATE_VIEWPORT);
			// Dynamic scissor and viewport if more than 1 camera


			// Input assembly state
			VkPipelineInputAssemblyStateCreateInfo input_assembly_state_create_info = {};
			input_assembly_state_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
			input_assembly_state_create_info.pNext = VK_NULL_HANDLE;
			input_assembly_state_create_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
			input_assembly_state_create_info.flags = 0U;

			// Viewport state
			VkPipelineViewportStateCreateInfo viewport_state_create_info = {};
			viewport_state_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
			viewport_state_create_info.pNext = VK_NULL_HANDLE;
			viewport_state_create_info.viewportCount = 1U;
			viewport_state_create_info.pViewports = VK_NULL_HANDLE;
			viewport_state_create_info.scissorCount = 1U;
			viewport_state_create_info.pScissors = VK_NULL_HANDLE;
			viewport_state_create_info.flags = 0U;


			VkPipelineDynamicStateCreateInfo dynamic_state_create_info = {};

			if (dynamic_states.Size() > 0U)
			{
				dynamic_state_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
				dynamic_state_create_info.pNext = VK_NULL_HANDLE;
				dynamic_state_create_info.dynamicStateCount = (uint32)dynamic_states.Size();
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
			rasterization_state_create_info.cullMode = VK_CULL_MODE_BACK_BIT;
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
			depth_stencil_state_create_info.depthCompareOp = VK_COMPARE_OP_LESS;
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
			color_blend_attachement_state.colorWriteMask = VK_COLOR_COMPONENT_R_BIT |
				VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

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
			pipeline_layout_create_info.setLayoutCount = 0U;
			pipeline_layout_create_info.pSetLayouts = VK_NULL_HANDLE;
			pipeline_layout_create_info.pushConstantRangeCount = 0U;
			pipeline_layout_create_info.pPushConstantRanges = VK_NULL_HANDLE;
			pipeline_layout_create_info.flags = 0U;

			VkPipelineLayout pipeline_layout;
			vkCreatePipelineLayout(_InDevice, &pipeline_layout_create_info, VK_NULL_HANDLE, &pipeline_layout);


			// Graphics pipeline
			VkGraphicsPipelineCreateInfo graphics_pipeline_create_info = {};
			graphics_pipeline_create_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
			graphics_pipeline_create_info.pNext = VK_NULL_HANDLE;
			graphics_pipeline_create_info.stageCount = (uint32)shader_stage_create_infos.Size();
			graphics_pipeline_create_info.pStages = shader_stage_create_infos.GetData();
			graphics_pipeline_create_info.pVertexInputState = &vertex_input_state_create_info;
			graphics_pipeline_create_info.pInputAssemblyState = &input_assembly_state_create_info;
			graphics_pipeline_create_info.pTessellationState = VK_NULL_HANDLE;
			graphics_pipeline_create_info.pViewportState = &viewport_state_create_info;
			graphics_pipeline_create_info.pRasterizationState = &rasterization_state_create_info;
			graphics_pipeline_create_info.pMultisampleState = &multisample_state_create_info;
			graphics_pipeline_create_info.pDepthStencilState = &depth_stencil_state_create_info;
			graphics_pipeline_create_info.pColorBlendState = &color_blend_state_create_info;
			graphics_pipeline_create_info.pDynamicState = &dynamic_state_create_info;
			graphics_pipeline_create_info.layout = pipeline_layout;
			graphics_pipeline_create_info.renderPass = _InRenderPass;
			graphics_pipeline_create_info.subpass = 0U;
			graphics_pipeline_create_info.basePipelineHandle = VK_NULL_HANDLE;
			graphics_pipeline_create_info.basePipelineIndex = -1;
			graphics_pipeline_create_info.flags = 0U;

			vkCreateGraphicsPipelines(_InDevice, _InPipelineCache, 1U, &graphics_pipeline_create_info, VK_NULL_HANDLE, &m_graphics_pipeline);
		}

		VkPipeline m_graphics_pipeline = VK_NULL_HANDLE;
	};
}


#endif // !__VULKAN_SHADER_HPP_