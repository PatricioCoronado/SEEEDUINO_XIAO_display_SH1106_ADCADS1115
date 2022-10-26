/*
Prueba de concepto con el micro
SEEEDUINO XIAO con SAMD21,
un display I2C con chip SH1106
y un ADC ADS1115
Patricio Coronado Collado octubre 2022
*/
#include <Arduino.h>
#include "U8g2lib.h"
#include "Adafruit_ADS1015.h"
//Objetos
U8X8_SH1106_128X64_NONAME_HW_I2C display(U8X8_PIN_NONE); // Display OLED
Adafruit_ADS1115 ads;//ADC
//Funciones
void ini_display(int);
//Variables globales
short _adc0;
short _adc1;
short _adc2;
short _adc3;
String adc0;
String adc1;
String adc2;
String adc3;
float LSB;
/***************************************************
 *                  setup
****************************************************/
void setup() 
{
  display.begin();//Inicializa display
  ini_display(2);
  display.setBusClock(1000000);
  ads.begin();//Inicializa el ADC
  //Configuración del ADC y definición del LSB
  //ads1015.setGain(GAIN_ONE);      1x gain   +/- 4.096V  1 bit = 2mV
  //ads1015.setGain(GAIN_TWO);      2x gain   +/- 2.048V  1 bit = 1mV
  //ads1015.setGain(GAIN_FOUR);     4x gain   +/- 1.024V  1 bit = 0.5mV
  //ads1015.setGain(GAIN_EIGHT);    8x gain   +/- 0.512V  1 bit = 0.25mV
  //ads1015.setGain(GAIN_SIXTEEN);  16x gain  +/- 0.256V  1 bit = 0.125mV
  ads.setGain(GAIN_ONE);
  LSB=0.125F/1000.0; 
}
/***************************************************
 *                  loop
****************************************************/
void loop() 
{
  //Lee el ADC
  _adc0=ads.readADC_SingleEnded(0);
  _adc1=ads.readADC_SingleEnded(1);
  _adc2=ads.readADC_SingleEnded(2);
  //_adc3=ads.readADC_SingleEnded(3);
  //Conversión a STRING
  adc0=String(_adc0*LSB);adc0="A0="+adc0 +" V";
  adc1=String(_adc1*LSB);adc1="A1="+adc1 +" V";
  adc2=String(_adc2*LSB);adc2="A2="+adc2 +" V";
  //adc3=String(_adc3*LSB);adc3="A3="+adc3 +" V";
  display.clear();
  ini_display(1);
  display.inverse();
  display.drawUTF8(0, 1,"    ADS1115     ");
  ini_display(2);
  display.noInverse();
  display.drawUTF8(0, 2, adc0.c_str());
  display.drawUTF8(0, 4, adc1.c_str());
  display.drawUTF8(0, 6, adc2.c_str());
  delay(1000);
}
/****************************************************
 * configura el font del display
 *****************************************************/
void ini_display(int valor)
{
  switch (valor)
  {
  case 1:
    display.setFont(u8x8_font_5x8_f);
    break;
    case 2:
    display.setFont(u8x8_font_7x14_1x2_f);
    break;
  case 3:
    display.setFont(u8x8_font_8x13_1x2_f);
  break;
  default:
      display.setFont(u8x8_font_8x13_1x2_f);
  break;
  }
}
/****************************************************/