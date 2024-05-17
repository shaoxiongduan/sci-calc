// Compact font taken from
// https://hackaday.io/project/6309-vga-graphics-over-spi-and-serial-vgatonic/log/20759-a-tiny-4x6-pixel-font-that-will-fit-on-almost-any-microcontroller-license-mit

#include <stdint.h>
#include "Defines.h"
#include "Font.h"
#include "Platform.h"
#include "Generated/SpriteTypes.h"

void Font::PrintString(const char* str, uint8_t line, uint8_t x, uint8_t colour)
{
	uint8_t* screenPtr = Platform::GetScreenBuffer();
	uint8_t xorMask = colour == COLOUR_BLACK ? 0 : 0xff;
	screenPtr += DISPLAY_WIDTH * line + x;

	for (;;)
	{
		char c = pgm_read_byte(str++);
		if (!c)
			break;

		DrawChar(screenPtr, c, xorMask);
		screenPtr += glyphWidth;
	}
}

void Font::PrintInt(uint16_t val, uint8_t line, uint8_t x, uint8_t colour)
{
	uint8_t* screenPtr = Platform::GetScreenBuffer();
	uint8_t xorMask = colour == COLOUR_BLACK ? 0 : 0xff;
	screenPtr += DISPLAY_WIDTH * line + x;

	if (val == 0)
	{
		DrawChar(screenPtr, '0', xorMask);
		return;
	}

	constexpr int maxDigits = 5;
	char buffer[maxDigits];
	int bufCount = 0;

	for (int n = 0; n < maxDigits && val != 0; n++)
	{
		unsigned char c = val % 10;
		buffer[bufCount++] = '0' + c;
		val = val / 10;
	}

	for (int n = bufCount - 1; n >= 0; n--)
	{
		DrawChar(screenPtr, buffer[n], xorMask);
		screenPtr += glyphWidth;
	}

}

void Font::DrawChar(uint8_t* screenPtr, char c, uint8_t xorMask)
{
	const uint8_t index = ((unsigned char)(c)) - firstGlyphIndex;
	const uint8_t* fontPtr = fontPageData + glyphWidth * index;

	screenPtr[0] = xorMask ^ pgm_read_byte(&fontPtr[0]);
	screenPtr[1] = xorMask ^ pgm_read_byte(&fontPtr[1]);
	screenPtr[2] = xorMask ^ pgm_read_byte(&fontPtr[2]);
	screenPtr[3] = xorMask ^ pgm_read_byte(&fontPtr[3]);
}

