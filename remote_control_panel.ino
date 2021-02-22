#include "LedControlMS.h"
#include <IRremote.h>
#define NBR_MTX 2
LedControl lc = LedControl(12, 11, 10, NBR_MTX);
String digits = "1234567890";
int digitCounter = 0;
unsigned long delaytime = 300;
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

int val = 0;
int VRx = A0;
int VRy = A1;
int SW = A2;

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

void setup()
{
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

    irrecv.enableIRIn();
    irrecv.blink13(true);
}

int string_in(const char *string, const char **strings, size_t strings_num)
{
    for (size_t i = 0; i < strings_num; i++)
    {
        if (!strcmp(string, strings[i]))
        {
            return 1;
        }
    }
    return -1;
}
/*
int GetNumber(char key) {
   int num = 0;
    switch (key){
       case NO_KEY:
          break;
       case '0': case '1': case '2': case '3': case '4':
       case '5': case '6': case '7': case '8': case '9':
          num = num * 10 + (key - '0');
          break;
       case '*':
          num = 0;
          break;
    }
   return num;
}
*/
/*
 * 0: rien
 * 1: poulpe
 * 2 : alien
 */

int type = 0;
int new_type = 0;
int posXG = 0;
int posYG = 0;
//char abs[] = ""

void loop()
{
    if (irrecv.decode(&results))
    {

        if (results.value == 0XFFFFFFFF)
            results.value = key_value;

        switch (results.value)
        {
        case 0xFFA25D:
            Serial.println("Power");
            break;
        case 0xFF629D:
            Serial.println("Vol+");
            break;
        case 0xFFE21D:
            Serial.println("Func");
            break;
        case 0xFF22DD:
            Serial.println("|<<");
            break;
        case 0xFF02FD:
            Serial.println(">||");
            break;
        case 0xFFC23D:
            Serial.println(">>|");
            break;
        case 0xFFE01F:
            Serial.println("-");
            break;
        case 0xFFA857:
            Serial.println("Vol-");
            break;
        case 0xFF906F:
            Serial.println("+");
            break;
        case 0xFF9867:
            Serial.println("EQ");
            break;
        case 0xFFB04F:
            Serial.println("Repeat");
            break;
        case 0xFF6897:
            Serial.println("0");
            new_type = 0;
            break;
        case 0xFF30CF:
            Serial.println("1");
            new_type = 1;
            break;
        case 0xFF18E7:
            Serial.println("2");
            new_type = 2;
            break;
        case 0xFF7A85:
            Serial.println("3");
            new_type = 3;
            break;
        case 0xFF10EF:
            Serial.println("4");
            new_type = 4;
            break;
        case 0xFF38C7:
            Serial.println("5");
            new_type = 5;
            break;
        case 0xFF5AA5:
            Serial.println("6");
            new_type = 6;
            break;
        case 0xFF42BD:
            Serial.println("7");
            new_type = 7;
            break;
        case 0xFF4AB5:
            Serial.println("8");
            new_type = 8;
            break;
        case 0xFF52AD:
            Serial.println("9");
            new_type = 9;
            break;
        }
        key_value = results.value;
        irrecv.resume();
    }
    if (type != new_type)
    {
        digitCounter = 0;
        for (int i = 0; i < NBR_MTX; i++)
        {
            lc.shutdown(i, false);
            lc.setIntensity(i, 1);
            lc.clearDisplay(i);
        }
        type = new_type;
        delay(5);
        int a[64] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        if (type == 1)
        {
            Serial.println("change to poulpe");
            int poulpe[18] = {0, 1, 6, 7, 8, 15, 26, 29, 32, 39, 40, 41, 46, 47, 48, 55, 58, 61};
            for (int z = 0; z < 18; z++)
            {
                a[poulpe[z]] = 0;
            }
        }
        else if (type == 2)
        {
            Serial.println("change to alien");
            int jean[34] = {0, 2, 3, 4, 5, 7, 8, 11, 12, 15, 16, 17, 19, 20, 22, 23, 24, 25, 26, 29, 30, 31, 32, 33, 38, 39, 40, 42, 45, 47, 56, 59, 60, 63};
            for (int z = 0; z < 34; z++)
            {
                a[jean[z]] = 0;
            }
        }
        else if (type == 3)
        {
            Serial.println("change to PD");
            int jean[30] = {0, 1, 2, 4, 5, 8, 10, 12, 14, 16, 18, 20, 23, 24, 25, 26, 28, 31, 32, 36, 39, 40, 44, 47, 48, 52, 54, 56, 60, 61};
            for (int z = 0; z < 64; z++)
            {
                a[z] = 0;
            }
            for (int z = 0; z < 30; z++)
            {
                a[jean[z]] = 1;
            }
        }
        else if (type == 4)
        {
            posXG = 0;
            posYG = 0;
            Serial.println("change to game");
            for (int z = 0; z < 64; z++)
            {
                a[z] = 0;
            }
            a[0] = 1;
            lc.setLed(0, 0, 0, true);
        }
        else
        {
            Serial.println("change to othersss");
            for (int z = 0; z < 64; z++)
            {
                a[z] = 0;
            }
        }
        delay(10);
        int c = -1;
        int val = 0;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                val = 8 * j + i;
                //Serial.println("a[val]");
                //Serial.println(val);
                //Serial.println(a[val]);
                if (a[val] == 1)
                {
                    lc.setLed(0, j, i, true);
                }
                else
                {
                    lc.setLed(0, j, i, false);
                }
                // delay(5);
            }
        }
        Serial.println("------");
    }
    if (type == 4)
    {
        xPosition = analogRead(VRx);
        yPosition = analogRead(VRy);
        SW_state = digitalRead(SW);
        mapX = map(xPosition, 0, 1023, -512, 512);
        mapY = map(yPosition, 0, 1023, -512, 512);
        int newPosXG = posXG;
        int newPosYG = posYG;
        if (mapX > 250)
        {
            if (posXG == 7)
            {
                newPosXG = 0;
            }
            else
            {
                newPosXG = newPosXG + 1;
            }
        }
        else if (mapX < -250)
        {
            if (posXG == 0)
            {
                newPosXG = 7;
            }
            else
            {
                newPosXG = newPosXG - 1;
            }
        }
        if (mapY > 250)
        {
            if (posYG == 7)
            {
                newPosYG = 0;
            }
            else
            {
                newPosYG = newPosYG + 1;
            }
        }
        else if (mapY < -250)
        {
            if (posYG == 0)
            {
                newPosYG = 7;
            }
            else
            {
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
    if (type == 3)
    {
        delay(100);
    }
    else if (type == 9)
    {
        delay(1000);
    }
    else
    {
        delay(200);
    }
}
