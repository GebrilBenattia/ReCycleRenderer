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

void VulkanSemaphore::CreateSemaphores(VkDevice& _LogicalDevice, std::vector<VkSemaphore>& _Semaphores, int _FramesInFlightCount)
{
	_Semaphores.resize(_FramesInFlightCount);

	VkSemaphoreCreateInfo semaphoreInfo{};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	for (size_t i = 0; i < _FramesInFlightCount; i++) {
		if (vkCreateSemaphore(_LogicalDevice, &semaphoreInfo, nullptr, &_Semaphores[i]) != VK_SUCCESS) {
			throw std::runtime_error("failed to create Semaphore objects for a frame!");
		}
	}
}

void VulkanSemaphore::DestroySemaphore(VkDevice& _LogicalDevice, VkSemaphore& _Semaphore)
{
	vkDestroySemaphore(_LogicalDevice, _Semaphore, nullptr);
}

void VulkanSemaphore::DestroySemaphores(VkDevice& _LogicalDevice, std::vector<VkSemaphore>& _Semaphores)
{
	for (size_t i = 0; i < _Semaphores.size(); i++) {
		vkDestroySemaphore(_LogicalDevice, _Semaphores[i], nullptr);
	}
}