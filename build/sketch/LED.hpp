#line 1 "c:\\Users\\sethome\\Desktop\\The-RGB-display-case\\code\\RGB-display-code\\LED.hpp"
/*
 * @Author: your name
 * @Date: 2021-09-16 19:55:32
 * @LastEditTime: 2022-02-05 13:53:20
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \The-RGB-display-case\code\RGB-display-code\LED.hpp
 */

#pragma once

#include "config.hpp"

#include "LED_anima.hpp"
#include "FastLED.h"

#define BACK_LED_NUM 8
#define LEFT_LED_NUM 8
#define FRONT_LED_NUM 8
#define RIGHT_LED_NUM 8
#define TOP_LED_NUM 64 //灯光配置 先后再左，然后前，接着右，最后上（即后左前右上排列LED编号在LED库中）
#define LED_PIN 5      //LED引脚 D4 D1

#define TickerUpdataSpeed 0.01 //定义定时器，100HZ的刷新率

const int numLED = (BACK_LED_NUM + LEFT_LED_NUM + FRONT_LED_NUM + RIGHT_LED_NUM + TOP_LED_NUM);

LED_anima::areaManage<numLED> anima; //LED动画类

namespace LED
{
   CRGBArray<numLED> LED_sendbuff;

   //LED 状态
   bool status = true;
   void open() { status = true; }
   void close() { status = false; }

   Ticker updataTicker; //更新LED的定时器
   void change()        //根据动画函数改变LED颜色
   {
      if (!status)
      {
         for (int i = 0; i < numLED; i++)
            LED_sendbuff[i] = CRGB(0x000000);

         //FastLED.show();
         return;
      }

      anima.update();
      for (int i = 0; i < numLED; i++)
         LED_sendbuff[i] = CRGB(anima.LEDs[i].RGB());

      //FastLED.show();
   }

   Ticker autoOpen_close; //自动开关
   void cheakTime()
   {
      tm nowTime;
      getLocalTime(&nowTime);
      if (nowTime.tm_hour == atoi(config::closeTime.substr(0, 2).c_str()) &&
          nowTime.tm_min == atoi(config::closeTime.substr(3, 2).c_str()))
         close();
      if (nowTime.tm_hour == atoi(config::openTime.substr(0, 2).c_str()) &&
          nowTime.tm_min == atoi(config::openTime.substr(3, 2).c_str()))
         open();
   }

   void init()
   {
      FastLED.addLeds<WS2812B, LED_PIN, GRB>(LED_sendbuff, numLED);
      FastLED.setTemperature(DirectSunlight);
      FastLED.setCorrection(TypicalSMD5050);

      for (size_t i = 0; i < numLED; i++)
      {
         LED_sendbuff[i] = CRGB(0xAA5501);
         FastLED.show();
         delay(20);
      }
      for (size_t i = 0; i < numLED; i++)
      {
         LED_sendbuff[i] = CRGB(0x0000000);
      }
      FastLED.show();

      if (config::LED_animaJson == "")
      {
         anima.addArea("fuck", "{\"LED_id\":[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31],\"anima\":{\"color\":{\"1\":{\"argv\":{\"frame\":\"1000\"},\"name\":\"colorFlow\"}},\"LEDs\":{\"1\":{\"name\":\"flow\",\"argv\":{\"frame\":\"100\"}}}},\"setColor\":11162881}");
         Serial.println("init anima.");
      }
      updataTicker.attach(TickerUpdataSpeed, change); //设定定时器

      autoOpen_close.attach(10, cheakTime); //设定定时器
   }
}; // namespace LED
