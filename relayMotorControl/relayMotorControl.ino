int m1pow = 5;
int m1dir = 3;
// motor2dir in2 = 2;
int m2dir = 2;
int m2pow = 6;


// int ENA = 5;
// int in1 = 3;
// int in2 = 2;
int log1led = 8;
int log2led = 9;
int log3led = 10;
#define SOP '<'
#define EOP '>'

bool started = false;
bool ended = false;

char inData[80];
byte index;


void setup()
{
  pinMode(m1pow, OUTPUT);
  pinMode(m1dir, OUTPUT);
  pinMode(m2dir, OUTPUT);
  pinMode(m2pow, OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(50);

}

void loop() {
digitalWrite(m1dir, HIGH);
digitalWrite(m2dir, HIGH);
 while(Serial1.available() > 0)
  {
    char inChar = Serial1.read();
    if(inChar == SOP)
    {
       index = 0;
       inData[index] = '\0';
       started = true;
       ended = false;
    }
    else if(inChar == EOP)
    {
       ended = true;
       break;
    }
    else
    {
      if(index < 79)
      {
        inData[index] = inChar;
        index++;
        inData[index] = '\0';
      }
    }
  }

delay(1000);

    if(started && ended)
  {
    // The end of packet marker arrived. Process the packet
    Serial.println(inData[0]);
    Serial.println(inData[1]);
    int no_carts = inData[1] - '0';
    char log_value = inData[0];
    if (log_value == 97) {
      Serial.println("Log1");


    analogWrite(m1pow, 255);
    analogWrite(m2pow, 255);
    digitalWrite(log1led,HIGH);
    delay(no_carts * 1000);
    analogWrite(m1pow, 0);
    analogWrite(m2pow, 0);
    digitalWrite(log1led,LOW);
    } else if (log_value == 98) {
      Serial.println("Log2");
    analogWrite(m1pow, 130);
    analogWrite(m2pow, 130);
    digitalWrite(log2led,HIGH);
    delay(no_carts * 2000);
    analogWrite(m1pow, 0);
    analogWrite(m2pow, 0);
    digitalWrite(log2led,LOW);
    } else if (log_value == 99) {
      Serial.println("Log3");
    analogWrite(m1pow, 80);
    analogWrite(m2pow, 80);
    digitalWrite(log3led,HIGH);
    delay(no_carts * 3000);
    analogWrite(m1pow, 0);
    analogWrite(m2pow, 0);
    digitalWrite(log3led,LOW);
    }  
    // Reset for the next packet
    started = false;
    ended = false;
    index = 0;
    inData[index] = '\0';
  }
}

 
//  digitalWrite(in1, LOW);
//  digitalWrite(in2, HIGH);
//  for (int i = 0; i < 255; i++) // increase motor speed from 0 to max
//  {  
//    analogWrite(ENA, i);
//    delay(40);
//  }
//  for (int i = 255; i > 0; --i) //Decrease motor speed from max to 0
//  {
//    analogWrite(ENA, i);
//    delay(40);
//  }
//}
//
