#include "OpenGLTexture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

OpenGLTexture::OpenGLTexture(const std::string& _VertexPath)
	:m_TextureID(0)
{
}

OpenGLTexture::~OpenGLTexture()
{
}