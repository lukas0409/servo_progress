/* 서보모터 각도를 문 열리는 진행도로 하고
진행도를 프로그레스 바로 LCD에 표시 */

#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd (0x27,20,4); // 접근주소: 0x3F or 0x27

Servo myservo;

int pos;
int abpos;
int i;

// 바이트들
byte zero[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte one[] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000
};
byte two[] = {
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000
};
byte three[] = {
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100
};
byte four[] = {
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110
};
byte five[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

void setup() {
  lcd.init(); // LCD 초기화
  lcd.backlight(); // 백라이트 켜기

  // 출력할 바이트 세팅
  lcd.createChar(0, zero);
  lcd.createChar(1, one);
  lcd.createChar(2, two);
  lcd.createChar(3, three);
  lcd.createChar(4, four);
  lcd.createChar(5, five);
  
  // 서보모터 세팅
  myservo.attach(7);
}

void loop() {
  lcd.init(); // LCD 초기화

  lcd.setCursor(0,0);
  lcd.print ("Progress..."); // 프로그레스 글자 

  for (pos = 40; pos <= 140; pos += 5) { // 위에 변수를 선언한 pos는 0, 180도보다 작다면 , 1도씩 더하고
    myservo.write(pos); // 서보모터를 pos 각도로 움직여라
    abpos = pos - 40;
    lcd.setCursor(0,0);
    updateProgressBar(abpos, 100, 1); // 진행 바 작동
    delay(1);
  }
}

// 진행바 표시함수
void updateProgressBar(unsigned long count, unsigned long totalCount, int lineToPrintOn) {
    double factor = totalCount/80.0;          
    int percent = (count+1)/factor;
    int number = percent/5;
    int remainder = percent%5;
    if(number > 0)
    {
      for(int j = 0; j < number; j++)
      {
        lcd.setCursor(j,lineToPrintOn);
       lcd.write(5);
      }
    }
       lcd.setCursor(number,lineToPrintOn);
       lcd.write(remainder); 
     if(number < 16)	//If using a 20 character display, this should be 20!
    {
      for(int j = number+1; j <= 16; j++)  //If using a 20 character display, this should be 20!
      {
        lcd.setCursor(j,lineToPrintOn);
       lcd.write(0);
      }
    }  
 }