uint16_t lgc(const uint8_t item, const uint8_t w) {
  return w * item + UI_MG * (4 + 2 * item);
}

void drawLauncher() {
  state = 0;
  
  scn.fillScreen(BLACK);

  const uint8_t w = (scn.width() - UI_MG * 8) / 3 - UI_MG * 3 / 2;

  // First row
  scn.fillRoundRect(lgc(0, w), UI_MG * 3, w, w, 8, L_DBLUE);
  scn.fillRoundRect(lgc(1, w), UI_MG * 3, w, w, 8, L_GREEN);
  scn.fillRoundRect(lgc(2, w), UI_MG * 3, w, w, 8, L_CYAN);

  // Second row
  scn.fillRoundRect(lgc(0, w), w + UI_MG * 5, w, w, 8, L_PINK);
  scn.fillRoundRect(lgc(1, w), w + UI_MG * 5, w, w, 8, L_BROWN);
  scn.fillRoundRect(lgc(2, w), w + UI_MG * 5, w, w, 8, L_DRED);

  // Icons
  // ------
  scn.drawBitmap(lgc(0, w) + w / 2 - 32, UI_MG * 3 + w / 2 - 32, timeIcon, 64, 64, WHITE);
  scn.drawBitmap(lgc(1, w) + w / 2 - 32, UI_MG * 3 + w / 2 - 32, brushIcon, 64, 64, WHITE);
  scn.drawBitmap(lgc(2, w) + w / 2 - 32, UI_MG * 3 + w / 2 - 32, calcIcon, 64, 64, WHITE);
  // ------
  scn.drawBitmap(lgc(0, w) + w / 2 - 32, UI_MG * 5 + w * 3 / 2 - 32, gameIcon, 64, 64, WHITE);
  scn.drawBitmap(lgc(1, w) + w / 2 - 32, UI_MG * 5 + w * 3 / 2 - 32, infoIcon, 64, 64, WHITE);
  scn.drawBitmap(lgc(2, w) + w / 2 - 32, UI_MG * 5 + w * 3 / 2 - 32, settingsIcon, 64, 64, WHITE);
}

void launcherHitbox(TSPoint p) {
  const uint8_t w = (scn.width() - UI_MG * 8) / 3 - UI_MG * 3 / 2;
  if (p.x > lgc(0, w) && p.y > UI_MG * 3 && p.x < lgc(0, w) + w && p.y < UI_MG * 3 + w) 
  drawClock();
  else if (p.x > lgc(1, w) && p.y > UI_MG * 3 && p.x < lgc(1, w) + w && p.y < UI_MG * 3 + w) 
  drawDraw();
  else if (p.x > lgc(2, w) && p.y > UI_MG * 3 && p.x < lgc(2, w) + w && p.y < UI_MG * 3 + w) 
  drawCalc();
  else if (p.x > lgc(2, w) && p.y > UI_MG * 5 + w && p.x < lgc(2, w) + w && p.y < UI_MG * 5 + w*2)
  drawSettings(); 
  else if (p.x > lgc(0, w) && p.y > UI_MG * 5 + w && p.x < lgc(0, w) + w && p.y < UI_MG * 5 + w*2)
  drawGames(); 
}
