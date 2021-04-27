const PROGMEM char months[][4] {
  "Jan",
  "Feb",
  "Mar",
  "Apr",
  "May",
  "Jun",
  "Jul",
  "Aug",
  "Sep",
  "Oct",
  "Nov",
  "Dec",
};

const PROGMEM char daysOfTheWeek[7][10] = {
  "Sunday", 
  "Monday", 
  "Tuesday", 
  "Wednesday",
  "Thursday", 
  "Friday", 
  "Saturday"
};

GFXcanvas1 clockText(135, 108); // Canvas for digital text

uint16_t eraseVals[][2] = {
  {UI_MG * 10, UI_MG * 10}, {UI_MG * 10, UI_MG * 10}, {UI_MG * 10, UI_MG * 10}
};

void drawClock() {
  state = 1;
  
  scn.fillScreen(BLACK);

  // Init digital text canvas
  clockText.setFont(&Raleway12pt);

  // Back button
  scn.drawRoundRect(0, 0, BTN_HEIGHT, BTN_HEIGHT, L_RADIUS, GRAY); // Close button
  drawBack(0, 0, BTN_HEIGHT);
  
  scn.fillRoundRect(scn.width() - BTN_HEIGHT, 0, BTN_HEIGHT, BTN_HEIGHT, 8, ACCENT);
  drawMenu(scn.width() - BTN_HEIGHT, 0, BTN_HEIGHT);

  const uint16_t r = (scn.height() - UI_MG * 2) / 2;
  scn.drawCircle(r + UI_MG, r + UI_MG, r, WHITE);

  // Calculate and draw the markings around the clock
  for (uint16_t deg = 0; deg <= 360; deg += 30) {
    uint16_t s = (scn.height() - UI_MG * 2) / 2 - UI_MG * 3 + 2;
    if (deg % 90 == 0) s -= UI_MG;
    const uint16_t e = (scn.height() - UI_MG * 2) / 2 - 1;
    const uint16_t sx = s * cos(radians(deg)) + r + UI_MG;
    const uint16_t sy = s * sin(radians(deg)) + r + UI_MG;
    const uint16_t ex = e * cos(radians(deg)) + r + UI_MG;
    const uint16_t ey = e * sin(radians(deg)) + r + UI_MG;
    scn.drawLine(sx, sy, ex, ey, GRAY);
  }

  // Draw a raised round rect for the text portion
  const uint16_t rw = scn.width() - 150 - UI_MG / 2;
  scn.fillRoundRect(rw, BTN_HEIGHT + UI_MG, scn.width() - rw, 
                    scn.height() - BTN_HEIGHT - UI_MG, 7, RAISED);
  scn.drawFastHLine(rw, BTN_HEIGHT + UI_MG * 2 + 109, scn.width() - rw, GRAY);
  
  clockTick(); // Update clock when UI is drawn
}

void clockTick() {
  const uint16_t r = scn.height() / 2;
  DateTime now = rtc.now();
  uint8_t hr       = now.hour();
  if (hr > 12) hr -= 12;
  const int16_t sd = now.second() * 6 - 90;
  const int16_t md = now.minute() * 6 - 90;
  const int16_t hd = now.hour() * 30 - 90;
  const uint16_t d = (scn.height() - UI_MG * 2) / 2 - UI_MG * 4;
  // Second
  const uint16_t sx = d * cos(radians(sd)) + r;
  const uint16_t sy = d * sin(radians(sd)) + r;
  // Minute
  const uint16_t mx = (d - UI_MG * 2) * cos(radians(md)) + r;
  const uint16_t my = (d - UI_MG * 2) * sin(radians(md)) + r;
  // Hour
  const uint16_t hx = (d - UI_MG * 4) * cos(radians(hd)) + r;
  const uint16_t hy = (d - UI_MG * 4) * sin(radians(hd)) + r;

  // Remove previous "hands" (if position has changed)
  for (uint8_t i = 0; i < 3; i++) {
    const uint16_t x = eraseVals[i][0];
    const uint16_t y = eraseVals[i][1];
    uint16_t nx = 0;
    uint16_t ny = 0;
    uint16_t col = BLACK;
    switch (i) {
      case 0:
      nx = sx;
      ny = sy;
      col = RED;
      break;
      case 1:
      nx = mx;
      ny = my;
      col = BLUE;
      break;
      case 2:
      nx = hx;
      ny = hy;
      col = GREEN;
      break;
    }

    scn.drawLine(r, r, nx, ny, col);
    
    if (x == nx && y == ny) continue;
    
    eraseVals[i][0] = nx;
    eraseVals[i][1] = ny;
    
    scn.drawLine(r, r, x, y, BLACK);
  }
  
  // Draw that dot in the center
  scn.fillCircle(r, r, 4, MAGENTA);

  // Also update "digital" clock
  // Using a canvas here for flicker-free updating 150

  // Clear the canvas
  clockText.fillScreen(BLACK);
  clockText.setCursor(0, BASE_FS + 4);

  // Format the text
  char s[3], m[3], h[3];
  snprintf(s, 3, "%02d", now.second());
  snprintf(m, 3, "%02d", now.minute());
  snprintf(h, 3, "%02d", now.hour());
  
  // Then write some new text
  clockText.print(h); clockText.print(F(":")); clockText.print(m);
  clockText.print(F(":")); clockText.println(s);
  clockText.print(daysOfTheWeek[now.dayOfTheWeek()]); clockText.print(F(" "));
  clockText.println(now.day());
  clockText.print(months[now.month() - 1]); clockText.print(F(" ")); 
  clockText.println(now.year());

  scn.drawBitmap(scn.width() - 150 + UI_MG / 2, BTN_HEIGHT + UI_MG * 2, clockText.getBuffer(), 
                 135, 108, WHITE, RAISED);
}


void drawMenu() {
  state = 2;
  
  scn.fillScreen(BLACK);
  scn.drawRoundRect(scn.width() - BTN_HEIGHT, 0, BTN_HEIGHT, BTN_HEIGHT, 12, GRAY);

  drawCross(scn.width() - BTN_HEIGHT, scn.width());

  scn.setFont(&Raleway24pt);
  scn.setCursor(UI_MG, UI_MG * 2 + BASE_FS * 2);
  scn.println(F("Set duration"));
  scn.setFont(&Raleway12pt);
  scn.setCursor(UI_MG, scn.height() / 2 - 20 - UI_MG * 2);
  scn.println(F("Current duration:"));
  
  scn.drawRoundRect(UI_MG, scn.height() / 2 - 20, scn.width() - UI_MG * 2,
                    BASE_FS * 3 + UI_MG * 4, L_RADIUS, MAGENTA);
  scn.setCursor(UI_MG * 2, scn.height() / 2 + BASE_FS * 3);
  scn.setFont(&Raleway36pt);
  scn.println(F("12:34"));
  scn.setFont(&Raleway12pt);

  scn.drawFastHLine(UI_MG, BASE_FS * 2 + UI_MG * 4, scn.width() - UI_MG * 2, GRAY);
  scn.drawFastHLine(UI_MG, scn.height() / 2 + BASE_FS * 3 + UI_MG * 4,
                    scn.width() - UI_MG * 2, GRAY);

  const uint16_t bStart = scn.height() / 2 + BASE_FS * 3 + UI_MG * 6;
  const uint16_t sw     = scn.width() - UI_MG * 2;
  scn.fillRoundRect(UI_MG, bStart, sw / 4 - UI_MG / 2, BTN_HEIGHT, 8, ACCENT);
  scn.fillRoundRect(sw / 4 + UI_MG, bStart, sw / 4 - UI_MG / 2, BTN_HEIGHT, 8, ACCENT);
  scn.fillRoundRect(sw / 2 + UI_MG,
  bStart, sw / 4 - UI_MG / 2, BTN_HEIGHT, 8, ACCENT);
  scn.fillRoundRect(sw / 4 * 3 + UI_MG,
  bStart, sw / 4 - UI_MG / 2, BTN_HEIGHT, 8, ACCENT);
}
