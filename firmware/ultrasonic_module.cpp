#include "ultrasonic_module.h"
#include "pins.h"

UltrasonicModule::UltrasonicModule() {
    // Construtor
}

void UltrasonicModule::begin() {
    Serial.println("Inicializando Módulo Ultrassônico...");
    // Configura os pinos Trigger e Echo para todos os sensores
    pinMode(US_APROX_TRIG_PIN, OUTPUT);
    pinMode(US_APROX_ECHO_PIN, INPUT);
    pinMode(US_PAPEL_TRIG_PIN, OUTPUT);
    pinMode(US_PAPEL_ECHO_PIN, INPUT);
    pinMode(US_PLASTICO_TRIG_PIN, OUTPUT);
    pinMode(US_PLASTICO_ECHO_PIN, INPUT);
    pinMode(US_METAL_TRIG_PIN, OUTPUT);
    pinMode(US_METAL_ECHO_PIN, INPUT);
    pinMode(US_VIDRO_TRIG_PIN, OUTPUT);
    pinMode(US_VIDRO_ECHO_PIN, INPUT);
    Serial.println("Módulo Ultrassônico inicializado.");
}

long UltrasonicModule::readDistanceCm(int trigPin, int echoPin) {
    // Limpa o pino Trigger
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Define o pino Trigger em HIGH por 10 microssegundos para enviar pulso
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Lê o tempo de duração do pulso no pino Echo
    long duration = pulseIn(echoPin, HIGH);

    // Calcula a distância em centímetros
    // A velocidade do som é de 343 metros por segundo, ou 0.0343 cm/microsegundo
    // A distância é (tempo * velocidade do som) / 2 (ida e volta)
    long distanceCm = duration * 0.0343 / 2;

    return distanceCm;
}

bool UltrasonicModule::detectObject(int trigPin, int echoPin, int thresholdCm) {
    long distance = readDistanceCm(trigPin, echoPin);
    // Serial.printf("Distância detectada (Pino %d/%d): %ld cm\n", trigPin, echoPin, distance);
    return (distance > 0 && distance < thresholdCm);
}

bool UltrasonicModule::isObjectConfirmed() {
    // Lógica para confirmar a presença do objeto (ex: múltiplas leituras, tempo de permanência)
    // Por enquanto, apenas simula
    return true;
}

bool UltrasonicModule::isCompartmentFull(int compartmentIndex, int thresholdCm) {
    int trigPin, echoPin;
    switch (compartmentIndex) {
        case 0: // Papel
            trigPin = US_PAPEL_TRIG_PIN;
            echoPin = US_PAPEL_ECHO_PIN;
            break;
        case 1: // Plástico
            trigPin = US_PLASTICO_TRIG_PIN;
            echoPin = US_PLASTICO_ECHO_PIN;
            break;
        case 2: // Metal
            trigPin = US_METAL_TRIG_PIN;
            echoPin = US_METAL_ECHO_PIN;
            break;
        case 3: // Vidro
            trigPin = US_VIDRO_TRIG_PIN;
            echoPin = US_VIDRO_ECHO_PIN;
            break;
        default:
            return false; // Índice inválido
    }
    long distance = readDistanceCm(trigPin, echoPin);
    Serial.printf("Nível do compartimento %d (Pino %d/%d): %ld cm\n", compartmentIndex, trigPin, echoPin, distance);
    return (distance > 0 && distance < thresholdCm);
}

UltrasonicModule ultrasonicModule; // Instância global
