#line 1 "c:\\Users\\sethome\\Desktop\\The-RGB-display-case\\code\\RGB-display-code\\homekit.hpp"
/*
 * @Author: your name
 * @Date: 2021-09-20 01:14:56
 * @LastEditTime: 2021-10-10 22:36:06
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \The-RGB-display-case\code\RGB-display-code\homekit.hpp
 */
#pragma once

#include "config.hpp"
#include "LED.hpp"
#include "LED.hpp"

#include "string"

#include "arduino_homekit_server.h";

#include "SPIFFS.h"
namespace homeKit
{
  void init()
  {

  }

  void loop()
  {

  }
};

// //ESP_HAP库
// extern "C" {
// #include "homeintegration.h"
// }

// namespace homeKit
// {
//   homekit_service_t *hapservice = {0};
// #define pair_file_name "/pair.dat"

//   void led_callback(homekit_characteristic_t *ch, homekit_value_t value, void *context)
//   {
//     if (ch->value.bool_value == true)
//       LED::close();
//     else
//       LED::open();

//     homekit_characteristic_t *ch1 = homekit_service_characteristic_by_type(hapservice, HOMEKIT_CHARACTERISTIC_ON);
//     if (ch1)
//       if (ch1->value.bool_value != ch->value.bool_value)
//       { //wil notify only if different
//         ch1->value.bool_value = ch->value.bool_value;
//         homekit_characteristic_notify(ch, ch->value);
//       }
//   }

//   //存储信息更改的回调函数
//   void storage_changed(char *szstorage, int bufsize)
//   {
//     SPIFFS.begin();
//     SPIFFS.remove(pair_file_name);
//     File fsDAT = SPIFFS.open(pair_file_name, "w+");

//     fsDAT.write((uint8_t *)szstorage, bufsize);

//     fsDAT.close();

//     SPIFFS.end();
//   }

//   void init()
//   {
//     //disable_extra4k_at_link_time();

//     //配置设置文件
//     if (!SPIFFS.exists(pair_file_name))
//     {
//       Serial.println("init homekit.bat");

//       SPIFFS.begin();
//       File fsDAT = SPIFFS.open(pair_file_name, "r");

//       int size = hap_get_storage_size_ex();
//       char *buf = new char[size];
//       memset(buf, 0xff, size);
//       int readed = fsDAT.readBytes(buf, size);
//       hap_init_storage_ex(buf, size);
//       fsDAT.close();
//       delete[] buf;
//       SPIFFS.end();
//     }

//     //设置文件更改回调
//     set_callback_storage_change(storage_changed);

//     //使用基本库里的灯泡
//     hap_setbase_accessorytype(homekit_accessory_category_lightbulb);

//     // char strbuff[8] = {};
//     // itoa(ESP.getChipId(), strbuff, 10);
//     // strbuff[7] = '0';

//     hap_initbase_accessory_service("RGB_DISPLAY_CASE", "made by sethome", "SN_00000000", "EspHapLed", "1.0"); //初始化信息

//     //添加服务
//     hapservice = hap_add_lightbulb_service("Led", led_callback, (void *)&" ");

//     // std::string pwd(strbuff);
//     // pwd.insert(2,1,'-');
//     // pwd.insert(6,1,'-');
//     // hap_set_device_password(strbuff);

//     hap_init_homekit_server();
//   }

//   void loop()
//   {
//     hap_homekit_loop();
//   }
// }; // namespace homeKit
