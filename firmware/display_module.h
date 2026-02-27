#ifndef DISPLAY_MODULE_H
#define DISPLAY_MODULE_H

#include <Arduino.h>
#include <U8g2lib.h>
#include "fsm.h" // Para acessar os estados da FSM

// Classe para gerenciar o display OLED
class DisplayModule {
public:
    DisplayModule();
    void begin();
    void showMessage(const String& message, int line = 0);
    void updateStatus(EcoSortState currentState);
    void clearDisplay();

private:
    // U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2; // Para display 128x64
    U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2; // Para display 128x32 (comum 0.96")
};

extern DisplayModule displayModule;

#endif // DISPLAY_MODULE_H
