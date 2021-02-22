#include "texture.h"

GLuint ATLLoadTexture(const char *fileName)
{
	BITMAP bm;
	GLuint idTexture = 0;
	CImage img;				//需要头文件atlimage.h
	HRESULT hr = img.Load(fileName);
	if (!SUCCEEDED(hr))	//文件加载失败
	{
		return NULL;
	}
	HBITMAP hbmp = img;
	if (!GetObject(hbmp, sizeof(bm), &bm))
		return 0;

	glGenTextures(1, &idTexture);
	if (idTexture)
	{
		glBindTexture(GL_TEXTURE_2D, idTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glPixelStoref(GL_PACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, bm.bmWidth, bm.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bm.bmBits);	//这里不是GL_RGB
	}
	return idTexture;
}