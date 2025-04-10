#include <avr/wdt.h>

volatile bool buttonFlag = false;
volatile bool wdtFlag = false;
volatile bool serialFlag = false;

volatile int counter = 0;
const int buttonPin = 2;
volatile int wdtCounter = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);

  cli();  // Disable interrupts
  wdt_reset();
  MCUSR = 0;
  WDTCSR |= (1 << WDCE) | (1 << WDE);
  WDTCSR = (1 << WDIE) | (1 << WDP3) | (1 << WDP0);  // 8s interrupt mode
  sei();  // Enable interrupts

  attachInterrupt(digitalPinToInterrupt(buttonPin), handleButtonInterrupt, FALLING);
}

void loop() {
  // Priority 1: Button event
  if (buttonFlag) {
    buttonFlag = false;
    counter = 1;
    Serial.println("Button pressed");
  }

  // Priority 2: Watchdog timer
  else if (wdtFlag) {
    wdtFlag = false;
    wdtCounter = 0;
    counter = 0;
    Serial.println("Watchdog timer reset");
  }

  // Priority 3: Serial input
  else if (Serial.available() > 0) {
    char number = Serial.read();
    if (number == '2') {  // Use '==' not '='
      counter = 2;
      Serial.println("Serial monitor read");
    }
  }

  // LED logic
  switch (counter) {
    case 0:
      digitalWrite(6, HIGH);
      delay(1000);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      digitalWrite(8, LOW);
      break;
    case 1:
      digitalWrite(8, HIGH);
      delay(1000);
      digitalWrite(8, LOW);
      digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      break;
    case 2:
      digitalWrite(7, HIGH);
      delay(1000);
      digitalWrite(8, LOW);
      digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      break;
  }
}

// High priority interrupt
void handleButtonInterrupt() {
  buttonFlag = true;
}

// Medium priority: Watchdog ISR
ISR(WDT_vect) {
  wdtCounter++;
  if (wdtCounter >= 1) {
    wdtFlag = true;
  }
}
