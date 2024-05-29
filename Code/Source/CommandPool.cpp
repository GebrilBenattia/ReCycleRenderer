#include "CommandPool.hpp"
#include <stdexcept>
#include <PhysicalDevice.hpp>

void CommandPool::CreateCommandPool(VkPhysicalDevice& _PhysicalDevice, VkSurfaceKHR& _Surface, VkDevice& _LogicalDevice, VkCommandPool& _CmdPool)
{
	QueueFamilyIndices queueFamilyIndices = PhysicalDevice::FindQueueFamilies(_PhysicalDevice, _Surface);

	VkCommandPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

	if (vkCreateCommandPool(_LogicalDevice, &poolInfo, nullptr, &_CmdPool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create command pool!");
	}
}

void CommandPool::DestroyCommandPool(VkDevice& _LogicalDevice, VkCommandPool& _CmdPool)
{
	vkDestroyCommandPool(_LogicalDevice, _CmdPool, nullptr);
}