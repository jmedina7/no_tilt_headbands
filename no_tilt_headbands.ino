
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

int setupHours = 0;     // How many hours will count down when started
int setupMinutes = 1;   // How many minutes will count down when started
int setupSeconds = 0;   // How many seconds will count down when started
time_t setupTime = 0;

int currentHours = 0;
int currentMinutes = 0;
int currentSeconds = 0;
time_t currentTime = 0;

time_t startTime = 0;
time_t elapsedTime = 0;

void timer() {
  lcd.print("Counting down...");
  lcd.setCursor(0, 1);
  if (hour(currentTime) < 10) lcd.print("0");
  lcd.print(hour(currentTime));
  lcd.print(":");
  if (minute(currentTime) < 10) lcd.print("0");
  lcd.print(minute(currentTime));
  lcd.print(":");
  if (second(currentTime) < 10) lcd.print("0");
  lcd.print(second(currentTime));
}
