/*

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
		 / row /
		 setBus(r);
		 digitalWrite(RAS, LOW);
		 / rw /
		 digitalWrite(WE, LOW);
		 / val /
		 digitalWrite(DI, (v & 1)? HIGH : LOW);
		 / col /
		 setBus(c);
		 if (mode==2) digitalWrite(a_bus[7], LOW);
		 if (mode==3) digitalWrite(a_bus[7], HIGH);
		 digitalWrite(CAS, LOW);
		 digitalWrite(WE, HIGH);
		 digitalWrite(CAS, HIGH);
		 digitalWrite(RAS, HIGH);
}


void fill(int v, bool rd) {
		 int r, c, g = 0;
		 int nocol = 0;
		 if (mode>1) nocol=1;
		 for (c = 0; c < (1<<bus_size-nocol); c++) {
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

// visualizzazione display
void setDisp() {
		 u8g2.clearBuffer();
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
		 u8g2.sendBuffer();
}

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
*/
