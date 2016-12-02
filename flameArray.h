#ifndef flameArray_h
#define flameArray_h

#include <Arduino.h>
#include <inttypes.h>

class flameArray{
public:

flameArray(int _bitAdc, int _pinAdc, int _flameCK, int _flameDS, int _flameMR, int _maxArray);
void flameReset();
void flameStart();
int flameRead(int _numArray);
uint8_t flameReadBit(int *_rate);
private:
int _ADCbit;
int _ADCpin;
int _CKflame;
int _DSflame;
int _MRflame;
int _ARRAYmax;
};

#endif