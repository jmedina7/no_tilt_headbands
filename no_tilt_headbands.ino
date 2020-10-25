
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

int S = 0; // count seconds
int M = 1; // count minutes
int H = 0; // count hours

char const *animals[] = {"snake", "dog", "cat", "elephant", "groundhog", "fox", "wolf", "ram", "toucan", "alpaca", "pig", "pigeon", "manatee", "cheetah", "bear", "worm", "goat", "sealion", "centipede", "koala", "octopus", "sheep", "sardine", "cow", "bull", "roach", "oyster", "killer whale", "deer", "horse", "seahorse", "platypus", "whale", "seagull", "lion", "tiger", "hamster", "frog", "bat", "swan", "rat", "falcon", "raven", "bedbug"};
int playerScore = 0;
int RECV_PIN = 8;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  // we are using a 16x2 LCD
  lcd.setCursor(2, 0);
  lcd.print("                             ");
  irrecv.enableIRIn(); // Start the receiver
  irrecv.blink13(true);
  randomSeed(analogRead(0));
}

void loop() {
  lcd.setCursor(6, 1);
  lcd.print(":");
  lcd.setCursor(9, 1);
  lcd.print(":");

  S--;
  delay(1000);

  if (S < 0)
  {
    M--;
    S = 59;
  }
  if (M < 0)
  {
    H--;
    M = 59;
  }
  if (H < 0) {
    H = 23;
    M = 59;
    S = 59;
  } if (M > 9)
  {
    lcd.setCursor(7, 1);
    lcd.print(M);
  }
  else
  {
    lcd.setCursor(7, 1);
    lcd.print("0");
    lcd.setCursor(8, 1);
    lcd.print(M);
    lcd.setCursor(9, 1);
    lcd.print(":");
  }

  if (S > 9)
  {
    lcd.setCursor(10, 1);
    lcd.print(S);
  }
  else
  {
    lcd.setCursor(10, 1);
    lcd.print("0");
    lcd.setCursor(11, 1);
    lcd.print(S);
    lcd.setCursor(12, 1);
    lcd.print(" ");
  }

  if (H > 9)
  {
    lcd.setCursor(4, 1);
    lcd.print (H);
  }
  else
  {
    lcd.setCursor(4, 1);
    lcd.print("0");
    lcd.setCursor(5, 1);
    lcd.print(H);
    lcd.setCursor(6, 1);
    lcd.print(":");
  }

  runGame();
}

void runGame() {
  const size_t n = sizeof(animals) / sizeof(animals[0]);
  shuffle();
  // start text on first row, third column
  for (int i = 0; i < n; i++) {
    lcd.setCursor(2, 0);
    lcd.print("                             ");
    lcd.setCursor(2, 0);
    lcd.print(animals[i]);
    Serial.println(animals[i]);
    while (!irrecv.decode(&results)) {

    }
    Serial.println(results.value);
    Serial.println(results.value, HEX);
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
        Serial.println("invalid keypress");
        i--;
        break;
    }
    irrecv.resume();
    delay(500);
  }
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
