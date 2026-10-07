# SmartGate

SmartGate is an NFC-based parking access control system built using an **ELEGOO Mega 2560**.

The system reads an RFID/NFC card using an RC522 reader, checks whether the card is authorized, and then controls a parking gate using a stepper motor.

The system also provides visual and audio feedback using:

- 16x2 LCD
- Green LED
- Red LED
- Buzzer

---

## Project Goal

The goal of SmartGate is to create a small prototype of an automated parking access system.

When an authorized NFC card is scanned:

1. The system recognizes the card.
2. The LCD displays the user's name.
3. The green LED turns on.
4. The buzzer gives an acceptance tone.
5. The gate opens.
6. The system waits for a short period.
7. The gate closes.
8. The system returns to standby mode.

If an unauthorized card is scanned:

1. The LCD displays `ACCESS DENIED`.
2. The red LED turns on.
3. The buzzer gives warning tones.
4. The gate remains closed.

---

## Current System Flow

```text
NFC Card
   ↓
RC522 RFID Reader
   ↓
ELEGOO Mega 2560
   │
   ├── LCD Display
   ├── Green LED
   ├── Red LED
   ├── Buzzer
   │
   └── ULN2003 Driver
            ↓
       28BYJ-48 Stepper
            ↓
        Parking Gate
```

---

## Hardware Used

- ELEGOO Mega 2560 R3
- RC522 RFID/NFC reader
- RFID/NFC card or tag
- 16x2 LCD display
- 10k potentiometer
- Green LED
- Red LED
- Buzzer
- 220Ω resistors
- 28BYJ-48 stepper motor
- ULN2003 stepper motor driver
- Breadboard
- Jumper wires
- USB cable

---

## Main Pin Connections

| Mega Pin | Device | Function |
|---:|---|---|
| 5 | RC522 | Reset |
| 6 | Green LED | Access granted indicator |
| 7 | Red LED | Access denied indicator |
| 8 | Buzzer | Audio feedback |
| 22 | LCD | RS |
| 23 | LCD | Enable |
| 24 | LCD | D4 |
| 25 | LCD | D5 |
| 26 | LCD | D6 |
| 27 | LCD | D7 |
| 30 | ULN2003 | IN1 |
| 32 | ULN2003 | IN2 |
| 34 | ULN2003 | IN3 |
| 36 | ULN2003 | IN4 |
| 50 | RC522 | MISO |
| 51 | RC522 | MOSI |
| 52 | RC522 | SCK |
| 53 | RC522 | SS |

The RC522 is powered from **3.3V**.

---

## Authorized NFC Card

The current authorized UID is:

```text
FA 83 7E 81
```

The system is currently configured for:

```text
HPONE MYAT
```

---

## LCD Messages

### Standby

```text
NFC PARKING
Tap your card
```

### Authorized

```text
WELCOME
HPONE MYAT
```

### Gate Opening

```text
GATE OPENING
```

### Gate Closing

```text
GATE CLOSING
```

### Completed

```text
THANK YOU
DRIVE SAFE
```

### Unauthorized

```text
ACCESS DENIED
UNKNOWN CARD
```

---

## Software

The project is programmed in Arduino C++.

Libraries used:

- `SPI`
- `MFRC522`
- `LiquidCrystal`
- `Stepper`

The main Arduino program is located here:

```text
arduino/SmartGate.ino
```

---

## Project Structure

```text
SmartGate/
│
├── README.md
│
├── arduino/
│   └── SmartGate.ino
│
└── docs/
    ├── BUILD_GUIDE.md
    ├── WIRING.md
    ├── HOW_IT_WORKS.md
    └── TROUBLESHOOTING.md
```

---

## Documentation

### Build Guide

See:[Build Guide](docs/BUILD_GUIDE.md)

This contains the full instructions for rebuilding SmartGate.

### Wiring Guide

See: [Wireing Guide](docs/WIRING.md)

This contains the quick pin and wiring reference.

### How It Works

See: [How_IT_WORKS Guide](docs/HOW_IT_WORKS.md)

This explains:

- What each component does
- Why each pin is connected
- How SPI communication works
- How the LCD communicates
- How the motor driver works
- How the complete system processes an NFC card

### Troubleshooting

See: [Troubleshooting Guide](docs/TROUBLESHOOTING.md)

This contains solutions for common problems such as:

- LCD backlight but no text
- RC522 not detecting cards
- Stepper motor vibrating
- LEDs not working
- Buzzer not working

---

## Current Features

- NFC card detection
- Authorized UID checking
- Access granted / denied logic
- LCD status messages
- Green access LED
- Red denied LED
- Audio feedback
- Automatic gate opening
- Automatic gate closing
- Serial access messages

---

## Current Version

This repository documents the current working SmartGate prototype.

Future features and improvements will be added as the project develops.
