#ifndef SLEEP_H
#define SLEEP_H

extern const int MIN_SLEEP_TIME;
//Raspberry pi can handle sleeping sort of accurately to around 30 micros
void Sleep(int Micros);

#endif
