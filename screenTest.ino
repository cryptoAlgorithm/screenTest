// the setup function runs once when you press reset or power the board

#include <Arduino.h>
#include <SPI.h>

#include <Adafruit_GFX.h>
#include <Waveshare_ILI9486.h>
#include "raleway12pt.h"
#include "raleway24pt.h"
#include "raleway36pt.h"

// RTC
#include "RTClib.h"
RTC_DS1307 rtc;

// Common 16-bit colors
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GRAY    0x8410
#define ACCENT  0x1338
#define SEC_A   0xF4E1
#define RAISED  0x4228

// Launcher colors
#define L_DBLUE 0x0A34 // Dark blue
#define L_GREEN 0x2BE6 // Green
#define L_CYAN  0x0411 // Cyan
#define L_PINK  0xA8AA // Dark pink
#define L_BROWN 0x6A68 // Brown
#define L_DRED  0xB0E3 // Dark red

// UI constants
#define BTN_HEIGHT 40
#define UI_MG      10
#define BASE_FS    12
#define N_RADIUS   7
#define L_RADIUS   12
#define VERSION    "0-2-1"

// State vars
uint8_t state = 0;

namespace
{
    Waveshare_ILI9486 scn;
}

// Update loop
void tick() {
  switch (state) {
    case 1:
      clockTick();
      break;
  }
}

bool hb_state = 0;
void setup() 
{
    SPI.begin();
    scn.begin();

    scn.setRotation(3);
    scn.setFont(&Raleway12pt);

    drawLauncher();

    // Init RTC
    rtc.begin();

    pinMode(LED_BUILTIN, OUTPUT);

    /* Debug */
    /*SerialUSB.begin(0);
    while(!SerialUSB);
    SerialUSB.println("Hi");*/
}

int i = 0;

// the loop function runs over and over again until power down or reset
void loop()
{
    //  Get raw touchscreen values.
    TSPoint p = scn.getPoint();

    //  Remaps raw touchscreen values to screen co-ordinates.  Automatically handles
    //  rotation!
    scn.normalizeTsPoint(p);

    // Check if in hitbox
    switch (state) {
      case 0:
        launcherHitbox(p);
        break;
      case 1:
        if (p.x > scn.width() - BTN_HEIGHT && p.y < BTN_HEIGHT) drawMenu();
        else if (p.x < BTN_HEIGHT && p.y < BTN_HEIGHT) drawLauncher();
        break;
      case 2:
        if (p.x > scn.width() - BTN_HEIGHT && p.y < BTN_HEIGHT) drawClock();
        break;
      case 3:
        drawHitbox(p);
        break;
      case 4:
        if (p.x < BTN_HEIGHT && p.y < BTN_HEIGHT + UI_MG / 2 && p.y > UI_MG / 2) drawLauncher();
        break;
      case 5:
        if (p.x < BTN_HEIGHT && p.y < BTN_HEIGHT + UI_MG / 2 && p.y > UI_MG / 2) drawLauncher();
        break;
    }

    if (millis() % 1000 == 0) {
      tick();
      digitalWrite(LED_BUILTIN, hb_state);
      hb_state = !hb_state;
    }
}
