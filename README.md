# FitPal
Smart Fitness Device which with help you to improve your technnique and target your muscles more efficiently thanks to the M5Stack Core2

USER MANUAL:

1. Pins are connected to the M5-Stack.:
      - GND M5Stack to GND Muscle Sensor 
      - 5V M5Stack to VCC Muscle Sensor
      - G35 M5Stack to VOUT Muscle Sensor
      - 1 set of electrodes connected to the MuscleSensor via a TRS Audio Plug
2. The skin area where we are going to put the electrodes is cleaned with alcohol and 2 of the electrodes are placed directly on the muscle next to each other.The last one is placed on a non-related musle as a reference point.
3. Download the ARDUINO IoT Remote App or access to the website to see and store the data. If not, you can use the Arduino Serial Plotter or Serial Monitor as a reference.  
4. create an Arduino IoT Cloud Account and create a new "Thing". Create the following variables with exactly the same information:
      - Declaration :bool effectiveornot, Type: Boolean, Variable Permission: Read & Write, Send Values: On change
      - Declaration: int effectivereps, Type: Integer number, Variable Permission: Read & Write, Send Values: On change
      - Declaration: int mvwifi, Type: Integer number, Variable Permission: Read & Write, Send Values: On change
5. Set the device information: ESP32/M5Stack Core2
6. Set your Network information: SSID and Password
7. Go to the "Sketch" window and paste the Main Program ONLY
8. Upload the code to M5Stack Core2
9. Go to Dashboard Window, create a new one and associate each variable "effectivereps", "effectiveornot" and "mvwifi" with each graphic element: “Effective Repetitions Made” Counter “Effective or Not Effective”  and “Muscle Activity” Graph, respectively.
10. Run the Device
11. Enjoy!!
12. To reset values, just reset the device.
13. If you want less delay, you should sacrifice the wifi connection, so the data will not be exported remotely.

PROBLEMS:
- NYUAD WIFI connection
- Big delay while transfering the data through the M5Stack Core 2 Device
- To much voltage given to the sensor (be carefull with this)
- Depending on Arduino IoT Cloud to share the data
