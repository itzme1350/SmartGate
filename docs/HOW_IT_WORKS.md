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
