#ifndef _GL_CANVAS_H_
#define _GL_CANVAS_H_

#include <cstdint>
#include <imgui.h>

class GLCanvas
{
	uint32_t mTextureID;
	ImVec2 mSize;
public:
	GLCanvas();
	~GLCanvas();
	
	void Init(uint32_t width, uint32_t height);
	void GetData(uint8_t* data);
	uint32_t GetGLTexID() { return mTextureID; }
	ImVec2 GetSize() { return mSize; }

private:

};


#endif