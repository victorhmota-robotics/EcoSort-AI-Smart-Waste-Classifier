#ifndef ULTRASONIC_MODULE_H
#define ULTRASONIC_MODULE_H

#include <Arduino.h>

// Classe para gerenciar os sensores ultrassônicos HC-SR04
class UltrasonicModule {
public:
    UltrasonicModule();
    void begin();
    long readDistanceCm(int trigPin, int echoPin);
    bool detectObject(int trigPin, int echoPin, int thresholdCm = 20); // Detecta objeto dentro de um limite
    bool isObjectConfirmed(); // Simulado
    bool isCompartmentFull(int compartmentIndex, int thresholdCm = 10); // Monitora nível de enchimento

private:
    // Variáveis e métodos internos
};

extern UltrasonicModule ultrasonicModule;

#endif // ULTRASONIC_MODULE_H
