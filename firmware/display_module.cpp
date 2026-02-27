#include "display_module.h"
#include "pins.h"

// Construtor - Inicializa a biblioteca U8g2 com os pinos I2C definidos em pins.h
// U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C(rotation, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE)
DisplayModule::DisplayModule() : u8g2(U8G2_R0, OLED_SCL_PIN, OLED_SDA_PIN, U8X8_PIN_NONE) {
    // O construtor da U8g2 é chamado aqui
}

void DisplayModule::begin() {
    Serial.println("Inicializando Módulo de Display OLED...");
    u8g2.begin();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.clearBuffer();
    u8g2.drawStr(0, 10, "EcoSort Init...");
    u8g2.sendBuffer();
    Serial.println("Módulo de Display OLED inicializado.");
}

void DisplayModule::showMessage(const String& message, int line) {
    u8g2.clearBuffer();
    u8g2.setCursor(0, (line * 10) + 10); // Ajusta a posição Y com base na linha
    u8g2.print(message);
    u8g2.sendBuffer();
}

void DisplayModule::updateStatus(EcoSortState currentState) {
    u8g2.clearBuffer();
    u8g2.setCursor(0, 10);
    u8g2.print("Status: ");
    switch (currentState) {
        case IDLE: u8g2.print("Ocioso"); break;
        case DETECCAO: u8g2.print("Detectando"); break;
        case ABERTURA_TAMPA: u8g2.print("Abrindo Tampa"); break;
        case CAPTURA: u8g2.print("Capturando"); break;
        case CLASSIFICACAO: u8g2.print("Classificando"); break;
        case DECISAO: u8g2.print("Decidindo"); break;
        case ACAO: u8g2.print("Acao"); break;
        case FECHAMENTO: u8g2.print("Fechando"); break;
        case ERRO: u8g2.print("ERRO!"); break;
    }
    u8g2.sendBuffer();
}

void DisplayModule::clearDisplay() {
    u8g2.clearBuffer();
    u8g2.sendBuffer();
}

DisplayModule displayModule; // Instância global
