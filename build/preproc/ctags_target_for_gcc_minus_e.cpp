# 1 "c:\\Users\\sethome\\Desktop\\The-RGB-display-case\\code\\RGB-display-code\\RGB-display-code.ino"
# 1 "c:\\Users\\sethome\\Desktop\\The-RGB-display-case\\code\\RGB-display-code\\RGB-display-code.ino"
/*

 * @Author: your name

 * @Date: 2021-09-12 11:05:20

 * @LastEditTime: 2021-09-24 21:24:27

 * @LastEditors: Please set LastEditors

 * @Description: In User Settings Edit

 * @FilePath: \The-RGB-display-case\code\RGB-display-code\RGB-display-code.ino

 */
# 9 "c:\\Users\\sethome\\Desktop\\The-RGB-display-case\\code\\RGB-display-code\\RGB-display-code.ino"
//made by sethome

//第三方库
# 13 "c:\\Users\\sethome\\Desktop\\The-RGB-display-case\\code\\RGB-display-code\\RGB-display-code.ino" 2

# 15 "c:\\Users\\sethome\\Desktop\\The-RGB-display-case\\code\\RGB-display-code\\RGB-display-code.ino" 2

# 17 "c:\\Users\\sethome\\Desktop\\The-RGB-display-case\\code\\RGB-display-code\\RGB-display-code.ino" 2

//项目构建库
# 20 "c:\\Users\\sethome\\Desktop\\The-RGB-display-case\\code\\RGB-display-code\\RGB-display-code.ino" 2


# 23 "c:\\Users\\sethome\\Desktop\\The-RGB-display-case\\code\\RGB-display-code\\RGB-display-code.ino" 2

//ESP32支持库
# 26 "c:\\Users\\sethome\\Desktop\\The-RGB-display-case\\code\\RGB-display-code\\RGB-display-code.ino" 2
# 27 "c:\\Users\\sethome\\Desktop\\The-RGB-display-case\\code\\RGB-display-code\\RGB-display-code.ino" 2
# 28 "c:\\Users\\sethome\\Desktop\\The-RGB-display-case\\code\\RGB-display-code\\RGB-display-code.ino" 2
# 29 "c:\\Users\\sethome\\Desktop\\The-RGB-display-case\\code\\RGB-display-code\\RGB-display-code.ino" 2

# 31 "c:\\Users\\sethome\\Desktop\\The-RGB-display-case\\code\\RGB-display-code\\RGB-display-code.ino" 2

// #include "coredecls.h"

//C&C++库
# 36 "c:\\Users\\sethome\\Desktop\\The-RGB-display-case\\code\\RGB-display-code\\RGB-display-code.ino" 2


# 37 "c:\\Users\\sethome\\Desktop\\The-RGB-display-case\\code\\RGB-display-code\\RGB-display-code.ino"
void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println("\n"); //清除信息

  config::initConfig();

  WiFi_config::init();

  if (config::homeKitStatus)
  {
    while (!WiFi_config::connect())
      delay(1000);
    homeKit::init();
  }
  Web::init();
  LED::init();

  pinMode(13 /*LED引脚 D4 D1*/, 0x02);
  digitalWrite(13 /*LED引脚 D4 D1*/, false);

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
