const PROGMEM char calcBtnMap[5][4] {
  {'C', ' ', '%', '/'},
  {'7', '8', '9', '*'},
  {'4', '5', '6', '-'},
  {'1', '2', '3', '+'},
  {'0', ' ', '.', '='}
};

void drawCalc() {
  state = 4;

  const uint8_t st = BTN_HEIGHT + UI_MG * 2;

  scn.fillScreen(BLACK);
  
  // Back button
  scn.drawRoundRect(0, UI_MG / 2, BTN_HEIGHT, BTN_HEIGHT, 12, GRAY); // Close button
  drawBack(0, UI_MG / 2, BTN_HEIGHT);
  
  scn.setFont(&Raleway24pt);
  scn.setCursor(UI_MG + BTN_HEIGHT, BASE_FS * 2 + UI_MG * 3 / 2);
  scn.println(F("0"));

  // Draw buttons area  
  const uint16_t w = scn.width() / 4;
  const uint16_t mh = scn.height() - st;
  const uint8_t h = mh / 5;
  
  scn.fillRoundRect(0, st, scn.width(), mh, L_RADIUS, RAISED);
  scn.fillRoundRect(w * 3, st, w, mh, L_RADIUS, SEC_A);
  
  for (uint8_t i = 1; i < 3; i++) scn.drawFastVLine(w * i, st, mh, GRAY);
  for (uint8_t i = 1; i < 5; i++) scn.drawFastHLine(0, st + h * i, scn.width(), GRAY);

  scn.setFont(&Raleway12pt);
  for (uint16_t y = 0; y < 5; y++) {
    for (uint16_t x = 0; x < 4; x++) {
      scn.setCursor(((x + 1) * w) - w / 2 - UI_MG / 2, ((y + 1) * h) - h / 2 + BASE_FS / 2 + st);
      scn.print(calcBtnMap[y][x]);
    }
  }
}
