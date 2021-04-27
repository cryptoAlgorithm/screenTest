uint16_t selColor = BLUE;

const PROGMEM uint16_t colArr[] = {
  BLACK,
  BLUE,
  RED,
  GREEN,
  CYAN,
  MAGENTA,
  YELLOW,
  WHITE,
  GRAY
};

void setDrawCol(const uint16_t y) {
  const uint8_t btnH = scn.height() / 10;
  for (uint8_t i = 0; i < 9; i++) { // Find out which button was pressed
    if (y > btnH * i && y <= btnH * (i + 1)) selColor = colArr[i];
  }
   
  // Update chosen color
  scn.fillRoundRect(scn.width() - btnH, btnH * 9, btnH, btnH, btnH, selColor);
}

void drawDraw() {
  state = 3;
  
  scn.fillScreen(BLACK);

  // Reset selected color
  selColor = BLUE;

  const uint8_t btnH = scn.height() / 10;
  const uint16_t w = scn.width() - btnH;
  // Draw all colors
  for (uint8_t i = 0; i < 9; i++) scn.fillRect(w, btnH * i, btnH, btnH, colArr[i]);

  scn.drawFastVLine(w - 1, 0, scn.height(), GRAY);
  
  scn.fillRoundRect(w, btnH * 9, btnH, btnH, btnH, selColor);
  
  // Delete button
  scn.drawRoundRect(0, scn.height() - BTN_HEIGHT, BTN_HEIGHT, BTN_HEIGHT, L_RADIUS, GRAY);
  scn.setCursor(UI_MG + 2, scn.height() - UI_MG - 2);
  scn.print(F("C"));

  scn.drawRoundRect(0, 0, BTN_HEIGHT, BTN_HEIGHT, L_RADIUS, GRAY); // Close button
  drawBack(0, 0, BTN_HEIGHT);
}

void drawHitbox(TSPoint p) {
  const uint8_t btnW = scn.height() / 10;
  if (p.x < BTN_HEIGHT && p.y < BTN_HEIGHT) drawLauncher();
  else if (p.x < BTN_HEIGHT && p.y > scn.height() - BTN_HEIGHT) drawDraw(); // Restart activity
  else if (p.x > scn.width() - btnW - 4) setDrawCol(p.y);
  else scn.fillCircle(p.x, p.y, 1, selColor);
}
