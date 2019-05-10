
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   { 
  pinMode(13,OUTPUT);             
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  delay(2000);
  }

void loop() {
  display.setTextColor(WHITE);
  displayT();
  display.display();
  delay(500);
  display.clearDisplay();
}

void test1(void) // Function for showing the name
{
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(33,3);
  display.println("IrriG");

}

void test2(void) //Function to show data of the first probe 
{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10,25);
  display.println("Moisture A :");
}

void test3(void) //Function to show data of second probe
{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10,35);
  display.println("Moisture B :");
}

void Value1(void) // Function for observing the data
{
  int p = analogRead(A0);
  Serial.println(p);   //Serial printing is done to archieve the data through python  
  int q = analogRead(A1);
    
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(95,25);
  display.println(p);
  display.display();
  display.setCursor(95,35);
  display.println(q);

  display.display();
    if(p>530){
      digitalWrite(13,HIGH);
  }
    else{
      digitalWrite(13,LOW);
  }
}

void displayT(void) // Function to make the grapics for OLLED
{
  for(int i=0;i<=128;i++){
    display.drawPixel(i, 0, WHITE);
    display.drawPixel(i, 63, WHITE);
    display.drawPixel(i, 20, WHITE);
    display.drawPixel(i, 46, WHITE);
  }
  for(int j=0;j<=63;j++){
    display.drawPixel(0, j, WHITE);
    display.drawPixel(127, j, WHITE);
  }
  test1();
  test2();
  test3();
  Value1();
}
  
