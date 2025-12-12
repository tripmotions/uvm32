#include "uvm32_target.h"

uint32_t* framebuffer = (uint32_t*)UVM32_EXTRAM_BASE;
#define WIDTH 320
#define HEIGHT 200

void main(void) {
    uint8_t r = 0, g = 0, b = 0;
    uint32_t framecount = 0;
    while (1) {
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                r = ((x + framecount) ^ y);
                g = (x ^ (y + framecount));
                b = (x ^ y);
                r += framecount;
                g += framecount * 2;
                b += framecount * 3;
                framebuffer[y * WIDTH + x] = (r << 24) | (g << 16) | (b << 8) | 0xFF;
            }
        }
        render(UVM32_EXTRAM_BASE, WIDTH*HEIGHT*4);
        printdec(framecount++);
        println("");
    }
}
