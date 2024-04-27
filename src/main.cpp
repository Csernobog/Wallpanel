#include "Arduino.h"
// Roo_Display
// -> https://github.com/dejwk/roo_display
#include "roo_display.h"
#include "roo_display/core/offscreen.h"
#include "roo_display/internal/raw_streamable_overlay.h"
#include "roo_display/ui/text_label.h"
#include "roo_display/shape/basic.h"
#include "roo_display/shape/smooth.h"
#include "roo_fonts/NotoSans_Bold/15.h"
#include "roo_fonts/NotoSans_Bold/27.h"
#include "roo_fonts/NotoSans_Regular/15.h"
#include "roo_display/image/jpeg/jpeg.h"
#include "roo_display/shape/basic.h"
#include "roo_display/driver/ili9341.h"
#include "roo_display/driver/touch_xpt2046.h"
#include "roo_display/backlit/esp32_ledc.h"
#include "roo_display/image/image.h"
//Arduino - HA integration
// -> https://github.com/dawidchyrzynski/arduino-home-assistant
#include <ArduinoHA.h>
#include "FS.h"
#include "SD.h"
#include <WiFi.h>
#include <time.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>
#include "ESP32TimerInterrupt.h"

// ICONs
#include "bitmaps.h"

using namespace roo_display;
static const Color kowalsky_color[] PROGMEM = {
  Color(0xffacacac),
  Color(0xff0b0b0b),
  Color(0xff000000),
  Color(0xffcbccd2),
  Color(0xff8195c8),
  Color(0xff5e70b4),
  Color(0xff5e6d9b),
  Color(0xff5467a6),
  Color(0xff4564ae),
  Color(0xff4b5b97),
  Color(0xff47558c),
  Color(0xff344b85),
  Color(0xff31406d),
  Color(0xff2b3c65),
  Color(0xff263869),
  Color(0xff23345f),
  Color(0xff1c2f5d),
  Color(0xff141e36),
  Color(0xff000827),
  Color(0xff020817),
  Color(0xff000112),
  Color(0xff010007),
  Color(0xffe1f1f3),
  Color(0xffdbebf1),
  Color(0xffd6e7eb),
  Color(0xffd3e3ea),
  Color(0xffd3e1e3),
  Color(0xffcfe0e4),
  Color(0xffd0dde3),
  Color(0xffcadae2),
  Color(0xffcad9db),
  Color(0xffc4d3ec),
  Color(0xffc5d4da),
  Color(0xffbed0d6),
  Color(0xffbfccd1),
  Color(0xffbbcad2),
  Color(0xffb5c6d4),
  Color(0xffc0c6cb),
  Color(0xffb8c5c8),
  Color(0xffb3c2cb),
  Color(0xffbec0c0),
  Color(0xffb2bdc3),
  Color(0xffacb9c2),
  Color(0xff9cb6cc),
  Color(0xffaab5b9),
  Color(0xffa3b3ba),
  Color(0xffa9b2b4),
  Color(0xff6eacdc),
  Color(0xffa4b1b3),
  Color(0xffa3adb1),
  Color(0xff94a8c2),
  Color(0xffa2a9ab),
  Color(0xff9da9ac),
  Color(0xff9aa5aa),
  Color(0xff96a0a2),
  Color(0xff8e9caf),
  Color(0xff5797cf),
  Color(0xff939ca1),
  Color(0xff959a9b),
  Color(0xff7e95aa),
  Color(0xff8b969c),
  Color(0xff818e9e),
  Color(0xff8a9093),
  Color(0xff4684c7),
  Color(0xff818a91),
  Color(0xff7e868d),
  Color(0xff647fa2),
  Color(0xff6c7c90),
  Color(0xff797e80),
  Color(0xff4576ac),
  Color(0xff3f71be),
  Color(0xff2f6dc9),
  Color(0xff74787a),
  Color(0xff50719a),
  Color(0xff396dad),
  Color(0xff617087),
  Color(0xff6c7073),
  Color(0xff3166a0),
  Color(0xff4c6393),
  Color(0xff386394),
  Color(0xff536584),
  Color(0xff63696e),
  Color(0xff28619b),
  Color(0xff355aa3),
  Color(0xff476085),
  Color(0xff5f6366),
  Color(0xff275899),
  Color(0xff345794),
  Color(0xff4e5c70),
  Color(0xff44587c),
  Color(0xff345685),
  Color(0xff195096),
  Color(0xff27518a),
  Color(0xff264b95),
  Color(0xff2e507e),
  Color(0xff384d7a),
  Color(0xff404f6b),
  Color(0xff22497f),
  Color(0xff344a74),
  Color(0xff454f56),
  Color(0xff20428a),
  Color(0xff374969),
  Color(0xff214775),
  Color(0xff21437e),
  Color(0xff2c4371),
  Color(0xff314263),
  Color(0xff334358),
  Color(0xff223c75),
  Color(0xff3b4144),
  Color(0xff243a63),
  Color(0xff2b3b58),
  Color(0xff2e3b45),
  Color(0xff213552),
  Color(0xff34393b),
  Color(0xff293648),
  Color(0xff1d304a),
  Color(0xff263044),
  Color(0xff182c53),
  Color(0xff2d3233),
  Color(0xff1e2c3e),
  Color(0xff132748),
  Color(0xff26292c),
  Color(0xff14243b),
  Color(0xff192430),
  Color(0xff181c24),
  Color(0xff061538),
  Color(0xff0b1425),
  Color(0xff0a1017),
  Color(0xff03070d),
  Color(0xffe7f4f3),
  Color(0xffe1ecea),
  Color(0xffdaebeb),
  Color(0xffdbe8e4),
  Color(0xffd9e4e3),
  Color(0xffd2e0dc),
  Color(0xffd0dcdb),
  Color(0xffd1d4d4),
  Color(0xffcbd1cf),
  Color(0xffc4d0d0),
  Color(0xffbdd1cb),
  Color(0xffc2ccca),
  Color(0xffb5cdc4),
  Color(0xffbdc9ca),
  Color(0xffb6c9cb),
  Color(0xffbbc8c5),
  Color(0xffb9c4c3),
  Color(0xffb5c1c2),
  Color(0xffa8c2c0),
  Color(0xffb3bfbe),
  Color(0xffb1bbbb),
  Color(0xffadb8b9),
  Color(0xff99a3a4),
  Color(0xff929494),
  Color(0xff808282),
  Color(0xff595f5f),
  Color(0xffeff9f4),
  Color(0xffcdd9d3),
  Color(0xffc4c8c4),
  Color(0xff525352),
  Color(0xff424442),
  Color(0xff1f201f),
  Color(0xff131a16),
  Color(0xff050706),
  Color(0xffdddfdb),
  Color(0xff848882),
  Color(0xff484947),
  Color(0xff363931),
  Color(0xff2d302b),
  Color(0xfffcfcf0),
  Color(0xffedebe1),
  Color(0xffcac9c5),
  Color(0xffbec0b9),
  Color(0xffb9b8b4),
  Color(0xffb4b4b2),
  Color(0xffb2b1ad),
  Color(0xff8c8c8b),
  Color(0xff73716a),
  Color(0xff6b6b69),
  Color(0xff656259),
  Color(0xff595958),
  Color(0xff575449),
  Color(0xff33322c),
  Color(0xff2a2b23),
  Color(0xff272823),
  Color(0xff22231c),
  Color(0xff1d1f18),
  Color(0xff191813),
  Color(0xff040403),
  Color(0xffece5dd),
  Color(0xffeae1d8),
  Color(0xffdfdbd3),
  Color(0xffe1d4cd),
  Color(0xffd7d1c9),
  Color(0xffd2ccc7),
  Color(0xffd0c6c0),
  Color(0xffc7c5c4),
  Color(0xfff5cf88),
  Color(0xffccc3bb),
  Color(0xffc4c2c1),
  Color(0xffc3c1be),
  Color(0xffc0beba),
  Color(0xffbcbab8),
  Color(0xffc5b9b2),
  Color(0xffe9c079),
  Color(0xffbfb1ab),
  Color(0xffcfb692),
  Color(0xffb9ada6),
  Color(0xffb3aaa2),
  Color(0xffaba7a3),
  Color(0xffb2a69b),
  Color(0xffa4a19e),
  Color(0xffaaa197),
  Color(0xffa59d98),
  Color(0xffa99c92),
  Color(0xffc4a26c),
  Color(0xffa2998f),
  Color(0xff9c9690),
  Color(0xff9a938b),
  Color(0xff978082),
  Color(0xff958e88),
  Color(0xff928b83),
  Color(0xff91887e),
  Color(0xff8b847d),
  Color(0xffb38f48),
  Color(0xff837f79),
  Color(0xff7d7b77),
  Color(0xff787673),
  Color(0xffa6803f),
  Color(0xff8f774d),
  Color(0xff9a6f28),
  Color(0xff86672e),
  Color(0xff815b1f),
  Color(0xff4f4e4c),
  Color(0xff69522f),
  Color(0xff644b1c),
  Color(0xff403e3d),
  Color(0xff483e2a),
  Color(0xff3b3a39),
  Color(0xff64410a),
  Color(0xff4c3b1c),
  Color(0xff333231),
  Color(0xff363024),
  Color(0xff3f3113),
  Color(0xff2c2a29),
  Color(0xff1f1d1c),
  Color(0xff1b1a19),
  Color(0xff131211),
  Color(0xffcac8c8),
  Color(0xffc8c6c6),
  Color(0xff4a4444),
  Color(0xff373535),
  Color(0xff302c2c),
  Color(0xff272424),
  Color(0xff242222),
  Color(0xffb7b5b6),
  Color(0xff171617),
};

//--------------------------------------------------------------------------------------------------------------------------------
// Secret vars 
//--------------------------------------------------------------------------------------------------------------------------------
#define WIFI_SSID "Balkoland_Guest"             // Your Wifi SSID
#define WIFI_PASSWORD "QWYMKZUW"                // Your Wifi password
#define BROKER_ADDR IPAddress(192, 168, 0, 60)  // = Your HA server IP  (xxx, xxx, xxx, xxx) format. NOT xxx.xxx.xxx.xxx!!!!
#define HA_PORT 8123                            // = Your HA server port
#define BROKER_USERNAME "mqtt"                  // = User for HA MQTT MOSQUITO Server
#define BROKER_PASSWORD "mqtt"                  // = password HA MQTT user
#define TOKEN "Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJiZGYyYWY5NTBjYzM0MTAwOWRiNmUwOGYxODg3ZTNkMiIsImlhdCI6MTcwOTU5MDk4NCwiZXhwIjoyMDI0OTUwOTg0fQ.AwD74FssPwMCsJbx37kTUigaIozwRGj7JWCPvaw60Vk"
//--------------------------------------------------------------------------------------------------------------------------------
// Timing setting vars
//--------------------------------------------------------------------------------------------------------------------------------
#define PUBLISH_INTERVAL 10000                  // MQTT how often image should be published to HA (milliseconds)
#define TIMER0_INTERVAL_MS 300000               // 5 min check (METEO DATA)
#define TIMER1_INTERVAL_MS 60000                // 1 min check (HA API, WIFI, ...)
#define KOWALSKI_TIME 1000                      // Kowalsky thinking delay
#define TIME_ZONE "CET-1CEST,M3.5.0,M10.5.0/3"  // Find here ->> https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv
//--------------------------------------------------------------------------------------------------------------------------------
// WallPanel - HA settings vars
//--------------------------------------------------------------------------------------------------------------------------------
#define ENTITY1 "switch.sonoff_10017ee877_1"           // HA entity name -  button1 state on/off
#define ENTITY1_NAME "Nappali"                         // Button1_TEXT = HA Template switch1 entity name
#define ENTITY1_ICON "mdi:lightbulb"                   // HA ICON for Button1 temlate switch1 entity
#define ENTITY2 "switch.kazan_socket_1"                // HA entity name -  button2 state on/off
#define ENTITY2_NAME "Melegviz"                        // Button2_TEXT = HA Template switch2 entity name
#define ENTITY2_ICON "mdi:waves"                       // HA ICON for Button2 temlate switch2 entity
#define SUN "/api/states/sun.sun"                      // HA Sun entity
#define WEATHER_API_CALL "/api/states/weather.otthon"  //HA Weather entity
//--------------------------------------------------------------------------------------------------------------------------------
// WallPanel - Colors
//--------------------------------------------------------------------------------------------------------------------------------
#define ON_COLOR Yellow  // Button ICON on Color
#define OFF_COLOR Black  // Button ICON off Color
#define BUTTON_TEXT_COLOR Black
#define BUTTON_ICON_COLOR Black
#define WEATHER_TEXT_COLOR Black
#define WEATHER_ICON_COLOR Black
#define BACKGROUND_COLOR Tan  // Button and Weather Data background color
//--------------------------------------------------------------------------------------------------------------------------------
// Hardver setting ESP32S3 + DISPLAY ILI9341 240x320 SPI SCREEN with SD reader and xpt2046 capacitive touch
//--------------------------------------------------------------------------------------------------------------------------------
static constexpr int kCsPin = 6;
static constexpr int kDcPin = 2;
static constexpr int kRstPin = 5;
static constexpr int kBlPin = 16;
static constexpr int kTouchCsPin = 35;
// SD SETTING use SPI2 ESP32S3
#define SD_CS_PIN 19  // or 5
#define SD_SCLK_PIN 1
#define SD_MOSI_PIN 20
#define SD_MISO_PIN 21
LedcBacklit backlit(kBlPin, /* ledc channel */ 0);  // Display BACKLIGHT
//--------------------------------------------------------------------------------------------------------------------------------
// Roo Display Class INIT
//--------------------------------------------------------------------------------------------------------------------------------
Ili9341spi<kCsPin, kDcPin, kRstPin> device;
TouchXpt2046<kTouchCsPin> touch_device;
Display display(device, touch_device,
                TouchCalibration(269, 249, 3829, 3684,
                                 Orientation::LeftDown()));
JpegDecoder decoder;
uint8_t background_buf[320 * 240 * 2];  // Offscreen buffer mem alloc
Offscreen<Rgb565> background(240, 320, background_buf);
//--------------------------------------------------------------------------------------------------------------------------------
// Display areas
//--------------------------------------------------------------------------------------------------------------------------------
Box gomb[] = { { 15, 195, 95, 275 }, { 145, 195, 225, 275 } };  //Buttons
Box btn_head(0, 0, 319, 19);                                    //Header (Time + HA connect +Wifi RSSI icon)
Box wetHead(15, 50, 225, 150);                                  //Weather box
//--------------------------------------------------------------------------------------------------------------------------------
// Weather Data Struct to decode weather data JSON
//--------------------------------------------------------------------------------------------------------------------------------
String weather_icon = "";
double weather_temp = 0;
String weather_temp_unit = "";
double weather_humidity = 0;
double weather_pressure = 0;
String weather_pressure_unit = "";
double weather_wind_dir = 0;
double weather_wind_speed = 0;
String weather_wind_speed_unit = "";
//--------------------------------------------------------------------------------------------------------------------------------
// STATE SEMAPHORES - help to prevent program collapse:)
//--------------------------------------------------------------------------------------------------------------------------------
bool wifiState = false;  // WIFI state true= WIFI is connected
bool sdState = false;    // SD reader state true=SD runing, card inserted and readable
bool timeState = false;
bool apiState = false;      // HA Server state = true= API running Response Code=200
bool weatherState = false;  // Weather entity awaiable
bool dayOrnight = false;    // Day = true Night = false
volatile int rScreen = 0;   // METEO redraw 5 min interrupt semaphore
volatile int cDevice = 0;   // HA,WIFI awiable check 1 min interrupt semaphore
bool was_touched = false;   // TOUCH detection
//--------------------------------------------------------------------------------------------------------------------------------
// GLOBALS
//--------------------------------------------------------------------------------------------------------------------------------
int statusCode = 0;
String response = "";
// Global Variables
String hatterlist = "";
int atlatszosag = 0x50;
int fileindex = 11;
int16_t x = -1;
int16_t y = -1;
int melyik_gomb = -1;
int regi_gomb = -1;

String filelist[20];  // Max 20 item
File dir;
int nFile = 0;

WiFiClient client;
HADevice hadevice;
HAMqtt mqtt(client, hadevice);
HttpClient httpclient = HttpClient(client, BROKER_ADDR, HA_PORT);
SPIClass sd_spi(HSPI);
ESP32Timer ITimer0(0);
ESP32Timer ITimer1(1);

// HA entity INIT
HANumber backl("Kijelzo_bckl");
HANumber transp("Kijelzo_trans");
HASwitch entity1(ENTITY1_NAME);
HASwitch entity2(ENTITY2_NAME);
HASelect hatter("Hatter");

int timeZone = 1;

void drawScreen(String backgroundImage);

// Timer0 Interrupt 5min
bool IRAM_ATTR TimerHandler0(void* timerNo) {
  rScreen = 1;
  return true;
}
// Timer1 Interrupt 1min
bool IRAM_ATTR TimerHandler1(void* timerNo) {
  cDevice = 1;
  return true;
}
// Switch entity omCommand
void onSwitchCommand(bool state, HASwitch* sender) {
  DrawingContext dc(display);
  Color colors[] PROGMEM = { color::Transparent, (state ? color::ON_COLOR : color::OFF_COLOR) };
  Palette palette = Palette::ReadOnly(colors, 2);
  if (sender == &entity1) {
    Serial.print("ENTITY1 STATE: ");
    Serial.println(state);
    dc.draw(ProgMemRaster<Indexed1>(48, 48, button_icon1, &palette), gomb[0].xMin() + 16, gomb[0].yMin() + 5);
    sender->setState(state);  // report state back to the Home Assistant
  }
  if (sender == &entity2) {
    Serial.print("ENTITY2 STATE: ");
    Serial.println(state);
    dc.draw(ProgMemRaster<Indexed1>(48, 48, button_icon2, &palette), gomb[1].xMin() + 16, gomb[1].yMin() + 5);
    sender->setState(state);  // report state back to the Home Assistant
  }
}
// Number entity omCommand
void onNumberCommand(HANumeric number, HANumber* sender) {
  if (sender == &backl) {
    if (!number.isSet()) {
      // the reset command was send by Home Assistant
    } else {
      // you can do whatever you want with the number as follows:
      int8_t numberInt8 = number.toInt8();
      int16_t numberInt16 = number.toInt16();
      int32_t numberInt32 = number.toInt32();
      uint8_t numberUInt8 = number.toUInt8();
      uint16_t numberUInt16 = number.toUInt16();
      uint32_t numberUInt32 = number.toUInt32();
      float numberFloat = number.toFloat();
    }
    analogWrite(kBlPin, number.toInt16());
    sender->setState(number);  // report the selected option back to the HA panel
  } else {
    if (sender == &transp) {
      if (!number.isSet()) {
        // the reset command was send by Home Assistant
      } else {
        // you can do whatever you want with the number as follows:
        int8_t numberInt8 = number.toInt8();
        int16_t numberInt16 = number.toInt16();
        int32_t numberInt32 = number.toInt32();
        uint8_t numberUInt8 = number.toUInt8();
        uint16_t numberUInt16 = number.toUInt16();
        uint32_t numberUInt32 = number.toUInt32();
        float numberFloat = number.toFloat();
      }
      sender->setState(number);
      atlatszosag = number.toInt8();
      drawScreen(filelist[fileindex]);
      DrawingContext dc(display);
      dc.draw(background, kCenter | kMiddle);  // Draw background to screen
    }
  }
}
// Select entity omCommand
void onSelectCommand(int8_t index, HASelect* sender) {
  Serial.print("Selected: ");
  Serial.println(index);
  Serial.println(filelist[index]);

  sender->setState(index);  // report the selected option back to the HA panel
  if (sdState) {
    fileindex = index;
    drawScreen(filelist[fileindex]);
    DrawingContext dc(display);
    dc.draw(background, kCenter | kMiddle);  // Draw background to screen
  }
}
// Display weather data
void drawWeather(DrawingContext& dc) {

  TextLabel label("", font_NotoSans_Regular_15(), color::Black);
  dc.draw(SmoothThickRoundRect(wetHead.xMin(), wetHead.yMin(), wetHead.xMax(), wetHead.yMax(),
                               6, 2, color::Gray, color::BACKGROUND_COLOR.withA(atlatszosag)));
  Alignment a = kLeft.shiftBy(5) | kTop.shiftBy(5);
  Tile tile(&label, wetHead, a, color::BACKGROUND_COLOR.withA(atlatszosag));
  dc.draw(tile);
  if (weatherState) {

    static Color colors[] PROGMEM = { color::Transparent, color::WEATHER_ICON_COLOR };
    static Palette palette = Palette::ReadOnly(colors, 2);
    Box(wetHead.xMin() + 15, wetHead.yMin() + 30, wetHead.xMin() + 15 + 48, wetHead.yMin() + 30 + 48);
    if (weather_icon == "lightning") {
      dc.draw(ProgMemRaster<Indexed1>(48, 48, thunderstorm, &palette), wetHead.xMin() + 15, wetHead.yMin() + 30);
      dc.draw(TextLabel("Zivatar", font_NotoSans_Bold_15(), color::WEATHER_TEXT_COLOR), wetHead.xMin() + 15, wetHead.yMin() + 90);
    }
    if (weather_icon == "fog") {
      dc.draw(ProgMemRaster<Indexed1>(48, 48, foggy, &palette), wetHead.xMin() + 15, wetHead.yMin() + 30);
      dc.draw(TextLabel("Ködös", font_NotoSans_Bold_15(), color::WEATHER_TEXT_COLOR), wetHead.xMin() + 15, wetHead.yMin() + 90);
    }
    if (weather_icon == "fog") {
      dc.draw(ProgMemRaster<Indexed1>(48, 48, foggy, &palette), wetHead.xMin() + 15, wetHead.yMin() + 30);
      dc.draw(TextLabel("Ködös", font_NotoSans_Bold_15(), color::WEATHER_TEXT_COLOR), wetHead.xMin() + 15, wetHead.yMin() + 90);
    }
    if (weather_icon == "cloudy") {
      dc.draw(ProgMemRaster<Indexed1>(48, 48, cloudy, &palette), wetHead.xMin() + 15, wetHead.yMin() + 30);
      dc.draw(TextLabel("Borult", font_NotoSans_Bold_15(), color::WEATHER_TEXT_COLOR), wetHead.xMin() + 15, wetHead.yMin() + 90);
    }
    if (weather_icon == "rainy") {
      dc.draw(ProgMemRaster<Indexed1>(48, 48, rainy, &palette), wetHead.xMin() + 15, wetHead.yMin() + 30);
      dc.draw(TextLabel("Esős", font_NotoSans_Bold_15(), color::WEATHER_TEXT_COLOR), wetHead.xMin() + 15, wetHead.yMin() + 90);
    }
    if (weather_icon == "partlycloudy") {
      if (dayOrnight == true) {
        dc.draw(ProgMemRaster<Indexed1>(48, 48, partly_cloudy_day, &palette), wetHead.xMin() + 15, wetHead.yMin() + 30);
      } else {
        dc.draw(ProgMemRaster<Indexed1>(48, 48, partly_cloudy_night, &palette), wetHead.xMin() + 15, wetHead.yMin() + 30);
      }
      dc.draw(TextLabel("Felhős", font_NotoSans_Bold_15(), color::WEATHER_TEXT_COLOR), wetHead.xMin() + 15, wetHead.yMin() + 90);
    }
    if (weather_icon == "sunny") {
      dc.draw(ProgMemRaster<Indexed1>(48, 48, sunny, &palette), wetHead.xMin() + 15, wetHead.yMin() + 30);
      dc.draw(TextLabel("Derült", font_NotoSans_Bold_15(), color::WEATHER_TEXT_COLOR), wetHead.xMin() + 15, wetHead.yMin() + 90);
    }
    if (weather_icon == "clear-night") {
      dc.draw(ProgMemRaster<Indexed1>(48, 48, clear_night, &palette), wetHead.xMin() + 15, wetHead.yMin() + 30);
      dc.draw(TextLabel("Derült", font_NotoSans_Bold_15(), color::WEATHER_TEXT_COLOR), wetHead.xMin() + 15, wetHead.yMin() + 90);
    }
    // Any other Weather state and icons

    char tempstr[10];
    char buffer[10];
    //Temperature
    dtostrf(weather_temp, 4, 1, tempstr);
    strcpy(buffer, tempstr);
    strcpy(buffer + strlen(tempstr), weather_temp_unit.c_str());
    dc.draw(TextLabel(buffer, font_NotoSans_Bold_27(), color::WEATHER_TEXT_COLOR), wetHead.xMin() + 5, wetHead.yMin() + 30);
    //Pressure
    dtostrf(weather_pressure, 6, 1, tempstr);
    strcpy(buffer, tempstr);
    strcpy(buffer + strlen(tempstr), weather_pressure_unit.c_str());
    dc.draw(TextLabel(buffer, font_NotoSans_Bold_15(), color::WEATHER_TEXT_COLOR), wetHead.xMin() + 120, wetHead.yMin() + 20);
    dc.draw(ProgMemRaster<Indexed1>(24, 24, pressure, &palette), wetHead.xMin() + 90, wetHead.yMin() + 5);
    //Humidity
    dtostrf(weather_humidity, 2, 0, tempstr);
    strcpy(buffer, tempstr);
    strcpy(buffer + strlen(tempstr), "%");
    dc.draw(TextLabel(buffer, font_NotoSans_Bold_15(), color::WEATHER_TEXT_COLOR), wetHead.xMin() + 120, wetHead.yMin() + 45);
    dc.draw(ProgMemRaster<Indexed1>(24, 24, humidity, &palette), wetHead.xMin() + 90, wetHead.yMin() + 30);
    //Wind Speed
    dtostrf(weather_wind_speed, 3, 1, tempstr);
    strcpy(buffer, tempstr);
    strcpy(buffer + strlen(tempstr), weather_wind_speed_unit.c_str());
    dc.draw(TextLabel(buffer, font_NotoSans_Bold_15(), color::WEATHER_TEXT_COLOR), wetHead.xMin() + 120, wetHead.yMin() + 70);
    dc.draw(ProgMemRaster<Indexed1>(24, 24, wind, &palette), wetHead.xMin() + 90, wetHead.yMin() + 55);
    //Wind direction

  } else {
    Serial.println("No weather data");
  }
}
// Get weather data from HA
void getWeather() {
  httpclient.beginRequest();
  httpclient.get(SUN);
  httpclient.sendHeader("Authorization", TOKEN);
  httpclient.sendHeader("Content-Type", "application/json");
  httpclient.endRequest();
  statusCode = httpclient.responseStatusCode();
  response = httpclient.responseBody();
  Serial.print("GET Status code: ");
  Serial.println(statusCode);
  Serial.print("GET Response: ");
  Serial.println(response);
  if (statusCode == 200) {
    JsonDocument doc;
    deserializeJson(doc, response.c_str());
    const char* w_icon = doc["state"];
    if (w_icon = "below_horizon") {
      dayOrnight = false;
    }
    if (w_icon = "above_horizon") {
      dayOrnight = true;
    }
    Serial.println(dayOrnight);
  }
  httpclient.beginRequest();
  httpclient.get(WEATHER_API_CALL);
  httpclient.sendHeader("Authorization", TOKEN);
  httpclient.sendHeader("Content-Type", "application/json");
  httpclient.endRequest();
  statusCode = httpclient.responseStatusCode();
  response = httpclient.responseBody();
  Serial.print("GET Status code: ");
  Serial.println(statusCode);
  Serial.print("GET Response: ");
  Serial.println(response);
  if (statusCode == 200) {
    // get SUCCED
    JsonDocument doc;
    deserializeJson(doc, response.c_str());
    const char* w_icon = doc["state"];
    const double w_temp = doc["attributes"]["temperature"];
    const char* w_temp_unit = doc["attributes"]["temperature_unit"];
    const double w_humidity = doc["attributes"]["humidity"];
    const double w_pressure = doc["attributes"]["pressure"];
    const char* w_pressure_unit = doc["attributes"]["pressure_unit"];
    const double w_wind_dir = doc["attributes"]["wind_bearing"];
    const double w_wind_speed = doc["attributes"]["wind_speed"];
    const char* w_wind_speed_unit = doc["attributes"]["wind_speed_unit"];
    weather_icon = w_icon;
    weather_temp = w_temp;
    weather_temp_unit = w_temp_unit;
    weather_pressure = w_pressure;
    weather_pressure_unit = w_pressure_unit;
    weather_humidity = w_humidity;
    weather_wind_dir = w_wind_dir;
    weather_wind_speed = w_wind_speed;
    weather_wind_speed_unit = w_wind_speed_unit;
    weatherState = true;
  } else {
    weatherState = false;
  }
}
// HA API Check
void checkHaApi() {
  httpclient.beginRequest();
  httpclient.get("/api/");
  httpclient.sendHeader("Authorization", TOKEN);
  httpclient.sendHeader("Content-Type", "application/json");
  httpclient.endRequest();
  // read the status code and body of the response
  statusCode = httpclient.responseStatusCode();
  response = httpclient.responseBody();
  Serial.print("GET Status code: ");
  Serial.println(statusCode);
  Serial.print("GET Response: ");
  Serial.println(response);
  if (statusCode == 200) {
    JsonDocument doc;
    deserializeJson(doc, response.c_str());
    const char* haAPIS = doc["message"];
    Serial.println(haAPIS);
    Serial.println(apiState);
    if (String(haAPIS) == "API running.") {
      apiState = 1;
    } else {
      apiState = 0;
    }
  } else {
    apiState = 0;
  }
}
// GET entityState from HA entity=HA entity name
bool getEntityStateFromApi(String entity) {
  Serial.println("getEntityStateFromAPI START");
  httpclient.beginRequest();
  httpclient.get("/api/states/" + entity);
  httpclient.sendHeader("Authorization", TOKEN);
  httpclient.sendHeader("Content-Type", "application/json");
  httpclient.endRequest();
  // read the status code and body of the response
  statusCode = httpclient.responseStatusCode();
  response = httpclient.responseBody();
  Serial.print("GET Status code: ");
  Serial.println(statusCode);
  Serial.print("GET Response: ");
  Serial.println(response);
  if (statusCode == 200) {
    JsonDocument doc;
    deserializeJson(doc, response.c_str());
    const char* sensor = doc["entity_id"];
    const char* state = doc["state"];
    Serial.println(sensor);
    Serial.println(state);
    if (String(state) == "on") {
      Serial.print(sensor);
      Serial.println(" HA Entity On");
      return true;
    } else if (String(state) == "off") {
      Serial.print(sensor);
      Serial.println(" HA Entity Off");
      return false;
    }
  } else {
    Serial.println("HA state unavaiable ... Set HA Entity Off");
    return false;
  }
  Serial.println("  getEntityStateFromAPI STOP");
}
// TOUCH check with Button
int checkbox(int t_x, int t_y) {
  for (int i = 0; i <= 1; i++) {
    if ((t_x >= gomb[i].xMin()) && (t_x <= gomb[i].xMax())) {
      if ((t_y >= gomb[i].yMin()) && (t_y <= gomb[i].yMax())) {
        return i;
      }
    }
  }
  return -1;
}
// ICON drawer
void drawIcon(DrawingContext& dc, const Pictogram& icon, int x, int y, Color color) {
  Pictogram my_icon = icon;
  my_icon.color_mode().setColor(color);
  dc.draw(Tile(&my_icon, my_icon.anchorExtents(), kNoAlign, color::Transparent), x, y);
}
// Draw screen in background
void drawScreen(String backgroundImage) {
  Serial.println("drawSreen START");
  DrawingContext dc(background);
  dc.draw(FilledRect(0, 0, 239, 319, color::Black), kCenter | kMiddle);
  if (sdState) {
    JpegFile background_jpg(decoder, SD, "/" + backgroundImage);
    dc.draw(background_jpg, kCenter | kTop);
  }
  dc.draw(SmoothThickRoundRect(btn_head.xMin(), btn_head.yMin(), btn_head.xMax(), btn_head.yMax(),
                               0, 1.5, color::Black, color::Black));

  TextLabel label1(entity1.getName(), font_NotoSans_Bold_15(), color::BUTTON_TEXT_COLOR);

  dc.draw(SmoothThickRoundRect(gomb[0].xMin() - 4, gomb[0].yMin() - 4, gomb[0].xMax() + 4, gomb[0].yMax() + 4,
                               6, 2, color::Gray, color::BACKGROUND_COLOR.withA(atlatszosag)));


  Alignment a1 = kCenter | kBottom.shiftBy(-5);
  Tile tile1(&label1, gomb[0], a1, color::BACKGROUND_COLOR.withA(atlatszosag));

  TextLabel label2(entity2.getName(), font_NotoSans_Bold_15(), color::BUTTON_TEXT_COLOR);
  dc.draw(SmoothThickRoundRect(gomb[1].xMin() - 4, gomb[1].yMin() - 4, gomb[1].xMax() + 4, gomb[1].yMax() + 4,
                               6, 2, color::Gray, color::BACKGROUND_COLOR.withA(atlatszosag)));
  Alignment a2 = kCenter | kBottom.shiftBy(-5);
  Tile tile2(&label2, gomb[1], a2, color::BACKGROUND_COLOR.withA(atlatszosag));

  dc.draw(tile1);
  dc.draw(tile2);
  Color colors1[] PROGMEM = { color::Transparent, (entity1.getCurrentState() ? color::ON_COLOR : color::OFF_COLOR) };
  Palette palette1 = Palette::ReadOnly(colors1, 2);
  dc.draw(ProgMemRaster<Indexed1>(48, 48, button_icon1, &palette1), gomb[0].xMin() + 16, gomb[0].yMin() + 5);

  Color colors2[] PROGMEM = { color::Transparent, (entity2.getCurrentState() ? color::ON_COLOR : color::OFF_COLOR) };
  Palette palette2 = Palette::ReadOnly(colors2, 2);
  dc.draw(ProgMemRaster<Indexed1>(48, 48, button_icon2, &palette2), gomb[1].xMin() + 16, gomb[1].yMin() + 5);

  drawWeather(dc);
  Serial.println("drawSreen END");
}
// Check file type = JPG
bool isFnJPG(String filename) {
  int8_t len = filename.length();
  bool result;
  if (filename.substring(len - 4) == ".jpg")

  // and anything else you want
  {
    result = true;
  } else {
    result = false;
  }
  return result;
}
// Read JPG file from SD CARD file_limit: max 20
void readDirectory(File dir, int numTabs) {
  int i = 0;
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) {
      // no more files
      break;
    }
    if (isFnJPG(String(entry.name()))) {
      filelist[i] = String(entry.name());
      hatterlist = hatterlist + String(entry.name()) + ";";
      i++;
    }
    entry.close();
  }
  Serial.print(i);
  Serial.println(" JPG File founded");
  if (i == 0) {
    sdState = false;  // SD runing but no JPG in SD CARD --> SD close No Background IMAGE
  }
  int8_t len = hatterlist.length();
  hatterlist = hatterlist.substring(0, len - 1);  // HA SELECT ENTITY DATA - SD CARD root DIR JPG files list
}
// Set TIME ZONE to NTP
void setTimezone(String timezone) {
  Serial.printf("  Setting Timezone to %s\n", timezone.c_str());
  setenv("TZ", timezone.c_str(), 1);  //  Now adjust the TZ.  Clock settings are adjusted to show the new local time
  tzset();
}
// TIME Setup
bool initTime(String timezone) {
  struct tm timeinfo;
  Serial.println("Setting up time");
  configTime(0, 0, "pool.ntp.org");  // First connect to NTP server, with 0 TZ offset
  if (!getLocalTime(&timeinfo)) {
    Serial.println("  Failed to obtain time");
    return 0;
  }
  Serial.println("  Got the time from NTP");
  // Now we can set the real timezone
  setTimezone(timezone);  // SET TIME ZONE
  return 1;
}
// Print display header (Date,Time, HA Status, WIFI RSSI)
void printHeader() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time 1");
    return;
  }
  char buffer[30];
  strftime(buffer, 80, "%F %H:%M:%S ", &timeinfo);

  DrawingContext dc(display);
  dc.setBackgroundColor(color::Black);
  dc.setFillMode(FILL_MODE_RECTANGLE);
  dc.draw(
    TextLabel(buffer, font_NotoSans_Regular_15(), color::White),
    3, 13);

  Color colors1[] PROGMEM = { color::Transparent, (apiState ? color::DodgerBlue : color::Red) };
  Palette palette1 = Palette::ReadOnly(colors1, 2);
  dc.draw(ProgMemRaster<Indexed1>(16, 16, home, &palette1), 200, 2);  
  /*if (apiState) {
    drawIcon(dc, ic_outlined_18_action_home(), 200, 0, color::DodgerBlue);
  } else {
    drawIcon(dc, ic_outlined_18_action_home(), 200, 0, color::Red);
  }*/
}
// Kowalski draw:)
void drawKowalski() {
  DrawingContext dc(display);
  static Palette palette = Palette::ReadOnly(kowalsky_color, 256);
  dc.draw(ProgMemRaster<Indexed8>(100, 192, kowalsky_data, &palette), 110, 30);
}
// HA Device setup
void haSetup() {
  // HA Decice start config
  hadevice.setName("WallPanel01");
  hadevice.setSoftwareVersion("1.1.0");
  // BUTTON1
  entity1.setIcon(ENTITY1_ICON);
  entity1.setName(ENTITY1_NAME);
  // BUTTON2
  entity2.setIcon(ENTITY2_ICON);
  entity2.setName(ENTITY2_NAME);
  // onSwitchCommand setting
  entity1.onCommand(onSwitchCommand);
  entity2.onCommand(onSwitchCommand);

  // DISPLAY BACKLIGHT
  backl.setIcon("mdi:brightness-6");
  backl.setName("Fényero");
  backl.setMin(1);    // can be float if precision is set via the constructor
  backl.setMax(255);  // can be float if precision is set via the constructor
  backl.setStep(1);   // minimum step: 0.001f
  backl.setMode(HANumber::ModeBox);
  backl.setMode(HANumber::ModeSlider);
  backl.onCommand(onNumberCommand);
  backl.setCurrentState(128);
  // BUTTONs TRANSPARENCY
  transp.setIcon("mdi:transition-masked");
  transp.setName("Átlátszóság");
  transp.setMin(1);    // can be float if precision is set via the constructor
  transp.setMax(255);  // can be float if precision is set via the constructor
  transp.setStep(1);   // minimum step: 0.001f
  transp.setMode(HANumber::ModeBox);
  transp.setMode(HANumber::ModeSlider);
  transp.onCommand(onNumberCommand);
  transp.setCurrentState(128);
  // BACKGROUND IMAGE SELECTOR FROM SD (only JPG max 240x320)
  hatter.setIcon("mdi:camera-burst");
  hatter.setName("Hatter");
  hatter.setOptions(hatterlist.c_str());
  hatter.onCommand(onSelectCommand);
  hatter.setCurrentState(11);
  hatter.setAvailability(sdState);
  // BUTTON STATE INIC FROM HA state
  entity1.setCurrentState(getEntityStateFromApi(ENTITY1));
  entity2.setCurrentState(getEntityStateFromApi(ENTITY2));
}
// setup START
void setup() {
  // Serial Start
  Serial.begin(9600);
  Serial.setDebugOutput(true);
  Serial.println();
  Serial.print("setup() running on core ");
  Serial.println(xPortGetCoreID());
  // Display Start
  SPI.begin(12, 13, 11, -1);
  display.init(Graylevel(0x00));
  drawKowalski();
  sd_spi.begin(SD_SCLK_PIN, SD_MISO_PIN, SD_MOSI_PIN, SD_CS_PIN);
  pinMode(SD_CS_PIN, OUTPUT);  // SS
  if (!SD.begin(SD_CS_PIN, sd_spi)) {
    Serial.println("SD Card Mount Failed");
    sdState = false;

  } else {
    Serial.println("SD Card Mount OK");
    dir = SD.open("/");
    readDirectory(dir, 0);
    sdState = true;
  }
  DrawingContext dc(display);
  dc.draw(TextLabel((sdState ? "SD...OK" : "SD...BAD"), font_NotoSans_Regular_15(), (sdState ? color::White : color::Red)), 3, 50);
  delay(KOWALSKI_TIME);
  //WIFI START
  byte mac[6];
  WiFi.macAddress(mac);
  hadevice.setUniqueId(mac, sizeof(mac));
  WiFi.setHostname("WallPanel01");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  WiFi.setSleep(false);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    dc.draw(TextLabel("WiFi BAD! REBOOT", font_NotoSans_Regular_15(), color::Red), 3, 70);
    delay(5000);
    ESP.restart();
  }
  dc.draw(TextLabel("WiFi....OK", font_NotoSans_Regular_15(), color::White), 3, 70);
  delay(KOWALSKI_TIME);
  // OTA CLASS
  ArduinoOTA.setHostname("WallPanel01");
  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else  // U_SPIFFS
        type = "filesystem";
      DrawingContext dc(display);
      dc.clear();
      drawKowalski();
      dc.draw(TextLabel("OTA start", font_NotoSans_Regular_15(), color::White), 100, 250);
      dc.draw(Rect(50, 270, 150, 290, color::Blue));
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      int prog = progress / (total / 100);
      DrawingContext dc(display);
      dc.draw(FilledRect(50, 270, prog + 50, 290, color::Blue));
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });
  //OTA CLASS END 
  ArduinoOTA.begin();   // START OTA
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("RSSI: ");
  Serial.println(rssi);
  //WIFI START_END
  timeState = initTime(TIME_ZONE);
  dc.draw(TextLabel((timeState ? "TIME....OK" : "TIME....BAD"), font_NotoSans_Regular_15(), (timeState ? color::White : color::Red)), 3, 90);
  delay(KOWALSKI_TIME);
  checkHaApi(); // TEST HA API RUNING?
  dc.draw(TextLabel((apiState ? "API....OK" : "API....BAD"), font_NotoSans_Regular_15(), (apiState ? color::White : color::Red)), 3, 110);
  delay(KOWALSKI_TIME);
  getWeather(); // GET WEATHER INFO FROM HA
  dc.draw(TextLabel((weatherState ? "WEATHER...GET" : "WEATHER....BAD"), font_NotoSans_Regular_15(), (weatherState ? color::White : color::Red)), 3, 130);
  delay(KOWALSKI_TIME);
  haSetup();  // HA Decice start config
  Serial.println("MQTT Start");
  mqtt.begin(BROKER_ADDR, BROKER_USERNAME, BROKER_PASSWORD);
  drawScreen(sdState ? filelist[fileindex] : "");  // Screen to backgrund
  dc.draw(background, kCenter | kMiddle);          // Draw background to screen
  if (ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, TimerHandler0)) {
    Serial.print(F("Starting  ITimer0 OK, millis() = "));
    Serial.println(millis());
    rScreen = 0;
  } else
    Serial.println(F("Can't set ITimer0. Select another Timer, freq. or timer"));

  if (ITimer1.attachInterruptInterval(TIMER1_INTERVAL_MS * 1000, TimerHandler1))

  {
    Serial.print(F("Starting  ITimer1 OK, millis() = "));
    Serial.println(millis());
    cDevice = 0;
  } else
    Serial.println(F("Can't set ITimer1. Select another Timer, freq. or timer"));

  delay(100);
  rScreen = 0;
  cDevice = 0;
}
// loop START
void loop(void) {
  // touch check
  bool touched = display.getTouch(x, y);
  if (touched) {
    DrawingContext dc(display);
    melyik_gomb = checkbox(x, y);      // 1 first button 2 second button -1 pressed out of valid area
    if (melyik_gomb != -1) {           // Valid area pressed
      if (melyik_gomb != regi_gomb) {  // Pressed area not = old pressed area
        regi_gomb = melyik_gomb;       // old area = new area
        switch (melyik_gomb) {         // select area (=select button)
          case 0:
            Serial.println("Button1 pressed");
            entity1.setState(!entity1.getCurrentState());          // State Change
            onSwitchCommand(entity1.getCurrentState(), &entity1);  // Write back current state, and display change
            break;
          case 1:
            Serial.println("Button2 pressed");
            entity2.setState(!entity2.getCurrentState());          // State Change
            onSwitchCommand(entity2.getCurrentState(), &entity2);  // Write back current state, and display change
            break;
        }
      }
    } else {
      if (regi_gomb != -1) {
        regi_gomb = -1;
      }
    }
    //was_touched = true;
  } else {
    regi_gomb = -1;
  }
  if (apiState == true) {
    mqtt.loop();
  }
  if (rScreen == 1)  // Weather API data Collect and redraw display
  {
    if (apiState == true) {
      getWeather();
    }
    drawScreen(sdState ? filelist[fileindex] : "");  // Screen to backgrund
    DrawingContext dc(display);
    dc.draw(background, kCenter | kMiddle);  // background to display
    rScreen = 0;                             // Timer0 Semaphore RESET
  }
  if (cDevice == 1) {
    checkHaApi();
    cDevice = 0;  // Timer1 Semaphore RESET
  }
  if (timeState == false) {
    timeState = initTime(TIME_ZONE);
  }
  printHeader();
  ArduinoOTA.handle();
}