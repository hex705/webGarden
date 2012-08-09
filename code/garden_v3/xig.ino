
 

void xigUpdate() {
digitalWrite(13,HIGH);
      
      Serial.print("http://api.thingspeak.com/update?key=S2YH7PIOWEVSMBAU&field1=");
      Serial.print(lightLevel,DEC);
      Serial.print("&field2=");
      Serial.print(moistureLevel,DEC);
      Serial.print("&field3=");
      Serial.println(valveState,DEC);
      
      
      response = false;
  
} // end update


void xigRecover() {
   
    // lcdMessage("abort :: recover");
     
     abortFlag = false; 
     markerFlag = true;

     Serial.println("abort");  // force the xig to give up lost connection
     delay(2000);              // slows down the number of aborts being sent -- this can take a few tries
     
    // Serial.flush();
    response = false;
    recovered = false;
    
}

void xigMarker() {
  
    markerFlag = false;
   // Serial.println("http://www.spinningtheweb.org/sandbox/ardPHP/xig_upload_example.php?value=Error");

}


void handleSerial(){
  // Serial.println("handling serial");
  if (Serial.available()) {
    digitalWrite(13,LOW);
    xigResponse ="";
    int buffCount = 0;
    
    // capture the return message
    do {
      
        char c = Serial.read();
        if (buffCount < 150) {  // keep only 15 characters
            xigResponse +=c;
            buffCount ++;
        } // end if buffCount
       
    } while ( Serial.available() );
        // Serial.println("end of handle");
 } // end - Serial.available
  
  Serial.flush();
  digitalWrite(13,HIGH);
  delay(250);
  digitalWrite(13,LOW);
  delay(250);
    digitalWrite(13,HIGH);
  delay(250);
  digitalWrite(13,LOW);
  delay(250);
    digitalWrite(13,HIGH);
  delay(250);
  digitalWrite(13,LOW);
  delay(250);
    digitalWrite(13,HIGH);
  delay(250);
  digitalWrite(13,LOW);
  delay(250);

} // end  -- handle serial


    
 void xigParse(){

          // Serial.println(xigResponse);
          char test = xigResponse.charAt(0);

      
          if ( xigResponse.startsWith("XBee") || (test >='0' && test <= '9') ) {
            
               // Serial.println("success");
                    // successful connection and return from the server
                  //  lcdMessage(xigResponse);
                    response = true ;
                    recovered = true;
                    blink(test);

           } else if  (xigResponse.startsWith("Xig: No session")) {
             
                    // no session -- but waiting -- special case recovered message from XIG
                  //  lcdMessage ("abrt rx no sess");
                    response  = true;
                    recovered = true;
                
             
           } else {
             
                    // make sure this is correct -- 
                     String m = "Fail:";
                     m+= xigResponse;
                  //   lcdMessage(m);
                     abortFlag = true; 
                     Serial.flush();
                     
                      digitalWrite(13,HIGH);
  delay(500);
  digitalWrite(13,LOW);
  delay(250);
    digitalWrite(13,HIGH);
  delay(500);
  digitalWrite(13,LOW);
  delay(250);
    digitalWrite(13,HIGH);
  delay(500);
  digitalWrite(13,LOW);
  delay(500);
    digitalWrite(13,HIGH);
  delay(250);
  digitalWrite(13,LOW);
  delay(250);
  
  
                     delay(1500);
           
         } // end -- you said
          
 } //end -- parse
    

void blink(int c){
   digitalWrite(11,HIGH);
      delay(1000);
      digitalWrite(11,LOW);
      delay(100);
  for (int i = 0; i < c; i ++) {
      digitalWrite(11,HIGH);
      delay(300);
      digitalWrite(11,LOW);
      delay(100);
      
  }
   digitalWrite(11,HIGH);
      delay(1000);
      digitalWrite(11,LOW);
      delay(100);
  
}
 
    
  
  

