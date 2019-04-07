#ifndef LD_ADJ_H
#define LD_ADJ_H

#include <Arduino.h>

// Possible adjustments
extern String ADJ[];
extern int ADJ_LEN;

class LdAdj {
public:
    LdAdj();
    int getNum();
    String getNextStr();
    String getPrevStr();
    String getString();
    void prevAdj();
    void nextAdj();

private:
    int _choice;
};

#endif
