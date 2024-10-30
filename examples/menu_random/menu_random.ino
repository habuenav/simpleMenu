#define LIBRARY 0 //establecer en 0 para usar U8g2lib y 1 para usar Adafruit_GFX
#include "Arduino.h"
#include <sm.h>
#include <Wire.h>

//ADAFRUIT GFX
//#define SCREEN_WIDTH 128  // 128x64 es la resolucion mas comun, invertir para pantallas verticales  y usar setRotation(1);
//#define SCREEN_HEIGHT 64 // para pantallas 0.91 poner 32 en lugar de 64
//#define SCREEN_ADDRESS 0x3C //la direccion i2c mas usada por las pantallas oled chinas

// inicializacion para pantallas de 0.96 y 0.91
//#include <Adafruit_SSD1306.h> 
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);  
//#include <Adafruit_SH110X.h>
//Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); //inicializacion para pantallas de 1.3
//Adafruit_SH1107 display = Adafruit_SH1107(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1, 1000000, 100000); //inicializacion para pantallas de 0.96 vertical y 0.78 vertical

//U8g2lib
//U8G2_SH1106_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE); //inicializacion para pantalla 1.3 128x64
//U8G2_SH1107_64X128_F_HW_I2C display(U8G2_R1, U8X8_PIN_NONE);  //inicializacion para pantalla 0.96 vertical 64x128
//U8G2_SH1107_TK078F288_80X128_F_HW_I2C display(U8G2_R1, U8X8_PIN_NONE);  //inicializacion para pantalla 0.78 vertical 80x128
//U8G2_SH1107_TK078F288_64X128_F_HW_I2C display(U8G2_R1, U8X8_PIN_NONE);  //inicializacion para pantalla 0.96 vertical 64x128 *version modificada por mi
U8G2_SSD1306_128X64_NONAME_F_HW_I2C display(U8G2_R0,U8X8_PIN_NONE); // inicializacion para pantalla 0.96 128x64
//U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C display(U8G2_R0,U8X8_PIN_NONE); // inicializacion para pantalla 0.91 128x32
//U8G2_SSD1306_64X32_1F_F_HW_I2C display(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); //inicializacion para pantalla 0.49 64x32
//U8G2_SSD1306_72X40_ER_F_HW_I2C display(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); // inicializacion para pantalla 72x40 0.42 
//U8G2_ST7567_ENH_DG128064I_F_HW_I2C display2(U8G2_R2,U8X8_PIN_NONE); //inicializacion para pantalla de 2.4 128x64 - with contrast about 230
//U8G2_ST7567_JLX12864_F_HW_I2C  display(U8G2_R2,U8X8_PIN_NONE);      // contraste al rededor de  150 por probar
//U8G2_ST7567_OS12864_F_HW_I2C     display(U8G2_R2,U8X8_PIN_NONE);    // contraste al rededor de 25 por probar

sm Menu(display);
txtMenu  opciones[]=  {
    "Menu",
    "opc 1",
    "opc 2",
    "opc 3",
  };
txtMenu  op1[]=  {
    "SubMenu",
    "opc A",
    "opc B",
    "Salir"
  };  

void setup() {
Serial.begin(115200);
/* configuraciones validas para el driver Adafruit
display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS); //begin 1306 pantallas 0.96 y 0.91
display.begin(SCREEN_ADDRESS, true); //begin 110x pantalla 1.3 y 0.96 vertical
display.clearDisplay();
display.display();
display.setRotation(0);
*/
  
// u8g2
//display.setI2CAddress (0x7E); //display ST7567
display.begin();
/* opciones validas para u8g2
display.setDisplayRotation(U8G2_R2);//display ST7567
Menu.titleFont=u8g2_font_ncenB08_tr; 
Menu.itemFont=u8g2_font_ncenB08_tr;
*/
//Menu.setAutoOff(15); //establece un autoapagado en 15 segundos
delay(1000); // Pausa por 1 segundo
//Menu.interline=4;
//Menu.Assign(opciones,0); 
Menu.Root(opciones,"root");
Menu.Show(); 

}

void loop() {

delay(1000);
if(Menu.Select(1,"root")){Menu.Assign(op1,"op1"); Menu.Show(); }
delay(1000);
Menu.Down();Menu.Show(); 
delay(1000);
Menu.Down();Menu.Show(); 
delay(1000);
if(Menu.Select(3,"op1")){Menu.Message("Salir",CENTER,800); Menu.Root(); Menu.Show(); }
delay(1000);
Menu.Down();Menu.Show(); 
delay(1000);
Menu.Down();Menu.Show(); 
delay(1000);
}
