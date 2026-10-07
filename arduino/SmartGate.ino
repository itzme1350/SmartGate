#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <Stepper.h>

// --------------------
// RC522
// --------------------
#define SS_PIN 53
#define RST_PIN 5

MFRC522 rfid(SS_PIN, RST_PIN);

// --------------------
// LEDs + Buzzer
// --------------------
#define GREEN_LED 6
#define RED_LED 7
#define BUZZER 8

// --------------------
// LCD
// RS, E, D4, D5, D6, D7
// --------------------
LiquidCrystal lcd(22, 23, 24, 25, 26, 27);

// --------------------
// Stepper Motor
// --------------------
const int stepsPerRevolution = 2048;

Stepper gateMotor(
  stepsPerRevolution,
  30, 34, 32, 36
);

const int GATE_STEPS = 500;

// --------------------
// Helper Functions
// --------------------
void showReady() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("NFC PARKING");

  lcd.setCursor(0, 1);
  lcd.print("Tap your card");
}

void openGate() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GATE OPENING");

  gateMotor.step(GATE_STEPS);
}

void closeGate() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GATE CLOSING");

  gateMotor.step(-GATE_STEPS);
}

// --------------------
// Setup
// --------------------
void setup() {
  Serial.begin(9600);

  SPI.begin();
  rfid.PCD_Init();

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  lcd.begin(16, 2);

  gateMotor.setSpeed(5);

  showReady();

  Serial.println("NFC PARKING ACCESS SYSTEM");
  Serial.println("Tap your card...");
}

// --------------------
// Main Loop
// --------------------
void loop() {

  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  bool validCard =
    rfid.uid.size == 4 &&
    rfid.uid.uidByte[0] == 0xFA &&
    rfid.uid.uidByte[1] == 0x83 &&
    rfid.uid.uidByte[2] == 0x7E &&
    rfid.uid.uidByte[3] == 0x81;

  if (validCard) {

    Serial.println("Hpone Myat,ACCESS GRANTED");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WELCOME");

    lcd.setCursor(0, 1);
    lcd.print("HPONE MYAT");

    digitalWrite(GREEN_LED, HIGH);

    tone(BUZZER, 1200, 200);

    delay(1500);

    openGate();

    delay(3000);

    closeGate();

    digitalWrite(GREEN_LED, LOW);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("THANK YOU");

    lcd.setCursor(0, 1);
    lcd.print("DRIVE SAFE");

    delay(1500);
  }

  else {

    Serial.println("UNKNOWN CARD,ACCESS DENIED");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ACCESS DENIED");

    lcd.setCursor(0, 1);
    lcd.print("UNKNOWN CARD");

    digitalWrite(RED_LED, HIGH);

    tone(BUZZER, 400, 250);
    delay(300);

    tone(BUZZER, 400, 250);

    delay(1500);

    digitalWrite(RED_LED, LOW);
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  delay(500);

  showReady();
}
