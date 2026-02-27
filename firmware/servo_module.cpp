#include "servo_module.h"
#include "pins.h"

ServoModule::ServoModule() {
    // Construtor
}

void ServoModule::begin() {
    Serial.println("Inicializando Módulo de Servos...");
    // Anexa os servos aos pinos correspondentes
    lidServo.attach(SERVO_PIN_TAMPA_PRINCIPAL);
    chamberDoorServo.attach(SERVO_PIN_PORTA_CAMARA);
    compartmentServos[0].attach(SERVO_PIN_COMPARTIMENTO_PAPEL);
    compartmentServos[1].attach(SERVO_PIN_COMPARTIMENTO_PLASTICO);
    compartmentServos[2].attach(SERVO_PIN_COMPARTIMENTO_METAL);
    compartmentServos[3].attach(SERVO_PIN_COMPARTIMENTO_VIDRO);

    // Garante que todos os servos estejam na posição fechada ao iniciar
    closeAllServos();
    Serial.println("Módulo de Servos inicializado.");
}

void ServoModule::openLid(int servoPin) {
    Serial.printf("Abrindo tampa principal (Pino: %d)...
", servoPin);
    lidServo.write(LID_OPEN_ANGLE);
    delay(1000); // Tempo para o servo se mover
}

void ServoModule::closeLid(int servoPin) {
    Serial.printf("Fechando tampa principal (Pino: %d)...
", servoPin);
    lidServo.write(LID_CLOSED_ANGLE);
    delay(1000); // Tempo para o servo se mover
}

bool ServoModule::isLidOpen() {
    // Lógica para verificar se a tampa está aberta (pode envolver um sensor de fim de curso)
    // Por enquanto, apenas simula
    return lidServo.read() == LID_OPEN_ANGLE;
}

void ServoModule::openChamberDoor(int servoPin) {
    Serial.printf("Abrindo porta da câmara (Pino: %d)...
", servoPin);
    chamberDoorServo.write(CHAMBER_OPEN_ANGLE);
    delay(1000); // Tempo para o servo se mover
}

void ServoModule::closeChamberDoor(int servoPin) {
    Serial.printf("Fechando porta da câmara (Pino: %d)...
", servoPin);
    chamberDoorServo.write(CHAMBER_CLOSED_ANGLE);
    delay(1000); // Tempo para o servo se mover
}

void ServoModule::openCompartment(int classificationResult) {
    Serial.printf("Abrindo compartimento para classificação: %d...
", classificationResult);
    if (classificationResult >= 0 && classificationResult < 4) {
        compartmentServos[classificationResult].write(COMPARTMENT_OPEN_ANGLE);
        delay(1000); // Tempo para o servo se mover
    }
}

void ServoModule::closeAllServos() {
    Serial.println("Fechando todos os servos...");
    lidServo.write(LID_CLOSED_ANGLE);
    chamberDoorServo.write(CHAMBER_CLOSED_ANGLE);
    for (int i = 0; i < 4; i++) {
        compartmentServos[i].write(COMPARTMENT_CLOSED_ANGLE);
    }
    delay(1500); // Tempo para todos os servos se moverem
}

bool ServoModule::areAllServosClosed() {
    // Lógica para verificar se todos os servos estão fechados
    // Por enquanto, apenas simula
    return (lidServo.read() == LID_CLOSED_ANGLE &&
            chamberDoorServo.read() == CHAMBER_CLOSED_ANGLE &&
            compartmentServos[0].read() == COMPARTMENT_CLOSED_ANGLE &&
            compartmentServos[1].read() == COMPARTMENT_CLOSED_ANGLE &&
            compartmentServos[2].read() == COMPARTMENT_CLOSED_ANGLE &&
            compartmentServos[3].read() == COMPARTMENT_CLOSED_ANGLE);
}

ServoModule servoModule; // Instância global
