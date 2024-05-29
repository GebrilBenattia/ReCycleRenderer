#include "VulkanSemaphore.hpp"
#include <stdexcept>

void VulkanSemaphore::CreateSemaphore(VkDevice& _LogicalDevice, VkSemaphore& _Semaphore)
{
	VkSemaphoreCreateInfo semaphoreInfo{};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	if (vkCreateSemaphore(_LogicalDevice, &semaphoreInfo, nullptr, &_Semaphore) != VK_SUCCESS) {
		throw std::runtime_error("failed to create Semaphore objects for a frame!");
	}
}

void VulkanSemaphore::DestroySemaphore(VkDevice& _LogicalDevice, VkSemaphore& _Semaphore)
{
	vkDestroySemaphore(_LogicalDevice, _Semaphore, nullptr);
}