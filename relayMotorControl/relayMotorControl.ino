int relay5 = 2; // Relay
int relay6 = 3;
int relay7 = 4;
int relay8 = 5;
#define SOP '<'
#define EOP '>'

bool started = false;
bool ended = false;

char inData[80];
byte index;

void setup()
{

  pinMode(relay5, OUTPUT);// set pin as output for relay 1
  pinMode(relay6, OUTPUT);// set pin as output for relay 2
  pinMode(relay7, OUTPUT);// set pin as output for relay 3
  pinMode(relay8, OUTPUT);// set pin as output for relay 4
  Serial.begin(9600);
  Serial1.begin(9600);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  digitalWrite(relay8, HIGH);

  delay(50);

}

void loop() {

  while (Serial1.available() > 0)
  {
    char inChar = Serial1.read();
    if (inChar == SOP)
    {
      index = 0;
      inData[index] = '\0';
      started = true;
      ended = false;
    }
    else if (inChar == EOP)
    {
      ended = true;
      break;
    }
    else
    {
      if (index < 79)
      {
        inData[index] = inChar;
        index++;
        inData[index] = '\0';
      }
    }
  }

  delay(500); // allow time to receive data 1000ms works great

  if (started && ended)
  {
    // The end of packet marker arrived. Process the packet
    Serial.println(inData[0]);
    Serial.println(inData[1]);
    int no_carts = inData[1] - '0';
    char log_value = inData[0];

//    Depending on the log alpha char received change relay duration
    if (log_value == 97) {
      Serial.println("Log1");
      relayOnOff(no_carts, 5000);
    } else if (log_value == 98) {
      Serial.println("Log2");
      relayOnOff(no_carts, 10000);
    } else if (log_value == 99) {
      Serial.println("Log3");
      relayOnOff(no_carts, 15000);

    }
    // Reset for the next packet
    started = false;
    ended = false;
    index = 0;
    inData[index] = '\0';
  }
}

void relayOnOff(int no_carts, int delayMS)
  {
      Serial.println("Log3");
      digitalWrite(relay5, LOW);// turn relay 1 ON
      digitalWrite(relay6, LOW);// turn relay 2 ON
      digitalWrite(relay7, LOW);// turn relay 3 ON
      digitalWrite(relay8, LOW);// turn relay 4 ON

      delay(no_carts * 15000);

      // stop the motor
      digitalWrite(relay5, HIGH);// turn relay 1 OFF
      digitalWrite(relay6, HIGH);// turn relay 2 OFF
      digitalWrite(relay7, HIGH);// turn relay 3 OFF
      digitalWrite(relay8, HIGH);// turn relay 4 OFF
  }
