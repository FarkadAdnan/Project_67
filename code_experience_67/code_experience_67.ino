/*
 By:Farkad Adnan
 E-mail: farkad.hpfa95@gmail.com
 inst : farkadadnan
 #farkadadnan , #farkad_adnan , فرقد عدنان#
 FaceBook: كتاب عالم الاردوينو
 inst : arduinobook
 #كتاب_عالم_الاردوينو  #كتاب_عالم_الآردوينو 
 */
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#define REPORTING_PERIOD_MS     1000
#define rs 9 
#define en 8 
#define d4 7 
#define d5 6  
#define d6 5 
#define d7 4 
  
PulseOximeter pox;
uint32_t tsLastReport = 0;
void onBeatDetected(){
    Serial.println("Beat!");
}
 
void setup(){
    Serial.begin(115200);
    Serial.print("Initializing pulse oximeter..");
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
     pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
    pox.setOnBeatDetectedCallback(onBeatDetected);
}
void loop(){
    pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("BPM: ");
        Serial.print(pox.getHeartRate());
        
        Serial.print("SpO2: ");
        Serial.print(pox.getSpO2());
        Serial.print("%");
        tsLastReport = millis();
    }
}
