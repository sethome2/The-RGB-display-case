#include <FastLED.h>//LED控制开源库
#include <functional>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <Ticker.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <cmath>
#include <cstring>
//#define debug//输出调试信息

//*************************************模块自身信息*******************************************
String ModleName = "RGB Shower";
String APssid = "";
String APpassword = "";
//*******************************************WIFI配置*******************************************
struct WIFI_t
{
	String ssid, passwd;//名称，密码
	IPAddress IP;//IP地址
	IPAddress gateway;//网关
	IPAddress subnet;//子网掩码
};
WIFI_t ModuleWifi_1 = { "Sethome's RGB shower.","",IPAddress(192,168,1,1),IPAddress(192,168,1,1),IPAddress(255,255,0,0) };
WIFI_t ModuleWifi_2 = { "Sethome's RGB shower.","",IPAddress(192,168,1,2),IPAddress(192,168,1,1),IPAddress(255,255,0,0) };
WIFI_t ModuleWifi_3 = { "Sethome's RGB shower.","",IPAddress(192,168,1,3),IPAddress(192,168,1,1),IPAddress(255,255,0,0) };
//(esp8266链接上限是4，所以最大模块数为3,1为主机)

void WIFI_conf_init()//wifi基础配置初始化
{
	WiFi.hostname(ModleName);

	WiFi.mode(WIFI_AP_STA);//启动发射与接收模式

	WIFI_init_AP(ModuleWifi_1);
}
void WIFI_init_AP(WIFI_t wifi_info)//初始化为AP模式
{
	//设置网络信息
	WiFi.softAPConfig(wifi_info.IP, wifi_info.gateway, wifi_info.subnet);//自己的地址，网关地址（AP模式下通常与自己地址相同），子网掩码
	WiFi.softAP(wifi_info.ssid, wifi_info.passwd, 3, 0, 4);//自己的地址，网关地址（AP模式下通常与自己地址相同），子网掩码

#ifdef debug
	Serial.print("AP opened,IP:"); Serial.println(WiFi.softAPIP());
#endif
}
void WIFI_connectAP(WIFI_t wifi_info)
{
	WiFi.begin(wifi_info.ssid, wifi_info.passwd);
	WiFi.config(wifi_info.IP, wifi_info.gateway, wifi_info.subnet, (8, 8, 8, 8), (8, 8, 4, 4));//静态配置

#ifdef debug
	Serial.print("STA opened,IP:"); Serial.println(WiFi.softAPIP());
#endif
}

//*******************************************LED灯光配置*******************************************
#define BACK_LED_NUM  8
#define LEFT_LED_NUM  8
#define FRONT_LED_NUM 8
#define RIGHT_LED_NUM 8
#define TOP_LED_NUM   64 //灯光配置 先后再左，然后前，接着右，最后上（即后左前右上排列LED编号在LED库中）
#define LED_PIN D1//LED引脚
const int numLED = (BACK_LED_NUM + LEFT_LED_NUM + FRONT_LED_NUM + RIGHT_LED_NUM + TOP_LED_NUM);
CRGBArray <numLED>LED;

#define BACK_SIDE  0
#define LEFT_SIDE  1
#define FRONT_SIDE 2
#define RIGHT_SIDE 3
#define TOP_SIDE   4 //区域及编号

//色域转换函数
#define THREE_MAX(a,b,c) (a>b?(a>c?a:c):(b>c?b:c))//输出三个数中最大数
#define THREE_MIN(a,b,c) (a>b?(b>c?c:b):(a>c?c:a))//输出三个数中最小数
void RGBtoHSV(unsigned char r, unsigned char g, unsigned char b, int *h, int *s, int *v)//HSV色域到RGB色域
{
	int imax,imin,diff;
	imax = THREE_MAX(r,g,b);
	imin = THREE_MIN(r,g,b);
	diff = imax - imin;
	*v = imax;

	if(imax == 0)	
		*s = 0;
	else	
		*s = diff;
 
	if(diff != 0)
	{
		if(r == imax)
			*h = 60 * (g - b) / diff;
		else if(g == imax)
			*h = 60 * (b - r) / diff + 120;
		else
			*h = 60 * (r - g) / diff + 240;
 
		if(*h < 0)
			*h = *h + 360;
	}
	else
		*h = -1;
}
void HSVtoRGB(unsigned char *r, unsigned char *g, unsigned char *b, int h, int s, int v)//HSV色域到RGB色域
{
	int i;

	float RGB_min, RGB_max;
	RGB_max = v * 2.55f;
	RGB_min = RGB_max * (100 - s) / 100.0f;

	i = h / 60;
	int difs = h % 60;

	float RGB_Adj = (RGB_max - RGB_min)*difs / 60.0f;

	switch (i)
	{
	case 0:
		*r = RGB_max; *g = RGB_min + RGB_Adj; *b = RGB_min; return;
	case 1:
		*r = RGB_max - RGB_Adj; *g = RGB_max; *b = RGB_min; return;
	case 2:
		*r = RGB_min; *g = RGB_max; *b = RGB_min + RGB_Adj; return;
		break;
	case 3:
		*r = RGB_min; *g = RGB_max - RGB_Adj; *b = RGB_max; return;
	case 4:
		*r = RGB_min + RGB_Adj; *g = RGB_min; *b = RGB_max; return;
	default:
		*r = RGB_max; *g = RGB_min; *b = RGB_max - RGB_Adj; return;
	}
}

class LED_baseConf
{
	private:
		unsigned char side;//区域编号
		unsigned int sideID;//LED在区域中的编号
		
		unsigned char R, G, B;//实际的LED颜色的
		//int h,s,v;//hsv色域的值
	public:
		LED_baseConf()//对象创建时的初始化函数
		{
			R = G = B = 0;
			side = sideID = -1;
		}
		void init_IDconf(unsigned char setSide,unsigned int setSideID)//初始化 ID值
		{
			side = setSide; sideID = setSideID;
		}
		void setColor(unsigned char red,unsigned char green,unsigned char blue)//设定颜色
		{
			R = red; G = green;	B = blue;
		}

		//外部读取数据函数
		unsigned char getSide()
		{
			return side;
		}
		unsigned int getSideID()
		{
			return sideID;
		}
		unsigned char getR()
		{
			return R;
		}
		unsigned char getG()
		{	
			return G;
		}
		unsigned char getB()
		{	
			return B;
		}
};
class LED_colorConf: public LED_baseConf
{
	public:
		LED_colorConf()//对象初始化函数
		{
			setR = setG = setB;
			animaSign = false;
		}
		typedef	std::function<void()> colorAnimaFuntion;
		
		colorAnimaFuntion colorAnima;//颜色动画函数指针
		
		void setColorConf(colorAnimaFuntion setFuntion,unsigned char R,unsigned char G,unsigned char B)//设置LED色彩动画及其参数
		{
			colorAnima = setFuntion;
			animaSign = false;
			setR = R; setG = G; setB = B;
		}
		
		void colorUpdata()//外部调用，每次LED色彩更新调用
		{
			colorAnima();
		}
		
		//动画函数列表
		void alwaysON();//常亮
		void breath();//呼吸灯效
		void colorFlow();//全彩色
		void rainbow();//彩虹色
	private:
		unsigned char setR, setG, setB;//设定的LED颜色
		bool animaSign;//动画函数判断标志 不同函数可能有不同作用
};
void LED_colorConf::alwaysON()//常亮
{
	LED_baseConf::setColor(setR,setG,setB);
}
void LED_colorConf::breath()//呼吸灯效
{
	#define PI 3.1415926
	static int h,s,v;//使用hsv色域来处理
	static int start_v;//开始时的
	static float degree = 0.0;//sin函数，平滑处理函数 范围0-90

	if(LED_colorConf::animaSign == false)//是否为第一次调用
	{
		LED_colorConf::animaSign = true;
		RGBtoHSV(LED_baseConf::getR(),LED_baseConf::getG(),LED_baseConf::getB(),&h,&s,&v);
	}
	
	v = sin((degree / 180.0) * PI);
	
	unsigned char r,g,b;
	HSVtoRGB(&r,&g,&b,h,s,v);

	LED_baseConf::setColor(r,g,b);
}
class LED_animaConf : public LED_colorConf
{
	public:

	private:
		unsigned head_ID,tail_ID;//颜色函数的链表头尾ID
};
LED_animaConf LED_set[numLED];//新建LED控制对象

Ticker LED_Ticker;
#define TickerAnimationSpeed 0.02 //定义定时器，

void LED_init()//初始化LED
{
	FastLED.addLeds<WS2812B, LED_PIN, GRB>(LED, numLED);
	FastLED.setBrightness(255);//设定LED亮度及参数

	for(int i = 0;i < 30;i++)
	{
		LED_set[i].setColorConf(std::bind(&LED_animaConf::alwaysON,&LED_set[i]),255,255,255);
	} 
	LED_Ticker.attach(TickerAnimationSpeed, LED_change);//设定定时器

	//初始化LED ID数据
	for (int i = 0; i < BACK_LED_NUM; i++)
		LED_set[i].init_IDconf(BACK_LED_NUM,i);

	for (int i = 0; i < LEFT_LED_NUM; i++)
		LED_set[i + BACK_LED_NUM].init_IDconf(LEFT_SIDE,i);

	for (int i = 0; i < FRONT_LED_NUM; i++)
		LED_set[i + BACK_LED_NUM + LEFT_LED_NUM].init_IDconf(FRONT_SIDE,i);

	for (int i = 0; i < RIGHT_LED_NUM; i++)
		LED_set[i + BACK_LED_NUM + LEFT_LED_NUM + FRONT_LED_NUM].init_IDconf(RIGHT_SIDE,i);

	for (int i = 0; i < TOP_LED_NUM; i++)
		LED_set[i + BACK_LED_NUM + LEFT_LED_NUM + FRONT_LED_NUM + RIGHT_LED_NUM].init_IDconf(TOP_SIDE,i);

#ifdef debug
	Serial.print("led inited.num:"); Serial.println(numLED);
#endif
}
void LED_change()//根据动画函数改变LED颜色
{
	for (int i = 0; i < numLED; i++)
	{
		LED_set[i].colorUpdata();//更新颜色
		LED[i] = CRGB(LED_set[i].getR(),LED_set[i].getG(),LED_set[i].getB());
	}
	FastLED.show();
}
//*******************************************web服务器代码*******************************************
ESP8266WebServer server(80);//80端口
//控制面板界面
String htmlControlPanel =
"<!DOCTYPE html>"
"<html>"
"<head>"
"    <style type=\"text/css\">"
"        h {"
"            font-family: arial;"
"            font-size: 30px"
"        }"
"        p {"
"            font-family: arial;"
"            font-size: 15px"
"        }"
"    </style>"
"    <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />"
"    <title>RGB display case</title>"
"</head>"
"<body>"
"    <h style=\"background-color:rgba(0,255,255,0.5)\">RGB display case web control</h>"
"    <p>"
"        project site:"
"        <a href=\"https://github.com/sethome2/The-RGB-display-case\">GITHUB</a>"
"    </p>"
"    <hr>"
"    <h>WIFI setting</h>"
"    <from action=\"/changWIFIConf\" method= \"POST\">"
"        <p>"
"            WIFI ssid"
"            <input type=\"text\" name = \"S\">"
"        </p>"
"        <p>"
"            WIFI password"
"            <input type=\"text\" name=\"P\">"
"        </p>"
"        <input type=\"submit\" value=\"change\">"
"    </from>"
"    <hr>"
"    <h>animation setting</h>"
"    <form action=\"/setColorAndAnima\" method= \"POST\">"
"        <p>"
"            back side<input type=\"color\" name=\"B\">"
"            <select name=\"A\">"
"                <option value=\"1\" selected>alwaysOn</option>"
"                <option value=\"2\">Breath</option>"
"                <option value=\"3\">AllColorChange</option>"
"                <option value=\"4\">runningLigth</option>"
"            </select>"
"        </p>"
"        <p>"
"            left side<input type=\"color\" name=\"L\">"
"            <select name=\"A\">"
"                <option value=\"1\" selected>alwaysOn</option>"
"                <option value=\"2\">Breath</option>"
"                <option value=\"3\">AllColorChange</option>"
"                <option value=\"4\">runningLigth</option>"
"            </select>"
"        </p>"
"        <p>"
"            front side<input type=\"color\" name=\"F\">"
"            <select name=\"A\">"
"                <option value=\"1\" selected>alwaysOn</option>"
"                <option value=\"2\">Breath</option>"
"                <option value=\"3\">AllColorChange</option>"
"                <option value=\"4\">runningLigth</option>"
"            </select>"
"        </p>"
"        <p>"
"            right side<input type=\"color\" name=\"R\">"
"            <select name=\"A\">"
"                <option value=\"1\" selected>alwaysOn</option>"
"                <option value=\"2\">Breath</option>"
"                <option value=\"3\">AllColorChange</option>"
"                <option value=\"4\">runningLigth</option>"
"            </select>"
"        </p>"
"        <p>"
"            top side<input type=\"color\" name=\"T\">"
"            <select name=\"A\">"
"                <option value=\"1\" selected>alwaysOn</option>"
"                <option value=\"2\">Breath</option>"
"                <option value=\"3\">AllColorChange</option>"
"                <option value=\"4\">runningLigth</option>"
"            </select>"
"        </p>"
"            <input type=\"submit\" value=\"change\">"
"    </form>"
"    <hr>"
"    <h>about</h>"
"    <p>NA</p>"
"</body>"
"</html>";

//OTA页面
String htmlWebOTA = 
"<form method=\'POST\' action=\'/update\' enctype=\'multipart/form-data\'>"
"	<input type=\'file\' name=\'update\'>"
"	<input type=\'submit\' value=\'Update\'>"
"</form>";
String html404 = 
"<!DOCTYPE html>" 
"<html>" 
"<head>" 
"    <meta charset=\"utf-8\">" 
"    <title>RGB????/RGB display case</title>" 
"</head>" 
"<body>" 
"    <h1>RGB display case web control</h1>" 
"    <p>project site</p>" 
"    <a href=\"https://github.com/sethome2/The-RGB-display-case\">GITHUB</a>" 
"    <p>404,The site was ate by author.</p>" 
"</body>" 
"</html>";

void webControlPanel()//控制面板被访问处理函数
{
	server.send(200, "text/html", htmlControlPanel);

#ifdef debug
	Serial.println("An user accessed webControlPanel.");
#endif
}
void LEDpanelChange()//修改某一参数
{
	if (server.method() == HTTP_POST)//请求方式为post
	{
		String change_name,changeValue;
		for (uint8_t i = 0; i < 5; i++)
		{

		}
		server.sendHeader("Location", "/");//回到根目录的控制面板
		server.send(303);//3030跳转代码
	}
	else
		server.send(405, "text/plain", "Error http way.");

#ifdef debug
	Serial.print(server.method());
	Serial.println("An user change LED by web panel.");
#endif
}

void webOTA()//OTA处理函数
{
	server.send(200, "text/html", htmlWebOTA);

#ifdef debug
	Serial.println("An user accessed webOTA.");
#endif
}
void handleNotFound()//404页面处理函数
{
	server.send(404, "text/html", html404);

#ifdef debug
	Serial.println("An user accessed unknow handle,404.");
#endif
}
void server_init()
{
	server.on("/", HTTP_GET, webControlPanel);
	server.on("/setColorAndAnima", HTTP_POST, LEDpanelChange);
	server.on("/OTA", HTTP_GET, webOTA);
	server.onNotFound(handleNotFound);//未找到页面处理

	//在线更新代码
	server.on("/update", HTTP_POST, []() 
	{
		server.sendHeader("Connection", "close");
		server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
		ESP.restart();
	});

	server.begin();
	MDNS.begin(ModleName);
	MDNS.addService("http", "tcp", 80);//启动本地DNS配置

#ifdef debug
	Serial.println("web server inited.");
#endif
}
void server_handle_client_data()
{
	server.handleClient();//处理来自WIFI客户端的请求
}

//*******************************************程序主体*******************************************
void setup()
{
	delay(1000);
	Serial.begin(1000000);
	Serial.println("");//清空系统启动信息

	WIFI_conf_init();//WiFi初始化
	LED_init();//LED初始化
	server_init();//网页服务器初始化

	pinMode(LED_BUILTIN, OUTPUT);//初始化板载LED
	digitalWrite(LED_BUILTIN, LOW);//关闭状态

#ifdef debug
	Serial.print("All inited.");
#endif
}
void loop()
{
	server_handle_client_data();//处理服务器数据
}
//end of file
