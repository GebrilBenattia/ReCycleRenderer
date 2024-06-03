#include "Framebuffers.hpp"
#include <stdexcept>

void Framebuffers::CreateFramebuffers(VkDevice& _LogicalDevice, std::vector<VkFramebuffer>& _Framebuffers, std::vector<VkImageView>& _Attachement0, size_t _ViewCount, VkRenderPass& _RenderPass, VkExtent2D _Extent)
{
    _Framebuffers.resize(_ViewCount);

    for (size_t i = 0; i < _ViewCount; i++) {
        VkImageView attachements[] = {
            _Attachement0[i]
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = _RenderPass;
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachements;
        framebufferInfo.width = _Extent.width;
        framebufferInfo.height = _Extent.height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(_LogicalDevice, &framebufferInfo, nullptr, &_Framebuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create framebuffer!");
        }
    }
}

void Framebuffers::DestroyFramebuffers(VkDevice& _LogicalDevice, std::vector<VkFramebuffer>& _Framebuffers)
{
    for (size_t i = 0; i < _Framebuffers.size(); i++) {
        vkDestroyFramebuffer(_LogicalDevice, _Framebuffers[i], nullptr);
    }
    _Framebuffers.clear();
}