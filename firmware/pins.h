#ifndef PINS_H
#define PINS_H

// Pinagem da Câmera OV2640
#define CAM_PIN_D0    5
#define CAM_PIN_D1    6
#define CAM_PIN_D2    7
#define CAM_PIN_D3    8
#define CAM_PIN_D4    9
#define CAM_PIN_D5    10
#define CAM_PIN_D6    11
#define CAM_PIN_D7    12
#define CAM_PIN_PCLK  3
#define CAM_PIN_VSYNC 4
#define CAM_PIN_HREF  2
#define CAM_PIN_XCLK  1
#define CAM_PIN_PWDN  45
#define CAM_PIN_RESET 46
#define CAM_PIN_SIOD  17  // SDA para Câmera
#define CAM_PIN_SIOC  18  // SCL para Câmera

// Pinagem dos Servos SG90
#define SERVO_PIN_TAMPA_PRINCIPAL   14
#define SERVO_PIN_PORTA_CAMARA      15
#define SERVO_PIN_COMPARTIMENTO_PAPEL   16
#define SERVO_PIN_COMPARTIMENTO_PLASTICO 19
#define SERVO_PIN_COMPARTIMENTO_METAL   20
#define SERVO_PIN_COMPARTIMENTO_VIDRO   21

// Pinagem dos Sensores Ultrassônicos HC-SR04
#define US_APROX_TRIG_PIN   33
#define US_APROX_ECHO_PIN   34
#define US_PAPEL_TRIG_PIN   35
#define US_PAPEL_ECHO_PIN   36
#define US_PLASTICO_TRIG_PIN 37
#define US_PLASTICO_ECHO_PIN 38
#define US_METAL_TRIG_PIN   39
#define US_METAL_ECHO_PIN   40
#define US_VIDRO_TRIG_PIN   41
#define US_VIDRO_ECHO_PIN   42

// Pinagem do Display OLED 0.96” (I2C)
#define OLED_SDA_PIN  8
#define OLED_SCL_PIN  9

// Pinagem do LED Branco
#define LED_BRANCO_PIN 48

#endif // PINS_H
