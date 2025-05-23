#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    while (!Serial);

    // Flash Memory Information
    Serial.println("ESP32-S3 Memory Information:");

    // Get Flash Chip Size
    Serial.print("Flash chip size: ");
    Serial.print(ESP.getFlashChipSize());
    Serial.println(" bytes");

    // Get Free Sketch Space
    Serial.print("Free sketch space: ");
    Serial.print(ESP.getFreeSketchSpace());
    Serial.println(" bytes");

    // Heap Information
    Serial.print("Total heap size: ");
    Serial.print(ESP.getHeapSize());
    Serial.println(" bytes");

    Serial.print("Free heap size: ");
    Serial.print(ESP.getFreeHeap());
    Serial.println(" bytes");

    Serial.print("Minimum free heap ever: ");
    Serial.print(ESP.getMinFreeHeap());
    Serial.println(" bytes");

    // PSRAM Information
    Serial.print("PSRAM size: ");
    Serial.print(ESP.getPsramSize());
    Serial.println(" bytes");

    Serial.print("Free PSRAM: ");
    Serial.print(ESP.getFreePsram());
    Serial.println(" bytes");

    // Internal RAM Information
    Serial.println("Internal RAM Information:");

    Serial.print("Total internal RAM size: ");
    Serial.print(ESP.getHeapSize() - ESP.getPsramSize());
    Serial.println(" bytes");

    Serial.print("Free internal RAM: ");
    Serial.print(ESP.getFreeHeap() - ESP.getFreePsram());
    Serial.println(" bytes");
}

void loop() {
    // Do nothing
}
