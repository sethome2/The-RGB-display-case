#include "Arduino.h"

#include "homekit/types.h"
#include "homekit/homekit.h"
#include "homekit/characteristics.h"
#include "stdio.h"
#include "port.h"
#include "esp_wifi_types.h"
#include "esp_wifi.h"

static char ACCESSORY_NAME[32] = "ESP32_LED";
#define ACCESSORY_SN  ("SN_0123456")  //SERIAL_NUMBER
#define ACCESSORY_MANUFACTURER ("sethome")
#define ACCESSORY_MODEL  ("ESP32_DEVKIT")

void led_set_power(bool on) {
  
}
