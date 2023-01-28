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

![](./images/breakaway-fem-header.png)

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





	
