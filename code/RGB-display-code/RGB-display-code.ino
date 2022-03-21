/*
 * @Author: sethome
 * @Date: 2021-09-12 11:05:20
 * @LastEditTime: 2022-03-13 22:56:23
 * @LastEditors: sethome
 * @Description: RGB_Display_Case main code
 * @FilePath: \The-RGB-display-case\code\RGB-display-code\RGB-display-code.ino
 */
// made by sethome

//第三方库
#include "FastLED.h" //LED控制开源库

#include "LED_anima.hpp" //LED动画开源库（我自己写的）

#include "Arduino.h"

//项目构建库
#include "Web.hpp"
#include "WiFi.hpp"
#include "LED.hpp"
#include "homekit.hpp"

// ESP32支持库
#include "WiFi.h"
#include "WiFiClient.h"
#include "WebServer.h"
#include "ESPmDNS.h"

#include "Ticker.h"

#include "esp_task_wdt.h"
// C&C++库
#include "string"

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

  // disable the wacthDog because web control is use too much time. (over 1s in AP, but 0.3s in STA) 
  // that will cause system reboot.
  // If you konw how to solove, please tell me in issue.
  disableLoopWDT();
  disableCore0WDT();
  disableCore1WDT(); // ESP32C3 doesn't had
}

void loop()
{
  if (config::homeKitStatus)
    homeKit::loop();
  Web::loop();
  
  //Serial.printf("%lld\n",ESP.getFreeHeap()); // test the memory usage
}
