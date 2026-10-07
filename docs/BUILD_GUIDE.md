# SmartGate Full Build Guide

## Project Goal

SmartGate is an NFC-based parking access control system built with an ELEGOO Mega 2560.

An authorized NFC card will:

1. Be detected by the RC522.
2. Display the user's name on the LCD.
3. Turn on the green LED.
4. Sound the buzzer.
5. Open the parking gate using a stepper motor.
6. Wait several seconds.
7. Close the gate.
8. Return to standby mode.

An unauthorized card will:

1. Display `ACCESS DENIED`.
2. Turn on the red LED.
3. Sound a warning buzzer.
4. Keep the gate closed.

---

## Hardware Used

- ELEGOO Mega 2560 R3
- RC522 RFID/NFC reader
- RFID/NFC card or tag
- 16x2 LCD display
- 10k potentiometer
- 28BYJ-48 stepper motor
- ULN2003 stepper motor driver
- Green LED
- Red LED
- Buzzer
- 220 ohm resistors
- Breadboard
- Jumper wires
- USB cable

---

## RC522 Wiring

| RC522 | ELEGOO Mega 2560 |
|---|---|
| SDA / SS | 53 |
| SCK | 52 |
| MOSI | 51 |
| MISO | 50 |
| IRQ | Not connected |
| GND | GND |
| RST | 5 |
| 3.3V | 3.3V |

> Important: Power the RC522 from **3.3V**, not 5V.

---

## LED Wiring

### Green LED

- Long leg -> 220 ohm resistor -> Mega pin 6
- Short leg -> GND

### Red LED

- Long leg -> 220 ohm resistor -> Mega pin 7
- Short leg -> GND

---

## Buzzer Wiring

- Positive -> Mega pin 8
- Negative -> GND

---

## 16x2 LCD Wiring

The LCD uses 4-bit mode.

| LCD Pin | Label | Connection |
|---|---|---|
| 1 | VSS | GND |
| 2 | VDD | 5V |
| 3 | VO | Potentiometer middle pin |
| 4 | RS | Mega pin 22 |
| 5 | RW | GND |
| 6 | E | Mega pin 23 |
| 7 | D0 | Not connected |
| 8 | D1 | Not connected |
| 9 | D2 | Not connected |
| 10 | D3 | Not connected |
| 11 | D4 | Mega pin 24 |
| 12 | D5 | Mega pin 25 |
| 13 | D6 | Mega pin 26 |
| 14 | D7 | Mega pin 27 |
| 15 | A | 5V through resistor |
| 16 | K | GND |

---

## Potentiometer Wiring

The potentiometer adjusts LCD contrast.

- One outside leg -> 5V
- Other outside leg -> GND
- Middle leg -> LCD pin 3 (VO)

If the LCD backlight is on but no text appears, slowly rotate the potentiometer.

---

## Stepper Motor

Motor:

`28BYJ-48`

Driver:

`ULN2003`

The motor's white 5-pin connector plugs directly into the white socket on the ULN2003 board.

Do not connect the motor's colored wires individually to the Mega.

---

## ULN2003 Wiring

| ULN2003 | ELEGOO Mega 2560 |
|---|---|
| IN1 | 30 |
| IN2 | 32 |
| IN3 | 34 |
| IN4 | 36 |
| VCC / + | 5V |
| GND / - | GND |

The working stepper pin order used in software is:

```cpp
Stepper gateMotor(
  2048,
  30, 34, 32, 36
);
