#include "BluetoothSerial.h" 
#include <AceButton.h>
using namespace ace_button;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run
`make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;


// define the GPIO connected with Relays and switches
#define RelayPin5 23  
#define RelayPin6 22
#define RelayPin7 21 
#define RelayPin8 19
#define RelayPin1 18  
#define RelayPin2 5
#define RelayPin3 16 
#define RelayPin4 17    


#define SwitchPin1 34 
#define SwitchPin2 35  
#define SwitchPin3 32  
#define SwitchPin4 33
#define SwitchPin5 25 
#define SwitchPin6 26  
#define SwitchPin7 27  
#define SwitchPin8 14  


int toggleState_1 = 1; //Define integer to remember the toggle state for relay 1
int toggleState_2 = 1; //Define integer to remember the toggle state for relay 2
int toggleState_3 = 1; //Define integer to remember the toggle state for relay 3
int toggleState_4 = 1; //Define integer to remember the toggle state for relay 4
int toggleState_5 = 1; //Define integer to remember the toggle state for relay 1
int toggleState_6 = 1; //Define integer to remember the toggle state for relay 2
int toggleState_7 = 1; //Define integer to remember the toggle state for relay 3
int toggleState_8 = 1; //Define integer to remember the toggle state for relay 4

char bt_data; // variable for storing bluetooth data 

ButtonConfig config1;
AceButton button1(&config1);
ButtonConfig config2;
AceButton button2(&config2);
ButtonConfig config3;
AceButton button3(&config3);
ButtonConfig config4;
AceButton button4(&config4);
ButtonConfig config5;
AceButton button5(&config5);
ButtonConfig config6;
AceButton button6(&config6);
ButtonConfig config7;
AceButton button7(&config7);
ButtonConfig config8;
AceButton button8(&config8);



void handleEvent1(AceButton*, uint8_t, uint8_t);
void handleEvent2(AceButton*, uint8_t, uint8_t);
void handleEvent3(AceButton*, uint8_t, uint8_t);
void handleEvent4(AceButton*, uint8_t, uint8_t);
void handleEvent5(AceButton*, uint8_t, uint8_t);
void handleEvent6(AceButton*, uint8_t, uint8_t);
void handleEvent7(AceButton*, uint8_t, uint8_t);
void handleEvent8(AceButton*, uint8_t, uint8_t);



void all_Switch_ON(){
  digitalWrite(RelayPin1, LOW); toggleState_1 = 0; delay(100);
  digitalWrite(RelayPin2, LOW); toggleState_2 = 0; delay(100);
  digitalWrite(RelayPin3, LOW); toggleState_3 = 0; delay(100);
  digitalWrite(RelayPin4, LOW); toggleState_4 = 0; delay(100);
  digitalWrite(RelayPin5, LOW); toggleState_5 = 0; delay(100);
  digitalWrite(RelayPin6, LOW); toggleState_6 = 0; delay(100);
  digitalWrite(RelayPin7, LOW); toggleState_7 = 0; delay(100);
  digitalWrite(RelayPin8, LOW); toggleState_8 = 0; delay(100);

}

void all_Switch_OFF(){
  digitalWrite(RelayPin1, HIGH); toggleState_1 = 1; delay(100);
  digitalWrite(RelayPin2, HIGH); toggleState_2 = 1; delay(100);
  digitalWrite(RelayPin3, HIGH); toggleState_3 = 1; delay(100);
  digitalWrite(RelayPin4, HIGH); toggleState_4 = 1; delay(100);
  digitalWrite(RelayPin5, HIGH); toggleState_5 = 1; delay(100);
  digitalWrite(RelayPin6, HIGH); toggleState_6 = 1; delay(100);
  digitalWrite(RelayPin7, HIGH); toggleState_7 = 1; delay(100);
  digitalWrite(RelayPin8, HIGH); toggleState_8 = 1; delay(100);

}

void Bluetooth_handle()
{
  bt_data = SerialBT.read();
//  Serial.println(bt_data);
  delay(20);

  switch(bt_data)
      {
        case 'a': digitalWrite(RelayPin1, HIGH);  toggleState_1 = 0; break; // if 'A' received Turn on Relay1
        case 'A': digitalWrite(RelayPin1, LOW);   toggleState_1 = 1; break; // if 'a' received Turn off Relay1
        case 'b': digitalWrite(RelayPin2, HIGH);  toggleState_2 = 0; break; // if 'B' received Turn on Relay2
        case 'B': digitalWrite(RelayPin2, LOW);   toggleState_2 = 1; break; // if 'b' received Turn off Relay2
        case 'c': digitalWrite(RelayPin3, HIGH);  toggleState_3 = 0; break; // if 'C' received Turn on Relay3
        case 'C': digitalWrite(RelayPin3, LOW);   toggleState_3 = 1; break; // if 'c' received Turn off Relay3
        case 'd': digitalWrite(RelayPin4, HIGH);  toggleState_4 = 0; break; // if 'D' received Turn on Relay4
        case 'D': digitalWrite(RelayPin4, LOW);   toggleState_4 = 1; break; // if 'd' received Turn off Relay4
        
        case 'e': digitalWrite(RelayPin5, HIGH);  toggleState_5 = 0; break; // if 'A' received Turn on Relay1
        case 'E': digitalWrite(RelayPin5, LOW);   toggleState_5 = 1; break; // if 'a' received Turn off Relay1
        case 'f': digitalWrite(RelayPin6, HIGH);  toggleState_6 = 0; break; // if 'B' received Turn on Relay2
        case 'F': digitalWrite(RelayPin6, LOW);   toggleState_6 = 1; break; // if 'b' received Turn off Relay2
        case 'g': digitalWrite(RelayPin7, HIGH);  toggleState_7 = 0; break; // if 'C' received Turn on Relay3
        case 'G': digitalWrite(RelayPin7, LOW);   toggleState_7 = 1; break; // if 'c' received Turn off Relay3
        case 'h': digitalWrite(RelayPin8, HIGH);  toggleState_8 = 0; break; // if 'D' received Turn on Relay4
        case 'H': digitalWrite(RelayPin8, LOW);   toggleState_8 = 1; break; // if 'd' received Turn off Relay4
        case 'I': all_Switch_ON(); break;  // if 'Z' received Turn on all Relays
        case 'i': all_Switch_OFF(); break; // if 'z' received Turn off all Relays
        default : break;
      }
}

void setup()
{
  Serial.begin(9600);

  btStart();  //Serial.println("Bluetooth On");
  
  SerialBT.begin("HA_BT_ESP32"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  delay(5000);

  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);
  
  pinMode(RelayPin5, OUTPUT);
  pinMode(RelayPin6, OUTPUT);
  pinMode(RelayPin7, OUTPUT);
  pinMode(RelayPin8, OUTPUT);

//  pinMode(wifiLed, OUTPUT);

  pinMode(SwitchPin1, INPUT_PULLUP);
  pinMode(SwitchPin2, INPUT_PULLUP);
  pinMode(SwitchPin3, INPUT_PULLUP);
  pinMode(SwitchPin4, INPUT_PULLUP);
  
  pinMode(SwitchPin5, INPUT_PULLUP);
  pinMode(SwitchPin6, INPUT_PULLUP);
  pinMode(SwitchPin7, INPUT_PULLUP);
  pinMode(SwitchPin8, INPUT_PULLUP);


  //During Starting all Relays should TURN OFF
  digitalWrite(RelayPin1, toggleState_1);
  digitalWrite(RelayPin2, toggleState_2);
  digitalWrite(RelayPin3, toggleState_3);
  digitalWrite(RelayPin4, toggleState_4);
  digitalWrite(RelayPin5, toggleState_5);
  digitalWrite(RelayPin6, toggleState_6);
  digitalWrite(RelayPin7, toggleState_7);
  digitalWrite(RelayPin8, toggleState_8);
 

  config1.setEventHandler(button1Handler);
  config2.setEventHandler(button2Handler);
  config3.setEventHandler(button3Handler);
  config4.setEventHandler(button4Handler);
  
  config5.setEventHandler(button5Handler);
  config6.setEventHandler(button6Handler);
  config7.setEventHandler(button7Handler);
  config8.setEventHandler(button8Handler);


  button1.init(SwitchPin1);
  button2.init(SwitchPin2);
  button3.init(SwitchPin3);
  button4.init(SwitchPin4);
  
  button5.init(SwitchPin5);
  button6.init(SwitchPin6);
  button7.init(SwitchPin7);
  button8.init(SwitchPin8);


  delay(200);
}

void loop()
{  
  if (SerialBT.available()){
   Bluetooth_handle();
 }

  button1.check();
  button2.check();
  button3.check();
  button4.check();
  
  button5.check();
  button6.check();
  button7.check();
  button8.check();

}


void button1Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT1");
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("kEventPressed");
      toggleState_1 = 0;
      digitalWrite(RelayPin1, LOW);
      break;
    case AceButton::kEventReleased:
      Serial.println("kEventReleased");
      toggleState_1 = 1;
      digitalWrite(RelayPin1, HIGH);
      break;
  }
}

void button2Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT2");
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("kEventPressed");
      toggleState_2 = 0;
      digitalWrite(RelayPin2, LOW);
      break;
    case AceButton::kEventReleased:
      Serial.println("kEventReleased");
      toggleState_2 = 1;
      digitalWrite(RelayPin2, HIGH);
      break;
  }
}

void button3Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT3");
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("kEventPressed");
      toggleState_3 = 0;
      digitalWrite(RelayPin3, LOW);
      break;
    case AceButton::kEventReleased:
      Serial.println("kEventReleased");
      toggleState_3 = 1;
      digitalWrite(RelayPin3, HIGH);
      break;
  }
}

void button4Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT4");
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("kEventPressed");
      toggleState_4 = 0;
      digitalWrite(RelayPin4, LOW);
      break;
    case AceButton::kEventReleased:
      Serial.println("kEventReleased");
      toggleState_4 = 1;
      digitalWrite(RelayPin4, HIGH);
      break;
  }
}

void button5Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT5");
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("kEventPressed");
      toggleState_5 = 0;
      digitalWrite(RelayPin5, LOW);
      break;
    case AceButton::kEventReleased:
      Serial.println("kEventReleased");
      toggleState_5 = 1;
      digitalWrite(RelayPin5, HIGH);
      break;
  }
}

void button6Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT6");
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("kEventPressed");
      toggleState_6 = 0;
      digitalWrite(RelayPin6, LOW);
      break;
    case AceButton::kEventReleased:
      Serial.println("kEventReleased");
      toggleState_6 = 1;
      digitalWrite(RelayPin6, HIGH);
      break;
  }
}

void button7Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT7");
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("kEventPressed");
      toggleState_7 = 0;
      digitalWrite(RelayPin7, LOW);
      break;
    case AceButton::kEventReleased:
      Serial.println("kEventReleased");
      toggleState_7 = 1;
      digitalWrite(RelayPin7, HIGH);
      break;
  }
}

void button8Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT8");
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("kEventPressed");
      toggleState_8 = 0;
      digitalWrite(RelayPin8, LOW);
      break;
    case AceButton::kEventReleased:
      Serial.println("kEventReleased");
      toggleState_8 = 1;
      digitalWrite(RelayPin8, HIGH);
      break;
  }
}
