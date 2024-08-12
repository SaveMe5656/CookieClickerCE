#include <sys/util.h>
#include <graphx.h>
#include <keypadc.h>

// include the program graphics
#include "gfx/gfx.h"

// create a boolean for if the cookie is "clicked" or not
bool clicked = false;

// function for rendering the big cookie
void displayCookie(int x, int y) {
    // render the background
    for (int i = navigationBar_width; i < GFX_LCD_WIDTH; i += bgBlue_width) {
        gfx_Sprite(bgBlue, i, 0);
    }

    // display the cookie
    if (!clicked) gfx_TransparentSprite(perfectCookie, x, y);
    //else gfx_TransparentSprite(nameForClickedCookie, x, y);
}

// function for updating the navigation bar
void updateNav(int nav) {
    // draw the navigation bar
    gfx_Sprite(navigationBar, 0, 0);

    // display the requested nav. bar icon over the enabled section
    gfx_TransparentSprite(icons_tiles[nav], 0, nav * 48 + 12);
}

int main (void) {
    // initialize the graphics
    gfx_Begin();

    // set the palette for the graphics
    gfx_SetPalette(palette_0, sizeof_palette_0, 0);
    gfx_FillScreen(1);
    gfx_SetTransparentColor(0);

    // set drawing to the offscreen buffer
    gfx_SetDrawBuffer();


    // draw the navigation bar with the cookie page enabled
    updateNav(0);

    
    // set the default dimensions for the big cookie
    int cookieX = (GFX_LCD_WIDTH - perfectCookie_width) / 2 + 9;
    int cookieY = (GFX_LCD_HEIGHT - perfectCookie_height) / 2;

    // draw the big cookie
    displayCookie(cookieX, cookieY);
    
    // swap the currently displayed drawing
    gfx_BlitBuffer();

    do {
        // scan the keypad and update kb_Data
        kb_Scan();

        // check if any of the desired buttons are pressed
        if (kb_Data[6] | kb_Data[1]) {
            // update the cookie depending on the key pressed
            if ((kb_Data[6] & kb_Enter) | (kb_Data[1] & kb_2nd)) {
                clicked = true;
                displayCookie(cookieX, cookieY);
            }

            // display the buffer on the screen
            gfx_BlitBuffer();
        } else if (clicked) {
            // reset the cookie's click state
            clicked = false;

            // draw the big cookie
            displayCookie(cookieX, cookieY);
            
            // swap the currently displayed drawing
            gfx_BlitBuffer();
        }

        

    } while (kb_Data[1] != kb_Mode);

    // stop drawing graphics and quit
    gfx_End();
    return 0;
}