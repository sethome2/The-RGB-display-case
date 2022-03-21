/*
 * @Author: sethome
 * @Date: 2021-09-16 12:42:44
 * @LastEditTime: 2022-02-03 19:47:55
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
#define WEBCONTROL_HTML "<!-- * @Author: sethome * @Date: 2021-09-16 12:19:09 * @LastEditTime: 2022-02-03 17:45:06 * @LastEditors: sethome * @Description: RGB_Display_Case web control * @FilePath: \\The-RGB-display-case\\code\\website\\display case control web - 中文版.html--><!DOCTYPE html><head>    <title>RGB展示柜/RGB display case</title>    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">    <meta charset=\"UTF-8\">    <style>        .text-center {            text-align: center;        }        .flex-container {            display: flex;            flex-flow: row wrap;            align-items: center;            justify-content: space-around;            background-color: lightgrey;        }        .margin {            margin: 5% 3%;        }        input {            outline-style: none;            border: 1px solid #ccc;            border-radius: 3px;        }        button {            outline-style: none;            border: 1px solid #ccc;            border-radius: 3px;        }        p {            font-size: larger;            text-align: center;            margin: 0 auto;        }        .p1 {            font-size: large;        }        .p2 {            font-size: medium;        }        .p3 {            font-size: small;        }    </style></head><body style=\"background-color: lightgray;\">    <nav class=\"text-center margin\" style=\"font-size: x-large;\">RGB display case web control        <div style=\"font-size:medium\">            project repo: <a href=\"https://github.com/sethome2/The-RGB-display-case\">The-RGB-display-case</a>        </div>    </nav>    <!--主要信息设置-->    <div>        <p>主要信息设置</p>        <div class=\"flex-container\" style=\"justify-content: center\">            <div>                <label>                    <p class=\"p1\">基本信息</p>                </label>                <ul class=\"margin\">                    <li>ip地址: WAIT_IP</li>                    <li>模块ID/MAC地址: WAIT_ID</li>                    <li>模块时间: WAIT_TIME</li>                </ul>                <form class=\"margin\" action=\"/change_module_info\" method=\"POST\">                    <label>模块名字</label>                    <input type=\"text\" name=\"moduleName\" value=\"WAIT_MODULE_NAME\">                    <input type=\"submit\" value=\"更改\">                </form>            </div>            <div>                <form class=\"margin text-center\" action=\"/change_auto_switch_led\" method=\"POST\">                    <label>                        <p class=\"p1\">自动开关时间设置</p1>                    </label>                    <div>                        <label> 自动关闭时间</label>                        <input type=\"time\" name=\"closeTime\" value=\"WAIT_CLOSE_TIME\" />                    </div>                    <div>                        <label> 自动打开时间</label>                        <input type=\"time\" name=\"openTime\" value=\"WAIT_OPEN_TIME\" />                    </div>                    <div class=\"text-center\">                        <input type=\"submit\" value=\"更改\">                    </div>                </form>            </div>            <div class=\"margin text-center\">                <div>                    <script>                        function LED_status_color() {                            if (document.getElementById(\"LED_status\").innerText == \"open\") {                                document.getElementById(\"LED_status\").style.color = \"#339933\";                            }                            else {                                document.getElementById(\"LED_status\").style.color = \"#FF6666\";                            }                        }                        setTimeout(\"LED_status_color()\", \"0\");                    </script>                    <label>                        LED状态: <a id=\"LED_status\"                            style=\"border: 1px solid #ccc; border-radius: 4px;\">WAIT_LED_STATUS</a>                        <!--WAIT_LED_STATUS 有两种状态 打开(open) 与 关闭(close)-->                    </label>                </div>                <button onclick=\"window.location.href='/open_led'\">开启LED</button>                <button onclick=\"window.location.href='/close_led'\">关闭LED</button>            </div>        </div>    </div>    </div>    <hr>    <div class=\"flex-container\">        <!--AP连接设置-->        <div class=\"margin\">            <p>AP 设置</p>            <div>                <form action=\"/change_ap_setting\" method=\"POST\">                    <div>                        <label>AP名称</label>                        <input type=\"input\" name=\"SSID\" value=\"WAIT_AP_NAME\" />                    </div>                    <div>                        <label>AP密码</label>                        <input type=\"password\" name=\"password\" placeholder=\"密码长度大于8小于14，留空则无密码\" />                    </div>                    <div class=\"text-center\">                        <input type=\"submit\" value=\"更改\">                    </div>                </form>            </div>            <div class=\"text-center margin\">                <button onclick=\"window.location.href='/close_ap'\">关闭AP（仅本次有效）</button>            </div>        </div>        <!--连接 WIFI 设置-->        <div class=\"margin\">            <p>连接 WIFI 设置</p>            <form action=\"/change_sta_setting\" method=\"POST\">                <div>                    <label>WIFI名称</label>                    <input type=\"input\" name=\"SSID\" value=\"WAIT_STA_NAME\" />                </div>                <div>                    <label>WIFI密码</label>                    <input type=\"password\" name=\"password\" placeholder=\"留空则无密码\" />                </div>                <div class=\"text-center\">                    <input type=\"submit\" value=\"更改\">                </div>            </form>            <!--<button onclick=\"window.location.href='/connection_info'\">连接状态</button>-->            <div class=\"margin text-center\">                <script>                    function Connetion_status_color() {                        if (document.getElementById(\"connetion_status\").innerText == \"connected\") {                            document.getElementById(\"connetion_status\").style.color = \"#339933\";                        }                        else {                            document.getElementById(\"connetion_status\").style.color = \"#FF6666\";                        }                    }                    setTimeout(\"Connetion_status_color()\", \"0\");                </script>                <label>连接状态:                    <a id=\"connetion_status\">WAIT_CONNETION_INFO</a>                    <!--WAIT_CONNETION_INFO 已连接(connected) 未连接(unconnect)-->                </label>            </div>        </div>        <!--HomeKit设置-->        <div class=\"margin\">            <p>HomeKit设置</p>            <form action=\"/change_homekit_setting\" method=\"POST\">                <div>                    <label>HomeKit状态:</label>                    <input type=\"checkbox\" name=\"status\" WAIT_HOMEKIT_STATUS>                </div>                <div>                    <label>HomeKit配件名称</label>                    <input type=\"input\" name=\"homeKitName\" value=\"WAIT_HOMEKIT_NAME\">                </div>                <div class=\"text-center\">                    <input type=\"submit\" value=\"更改\">                </div>            </form>        </div>        <!--其他设置-->        <div class=\"margin\">            <p>其他设置设置</p>            <div style=\" text-align: center;\">                <button onclick=\"window.location.href='/led_anima_setting'\">进入动画设置</button>                <button onclick=\"window.location.href='/ota'\">ota更新</button>                <button onclick=\"window.location.href='/reboot'\">重启（大部分修改重启后生效）</button>            </div>        </div>    </div></body><hr><footer class=\"text-center\" style=\"position: sticky;\">    <p class=\"p2\">made and designed by sethome</p></footer>"
#define OTA_HTML "<!DOCTYPE html><head>	<style type=\"text/css\">		.text-center {			text-align: center;		}	</style>	<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">	<meta charset=\"UTF-8\">	<title>RGB Display Case Update</title></head><body style=\"background-color: lightgray;\">	<nav style=\"font-size: larger; text-align: center; margin: 0 auto;		\">RGB display case web control		<p class=\"font-size: medium;\">			project site:			<a href=\"https://github.com/sethome2/The-RGB-display-case\">GITHUB</a>		</p>	</nav>	<div class=\"text-center\" style=\"font-size:large\">		<form method='POST' action='/update' enctype='multipart/form-data'>UpdateFile			<input type='file' name='update'>			<input type='submit' value='Update'>		</form>	</div></body>"
#define CHANGE_ANIMA_HTML "<!DOCTYPE html><head>    <title>RGB Display Case Animation</title>    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">    <meta charset=\"UTF-8\">    <style>        .text-center {            text-align: center;        }        .flex-container {            display: flex;            flex-flow: row wrap;            align-items: center;            justify-content: space-around;            background-color: lightgrey;        }        input {            outline-style: none;            border: 1px solid #ccc;            border-radius: 3px;        }        button {            outline-style: none;            border: 1px solid #ccc;            border-radius: 3px;        }        p {            font-size: larger;            text-align: center;            margin: 0 auto;        }        .p1 {            font-size: large;        }        .p2 {            font-size: medium;        }        .p3 {            font-size: small;        }    </style></head><body style=\"background-color: lightgray;\">    <nav class=\"text-center margin\" style=\"font-size: x-large;\">RGB display case web control        <div class=\"p2\">            project repo: <a href=\"https://github.com/sethome2/The-RGB-display-case\">The-RGB-display-case</a>        </div>    </nav>    <div class=\"text-center\">        <p>Animation Json</p>        <form action=\"/change_anima\" method=\"post\">            <textarea name=\"animaJson\" ontenteditable=\"true\" wrap=\"soft\"                style=\"border-radius: 4px; border-style: hidden; width: 80%;\">            WAIT_JSON</textarea>            <p>                <input type=\"submit\" value=\"change\">            </p>        </form>        <script>            var textarea = document.querySelector('textarea');            textarea.addEventListener('input', (e) => {                textarea.style.height = '100px';                textarea.style.height = e.target.scrollHeight + 'px';            });        </script>    </div></body><hr><footer class=\"text-center\" style=\"position: sticky;\">    <p class=\"p2\">made and designed by sethome</p></footer>"
#define NOT_FOUNED_HTML "<!DOCTYPE html><html><head>	<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">	<meta charset=\"UTF-8\">	<title>RGB Display Case</title></head><body style=\"background-color: lightgray;\">    <p style=\"text-align: center; font-size: xx-large;\">404,not found.</p>    <p style=\"text-align: center;\">RGB Display Case</p></body></html>"

  std::string updateWebContrl()
  {
    std::string webContrl = WEBCONTROL_HTML;

    unsigned int index = 0;
    /**
     * @brief 替换HTML的文字 顺序不能乱 从前到后
     *        replace HTML text, and don't mess up the order, front to back
     */

    //模块连接的WiFi IP
    index = webContrl.find("WAIT_IP");
    std::string IP = "";
    if (index != std::string::npos)
      if (WiFi_config::getSTA_IP(IP))
        webContrl.replace(index, 7, IP);

    //模块自身ID
    index = webContrl.find("WAIT_ID", index);
    if (index != std::string::npos)
    {
      char strbuff[64] = {};
      sprintf(strbuff, "%lld", ESP.getEfuseMac());
      webContrl.replace(index, 7, strbuff);
    }

    //模块时间
    index = webContrl.find("WAIT_TIME", index);
    if (index != std::string::npos)
    {
      tm nowTime;
      char strbuff[64] = {};
      getLocalTime(&nowTime);
      sprintf(strbuff, "%d-%d-%d %d:%d", nowTime.tm_year + 1900, nowTime.tm_mon, nowTime.tm_mday, nowTime.tm_hour, nowTime.tm_min);
      webContrl.replace(index, 9, strbuff);
    }

    //模块的名字
    index = webContrl.find("WAIT_MODULE_NAME", index);
    if (index != std::string::npos)
      webContrl.replace(index, 16, config::moduleName);

    //模块关闭时间
    index = webContrl.find("WAIT_CLOSE_TIME", index);
    if (index != std::string::npos)
      webContrl.replace(index, 15, config::closeTime);

    //模块打开时间
    index = webContrl.find("WAIT_OPEN_TIME", index);
    if (index != std::string::npos)
      webContrl.replace(index, 14, config::openTime);

    //模块LED状态
    index = webContrl.find("WAIT_LED_STATUS", index);
    if (index != std::string::npos)
      if (LED::status)
        webContrl.replace(index, 15, "open");
      else
        webContrl.replace(index, 15, "close");

    //模块AP名字
    index = webContrl.find("WAIT_AP_NAME", index);
    if (index != std::string::npos)
      webContrl.replace(index, 12, config::APname);

    //模块STA名字
    index = webContrl.find("WAIT_STA_NAME", index);
    if (index != std::string::npos)
      webContrl.replace(index, 13, config::STAname);

    //模块连接WiFi状态
    index = webContrl.find("WAIT_CONNETION_INFO", index);
    if (index != std::string::npos)
      if (WiFi_config::connect())
        webContrl.replace(index, 19, "connected");
      else
        webContrl.replace(index, 19, "unconnect");

    //更新homeKit状态
    index = webContrl.find("WAIT_HOMEKIT_STATUS", index);
    if (index != std::string::npos)
      if (config::homeKitStatus)
        webContrl.replace(index, 19, "checked");
      else
        webContrl.replace(index, 19, "");

    // homekit配件名称
    index = webContrl.find("WAIT_HOMEKIT_NAME", index);
    if (index != std::string::npos)
      webContrl.replace(index, 17, config::homeKitName);

    return webContrl;
  }

  std::string updateAnimaJson()
  {
    std::string animaWeb = CHANGE_ANIMA_HTML;
    unsigned int index = 0;
    index = animaWeb.find("WAIT_JSON", index);
    if (index != std::string::npos)
        animaWeb.replace(index, 9, config::LED_animaJson);

    return animaWeb;
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
  void onFavicon()
  {
    server.send(404);
  }
  void onLED_AmimaSetting()
  {
    server.send(200, "text/html", CHANGE_ANIMA_HTML);
  }

  void onOTA() // OTA更新
  {
    server.send(200, "text/html", htmlCode::updateAnimaJson().c_str());
  }

  void onOTAFileUpload()
  {
    HTTPUpload &upload = server.upload();
    if (upload.status == UPLOAD_FILE_START)
    {
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN))
      { // start with max available size
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
      { // true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      }
      else
      {
        Update.printError(Serial);
      }
    }
  }

  void onNotFound() // 404页面
  {
    server.send(200, "text/html", NOT_FOUNED_HTML);
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

    server.sendHeader("Location", "/");
    server.send(303);
  }

  //处理模块信息表单
  void onChangeModuleInfo()
  {
    if (server.hasArg("moduleName"))
      config::moduleName = server.arg("moduleName").c_str();

    // config::saveAll();
    config::save(config::moduleName_Url, config::moduleName);

    server.sendHeader("Location", "/");
    server.send(303);
  }

  //处理自动开关
  void onChangeAutoSwitchLED()
  {
    if (server.hasArg("closeTime"))
      config::closeTime = server.arg("closeTime").c_str();
    if (server.hasArg("openTime"))
      config::openTime = server.arg("openTime").c_str();

    // config::saveAll();
    config::save(config::closeTime_Url, config::closeTime);
    config::save(config::openTime_Url, config::openTime);

    server.sendHeader("Location", "/");
    server.send(303);
  }

  //处理AP表单
  void onChangeAPSetting()
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

    // config::saveAll();
    config::save(config::APname_Url, config::APname);
    config::save(config::APpassword_Url, config::APpassword);

    server.sendHeader("Location", "/");
    server.send(303);

    // WiFi_config::init(); // reset the WiFi will lose the web connection
  }

  //处理STA表单
  void onChangeSTASetting()
  {
    if (server.hasArg("SSID"))
      config::STAname = server.arg("SSID").c_str();

    if (server.hasArg("password"))
      config::STApassword = server.arg("password").c_str();

    // config::saveAll();
    config::save(config::STAname_Url, config::STAname);
    config::save(config::STApassword_Url, config::STApassword);

    server.sendHeader("Location", "/");
    server.send(303);

    // WiFi_config::init(); // reset the WiFi will lose the web connection
  }

  void onChangeHomeKitSetting() //处理homeKit表单
  {
    if (server.hasArg("status"))
    {
      if (server.arg("status") == "on")
        config::homeKitStatus = true;
    }
    else
      config::homeKitStatus = false;

    if (server.hasArg("homeKitName"))
      config::homeKitName = server.arg("homeKitName").c_str();

    // config::saveAll();
    config::save(config::homeKitName_Url, config::homeKitName);
    if (config::homeKitStatus)
      config::save(config::homeKitStatus_Url, "1");
    else
      config::save(config::homeKitStatus_Url, "0");

    server.sendHeader("Location", "/");
    server.send(303);
  }

  void onChangeAnima()
  {
    if (server.hasArg("animaJson"))
      config::LED_animaJson = server.arg("animaJson").c_str();

    // config::saveAll();
    config::save(config::LED_animaJson_Url, config::LED_animaJson);

    server.sendHeader("Location", "/led_anima_setting");
    server.send(303);
  }

  void init()
  {
    //页面响应
    server.on("/", onRoot);
    server.onNotFound(onNotFound);
    server.on("/favicon.ico", onFavicon);
    server.on("/led_anima_setting", onLED_AmimaSetting);

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

    server.on("/change_anima", HTTP_POST, onChangeAnima); // 修改LED颜色

    // ota更新
    server.on("/ota", onOTA);
    server.on(
        "/update", HTTP_POST, []()
        {
          delay(1000);
          server.sendHeader("Connection", "close");
          server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
          ESP.restart(); },
        []()
        {
          HTTPUpload &upload = server.upload();
          if (upload.status == UPLOAD_FILE_START)
          {
            Serial.printf("Update: %s\n", upload.filename.c_str());
            if (!Update.begin(UPDATE_SIZE_UNKNOWN))
            { // start with max available size
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
            { // true to set the size to the current progress
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