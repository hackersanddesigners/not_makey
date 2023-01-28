# not_makey

This repository describes how to manufacture a shield for the ESP32, and the code to program pins as resistive touch sensors that each send strings to a laptop over Bluetooth. It is programmed to send letters that correspond with PJ machine keycodes used in e.g. this workshop https://github.com/hackersanddesigners/interfacial-workout-23

## tools

* Roland Modela MDX-20 with fabmodules for pcb production installed, such as this setup at Waag fablab [decribed here](https://fablab.waag.org/PCB%20Milling/How%20to%20use%20the%20Modela%20MDX-20/). Note that this process doesn't require Gerber files, instead you need a 1000 DPI black and monochrome image of the TOP and or BOTTOM of the board, and a separate file with holes and the board outline).
* Soldering station, solder, clippers

## bill of materials

* an ESP32 WROOM devkit, e.g. [this one from Espressif](https://www.espressif.com/en/products/modules/esp32) €14,49 at [Reichelt](https://www.reichelt.nl/nl/nl/entwicklungsboard-esp32-wroom-32e-esp32devkitc32e-p341303.html?&trstct=pos_1&nbc=1)
* mini usb programming cable e.g. [this one at kiwi](https://www.kiwi-electronics.com/nl/microusb-kabel-usb-a-naar-micro-b-15cm-3240?search=usb-A%20naar%20micro-b) €1,25
* single row break-away female header strips (you need 2x a single row strips of 15 positions) e.g. [this one](https://www.reichelt.nl/nl/nl/vrouwelijke-connector-2-54mm-1x20-scheidbaar-vertind-fis-bl1-20-z-p283794.html?&nbc=1) at Reichelt €1,22 each
* 14x 22Mohm resistors e.g. [this one](https://nl.farnell.com/yageo/hhv-25jt-52-22m/res-22m-5-250mw-axial-metal-film/dp/1779371?st=22m%20ohm%20resistor) at Farnell €0,07 each. These can be hard to find in DIY shops you might need to look at Farnell, Mouser, or get some from China :(
* 14 or more Alligator clips to connect your DIY buttons to the board

<img src="./images/breakaway-fem-header.png" alt="header" width="500"> 

*Break-away header strip*

## software & dependencies

* Arduino IDE: [www.arduino.cc](www.arduino.cc)
	* Install the board with the board manager: 
		* *esp32* by espressif
		* select board > ESP Arduino > ESP 32 Dev Module  
	* Install the following libraries: 
		* *movingAVG.h* by Jack Christensen
		* the other libs included in the code don't seem to need an install (perhaps come with ESP32 board definitions? > check)
* Eagle (if you want to edit or redesign the board)
* GIMP or photoshop (if you want to edit the milling files directly)

## acknowledgments

* Joylab's Jay Silver & Erik Rosenbaum's *MakeyMakey board* [https://github.com/sparkfun/MaKeyMaKey](https://github.com/sparkfun/MaKeyMaKey)
* Manualbl's [repository on using ESP32 as Bluetooth Keyboard](https://gist.github.com/manuelbl/66f059effc8a7be148adb1f104666467)
* Jack Christensen's [moving average library](https://github.com/JChristensen/movingAvg)

## Manufacturing the shield

## prototyping setup

<img src="./images/wiring.png" alt="header" width="500"> 

## schematic

<img src="./images/schematic.png" alt="header" width="600"> 

## board layout 

<img src="./images/simple_boardlayout_bottom.png" alt="header" width="500"> 

## fabrication files for Roland modela MDX-20

* exported from Eagle at 1000 dpi in monochrome
* BOTTOM - exported layers: bottom, via's, holes (flip horizontally in img editor)
* CUT - exported layers:holes & board dimension (place rect larger than board on unused layer or board outline disappears when exporting the image)

### Milling the PCB

See also: [http://fabacademy.org/archives/2015/eu/students/bogers.loes/06electronicsdesign.html](http://fabacademy.org/archives/2015/eu/students/bogers.loes/06electronicsdesign.html)

* Mill the [bottom.png file](./fabrication/bottom.png)
* Drill holes and outline [cut.png file](./fabrication/cut.png)
* Wash
* Test connections
* Make corrections

<img src="./fabrication/bottom.png" alt="header" width="400">

<img src="./fabrication/cut.png" alt="header" width="400"> 

### Soldering

* resistors
* connectors


## Programming the ESP

What the program does.... bla bla bla

### Select the board & port

### Compile the code to check libs are working

### Upload to the board

### Connect to device via Bluetooth

### Check the serial monitor

### Open a notepad to test



## Bringing it all together

Connect the ESP to the shield, taking care the orientation is correct. 

Test by touching a resistor pad with one finger, while touching the 3V3 with the other finger. The principle is the same as makey makey, but here the resistors are connected as a pull-up resistor (keeps the signal high until a change is registered), so you touch 3V3 instead of GND.



	
