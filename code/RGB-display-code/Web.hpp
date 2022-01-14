/*
 * @Author: sethome
 * @Date: 2021-09-16 12:42:44
 * @LastEditTime: 2021-12-27 10:12:52
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \The-RGB-display-case\code\RGB-display-code\WebControl.hpp
 */

#pragma once

#define _WEB_HPP_
#ifdef _WEB_HPP_

#include "config.hpp"
#include "LED.hpp"
#include "WiFi.hpp"

#include "Update.h"

#include "time.h"

namespace htmlCode
{
#define webContrl_copy "<!DOCTYPE html><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /><html><head>    <style type=\"text/css\">        h {            font-family: arial;            font-size: 30px        }        p {            font-family: arial;            font-size: 15px        }    </style>    <title>RGB display case</title></head><body>    <h style=\"background-color:rgba(0,255,255,0.5)\">RGB display case web control</h>    <p>        project site:        <a href=\"https://github.com/sethome2/The-RGB-display-case\">GITHUB</a>    </p>    <hr>    <h>模块信息</h>    <p>    <ul>        <li>ip地址:WAIT_IP</li>        <li>模块ID:WAIT_ID</li>        <li>模块时间：WAIT_TIME</li>    </ul>    </p>    <p>    <form action=\"/change_module_info\" method=\"POST\">        <p>            模块名字            <input type=\"text\" name=\"moduleName\" value=\"WAIT_MODULE_NAME\">        </p>        <p>            <input type=\"submit\" value=\"更改\">        </p>    </form>    <br>    <button onclick=\"window.location.href='/open_led'\">开启LED</button>    <button onclick=\"window.location.href='/close_led'\">关闭LED</button>    <br><br>    <form action=\"/change_auto_switch_led\" method=\"POST\"> 更改自动开关时间        <p>            自动关闭时间<input type=\"time\" name=\"closeTime\" value=\"WAIT_CLOSE_TIME\" />        </p>        <p>            自动打开时间<input type=\"time\" name=\"openTime\" value=\"WAIT_OPEN_TIME\" />        </p>        <input type=\"submit\" value=\"更改\">    </form>    </p>    <hr>    <h>AP 设置</h>    <form action=\"/change_ap_setting\" method=\"POST\">AP设置        <p>            AP名称<input type=\"input\" name=\"SSID\" value=\"WAIT_AP_NAME\" />        </p>        <p>            AP密码<input type=\"input\" name=\"password\" placeholder=\"密码长度大于8小于14，留空则无密码\" />        </p>        <input type=\"submit\" value=\"更改\">    </form>    <button onclick=\"window.location.href='/c'\">关闭AP（仅本次有效）</button>    <hr>    <h>连接 WIFI 设置</h>    <form action=\"/change_sta_setting\" method=\"POST\">连接WIFI设置        <p>            WIFI名称<input type=\"input\" name=\"SSID\" value=\"WAIT_STA_NAME\" />        </p>        <p>            WIFI密码<input type=\"input\" name=\"password\" />        </p>        <input type=\"submit\" value=\"更改\">    </form>    <button onclick=\"window.location.href='/connection_info'\">连接状态</button>    <hr>    <h>HomeKit设置</h>    <form action=\"/change_homekit_setting\" method=\"POST\">        <p>            HomeKit状态:            <input type=\"checkbox\" name=\"status\" WAIT_HOMEKIT_STATUS>        </p>        <p>            HomeKit配件名称            <input type=\"input\" name=\"homeKitName\" value=\"WAIT_HOMEKIT_NAME\">        </p>        <input type=\"submit\" value=\"更改\">    </form>    <hr>    <h>其他设置设置</h>    <p>        <button onclick=\"window.location.href='/led_anima_setting'\">进入动画设置</button>        <button onclick=\"window.location.href='/ota'\">ota更新</button>        <button onclick=\"window.location.href='/reboot'\">重启（大部分修改重启后生效）</button>    </p>    <hr>    <h>关于</h>    <p>made and designed by sethome</p></body></html>"
#define ota "<!DOCTYPE html><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /><html><head>	<style type=\"text/css\">		h {			font-family: arial;			font-size: 30px		}		p {			font-family: arial;			font-size: 15px		}	</style>	<title>RGB display case</title></head><body>	<h style=\"background-color:rgba(0,255,255,0.5)\">RGB display case web control</h>	<p>		project site:		<a href=\"https://github.com/sethome2/The-RGB-display-case\">GITHUB</a>	</p>	<form method='POST' action='/update' enctype='multipart/form-data'>上传OTA更新		<input type='file' name='update'>		<input type='submit' value='Update'>	</form></body>"
  std::string updateWebContrl()
  {
    std::string webContrl = webContrl_copy;

    int index = 0;

    index = webContrl.find("WAIT_MODULE_NAME");
    if (index != std::string::npos)
      webContrl.replace(index, 16, config::moduleName);

    //模块连接的WiFi IP
    index = webContrl.find("WAIT_IP");
    std::string IP = "";
    if (WiFi_config::getSTA_IP(IP))
      if (index != std::string::npos)
        webContrl.replace(index, 7, IP);

    //模块自身ID
    index = webContrl.find("WAIT_ID");
    if (index != std::string::npos)
    {
      char strbuff[64] = {};
      sprintf(strbuff, "%lld", ESP.getEfuseMac());
      webContrl.replace(index, 7, strbuff);
    }

    //模块时间
    index = webContrl.find("WAIT_TIME");
    if (index != std::string::npos)
    {
      tm nowTime;
      char strbuff[64] = {};
      getLocalTime(&nowTime);
      sprintf(strbuff, "%d-%d-%d %d:%d", nowTime.tm_year + 1900, nowTime.tm_mon, nowTime.tm_mday, nowTime.tm_hour, nowTime.tm_min);
      webContrl.replace(index, 9, strbuff);
    }

    //模块当前时间
    index = webContrl.find("WAIT_CLOSE_TIME");
    if (index != std::string::npos)
      webContrl.replace(index, 15, config::closeTime);

    //模块关闭时间
    index = webContrl.find("WAIT_OPEN_TIME");
    if (index != std::string::npos)
      webContrl.replace(index, 14, config::openTime);

    //模块AP名字
    index = webContrl.find("WAIT_AP_NAME");
    if (index != std::string::npos)
      webContrl.replace(index, 12, config::APname);

    //模块STA名字
    index = webContrl.find("WAIT_STA_NAME");
    if (index != std::string::npos)
      webContrl.replace(index, 13, config::STAname);

    //更新homeKit状态
    index = webContrl.find("WAIT_HOMEKIT_STATUS");
    if (index != std::string::npos)
      if (config::homeKitStatus)
        webContrl.replace(index, 19, "checked");
      else
        webContrl.replace(index, 19, "");

    //homekit配件名称
    index = webContrl.find("WAIT_HOMEKIT_NAME");
    if (index != std::string::npos)
      webContrl.replace(index, 17, config::homeKitName);

    return webContrl;
  }
};

namespace Web
{
  WebServer server;

  //****处理页面******
  //页面响应
  void onRoot() //主页面响应
  {
    server.send(200, "text/html", htmlCode::updateWebContrl().c_str());
  }
  void onOTA() //OTA更新
  {
    server.send(200, "text/html", ota);
  }
  void onOTAFileUpload()
  {
    HTTPUpload &upload = server.upload();
    if (upload.status == UPLOAD_FILE_START)
    {
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN))
      { //start with max available size
        Update.printError(Serial);
      }
    }
    else if (upload.status == UPLOAD_FILE_WRITE)
    {
      /* flashing firmware to ESP*/
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize)
      {
        Update.printError(Serial);
      }
    }
    else if (upload.status == UPLOAD_FILE_END)
    {
      if (Update.end(true))
      { //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      }
      else
      {
        Update.printError(Serial);
      }
    }
  }

  void onNotFound() //404页面
  {
    server.send(200, "text/html", "<!DOCTYPE html><html><head>    <meta charset=\"utf-8\">    <title>RGB展示柜/RGB display case</title></head><body>    <h1>RGB display case web control</h1>    <p>project site        <a href=\"https://github.com/sethome2/The-RGB-display-case\">GITHUB</a>    </p>    <p>404,The site was ate by author.</p></body></html>");
  }
  void onRequesrConnectionInfos()
  {
    if (WiFi_config::connect())
      server.send(200, "text/html", ("<h1>Linked WiFi</h1><p>name:" + config::STAname + "</p>").c_str());
    else
      server.send(200, "text/html", ("<h1>Lose WiFi signal or error password.</h1><p>name:" + config::STAname + "</p>").c_str());
  }

  //动作响应
  //开关灯
  void onCloseLED()
  {
    LED::close();

    server.sendHeader("Location", "/");
    server.send(303);
  }
  void onOpenLED()
  {
    LED::open();

    server.sendHeader("Location", "/");
    server.send(303);
  }
  //重启
  void onReboot()
  {
    server.send(200, "text/html", "<h1>Rebooting...</h1><script type=\"text/javascript\">function jumurl(){self.location = '/';}setTimeout(jumurl,4000);</script>");
    ESP.restart();
  }
  void onCloseAP()
  {
    WiFi_config::disableAP();
  }

  void onChangeModuleInfo() //处理模块信息表单
  {
    if (server.hasArg("moduleName"))
      config::moduleName = server.arg("moduleName").c_str();

    config::saveAll();

    server.sendHeader("Location", "/");
    server.send(303);
  }

  void onChangeAutoSwitchLED() //处理自动开关
  {
    server.sendHeader("Location", "/");
    if (server.hasArg("closeTime"))
      config::closeTime = server.arg("closeTime").c_str();
    if (server.hasArg("openTime"))
      config::openTime = server.arg("openTime").c_str();

    config::saveAll();
    server.send(303);
  }

  void onChangeAPSetting() //处理AP表单
  {
    if (server.hasArg("SSID"))
    {
      config::APname = server.arg("SSID").c_str();
      Serial.println(config::APname.c_str());
    }
    if (server.hasArg("password"))
    {
      config::APpassword = server.arg("password").c_str();
      Serial.println(config::APpassword.c_str());
    }

    config::saveAll();
    WiFi_config::init();

    server.sendHeader("Location", "/");
    server.send(303);
  }
  void onChangeSTASetting() //处理STA表单
  {
    if (server.hasArg("SSID"))
      config::STAname = server.arg("SSID").c_str();

    if (server.hasArg("password"))
      config::STApassword = server.arg("password").c_str();

    config::saveAll();
    WiFi_config::init();

    server.sendHeader("Location", "/");
    server.send(303);
  }

  void onChangeHomeKitSetting() //处理homeKit表单
  {
    if (server.hasArg("status"))
    {
      if (server.arg("status") == "on")
        config::homeKitStatus = true;

      Serial.print("homeKit Status:");
      Serial.print(config::homeKitStatus);
      Serial.println(server.arg("status"));
    }
    else
      config::homeKitStatus = false;

    if (server.hasArg("homeKitName"))
    {
      config::homeKitName = server.arg("homeKitName").c_str();
      Serial.println(("homeKit Name:" + config::homeKitName).c_str());
    }

    config::saveAll();

    server.sendHeader("Location", "/");
    server.send(303);
  }

  void init()
  {
    //页面响应
    server.on("/", onRoot);
    server.onNotFound(onNotFound);
    server.on("/connection_info", onRequesrConnectionInfos);

    //动作响应
    //开关灯动作响应
    server.on("/close_led", onCloseLED);
    server.on("/open_led", onOpenLED);
    //重启动作响应
    server.on("/reboot", onReboot);
    //关闭AP动作响应
    server.on("/close_ap", onCloseAP);

    //处理提交的表单
    server.on("/change_module_info", HTTP_POST, onChangeModuleInfo);
    server.on("/change_auto_switch_led", HTTP_POST, onChangeAutoSwitchLED);
    server.on("/change_ap_setting", HTTP_POST, onChangeAPSetting);
    server.on("/change_sta_setting", HTTP_POST, onChangeSTASetting);
    server.on("/change_homekit_setting", HTTP_POST, onChangeHomeKitSetting);

    //ota更新
    server.on("/ota", onOTA);
    server.on(
        "/update", HTTP_POST, []()
        {
          delay(1000);
          server.sendHeader("Connection", "close");
          server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
          ESP.restart();
        },
        []()
        {
          HTTPUpload &upload = server.upload();
          if (upload.status == UPLOAD_FILE_START)
          {
            Serial.printf("Update: %s\n", upload.filename.c_str());
            if (!Update.begin(UPDATE_SIZE_UNKNOWN))
            { //start with max available size
              Update.printError(Serial);
            }
          }
          else if (upload.status == UPLOAD_FILE_WRITE)
          {
            /* flashing firmware to ESP*/
            if (Update.write(upload.buf, upload.currentSize) != upload.currentSize)
            {
              Update.printError(Serial);
            }
          }
          else if (upload.status == UPLOAD_FILE_END)
          {
            if (Update.end(true))
            { //true to set the size to the current progress
              Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
            }
            else
            {
              Update.printError(Serial);
            }
          }
        });

    server.begin();
  }

  void loop()
  {
    server.handleClient();
  }
};
#endif