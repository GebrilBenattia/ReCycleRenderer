#pragma once

#include <string>

class OpenGLTexture
{
private:

	unsigned int m_TextureID;

public:

	OpenGLTexture(const std::string& _TexturePath);
	~OpenGLTexture();

	void LoadTexture(const std::string& _TexturePath);
	void CreateTexture();
};