#include "VulkanShader.hpp"
#include <fstream>

std::vector<char> VulkanShader::ReadFile(const std::string& _Filepath)
{
    std::ifstream file(_Filepath, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file!");
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}

VkShaderModule VulkanShader::CreateShaderModule(VkDevice& _LogicalDevice, const std::vector<char>& _Code)
{
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = _Code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(_Code.data());

    VkShaderModule shaderModule;
    if (vkCreateShaderModule(_LogicalDevice, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
        throw std::runtime_error("failed to create shader module!");
    }

    return shaderModule;
}