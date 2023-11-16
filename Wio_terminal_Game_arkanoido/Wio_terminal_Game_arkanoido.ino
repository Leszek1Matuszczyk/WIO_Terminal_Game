#include <TFT_eSPI.h>
#include "Free_Fonts.h"
#include <SPI.h>

TFT_eSPI lcd = TFT_eSPI();  // Initialize TFT display

struct hero {
  int posX;
  int posY;
  int sizeX;
  int sizeY;
  byte life;
  uint32_t color;
  byte speed;
  byte direction;
};

struct ball {
  int posX;
  int posY;
  int sizeX;
  int sizeY;
  byte life;
  uint8_t color;
  byte VectorX;
  byte VectorY;
  bool VX;
  bool VY;
};

struct box {
  int posX;
  int posY;
  int sizeX;
  int sizeY;
  uint32_t color;
  byte state;
};

hero Spaceship = {
  120,
  230,
  62,
  8,
  100,
  TFT_WHITE,
  5,
  1
};

ball pong = {
  170,
  200,
  3,
  3,
  10,
  TFT_WHITE,
  0,
  0,
  0,
  0,
};

box Hit[100];
int score = 0;
long int Wait = 0;
byte games = 5;

byte heroMove(hero person) {
  // Read input from buttons
  bool up = digitalRead(WIO_5S_UP);
  bool down = digitalRead(WIO_5S_DOWN);
  bool right = digitalRead(WIO_5S_RIGHT);
  bool left = digitalRead(WIO_5S_LEFT);
  bool press = digitalRead(WIO_5S_PRESS);

  // Move the hero based on button input
  if (up | down | left | right == 0) {
    lcd.fillRect(person.posX, person.posY, person.sizeX, person.sizeY, TFT_BLACK);
    if (up == 0) {
      person.posY = person.posY - person.speed;
      person.direction = 1;
    }
    if (down == 0) {
      person.posY = person.posY + person.speed;
      person.direction = 2;
    }
    if (right == 0) {
      person.posX = person.posX + person.speed;
      person.direction = 3;
    }
    if (left == 0) {
      person.posX = person.posX - person.speed;
      person.direction = 4;
    }

    // Ensure hero stays within screen boundaries
    if (person.posY > 190 & person.posY < 240 - person.sizeY) {
      Spaceship.posY = person.posY;
    } else {
      if (person.posY < 190) {
        person.posY = 191;
      } else {
        person.posY = 239 - person.sizeY;
      }
    }

    if (person.posX > 0 & person.posX < 320 - person.sizeX) {
      Spaceship.posX = person.posX;
    } else {
      if (person.posX < 0) {
        person.posX = 1;
      }
      if (person.posX > 320 - person.sizeX) {
        person.posX = 319 - person.sizeX;
      }
    }
  }

  // Update hero properties
  Spaceship.color = person.color;
  Spaceship.life = person.life;
  Spaceship.posX = person.posX;
  Spaceship.posY = person.posY;
  Spaceship.sizeX = person.sizeX;
  Spaceship.sizeY = person.sizeY;
  Spaceship.speed = person.speed;

  if (person.direction != 0) {
    Spaceship.direction = person.direction;
  }

  // Draw the updated hero on the screen
  lcd.fillRect(Spaceship.posX, Spaceship.posY, Spaceship.sizeX, Spaceship.sizeY, Spaceship.color);
}

byte ballMov(ball pin, hero person) {
  lcd.fillCircle(pin.posX, pin.posY, pin.sizeX, TFT_BLACK);

  // Update ball position based on its vector
  if (pin.VX == 0) {
    pin.posX = pin.posX + pin.VectorX;
    if (pin.posX > 320) { pin.VX = 1; }
  }
  if (pin.VX == 1) {
    pin.posX = pin.posX - pin.VectorX;
    if (pin.posX < 0) { pin.VX = 0; }
  }

  if (pin.VY == 0) {
    pin.posY = pin.posY + pin.VectorY;
    if (pin.posY > 260) { pin.VY = 1; }

    // Check for collision with the hero (spaceship) and update ball direction
    if (person.posX < pin.posX & pin.posX < person.posX + person.sizeX & pin.posY >= person.posY & pin.posY < person.posY + person.sizeY) {
      pin.VY = 1;
      pong.VectorX = random(0, 6);
      pong.VectorY = 8 - pong.VectorX;
    }
  }
  if (pin.VY == 1) {
    pin.posY = pin.posY - pin.VectorY;
    if (pin.posY < 20) { pin.VY = 0; }
  }

  // Update global ball properties
  pong.posX = pin.posX;
  pong.posY = pin.posY;
  pong.VX = pin.VX;
  pong.VY = pin.VY;

  // Draw the updated ball on the screen
  lcd.fillCircle(pin.posX, pin.posY, pin.sizeX, pin.color);
}

byte Target(int posX, int posY, int sizeX, int sizeY, uint32_t filling, byte state, byte grid) {
  if (Hit[grid].state > 0) {
    // Check for collision with the ball and update game state and score
    if (posX - 5 < pong.posX & pong.posX < posX + sizeX + 5 & pong.posY >= posY - 5 & pong.posY < posY) {
      pong.VY = 1;
      Hit[grid].state = Hit[grid].state - 1;
      score = score + 50;
    }

    if (posX - 5 < pong.posX & pong.posX < posX + sizeX + 5 & pong.posY >= posY + sizeY & pong.posY < posY + sizeY + 5) {
      pong.VY = 0;
      Hit[grid].state = Hit[grid].state - 1;
      score = score + 50;
    }
    if (posX - 6 < pong.posX & pong.posX < posX & pong.posY >= posY & pong.posY < posY + sizeY) {
      pong.VX = 1;
      Hit[grid].state = Hit[grid].state - 1;
      score = score + 50;
    }
    if (posX + sizeX < pong.posX & pong.posX < posX + sizeX + 7 & pong.posY >= posY & pong.posY < posY + sizeY) {
      pong.VX = 0;
      Hit[grid].state = Hit[grid].state - 1;
      score = score + 50;
    }

    // Draw the target on the screen
    lcd.fillRect(posX, posY, sizeX, sizeY, filling);
    Serial.println(pong.VX);
  } else {
    // Clear the target from the screen if its state is 0
    lcd.fillRect(posX, posY, sizeX, sizeY, TFT_BLACK);
  }
}

byte points(int point) {
  // Display the current score and remaining balls on the screen
  lcd.fillRect(0, 0, 340, 17, TFT_CYAN);
  lcd.setCursor(0, 12);
  lcd.setTextColor(TFT_BLACK);
  lcd.setFreeFont(FF1);
  lcd.print("Score: ");
  lcd.print(score);
  lcd.setCursor(140, 12);
  lcd.print("Balls: ");
  lcd.print(games);
}

void setup() {
  lcd.init();
  lcd.setRotation(3);

  // Display the introductory screen
  lcd.fillScreen(TFT_BLACK);
  lcd.setCursor(2, 12);
  lcd.setTextColor(TFT_WHITE);
  lcd.setFreeFont(FF1);
  lcd.print("Simple game Arkanoid style\ncreated using Arduino IDE.\n      Have fun playing!" );
  lcd.setCursor(40, 120);
  lcd.setTextColor(TFT_WHITE);
  lcd.setFreeFont(FF4);
  lcd.print("Arkanoido");
  lcd.setCursor(25, 132);
  lcd.setFreeFont(FF1);
  lcd.print("Leszek Entertainment Corp.");
  lcd.println();
  lcd.print("");
  delay(15000);
  lcd.fillScreen(TFT_BLACK);

  // Set up input pins
  pinMode(WIO_5S_UP, INPUT_PULLUP);
  pinMode(WIO_5S_DOWN, INPUT_PULLUP);
  pinMode(WIO_5S_LEFT, INPUT_PULLUP);
  pinMode(WIO_5S_RIGHT, INPUT_PULLUP);
  pinMode(WIO_5S_PRESS, INPUT_PULLUP);
  Serial.begin(9600);

  // Initialize game boxes
  for (int j = 1; j < 7; j++) {
    for (int i = 1; i < 15; i++) {
      Hit[i - 1 + j * 14].posX = 20 * i;
      Hit[i - 1 + j * 14].posY = 30 + 10 * j;
      Hit[i - 1 + j * 14].sizeX = 20;
      Hit[i - 1 + j * 14].sizeY = 10;
      Hit[i - 1 + j * 14].color = TFT_BLUE + 800 * i * j;
      Hit[i - 1 + j * 14].state = 1;
    }
  }
}

void loop() {
  // Update hero and targets, draw score, and handle ball movement
  if (millis() > Wait + 1) {
    heroMove(Spaceship);

    for (int i = 0; i < 99; i++) {
      Target(Hit[i].posX, Hit[i].posY, Hit[i].sizeX, Hit[i].sizeY, Hit[i].color, Hit[i].state, i);
    }
    points(score);
    ballMov(pong, Spaceship);
    Serial.println(Spaceship.posY);

    // Handle ball out-of-bounds
    if (pong.posY > 250) {
      games--;
      pong.posX = 170;
      pong.posY = 200;
      pong.VectorX = 0;
      pong.VectorY = 0;
    }

    // Game over condition
    while (games == 0) {
      lcd.fillScreen(TFT_BLACK);
      lcd.setCursor(40, 120);
      lcd.setTextColor(TFT_WHITE);
      lcd.setFreeFont(FF4);
      lcd.print("Game over");
      lcd.setCursor(25, 132);
      lcd.setFreeFont(FF1);
      lcd.print("To play again press reset");
      while (1) {};
    }

    // Win condition
    while (score >= 4200) {
      lcd.fillScreen(TFT_BLACK);
      lcd.setCursor(40, 120);
      lcd.setTextColor(TFT_WHITE);
      lcd.setFreeFont(FF4);
      lcd.print("You Win!");
      lcd.setCursor(25, 132);
      lcd.setFreeFont(FF1);
      lcd.print("To play again press reset");
      while (1) {};
    }

    Wait = millis();
  }
}
