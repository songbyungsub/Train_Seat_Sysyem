#include <Adafruit_GFX.h> //GFX 라이브러리
#include <SoftwareSerial.h> //직렬통신 라이브러리
#include <HX711.h> // 로드셀 무게센서 라이브러리
#include "kproject_gfx.h" // TFT_LCD 라이브러리

#define calibration_factor -7050.06 //로드셀 무게센서 스케일 값 선언
#define DOUT2 9 //로드셀 엠프 데이터 아웃 핀 넘버 선언
#define CLK2 8 // 로드셀 엠프 클락 핀 넘버

#define ILI9341_WHITE 0xFFFF //TFT_LCD 하얀색 16진법 선언
#define ILI9341_RED 0xF800 //TFT_LCD 빨간색 16진법 선언
#define ILI9341_GREEN 0x07E0 //TFT_LCD 초록색 16진법 선언

int state = 1; //좌석표시와 혼잡도 표시의 구분을 위한 state변수선언
SoftwareSerial soft(2, 3); //TFT_LCD의 RX,TX 핀 넘버 선언
kproject_gfx display(soft, 320, 240); //TFT_LCD의 화면 크기 선언

// 압력센서의 아날로그 핀 넘버 선언
int FSR = A0; 
int FSR2 = A1;
int FSR3 = A2;
int FSR4 = A3;
int FSR5 = A4;
int FSR6 = A5;
int FSR7 = A6;
int FSR8 = A7;
int FSR9 = A8;
int FSR10 = A9;

// 압력센서를 루프에서 사용할 변수 선언
int value = 0;
int value2 = 0;
int value3 = 0;
int value4 = 0;
int value5 = 0;
int value6 = 0;
int value7 = 0;
int value8 = 0;
int value9 = 0;
int value10 = 0;

// 좌석표시 10초 , 혼잡도 표시 5초를 위한 변수 선언
int i = 0;
int j = 0;

HX711 scale2(DOUT2, CLK2); // 엠프 핀 선언

void setup() 
{
  soft.begin(57600); //TFT_LCD의 통신속도는 57600 baud rate
  Serial.begin(9600); // 시리얼 통신 개방
  display.setCursor(50, 90); //TFT_LCD의 시작 커서 x좌표 50, y좌표 90
  display.setHanFont(5); // TFT_LCD에 나오는 글씨 크기 5
  display.fillRect(0, 0, 320, 240, KPROJECT_BLACK); //TFT_LCD의 (0,0)에서 (320,240)까지 검은색으로 채우기
  scale2.set_scale(calibration_factor); // 무게센서 스케일 지정
  scale2.tare(); // 무게센서 스케일 설정
}


void loop()
{   
    
    if(state == 0) // 좌석표시 상태
    {
          while(1)
          {
                 // 압력센서 10개의 아날로그 신호를 0~250까지의 숫자로 변환하여 value1~10에 대입 
                 value = map(analogRead(FSR), 0, 250, 0, 250);
                 value2 = map(analogRead(FSR2), 0, 250, 0, 250);
                 value3 = map(analogRead(FSR3), 0, 250, 0, 250);
                 value4 = map(analogRead(FSR4), 0, 250, 0, 250);
                 value5 = map(analogRead(FSR5), 0, 250, 0, 250);
                 value6 = map(analogRead(FSR6), 0, 250, 0, 250);
                 value7 = map(analogRead(FSR7), 0, 250, 0, 250);
                 value8 = map(analogRead(FSR8), 0, 250, 0, 250);
                 value9 = map(analogRead(FSR9), 0, 250, 0, 250);
                 value10 = map(analogRead(FSR10), 0, 250, 0, 250);
                 
                 display.fillRect(0, 0, 320, 240, KPROJECT_BLACK);  //TFT_LCD의 (0,0)에서 (320,240)까지 검은색으로 채우기(안해주면 TFT_LCD에 누적되어서 나온다.)

                 // 좌석표시를 위한 선 긋기
                 // ex) drawLine(시작 x좌표, 시작 y좌표, 타켓 x좌표, 타켓 y좌표, 색)
                 display.drawLine(0, 0, 320, 0, display.color565(255, 255, 255)); 
                 display.drawLine(0, 100, 320, 100, display.color565(255, 255, 255));
                 display.drawLine(64, 0, 64, 99, display.color565(255,255,255));
                 display.drawLine(128, 0, 128, 99, display.color565(255,255,255));
                 display.drawLine(192, 0, 192, 99, display.color565(255,255,255));
                 display.drawLine(256, 0, 256, 99, display.color565(255,255,255));
                 
                // 좌석표시를 위한 선 긋기
                 display.drawLine(0, 239, 320, 239, display.color565(255, 255, 255));
                 display.drawLine(0, 140, 320, 140, display.color565(255, 255, 255));
                 display.drawLine(64, 140, 64, 239, display.color565(255,255,255));
                 display.drawLine(128, 140, 128, 239, display.color565(255,255,255));
                 display.drawLine(192, 140, 192, 239, display.color565(255,255,255));
                 display.drawLine(256, 140, 256, 239, display.color565(255,255,255));

                 // 압력센서10개의 아날로그 신호를 변환한 값이 5 이상일 경우 해당 칸을 회색으로 채우기
                 if(value > 5)  display.fillRect(257, 141, 63, 98, display.color565(123,125,123));
                 // 아닐경우 해당 칸을 검은색으로 채우기 
                 else display.fillRect(257, 141, 63, 98, KPROJECT_BLACK);
                 
                 if(value2 > 5) display.fillRect(193, 141, 63, 98, display.color565(123,125,123));
                 else display.fillRect(193, 141, 63, 98, KPROJECT_BLACK);
                 
                 if(value3 > 5) display.fillRect(129, 141, 63, 98, display.color565(123,125,123));
                 else display.fillRect(129, 141, 63, 98, KPROJECT_BLACK);
                 
                 if(value4 > 5) display.fillRect(65, 141, 63, 98, display.color565(123,125,123));
                 else display.fillRect(65, 141, 63, 98, KPROJECT_BLACK);
                 
                 if(value5 > 5) display.fillRect(0, 141, 64, 98, display.color565(123,125,123));
                 else display.fillRect(0, 141, 64, 98, KPROJECT_BLACK);
                 
                 if(value6 > 5) display.fillRect(0, 1, 64, 99, display.color565(123,125,123));
                 else display.fillRect(0, 1, 64, 99, KPROJECT_BLACK);
                 
                 if(value7 > 5) display.fillRect(65, 1, 63, 99, display.color565(123,125,123));
                 else display.fillRect(65, 1, 63, 98, KPROJECT_BLACK);
                 
                 if(value8 > 5) display.fillRect(129, 1, 63, 99, display.color565(123,125,123));
                 else display.fillRect(129, 1, 63, 99, KPROJECT_BLACK);
                 
                 if(value9 > 5) display.fillRect(193, 1, 63, 99, display.color565(123,125,123));
                 else display.fillRect(193, 1, 63, 99, KPROJECT_BLACK);
                 
                 if(value10 > 5) display.fillRect(257, 1, 64, 99, display.color565(123,125,123));
                 else display.fillRect(257, 1, 64, 99, KPROJECT_BLACK);

                 
                 // 10초 작동을 위한 if문 
                 if(i == 10) // 10초가 지날시
                 {
                       state = 1; // 혼잡도 표시로 
                       i = 0; //좌석표시 시간 카운트는 다시 0초로
                       break;
                 }
                 delay(1000); // 1초
                 i++; // 1초 지날시 i를 1 증가
                 
                 }

             }
              
             if(state == 1) // 혼잡도 표시 상태
             {    
                  while(1)
                  {      
                        display.fillRect(0, 0, 320, 240, KPROJECT_BLACK); 
                        display.drawRoundRect(0, 0, 320, 240, 30, display.color565(255, 255, 255)); // 화면 겉 테두리에 흰색 둥근 사각형 라인 긋기
                        display.setTextSize(5); // 글씨크기는 5로 설정
                        if(-(scale2.get_units()) < 5) // 무게센서의 값이 5lbs보다 작을시 하얀색 "원 활" TFT_LCD에 표시 
                        {
                            display.setTextColor(ILI9341_WHITE);
                            display.print_string("원 활");
                        }
                        else if((-(scale2.get_units())) < 10) // 무게센서의 값이 5~15lbs일시 초록색 "보 통" TFT_LCD에 표시 
                        {
                            display.setTextColor(ILI9341_GREEN);
                            display.print_string("보 통");
                        }
                        else
                        {
                            display.setTextColor(ILI9341_RED); // 무게센서의 값이 15lbs보다 클시  빨간색 "혼 잡" TFT_LCD에 표시 
                            display.print_string("혼 잡");
                        }
                        
                        if(j == 5) // 5초가 지날시
                        {
                            state = 0; // 좌석표시 상태로
                            j = 0; // 혼잡도 표시 시간 카운트는 다시 0초로
                            break;
                        }
                        delay(1000); //1초
                        j++; // 1초 지날시 i를 1 증가
                  } 
             }
             delay(1000);
}
