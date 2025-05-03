#include <at89c5131.h>
#include "lcd.h"

sbit out = P0^7;

void debounce_delay(void);
void rowi(int i);
void output(int r, int c);
void led_disp(int r, int c);
//void speaker(int r, int c);
void tone_delay(int r, int c);
code unsigned char sa[]="Sa";						
code unsigned char re[]="Re";						
code unsigned char ga[]="Ga";						
code unsigned char ma[]="Ma";						
code unsigned char pa[]="Pa";						
code unsigned char dha[]="Dha";					
code unsigned char ni[]="Ni";						
code unsigned char sa_high[]="Sa_High";						
code unsigned char silence[]="Silence";						

void main(void)
{
int row_idx = 0;
int column_idx = 0;
out = 1;

while(1){
//BLOCK 1
P3 = 0X0F;
	
do{
	led_disp(row_idx, column_idx);
	output(row_idx, column_idx);
	if(row_idx != 0 && column_idx != 0)
	{
	if((row_idx != 3) || (column_idx != 3))
	{
	while(P3 != 0X0F)
	{
		//speaker(row_idx, column_idx);
	  out = ~out;
    tone_delay(row_idx, column_idx);
	}
  }
  }
}while(P3 != 0X0F);
	led_disp(0, 0);

ACC = 0XFF;

//BLOCK 2
do{
P3 = 0X0F;
}while(P3 == 0X0F);

P2 = 0X00;
debounce_delay();
P2 = 0XFF;

do{
P3 = 0X0F;///////////////////////////
}while(P3 == 0X0F);

//BLOCK 3
row_idx = 1;
rowi(row_idx);
if(ACC == 0X0F)
{
 row_idx = row_idx + 1;
 rowi(row_idx);
 if(ACC == 0X0F)
 {
	row_idx = row_idx + 1;
  rowi(row_idx);
 }
}
if(ACC == 0X07)
{column_idx = 1;}
else if(ACC == 0X0B)
{column_idx = 2;}
else if(ACC == 0X0D)
{column_idx = 3;}

}
}

void debounce_delay(void)
{
	TMOD = 0X10;
	TL1 = 0xC0; //Starting Count value
	TH1 = 0x63;
	TR1 = 1; //Start bit indicates the counting starts
	while(TF1 == 0); //Checks overflow that is FFFFH to 0000H
	TR1 = 0; //Stops the timer
	TF1 = 0;
}
	
void rowi(int i)
{
if(i == 1)
{P3 = 0XEF; /*11101111*/}
else if(i == 2)
{P3 = 0XDF; /*11011111*/}
else if(i == 3)
{P3 = 0XBF; /*10111111*/}
ACC = P3;
ACC = ACC & 0X0F;
}

void output(int r, int c)
{
	if(r == 0 && c == 0)
	{P1 = 0;}
	switch(r){
	case 1:
		if(c == 1)
		//{P1 = 24;}
		{P1 = 16;}
		else if(c == 2)
		//{P1 = 27;}
		{P1 = 32;}
		else if(c == 3)
		//{P1 = 30;}
		{P1 = 48;}
  break;
  case 2:
		if(c == 1)
		//{P1 = 32;}
		{P1 = 64;}
		else if(c == 2)
		//{P1 = 36;}
		{P1 = 80;}
		else if(c == 3)
		//{P1 = 40;}
		{P1 = 96;}
	break;
	case 3:
		if(c == 1)
		//{P1 = 45;}
		{P1 = 112;}
		else if(c == 2)
		//{P1 = 48;}
		{P1 = 128;}
		else if(c == 3)
		//{P1 = 0;}
		{P1 = 144;}
	break;
}
}

void led_disp(int r, int c)
{
lcd_init();
lcd_cmd(0x80);													//Move cursor to first line
msdelay(4);
if(r == 0 && c == 0)
	{	lcd_write_string(silence);}
	switch(r){
	case 1:
		if(c == 1)
		//{P1 = 24;}
		{	lcd_write_string(sa);}
		else if(c == 2)
		//{P1 = 27;}
	{	lcd_write_string(re);}
		else if(c == 3)
		//{P1 = 30;}
	{	lcd_write_string(ga);}
  break;
  case 2:
		if(c == 1)
		//{P1 = 32;}
	{	lcd_write_string(ma);}
		else if(c == 2)
		//{P1 = 36;}
	{	lcd_write_string(pa);}
		else if(c == 3)
		//{P1 = 40;}
	{	lcd_write_string(dha);}
	break;
	case 3:
		if(c == 1)
		//{P1 = 45;}
	{	lcd_write_string(ni);}
		else if(c == 2)
		//{P1 = 48;}
	{	lcd_write_string(sa_high);}
		else if(c == 3)
		//{P1 = 0;}
	{	lcd_write_string(silence);}
	break;
}
}


void tone_delay(int r, int c)
{
	TMOD = 0X10;

	switch(r){
	case 1:
		if(c == 1)
    {TL1 = 0XBA;
		TH1 = 0XEF;}
		else if(c == 2)
    {TL1 = 0X89;
		TH1 = 0XF1;}
		else if(c == 3)
    {TL1 = 0XFB;
		TH1 = 0XF2;}
		break;
  case 2:
		if(c == 1)
    {TL1 = 0XCB;
		TH1 = 0XF3;}
		else if(c == 2)
    {TL1 = 0X27;
		TH1 = 0XF5;}
		else if(c == 3)
    {TL1 = 0X3C;
		TH1 = 0XF6;}
		break;
	case 3:
		if(c == 1)
    {TL1 = 0X52;
		TH1 = 0XF7;}
		else if(c == 2)
    {TL1 = 0XDD;
		TH1 = 0XF7;}
		break;
}
	TR1 = 1; //Start bit indicates the counting starts
	while(TF1 == 0); //Checks overflow that is FFFFH to 0000H
	TR1 = 0; //Stops the timer
	TF1 = 0;
}

