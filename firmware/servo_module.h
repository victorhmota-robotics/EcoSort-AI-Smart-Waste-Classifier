#ifndef SERVO_MODULE_H
#define SERVO_MODULE_H

#include <Arduino.h>
#include <ESP32Servo.h>

// Classe para gerenciar os servos SG90
class ServoModule {
public:
    ServoModule();
    void begin();
    void openLid(int servoPin);
    void closeLid(int servoPin);
    bool isLidOpen(); // Simulado
    void openChamberDoor(int servoPin);
    void closeChamberDoor(int servoPin);
    void openCompartment(int classificationResult); // Abre o compartimento baseado na classificação
    void closeAllServos();
    bool areAllServosClosed(); // Simulado

private:
    Servo lidServo; // Servo da tampa principal
    Servo chamberDoorServo; // Servo da porta da câmara de análise
    Servo compartmentServos[4]; // Servos dos 4 compartimentos

    // Posições dos servos (exemplo, ajustar conforme necessário)
    const int LID_OPEN_ANGLE = 90;
    const int LID_CLOSED_ANGLE = 0;
    const int CHAMBER_OPEN_ANGLE = 90;
    const int CHAMBER_CLOSED_ANGLE = 0;
    const int COMPARTMENT_OPEN_ANGLE = 90;
    const int COMPARTMENT_CLOSED_ANGLE = 0;
};

extern ServoModule servoModule;

#endif // SERVO_MODULE_H
