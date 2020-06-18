#include <ArduinoJson.h>
#include <DallasTemperature.h>
#include <ESP8266WebServer.h>
#include <OneWire.h>
#include <stdio.h>

#include "WifiCredentials.h" //Make sure that you have put your credentials in the 'WifiCredentials.h.template' file and renamed the file to 'WifiCredentials.h'

#define HTTP_REST_PORT 80
#define MAX_WIFI_INIT_RETRY 50
#define ONE_WIRE_BUS D3
#define WIFI_RETRY_DELAY 500


ESP8266WebServer http_rest_server(HTTP_REST_PORT);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
char TemperatureStr[6];
unsigned int SecureCounter;

int init_wifi() {
    int retries = 0;

    Serial.println("Connecting to WiFi AP..........");

    WiFi.mode(WIFI_STA);
    WiFi.begin(wifi_ssid, wifi_passwd);
    // check the status of WiFi connection to be WL_CONNECTED
    while ((WiFi.status() != WL_CONNECTED) && (retries < MAX_WIFI_INIT_RETRY)) {
        retries++;
        delay(WIFI_RETRY_DELAY);
        Serial.print("#");
    }
    return WiFi.status(); // return the WiFi connection status
}

void readTemperature() {
   float temp;
   int cnt = 3; //retry counter
   do {
       if (cnt <= 0) {
          String nanStr = "NaN";
          nanStr.toCharArray(TemperatureStr, 6);
          break;
       }
       DS18B20.requestTemperatures(); 
       temp = DS18B20.getTempCByIndex(0);
       
       dtostrf(temp, 2, 2, TemperatureStr);
       delay(100);
       cnt--;
   } while (temp == 85.0 || temp == (-127.0));
   SecureCounter++;
}

void getApi() {
    readTemperature();
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& jsonObj = jsonBuffer.createObject();
    char JSONmessageBuffer[200];
  
    jsonObj["secure_counter"] = SecureCounter;
    jsonObj["symbol"] = "°C";
    jsonObj["temperature"] = TemperatureStr;
    jsonObj["unit"] = "Celsius";
    jsonObj.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    http_rest_server.send(200, "application/json", JSONmessageBuffer);
}

void getIndex() {
    readTemperature();
    http_rest_server.send(200, "text/html", "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title>Temp2IoT</title><style type=\"text/css\">html{font-family:-apple-system,BlinkMacSystemFont,\"Segoe UI\",Roboto,\"Helvetica Neue\",Arial,\"Noto Sans\",sans-serif,\"Apple Color Emoji\",\"Segoe UI Emoji\",\"Segoe UI Symbol\",\"Noto Color Emoji\";-webkit-text-size-adjust:100%;background: #1e87f0;color:#666;}@media all and (min-width:600px) {.card {box-shadow: 0 5px 15px rgba(0,0,0,.2);}}body{margin:0;}.container {right: 0%;top: 50%;position: fixed;-webkit-transform: translateY(-50%);-moz-transform: translateY(-50%);-ms-transform: translateY(-50%);-o-transform: translateY(-50%);transform: translateY(-50%);width: 100%;}.card {margin: auto;background: #1e87f0;color: #fff;width: 400px;}.card-header {padding: 20px 40px;margin: 0 0 20px 0;}.card-header h3,.card-body h1 {font-family: -apple-system,BlinkMacSystemFont,\"Segoe UI\",Roboto,\"Helvetica Neue\",Arial,\"Noto Sans\",sans-serif,\"Apple Color Emoji\",\"Segoe UI Emoji\",\"Segoe UI Symbol\",\"Noto Color Emoji\";font-weight: 400;text-transform: none;}.card-header h3 {font-size: 1.5rem;line-height: 1.4;}.card-body h1 {font-size: 5rem;line-height: 0.8;margin: 0 0 15px 0;}.card-body {padding: 40px 40px;}.card-footer {padding: 20px 40px;color: rgba(255,255,255,.7);}.card-footer a{color: #fff;text-decoration: none;cursor: pointer;}.icon {fill: currentColor;}</style></head><body><div class=\"container\"><div class=\"card\"><div class=\"card-header\"><h3><span class=\"icon\"><svg width=\"20\" height=\"20\" viewBox=\"0 0 256 512\" xmlns=\"http://www.w3.org/2000/svg\" data-svg=\"thermometer-half\"><path d=\"M192 384c0 35.346-28.654 64-64 64s-64-28.654-64-64c0-23.685 12.876-44.349 32-55.417V224c0-17.673 14.327-32 32-32s32 14.327 32 32v104.583c19.124 11.068 32 31.732 32 55.417zm32-84.653c19.912 22.563 32 52.194 32 84.653 0 70.696-57.303 128-128 128-.299 0-.609-.001-.909-.003C56.789 511.509-.357 453.636.002 383.333.166 351.135 12.225 321.755 32 299.347V96c0-53.019 42.981-96 96-96s96 42.981 96 96v203.347zM208 384c0-34.339-19.37-52.19-32-66.502V96c0-26.467-21.533-48-48-48S80 69.533 80 96v221.498c-12.732 14.428-31.825 32.1-31.999 66.08-.224 43.876 35.563 80.116 79.423 80.42L128 464c44.112 0 80-35.888 80-80z\"></path></svg></span>Temp2IoT</h3></div><div class=\"card-body\"><h1>" + String(TemperatureStr) + " °C</h1><p style=\"margin: 0px;\">Water Temperature</p></div><div class=\"card-footer\"><p>Secure Counter: " + String(SecureCounter) + "<br><span class=\"icon\" style=\"line-height: 2; position: relative; bottom: -2px;\"><svg width=\"16\" height=\"16\" viewBox=\"0 0 20 20\" xmlns=\"http://www.w3.org/2000/svg\" data-svg=\"github\"><path d=\"M10,1 C5.03,1 1,5.03 1,10 C1,13.98 3.58,17.35 7.16,18.54 C7.61,18.62 7.77,18.34 7.77,18.11 C7.77,17.9 7.76,17.33 7.76,16.58 C5.26,17.12 4.73,15.37 4.73,15.37 C4.32,14.33 3.73,14.05 3.73,14.05 C2.91,13.5 3.79,13.5 3.79,13.5 C4.69,13.56 5.17,14.43 5.17,14.43 C5.97,15.8 7.28,15.41 7.79,15.18 C7.87,14.6 8.1,14.2 8.36,13.98 C6.36,13.75 4.26,12.98 4.26,9.53 C4.26,8.55 4.61,7.74 5.19,7.11 C5.1,6.88 4.79,5.97 5.28,4.73 C5.28,4.73 6.04,4.49 7.75,5.65 C8.47,5.45 9.24,5.35 10,5.35 C10.76,5.35 11.53,5.45 12.25,5.65 C13.97,4.48 14.72,4.73 14.72,4.73 C15.21,5.97 14.9,6.88 14.81,7.11 C15.39,7.74 15.73,8.54 15.73,9.53 C15.73,12.99 13.63,13.75 11.62,13.97 C11.94,14.25 12.23,14.8 12.23,15.64 C12.23,16.84 12.22,17.81 12.22,18.11 C12.22,18.35 12.38,18.63 12.84,18.54 C16.42,17.35 19,13.98 19,10 C19,5.03 14.97,1 10,1 L10,1 Z\"></path></svg></span> Find the <a href=\"https://github.com/100prznt/Temp2IoT\" target=\"_blank\">Temp2IoT</a> project on GitHub.</p></div></div></div></body></html>");
}


void config_rest_server_routing() {
    http_rest_server.on("/", HTTP_GET, getIndex);
    http_rest_server.on("/api", HTTP_GET, getApi);
}

void setup(void) {
    Serial.begin(115200);
    delay(10);

    DS18B20.begin();
    SecureCounter = 0;

    if (init_wifi() == WL_CONNECTED) {
        Serial.print("Connetted to ");
        Serial.print(wifi_ssid);
        Serial.print("--- IP: ");
        Serial.println(WiFi.localIP());
    }
    else {
        Serial.print("Error connecting to: ");
        Serial.println(wifi_ssid);
    }

    config_rest_server_routing();

    http_rest_server.begin();
    Serial.println("HTTP Temp2IoT server started");
}

void loop(void) {
    http_rest_server.handleClient();
}
