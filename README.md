# ESP8266 for Arduino UNO

This repository contains my ESP8266 working with a Arduino UNO.

See the sub folders in this repository for test scripts.

## The wifi.ino script

1. Connects to a WIFI AP, and gets IP address. Configure the vars for your needs.
2. When button on INPUT PIN 2 is pressed, a HTTP request is sent to google.

### Wiring Diagram

This is the complete wiring diagram using the "wifi/wifi.ino" script. Just follow the simple steps and upload it to your arduino and you are good.

![Wire Diagram](/images/wire_diagram.png)

- The resistor can be any resitor, I use a 1K resistor. The resistor is needed because we have a direct positive to negative when button is pushed.
- Connecting the ESP8266, you see that we use a total of 5 Connection points on the chip. RX, TX, GND, VCC and CH_PD. Both VCC and CH_PD connects to +3.3V. RX to input 11, TX to input 12 and GND to .. GND.


## Where to buy the ESP8266 chip?

Ebay, really cheap - like 3 $.


## ESP8266 Diagram

![ESP8266 Diagram](/images/diagram.jpg)



