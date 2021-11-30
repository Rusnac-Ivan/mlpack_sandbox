#include "GLCanvas.h"
#include <glad/glad.h>

GLCanvas::GLCanvas() : mTextureID(NULL)
{}

GLCanvas::~GLCanvas()
{
	if(mTextureID != NULL)
		glDeleteTextures(1, &mTextureID);
}

void GLCanvas::Init(uint32_t width, uint32_t height)
{
    mSize = ImVec2(width, height);

	glGenTextures(1, &mTextureID);

    glBindTexture(GL_TEXTURE_2D, mTextureID); 

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void GLCanvas::GetData(uint8_t* data)
{
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RED, GL_UNSIGNED_BYTE, data);
}