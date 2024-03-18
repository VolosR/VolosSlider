
#define LILYGO_TDISPLAY_AMOLED_SERIES
#include "LilyGo_AMOLED.h"    
#include <TFT_eSPI.h>  
#include "middleFont.h"
#include "hugeFatFont.h"
#include "fatFont.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite s1 = TFT_eSprite(&tft);
TFT_eSprite s2 = TFT_eSprite(&tft);
TFT_eSprite s3 = TFT_eSprite(&tft);
LilyGo_Class amoled;

int deb=0;
unsigned short grays[24];
unsigned short onOffColo[2]={TFT_RED,TFT_GREEN};

int slider[3];// each slider value 0-400 becouse touch region is 400px
int value[3];  // variable  stores value for each slider 0-255
bool onOff[3]={0,1,0}; //on of for each slider

void setup()
{
    amoled.begin();
    amoled.setBrightness(120);
    amoled.setRotation(1);
    s1.createSprite(80,536);
    s2.createSprite(80,536);
    s3.createSprite(80,536);

     //define level of grays or greys
     int co=240;
     for(int i=0;i<24;i++)
     {grays[i]=tft.color565(co, co, co);
     co=co-10;}

     draw1();
      draw2();
       draw3();
}

void draw1()
{
  s1.fillSprite(TFT_BLACK);
  s1.fillSmoothRoundRect(4,4,72,528,3,0x18E3,TFT_BLACK);
  s1.fillSmoothRoundRect(6, 6, 68, 88, 5, grays[19]);
  s1.loadFont(middleFont);
  s1.setTextColor(grays[8],grays[19]);
  s1.drawString("CH1",8,8,4);
  s1.unloadFont();

  s1.drawFastHLine(8, 38, 50, grays[11]);
  s1.fillSmoothCircle(50,18,6,onOffColo[onOff[0]],grays[19]);

  s1.loadFont(hugeFatFont);
  s1.setTextColor(grays[0],grays[19]);
  s1.drawString(String(value[0]),10,50,2);
  s1.unloadFont();
  drawGraRect(44, 520,slider[0], TFT_PURPLE, TFT_PINK,s1);
  amoled.pushColors(0, 0, 80, 536, (uint16_t *)s1.getPointer());
}

void draw2()
{
  s2.fillSprite(TFT_BLACK);
  s2.fillSmoothRoundRect(4,4,72,528,3,0x18E3,TFT_BLACK);
  s2.fillSmoothRoundRect(6, 6, 68, 88, 5, grays[19]);
  s2.loadFont(middleFont);
  s2.setTextColor(grays[8],grays[19]);
  s2.drawString("CH1",8,8,4);
  s2.unloadFont();

  s2.drawFastHLine(8, 38, 50, grays[11]);
  s2.fillSmoothCircle(50,18,6,onOffColo[onOff[1]],grays[19]);

  s2.loadFont(hugeFatFont);
  s2.setTextColor(grays[0],grays[19]);
  s2.drawString(String(value[1]),10,50,2);
  s2.unloadFont();
  drawGraRect(44, 520,slider[1], 0x02B0, 0x1D5E,s2);
  amoled.pushColors(80, 0, 80, 536, (uint16_t *)s2.getPointer());
}

void draw3()
{
  s3.fillSprite(TFT_BLACK);
  s3.fillSmoothRoundRect(4,4,72,528,3,0x18E3,TFT_BLACK);
  s3.fillSmoothRoundRect(6, 6, 68, 88, 5, grays[19]);
  s3.loadFont(middleFont);
  s3.setTextColor(grays[8],grays[19]);
  s3.drawString("CH1",8,8,4);
  s3.unloadFont();

  s3.drawFastHLine(8, 38, 50, grays[11]);
  s3.fillSmoothCircle(50,18,6,onOffColo[onOff[2]],grays[19]);

  s3.loadFont(hugeFatFont);
  s3.setTextColor(grays[0],grays[19]);
  s3.drawString(String(value[2]),10,50,2);
  s3.unloadFont();
  drawGraRect(44, 520,slider[2], 0x7B40, 0xF70A,s3);
  amoled.pushColors(160, 0, 80, 536, (uint16_t *)s3.getPointer());
}

void drawGraRect(int16_t x, int16_t y, int leng, uint16_t color_start, uint16_t color_end,TFT_eSprite &sprite) {

  for(int i=0;i<25;i++)
  if(i%6==0)
  sprite.drawWedgeLine(6,520-(i*17),22,520-(i*17),2,2,0x8430);
  else
  sprite.drawWedgeLine(12,520-(i*17),18,520-(i*17),1,1,0x8430);

  sprite.drawWedgeLine(x+5, y, x+5, 120, 5, 5,0x39E7,TFT_BLACK);
  sprite.drawSpot(x+5, y, 5, color_start);
  for (int16_t i = 0; i <= leng; i++) {
    // Interpolacija boje između početne i završne boje
    uint8_t interpolation = map(i, 0, leng, 0, 255);
    uint8_t red = map(interpolation, 0, 255, (color_start >> 8) & 0xF8, (color_end >> 8) & 0xF8);
    uint8_t green = map(interpolation, 0, 255, (color_start >> 3) & 0xFC, (color_end >> 3) & 0xFC);
    uint8_t blue = map(interpolation, 0, 255, (color_start << 3) & 0xF8, (color_end << 3) & 0xF8);
    uint16_t color = tft.color565(red, green, blue);

  sprite.fillRect(x,y-i,10,1,color); 
  }
  sprite.fillSmoothCircle(x+5, y-leng, 14,TFT_SILVER, TFT_BLACK);
  sprite.fillSmoothCircle(x+5, y-leng, 7,color_start,TFT_SILVER);
}

void loop()
{
   static int16_t x, y;
   bool touched = amoled.getPoint(&x, &y);
   if(touched)
  {
    if(y>100){
    int end=map(y,520,120,0,400);
    if(end>400) end=400;
    if(end<0) end=0;

    if(x>0 && x<80)
    {slider[0]=end; value[0]=map(end,0,400,0,255); draw1();}
     if(x>80 && x<160)
    {slider[1]=end;value[1]=map(end,0,400,0,255); draw2();}
     if(x>160 && x<240)
    {slider[2]=end;value[2]=map(end,0,400,0,255);draw3();}
    }

    if(y>2 && y<100)
    {
      if(deb==0)
        {
        deb=1;
         if(x>0 && x<80)
            {onOff[0]=!onOff[0]; draw1();}
         if(x>80 && x<160)
            {onOff[1]=!onOff[1]; draw2();}
         if(x>160 && x<240)
            {onOff[2]=!onOff[2];draw3();}
        } 
    }
  }else deb=0;




}





