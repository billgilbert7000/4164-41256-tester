void  initDram()
{
		 int i;
		 _delay_us(250);         // Initial DRAM startup delay 250us
		 for(i = 0 ; i < 8 ; i++)  {
					digitalWrite(a_bus[i],LOW);
		 }
  
		 for(i = 0 ; i < 8 ; i++)  {
					digitalWrite(RAS, LOW);
					digitalWrite(RAS, HIGH);
		 }
  
}

void setBus(unsigned int a) {
		 int i;
		 for (i = 0; i < bus_size; i++) { //cambiato con bus_size piccolo
					if (bitRead(a, i)==1) {
							 digitalWrite(a_bus[i], HIGH);
					} else {
							 digitalWrite(a_bus[i], LOW);
					}
		 } 
}

void writeAddress(unsigned int r, unsigned int c, int v) {
		 /* row */
		 setBus(r);
		 digitalWrite(RAS, LOW);
		 /* rw */
		 digitalWrite(WE, LOW);
		 /* val */
		 digitalWrite(DI, (v & 1)? HIGH : LOW);
		 /* col */
		 setBus(c);
		 if (mode==2) digitalWrite(a_bus[7], LOW);
		 if (mode==3) digitalWrite(a_bus[7], HIGH);
		 digitalWrite(CAS, LOW);
		 digitalWrite(WE, HIGH);
		 digitalWrite(CAS, HIGH);
		 digitalWrite(RAS, HIGH);
}

int readAddress(unsigned int r, unsigned int c) {
		 int ret = 0;

		 /* row */
		 setBus(r);
		 digitalWrite(RAS, LOW);
		 /* col */
		 setBus(c);
		 if (mode==2) digitalWrite(a_bus[7], LOW);
		 if (mode==3) digitalWrite(a_bus[7], HIGH);
		 digitalWrite(CAS, LOW);
		 /* get current value */
		 ret = digitalRead(DO);

		 digitalWrite(CAS, HIGH);
		 digitalWrite(RAS, HIGH);
		 return ret;
}

void error(int r, int c)
{
		 unsigned long a = ((unsigned long)c << bus_size) + r;
		 String mhex = String(a,HEX);
		 interrupts();
		 u8g2.clearBuffer();
		 u8g2.setFont(u8g2_font_gb16st_t_2);
		 u8g2.drawStr(4, 12, NAME);
		 u8g2.setFont(u8g2_font_gb16st_t_2);
		 u8g2.drawStr(4,32,"Err. on ");
		 u8g2.drawStr(70,32,(char*)mhex.c_str() );
		 u8g2.sendBuffer();
		 isError=true;
		 while (digitalRead(M_START)==LOW) {
		 }
		 while (digitalRead(M_START)==HIGH) {
		 }
		 delay(300);
}


void animate(int v) {
		 /*interrupts();
			 if (v==1){u8g2.drawStr(110,32,"\\");} else {u8g2.drawStr(110,32,"/");}
			 u8g2.sendBuffer();
			 noInterrupts();*/
}

void fill(int v, bool rd) {
		 int r, c, g = 0;
		 int nocol = 0;
		 if (mode>1) nocol=1;
		 //v %= 1;
		 for (c = 0; c < (1<<bus_size-nocol); c++) {
					if (rd) animate(g? HIGH : LOW); //animazione
					for (r = 0; r < (1<<bus_size); r++) {
							 writeAddress(r, c, v);
							 if (rd){
										if (v != readAddress(r, c)){
												 error(r, c);
												 return;
										}
							 }
					}
					g ^= 1;
		 }
		 //blink();
}

void fillx(int v) {
		 int r, c, g = 0;
		 int nocol = 0;
		 if (mode>1) nocol=1;
		 v %= 1;
		 for (c = 0; c < (1<<bus_size-nocol); c++) {
					animate(g? HIGH : LOW); //animazione
					for (r = 0; r < (1<<bus_size); r++) {
							 writeAddress(r, c, v);
							 if (v != readAddress(r, c)){
										error(r, c);
										return;
							 }
							 v ^= 1;
					}
					g ^= 1;
		 }
}

void readonly(int v) {
		 int r, c;
		 int nocol = 0;
		 if (mode>1) nocol=1;
		 for (c = 0; c < (1<<bus_size-nocol); c++) {
					for (r = 0; r < (1<<bus_size); r++) {
							 if (v != readAddress(r, c)){
										error(r, c);
										return;
							 }
					}
		 }
}

byte selchip() {
		 return 1;
		 /*
     //selezione chip
		 int MREAD = analogRead(M_CHIPSEL); // 0 - 180 - 470 : 0=4164 510=vuoto 1024=4116
		 //Serial.println(MREAD);
		 if (MREAD<10) {//4164
		 return 0;
		 } else if (MREAD<200) {//4164-256-32
		 return 1;
		 } else {//4116
		 return 2;
		 }
		 */
}

// visualizzazione display
void setDisp() {
		 u8g2.clearBuffer(); // clear the internal memory
		 u8g2.setFont(u8g2_font_gb16st_t_2);
		 u8g2.drawStr(4, 12, NAME);
		 u8g2.setFont(u8g2_font_5x7_tf);
		 u8g2.drawStr(90,27, VERSION);
		 u8g2.setFont(u8g2_font_gb16st_t_2);
		 switch (selector) {
		 case 0:
					u8g2.drawStr(4,32,"  OFF   ");
					break;
		 case 2:
					u8g2.drawStr(4,32,"4116 16k");
					break;
		 case 1:
					if (mode == 0) u8g2.drawStr(4,32,"256Kx1");
					if (mode == 1) u8g2.drawStr(4,32,"64Kx1");
					if (mode == 2) u8g2.drawStr(4,32,"32Kx1 L");
					if (mode == 3) u8g2.drawStr(4,32,"32Kx1 H");
		 }
		 u8g2.sendBuffer();         // transfer internal memory to the display
}

//reset display
void resDisp (String ntest) {
		 u8g2.clearBuffer();
		 u8g2.setFont(u8g2_font_logisoso16_tr);
		 u8g2.setCursor(4,16);
		 u8g2.print(ntest);
		 u8g2.setFont(u8g2_font_gb16st_t_2);
		 switch (selector) {
		 case 0:
					u8g2.drawStr(4,32,"   ");
					break;
		 case 2:
					u8g2.drawStr(4,32,">16k");
					break;
		 case 1:
					if (mode == 0) u8g2.drawStr(4,32,">256k");
					if (mode == 1) u8g2.drawStr(4,32,">64K");
					if (mode == 2) u8g2.drawStr(4,32,">32K Low");
					if (mode == 3) u8g2.drawStr(4,32,">32K High");
		 }
}

void finish() {
   u8g2.clearBuffer();
   u8g2.setFont(u8g2_font_logisoso16_tr);
   u8g2.drawStr(6,16,"TEST PASSED");
   u8g2.setFont(u8g2_font_gb16st_t_2);
   u8g2.drawStr(12,30,"press start");
   u8g2.sendBuffer();
}
