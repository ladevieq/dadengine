#pragma once

#include "../Core/Core.hpp"

enum TEXTURE_MODE
{
	ANYSOTROPIC
};

class Texture2D
{
	uint32 Width;
	uint32 Height;
	uint8 MipLevel;
};