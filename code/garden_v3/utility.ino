//
//// lcd clear line utility function
//
//void clearLine (int line) {
//  clearLine(line, 16); // deafult width to clear
//}
//
//void clearLine (int line, int width){
//    lcd.setCursor(0,line);
//    for (int i =0 ; i < width; i ++ ) {
//        lcd.print(" ");
//    }
//    
//    lcd.setCursor(0,line);
//} // end clear line
//
//
//// message utility function
//void lcdMessage(String m) {
//  lcdMessage(m,1); // defaul write to second line
//}
//
//void lcdMessage(String m, int l) {
//   // LDC messages
//    clearLine(l);
//    lcd.print(m);
//  
//}
//
//// message utility function
//void lcdMessage(char c) {
//  lcdMessage(c,1); // defaul write to second line
//}
//
//void lcdMessage(char c, int l) {
//   // LDC messages
//    lcd.print(c);
//  
//}
//
//
//// utility -- indicates that Arduino is fxn'ing
//void heartBeat(){
//  
//  heartToggle = 1 - heartToggle;
//
//  // blink heart
//  lcd.setCursor(15,0);  // top right corner
//  lcd.write(heartToggle);  // write the custom character
//  
// 
//  // write idle every 5th time
// 
//  String forLCD = "IDLE: ";
//  forLCD += ctr;
//  
//  idleCount++;
//  if (idleCount % 6 == 0 )   lcdMessage(forLCD);  
//  
//}  // end heart beat

