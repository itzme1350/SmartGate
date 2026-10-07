# How SmartGate Works

## System Overview
SmartGate is an NFC-based parking access control system built using an ELEGOO Mega 2560.

The Mega 2560 acts as the main controller. It receives data from the RC522 RFID/NFC reader and then controls the LCD, LEDs, buzzer, and stepper motor.

The basic system flow is:

```text

NFC Card

   ↓

RC522 RFID Reader

   ↓

ELEGOO Mega 2560

   ├── LCD

   ├── Green LED

   ├── Red LED

   ├── Buzzer

   └── ULN2003 Driver

            ↓

       Stepper Motor

            ↓

          Gate

## ELEGOO Mega 2560
The ELEGOO Mega 2560 is the main controller of SmartGate.

It runs the Arduino program and decides what should happen after an NFC card is scanned.

The Mega has several types of pins.

Power Pins

The main power connections used in this project are:

* 5V
* 3.3V
* GND

The 5V pin powers components such as the LCD and ULN2003 motor driver.

The 3.3V pin powers the RC522 RFID reader.

GND means ground.

All components need a common ground so that they share the same electrical reference.

⸻

Digital Pins

Digital pins can be used as inputs or outputs.

Examples in SmartGate:
Pin 6  -> Green LED
Pin 7  -> Red LED
Pin 8  -> Buzzer
Pin 22 -> LCD RS
Pin 23 -> LCD Enable
Pin 24 -> LCD D4
Pin 25 -> LCD D5
Pin 26 -> LCD D6
Pin 27 -> LCD D7
Pin 30 -> ULN2003 IN1
Pin 32 -> ULN2003 IN2
Pin 34 -> ULN2003 IN3
Pin 36 -> ULN2003 IN4

## RC522 NFC Reader

The RC522 reads RFID or NFC cards and tags.

When a tag is placed near the reader, the RC522 reads its UID.

A UID is a "unique identification number" stored on the card.

The Arduino program compares the scanned UID with this stored UID.

If they match, access is granted.

If they do not match, access is denied.

##RC522 Connections
The RC522 is connected to the Mega using SPI communication.


## SPI Pins
SPI stands for Serial Peripheral Interface.

It allows the Mega to communicate with the RC522.

The Mega is the master device.

The RC522 is the peripheral device.

The important SPI pins are:

MOSI

MOSI means: Master Out, Slave In
Mega -----> RC522
     MOSI
     
MISO means:
     Master In, Slave Out

## LEDs
...

## Buzzer
...

## 16x2 LCD
...

## Potentiometer
...

## Stepper Motor
...

## ULN2003 Driver
...

## Full System Flow
...
