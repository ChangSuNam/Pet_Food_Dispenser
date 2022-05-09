## Timed Pet Food Disepnser

  ![IMG_1461](https://user-images.githubusercontent.com/25335750/167328868-48255829-82e8-4902-98b0-e3136a8507bc.jpg)

  
# Project Description
For this project, I wanted to create something practical using ESP32. I decided to create a pet food dispenser for owner that may have to leave their pet alone for a few hours, or even days. In such cases, some owners give their pet large amount of food on a bowl before they leave, but this can be troublesome for multiple reasons: 1. The food gets soggy from the saliva of the pet. This could infect the food with bacteria. 2. Some pets do not eat some portion of the food and eat the rest when they are hungry again. Instead, they will finish the given food instantly. 
To solve theses issues, I designed my dispenser to drop the food to a bowl at a certain time, set up by the user. 

## Hardware and Enclosure 

The enclosure for this project was 3D printed. Tinkercad was used to create the modelling of the enclosure. The .stl file of the enclosure is uploaded here: https://github.com/ChangSuNam/Pet_Food_Dispenser/blob/main/pet%20food%20dispenser%20enclosure.stl




![IMG_1215](https://user-images.githubusercontent.com/25335750/167328898-3ed5aca8-8005-4ab2-89bc-50e03ffdd25a.jpg)
![IMG_1216](https://user-images.githubusercontent.com/25335750/167328926-8b9a3947-aa8f-4829-989f-79279e106f2b.jpg)
![IMG_1230](https://user-images.githubusercontent.com/25335750/167328902-61ea22dd-ffd2-41f8-b242-43686a78f02c.jpg)
![IMG_1327](https://user-images.githubusercontent.com/25335750/167328909-2ddcb688-365f-41d6-85f6-d32962e26bbf.jpg)
The filaments blocking the rectaungular space designed to locate the ESP32 had to be removed manually.
![IMG_1335](https://user-images.githubusercontent.com/25335750/167328916-ee18bb05-d67c-404f-be2c-23fbb4822e2b.jpg)
The ESP32 is hidden at the bottom, preventing the pet from biting or scratching it. 

The enclousre was printed using 0.6 PLA. Since PLA is not food safe, instead of including the bowl on the enclosure, I created a hole where the user can locate their own clean bowl.
  
On top of ESP32, an essential hardware for this project is S90G Servo Motor. It is used to open, and close the lid. In addition, momentary, normally open, single pole single throw switch was used to reset the timer, and close the lid again. The lid 3D printed with the enclosure was glued and taped to the servo motor:![IMG_1329](https://user-images.githubusercontent.com/25335750/167329465-c13a4c96-851f-4cd4-bec5-7c82752081a7.jpg)

A transparent plastic bottle is used to store the food prior to dispensing. Its neck was cut using a saw to widen the entrance. Its rough edge was then sanded down and taped for safety:![IMG_1332](https://user-images.githubusercontent.com/25335750/167329591-704e78ac-d097-4f02-b8dc-8bd50f012ae7.jpg)
![IMG_1334](https://user-images.githubusercontent.com/25335750/167329595-bbb08909-a729-4719-93cc-ba42730e784e.jpg)
The bottle is connected to a metal rod using glue and tape. The enclosure was created with a small hole that fits this rod.
  
The dispenser does not use a battery, because in cases the owner has to leave their home for a long time, the battery might run out of power, and the pet would starve. For this reason, the dispenser is connected to a laptop with USB-C to draw power.  


  
### Software

Instead of using delay(), this disepnser relies on timer interrupts. This is because interrupts prevent errors or functions blocking the code to be executed. Hence, usage of timer prevents the pet from starving due to malfunctioning of the dispenser.

When the timer is interrupted, the servo motor moves so that the lid opens, and food that was in the bottle is dropped on the bowl. When ther user wants to restart the program after filling the bottle again with food, they could simply press the switch. This will control the motor to close the lid again, and reset the timer. 

The details of code that executes the process above can be found here: https://github.com/ChangSuNam/Pet_Food_Dispenser/blob/main/Module5_Pet_Food_Dispenser.ino 

This code was created referring to the timer library, which can be found here: https://github.com/espressif/arduino-esp32/blob/master/libraries/ESP32/examples/Timer/RepeatTimer/RepeatTimer.ino


#### Technical difficulties

-When using the 3D printer, it is important to check the maximum length and width allowed to print before creating the modelling. The 3D printer I used supported maximum length and width of 225mm by 225mm. Since my model was larger, I had to resize them to print it.

-The timer uses milliseconds, not seconds. Be careful when setting the time.

-When using timer on ESP32, "timerWrite(timer, 0);" will reset the timer. I was originally creating boolean flags to check the timer and state of the servomotor to reset the timer, but using the provided snippet of code makes it much simpler to reset the timer.

##### Sample usage

The video of this dispenser running can be found here: https://youtu.be/rDXSdaNEKCw

For the purpose of demo, the timer is set to open the lid in 10 seconds. The duration can be altered by changing the second parameter at code "timerAlarmWrite(timer,10000000,true);" in the setup(). 

Additional reference: https://espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf



