#include <LiquidCrystal.h>
#include <flameArray.h>
LiquidCrystal lcd(5,4,3,2,1,0);
flameArray api(8,A5,12,11,13,7);//bit mode(8/10), analog pin, clock pin, DT pin, MR pin, max array(why "7"? couse 0-7)

int adc;
int rate[8]={100,100,100,100,100,100,100,100};
void setup() {
  // put your setup code here, to run once:
lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:

adc=api.flameRead(0);//read value per bit array
lcd.setCursor(0,0);
lcd.print(adc);lcd.print("  ");

adc=api.flameReadBit(rate);//read all bit (if value > rate, bit = 1) output is 1 variable
lcd.setCursor(5,0);
lcd.print(adc);lcd.print("  ");
}
