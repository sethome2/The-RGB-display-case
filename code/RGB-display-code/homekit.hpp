/*
 * @Author: your name
 * @Date: 2021-09-20 01:14:56
 * @LastEditTime: 2022-02-03 19:28:59
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \The-RGB-display-case\code\RGB-display-code\homekit.hpp
 */
#pragma once

#include "config.hpp"
#include "LED.hpp"

#include "string"

#include "HomeSpan.h"

#include "SPIFFS.h"

namespace homeKit
{
  struct RGB_display_case : Service::LightBulb
  {

    int lampPin;                   // store the pin number connected to a hypothetical relay that turns the Table Lamp on/off
    SpanCharacteristic *lampPower; // store a reference to the On Characteristic

    RGB_display_case() : Service::LightBulb()
    { // constructor() method for TableLamp defined with one parameter.  Note we also call the constructor() method for the LightBulb Service.
      lampPower = new Characteristic::On(); // instantiate the On Characteristic and save it as lampPower
    }

    boolean update() // update() method
    { 
      if(LED::status)
        LED::close();
      else
        LED::open();

      return (true); // return true to let HomeKit (and the Home App Client) know the update was successful
    }
  };

  void init()
  {
    homeSpan.begin(); // initialize HomeSpan

    new SpanAccessory();                          // Table Lamp Accessory
    new Service::AccessoryInformation();          // HAP requires every Accessory to implement an AccessoryInformation Service, with 6 *required* Characteristics
    new Characteristic::Name("RGB_display_case"); // Name of the Accessory, which shows up on the HomeKit "tiles", and should be unique across Accessories
    new Characteristic::Manufacturer("sethome");  // Manufacturer of the Accessory (arbitrary text string, and can be the same for every Accessory)
    char strbuff[64] = {};
    sprintf(strbuff, "%lld", ESP.getEfuseMac());
    new Characteristic::SerialNumber(strbuff);     // Serial Number of the Accessory (arbitrary text string, and can be the same for every Accessory)
    new Characteristic::Model("RGB_display_case"); // Model of the Accessory (arbitrary text string, and can be the same for every Accessory)
    new Characteristic::FirmwareRevision("0.1");   // Firmware of the Accessory (arbitrary text string, and can be the same for every Accessory)
    new Characteristic::Identify();                // Provides a hook that allows a HomeKit Client to identify the device

    new Service::HAPProtocolInformation();                // HAP requires every Accessory (except those in a bridge) to implement a Protcol Information Service
    new Characteristic::Version(config::VERSION.c_str()); // Set the Version Characteristic to "1.1.0," which is required by HAP
    
    new RGB_display_case();
    //setLogLevel(0);
  }

  void loop()
  {
    homeSpan.poll();
  }

  void disenable()
  {
  }
};
