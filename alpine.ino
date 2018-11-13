
#define CHECK_MS 1
#define DOUBLE_MS 40
#define HOLD_MS 600

#define alpPin 10  //digital Pin to Alpine
#define analogPin 5 //pin from wheel

#define resistor 1083
#define NO_B 1600 //nothing pressed
#define MODE_B 1466 // MODE
#define NXTU_B 172+resistor // NEXT UP
#define NXTD_B 72+resistor // NEXT DOWN
#define MUTE_B 392 //390 // MUTE
#define VOLU_B 172 // VOLUME UP
#define VOLD_B 72 // VOLUME DOWN
#define MAX_ERR 50 //MAX ERROR IN RESISTANCE MESEURE

boolean  volUp[32] = 	{0,1,1,0,0,0,0,1, 0,1,0,0,1,1,1,0, 0,0,1,0,1,0,0,0, 1,1,0,1,0,1,1,1 }; //volume up
boolean  volDn[32] = 	{0,1,1,0,0,0,0,1, 0,1,0,0,1,1,1,0, 1,0,1,0,1,0,0,0, 0,1,0,1,0,1,1,1 }; //volume down
boolean  mute[32] = 	{0,1,1,0,0,0,0,1, 0,1,0,0,1,1,1,0, 0,1,1,0,1,0,0,0, 1,0,0,1,0,1,1,1 };  // mute
boolean  pstUp[32] =	{0,1,1,0,0,0,0,1, 0,1,0,0,1,1,1,0, 0,1,1,1,0,0,0,0, 1,0,0,0,1,1,1,1 }; // folder up
boolean  pstDn[32] = 	{0,1,1,0,0,0,0,1, 0,1,0,0,1,1,1,0, 1,1,1,1,0,0,0,0, 0,0,0,0,1,1,1,1 }; // folder down
boolean  source[32] = 	{0,1,1,0,0,0,0,1, 0,1,0,0,1,1,1,0, 0,1,0,1,0,0,0,0, 1,0,1,0,1,1,1,1 }; // source
boolean  trkUp[32] = 	{0,1,1,0,0,0,0,1, 0,1,0,0,1,1,1,0, 0,1,0,0,1,0,0,0, 1,0,1,1,0,1,1,1 }; // track up	
boolean  trkDn[32] = 	{0,1,1,0,0,0,0,1, 0,1,0,0,1,1,1,0, 1,1,0,0,1,0,0,0, 0,0,1,1,0,1,1,1 }; // track down
boolean  power[32] = 	{0,1,1,0,0,0,0,1, 0,1,0,0,1,1,1,0, 1,0,0,1,0,0,0,0, 0,1,1,0,1,1,1,1 };	//power
boolean  entPlay[32] = 	{0,1,1,0,0,0,0,1, 0,1,0,0,1,1,1,0, 0,0,0,1,1,1,1,1, 1,1,1,0,0,0,0,0 }; //play/pause
boolean  bandProg[32] = {0,1,1,0,0,0,0,1, 0,1,0,0,1,1,1,0, 0,1,1,0,0,0,0,1, 1,0,0,1,1,1,1,0 }; //band 
boolean  defeat[32] = 	{0,1,1,0,0,0,0,1, 0,1,0,0,1,1,1,0, 1,0,1,0,0,0,0,0, 0,1,0,1,1,1,1,1 }; //??
boolean  eject[32] = 	{0,1,1,0,0,0,0,1, 0,1,0,0,1,1,1,0, 1,1,0,1,0,0,0,0, 0,0,1,0,1,1,1,1 }; //??

boolean spFlag = 0;
boolean dpFlag = 0;
boolean hpFlag = 0;

int button = 0;
int spbutton = 0;


int raw = 0;           // variable to store the raw input value
int Vin = 5;           // variable to store the input voltage
float Vout = 0;        // variable to store the output voltage
float R1 = 10;         // variable to store the R1 value
float R2 = 0;          // variable to store the R2 value
float buffer = 0;      // buffer variable for calculation

void setup() {
    //Serial.begin(9600);
    pinMode(alpPin, OUTPUT);
    //Serial.println("Alfa 156 steering wheel control to Alpine");
}

void loop() {
    static unsigned long oldTime = 0;
    int switchStatus = 0;
    if (millis() >= oldTime + CHECK_MS) {
        oldTime = millis();
        switchStatus = CheckSwitch();
        
        if (switchStatus == 0) {
            //no button press

        } else if (switchStatus == 1) {
            // single press
            switch (spbutton) {
                case 0: // no butto, why are wh here
                    break;
                case 1: // mode 
                    sourceSend();
                    break;
                case 2: // next up
                    trkUpSend();
                    break;
                case 3: // next down
                    trkDnSend();
                    break;
                case 4: // mute
                    muteSend();
                    break;
                case 5: // vol up
                    volUpSend();
                    break;
                case 6: // vol down
                    volDnSend();
                    break;
            }
        } else if (switchStatus == 2) {
            //double press
            switch (spbutton) {
                case 0: // no butto, why are wh here
                    break;
                case 1: // mode
                    sourceSend();
                    break;
                case 2: // next up
                    pstUpSend();
                    break;
                case 3: // next down
                    pstDnSend();
                    break;
                case 4: // mute
                    bandProgSend();
                    break;
                case 5: // vol up
                    volUpSend();
                    break;
                case 6: // vol down
                    volDnSend();
                    break;
            }
        } else if (switchStatus == 3) {
            //hold
            switch (spbutton) {
                case 0: // no butto, why are wh here
                    break;
                case 1: // mode
                    powerSend();
                    break;
                case 2: // next up
                    trkUpSend();
                    break;
                case 3: // next down
                    trkDnSend();
                    break;
                case 4: // mute
                    ejectSend();
                    break;
                case 5: // vol up
                    pstUpSend();
                    break;
                case 6: // vol down
                    pstDnSend();
                    break;
            }
        }
    }
}

// Service routine called by a timer interrupt
int CheckSwitch() {
    static uint16_t State = 0; // Current debounce status
    static int curTime = 0;

    State = (State << 1) | !RawKeyPressed() | 0xe000;
    if (!spFlag) {
        if (hpFlag) {
            if (State == 0xe000) {
                return 3;
            } else {
                hpFlag = 0;
            }
        }
        if (State == 0xf000) {
            spFlag = 1;
            hpFlag = 1;
            dpFlag = 1;
            curTime = 0;
            spbutton = button;
            return 0;
        }
    }
    if (hpFlag && State != 0xe000) {
        hpFlag = 0;
    }
    if (spFlag && hpFlag && curTime > HOLD_MS / CHECK_MS) {
        spFlag = 0;
        dpFlag = 0;
        return 3;
    } else if (spFlag && dpFlag && State == 0xf000 && curTime < DOUBLE_MS) {
        spFlag = 0;
        hpFlag = 0;
        dpFlag = 0;
        return 2;
    } else if (spFlag && !hpFlag && curTime > DOUBLE_MS) {
        spFlag = 0;
        hpFlag = 0;
        dpFlag = 0;
        return 1;
    } else {
        curTime = curTime + CHECK_MS;
        return 0;
    }
}

boolean RawKeyPressed() {
    int anaPin = 0;
    anaPin = analogRead(analogPin);
    Vout = (5.0 / 1023.0) * anaPin;    // Calculates the Voltage on th Input PIN
    buffer = (Vin / Vout) - 1;
   R2 = R1 / buffer*1000;
  //Serial.print("Voltage: ");      //
  //Serial.println(Vout);           // Outputs the information
   //Serial.print("R2: ");           //
   //Serial.println(R2);             //
  
    if (R2 > NO_B - 20) {
        button = 0;
        return 0;
    } else if (R2 > MODE_B - MAX_ERR && R2 < MODE_B + MAX_ERR) {
        button = 1;
        return 1;
    } else if (R2 > NXTU_B - MAX_ERR && R2 < NXTU_B + MAX_ERR) {
        button = 2;
        return 1;
    } else if (R2 > NXTD_B - MAX_ERR && R2 < NXTD_B + MAX_ERR) {
        button = 3;
        return 1;
    } else if (R2 > MUTE_B - MAX_ERR && R2 < MUTE_B + MAX_ERR) {
        button = 4;
        return 1;
    } else if (R2 > VOLU_B - MAX_ERR && R2 < VOLU_B + MAX_ERR) {
        button = 5;
        return 1;
    } else if (R2 > VOLD_B - MAX_ERR && R2 < VOLD_B + MAX_ERR ) {
        button = 6;
        return 1;
    } else {
        button = 0;
        return 0;
    }
}



//-----------SOURCE------------------

void sourceSend() {
    //first send 9ms high
	digitalWrite(alpPin, HIGH);
	delay(9);

        //send 4.5ms high
	digitalWrite(alpPin, LOW);
	delayMicroseconds(4500);
        

	for (int i = 0; i <= 32; i++) {

		//send bit for 0.5ms
		digitalWrite(alpPin, HIGH);
		delayMicroseconds(560);

		if (source[i] == 1 ) {

			digitalWrite(alpPin, LOW);
			delayMicroseconds(1680);
		} else {
			digitalWrite(alpPin, LOW);
			delayMicroseconds(560);
		} 
	}
	// send 41ms low
	digitalWrite(alpPin, LOW);
	delay(41); 
}

//---------MODE-----------------------------------------------

void modeSend() {
	//first send 9ms high
	digitalWrite(alpPin, HIGH);
	delay(9);

        //send 4.5ms high
	digitalWrite(alpPin, LOW);
	delayMicroseconds(4500);
        

	for (int i = 0; i <= 32; i++) {

		//send bit for 0.5ms
		digitalWrite(alpPin, HIGH);
		delayMicroseconds(560);

		if (entPlay[i] == 1 ) {

			digitalWrite(alpPin, LOW);
			delayMicroseconds(1680);
		} else {
			digitalWrite(alpPin, LOW);
			delayMicroseconds(560);
		} 
	}
	// send 41ms low
	digitalWrite(alpPin, LOW);
	delay(41); 
}



//---------NEXT UP-----------------------------------------------

void trkUpSend() {
 //first send 9ms high
	digitalWrite(alpPin, HIGH);
	delay(9);

        //send 4.5ms high
	digitalWrite(alpPin, LOW);
	delayMicroseconds(4500);
        

    for (int i = 0; i <= 32; i++) {

		//send bit for 0.5ms
		digitalWrite(alpPin, HIGH);
		delayMicroseconds(560);

		if (trkUp[i] == 1 ) {
			digitalWrite(alpPin, LOW);
			delayMicroseconds(1680);
		} else {
			digitalWrite(alpPin, LOW);
			delayMicroseconds(560);
		} 
	}
	// send 41ms low
	digitalWrite(alpPin, LOW);
	delay(41); 

}


//---------NEXT DOWN----------------------------------------------

void trkDnSend() {
//first send 9ms high
	digitalWrite(alpPin, HIGH);
	delay(9);

        //send 4.5ms high
	digitalWrite(alpPin, LOW);
	delayMicroseconds(4500);
        
	for (int i = 0; i <= 32; i++) {

		digitalWrite(alpPin, HIGH);
		delayMicroseconds(560);

		if (trkDn[i] == 1 ) {
			digitalWrite(alpPin, LOW);
			delayMicroseconds(1680);
		} else {
			digitalWrite(alpPin, LOW);
			delayMicroseconds(560);
		} 
	}
	// send 41ms low
	digitalWrite(alpPin, LOW);
	delay(41); 

}


//---------MUTE---------------------------------------------------

void muteSend() {

	//first send 9ms high
	digitalWrite(alpPin, HIGH);
	delay(9);

        //send 4.5ms high
	digitalWrite(alpPin, LOW);
	delayMicroseconds(4500);
        

	for (int i = 0; i <= 32; i++) {

		//send bit for 0.5ms
		digitalWrite(alpPin, HIGH);
		delayMicroseconds(560);

		if (mute[i] == 1 ) {

			digitalWrite(alpPin, LOW);
			delayMicroseconds(1680);
		} else {
			digitalWrite(alpPin, LOW);
			delayMicroseconds(560);
		} 
	}
	// send 41ms low
	digitalWrite(alpPin, LOW);
	delay(41); 
}



//---------VOL UP-----------------------------------------------

void volUpSend() {

	//first send 9ms high
	digitalWrite(alpPin, HIGH);
	delay(9);

        //send 4.5ms high
	digitalWrite(alpPin, LOW);
	delayMicroseconds(4500);

	for (int i = 0; i <= 32; i++) {

		//send bit for 0.5ms
		digitalWrite(alpPin, HIGH);
		delayMicroseconds(560);

		if (volUp[i] == 1 ) {

			digitalWrite(alpPin, LOW);
			delayMicroseconds(1680);
		} else {
			digitalWrite(alpPin, LOW);
			delayMicroseconds(560);
		} 
	}
           
	// send 41ms low
	digitalWrite(alpPin, LOW);
	delay(41);
        Serial.println("Volup sent");
}


//---------VOL DOWN-----------------------------------------------

void volDnSend() {

	//first send 9ms high
	digitalWrite(alpPin, HIGH);
	delay(9);

        //send 4.5ms high
	digitalWrite(alpPin, LOW);
	delayMicroseconds(4500);

	for (int i = 0; i <= 32; i++) {
  
                //send bit for 0.5ms
		digitalWrite(alpPin, HIGH);
		delayMicroseconds(560);

		if (volDn[i] == 1 ) {
                        digitalWrite(alpPin, LOW);
			delayMicroseconds(1680);
		} else {
			digitalWrite(alpPin, LOW);
			delayMicroseconds(560);
		} 
	}
	// send 41ms low
	digitalWrite(alpPin, LOW);
	delay(41); 
}



//---------EJECT-----------------------------------------------

void ejectSend() {

	//first send 9ms high
	digitalWrite(alpPin, HIGH);
	delay(9);

        //send 4.5ms high
	digitalWrite(alpPin, LOW);
	delayMicroseconds(4500);
        
	for (int i = 0; i <= 32; i++) {
  
                //send bit for 0.5ms
		digitalWrite(alpPin, HIGH);
		delayMicroseconds(560);

		if (eject[i] == 1 ) {
			digitalWrite(alpPin, LOW);
			delayMicroseconds(1680);
		} else {
			digitalWrite(alpPin, LOW);
			delayMicroseconds(560);
		} 
	}
	// send 41ms low
	digitalWrite(alpPin, LOW);
	delay(41); 

}

//---------POWER-----------------------------------------------

void powerSend() {

	//first send 9ms high
	digitalWrite(alpPin, HIGH);
	delay(9);

        //send 4.5ms high
	digitalWrite(alpPin, LOW);
	delayMicroseconds(4500);
        
	for (int i = 0; i <= 32; i++) {
  
                //send bit for 0.5ms
		digitalWrite(alpPin, HIGH);
		delayMicroseconds(560);

		if (power[i] == 1 ) {
			digitalWrite(alpPin, LOW);
			delayMicroseconds(1680);
		} else {
			digitalWrite(alpPin, LOW);
			delayMicroseconds(560);
		} 
	}
	// send 41ms low
	digitalWrite(alpPin, LOW);
	delay(41); 

}

//---------Position UP-----------------------------------------------

void pstUpSend() {

	//first send 9ms high
	digitalWrite(alpPin, HIGH);
	delay(9);

        //send 4.5ms high
	digitalWrite(alpPin, LOW);
	delayMicroseconds(4500);
        
	for (int i = 0; i <= 32; i++) {
  
                //send bit for 0.5ms
		digitalWrite(alpPin, HIGH);
		delayMicroseconds(560);

		if (pstUp[i] == 1 ) {
			digitalWrite(alpPin, LOW);
			delayMicroseconds(1680);
		} else {
			digitalWrite(alpPin, LOW);
			delayMicroseconds(560);
		} 
	}
	// send 41ms low
	digitalWrite(alpPin, LOW);
	delay(41); 

}

//---------Position DOWN-----------------------------------------------

void pstDnSend() {

	//first send 9ms high
	digitalWrite(alpPin, HIGH);
	delay(9);

        //send 4.5ms high
	digitalWrite(alpPin, LOW);
	delayMicroseconds(4500);
        
	for (int i = 0; i <= 32; i++) {
  
                //send bit for 0.5ms
		digitalWrite(alpPin, HIGH);
		delayMicroseconds(560);

		if (pstDn[i] == 1 ) {
			digitalWrite(alpPin, LOW);
			delayMicroseconds(1680);
		} else {
			digitalWrite(alpPin, LOW);
			delayMicroseconds(560);
		} 
	}
	// send 41ms low
	digitalWrite(alpPin, LOW);
	delay(41); 

}

//---------BAND CHANGE-----------------------------------------------

void bandProgSend() {

	//first send 9ms high
	digitalWrite(alpPin, HIGH);
	delay(9);

        //send 4.5ms high
	digitalWrite(alpPin, LOW);
	delayMicroseconds(4500);
        
	for (int i = 0; i <= 32; i++) {
  
                //send bit for 0.5ms
		digitalWrite(alpPin, HIGH);
		delayMicroseconds(560);

		if (bandProg[i] == 1 ) {
			digitalWrite(alpPin, LOW);
			delayMicroseconds(1680);
		} else {
			digitalWrite(alpPin, LOW);
			delayMicroseconds(560);
		} 
	}
	// send 41ms low
	digitalWrite(alpPin, LOW);
	delay(41); 

}
