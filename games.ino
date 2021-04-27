uint16_t prevPaddlePos = 0;
unsigned long pPrevUpdate = 0;

void updateFromXPos(const uint16_t x) {
  // Throttling
  if (millis() < pPrevUpdate + 50) return;
  
  // Erase previous paddle
  scn.fillRect(prevPaddlePos - BTN_HEIGHT * 2, scn.height() - BTN_HEIGHT - UI_MG,
                    BTN_HEIGHT * 4, BTN_HEIGHT, BLACK);
  
  scn.fillRect(x - BTN_HEIGHT * 2, scn.height() - BTN_HEIGHT - UI_MG,
                    BTN_HEIGHT * 4, BTN_HEIGHT, SEC_A);

  prevPaddlePos = x;
  pPrevUpdate = millis();
}

void drawGames() {
  state = 6;
  
  scn.fillScreen(BLACK);
  
  scn.setFont(&Raleway24pt);
  scn.setCursor(UI_MG + BTN_HEIGHT, BASE_FS * 2 + UI_MG * 3 / 2);
  scn.println(F("Finger Tracking"));

  updateFromXPos(scn.width() / 2);
  
  // Back button
  scn.drawRoundRect(0, UI_MG / 2, BTN_HEIGHT, BTN_HEIGHT, 12, GRAY); // Close button
  drawBack(0, UI_MG / 2, BTN_HEIGHT);
}

void handleGameHitbox(TSPoint p) {
  updateFromXPos(p.x);
}
