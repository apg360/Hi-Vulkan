
#pragma once // include guard

//# -----------------------------------------------------
// Step 3 - Find/Create GPU Device and setup your selected device
//
//________//________// START
//Variables and Functions before main function of this step
VkResult vk_error;
struct global_parameters * local_VulkanKore_param;

//________//________// END

int SetupRenderPass(struct global_parameters *pVulkanKore_param)
{
	local_VulkanKore_param=pVulkanKore_param;
	
	// Clear the framebuffer's color and depth attachments (set clear color to red).
	// Always store the fragment stage results.
	VezAttachmentReference attachmentReferences[2]     = {};
	attachmentReferences[0].clearValue.color = { 0.3f, 0.3f, 0.3f, 0.0f };
	attachmentReferences[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	attachmentReferences[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	attachmentReferences[1].clearValue.depthStencil.depth = 1.0f;
	attachmentReferences[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	attachmentReferences[1].storeOp = VK_ATTACHMENT_STORE_OP_STORE;

	// Begin a render pass.
	VezRenderPassBeginInfo beginInfo = {};
	beginInfo.framebuffer = framebuffer;
	beginInfo.attachmentCount = (uint32_t)COUNT_ARRAY_ELEMS(attachmentReferences);
	beginInfo.pAttachments = &attachmentReferences;
	vezCmdBeginRenderPass(commandBuffer, &beginInfo);
	
	//--//--//--//
    //Cleanup (for every "malloc" there must be a "free"
	
	return EXIT_SUCCESS;
}// END SetupRenderPass(..)
