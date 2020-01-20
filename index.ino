
#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>

Espalexa espalexa;

boolean connectWifi()
{
  boolean is_connnected = true;
  int i = 0;
  char *wifi_name = "**";
  char *wifi_password = "**";

  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_name, wifi_password);

  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    if (i > 20)
    {
      is_connnected = false;
      break;
    }
    i++;
  }

  if (is_connnected)
  {
    Serial.print('\n');
    Serial.print("Connected to ");
    Serial.println(wifi_name);
  }
  else
  {
    Serial.println("Connection failed.");
  }

  return is_connnected;
}

void firstLightChanged(uint8_t brightness, uint32_t rgb)
{
  Serial.print('\n');
  Serial.print("LED 1");

  Serial.println('\n');
  Serial.println("brightness: ");
  Serial.println(brightness);
  Serial.println('\n');
  Serial.println("RGB: ");
  Serial.println(rgb);

  if (brightness)
  {
    Serial.print("ON, brightness ");
    Serial.println(brightness);
  }
  else
  {
    Serial.println("OFF");
  }
}

void setup()
{
  Serial.begin(115200);
  boolean isWifiConnected = connectWifi();

  if (isWifiConnected)
  {
    espalexa.addDevice("Light 1", firstLightChanged);
    espalexa.begin();
  }
  else
  {
    while (1)
    {
      Serial.println("Cannot connect to WiFi.");
      delay(2500);
    }
  }
}

void loop()
{
  espalexa.loop();
  delay(100);
}