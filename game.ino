#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include <Wire.h>

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
const int BUTTON_LEFT_PRESSED = 400;
const int BUTTON_RIGHT_PRESSED = 600;
const int IO_BUTTON_UP = 4;
const int IO_BUTTON_DOWN = 7;
const int AIO_BUTTON_MATRIX = 3;

bool gameActive = false;
unsigned long startTime = 0;

int geschwindigkeit = 120;
int minGeschwindigkeit = 50;
int positionx = 3;
int positiony = 7;
int score = 0;

int a, b, c, d, e, f, g, h;

void setup() {
  score = 0;
  Serial.begin(115200);
  Serial.println("Start Hello World");
  matrix.begin(0x70);
  matrix.setBrightness(0.1);
  pinMode(BUTTON_LEFT_PRESSED, INPUT);
  pinMode(BUTTON_RIGHT_PRESSED, INPUT);
  pinMode(IO_BUTTON_DOWN, INPUT);
  pinMode(IO_BUTTON_UP, INPUT);
}

void loop() {
  gameActive = true;
  score = 0;
  startTime = millis();
   if (!gameActive) {
    unsigned long endTime = millis();
    unsigned long elapsedTime = endTime - startTime;
    String ajay = String(elapsedTime);
    displayTime(elapsedTime, ajay);
  }

  while (gameActive) {
    a = random(0, 8);
    b = random(0, 8);
    c = random(0, 8);
    d = random(0, 8);
    e = random(0, 8);
    f = random(0, 8);
    g = random(0, 8);
    h = random(0, 8);

    for (int z = 0; z <= 21; z++) {
      // Spielerbewegung
      if (analogRead(AIO_BUTTON_MATRIX) == 511) {
        positionx = positionx - 1;
        delay(50);
        if (positionx < 0) {
          positionx = 0;
        }
      }

      if (analogRead(AIO_BUTTON_MATRIX) == 695) {
        positionx = positionx + 1;
        delay(50);
        if (positionx > 7) {
          positionx = 7;
        }
      }

      if (analogRead(AIO_BUTTON_MATRIX) == 7) {
        positiony = positiony - 1;
        if (positiony < 0) {
          positiony = 0;
        }
      }

      if (analogRead(AIO_BUTTON_MATRIX) == 4) {
        positiony = positiony + 1;
        if (positiony > 7) {
          positiony = 7;
        }
      }

      matrix.drawPixel(positionx, positiony, 1);
      matrix.drawPixel(positionx - 1, positiony, 0);
      matrix.drawPixel(positionx + 1, positiony, 0);
      matrix.drawPixel(positionx, positiony - 1, 0);
      matrix.drawPixel(positionx, positiony + 1, 0);

      matrix.drawPixel(a, z, 1);
      matrix.drawPixel(b, z - 2, 1);
      matrix.drawPixel(c, z - 4, 1);
      matrix.drawPixel(d, z - 6, 1);
      matrix.drawPixel(e, z - 8, 1);
      matrix.drawPixel(f, z - 10, 1);
      matrix.drawPixel(g, z - 12, 1);
      matrix.drawPixel(h, z - 14, 1);
      matrix.writeDisplay();

      matrix.drawPixel(a, z, 0);
      matrix.drawPixel(b, z - 2, 0);
      matrix.drawPixel(c, z - 4, 0);
      matrix.drawPixel(d, z - 6, 0);
      matrix.drawPixel(e, z - 8, 0);
      matrix.drawPixel(f, z - 10, 0);
      matrix.drawPixel(g, z - 12, 0);
      matrix.drawPixel(h, z - 14, 0);

      if (a == positionx && z == positiony) {
        matrix.print(score);
        matrix.writeDisplay();
        delay(2000);
        gameActive = false;
        exit(0);
      }

      if (b == positionx && z - 2 == positiony) {
        matrix.print(score);
        matrix.writeDisplay();
        delay(2000);
        gameActive = false;
        exit(0);
      }

      if (c == positionx && z - 4 == positiony) {
        matrix.print(score);
        matrix.writeDisplay();
        delay(2000);
        gameActive = false;
        exit(0);
      }

      if (d == positionx && z - 6 == positiony) {
        matrix.print(score);
        matrix.writeDisplay();
        delay(2000);
        gameActive = false;
        exit(0);
      }

      if (e == positionx && z - 8 == positiony) {
        matrix.print(score);
        matrix.writeDisplay();
        delay(2000);
        gameActive = false;
        exit(0);
      }

      if (f == positionx && z - 10 == positiony) {
        matrix.print(score);
        matrix.writeDisplay();
        delay(2000);
        gameActive = false;
        exit(0);
      }

      if (g == positionx && z - 12 == positiony) {
        matrix.print(score = score);
        matrix.writeDisplay();
        delay(2000);
        gameActive = false;
        exit(0);
      }

      if (h == positionx && z - 14 == positiony) {
        matrix.print(score);
        matrix.writeDisplay();
        delay(2000);
        gameActive = false;
        exit(0);
      }

      Serial.println(analogRead(AIO_BUTTON_MATRIX));
      delay(geschwindigkeit);
    }

    Serial.println(analogRead(AIO_BUTTON_MATRIX));

    if (geschwindigkeit > minGeschwindigkeit) {
      geschwindigkeit = geschwindigkeit - 10;
    }
  }
}

void displayTime(unsigned time, String ajay) {
  if (!gameActive){
  for (int y = 8; y >= -53; y--) {
    matrix.clear();
    matrix.setCursor(y, 0);
    matrix.print("error");
    matrix.writeDisplay();
    delay(67);
  }
  }
}

