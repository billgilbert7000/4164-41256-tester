#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "config.hpp"

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); 

int mode;
int lastState = HIGH;
int currentState;
unsigned long pressedTime = 0;
byte selector = 0;
byte l_sel = 0;
bool isError = false;
byte ntest =0;

String  m_sym[2] = {"\\","/"};

volatile int bus_size;
const unsigned int a_bus[BUS_SIZE] = {
		 XA0, XA1, XA2, XA3, XA4, XA5, XA6, XA7, XA8
};

/* -----  SETUP  ------ */
void setup() {
		 int i;
		 u8g2.begin();
		 Serial.begin(9600); 

		 for (i = 0; i < BUS_SIZE; i++)
					pinMode(a_bus[i], OUTPUT);

		 pinMode(CAS, OUTPUT);
		 pinMode(RAS, OUTPUT);
		 pinMode(WE, OUTPUT);
		 pinMode(DI, OUTPUT);
		 //pinMode(M_CHIPSEL, INPUT);
		 pinMode(M_START, INPUT);
		 pinMode(DO, INPUT);
		 digitalWrite(WE, HIGH);
		 digitalWrite(RAS, HIGH);
		 digitalWrite(CAS, HIGH);


/*
	if (digitalRead(M_TYPE)) {
	/* jumper not set - 41256 */
		 /*bus_size = BUS_SIZE;
		 //Serial.print("256Kx1 ");
		 } else {
		 /* jumper set - 4164 */
		 /*bus_size = BUS_SIZE - 1;
		 //Serial.print("64Kx1 ");
		 }*/
		 selector=selchip();
		 l_sel=selector;
		 setDisp();\
}
/* -----------  LOOP  ---------- */
void loop(void) {

		 selector=selchip(); // 0= vuoto 1=4164 2=4116

		 if (l_sel!=selector) {
					l_sel=selector;
					setDisp();
		 }
      
		 //change mode - start
		 currentState = digitalRead(M_START);
		 if (lastState == HIGH && currentState == LOW) { // button is pressed
					pressedTime = millis();
					lastState = LOW;
		 }
		 if(lastState == LOW && currentState == HIGH) { // button is released
					lastState = HIGH;
					long pressDuration = millis() - pressedTime;
					if (pressDuration < 1500 ) { //short press chenge mode
							 if (selector==1 ){
										mode++;
										if (mode > 3) mode=0;
										setDisp();
							 }
					}
		 }
		 if(lastState == LOW && currentState == LOW &&  millis() - pressedTime > 1500) {
					//else { //long press start
					isError=false;
					ntest=0;
					if (selector>0) startTest();
		 }
   
		 delay(100);
}

   
void startTest() {
		 initDram();
		 u8g2.clearBuffer();
		 u8g2.setFont(u8g2_font_logisoso16_tr);
		 u8g2.drawStr(8,16,"Test no.1");
		 u8g2.setFont(u8g2_font_gb16st_t_2);
		 switch (selector) {
		 case 2:
					u8g2.drawStr(4,32,">16k");
					bus_size = BUS_SIZE - 2;
					break;
		 case 1:
					if (mode == 0){
							 u8g2.drawStr(4,32,">256k");
							 bus_size = BUS_SIZE;
					} else {
							 bus_size = BUS_SIZE - 1;
					}
					if (mode == 1) u8g2.drawStr(4,32,">64k");
					if (mode == 2) u8g2.drawStr(4,32,">32k Low");
					if (mode == 3) u8g2.drawStr(4,32,">32k High");
		 }

		 u8g2.sendBuffer();
		 interrupts(); noInterrupts(); 
  
		 fillx(0);
		 if (!isError){
					resDisp("Test no.2");
					interrupts();u8g2.sendBuffer(); noInterrupts(); 
					fillx(1);
		 }
		 if (!isError){
					interrupts(); 
					resDisp("Full Write...");
					u8g2.sendBuffer();
					noInterrupts(); 
					fill(1,false);
		 }
		 if (!isError){
					interrupts(); 
					resDisp("Full Read...");
					u8g2.sendBuffer();
					noInterrupts(); 
					readonly(1);
		 }
		 if (!isError){
					resDisp("Finishing...");
					interrupts();u8g2.sendBuffer(); noInterrupts(); 
					fill(0,true);
		 }

		 interrupts();
  
		 if (!isError){
					finish();
					/*
						u8g2.clearBuffer();
						u8g2.setFont(u8g2_font_logisoso16_tr);
						u8g2.drawStr(6,16,"TEST PASSED");
						u8g2.setFont(u8g2_font_gb16st_t_2);
						u8g2.drawStr(12,30,"press start");
						u8g2.sendBuffer();*/
					while (digitalRead(M_START)==LOW) {
					}
          while (digitalRead(M_START)==HIGH) {
					}
					setDisp();
					delay(300);
		 } else {
					setDisp();
		 }
}
