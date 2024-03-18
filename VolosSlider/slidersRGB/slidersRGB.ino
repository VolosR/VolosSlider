
#define LILYGO_TDISPLAY_AMOLED_SERIES
#include "LilyGo_AMOLED.h"    
#include <TFT_eSPI.h>  
#include "middleFont.h"
#include "hugeFatFont.h"
#include "fatFont.h"
#include "smallFont.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite s1 = TFT_eSprite(&tft);
TFT_eSprite s2 = TFT_eSprite(&tft);
TFT_eSprite s3 = TFT_eSprite(&tft);
TFT_eSprite s4 = TFT_eSprite(&tft);
TFT_eSprite spr = TFT_eSprite(&tft);
LilyGo_Class amoled;

int deb=0;
int chosen=0;  // chosen shape , background, text, circle
unsigned short grays[24];
unsigned short onOffColo[2]={TFT_RED,TFT_GREEN};
unsigned short tmpColors[3];
String lbl[3]={"B","T","S"};

int slider[3][3];// each slider value 0-400 becouse touch region is 400px
int value[3][3]={{20,20,20},
                 {200,230,200},
                 {50,60,150}};  // variable taht stores value for each slider 0-255
int brightnes=120;

void setup()
{
    amoled.begin();
    amoled.setBrightness(brightnes);
    amoled.setRotation(1);
    s1.createSprite(60,420);
    s2.createSprite(60,420);
    s3.createSprite(60,420);
    s4.createSprite(60,420);
    spr.createSprite(232,110);

     //define level of grays or greys
     int co=240;
     for(int i=0;i<24;i++)
     {grays[i]=tft.color565(co, co, co);
     co=co-10;}

     for(int i=0;i<3;i++)
       {tmpColors[i]=tft.color565(value[i][0], value[i][1], value[i][2]);
       for(int j=0;j<3;j++)
       slider[i][j]=map(value[i][j],0,255,0,384);
       }

    draw();
     draw1();
      draw2();
       draw3();
        draw4();

}

void draw()
{
  spr.fillSprite(TFT_BLACK);
  //spr.fillSprite(tft.color565(value[0][0], value[0][1], value[0][2]));
  spr.loadFont(fatFont);
  spr.setTextColor(grays[10],TFT_BLACK);
  spr.drawString("R: ",0,0);
  spr.drawString("G: ",0,30);
  spr.drawString("B: ",0,60);

  spr.setTextColor(grays[5],TFT_BLACK);
  spr.drawString(String(value[chosen][0]),26,0);
  spr.drawString(String(value[chosen][1]),26,30);
  spr.drawString(String(value[chosen][2]),26,60);
  
 
  spr.fillRect(112,80,120,30,0xCE01);
  spr.setTextColor(TFT_BLACK,0xCE01);
  tmpColors[chosen]=tft.color565(value[chosen][0], value[chosen][1], value[chosen][2]);
 
  spr.drawString("0x"+String(tmpColors[chosen],HEX),130,83);
   spr.unloadFont();
    spr.loadFont(smallFont);
    spr.setTextColor(0xBD41,TFT_BLACK);
    spr.drawString("BCKLIGHT: "+String(brightnes),0,92);
    spr.unloadFont();


    spr.fillSmoothRoundRect(100, 0, 132, 74, 4, tmpColors[0],TFT_BLACK);
     spr.fillRoundRect(74, 30, 32, 44, 4, tmpColors[0]);
    spr.loadFont(fatFont);
    spr.setTextColor(tmpColors[1],tmpColors[0]);
    spr.drawString("Hello!",116,4);
    spr.unloadFont();
    spr.loadFont(smallFont);
    spr.drawString("This is Text :)",83,42);
       spr.setTextColor(grays[6],grays[15]);
       spr.fillSmoothRoundRect(74, 0, 22, 26, 2, grays[15]);
       spr.drawString(lbl[chosen],80,4);
    spr.unloadFont();
    spr.fillRect(190,4,30,26,tmpColors[2]);
    spr.fillRect(200,36,18,24,tmpColors[2]);
  amoled.pushColors(4, 4, 232, 110, (uint16_t *)spr.getPointer());
}

void draw1()
{
  s1.fillSprite(TFT_BLACK);
  s1.fillSmoothRoundRect(2,2,56,406,3,0x18E3,TFT_BLACK);
  drawGraRect(36, 400,slider[chosen][0], 0x6061, 0xFB92,s1);
  amoled.pushColors(0, 116, 60, 420, (uint16_t *)s1.getPointer());
}

void draw2()
{
  s2.fillSprite(TFT_BLACK);
  s2.fillSmoothRoundRect(2,2,56,406,3,0x18E3,TFT_BLACK);
  drawGraRect(36, 400,slider[chosen][1], 0x0A26, 0x1FD7,s2);
  amoled.pushColors(60, 116, 60, 420, (uint16_t *)s2.getPointer());
}

void draw3()
{
  s3.fillSprite(TFT_BLACK);
  s3.fillSmoothRoundRect(2,2,56,406,3,0x18E3,TFT_BLACK);
  drawGraRect(36, 400,slider[chosen][2], 0x02B0, 0x1D5E,s3);
  amoled.pushColors(120, 116, 60, 420, (uint16_t *)s3.getPointer());
}

void draw4()
{
  s4.fillSprite(TFT_BLACK);
  s4.fillSmoothRoundRect(2,2,56,406,3,0x18E3,TFT_BLACK);
  drawGraRect(36, 400,map(brightnes,0,255,0,384), 0x7B40, 0xF70A,s4);
  amoled.pushColors(180, 116, 60, 420, (uint16_t *)s4.getPointer());
}

void drawGraRect(int16_t x, int16_t y, int leng, uint16_t color_start, uint16_t color_end,TFT_eSprite &sprite) {

  for(int i=0;i<25;i++)
  if(i%6==0)
  sprite.drawWedgeLine(4,y-(i*16),18,y-(i*16),2,2,0x8430);
  else
  sprite.drawWedgeLine(10,y-(i*16),14,y-(i*16),1,1,0x8430);

  sprite.drawWedgeLine(x+5, y, x+5, 10, 5, 5,0x39E7,TFT_BLACK);
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
    if(y>110){
    int end=map(y,516,132,0,384);
    if(end>384) end=384;
    if(end<0) end=0;

    if(x>0 && x<60)
    {slider[chosen][0]=end; value[chosen][0]=map(end,0,384,0,255); draw1(); draw();}
     if(x>60 && x<120)
    {slider[chosen][1]=end;value[chosen][1]=map(end,0,384,0,255); draw2(); draw();}
     if(x>120 && x<180)
    {slider[chosen][2]=end;value[chosen][2]=map(end,0,384,0,255);draw3(); draw();}
     if(x>180 && x<240)
    {brightnes=map(end,0,384,0,255);draw4(); draw(); amoled.setBrightness(brightnes); }
    }

    if(y<70)
    {
      if(deb==0)
      {deb=1; chosen++; if(chosen==3) chosen=0; draw(); draw1(); draw2(); draw3();}
    }

 
  }else deb=0;
}





