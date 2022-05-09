#include <ESP32Servo.h>

/**
 * This program allows ESP32 to control a servo motor to open and close the pet food dispenser.
 * The lid opens at a desired time, using a timer.
 * The lid closes when the user presses the switch.
 * 
 * @Author ChangSu Nam
 * @UNI cn2521
 * @Since Module 5 May 2022
 */

 
volatile int interrupts;
int totalInterrupts;
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

/**
 * myservo the servo motor
 * servoPin the pin that servo motor is connected to on ESP32
 * state the starting position of servo motor
 * isSwitchOn the state of switch
 */
Servo myservo;
const int servoPin = 17;
const int switchPin = 26; 
int state = 0; 
int isSwitchOn = 0; 



/**
 * The code below is executed when the set time is up on the timer. 
 * 
 * When state is 0, the lid opens
 * When state is 100, the lid closes.
 */
void IRAM_ATTR onTime(){
  
  portENTER_CRITICAL_ISR(&timerMux);
  interrupts++;
  portEXIT_CRITICAL_ISR(&timerMux);
    state = 0; //servo motor will open the lid
    myservo.write(state);
}




void setup() { 
/**
 * The code below sets up the timer
 */
 timer = timerBegin(0,80,true);
 timerAttachInterrupt(timer, &onTime, true);
 timerAlarmWrite(timer,10000000,true);  // every 5000000ms or 5s, timer is interrupted.
 timerAlarmEnable(timer);
 
/**
 * The code below sets up the servo motor, and switch
 */
  myservo.setPeriodHertz(50);
  myservo.attach(servoPin, 500, 2500);
  pinMode(switchPin, INPUT_PULLUP);
}




void loop() {
  //Pressing the switch closes the lid, and resets the timer.
  isSwitchOn = digitalRead(switchPin);
  if(isSwitchOn == LOW){ // switch is pressed
      Serial.println("Switch pressed");
      state = 100; //servo motor will close the lid
      myservo.write(state);
      timerWrite(timer, 0); //reset the timer
   }

  //timer interrupt handling
  if(interrupts>0){
    portENTER_CRITICAL(&timerMux);
    interrupts--;
    portEXIT_CRITICAL(&timerMux);
    totalInterrupts++;
  }
  
}
