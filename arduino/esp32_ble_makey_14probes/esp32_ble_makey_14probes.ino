/*

  Sample program for ESP32 acting as a Bluetooth keyboard
  https://gist.github.com/manuelbl/66f059effc8a7be148adb1f104666467

  Modified by Loes (2022) To work with PJ machine

  This program lets an ESP32 act as a keyboard connected via Bluetooth.
  When a button attached to the ESP32 is pressed, it will generate the key strokes

  In order to receive the message, add the ESP32 as a Bluetooth keyboard of your computer
  or mobile phone:

  1. Go to your computers/phones settings
  2. Ensure Bluetooth is turned on
  3. Scan for Bluetooth devices
  4. Connect to the device called "NOT_MAKEY" (you can change this name in the code)
  5. Open an empty document in a text editor
  6. Press the buttons attached to the ESP32 to generate different letters

  WIRING DIAGRAM
    14 DIY capacitive "switches" you might use with makey makey are connected to GPIO pins that have ADC
    One leg of each switch goes to a 22M pullup resistor (connect to 3V3 rail)
    The other leg of the "switch" should touch GND rail
    ADC resolution on ESP32 is 0-4095! https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/
    in the diagram you can see letters and correlating functions in pj machine
  /*
                                 +----ESP32----+
                                 |     usb     |
                                 | 3V3     VIN |
                                 | GND     GND |
  left | A | = 3V3 <---/\/\/\--- | D15     D13 | ---/\/\/\---> 3v3 = N | change font
                    BUILTIN LED  | D2      D12 | ---/\/\/\---> 3V3 = P | go to next block
  Right| Q | = 3V3 <---/\/\/\--- | D4      D14 | ---/\/\/\---> 3V3 = T | generate PDF
                                 | RX2     D27 | ---/\/\/\---> 3V3 = R | decrease letter spacing
                                 | TX2     D26 | ---/\/\/\---> 3V3 = Y | increase letter spacing
                                 | D5      D25 | ---/\/\/\---> 3V3 = E | decrease block width
                                 | D18     D33 | ---/\/\/\---> 3V3 = I | increase block width
                                 | D19     D32 | ---/\/\/\---> 3V3 = M | rotate clockwise
                                 | D21     D35 | ---/\/\/\---> 3V3 = U | zoom in
                                 | RX0     D34 | ---/\/\/\---> 3V3 = SPACE | zoom out
                                 | TX0     D39 | ---/\/\/\---> 3V3 = W | move down
                                 | D22     D36 | ---/\/\/\---> 3V3 = S | move up
                                 | D23      EN |
                                 +-------------+
*/


#define US_KEYBOARD 1

#include <Arduino.h>
#include "BLEDevice.h"
#include "BLEHIDDevice.h"
#include "HIDKeyboardTypes.h"
#include <movingAvg.h>

// Define values that constitute Pressed and Released (find values w other sketch)
const int PressedMaxThreshold = 2400;
const int ReleasedMinThreshold = 2700;
const byte PinCount = 14;

// how esp shows up in bluetooth device list
#define DEVICE_NAME "NOT_MAKEY"

// array w numbers of all 14 pins with ADC (pin2 doesnt work w BLE)
const byte InputPins[PinCount] = {15, 4, 13, 12, 14, 27, 26, 25, 33, 32, 35, 34, 39, 36}; // ONLY ADC PINS!
int buttonState[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int prevButtonState[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
const char KeyCodes[PinCount] = {'a', 'q', 'n', 'p', 't', 'r', 'y', 'e', 'i', 'm', 'u', ' ', 'w', 's'};

const int ledPin =  2;      // builtin LED on esp32
int delayTime = 100;

struct TouchInput {
  byte analogPin;
  char keycode;
  movingAvg filter = movingAvg(20);     // use moving average filter that takes 20 samples
  boolean wasPressed = false;
};

TouchInput Pins[PinCount];

// Forward declarations
void bluetoothTask(void*);
void typeText(const char* text);

bool isBleConnected = false;

// define 14 keystrokes used in PJ machine
#define MESSAGE0 "a\n"
#define MESSAGE1 "q\n"
#define MESSAGE2 "n\n"
#define MESSAGE3 "p\n"
#define MESSAGE4 "t\n"
#define MESSAGE5 "r\n"
#define MESSAGE6 "y\n"
#define MESSAGE7 "e\n"
#define MESSAGE8 "i\n"
#define MESSAGE9 "m\n"
#define MESSAGE10 "u\n"
#define MESSAGE11 " \n"
#define MESSAGE12 "w\n"
#define MESSAGE13 "s\n"

void setup() {
  Serial.begin(115200);

  // configure pins for all buttons by cycling through array
  for (int thisPin = 0; thisPin < PinCount; thisPin++) {
    Pins[thisPin].analogPin = InputPins[thisPin];
    Pins[thisPin].keycode = KeyCodes[thisPin];
    Pins[thisPin].filter.begin();
  }

  //configure built in led (ESP32 has this on pin 2) as output
  pinMode(ledPin, OUTPUT);

  // start Bluetooth task
  xTaskCreate(bluetoothTask, "bluetooth", 20000, NULL, 5, NULL);
}


// Define Output Actions
int outputAction(int currentButton) {
  if (currentButton == 0) {
    typeText(MESSAGE0);
    digitalWrite(ledPin, HIGH);
    delay(delayTime);
  }
  if (currentButton == 1) {
    typeText(MESSAGE1);
    digitalWrite(ledPin, HIGH);
    delay(delayTime);
  }
  if (currentButton == 2) {
    typeText(MESSAGE2);
    digitalWrite(ledPin, HIGH);
    delay(delayTime);
  }
  if (currentButton == 3) {
    typeText(MESSAGE3);
    digitalWrite(ledPin, HIGH);
    delay(delayTime);
  }
  if (currentButton == 4) {
    typeText(MESSAGE4);
    digitalWrite(ledPin, HIGH);
    delay(delayTime);
  }
  if (currentButton == 5) {
    typeText(MESSAGE5);
    digitalWrite(ledPin, HIGH);
    delay(delayTime);
  }
  if (currentButton == 6) {
    typeText(MESSAGE6);
    digitalWrite(ledPin, HIGH);
    delay(delayTime);
  }
  if (currentButton == 7) {
    typeText(MESSAGE7);
    digitalWrite(ledPin, HIGH);
    delay(delayTime);
  }
  if (currentButton == 8) {
    typeText(MESSAGE8);
    digitalWrite(ledPin, HIGH);
    delay(delayTime);
  }
  if (currentButton == 9) {
    typeText(MESSAGE9);
    digitalWrite(ledPin, HIGH);
    delay(delayTime);
  }
  if (currentButton == 10) {
    typeText(MESSAGE10);
    digitalWrite(ledPin, HIGH);
    delay(delayTime);
  }
  if (currentButton == 11) {
    typeText(MESSAGE11);
    digitalWrite(ledPin, HIGH);
    delay(delayTime);
  }
  if (currentButton == 12) {
    typeText(MESSAGE12);
    digitalWrite(ledPin, HIGH);
    delay(delayTime);
  }
  if (currentButton == 13) {
    typeText(MESSAGE13);
    digitalWrite(ledPin, HIGH);
    delay(delayTime);
  }

  digitalWrite(ledPin, LOW);
  delay(10);
}


void loop() {

  if (isBleConnected) {
    for (int thisPin = 0; thisPin < PinCount; thisPin++) {
      float currentAverage = Pins[thisPin].filter.reading(analogRead(Pins[thisPin].analogPin));
      Serial.println(currentAverage);
      boolean previousState = Pins[thisPin].wasPressed;
      boolean currentState = previousState; // Default if in the dead zone
      if (currentAverage < PressedMaxThreshold) {
        currentState = true;      // Pressed
      }
      else if (currentAverage > ReleasedMinThreshold) {
        currentState = false;      // Released
      }
      if (currentState != previousState) {
        if (currentState) {
          outputAction(thisPin);
        }
        Pins[thisPin].wasPressed = currentState;
      }
    }
  }
}

// Message (report) sent when a key is pressed or released
struct InputReport {
  uint8_t modifiers;       // bitmask: CTRL = 1, SHIFT = 2, ALT = 4
  uint8_t reserved;        // must be 0
  uint8_t pressedKeys[6];  // up to six concurrenlty pressed keys
};

// Message (report) received when an LED's state changed
struct OutputReport {
  uint8_t leds;            // bitmask: num lock = 1, caps lock = 2, scroll lock = 4, compose = 8, kana = 16
};


// The report map describes the HID device (a keyboard in this case) and
// the messages (reports in HID terms) sent and received.
static const uint8_t REPORT_MAP[] = {
  USAGE_PAGE(1),      0x01,       // Generic Desktop Controls
  USAGE(1),           0x06,       // Keyboard
  COLLECTION(1),      0x01,       // Application
  REPORT_ID(1),       0x01,       //   Report ID (1)
  USAGE_PAGE(1),      0x07,       //   Keyboard/Keypad
  USAGE_MINIMUM(1),   0xE0,       //   Keyboard Left Control
  USAGE_MAXIMUM(1),   0xE7,       //   Keyboard Right Control
  LOGICAL_MINIMUM(1), 0x00,       //   Each bit is either 0 or 1
  LOGICAL_MAXIMUM(1), 0x01,
  REPORT_COUNT(1),    0x08,       //   8 bits for the modifier keys
  REPORT_SIZE(1),     0x01,
  HIDINPUT(1),        0x02,       //   Data, Var, Abs
  REPORT_COUNT(1),    0x01,       //   1 byte (unused)
  REPORT_SIZE(1),     0x08,
  HIDINPUT(1),        0x01,       //   Const, Array, Abs
  REPORT_COUNT(1),    0x06,       //   6 bytes (for up to 6 concurrently pressed keys)
  REPORT_SIZE(1),     0x08,
  LOGICAL_MINIMUM(1), 0x00,
  LOGICAL_MAXIMUM(1), 0x65,       //   101 keys
  USAGE_MINIMUM(1),   0x00,
  USAGE_MAXIMUM(1),   0x65,
  HIDINPUT(1),        0x00,       //   Data, Array, Abs
  REPORT_COUNT(1),    0x05,       //   5 bits (Num lock, Caps lock, Scroll lock, Compose, Kana)
  REPORT_SIZE(1),     0x01,
  USAGE_PAGE(1),      0x08,       //   LEDs
  USAGE_MINIMUM(1),   0x01,       //   Num Lock
  USAGE_MAXIMUM(1),   0x05,       //   Kana
  LOGICAL_MINIMUM(1), 0x00,
  LOGICAL_MAXIMUM(1), 0x01,
  HIDOUTPUT(1),       0x02,       //   Data, Var, Abs
  REPORT_COUNT(1),    0x01,       //   3 bits (Padding)
  REPORT_SIZE(1),     0x03,
  HIDOUTPUT(1),       0x01,       //   Const, Array, Abs
  END_COLLECTION(0)               // End application collection
};


BLEHIDDevice* hid;
BLECharacteristic* input;
BLECharacteristic* output;

const InputReport NO_KEY_PRESSED = { };


/*
   Callbacks related to BLE connection
*/
class BleKeyboardCallbacks : public BLEServerCallbacks {

    void onConnect(BLEServer* server) {
      isBleConnected = true;

      // Allow notifications for characteristics
      BLE2902* cccDesc = (BLE2902*)input->getDescriptorByUUID(BLEUUID((uint16_t)0x2902));
      cccDesc->setNotifications(true);

      Serial.println("Client has connected");
    }

    void onDisconnect(BLEServer* server) {
      isBleConnected = false;

      // Disallow notifications for characteristics
      BLE2902* cccDesc = (BLE2902*)input->getDescriptorByUUID(BLEUUID((uint16_t)0x2902));
      cccDesc->setNotifications(false);

      Serial.println("Client has disconnected");
    }
};


/*
   Called when the client (computer, smart phone) wants to turn on or off
   the LEDs in the keyboard.

   bit 0 - NUM LOCK
   bit 1 - CAPS LOCK
   bit 2 - SCROLL LOCK
*/
class OutputCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* characteristic) {
      OutputReport* report = (OutputReport*) characteristic->getData();
      Serial.print("LED state: ");
      Serial.print((int) report->leds);
      Serial.println();
    }
};


void bluetoothTask(void*) {

  // initialize the device
  BLEDevice::init(DEVICE_NAME);
  BLEServer* server = BLEDevice::createServer();
  server->setCallbacks(new BleKeyboardCallbacks());

  // create an HID device
  hid = new BLEHIDDevice(server);
  input = hid->inputReport(1); // report ID
  output = hid->outputReport(1); // report ID
  output->setCallbacks(new OutputCallbacks());

  // set manufacturer name
  hid->manufacturer()->setValue("Maker Community");
  // set USB vendor and product ID
  hid->pnp(0x02, 0xe502, 0xa111, 0x0210);
  // information about HID device: device is not localized, device can be connected
  hid->hidInfo(0x00, 0x02);

  // Security: device requires bonding
  BLESecurity* security = new BLESecurity();
  security->setAuthenticationMode(ESP_LE_AUTH_BOND);

  // set report map
  hid->reportMap((uint8_t*)REPORT_MAP, sizeof(REPORT_MAP));
  hid->startServices();

  // set battery level to 100%
  hid->setBatteryLevel(100);

  // advertise the services
  BLEAdvertising* advertising = server->getAdvertising();
  advertising->setAppearance(HID_KEYBOARD);
  advertising->addServiceUUID(hid->hidService()->getUUID());
  advertising->addServiceUUID(hid->deviceInfo()->getUUID());
  advertising->addServiceUUID(hid->batteryService()->getUUID());
  advertising->start();

  Serial.println("BLE ready");
  delay(portMAX_DELAY);
};


void typeText(const char* text) {
  int len = strlen(text);
  for (int i = 0; i < len; i++) {

    // translate character to key combination
    uint8_t val = (uint8_t)text[i];
    if (val > KEYMAP_SIZE)
      continue; // character not available on keyboard - skip
    KEYMAP map = keymap[val];

    // create input report
    InputReport report = {
      .modifiers = map.modifier,
      .reserved = 0,
      .pressedKeys = {
        map.usage,
        0, 0, 0, 0, 0
      }
    };

    // send the input report
    input->setValue((uint8_t*)&report, sizeof(report));
    input->notify();

    delay(5);

    // release all keys between two characters; otherwise two identical
    // consecutive characters are treated as just one key press
    input->setValue((uint8_t*)&NO_KEY_PRESSED, sizeof(NO_KEY_PRESSED));
    input->notify();

    delay(5);
  }
}
