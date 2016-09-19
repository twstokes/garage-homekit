# garage-homekit
https://www.tannr.com/2016/09/18/wireless-garage-door-opener-v2

https://youtu.be/C3-Wd1SD7OY

### Going from garage remote to iOS HomeKit

*This repository serves as an example and will probably not be updated or maintained. Clone and customize!*

## What this is:

A way to convert a standard home garage door opener to an IoT device that works with Apple products from anywhere in the world.

### Folders:

* **./docker_homebridge:** [Dockerized](https://www.docker.com/) [Homebridge](https://github.com/nfarina/homebridge).
* **./garage_door:** [Arduino](https://www.arduino.cc/) code and [Fritzing](www.fritzing.org) schematic for [Adafruit Feather HUZZAH ESP8266](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/overview).

### Gist:

1. A standard garage door remote is programmed to work with the garage door
 * The battery is replaced with power from the Feather
 * The button functionality is replaced with a transistor, triggered by an output from the Feather
2. The output is triggered by an HTTP call to the Feather over the wireless network
 * For convenience, the Feather's blue LED is lit when it's connected
 * Red LED is lit when something goes wrong
3. Homebridge is running on a dedicated computer that's running Docker
 * Via the Http plugin for Homebridge, we can communicate through HomeKit to the Feather

### Parts:

* [Adafruit Feather HUZZAH ESP8266](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/overview)
* Standard garage door opener
* 2N222 transistor
* 220 Ω resistor
* [Adafruit Perma-Proto board](https://www.adafruit.com/products/1609) (not required, but nice)
* iOS device
* Something that can run Homebridge (Docker isn't required)