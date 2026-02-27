#ifndef CAMERA_MODULE_H
#define CAMERA_MODULE_H

#include <Arduino.h>

// Classe para gerenciar o módulo da câmera OV2640
class CameraModule {
public:
    CameraModule();
    void begin();
    bool captureImage();
    int runInference(); // Simula a inferência do modelo de IA

private:
    // Variáveis e métodos internos para controle da câmera
};

extern CameraModule cameraModule;

#endif // CAMERA_MODULE_H
