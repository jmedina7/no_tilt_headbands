
/*
   Remote codes
   >>| (SKIP) FFC23D
   >|| (play) FF02FD
   0 FF6897
   1 FF30CF
   2 FF18E7
*/

#include <IRremote.h>
#include <LiquidCrystal.h>
#include <TimeLib.h>
LiquidCrystal lcd = LiquidCrystal(2, 3, 4, 5, 6, 7);
char buffer[30];

char const *animals[] = {"snake", "dog", "cat", "elephant", "groundhog", "fox", "wolf", "ram", "toucan", "alpaca", "pig", "pigeon", "manatee", "cheetah", "bear", "worm", "goat", "sealion", "centipede", "koala", "octopus", "sheep", "sardine", "cow", "bull", "roach", "oyster", "killer whale", "deer", "horse", "seahorse", "platypus", "whale", "seagull", "lion", "tiger", "hamster", "frog", "bat", "swan", "rat", "falcon", "raven", "bedbug"};
int playerScore = 0;
int RECV_PIN = 8;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long endTime;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  // we are using a 16x2 LCD
  lcd.setCursor(2, 0);
  lcd.clear();
  irrecv.enableIRIn(); // Start the receiver
  irrecv.blink13(true);
  randomSeed(analogRead(0));
  runGame();
}

void loop() {

}

void runGame() {
  const size_t n = sizeof(animals) / sizeof(animals[0]);
  shuffle();
  endTime = millis() + 60000;
  // start text on first row, third column
  for (int i = 0; i < n; i++) {
    if (millis() > endTime) {
      break;
    }
    lcd.clear();
    lcd.print(animals[i]);
    Serial.println(animals[i]);
    while (!irrecv.decode(&results)) {
      if (millis() > endTime) {
        break;
      }
    }
    if (millis() > endTime) {
      break;
    }
    Serial.println(results.value);
    switch (results.value) {
      case 16712445:
        Serial.println("play");
        playerScore++;
        Serial.println(playerScore);
        break;
      case 16761405:
        Serial.println("skip");
        break;
      default:
        i--;
        break;
    }
    irrecv.resume();
    delay(500);
  }
  lcd.clear();
  lcd.print("Times up!");
  delay(1500);
  lcd.clear();
  lcd.print("Score: ");
  lcd.print(playerScore, DEC);
  lcd.setCursor(1, 1);
  lcd.print("Game over");
  delay(3000);
}

void shuffle() {
  const size_t n = sizeof(animals) / sizeof(animals[0]);
  for (size_t i = 0; i < n - 1; i++)
  {
    size_t j = random(0, n - i);

    const char *t = animals[i];
    animals[i] = animals[j];
    animals[j] = t;
  }
}
