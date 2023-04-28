int ldrpin = A0;   //ldr submits data to the arduino using this pin
int threshold = 30;  //ldr collects data and submits values to the arduino. the threshold for certain calculations are taken as 30. this is customizable
int blueled1 = 11;  //when the led's are connected to. these pins are also PWM pins because we will be using the analogWrite() command to control the brightness of the led's
int greenled2 = 10;
int redled3 = 9;

void setup() {
  Serial.begin(9600);
  pinMode(blueled1, OUTPUT); pinMode(greenled2, OUTPUT); pinMode(redled3, OUTPUT);  //these commands are to indicate the output signal is being sent to the three led pins 
  digitalWrite(blueled1, LOW); digitalWrite(greenled2, LOW); digitalWrite(redled3, LOW);  //these are to ensure that the led bulbs don't switch on during setup
  
}

void loop() {
  int data = analogRead(ldrpin);  //data is a variable in which the data collected by the ldr is submitted to the arduino via analog 0 pin
  Serial.println("");
  Serial.print("Light Sensor ");
  Serial.print("Value = ");
  Serial.print(data);
  delay(100);  //every 100 ms, data collected by the ldr is submitted to the arduino. if the value in the delay() command value is changed, the speed with which the led colors change also changes.

  if (data>750) {  //violet color
    analogWrite(blueled1, 127);
    digitalWrite(greenled2, LOW);
    analogWrite(redled3, 127);
    delay(100);
  } else {
    if (data<=750 && data>650) {  //violet to indigo color
      analogWrite(blueled1, (data/2.9));  //data is being divided by 2.9 because 750 (max intensity when ldr is ubjected to flashlight) / 255 (max frequency supported by arduino) = 2.9
      analogWrite(greenled2, 255-(data/2.9)); //255 - data value because we have used 7 colors (of the rainbow) and added an extra section (red in the end)
      analogWrite(redled3, (data/2.9)-228);
      delay(10);
    } else if (data<=650 && data>550) { //indigo to blue color
      analogWrite(blueled1, ((data+100)/2.9));  //+100 or +200 is to adjust the brightness of every value - as data value goes down, and isn't 750 anymore, the data/2.9 is not as bright as 255
      analogWrite(greenled2, ((data+100)/2.9)-191);  //and hence is very dim by the time the ambient surroundings become dark
      digitalWrite(redled3, LOW);
      delay(10);
    } else if (data<=550 && data>450) { //blue to green color
      analogWrite(blueled1, ((data+200)/2.9)-155);
      analogWrite(greenled2, ((data+200)/2.9));
      digitalWrite(redled3, LOW);
      delay(10);
    } else if (data<=450 && data>350) { //green to yellow color
      analogWrite(blueled1, ((data+300)/2.9)-119);
      analogWrite(greenled2, ((data+300)/2.9));
      analogWrite(redled3, ((data+300)/2.9)-119);
      delay(10);
    } else if (data<=350 && data>250) { //yellow to orange color
      analogWrite(blueled1, 0);
      analogWrite(greenled2, ((data+400)/2.9)-82));
      analogWrite(redled3, ((data+400)/2.9));
      delay(10);
    } else if (data<=250 && data>150) { //orange to red color
      analogWrite(blueled1, 0);
      analogWrite(greenled2, ((data+500)/2.9)-26);
      analogWrite(redled3, ((data+500)/2.9));
      delay(10);
    } else {  //red color
      digitalWrite(blueled1, LOW);
      digitalWrite(greenled2, LOW);
      analogWrite(redled3, ((data+600)/2.9));
      delay(10);
    }
  }
    //digitalWrite(led1, HIGH);
    //digitalWrite(led2, HIGH);
    //digitalWrite(led3, HIGH);
} 