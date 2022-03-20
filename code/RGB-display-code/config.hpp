/*
 * @Author: your name
 * @Date: 2021-09-16 15:35:05
 * @LastEditTime: 2021-12-27 11:10:13
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \The-RGB-display-case\code\RGB-display-code\config.hpp
 */

#pragma once

#define _CONFIG_HPP_
#ifdef _CONFIG_HPP_

//ESP32支持库
#include "WiFi.h"
#include "WiFiClient.h"
#include "WebServer.h"
#include "ESPmDNS.h"

#include "SPIFFS.h"

#include "Ticker.h"

// #include "coredecls.h"

//C/C++库
#include "string"
#include "time.h"

namespace config
{
  const std::string VERSION = "ver1.0 alpha 2021/12/17";

  /*将会保存在SPIFFS文件系统的*/
  //模块名字
  std::string moduleName = "";
  const std::string moduleName_Url = "/moduleName.txt";

  //模块时区
  char timezone = 8;

  //自动开关设置
  std::string closeTime = "";
  const std::string closeTime_Url = "/closeTime.txt";
  std::string openTime = "";
  const std::string openTime_Url = "/openTime.txt";

  //WiFi配置
  std::string APname = "";
  const std::string defaultAPname = "RGB_Display_Case";
  const std::string APname_Url = "/APname.txt";
  std::string APpassword = "";
  const std::string APpassword_Url = "/APpassword.txt";
  std::string STAname = "";
  const std::string STAname_Url = "/STAname.txt";

  std::string STApassword = "";
  const std::string STApassword_Url = "/STApassword.txt";

  //homeKit配置
  bool homeKitStatus = false;
  const std::string homeKitStatus_Url = "/homeKitStatus.config";

  std::string homeKitName = "";
  const std::string homeKitName_Url = "/homeKitName_Url.txt";

  //LED_anima配置
  std::string LED_animaJson = "";
  const std::string LED_animaJson_Url = "/LED_animaJson.json";

  //读取某一配置(不推荐外部调用)
  const std::string read(std::string url)
  {
    std::string contain;
    File f = SPIFFS.open(url.c_str(), FILE_READ);

    while (f.available())
      contain.insert(contain.end(), f.read());

    f.close();
    return contain;
  }
  //读取所有配置
  void readAll()
  {
    //读取模块名字
    moduleName = read(moduleName_Url);
    //读取开关时间
    openTime = read(openTime_Url);
    closeTime = read(closeTime_Url);

    //读取WIFI配置
    STAname = read(STAname_Url);
    STApassword = read(STApassword_Url);
    APname = read(APname_Url);
    APpassword = read(APpassword_Url);

    //读取homeKit配置
    homeKitStatus = atoi(read(homeKitStatus_Url).c_str());
    homeKitName = read(homeKitName_Url);

    //读取LED_anima配置
    LED_animaJson = read(LED_animaJson_Url);

    //SPIFFS.end();
  }

  //保存某一配置(不推荐外部调用)
  void save(std::string url, std::string contain)
  {
    File f = SPIFFS.open(url.c_str(), FILE_WRITE);
    f.print(contain.c_str());
    // delay(1);
    f.close();
  }
  //保存所有配置
  void saveAll()
  {
    //保存模块名字
    save(moduleName_Url, moduleName);
    //保存开关时间
    save(closeTime_Url, closeTime);
    save(openTime_Url, openTime);

    //保存WiFi配置
    save(STAname_Url, STAname);
    save(STApassword_Url, STApassword);
    save(APname_Url, APname);
    save(APpassword_Url, APpassword);

    //保存homeKit配置
    if (homeKitStatus)
      save(homeKitStatus_Url, "1");
    else
      save(homeKitStatus_Url, "0");
    save(homeKitName_Url, homeKitName);

    //保存LED_anima配置
    save(LED_animaJson_Url, LED_animaJson);
  }

  //输出当前配置
  void serialPrintConfig()
  {
    Serial.println(PSTR("\n####WIFI INFO####"));
    Serial.println(("AP name:" + APname).c_str());
    Serial.println(("AP password:" + APpassword).c_str());
    Serial.println(("STA name:" + STAname).c_str());
    Serial.println(("STA password:" + STApassword).c_str());

    Serial.println(PSTR("\n####HOMEKIT INFO####"));
    Serial.print(PSTR("HomeKit Status:"));
    Serial.println(homeKitStatus);
    Serial.println(("HomeKit Name:" + homeKitName).c_str());

    Serial.println(PSTR("\n####LED_anima Config####"));
    Serial.println(("LED_anima setting:" + LED_animaJson).c_str());
  }

  //从文件系统初始化参数
  void initConfig()
  {
    SPIFFS.begin(true);

    readAll();
    if (APname == "")
      APname = defaultAPname;
    serialPrintConfig();

    configTime(timezone * 3600, 0, "cn.pool.ntp.org", "cn.pool.ntp.org", "cn.pool.ntp.orgcn.pool.ntp.org"); // UTC
  }
}; // namespace config
#endif
