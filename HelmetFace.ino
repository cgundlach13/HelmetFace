
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Duo happy
#endif

#define PIN 6

char Msg1[] = "OwO";

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_GRBW    Pixels are wired for GRBW bitstream (RGB+W NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)


// Example for NeoPixel Shield.  In this application we'd like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino.  When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order.  The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, 6,
NEO_MATRIX_BOTTOM + NEO_MATRIX_RIGHT +
NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
NEO_GRB + NEO_KHZ800);

struct RGB {
  byte r;
  byte g;
  byte b;
};

// Define some colors we'll use frequently
RGB white = { 255, 255, 255 };
RGB red = { 255, 0, 0 };
RGB orange = { 255, 69, 0};
RGB yellow = {255, 255, 0};
RGB green = { 0, 255, 0};
RGB cyan = {0, 229, 229};
RGB blue = { 0, 0, 255};
RGB purple = { 106, 13, 173};

RGB off = { 0, 0, 0 };

const uint16_t colors[] = {
  matrix.Color(255, 69, 0), matrix.Color(0, 255, 0), matrix.Color(255, 255, 255), matrix.Color(0, 229, 229), matrix.Color(255, 0, 0) };

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(100);
  matrix.setTextColor(colors[1]);
}

int x    = matrix.width();
int pass = 0;

void loop() {

  matrix.setTextColor(colors[3]);
  scrollText("PLS DON'T HIT ME");
  delay(100);

  matrix.fillScreen(0);
  drawRainbowFace(2);
  drawRainbowFace(2);
  drawRainbowFace(2);
  drawRainbowFace(2);
  

//  drawFace(red);
//  delay(10000);
//
//  scrollText("pls don't hit me");
//  delay(100);
//  
//  matrix.fillScreen(0);
//  drawFace(green);
//  delay(10000);
}


void scrollText(String textToDisplay) {
  int x = matrix.width();

  // Account for 6 pixel wide characters plus a space (7). Ended up needing the +4 to string length to make the whole message scroll off before it reset.
  int pixelsInText = (textToDisplay.length() + 4) * 7;

  matrix.setCursor(x, 0);
  matrix.print(textToDisplay);
  matrix.show();

  while(x > (matrix.width() - pixelsInText)) {
    matrix.fillScreen(0);
    matrix.setCursor(--x, 0);
    matrix.print(textToDisplay);
    matrix.show();
    delay(40);
  }
}


void fadePixel(int x, int y, RGB startColor, RGB endColor, int steps, int wait) {
  for(int i = 0; i <= steps; i++) 
  {
     int newR = startColor.r + (endColor.r - startColor.r) * i / steps;
     int newG = startColor.g + (endColor.g - startColor.g) * i / steps;
     int newB = startColor.b + (endColor.b - startColor.b) * i / steps;

     matrix.drawPixel(x, y, matrix.Color(newR, newG, newB));
     matrix.show();
     delay(wait);
  }
}



void drawFace(RGB faceColor) {
  
int face[8][32] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
  {1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1},
  {0,0,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,0,0},
  {0,0,0,1,1,1,0,0,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,0,0,1,1,1,0,0,0},
  {0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

//Top to bottom pixel changes
//for(int row = 0; row < 8; row++) {
//    for(int column = 0; column < 32; column++) {
//     if(face[row][column] == 1) {
//       fadePixel(column, row, white, faceColor, 1, 0);
//     }
//   }
//  }

//Side to side pixel changes
for(int column = 0; column < 32; column++) {
    for(int row = 0; row < 8; row++) {
     if(face[row][column] == 1) {
       fadePixel(column, row, white, faceColor, 1, 0);
     }
   }
  }

}


void drawRainbowFace(int Timer) {

    
    drawFace(red);
    delay(Timer);
    drawFace(orange);
    delay(Timer);
    drawFace(yellow);
    delay(Timer);
    drawFace(green);
    delay(Timer);
    drawFace(cyan);
    delay(Timer);
    drawFace(blue);
    delay(Timer);
    drawFace(purple);
    delay(Timer);
}
