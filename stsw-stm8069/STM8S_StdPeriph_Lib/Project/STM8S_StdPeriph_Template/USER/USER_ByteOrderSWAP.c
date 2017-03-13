

#include "user_byteorderswap.h"

uint32_t swapInt32(uint32_t value)
{
	return ((value & 0x000000FF)<<24)|
			((value & 0x0000FF00)<<8)|
			((value & 0x00FF0000)>>8)|
			((value & 0xFF000000)>>24);
}