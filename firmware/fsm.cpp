#include "fsm.h"
#include <Arduino.h>

// Incluir módulos para interação
#include "camera_module.h"
#include "servo_module.h"
#include "ultrasonic_module.h"
#include "display_module.h"
#include "led_module.h"

EcoSortFSM::EcoSortFSM() {
    currentState = IDLE;
    stateEntryTime = 0;
}

void EcoSortFSM::begin() {
    // Inicializações de módulos aqui, se necessário
        cameraModule.begin();
    servoModule.begin();
    ultrasonicModule.begin();
    displayModule.begin();
rial.begin(115200);
    Serial.println("EcoSort FSM Iniciada.");
    Serial.print("Estado Inicial: ");
    Serial.println("IDLE");
}

void EcoSortFSM::transitionTo(EcoSortState newState) {
    currentState = newState;
    stateEntryTime = millis();
    Serial.print("Transição para o estado: ");
    switch (newState) {
        case IDLE: Serial.println("IDLE"); break;
        case DETECCAO: Serial.println("DETECCAO"); break;
        case ABERTURA_TAMPA: Serial.println("ABERTURA_TAMPA"); break;
        case CAPTURA: Serial.println("CAPTURA"); break;
        case CLASSIFICACAO: Serial.println("CLASSIFICACAO"); break;
        case DECISAO: Serial.println("DECISAO"); break;
        case ACAO: Serial.println("ACAO"); break;
        case FECHAMENTO: Serial.println("FECHAMENTO"); break;
        case ERRO: Serial.println("ERRO"); break;
    }
    // display_module.updateStatus(newState);
}

EcoSortState EcoSortFSM::getCurrentState() {
    return currentState;
}

void EcoSortFSM::run() {
    switch (currentState) {
        case IDLE:
            handleIdle();
            break;
        case DETECCAO:
            handleDeteccao();
            break;
        case ABERTURA_TAMPA:
            handleAberturaTampa();
            break;
        case CAPTURA:
            handleCaptura();
            break;
        case CLASSIFICACAO:
            handleClassificacao();
            break;
        case DECISAO:
            handleDecisao();
            break;
        case ACAO:
            handleAcao();
            break;
        case FECHAMENTO:
            handleFechamento();
            break;
        case ERRO:
            handleError();
            break;
    }
}

void EcoSortFSM::handleIdle() {
    // Lógica para o estado IDLE
    // Aguarda detecção de objeto pelo sensor ultrassônico de aproximação
    if (ultrasonicModule.detectObject(US_APROX_TRIG_PIN, US_APROX_ECHO_PIN)) {
        transitionTo(DETECCAO);
    }
    // Simulação: Transiciona após 5 segundos
    if (millis() - stateEntryTime > 5000) {
        Serial.println("Simulando detecção de objeto.");
        transitionTo(DETECCAO);
    }
}

void EcoSortFSM::handleDeteccao() {
    // Lógica para o estado DETECCAO
    // Confirma a presença do objeto e transiciona para abertura da tampa
    if (ultrasonicModule.isObjectConfirmed()) {
        transitionTo(ABERTURA_TAMPA);
    }
    // Simulação: Transiciona após 2 segundos
    if (millis() - stateEntryTime > 2000) {
        Serial.println("Simulando confirmação de objeto.");
        transitionTo(ABERTURA_TAMPA);
    }
}

void EcoSortFSM::handleAberturaTampa() {
    // Lógica para o estado ABERTURA_TAMPA
    // Abre o servo da tampa principal
    servoModule.openLid(SERVO_PIN_TAMPA_PRINCIPAL);
    if (servoModule.isLidOpen()) {
        transitionTo(CAPTURA);
    }
    // Simulação: Transiciona após 3 segundos
    if (millis() - stateEntryTime > 3000) {
        Serial.println("Simulando abertura da tampa.");
        transitionTo(CAPTURA);
    }
}

void EcoSortFSM::handleCaptura() {
    // Lógica para o estado CAPTURA
    // Fecha a porta da câmara, liga o LED, captura a imagem
    servoModule.closeChamberDoor(SERVO_PIN_PORTA_CAMARA);
    ledModule.turnOn(LED_BRANCO_PIN);
    if (cameraModule.captureImage()) {
        ledModule.turnOff(LED_BRANCO_PIN);
        transitionTo(CLASSIFICACAO);
    } else {
        transitionTo(ERRO);
    }
    // Simulação: Transiciona após 4 segundos
    if (millis() - stateEntryTime > 4000) {
        Serial.println("Simulando captura de imagem.");
        transitionTo(CLASSIFICACAO);
    }
}

void EcoSortFSM::handleClassificacao() {
    // Lógica para o estado CLASSIFICACAO
    // Roda o modelo de IA no ESP32-S3 para classificar a imagem
    int classificationResult = cameraModule.runInference();
    if (classificationResult != -1) { // -1 indicaria erro
        // Armazena o resultado para o estado de Decisão
        // fsmData.lastClassification = classificationResult;
        // Para simplificar, vamos armazenar o resultado em uma variável global ou passar para o próximo estado
        // Por enquanto, vamos usar uma variável estática para simular
        static int lastClassificationResult = 0;
        lastClassificationResult = classificationResult;
        transitionTo(DECISAO);
    } else {
        transitionTo(ERRO);
    }
    // Simulação: Transiciona após 5 segundos com um resultado aleatório
    if (millis() - stateEntryTime > 5000) {
        Serial.println("Simulando classificação de resíduo.");
        // Simular um resultado de classificação (0=Papel, 1=Plastico, etc.)
        // fsmData.lastClassification = random(0, 4);
        transitionTo(DECISAO);
    }
}

void EcoSortFSM::handleDecisao() {
    // Lógica para o estado DECISAO
    // Baseado na classificação, decide qual compartimento abrir
    // int targetCompartment = fsmData.lastClassification;
    // Precisamos obter o resultado da classificação do estado anterior
    // Por enquanto, vamos usar a variável estática simulada

    int targetCompartment = lastClassificationResult;

    if (ultrasonicModule.isCompartmentFull(targetCompartment)) {
        displayModule.showMessage("Compartimento Cheio!");
        transitionTo(ERRO); // Ou tentar outro compartimento, se houver lógica para isso
    } else {
        transitionTo(ACAO);
    }
    // Simulação: Transiciona após 1 segundo
    if (millis() - stateEntryTime > 1000) {
        Serial.println("Simulando decisão de compartimento.");
        transitionTo(ACAO);
    }
}

void EcoSortFSM::handleAcao() {
    // Lógica para o estado ACAO
    // Abre o servo do compartimento correto

    servoModule.openCompartment(lastClassificationResult);
    // if (servoModule.isCompartmentOpen()) { // Não temos essa função ainda, manter comentado
    //     transitionTo(FECHAMENTO);
    // }
    // Simulação: Transiciona após 3 segundos
    if (millis() - stateEntryTime > 3000) {
        Serial.println("Simulando abertura de compartimento.");
        transitionTo(FECHAMENTO);
    }
}

void EcoSortFSM::handleFechamento() {
    // Lógica para o estado FECHAMENTO
    // Fecha todas as portas e retorna ao IDLE
    servoModule.closeAllServos();
    if (servoModule.areAllServosClosed()) {
        transitionTo(IDLE);
    }
    // Simulação: Transiciona após 4 segundos
    if (millis() - stateEntryTime > 4000) {
        Serial.println("Simulando fechamento de portas.");
        transitionTo(IDLE);
    }
}

void EcoSortFSM::handleError() {
    // Lógica para o estado ERRO
    // Exibir mensagem de erro no display, talvez piscar um LED
    displayModule.showMessage("ERRO! Reiniciando...");
    // delay(5000); // Aguarda 5 segundos antes de tentar reiniciar
    // transitionTo(IDLE);
    // Simulação: Transiciona após 5 segundos
    if (millis() - stateEntryTime > 5000) {
        Serial.println("Simulando recuperação de erro.");
        transitionTo(IDLE);
    }
}

// Variável global para armazenar o último resultado de classificação
// Isso é uma simplificação para o exemplo, em um projeto real, seria melhor encapsular isso na classe FSM
int lastClassificationResult = 0;

