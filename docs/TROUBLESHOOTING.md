# SmartGate Troubleshooting Guide

This page documents problems encountered while building SmartGate and how to fix them.

## RC522 Does Not Detect NFC Card

Check:

- SDA / SS -> Mega pin 53
- SCK -> Mega pin 52
- MOSI -> Mega pin 51
- MISO -> Mega pin 50
- RST -> Mega pin 5
- GND -> GND
- VCC -> 3.3V

Important:

Do not power the RC522 with 5V.

If the reader still does not work, upload a simple UID-reader sketch and test the RC522 by itself.

---

## LCD Backlight Is On but No Text Appears

This usually means the LCD has power but the contrast or data wiring is wrong.

Check:

- LCD pin 1 -> GND
- LCD pin 2 -> 5V
- LCD pin 3 -> potentiometer middle pin
- LCD pin 4 -> Mega pin 22
- LCD pin 5 -> GND
- LCD pin 6 -> Mega pin 23
- LCD pin 11 -> Mega pin 24
- LCD pin 12 -> Mega pin 25
- LCD pin 13 -> Mega pin 26
- LCD pin 14 -> Mega pin 27

Slowly rotate the potentiometer.

If needed, temporarily connect LCD pin 3 (VO) directly to GND to test maximum contrast.

---

## LCD Shows Dark Blocks Only

Dark blocks usually mean the LCD has power and contrast, but is not receiving valid data.

Check:

- RS
- E
- D4
- D5
- D6
- D7

Also make sure the code matches:

```cpp
LiquidCrystal lcd(22, 23, 24, 25, 26, 27);
