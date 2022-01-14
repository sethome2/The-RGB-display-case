#line 1 "c:\\Users\\sethome\\Desktop\\The-RGB-display-case\\code\\RGB-display-code\\RGB-display-code.ino"
/*
 * @Author: your name
 * @Date: 2021-09-12 11:05:20
 * @LastEditTime: 2021-12-28 01:13:28
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \The-RGB-display-case\code\RGB-display-code\RGB-display-code.ino
 */
//made by sethome

//第三方库
#include "FastLED.h" //LED控制开源库

#include "LED_anima.hpp" //LED动画开源库（我自己写的）

#include "Arduino.h"

//项目构建库
#include "Web.hpp"
#include "WiFi.hpp"
#include "LED.hpp"
#include "homekit.hpp"

//ESP32支持库
#include "WiFi.h"
#include "WiFiClient.h"
#include "WebServer.h"
#include "ESPmDNS.h"

#include "Ticker.h"

// #include "coredecls.h"

//C&C++库
#include "string"

#line 37 "c:\\Users\\sethome\\Desktop\\The-RGB-display-case\\code\\RGB-display-code\\RGB-display-code.ino"
void setup();
#line 68 "c:\\Users\\sethome\\Desktop\\The-RGB-display-case\\code\\RGB-display-code\\RGB-display-code.ino"
void loop();
#line 37 "c:\\Users\\sethome\\Desktop\\The-RGB-display-case\\code\\RGB-display-code\\RGB-display-code.ino"
void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println("\n"); //清除信息

  config::initConfig();

  WiFi_config::init();

  if (config::homeKitStatus) //启动homekit
  {
    for (int i = 0; i < 10; i++) //等待10s，让wifi链接
      if (!WiFi_config::connect())
        break;
      else
        delay(1000);

    homeKit::init();
  }
  else
    homeKit::disenable();

  Web::init();
  LED::init();

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, false);

  Serial.println(config::homeKitName.c_str());
}
void loop()
{
  if (config::homeKitStatus)
    while (1)
    {
      homeKit::loop();
      Web::loop();
    }
  Web::loop();
}

