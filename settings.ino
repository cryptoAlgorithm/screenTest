void drawSettings() {
  state = 5;
  
  scn.fillScreen(BLACK);
  
  scn.setFont(&Raleway24pt);
  scn.setCursor(UI_MG + BTN_HEIGHT, BASE_FS * 2 + UI_MG * 3 / 2);
  scn.println(F("Settings"));
  scn.setFont(&Raleway12pt);
  scn.print(F("Version: ")); scn.print(F(VERSION)); 
  scn.print(F(" (")); scn.print(F(__DATE__)); scn.print(F(" ")); 
  scn.print(F(__TIME__)); scn.println(F(")"));
  scn.println(F("Programmed by Vincent Kwok"));

  scn.drawFastHLine(UI_MG, BTN_HEIGHT + UI_MG * 2, scn.width() - UI_MG * 2, GRAY);
  
  // Back button
  scn.drawRoundRect(0, UI_MG / 2, BTN_HEIGHT, BTN_HEIGHT, 12, GRAY); // Close button
  drawBack(0, UI_MG / 2, BTN_HEIGHT);
}
