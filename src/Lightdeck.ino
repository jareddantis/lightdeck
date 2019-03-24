/**
 * @file      Lightdeck.ino
 * @brief     yes
 * @author    Jared Dantis, 2019
 * @author    Ben Trew, 2018
 * @copyright GPLv3 (see README.md and LICENSE)
 */

#include <LdAdj.h>
#include <LdConst.h>
#include <LdDisplay.h>
#include <LdMidi.h>
#include <LdBtn.h>
#include <LdHoldBtn.h>

/**
 * Objects
 */
LdAdj value;                     ///< Adjustment values
LdDisplay disp;                  ///< LCD
LdMidi mid;                      ///< MIDI

/**
 * Buttons
 */
LdBtn adjBtn(PIN_BTN_MODE);      ///< Adjustment selection button
LdBtn rstBtn(PIN_BTN_RESET);     ///< Reset adjustments button
LdBtn undoBtn(PIN_BTN_UNDO);     ///< Undo adjustment button
LdHoldBtn decBtn(PIN_BTN_MINUS); ///< Adjustment decrement button
LdHoldBtn incBtn(PIN_BTN_PLUS);  ///< Adjustment increment button

void setup() {
    disp.welcome();
    mid.begin(value.getArray());
}

void loop() {
    mid.read();
    disp.updateAdj(value.getAdj());
    disp.updateValue(String(value.get(value.getChoice())));

    // Buttons
    decBtn.pressed(onDecBtnPressed);
    incBtn.pressed(onIncBtnPressed);
    if (adjBtn.pressed()) value.nextAdj();
    if (undoBtn.pressed()) mid.sendNote(MID_CHAN_UNDO);
    if (rstBtn.pressed()) {
        value.reset();
        mid.sendNote(MID_CHAN_RESET);
    }
}

void onDecBtnPressed() {
    int num = value.getChoice();
    mid.sendControlChange(num, value.update(num, false));
}

void onIncBtnPressed() {
    int num = value.getChoice();
    mid.sendControlChange(num, value.update(num, true));
}
