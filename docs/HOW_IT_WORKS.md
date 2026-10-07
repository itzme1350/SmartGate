# How SmartGate Works

## System Overview

SmartGate is an NFC-based parking access control system built with an **ELEGOO Mega 2560**.

The Mega 2560 acts as the main controller of the system. It receives information from the RC522 NFC reader, makes an access decision, and then controls the LCD, LEDs, buzzer, and stepper motor.

### Basic System Flow

```text
NFC Card / Tag
      ↓
RC522 RFID Reader
      ↓
   SPI Data
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

The overall concept is:

```text
INPUT → PROCESSING → OUTPUT
```

For SmartGate:

```text
NFC Card
   ↓
RC522 Reader
   ↓
Mega checks UID
   ↓
Access decision
   ↓
LCD + LED + Buzzer + Gate
```

---

# 1. ELEGOO Mega 2560

The **ELEGOO Mega 2560** is the brain of SmartGate.

It runs the Arduino program and controls all of the connected hardware.

The Mega performs three main jobs:

1. Receives information from the RC522.
2. Checks whether the NFC UID is authorized.
3. Controls the outputs depending on the result.

The project uses three main types of Mega connections:

- Power
- Input/communication
- Output/control

---

## Power Pins

SmartGate uses:

```text
5V
3.3V
GND
```

### 5V

Used for components such as:

- LCD
- ULN2003 stepper driver
- LCD backlight

### 3.3V

Used to power the RC522.

```text
Mega 3.3V → RC522 3.3V
```

### GND

GND means ground.

All devices need a common electrical reference.

Several SmartGate components connect to the Mega's GND.

---

# 2. RC522 RFID/NFC Reader

The RC522 detects compatible RFID/NFC cards and tags.

When a card is placed near the RC522, the reader detects the card and reads its UID.

The UID currently authorized in SmartGate is:

```text
FA 83 7E 81
```

The Arduino program compares the detected UID with this stored UID.

If they match:

```text
ACCESS GRANTED
```

If they do not match:

```text
ACCESS DENIED
```

---

# 3. RC522 Wiring

The RC522 communicates with the Mega using **SPI communication**.

| RC522 | Mega 2560 | Purpose |
|---|---:|---|
| SDA / SS | 53 | Selects RC522 |
| SCK | 52 | SPI clock |
| MOSI | 51 | Mega → RC522 data |
| MISO | 50 | RC522 → Mega data |
| IRQ | Not connected | Not used |
| GND | GND | Ground |
| RST | 5 | Reset |
| 3.3V | 3.3V | Power |

> **Important:** The RC522 is powered from **3.3V**, not 5V.

---

# 4. How SPI Works

SPI stands for:

**Serial Peripheral Interface**

In this system:

```text
Mega 2560 = Controller / Master
RC522     = Peripheral
```

The main SPI connections are:

```text
MOSI
MISO
SCK
SS
```

---

## MOSI

MOSI means:

**Master Out, Slave In**

It carries information from the Mega to the RC522.

```text
Mega ───────→ RC522
       MOSI
```

On the Mega:

```text
MOSI = Pin 51
```

---

## MISO

MISO means:

**Master In, Slave Out**

It carries information from the RC522 back to the Mega.

```text
Mega ←─────── RC522
       MISO
```

On the Mega:

```text
MISO = Pin 50
```

---

## SCK

SCK is the SPI clock.

```text
Mega ── Clock ──→ RC522
```

The clock keeps both devices synchronized while transferring data.

On the Mega:

```text
SCK = Pin 52
```

---

## SS / SDA

The pin labeled `SDA` on the RC522 is used as the SPI **SS/CS** connection.

It tells the RC522 when the Mega wants to communicate with it.

```text
RC522 SDA/SS → Mega Pin 53
```

---

## RST

RST means reset.

```text
RC522 RST → Mega Pin 5
```

The program uses this connection when initializing the RC522.

---

# 5. Green LED

The green LED represents:

```text
ACCESS GRANTED
```

Connection:

```text
Mega Pin 6
    ↓
220Ω Resistor
    ↓
Green LED
    ↓
GND
```

Arduino code:

```cpp
digitalWrite(GREEN_LED, HIGH);
```

turns the LED on.

Arduino code:

```cpp
digitalWrite(GREEN_LED, LOW);
```

turns it off.

---

# 6. Red LED

The red LED represents:

```text
ACCESS DENIED
```

Connection:

```text
Mega Pin 7
    ↓
220Ω Resistor
    ↓
Red LED
    ↓
GND
```

---

# 7. Why the LEDs Need Resistors

Each LED uses approximately a **220Ω resistor**.

The resistor limits electrical current.

Without the resistor, excessive current could damage:

- The LED
- The Mega output pin

---

# 8. LED Polarity

An LED has positive and negative sides.

Usually:

```text
Long leg  = Anode (+)
Short leg = Cathode (-)
```

Connection:

```text
Mega Pin
   ↓
220Ω Resistor
   ↓
Long LED Leg
   ↓
Short LED Leg
   ↓
GND
```

---

# 9. Buzzer

The buzzer provides audio feedback.

Connection:

```text
Buzzer + → Mega Pin 8
Buzzer - → GND
```

For an authorized card:

```cpp
tone(BUZZER, 1200, 200);
```

This generates approximately:

```text
Frequency = 1200 Hz
Duration  = 200 ms
```

The denied-access sequence uses a lower warning tone.

---

# 10. 16x2 LCD

The LCD displays information about the state of SmartGate.

A 16x2 LCD has:

```text
16 characters per row
2 rows
```

Example standby screen:

```text
NFC PARKING
Tap your card
```

Authorized screen:

```text
WELCOME
HPONE MYAT
```

Unauthorized screen:

```text
ACCESS DENIED
UNKNOWN CARD
```

---

# 11. LCD Wiring

| LCD Pin | Name | Connection |
|---:|---|---|
| 1 | VSS | GND |
| 2 | VDD | 5V |
| 3 | VO | Potentiometer middle pin |
| 4 | RS | Mega 22 |
| 5 | RW | GND |
| 6 | E | Mega 23 |
| 7 | D0 | Not connected |
| 8 | D1 | Not connected |
| 9 | D2 | Not connected |
| 10 | D3 | Not connected |
| 11 | D4 | Mega 24 |
| 12 | D5 | Mega 25 |
| 13 | D6 | Mega 26 |
| 14 | D7 | Mega 27 |
| 15 | A | 5V through resistor |
| 16 | K | GND |

The Arduino LCD configuration is:

```cpp
LiquidCrystal lcd(22, 23, 24, 25, 26, 27);
```

The order means:

```text
22 = RS
23 = Enable
24 = D4
25 = D5
26 = D6
27 = D7
```

---

# 12. LCD RS Pin

RS means:

**Register Select**

It tells the LCD whether the Mega is sending:

```text
A command
```

or:

```text
Character data
```

For example:

```text
Clear screen
```

is a command.

But:

```text
WELCOME
```

is character data.

---

# 13. LCD Enable Pin

The Enable pin is connected to:

```text
Mega Pin 23
```

The Mega first places information on the data lines and then pulses the Enable pin.

This tells the LCD:

```text
Read this data now.
```

---

# 14. LCD Data Pins

SmartGate uses:

```text
D4 → Mega 24
D5 → Mega 25
D6 → Mega 26
D7 → Mega 27
```

These lines carry the binary information needed to display characters.

---

# 15. Why D0-D3 Are Not Connected

The LCD supports:

```text
8-bit mode
```

and:

```text
4-bit mode
```

SmartGate uses **4-bit mode**.

Therefore only:

```text
D4
D5
D6
D7
```

are needed.

The Arduino sends an 8-bit value in two 4-bit sections.

This saves Mega pins.

---

# 16. Potentiometer

A **10k potentiometer** controls LCD contrast.

Connection:

```text
5V ─────┐
        │
    Potentiometer
        │
GND ────┘

Middle Pin
    ↓
LCD VO
```

The two outside potentiometer pins connect to:

```text
5V
GND
```

The center pin connects to:

```text
LCD Pin 3 / VO
```

Turning the potentiometer changes the voltage applied to VO.

This changes how dark the LCD characters appear.

---

# 17. LCD Backlight

The LCD backlight is separate from the LCD communication circuitry.

```text
LCD Pin 15 / A → 5V through resistor
LCD Pin 16 / K → GND
```

Because these systems are separate, it is possible for the LCD backlight to work while no text appears.

If this happens, check:

- Contrast potentiometer
- RS
- Enable
- D4-D7

---

# 18. 28BYJ-48 Stepper Motor

The 28BYJ-48 stepper motor physically moves the parking gate.

Unlike a normal DC motor, a stepper motor moves in controlled increments called **steps**.

This allows SmartGate to control:

- Direction
- Speed
- Rotation amount

---

# 19. ULN2003 Stepper Driver

The Mega should not directly power the stepper motor coils.

Instead SmartGate uses a **ULN2003 driver board**.

The signal path is:

```text
Mega 2560
    ↓
ULN2003 Driver
    ↓
28BYJ-48 Stepper
    ↓
Parking Gate
```

The Mega sends small control signals.

The ULN2003 switches the current required by the motor.

---

# 20. ULN2003 Wiring

| ULN2003 | Mega 2560 |
|---|---:|
| IN1 | 30 |
| IN2 | 32 |
| IN3 | 34 |
| IN4 | 36 |
| + / VCC | 5V |
| - / GND | GND |

The stepper's white 5-pin connector plugs directly into the white socket on the ULN2003 board.

The individual motor wires do not connect directly to Mega GPIO pins.

---

# 21. How the Stepper Moves

The stepper contains several electromagnetic coils.

The controller energizes these coils in sequence.

Conceptually:

```text
Coil 1
  ↓
Coil 2
  ↓
Coil 3
  ↓
Coil 4
  ↓
Repeat
```

Changing the order of this sequence changes the direction of rotation.

---

# 22. Stepper Motor Software

SmartGate defines:

```cpp
const int stepsPerRevolution = 2048;
```

and:

```cpp
Stepper gateMotor(
  stepsPerRevolution,
  30, 34, 32, 36
);
```

The physical wiring is:

```text
IN1 → 30
IN2 → 32
IN3 → 34
IN4 → 36
```

However, the working Stepper library sequence is:

```text
30, 34, 32, 36
```

This ordering is important.

An incorrect sequence can cause the motor to vibrate without rotating correctly.

---

# 23. Opening the Gate

The gate movement amount is currently:

```cpp
const int GATE_STEPS = 500;
```

Opening:

```cpp
gateMotor.step(GATE_STEPS);
```

This moves the stepper in one direction.

---

# 24. Closing the Gate

Closing uses:

```cpp
gateMotor.step(-GATE_STEPS);
```

The negative value reverses the motor direction.

---

# 25. Full SmartGate Operation

When the Arduino starts, the system initializes:

```cpp
SPI.begin();
rfid.PCD_Init();
lcd.begin(16, 2);
gateMotor.setSpeed(5);
```

Then the display shows:

```text
NFC PARKING
Tap your card
```

---

## Step 1 — Detect NFC Card

The program continuously checks:

```cpp
if (!rfid.PICC_IsNewCardPresent()) {
  return;
}
```

If no card is present, nothing happens.

---

## Step 2 — Read Card

When a card appears:

```cpp
if (!rfid.PICC_ReadCardSerial()) {
  return;
}
```

The RC522 reads the UID.

---

## Step 3 — Check UID

The program compares the UID:

```cpp
bool validCard =
  rfid.uid.size == 4 &&
  rfid.uid.uidByte[0] == 0xFA &&
  rfid.uid.uidByte[1] == 0x83 &&
  rfid.uid.uidByte[2] == 0x7E &&
  rfid.uid.uidByte[3] == 0x81;
```

This checks for:

```text
FA 83 7E 81
```

---

# 26. Authorized Access

If:

```cpp
if (validCard)
```

is true, SmartGate performs the authorized sequence.

The LCD displays:

```text
WELCOME
HPONE MYAT
```

The green LED turns on:

```cpp
digitalWrite(GREEN_LED, HIGH);
```

The buzzer sounds:

```cpp
tone(BUZZER, 1200, 200);
```

The gate opens:

```cpp
gateMotor.step(GATE_STEPS);
```

The program waits:

```cpp
delay(3000);
```

Then the motor reverses:

```cpp
gateMotor.step(-GATE_STEPS);
```

The gate closes.

Finally the LCD displays:

```text
THANK YOU
DRIVE SAFE
```

Then SmartGate returns to standby.

---

# 27. Unauthorized Access

If the UID does not match, the program enters the `else` section.

The LCD displays:

```text
ACCESS DENIED
UNKNOWN CARD
```

The red LED turns on:

```cpp
digitalWrite(RED_LED, HIGH);
```

Two warning sounds are generated:

```cpp
tone(BUZZER, 400, 250);
delay(300);
tone(BUZZER, 400, 250);
```

The stepper motor is never commanded to move.

Therefore the gate stays closed.

---

# 28. Complete Signal Flow

```text
                     INPUT
                       │
                  NFC / RFID
                       │
                       ▼
                    RC522
                       │
                    SPI Data
                       │
                       ▼
                ELEGOO Mega 2560
                       │
          ┌────────────┼────────────┐
          │            │            │
          ▼            ▼            ▼
         LCD          LEDs        Buzzer
                                   
                       │
                       ▼
                    ULN2003
                       │
                       ▼
                28BYJ-48 Stepper
                       │
                       ▼
                 Parking Gate
```

---

# 29. Main Pin Summary

| Mega Pin | Device | Function |
|---:|---|---|
| 5 | RC522 | Reset |
| 6 | Green LED | Access granted |
| 7 | Red LED | Access denied |
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

---

# 30. SmartGate Control Concept

The easiest way to understand the entire project is:

```text
SENSE
  ↓
DECIDE
  ↓
ACT
```

### Sense

```text
RC522 detects NFC card
```

### Decide

```text
Mega reads UID
↓
Mega compares UID
↓
Authorized?
```

### Act

Authorized:

```text
Green LED
+ Welcome message
+ Beep
+ Open gate
```

Unauthorized:

```text
Red LED
+ Access denied message
+ Warning beeps
+ Gate stays closed
```

This is the basic hardware and software architecture of the SmartGate parking access system.
