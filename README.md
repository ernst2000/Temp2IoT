<img src="docu/Temp2IoT_Icon_Black.svg" alt="Temp2IoT wiring" width="64" height="64" />

# Temp2IoT
Very basic IoT thermometer with REST API and Web-UI. Implemented according to the "KISS" approach - **K**eep **I**t **S**imple and **S**tupid

## Features
* Temperature measurement at one measuring points using a DS18B20 sensor
* Shows the measured values on integrated Web UI
* REST API for integration with master systems


## Hardware

### BOM

| Description          | Qty. | Price     | ASIN (partner-link from amazon.de)    |
|----------------------|------|----------:|---------------------------------------|
| WeMos D1 mini        | 1    | EUR 6,99  | [B08BTYHJM1](https://amzn.to/3q9VDDx) |
| DS18B20 waterproof   | 1    | EUR 3,79  | [B07SHHNJ37](https://amzn.to/3rE94M5) |
| Resistor 4K7 (1/4 W) | 1    | EUR 0,99  | [B00IYT46U4](https://amzn.to/2MTAsHd) |
|----------------------|------|-----------|---------------------------------------|
| Total                |      | EUR 11,77 |                                       |

*quoted prices from 2021/02/10*

Also a USB-micro cable and a USB power supply is required

### Wiring

![Temp2IoT wiring](hardware/temp2iot_wiring.png)

### Photos

![Temp2IoT minimal build up](hardware/hardware_raw.jpg)
Minimal build up with SMD resistor on the back

## Setup

Wenn bisher noch keine WeMos D1 mini mit der Arduino IDE programmiert wurden ist zuerst eine entsprechende Einrichtung erforderlich.
* [Wiki - Setup Arduino IDE for WeMos D1 mini](https://github.com/100prznt/Temp2IoT/wiki/Setup-Arduino-IDE)

1. Clone or download the repository
2. Put your credentials in the `src\Temp2IoT\WifiCredentials.h.template` file and rename the file to `WifiCredentials.h`
3. Open the `src\Temp2IoT\Temp2IoT.ino` with the Arduino IDE
4. Compile and upload
5. Open the serial monitor (in Arduino IDE) to see the WiFi status and the applied IP address


## REST API
* URL: `http://<Temp2IoT IP>/api`
* Method: `GET`

```
{
  "secure_counter": 3,
  "symbol": "°C",
  "temperature": "25.63",
  "unit": "Celsius"
}
```

## Web UI
* URL: `http://<Temp2IoT IP>/`
  <br>
  <br>
  <br>
![Web UI on a desktop browser](docu/webui_desktop.png)
Web UI on a desktop browser
  <br>
  <br>
  <br>
![Web UI on a smartphone browser](docu/webui_smartphone.png)
Web UI on a smartphone browser


## Enclosure
In the folder [hardware/enclosure](hardware/enclosure) you will find 2 STL files of a suitable enclosure. If the cover is printed upside-down, you can print the first two layers in a different color to make the Temp2IoT icon stand out better.

### Photos

![3d-printed enclousure with Temp2IoT icon](hardware/temp2iot_logo_case.jpg)
3d-printed enclousure with Temp2IoT icon
  <br>
  <br>
![3d-printed enclousure open](hardware/temp2iot_logo_case_open.jpg)
Blackened inside so that the LED produces a focused light spot
