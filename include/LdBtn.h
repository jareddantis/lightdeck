#ifndef LD_BTN_H
#define LD_BTN_H

#include <Arduino.h>
#include <Bounce2.h>

class LdBtn {
protected:
    Bounce _debouncer;

public:
    LdBtn(int);
    bool pressed();
    void pressed(void(*onPress)(void), void(*onHold)(void));

private:
    bool _onHoldFired;
};

#endif
