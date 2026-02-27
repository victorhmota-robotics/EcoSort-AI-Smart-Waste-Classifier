#ifndef LED_MODULE_H
#define LED_MODULE_H

#include <Arduino.h>

// Classe para gerenciar o LED branco
class LEDModule {
public:
    LEDModule();
    void begin();
    void turnOn(int ledPin);
    void turnOff(int ledPin);

private:
    // Variáveis e métodos internos
};

extern LEDModule ledModule;

#endif // LED_MODULE_H
