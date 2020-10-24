
/*
 * Remote codes
 * >>| (SKIP) FFC23D
 * >|| (play) FF02FD
 * 0 FF6897
 * 1 FF30CF
 * 2 FF18E7
 */

#include <IRremote.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd = LiquidCrystal(2, 3, 4, 5, 6, 7);

char const *animals[] = {"snake", "dog", "cat", "elephant", "groundhog", "fox", "wolf"};
int playerScore = 0;
int RECV_PIN = 8;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  // we are using a 16x2 LCD
  irrecv.enableIRIn(); // Start the receiver
  irrecv.blink13(true);
}

void loop() {
  if (irrecv.decode(&results))
  {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  // start text on first row, third column
  for (int i = 0; i < 7; i++) {
    lcd.setCursor(2, 0);
    lcd.print(animals[i]);
    delay(1000);
  }
}