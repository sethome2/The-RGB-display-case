/*
 * @Author: your name
 * @Date: 2021-09-16 15:23:17
 * @LastEditTime: 2022-03-13 01:25:03
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \The-RGB-display-case\code\RGB-display-code\WiFi.hpp
 */

#pragma once

#include "config.hpp"

#include "ESPmDNS.h"

namespace WiFi_config
{
  void init()
  {
    WiFi.mode(WIFI_AP);
    WiFi.hostname(config::moduleName.c_str());

    //默认IP地址为192.168.4.1
    WiFi.softAP(config::APname.c_str(), config::APpassword.c_str());
    //WiFi.begin(config::STAname.c_str(), config::STApassword.c_str());

    MDNS.begin(config::moduleName.c_str());
    MDNS.addService("https", "tcp", 80);
    MDNS.addService("http", "tcp", 80);
  }

  void disableAP() { WiFi.softAPdisconnect(true); }
  bool connect() { return WiFi.status() == WL_CONNECTED; }
  bool getSTA_IP(std::string &IP)
  {
    if (WiFi.isConnected())
    {
      IP = WiFi.localIP().toString().c_str();
      return true;
    }
    else
      return false;
  }
};
