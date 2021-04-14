#if 1

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>
#define MINPRESSURE 200
#define MAXPRESSURE 1000

//MARK: SCREEN CALIBRATION
//----------------------------------

// ALL Touch panels and wiring is DIFFERENT
// copy-paste results from TouchScreen_Calibr_native.ino
const int XP=8, XM=A2, YP=A3, YM=9; //240x320 ID=0x9341
const int TS_LEFT=120, TS_RT=933, TS_TOP=66, TS_BOT=885;
const int tx1=1, tx2=2, tx3=3;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

//MARK: DECLARE VARIABLES
const int pin2=2,pin3=3,pin5=5;

int number_of_carts = 0; //Number of carts

Adafruit_GFX_Button cart_increase_btn, cart_decrease_btn, next_screen_btn, log1_btn, log2_btn, log3_btn;

int pixel_x, pixel_y;     //Touch_getXY() updates global vars
bool Touch_getXY(void)
{
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
        pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());
    }
    return pressed;
}

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void setup(void)
{
//LCD SETUP
    Serial.begin(9600);
    uint16_t ID = tft.readID();
    Serial.print("Show BMP files on TFT with ID:0x");
    Serial.println(ID, HEX);
    if (ID == 0x0D3D3) ID = 0x9481;
    tft.begin(ID);

//    SETUP PINS
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin5, OUTPUT);

  
  
//MARK: SETUP CART IMAGE
    tft.fillScreen(BLACK);
  
//  MARK: SCREEN ONE SETUP
//    uint16_t ID = tft.readID();
    Serial.print("TFT ID = 0x");
    Serial.println(ID, HEX);
    Serial.println("Calibrate for your Touch Panel");
    cart_increase_btn.initButton(&tft, 50, 100, 50, 40, WHITE, CYAN, BLACK, "+", 2);
    cart_decrease_btn.initButton(&tft, 160, 100, 50, 40, WHITE, CYAN, BLACK, "-", 2);
    next_screen_btn.initButton(&tft, 100, 200, 100, 40, WHITE, CYAN, BLACK, "NEXT", 2);
    next_screen_btn.drawButton(false);
    cart_increase_btn.drawButton(false);
    cart_decrease_btn.drawButton(false);

//  MARK: SCRREN TWO SETUP
//    Serial.begin(9600);
//    uint16_t ID = tft.readID();
//    Serial.print("TFT ID = 0x");
//    Serial.println(ID, HEX);
//    Serial.println("Calibrate for your Touch Panel");
//    if (ID == 0xD3D3) ID = 0x9486; // write-only shield
//    tft.begin(ID);
//    tft.setRotation(0);            //PORTRAIT
//    tft.fillScreen(BLACK);

  delay(50);
}

void loop(void)
{
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin5, HIGH);
  
//  MARK: SCREEN ONE ACTIONS
  bool first_screen_touch = Touch_getXY();
  next_screen_btn.press(first_screen_touch && next_screen_btn.contains(pixel_x, pixel_y));
  cart_increase_btn.press(first_screen_touch && cart_increase_btn.contains(pixel_x, pixel_y));
  cart_decrease_btn.press(first_screen_touch && cart_decrease_btn.contains(pixel_x, pixel_y));

//DRAW SHOPPING CART
    tft.drawLine(98, 80, 102, 80, YELLOW);
    tft.drawLine(102, 80, 106, 98, YELLOW);
    tft.drawLine(103, 84, 120, 84, YELLOW);
    tft.drawLine(105, 94, 115, 94, YELLOW);
    tft.drawLine(120, 84, 115, 94, YELLOW);
    tft.drawLine(106, 98, 115, 98, YELLOW);
    tft.drawCircle(107,100,2, YELLOW);
    tft.drawCircle(115,100,2, YELLOW);


  if(cart_increase_btn.justReleased()) {
    number_of_carts++;


    tft.setTextColor(BLACK, CYAN);
    tft.setTextColor(CYAN, BLACK);
    tft.setTextSize(2);
    tft.setCursor(0, 10);
    tft.println("There are " +  String(number_of_carts)  + " carts.");
  }
  if(cart_decrease_btn.justReleased()) {
    number_of_carts--;
        tft.setTextColor(BLACK, CYAN);

    tft.setTextColor(CYAN, BLACK);
    tft.setTextSize(2);
    tft.setCursor(0, 10);
    tft.println("There are " +  String(number_of_carts)  + " carts.");
  }


  if(next_screen_btn.justReleased())
    {
      tft.fillScreen(BLACK);
          log1_btn.initButton(&tft,  100, 200, 100, 40, WHITE, CYAN, BLACK, "LOG1", 2);
    log2_btn.initButton(&tft, 100, 240, 100, 40, WHITE, CYAN, BLACK, "LOG2", 2);
    log3_btn.initButton(&tft, 100, 280, 100, 40, WHITE, CYAN, BLACK, "LOG3", 2);
    log1_btn.drawButton(false);
    log2_btn.drawButton(false);
    log3_btn.drawButton(false);
    tft.fillRect(40, 80, 160, 80, RED);
      tft.setTextColor(CYAN);
  tft.setTextSize(2);
  tft.setCursor(0, 10);
      tft.println("Hello, there are " +  String(number_of_carts)  + " carts. Select disinfectant level");
    }
    if (next_screen_btn.justPressed()) {
      Serial.println("PRESSED");
    }


// MARK: SCREEN TWO ACTIONS
    bool down = Touch_getXY();
    log1_btn.press(down && log1_btn.contains(pixel_x, pixel_y));
    log2_btn.press(down && log2_btn.contains(pixel_x, pixel_y));
    log3_btn.press(down && log3_btn.contains(pixel_x, pixel_y));
    if (log1_btn.justReleased()) {
//      Convert concatenated string to char array
//    String sendS = String(tx1) + "," + String(tx2)  + ",";
//    int inputLen = sizeof(sendS);
//      char copy[inputLen];
//      sendS.toCharArray(copy, inputLen);
//              Serial.write(copy);
//Serial.write('a');
        log1_btn.drawButton();
//          digitalWrite(pin2, LOW);
//          digitalWrite(pin3, HIGH);
//          digitalWrite(pin5, HIGH);
//          delay(number_of_carts * 2000);
    }
    else if (log2_btn.justReleased()) {
//                Serial.write("B\n");
        log2_btn.drawButton();

        //      Convert concatenated string to char array
    String sendS = String(tx1) + "," + String(tx2)  + ",";
    int inputLen = sizeof(sendS);
    char copy[inputLen];
    sendS.toCharArray(copy, inputLen);
//              Serial.write(copy);
//Serial.write('b');
//          digitalWrite(pin3, LOW);
//          digitalWrite(pin2, HIGH);
//          digitalWrite(pin5, HIGH);
//          delay(number_of_carts * 5000);
    }
    else if (log3_btn.justReleased()) {
                    //      Convert concatenated string to char array
//    String sendS = String(tx1) + "," + String(tx3)  + ",";
//    int inputLen = sizeof(sendS);
//    char copy[inputLen];
//    sendS.toCharArray(copy, inputLen);
//  Serial.write(copy);
//Serial.write('c');
    
        log3_btn.drawButton();
//          digitalWrite(pin5, LOW);
//          digitalWrite(pin2, HIGH);
//          digitalWrite(pin3, HIGH);
          
//          delay(number_of_carts * 9000);
    }

//    MARK: Number of chars. Convert int to string to char array then take char [0]
char b[2];
String str;
str=String(number_of_carts);
str.toCharArray(b,2);


    if (log1_btn.justPressed()) {
Serial.write('<');
Serial.write('a');
Serial.write(b[0]);
Serial.write('>');
        
        log1_btn.drawButton(true);
        tft.fillRect(40, 80, 160, 80, GREEN);
        delay(5000);
    }
    else if (log2_btn.justPressed()) {
  Serial.write('<');
  Serial.write('b');
  Serial.write(b[0]);
  Serial.write('>');

      
        log2_btn.drawButton(true);
        tft.fillRect(40, 80, 160, 80, RED);
                delay(5000);
    }
   else if (log3_btn.justPressed()) {
  Serial.write('<');
  Serial.write('c');
  Serial.write(b[0]);
  Serial.write('>');
        log3_btn.drawButton(true);
        tft.fillRect(40, 80, 160, 80, CYAN);
                delay(5000);
    }
}
#endif
