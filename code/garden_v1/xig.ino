
 

void xigUpdate() {

     lcdMessage("xigUpdate...");
     
     light = analogRead(photoCell);
     
      // upload the current value to the server, it will be stored in a dataFile.txt
      Serial.print("http://www.spinningtheweb.org/sandbox/ardPHP/xig_upload_eg_withLight.php?value=");
      Serial.print(ctr,DEC);
      Serial.print("&light=");
      Serial.println(light,DEC);
      
      delay(50);
      
      Serial.print("http://api.thingspeak.com/update?key=NQVB30JV75UUMHE8&light=");
      Serial.println(ctr,DEC);
       
      ctr++; // increment the data to upload
      
      response = false;
  
} // end update


void xigRecover() {
   
     lcdMessage("abort :: recover");
     
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
    Serial.println("http://www.spinningtheweb.org/sandbox/ardPHP/xig_upload_example.php?value=Error");

}


void handleSerial(){
  
  lcdMessage("handleSerial");
  delay(250);
   
  if (Serial.available()) {
    
    xigResponse ="";
    int buffCount = 0;
    
    // capture the return message
    do {
      
        char c = Serial.read();
        if (buffCount < 15) {  // keep only 15 characters
            xigResponse +=c;
            buffCount ++;
        } // end if buffCount
       
    } while ( Serial.available() );
         
 } // end - Serial.available
  
  Serial.flush();

} // end  -- handle serial


    
 void xigParse(){
    
     lcdMessage("xigParse...");
     delay(250);
      
          if (xigResponse.startsWith(serverPrefix)) {
            
                    // successful connection and return from the server
                    lcdMessage(xigResponse);
                    response = true ;
                    recovered = true;
  


           } else if  (xigResponse.startsWith("Xig: No session")) {
             
                    // no session -- but waiting -- special case recovered message from XIG
                    lcdMessage ("abrt rx no sess");
                    response  = true ;
                    recovered = true;
                
             
           } else {
             
                    // make sure this is correct -- 
                     String m = "Fail:";
                     m+= xigResponse;
                     lcdMessage(m);
                     abortFlag = true; 
                     
                     delay(3000);
           
           } // end -- you said
          
 } //end -- parse
    



 
    
  
  

