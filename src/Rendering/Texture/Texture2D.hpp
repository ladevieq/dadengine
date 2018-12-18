#pragma once

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