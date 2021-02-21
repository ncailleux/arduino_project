// #include "LedControlMS.h"
// #include <Keypad.h>
// #define NBR_MTX 2 
// LedControl lc=LedControl(12,11,10, NBR_MTX);
// String digits= "1234567890";
// int digitCounter=0;
// unsigned long delaytime=300;
// const byte ROWS = 4; 
// const byte COLS = 4;
// char hexaKeys[ROWS][COLS] = {
//   {'1','2','3','A'},
//   {'4','5','6','B'},
//   {'7','8','9','C'},
//   {'*','0','#','D'}
// };
// byte rowPins[ROWS] = {9, 8, 7, 6};
// byte colPins[COLS] = {5, 4, 3, 2};
// Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

// void setup() {
//   Serial.begin (9600);
//   Serial.println("Setup");
//   digitCounter=0;
//   for (int i=0; i< NBR_MTX; i++){
//     lc.shutdown(i,false);
//     lc.setIntensity(i,2);
//     lc.clearDisplay(i);
//   }
// }
// int string_in(const char* string, const char** strings, size_t strings_num) {
//     for (size_t i = 0; i < strings_num; i++) {
//         if (!strcmp(string, strings[i])) {
//             return 1;
//         }
//     }
//     return -1;
// }
// int GetNumber(char key) {
//    int num = 0;
//     switch (key){
//        case NO_KEY:
//           break;
//        case '0': case '1': case '2': case '3': case '4':
//        case '5': case '6': case '7': case '8': case '9':
//           num = num * 10 + (key - '0');
//           break;
//        case '*':
//           num = 0;
//           break;
//     }
//    return num;
// }/*
// int GetNumber(char val) {
//    int num = 0;
//    switch (val){
//        case '':
//           num = 0;
//           break;
//     }
//    return num;
// }*/
// /*
//  * 0: rien
//  * 1: poulpe
//  * 2 : alien
//  */
// int type = 0;
// int new_type = 0;

// void loop() { 
//   char customKey = customKeypad.getKey();
//   int v1 = GetNumber(customKey);
//   if (v1){
//     //Serial.println(v1);
//     new_type = v1;
//   }
//   if (type != new_type) {
//     digitCounter=0; 
//     for (int i=0; i< NBR_MTX; i++){ lc.shutdown(i,false); lc.setIntensity(i,8); lc.clearDisplay(i); }
//     //Serial.println("new_type");
//     Serial.println(type);
//     Serial.println(new_type);
//     type = new_type;
//     const char* a[] = {"0-0", "0-1", "0-2", "0-3", "0-4", "0-5", "0-6", "0-7", "1-0", "1-1", "1-2", "1-3", "1-4", "1-5", "1-6", "1-7", "2-0", "2-1", "2-2", "2-3", "2-4", "2-5", "2-6", "2-7", "3-0", "3-1", "3-2", "3-3", "3-4", "3-5", "3-6", "3-7", "4-0", "4-1", "4-2", "4-3", "4-4", "4-5", "4-6", "4-7", "5-0", "5-1", "5-2", "5-3", "5-4", "5-5", "5-6", "5-7", "6-0", "6-1", "6-2", "6-3", "6-4", "6-5", "6-6", "6-7", "7-0", "7-1", "7-2", "7-3", "7-4", "7-5", "7-6"};
//     int len_a = 63;
//     // const char* a[] = {"0-0", "0-1", "0-6", "0-7", "1-0", "1-7", "3-2", "3-5", "4-0", "4-7","5-0", "5-1", "5-6", "5-7", "6-0", "6-7", "7-2", "7-5"};
//     // int len_a = 18;
//     delay(5);
//     if (type == 1) {
//       Serial.println("change to poulpe");
//       const char* a[] = {"0-0", "0-1", "0-6", "0-7", "1-0", "1-7", "3-2", "3-5", "4-0", "4-7","5-0", "5-1", "5-6", "5-7", "6-0", "6-7", "7-2", "7-5"};
//       len_a = 18;
//     }
//     if (type == 2) {
//       Serial.println("change to alien");
//       //const char* a[] = {"0-0", "0-1", "0-6", "0-7", "1-0", "1-7", "4-0", "4-7", "5-0", "5-2", "5-5", "5-7", "6-0", "6-1", "6-6", "6-7", "7-0", "7-2", "7-5", "7-7"};
//       //len_a = 20;
//       const char* a[] = {"0-0", "0-1", "0-2", "0-3", "0-4", "0-5", "0-6", "0-7", "1-0", "1-1", "1-2", "1-3", "1-4", "1-5", "1-6", "1-7", "2-0", "2-1", "2-6", "2-7", "3-0", "3-1", "3-6", "3-7", "4-0", "4-1", "4-2", "4-3", "4-4", "4-5", "4-6", "4-7", "5-0", "5-1", "5-2", "5-3", "5-4", "5-5", "5-6", "5-7", "6-0", "6-1", "6-2", "6-3", "6-4", "6-5", "6-6", "6-7", "7-0", "7-1", "7-2", "7-3", "7-4", "7-5", "7-6"};
//       int len_a = 55;
//     }
//     //Serial.println("update");
//     Serial.println(len_a);
//     Serial.println(type);
//     Serial.println("------");
//     delay(10);
//     int c = -1;
//     char e[] = "";
//     char str[5] = "";
//     for (int i=0; i< 8; i++){ 
//       for (int j=0; j< 8; j++){
//         char str[5] = "";
//         sprintf(str, "%d", i);
//         strcat(str, "-");
//         sprintf(e, "%d", j);
//         strcat(str, e);
//         c = string_in(str, a, len_a);
//         //Serial.println(c);
//         if (c == 1) {
//             lc.setLed(0,i,j,false);
//         }
//         else {
//             lc.setLed(0,i,j,true);
//         }
//         // delay(5);
//       }
//     }
//   }
//   delay(250);
// }
