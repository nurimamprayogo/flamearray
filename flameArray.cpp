#include <Arduino.h>
#include <inttypes.h>
#include "flameArray.h"

flameArray::flameArray(int _bitAdc, int _pinAdc, int _flameCK, int _flameDS, int _flameMR, int _maxArray)
{
	
	_ADCbit=_bitAdc;
	_ADCpin=_pinAdc;
	_CKflame=_flameCK;
	_DSflame=_flameDS;
	_MRflame=_flameMR;
	_ARRAYmax=_maxArray+1;
	
	pinMode(_CKflame,OUTPUT);
	pinMode(_DSflame,OUTPUT);
	pinMode(_MRflame,OUTPUT);
}
void flameArray::flameReset()
{
	digitalWrite(_MRflame,0);
	delayMicroseconds(10);
	digitalWrite(_MRflame,1);
}
void flameArray::flameStart()
{
	digitalWrite(_MRflame,1);
	digitalWrite(_CKflame,0);
	digitalWrite(_CKflame,1);
	digitalWrite(_CKflame,0);
	digitalWrite(_DSflame,1);
	digitalWrite(_CKflame,1);
	digitalWrite(_CKflame,0);
	digitalWrite(_DSflame,0);
	digitalWrite(_CKflame,1);
	digitalWrite(_CKflame,0);
}
int flameArray::flameRead(int _numArray)
{
	int _data;
	int _flameCount;
	flameReset();
	flameStart();
	delayMicroseconds(10);
	for(_flameCount=0;_flameCount<_numArray;_flameCount++)         
		{ 
		digitalWrite(_CKflame,1);
		digitalWrite(_CKflame,0);
		delayMicroseconds(10);     
		} 
	_data=analogRead(_ADCpin);
	if(_ADCbit==9)_data=map(_data,0,1023,0,512);
	else if(_ADCbit==8)_data=map(_data,0,1023,0,255);
	else if(_ADCbit==7)_data=map(_data,0,1023,0,127);
	else if(_ADCbit==6)_data=map(_data,0,1023,0,63);
	else if(_ADCbit==5)_data=map(_data,0,1023,0,31);
	return _data;
}
/*
int *flameArray::flameReadValue()
{
	int _data;
	int _flameCount;
	int _dataArray[_ARRAYmax];
	flameReset();
	flameStart();
	delayMicroseconds(10);
	for(_flameCount=0;_flameCount<_ARRAYmax;_flameCount++) 
	{
		_data=analogRead(_ADCpin);
		if(_ADCbit==8)_data=_data/4;
		_dataArray[_flameCount]=_data;
		delayMicroseconds(10); 
		digitalWrite(_CKflame,1);
		digitalWrite(_CKflame,0);
		delayMicroseconds(10);  
	}
	return _dataArray;
}
*/
uint8_t flameArray::flameReadBit(int *_rate)
{
	int _data[_ARRAYmax];
	int _flameCount;
	uint8_t _bit=0;
	for(_flameCount=0;_flameCount<_ARRAYmax;_flameCount++) 
	{
		_data[_flameCount]=flameRead(_flameCount);
	}
	for(_flameCount=0;_flameCount<_ARRAYmax;_flameCount++) 
	{
		_data[_flameCount]=flameRead(_flameCount);
	}
	for(_flameCount=0;_flameCount<_ARRAYmax;_flameCount++) 
	{
		if(_data[_flameCount]<_rate[_flameCount])_bit=_bit+1;
		if(_flameCount<_ARRAYmax-1)_bit=_bit*2;
	}
return _bit;
}