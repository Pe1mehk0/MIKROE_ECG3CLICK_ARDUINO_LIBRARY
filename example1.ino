#include "ecg3_click.h"
#include <SPI.h> // Need to include SPI for the ecg3_click.cpp dependency

#define CS_PIN 15 // Chip Select pin for the ECG 3 Click

// Create the ECG sensor instance
ECG3Click ecg(CS_PIN);

// We use 2ms to reliably read a new sample each iteration.
const int TARGET_DELAY_MS = 8; 

void setup() {
    // Start serial communication to print data
    Serial.begin(115200);
    while (!Serial);
    
    Serial.println("  MAX30003 ECG Data Acquisition Ready  ");
    
    // Initialize the ECG sensor chip and SPI communication
    ecg.begin();
    Serial.println("Initialization complete. Data stream started.");
}

void loop() {
    // 1. Read the ECG data
    int32_t ecgValue = ecg.getECG(); 

    // 2. Output the data point (for Serial Plotter)
    Serial.println(ecgValue);

    delay(TARGET_DELAY_MS); 
}
