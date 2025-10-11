# ❤️ ECG3Click Arduino Library Overview

This library provides a lightweight and reliable way to interface the MIKROE ECG 3 Click board with Arduino via SPI.
At the time of development, no existing Arduino library supported this board — so it was written to simplify access to real ECG data from the MAX30003 analog front-end.

This library was originally developed for Vital, a wearable health-monitoring system created during the Samsung Solve for Tomorrow competition in Poland.

One of its goals was to provide continuous raw ECG data for real-time cardiac monitoring in emergency departments.

After successfully integrating it into the working prototype, the library was released publicly to support other developers and researchers who want to interface the ECG 3 Click board with the Arduino ecosystem.

> ⚠️ **Disclaimer:** This library is *not a medical device*. Use it only for educational, research, and prototyping purposes.

---

## 🧠 Development Context

**Tested Hardware:** [Adafruit Feather ESP32 V2]
**Board Communication:** SPI interface (hardware SPI)

## ✨ Features

- Simple `ECG3Click` C++ class (`begin()`, `getECG()`)
- Full SPI register access: `writeRegister()` / `readRegister()`
- Startup sequence: software reset → FIFO reset → sync
- Ready-to-use defaults:
  - **Sample rate:** 128 Hz  
  - **Gain:** 40 V/V  
  - **HPF:** 0.5 Hz  
  - **LPF:** 40 Hz  
  - **DC lead-off** and **internal bias (100 MΩ)** enabled  
  - **Calibration:** bipolar, 500 µV amplitude  
  - **RTOR:** window = 12, auto-gain, PAVG = 8  

---

## 📦 Installation

1. Clone or download this repository.  
2. Copy the folder into your Arduino `libraries/` directory.  
3. Restart the Arduino IDE.  
4. Open the example or write your own sketch.


---

## 🔌 Wiring (Feather ESP32 v2 Example)

The library calls `SPI.begin(SCLK, MISO, MOSI, CS)` inside `begin()`.  
Default pins:

| Signal | Pin |
|---------|-----|
| SCLK | 5 |
| MISO | 21 |
| MOSI | 19 |
| CS | (user-defined in constructor) |

> You can change them directly in `ecg3_click.cpp` if needed.

---

| Function                    | Description                                        |
| --------------------------- | -------------------------------------------------- |
| `begin()`                   | Initializes SPI, configures all MAX30003 registers |
| `getECG()`                  | Reads one ECG sample              |
| `writeRegister(addr, data)` | Low-level write                                    |
| `readRegister(addr)`        | Low-level read                                     |
| `ecg3_swReset()`            | Software reset                                     |
| `ecg3_fifoReset()`          | FIFO reset                                         |
| `ecg3_sync()`               | Synchronization pulse                              |


---

# 🎉 Future Improvements

This is the initial release (v1.0.0), focused on essential functionality. Future functions can easily be implemented in future versions, including:

  - RTOR (R–R interval) measurement and heart rate calculation
  - Lead-off detection
  - Interrupt-driven sampling
  - Extended calibration options

# 🧑‍💻 Author

Developed by Aliaksandr Kuryla under the Vital
