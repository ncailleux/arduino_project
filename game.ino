#include "LedControlMS.h"

#define VIN 5 // V power voltage
#define R 10000 //ohm resistance value

#define NBR_MTX 2
LedControl lc = LedControl(12, 11, 10, NBR_MTX);

int digitCounter = 0;

int val = 0;
int VRx = A0;
int VRy = A1;
int SW = A2;

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

const int buttonPin1 = 2;
const int buttonPin2 = 4;
const int buttonPin3 = 9;
const int buttonPin4 = 8;
int button1 = 0;
int button2 = 0;
int button3 = 0;
int button4 = 0;

const int sensorPin = A5;
int sensorVal;
float res;

void setup() {
    Serial.begin(9600);
    Serial.println("Setup");
    digitCounter = 0;
    for (int i = 0; i < NBR_MTX; i++)
    {
        lc.shutdown(i, false);
        lc.setIntensity(i, 1);
        lc.clearDisplay(i);
    }
    pinMode(VRx, INPUT);
    pinMode(VRy, INPUT);
    pinMode(SW, INPUT_PULLUP);
    // pinMode(ledPin, OUTPUT);
    pinMode(buttonPin1, INPUT);
    pinMode(buttonPin2, INPUT);
    pinMode(buttonPin3, INPUT);
    pinMode(buttonPin4, INPUT);
}

int string_in(const char *string, const char **strings, size_t strings_num) {
    for (size_t i = 0; i < strings_num; i++) {
        if (!strcmp(string, strings[i])) {
            return 1;
        }
    }
    return -1;
}

float sensorRawToPhys(int raw){
  // Conversion rule
  float Vout = float(raw) * (VIN / float(1023));// Conversion analog to voltage
  float phys = R *((Vout))/VIN; // Conversion voltage to resistance between GND and signal
  float phys2 = R *((VIN - Vout))/VIN; // Conversion voltage to resistance between 5V and signal
  return phys;
}

int type = 0;
int new_type = 0;
int posXG = 0;
int posYG = 0;

/*
    0: rien
    1: poulpe
    2: lapin
    3: PD
    4: joystick
*/

void loop() {

    button1 = digitalRead(buttonPin1);
    button2 = digitalRead(buttonPin2);
    button3 = digitalRead(buttonPin3);
    button4 = digitalRead(buttonPin4);
    if (button1 == HIGH) {
        Serial.println("LES BTN 1");
        new_type = new_type + 1;
        if (new_type > 5) {
            new_type = 0;
        }
    }
    else {
        //Serial.println("LES BTN 1");
    }
    if (button2 == HIGH) {
        Serial.println("LES BTN 2");
    }
    else {
        //Serial.println("LES BTN 2");
    }
    if (button3 == HIGH) {
        Serial.println("LES BTN 3");
    }
    else {
        //Serial.println("LES BTN 3");
    }
    if (button4 == HIGH) {
        Serial.println("LES BTN 4");
    }
    else {
        //Serial.println("LES BTN 4");
    }

    if (type != new_type) {
        digitCounter = 0;
        for (int i = 0; i < NBR_MTX; i++) {
            lc.shutdown(i, false);
            lc.setIntensity(i, 1);
            lc.clearDisplay(i);
        }
        type = new_type;
        delay(5);
        int a[64] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        if (type == 1) {
            Serial.println("change to poulpe");
            int poulpe[18] = {0, 1, 6, 7, 8, 15, 26, 29, 32, 39, 40, 41, 46, 47, 48, 55, 58, 61};
            for (int z = 0; z < 18; z++) {
                a[poulpe[z]] = 0;
            }
        }
        else if (type == 2) {
            Serial.println("change to alien");
            int jean[34] = {0, 2, 3, 4, 5, 7, 8, 11, 12, 15, 16, 17, 19, 20, 22, 23, 24, 25, 26, 29, 30, 31, 32, 33, 38, 39, 40, 42, 45, 47, 56, 59, 60, 63};
            for (int z = 0; z < 34; z++) {
                a[jean[z]] = 0;
            }
        }
        else if (type == 3) {
            Serial.println("change to PD");
            int jean[30] = {0, 1, 2, 4, 5, 8, 10, 12, 14, 16, 18, 20, 23, 24, 25, 26, 28, 31, 32, 36, 39, 40, 44, 47, 48, 52, 54, 56, 60, 61};
            for (int z = 0; z < 64; z++) {
                a[z] = 0;
            }
            for (int z = 0; z < 30; z++) {
                a[jean[z]] = 1;
            }
        }
        else if (type == 4) {
            posXG = 0;
            posYG = 0;
            Serial.println("change to game");
            for (int z = 0; z < 64; z++) {
                a[z] = 0;
            }
            a[0] = 1;
            lc.setLed(0, 0, 0, true);
        }
        else {
            Serial.println("change to othersss");
            for (int z = 0; z < 64; z++) {
                a[z] = 0;
            }
        }
        delay(10);
        int c = -1;
        int val = 0;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                val = 8 * j + i;
                if (a[val] == 1) {
                    lc.setLed(0, j, i, true);
                }
                else {
                    lc.setLed(0, j, i, false);
                }
            }
        }
        Serial.println("------");
    }
    if (type == 4) {
        xPosition = analogRead(VRx);
        yPosition = analogRead(VRy);
        SW_state = digitalRead(SW);
        mapX = map(xPosition, 0, 1023, -512, 512);
        mapY = map(yPosition, 0, 1023, -512, 512);
        int newPosXG = posXG;
        int newPosYG = posYG;
        if (mapY > 250) {
            if (posXG == 7) {
                newPosXG = 0;
            }
            else {
                newPosXG = newPosXG + 1;
            }
        }
        else if (mapY < -250) {
            if (posXG == 0) {
                newPosXG = 7;
            }
            else {
                newPosXG = newPosXG - 1;
            }
        }
        if (mapX > 250) {
            if (posYG == 7) {
                newPosYG = 0;
            }
            else {
                newPosYG = newPosYG + 1;
            }
        }
        else if (mapX < -250) {
            if (posYG == 0) {
                newPosYG = 7;
            }
            else {
                newPosYG = newPosYG - 1;
            }
        }
        lc.setLed(0, posXG, posYG, false);
        lc.setLed(0, newPosXG, newPosYG, true);
        posXG = newPosXG;
        posYG = newPosYG;
        /*
        Serial.print("X: ");
        Serial.print(mapX);
        Serial.print(" | Y: ");
        Serial.print(mapY);
        Serial.print(" | Button: ");
        Serial.println(SW_state);
        */
    }
    if (type == 5) {
        sensorVal = analogRead(sensorPin);
        res = sensorRawToPhys(sensorVal);
        int maxVal = getConditionValue(res);
        int val = 0;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                val = 8 * j + i;
                if (val < maxVal) {
                    lc.setLed(0, j, i, true);
                }
                else {
                    lc.setLed(0, j, i, false);
                }
            }
        }
        /*
        Serial.print(F("Raw value from sensor= "));
        Serial.println(sensorVal); // the analog reading
        Serial.print(F("Physical value from sensor = "));
        Serial.print(res); // the analog reading
        Serial.println(F(" ohm")); // the analog reading
        */
        delay(100);
    }
    else if (type == 3) {
        delay(100);
    }
    else {
        delay(200);
    }
}

int getConditionValue(float res) {
    int maxVal = 0;
    if (res < 50) {
        maxVal = 0;
    }
    else if (res < 157) {
        maxVal = 1;
    }
    else if (res < 314) {
        maxVal = 2;
    }
    else if (res < 471) {
        maxVal = 3;
    }
    else if (res < 628) {
        maxVal = 4;
    }
    else if (res < 785) {
        maxVal = 5;
    }
    else if (res < 942) {
        maxVal = 6;
    }
    else if (res < 1099) {
        maxVal = 7;
    }
    else if (res < 1256) {
        maxVal = 8;
    }
    else if (res < 1413) {
        maxVal = 9;
    }
    else if (res < 1570) {
        maxVal = 10;
    }
    else if (res < 1727) {
        maxVal = 11;
    }
    else if (res < 1884) {
        maxVal = 12;
    }
    else if (res < 2041) {
        maxVal = 13;
    }
    else if (res < 2198) {
        maxVal = 14;
    }
    else if (res < 2355) {
        maxVal = 15;
    }
    else if (res < 2512) {
        maxVal = 16;
    }
    else if (res < 2669) {
        maxVal = 17;
    }
    else if (res < 2826) {
        maxVal = 18;
    }
    else if (res < 2983) {
        maxVal = 19;
    }
    else if (res < 3140) {
        maxVal = 20;
    }
    else if (res < 3297) {
        maxVal = 21;
    }
    else if (res < 3454) {
        maxVal = 22;
    }
    else if (res < 3611) {
        maxVal = 23;
    }
    else if (res < 3768) {
        maxVal = 24;
    }
    else if (res < 3925) {
        maxVal = 25;
    }
    else if (res < 4082) {
        maxVal = 26;
    }
    else if (res < 4239) {
        maxVal = 27;
    }
    else if (res < 4396) {
        maxVal = 28;
    }
    else if (res < 4553) {
        maxVal = 29;
    }
    else if (res < 4710) {
        maxVal = 30;
    }
    else if (res < 4867) {
        maxVal = 31;
    }
    else if (res < 5024) {
        maxVal = 32;
    }
    else if (res < 5181) {
        maxVal = 33;
    }
    else if (res < 5338) {
        maxVal = 34;
    }
    else if (res < 5495) {
        maxVal = 35;
    }
    else if (res < 5652) {
        maxVal = 36;
    }
    else if (res < 5809) {
        maxVal = 37;
    }
    else if (res < 5966) {
        maxVal = 38;
    }
    else if (res < 6123) {
        maxVal = 39;
    }
    else if (res < 6280) {
        maxVal = 40;
    }
    else if (res < 6437) {
        maxVal = 41;
    }
    else if (res < 6594) {
        maxVal = 42;
    }
    else if (res < 6751) {
        maxVal = 43;
    }
    else if (res < 6908) {
        maxVal = 44;
    }
    else if (res < 7065) {
        maxVal = 45;
    }
    else if (res < 7222) {
        maxVal = 46;
    }
    else if (res < 7379) {
        maxVal = 47;
    }
    else if (res < 7536) {
        maxVal = 48;
    }
    else if (res < 7693) {
        maxVal = 49;
    }
    else if (res < 7850) {
        maxVal = 50;
    }
    else if (res < 8007) {
        maxVal = 51;
    }
    else if (res < 8164) {
        maxVal = 52;
    }
    else if (res < 8321) {
        maxVal = 53;
    }
    else if (res < 8478) {
        maxVal = 54;
    }
    else if (res < 8635) {
        maxVal = 55;
    }
    else if (res < 8792) {
        maxVal = 56;
    }
    else if (res < 8949) {
        maxVal = 57;
    }
    else if (res < 9106) {
        maxVal = 58;
    }
    else if (res < 9263) {
        maxVal = 59;
    }
    else if (res < 9420) {
        maxVal = 60;
    }
    else if (res < 9577) {
        maxVal = 61;
    }
    else if (res < 9734) {
        maxVal = 62;
    }
    else if (res < 9891) {
        maxVal = 63;
    }
    else {
        maxVal = 64;
    }
    return maxVal;
}