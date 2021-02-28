#ifndef DISPLAY_H
#define DISPLAY_H

#include <lvgl.h>

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

class Display
{
private:

public:
	void init();
	void routine();
};

#endif
