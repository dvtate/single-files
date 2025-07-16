
#include <stdio.h>
#include <inttypes.h>
#include <stdarg.h>

#define COLOR_RESET		"\x1B[0m"


inline void textColor()
{
	puts(COLOR_RESET);
}


inline void cycle3(uint8_t& v0, uint8_t& v1, uint8_t& v2, uint8_t& curHi)
{

	if (curHi == 0) {
		v0--; v1++;
	} else if (curHi == 1) {
		v1--; v2++;
	} else if (curHi == 2) {
		v2--; v0++;
	}

	if (v0 <= 0 && curHi == 0)
		curHi = 1;
	else if (v1 <= 0 && curHi == 1)
		curHi = 2;
	else if (v2 <= 0 && curHi == 2)
		curHi = 0;

}
inline void color_puts(const char* text, uint8_t red, uint8_t green, uint8_t blue)
	{ printf("\x1B[38;2;%d;%d;%dm%s\x1B[0m", red, green, blue, text); }	

void color_printf(uint8_t red, uint8_t green, uint8_t blue, const char* format, ...){

    va_list args;
    va_start(args, format);

	printf("\x1B[38;2;%d;%d;%dm", red, green, blue); 

    vprintf(format, args);

    va_end(args);

	printf(COLOR_RESET);

}	

int main(){

	uint8_t r = 255, g = 0, b = 0, curhi = 0;

	for (int i = 0; i < 10000; i++) {
		color_puts("hello world", r, g, b);
		cycle3(r,g,b,curhi);
	}

}
