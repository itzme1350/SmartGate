# SmartGate Wiring Reference

This file is the quick wiring reference for rebuilding SmartGate.

## ELEGOO Mega 2560 Pin Map

### RC522 RFID/NFC Reader

| RC522 | Mega 2560 |
|---|---|
| SDA / SS | 53 |
| SCK | 52 |
| MOSI | 51 |
| MISO | 50 |
| IRQ | Not connected |
| GND | GND |
| RST | 5 |
| 3.3V | 3.3V |

> RC522 must use 3.3V.

---

### LEDs

#### Green LED
- Long leg -> 220 ohm resistor -> Pin 6
- Short leg -> GND

#### Red LED
- Long leg -> 220 ohm resistor -> Pin 7
- Short leg -> GND

---

### Buzzer

- Positive -> Pin 8
- Negative -> GND

---

### 16x2 LCD

| LCD Pin | Label | Mega Connection |
|---|---|---|
| 1 | VSS | GND |
| 2 | VDD | 5V |
| 3 | VO | Potentiometer middle pin |
| 4 | RS | 22 |
| 5 | RW | GND |
| 6 | E | 23 |
| 7 | D0 | Not connected |
| 8 | D1 | Not connected |
| 9 | D2 | Not connected |
| 10 | D3 | Not connected |
| 11 | D4 | 24 |
| 12 | D5 | 25 |
| 13 | D6 | 26 |
| 14 | D7 | 27 |
| 15 | A | 5V through resistor |
| 16 | K | GND |

---

### LCD Contrast Potentiometer

- Outside leg 1 -> 5V
- Outside leg 2 -> GND
- Middle leg -> LCD pin 3 (VO)

---

### ULN2003 Stepper Driver

| ULN2003 | Mega 2560 |
|---|---|
| IN1 | 30 |
| IN2 | 32 |
| IN3 | 34 |
| IN4 | 36 |
| VCC / + | 5V |
| GND / - | GND |

The 28BYJ-48 stepper motor plugs directly into the white 5-pin socket on the ULN2003 board.

---

## Software Pin Summary

```cpp
#define SS_PIN 53
#define RST_PIN 5

#define GREEN_LED 6
#define RED_LED 7
#define BUZZER 8

LiquidCrystal lcd(22, 23, 24, 25, 26, 27);

Stepper gateMotor(
  2048,
  30, 34, 32, 36
);
