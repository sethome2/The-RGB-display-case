# 1 "c:\\Users\\sethome\\Desktop\\The-RGB-display-case\\code\\RGB-display-code\\RGB-display-code.ino"
/*

 * @Author: sethome

 * @Date: 2021-09-12 11:05:20

 * @LastEditTime: 2022-02-05 13:53:37

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

# 33 "c:\\Users\\sethome\\Desktop\\The-RGB-display-case\\code\\RGB-display-code\\RGB-display-code.ino" 2

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
}
void loop()
{
  if (config::homeKitStatus)
    homeKit::loop();
  Web::loop();
  Serial.printf("%lld\n",ESP.getFreeHeap());
  //FastLED.show();
}
