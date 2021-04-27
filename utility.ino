void drawCross(const uint16_t s, const uint16_t e) {
  scn.drawLine(s + UI_MG, UI_MG, e - UI_MG, BTN_HEIGHT - UI_MG, RED);
  scn.drawLine(e - UI_MG, UI_MG, s + UI_MG, BTN_HEIGHT - UI_MG, RED);
}

void drawBack(const uint16_t x, const uint16_t y, const uint16_t w) {
  const uint16_t mp = y + w / 2;
  scn.drawLine(x + w - UI_MG * 3 / 2, UI_MG + y, UI_MG * 3 / 2, mp, WHITE);
  scn.drawLine(x + w - UI_MG * 3 / 2, y + w - UI_MG, UI_MG * 3 / 2, mp, WHITE);
}

void drawMenu(const uint16_t x, const uint16_t y, const uint16_t w) {
  const uint16_t sp = w / 6;
  const uint16_t st = x + UI_MG;
  const uint16_t wd = w - UI_MG * 2;
  scn.drawFastHLine(st, sp * 2 + 1, wd, WHITE);
  scn.drawFastHLine(st, sp * 3 + 1, wd, WHITE);
  scn.drawFastHLine(st, sp * 4 + 1, wd, WHITE);
}
