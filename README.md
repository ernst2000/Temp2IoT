<img src="docu/Temp2IoT_Icon_Black.svg" alt="Temp2IoT wiring" width="80" height="80" />

# Temp2IoT
Very basic IoT thermometer with REST API and Web-UI. Implemented according to the "KISS" approach - **K**eep **I**t **S**imple and **S**tupid

## Features
* Temperature measurement at one or two measuring points using DS18B20 sensors
* Shows the measured values on integrated web UI
* REST API for integration with master systems (e.g. ioBroker)
* Configuration also via a web UI


## Hardware

### BOM

| Description          | Qty.   | Price     | ASIN (partner-link from amazon.de)    |
|----------------------|--------|----------:|---------------------------------------|
| WeMos D1 mini        | 1      | EUR 6,49  | [B01N9RXGHY](https://amzn.to/3clRAiP) |
| DS18B20 waterproof   | 1 or 2 | EUR 3,50  | [B01MZG48OE](https://amzn.to/2NQUkvc) |
| Resistor 2K2 (0,6 W) | 1      | EUR 0,99  | [B007R3QXUE](https://amzn.to/3ja1jww) |
|----------------------|--------|-----------|---------------------------------------|
| Total                |        | EUR 10,98 |                                       |

*quoted prices from 2022/09/08*

Also a USB-micro cable and a USB power supply is required

### Wiring

![Temp2IoT wiring](hardware/temp2iot_wiring_2.png)

### Power Supply
:warning: Caution Danger to life :warning:

If the thermometer is used to measure water temperatures, it is essential to use an appropriately classified power supply unit. It is important that the power supply is designed as a safety transformer.

A simple USB power supply that meets these requirements can be found here:
* [5V USB-Netzteil mit Sicherheitstransformator | 07-314.0](https://shop.stegertrafo.de/5v-usb-netzteil-mit-sicherheitstransformator-07-314-0.html)

<img src="docu/Sitrenn.svg" alt="Temp2IoT wiring" width="180" height="210" />
Symbol of a short-circuit proof, closed safety transformer 

### Photos

![Temp2IoT minimal build up](hardware/hardware_raw.jpg)
Minimal build up with SMD resistor on the back and only one connected DS18B20. 

## Setup

You have two options to upload the software to the WeMos D1 mini.

### ESP8266 Flasher (Windows)

You can download the compiled Flasher Tool from the GitHub Repository
* [nodemcu/nodemcu-flasher](https://github.com/nodemcu/nodemcu-flasher)

1. Clone or download the repository
2. Start the ESP8266Flasher.exe
3. Select the pre-compiled Temp2IoT binary on the config-tab, find at: `src\Temp2IoT\emp2IoT.ino.d1_mini.bin`
4. Switch back to the operation-tab and select the right COM-port
5. Press the Flash-Button


## REST API
* URL: `http://<Temp2IoT IP>/api`
* Method: `GET`

```
{
  "systemname": "My Temp2IoT instance",
  "secure_counter": 50,
  "firmware": "2.2.04-b",
  "sensors": [
    {
      "name": "water",
      "value": 23.625,
      "mean-1": {
        "count": 5,
        "value": 23.6,
        "period": 3600
      },
      "mean-24": {
        "count": 5,
        "value": 23.6,
        "period": 86400
      },
      "unit": "Celsius",
      "time": "Fri Jul  9 13:12:36 2021"
    },
    {
      "name": "ambient",
      "value": 23.9375,
      "unit": "Celsius",
      "time": "Fri Jul  9 13:12:37 2021"
    }
  ]
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

## System Setup
* URL: `http://<Temp2IoT IP>/setup/`
  <br>
  <br>
  <br>
![Web setup page on a smartphone browser](docu/setup_smartphone.png)
Setup page on a smartphone browser

## Color Scheme
<img src="docu/Scheme_100prznt.png" alt="Temp2IoT Color Scheme 100prznt" width="260" height="332" />  <img src="docu/Scheme_Classic.png" alt="Temp2IoT Color Scheme CLASSIC" width="260" height="332" />  <img src="docu/Scheme_Total.png" alt="Temp2IoT Color Scheme TOTAL" width="260" height="332" />  <img src="docu/Scheme_Power.png" alt="Temp2IoT Color Scheme POWER" width="260" height="332" />  <img src="docu/Scheme_Sun.png" alt="Temp2IoT Color Scheme SUN" width="260" height="332" />  <img src="docu/Scheme_100przntDark.png" alt="Temp2IoT Color Scheme DARK" width="260" height="332" />

### Colors

| # | scheme   | primary color | badge                                                   |
|:--|:---------|:--------------|---------------------------------------------------------|
| 1 | 100prznt | `#ff2e64`     | ![#ff2e64](https://img.shields.io/badge/-ff2e64-ff2e64) |
| 2 | Classic  | `#1e87f0`     | ![#1e87f0](https://img.shields.io/badge/-1e87f0-1e87f0) |
| 3 | Total    | `#30a4a1`     | ![#30a4a1](https://img.shields.io/badge/-30a4a1-30a4a1) |
| 4 | Power    | `#325c84`     | ![#325c84](https://img.shields.io/badge/-325c84-325c84) |
| 5 | Sun      | `#f08a00`     | ![#f08a00](https://img.shields.io/badge/-f08a00-f08a00) |
| 6 | Dark     | `#060d2a`     | ![#060d2a](https://img.shields.io/badge/-060d2a-060d2a) |



## Debug Output

Feel free to take a look at the serial monitor (115200 baud).

```
21:54:57.656 ->
21:54:57.656 ->        _____               ___ ___    _____       
21:54:57.656 ->       |_   _|__ _ __  _ __|_  )_ _|__|_   _|      
21:54:57.702 ->         | |/ -_) '  \| '_ \/ / | |/ _ \| |        
21:54:57.702 ->         |_|\___|_|_|_| .__/___|___\___/|_|        
21:54:57.702 ->                      |_|                          
21:54:57.702 -> 
21:54:57.702 -> **************************************************
21:54:57.702 ->        a 100prznt.de project by E. Ruemmler       
21:54:57.702 ->                       v2.2.04-b
21:54:57.702 -> 
```

## Enclosure
In the folder [hardware/enclosure](hardware/enclosure) you will find 2 STL files of a suitable enclosure. If the cover is printed upside-down, you can print the first two layers in a different color to make the Temp2IoT icon stand out better.

### Photos

![3d-printed enclousure with Temp2IoT icon](hardware/temp2iot_logo_case.jpg)
3d-printed enclousure with Temp2IoT icon
  <br>
  <br>
![3d-printed enclousure open](hardware/temp2iot_logo_case_open.jpg)
Blackened inside so that the LED produces a focused light spot

## Community
Found this project on the german [Poolpowershop-Forum](https://www.poolpowershop-forum.de/).
* [WiFi Thermometer für 10 Euro selbst gebaut (Web UI, REST API)](https://www.poolpowershop-forum.de/forum/thread/1103493-wifi-thermometer-f%C3%BCr-10-euro-selbst-gebaut-web-ui-rest-api/)

## Credits
This app is made possible by contributions from:
* [Elias Rümmler](http://www.100prznt.de) ([@rmmlr](https://github.com/rmmlr)) - core contributor

### Open Source Project Credits

* [Follower Counter](https://github.com/jegade/followercounter) - The architeture of Temp2IoT based on a awesome code from [@jegade](https://github.com/jegade) used for his followercounter project.
* Used Arduino libraries are described in the code.

## License
The Temp2IoT project is licensed under [MIT](http://www.opensource.org/licenses/mit-license.php "Read more about the MIT license form"). Refer to [LICENSE.txt](https://github.com/100prznt/Temp2IoT/blob/master/LICENSE.txt) for more information.

## Contributions
Contributions are welcome. Fork this repository and send a pull request if you have something useful to add.
