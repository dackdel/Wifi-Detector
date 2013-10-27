#include <Process.h>
const int RED_LED = 9;
const int GREEN_LED = 10;
const int BLUE_LED = 11; 
void setup() {
  Bridge.begin();   // Initialize the Bridge
  Serial.begin(9600);   // Initialize the Serial
  pinMode(RED_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);
  pinMode(BLUE_LED,OUTPUT);
}
void loop() {
  Process p;
  // This command line runs the WifiStatus script, (/usr/bin/pretty-wifi-info.lua), then 
  // sends the result to the grep command to look for a line containing the word
  // "Signal:"  the result is passed to this sketch:
  p.runShellCommand("/usr/bin/pretty-wifi-info.lua | grep Signal");
  // do nothing until the process finishes, so you get the whole output:
  while(p.running());  
  // Read command output. runShellCommand() should have passed "Signal: xx&":
  while (p.available()) {
    int result = p.parseInt();   // look for an integer
    if(result!=0){
      if(result<=40){
        analogWrite(RED_LED, 255);
        analogWrite(GREEN_LED, 0);
        analogWrite(BLUE_LED, 0);
      }
      else if(result>40 && result<=60){
        analogWrite(RED_LED, 255);
        analogWrite(GREEN_LED, 255);
        analogWrite(BLUE_LED, 0);
      }
      else if(result>60){
        analogWrite(RED_LED, 0);
        analogWrite(GREEN_LED, 255);
        analogWrite(BLUE_LED, 0);
      }
      Serial.println(result);         // print the number as well
    } 
  }   
  //delay(5000);  // wait 5 seconds before you do it again
}
