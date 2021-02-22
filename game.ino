#include "LedControlMS.h"

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
        if (new_type > 4) {
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
    if (type == 3) {
        delay(100);
    }
    else {
        delay(200);
    }
}
