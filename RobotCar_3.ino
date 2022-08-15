 //**************************** RobotCar_3 ********************************
// Only files with the .ino extension are scanned for include files.     *
// This is by design, for simplicity for one thing and so that a         *
// library can't include another library that includes another library   *
// and so on.                                                            *
// Athugid ad setja snuningsAtt i RobotFunctions.h a -1 ef servomotor    *
// er orvhentur  Breytt 23.3.2017                                        *
//***********************************************************************/
#include "Arduino.h"
#include "RobotFunctions.h"
#include <SoftwareSerial.h>
#include "MyDFPlayer.h"


//************************** uppsetning á forritinu *****************
void setup() 
{ 
    pinMode(ledPin13, OUTPUT);
    pinMode(ledPin3, OUTPUT);
    pinMode(ledPin11, OUTPUT);
    pinMode(motorVpwm_,OUTPUT);
    pinMode(motorVgir_,OUTPUT);
    pinMode(motorHpwm_,OUTPUT);
    pinMode(motorHgir_,OUTPUT);
  
    servoMain.attach(10);//Servo on digital pin ~10
  
    pinMode(sonarTrigger_,OUTPUT);
    pinMode(sonarEcho_,INPUT_PULLUP); //Allir inngangar verda að hafa pullup vidnam 
                                      //her notum við internal pullup (20kohm) orgjorvans 
    pinMode(TXspilari_,OUTPUT);
    pinMode(RXspilari_,INPUT_PULLUP); //Notum aftur Internal pullup vidnam

   Serial.begin(9600); 
   
//    ******************** Setja upp MDFPlayer ************************* */
      mySerial.begin(9600);
      delay(500);

   mp3_play_track(17);  // 17. Bíll í gang 
    delay(5000); 
   mp3_play_track(1);     // 1. Keyrir du dud udududu
     //lagNr=2;
     //Timar
       time=millis();         //Setur time breytuna á tíma liðinn frá starti
       timeX=time;
       reiknaPulsBreidd(0,-1); //SONAR beint framm, í þessum bíl er leiðrétt um +2°
       delay(100);
       lengdX=lengd(); 
}//End of setup *********

//*************************** Keyrslulykkjan **********************
void loop()
{  
    reiknaPulsBreidd(0,-1); //SONAR beint framm, í þessum bíl er leiðrétt um +2°
    delay(100);    
    startCar(); // Bíll keyrir áfram
    delay(100);
  // blikkandi blátt og gult ljós í akstri
         
         if(lengd() > 50) {
                  digitalWrite(ledPin11, HIGH);
                  delay(100);
                  digitalWrite(ledPin11, LOW );
                  delay(20);
                  digitalWrite(ledPin3, HIGH);
                  delay(100);
                  digitalWrite(ledPin3, LOW );
                  delay(20);
}
   // höfum lengdina < en 30 cm sökum rýmis í kennslustofu
   while(lengd()<30)
   {  
    // ef fjarlægð er minni en 30 cm frá hindrun stoðvast bílinn
      stopCar();
      
      delay(1000); 
      // Rautt ljós blikkar þegar hann er að skanna til vinstri og hægri
          digitalWrite(ledPin13, HIGH);
          delay(100);
          digitalWrite(ledPin13, LOW );
           delay(20);
      reiknaPulsBreidd(75,-1); //snúa til hægri
      delay(1000);
            digitalWrite(ledPin13, HIGH);
            delay(100);
            digitalWrite(ledPin13, LOW );
            delay(20);    
      int right = lengd(); // mæla vegalengd hægri
      delay(1000);
            digitalWrite(ledPin13, HIGH);
            delay(100);
            digitalWrite(ledPin13, LOW );
            delay(20);
      reiknaPulsBreidd(-75,-1); //snúa til vinstri
      delay(1000);
            digitalWrite(ledPin13, HIGH);
            delay(100);
            digitalWrite(ledPin13, LOW );
            delay(20); 
      int left = lengd(); // mæla vegalengd vinstri
      delay(1000);
            digitalWrite(ledPin13, HIGH);
            delay(100);
            digitalWrite(ledPin13, LOW );
            delay(20);
            
      // ef fjarlægð vinstri er stærri en fjarlægð hægri
      if (right < left) {
        //beygja til vinstri
        driveLeft();
      }
      else if (left < right) {
        //beygja til hægri
        driveRight(); 
      }
 
      delay(180);      // Gefa tíma til að beygja ca +/- 90°
      reiknaPulsBreidd(0,-1); //horfa áfram / stilla af sónar og beina beint fram
      delay(100);
          digitalWrite(ledPin13, HIGH);
          delay(100);
          digitalWrite(ledPin13, LOW );
          delay(20);
      startCar();     
      delay(500);          
      }



      //á ákveðnum fresti verður tjékkað á lengd til að kanna hvort bíll sitji fastur

      if (millis() >= (timeX+2500)){
        
      //ef við erum föst og lengdin er búin að vera sú sama í 2.5 sek
      if ( lengd() >= (lengdX-6) && lengd() <= (lengdX+6) ){
      // þá stoppum við og fleira                   
      stopCar();
      //  delay(200); sleppum delay hér þar sem það er delay inni í stopCar fallinu
      backCar();
      delay(1000);
      stopBackCar();
      delay(300);
      reiknaPulsBreidd(75,-1); //snúa til hægri
      delay(1000);
      int right = lengd(); // mæla vegalengd hægri
      delay(1000);
      reiknaPulsBreidd(-75,-1); //snúa til vinstri
      delay(1000);
      int left = lengd(); // mæla vegalengd vinstri
      delay(1000);
      if (right < left) {
      driveLeft();
      delay(190);
      }
      else if (left < right) {
      driveRight();
      delay(190);
      }
      // uppfærum lengdina
      lengdX = lengd();
      // uppfærum tímann
      timeX = millis();

      }

   }   
 }
 
//End of loop *********************
