//
// Created by Niumo on 2025/10/18.
//

#ifndef LECT0_UIFONT_H
#define LECT0_UIFONT_H

#include "FontBase.h"
#include "ST7306_LCD.h"

void drawFontChar(ST7306_LCD &lcd, uint16_t x, uint16_t y, uint16_t color, FontBase *fb, uint16_t uni) {
    if(fb != nullptr)
    {
        if(fb->findUni(uni) != -1)
        {
            FontBase::fontinfo opt = fb->getInfo(fb->findUni(uni));
            printf("%d\n", fb->findUni(uni));
            for(uint16_t cnt = 0; cnt < opt.height*opt.width; cnt++)
            {
                if((opt.data[cnt / 8] >> (7 - cnt % 8)) & 1)
                {
                    lcd.drawPixel(x + cnt / opt.width, y - cnt % opt.width , color);
                    //printf("%d %d \n",x + cnt / opt.height, y + cnt % opt.width);
                }
            }
        }
    }
}

#endif //LECT0_UIFONT_H
