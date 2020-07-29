#include "Texture2D.h"

// Creates a linearly mapped texture
Texture2D::Texture2D(const char* imagePath)
{
	m_Path = imagePath;

	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	m_Data = stbi_load(m_Path, &m_Width, &m_Height, &m_NRChannels, 0);

	if (m_Data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Data);
	}
}

/*
	Read https://learnopengl.com/Getting-started/Textures for more info
	@param textureWrapS - S stands for the x-axis of the image, this parameter defines how the image gets wrapped on the y-axis
	Valid values
		- GL_REPEAT - texture repeats when the texture coordinates x-value is greater than is > 1
		- GL_MIRRORED_REPEAT - Same as GL_REPEAT but the image is mirrored after each repeat
		- GL_CLAMP_TO_EDGE - 
		- GL_CLAMP_TO_BORDER - Gives any coordinates outside of the range 0 and 1 a border color that you define
	@param textureWrapT - T stands for the y-axis of the image, this parameter defines how the image gets wrapped on the y-axis
*/
// Customizable Texture Option, coming soon.
//Texture::Texture(const char* imagePath, GLuint textureWrapS, GLuint textureWrapT, float* borderColor, GLuint minFilter, GLuint magFilter) {
//	if(!borderColor == nullptr)
//}

Texture2D::~Texture2D() {
	
}

void Texture2D::Bind() {
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture2D::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}
