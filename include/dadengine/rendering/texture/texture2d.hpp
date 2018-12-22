#ifndef __TEXTURE_2D_HPP_
#define __TEXTURE_2D_HPP_

#include <stdint.h>

enum TEXTURE_MODE
{
	ANYSOTROPIC
};

class Texture2D
{
	uint32_t Width;
	uint32_t Height;
	uint8_t MipLevel;
};

#endif //__TEXTURE_2D_HPP_