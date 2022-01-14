/*
 * @Author: your name
 * @Date: 2021-09-20 01:14:56
 * @LastEditTime: 2021-12-28 00:44:45
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \The-RGB-display-case\code\RGB-display-code\homekit.hpp
 */
#pragma once

#include "config.hpp"
#include "LED.hpp"

#include "string"

extern "C"
{
#include "homeintegration.h"
}

#include "SPIFFS.h"

namespace homeKit
{
#define pair_file_name "/pair.dat"

  const int led_gpio = 4;
  homekit_service_t *hapservice = {0};

  void init_hap_storage()
  {
    Serial.print("init_hap_storage");
    File fsDAT = SPIFFS.open(pair_file_name, "r");
    if (!fsDAT)
    {
      Serial.println("Failed to read file pair.dat");
      return;
    }
    int size = hap_get_storage_size_ex();
    char *buf = new char[size];
    memset(buf, 0xff, size);
    int readed = fsDAT.readBytes(buf, size);
    Serial.print("Readed bytes ->");
    Serial.println(readed);
    hap_init_storage_ex(buf, size);
    fsDAT.close();
    delete[] buf;
  }

  void storage_changed(char *szstorage, int size)
  {
    SPIFFS.remove(pair_file_name);
    File fsDAT = SPIFFS.open(pair_file_name, "w+");
    if (!fsDAT) //error
      return;
    fsDAT.write((uint8_t *)szstorage, size);
    fsDAT.close();
  }

  void led_callback(homekit_characteristic_t *ch, homekit_value_t value, void *context)
  {
    Serial.println("led_callback");
    if (ch->value.bool_value)
    {
      LED::open();
    }
    else
    {
      LED::close();
    }

    static homekit_characteristic_t *newCh = homekit_service_characteristic_by_type(hapservice, HOMEKIT_CHARACTERISTIC_ON);
    if (newCh)
    {
      Serial.println("found characteristic");
      if (newCh->value.bool_value != ch->value.bool_value)
      { //will notify only if different
        newCh->value.bool_value = ch->value.bool_value;
        homekit_characteristic_notify(newCh, newCh->value);
      }
    }
  }

  void disenable()
  {
    SPIFFS.remove(pair_file_name);
  }

  void init()
  {
    hap_set_identity_gpio(LED_PIN); //identity_led=2 will blink on identity

    /// now will setup homekit device

    //this is for custom storage usage
    // In given example we are using \pair.dat file in our SPIFFS system
    //see implementation below
    init_hap_storage();
    set_callback_storage_change(storage_changed);

    /// We will use for this example only one accessory (possible to use a several on the same ESP)
    //Our accessory type is light bulb, Apple interface will proper show that
    hap_setbase_accessorytype(homekit_accessory_category_lightbulb);

    /// init base properties
    char strbuff[64] = {};
    sprintf(strbuff, "%lld", ESP.getEfuseMac());
    hap_initbase_accessory_service(config::homeKitName.c_str(), "sethome", strbuff, "RGB_display_case", config::VERSION.c_str());
    //设置密码
    //char pwdbuff[11] = {strbuff[0], strbuff[1], strbuff[2], '-', strbuff[3], strbuff[4], '-', strbuff[5], strbuff[6], strbuff[7], '\0'};
    //Serial.println(pwdbuff);
    //hap_set_device_password(pwdbuff);

    //we will add only one light bulb service and keep pointer for nest using
    hapservice = hap_add_lightbulb_service("Led", led_callback, NULL);

    //and finally init HAP
    hap_init_homekit_server();
  }

  void loop()
  {
  }
};
