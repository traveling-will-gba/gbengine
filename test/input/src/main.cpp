#include "video.h"
#include "input.h"
#include "utils.h"

#define RED 0x0000FF

volatile unsigned short *vid_mem = (unsigned short *)0x6000000;

int main() {
	reset_dispcnt();
	set_video_mode(3);
	enable_background(2);

    while(1) {   
        check_buttons_states();

        for(int i=0;i<=9;i++){
            int padding = i + 10;

            if (pressing(1 << i)) {
                for(int x=-2;x<=2;x++) {
                    for(int y=-2;y<=2;y++) {
                        vid_mem[(50 + x) * 240 + (20 + y + i * 10)] = RED;
                    }
                }
            }
            else {
                for(int x=-2;x<=2;x++) {
                    for(int y=-2;y<=2;y++) {
                        vid_mem[(50 + x) * 240 + (20 + y + i * 10)] = 0;
                    }
                }
            }
        }
    }   

    return 0;
}
