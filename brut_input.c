
#include "brut_input.h"

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


char hexDigit(unsigned n)
{
    if (n < 10) {
        return n + '0';
    } else {
        return (n - 10) + 'A';
    }
}

//Conversion d'un caractère en hexadecimal
void charToHex(char c, char hex[3])
{
    hex[0] = hexDigit(c / 0x10);
    hex[1] = hexDigit(c % 0x10);
    hex[2] = '\0';
}

void HexToBinary(char input[3], char res[9]){
    // /char res[9]; // the length of the output string has to be n+1 where n is the number of binary digits to show, in this case 8
    res[8] = '\0';
    int t = 128; // set this to s^(n-1) where n is the number of binary digits to show, in this case 8
    int v = strtol(input, 0, 16); // convert the hex value to a number

    while(t) // loop till we're done
    {
        strcat(res, t < v ? "1" : "0");
        if(t < v)
            v -= t;
        t /= 2;
    }
    // res now contains the binary representation of the number
}

void fusion(char Left[9], char Right[9], char Res[13]){
    Res[12] = '\0';
    int i=0;
    for (i=0; i<6; i++){
        Res[i]=Left[i+10];
    }
    for (i=0; i<6; i++){
      Res[i+6]=Right[i+2];
    }
    //Now Res conitent Left+right
}

int binaryToDecimal(char tableau[13]){
    int resultat=0;
    int i=0;
    for (i=0;i<12;i++){
        if(tableau[i]=='1'){
          resultat+=pow(2,11-i);
        }
    }
    return resultat;
}
