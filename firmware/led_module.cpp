#include "led_module.h"
#include "pins.h"

LEDModule::LEDModule() {
    // Construtor
}

void LEDModule::begin() {
    Serial.println("Inicializando Módulo de LED...");
    pinMode(LED_BRANCO_PIN, OUTPUT);
    turnOff(LED_BRANCO_PIN); // Garante que o LED esteja desligado ao iniciar
    Serial.println("Módulo de LED inicializado.");
}

void LEDModule::turnOn(int ledPin) {
    Serial.printf("Ligando LED (Pino: %d)...
", ledPin);
    digitalWrite(ledPin, HIGH);
}

void LEDModule::turnOff(int ledPin) {
    Serial.printf("Desligando LED (Pino: %d)...
", ledPin);
    digitalWrite(ledPin, LOW);
}

LEDModule ledModule; // Instância global
