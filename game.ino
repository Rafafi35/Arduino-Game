#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include <Wire.h>

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
const int BUTTON_LEFT_PRESSED = 400;
const int BUTTON_RIGHT_PRESSED = 600;
const int IO_BUTTON_UP = 4;
const int IO_BUTTON_DOWN = 7;
const int PIN_ADC_TASTEN_LEFT_RIGHT = A3;
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
  Serial.begin(9600);
  Serial.println("Start Hello World");
  matrix.begin(0x70);
  matrix.setBrightness(0.1);
  pinMode(IO_BUTTON_DOWN, INPUT);
  pinMode(IO_BUTTON_UP, INPUT);
}

void loop() {
  gameActive = true;
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
      // ADC-Werte für Links/Rechts-Bewegung kontinuierlich lesen
      int adc_tastenLR = analogRead(PIN_ADC_TASTEN_LEFT_RIGHT);
      int status_left = 0;
      int status_right = 0;
      
      // Verbesserte Tastenerkennung basierend auf ADC-Werten
      if (adc_tastenLR < 250) {
        status_left = 0;
        status_right = 0;
      } else if (adc_tastenLR < 575) {
        status_left = 1;
        status_right = 0;
      } else if (adc_tastenLR < 725) {
        status_left = 0;
        status_right = 1;
      } else {
        status_left = 1;
        status_right = 1;
      }

      // Spielerbewegung links/rechts
      if (status_left) {
        if (positionx <= 0) {
          positionx = 7;
        } else {
         positionx = positionx - 1; 
        }
      }

      if (status_right) {
        if (positionx >= 7) {
          positionx = 0;
        } else {
          positionx = positionx + 1;
        }
      }

      // Matrix löschen und Spieler zeichnen
      matrix.clear();
      matrix.drawPixel(positionx, positiony, 1);

      // Hindernisse zeichnen
      matrix.drawPixel(a, z, 1);
      matrix.drawPixel(b, z - 2, 1);
      matrix.drawPixel(c, z - 4, 1);
      matrix.drawPixel(d, z - 6, 1);
      matrix.drawPixel(e, z - 8, 1);
      matrix.drawPixel(f, z - 10, 1);
      matrix.drawPixel(g, z - 12, 1);
      matrix.drawPixel(h, z - 14, 1);
      
      matrix.writeDisplay();

      // Kollisionserkennung
      if ((a == positionx && z == positiony) ||
          (b == positionx && z - 2 == positiony) ||
          (c == positionx && z - 4 == positiony) ||
          (d == positionx && z - 6 == positiony) ||
          (e == positionx && z - 8 == positiony) ||
          (f == positionx && z - 10 == positiony) ||
          (g == positionx && z - 12 == positiony) ||
          (h == positionx && z - 14 == positiony)) {
        
        matrix.clear();
        matrix.print(score);
        matrix.writeDisplay();
        delay(2000);
        gameActive = false;
        exit(0);
        return; // Verwende return statt exit(0)
      }

      Serial.print("ADC L/R: ");
      Serial.print(adc_tastenLR);
      Serial.print(" | Matrix: ");
      Serial.print(" | Pos: ");
      Serial.print(positionx);
      Serial.print(",");
      Serial.println(positiony);
      
      delay(geschwindigkeit);
    }

    score++; // Score erhöhen nach jeder überstandenen Runde

    // Geschwindigkeit erhöhen
    if (geschwindigkeit > minGeschwindigkeit) {
      geschwindigkeit = geschwindigkeit - 2;
    }
  }
}

void displayTime(unsigned time, String ajay) {
  if (!gameActive) {
    for (int y = 8; y >= -53; y--) {
      matrix.clear();
      matrix.setCursor(y, 0);
      matrix.writeDisplay();
      delay(67);
    }
  }
}