//
// Created by Niumo on 2025/10/12.
//

#ifndef CLOCK_APP_H
#define CLOCK_APP_H

#include "ST7306_LCD.h"
#include "AppBase.h"
#include "UIFont.h"
#include "font_80.h"
#include "font_48.h"
#include "font_20.h"
#include <WiFi.h>

const char* ssid = "Mao Plus";
const char* password = "w0aizuige";

class ClockApp : public AppBase {
public:
    const char* getName() override { return "Clock"; }

    void initialize() override {
        // 初始化显示资源
        lastUpdate = millis();
    }

    void update() override {
        unsigned long currentTime = millis();
        if (currentTime - lastUpdate >= 1000) { // 每秒更新
            lastUpdate = currentTime;
            // 更新时间数据
        }
    }

    void draw() override {
        //WiFi.begin(ssid,password);
        //while(WiFi.status() != WL_CONNECTED){
        //    // statement
        //    delay(500);
        //    printf("Connecting to WiFi...");
        //}
        printf("%d", lastUpdate);
        st7306Lcd.fillScreen(0x0000);
        drawFontChar(st7306Lcd, 60, 60, 0xFFFF, &f80, lastUpdate%10+48);
        drawFontChar(st7306Lcd, 150, 60, 0xFFFF, &f48, (lastUpdate/10)%10+48);
        st7306Lcd.refreshReal();
    }

    void onStart() override {
        AppBase::onStart();
        Serial.println("Clock App Started");
    }

private:
    unsigned long lastUpdate = 0;
};

#endif