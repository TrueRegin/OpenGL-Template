#pragma once
#include <glad\glad.h>
#include <stb_image\stb_image.h>

namespace TextureManager {

}

class Texture2D {
private:
	const char* m_Path;
	unsigned char* m_Data;
	unsigned int m_ID;
	int m_Width, m_Height, m_NRChannels;
public:
	Texture2D(const char* imagePath);
	//Texture2D(GLuint textureWrapS, GLuint textureWrapT, float* borderColor, GLuint minFilter, GLuint magFilter);
	~Texture2D();

	void Bind();
	void Unbind();
};