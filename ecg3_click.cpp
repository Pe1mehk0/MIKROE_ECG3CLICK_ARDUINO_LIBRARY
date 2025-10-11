#include "ecg3_click.h"

static int status3Count = 0;
static int status0Count = 0;

ECG3Click::ECG3Click(int csPin) : _csPin(csPin) {}


void ECG3Click::begin() {
    pinMode(_csPin, OUTPUT);
    SPI.begin(5, 21, 19, _csPin);
    deselectChip();

    // Perform resets and synchronization
    ecg3_swReset();
    ecg3_fifoReset();
    ecg3_sync();

    // General Configuration
    writeRegister(_ECG3_CNFG_GEN_REG, 
        _ECG3_FMSTR_32768HZ_ECG_128HZ | 
        _ECG3_ECG_CHANN_EN | 
        _ECG3_DCLOFF_EN |                
        _ECG3_RBIAS_100M_OHM |          
        _ECG3_RBIASP_EN | 
        _ECG3_RBIASN_EN);

    // Calibration Settings
    writeRegister(_ECG3_CNFG_CAL_REG, 
        _ECG3_VCAL_EN | 
        _ECG3_VMODE_BIPOL | 
        _ECG3_VMAG_500MICROV);

    // Electrode Multiplexer Configuration
    writeRegister(_ECG3_CNFG_EMUX_REG, 
        _ECG3_ECGP_EN | 
        _ECG3_ECGN_EN | 
        _ECG3_ECGP_CAL_VCALP | 
        _ECG3_ECGN_CAL_VCALN);

    // ECG-Specific Configuration
    writeRegister(_ECG3_CNFG_ECG_REG, 
        0x800000 |                      
        _ECG3_GAIN_40VPERV |            
        _ECG3_DHPF_500MILIHZ | 
        _ECG3_DLPF_40HZ);

    // RTOR Configuration
    writeRegister(_ECG3_CNFG_RTOR1_REG, 
        _ECG3_WNDW_12 | 
        _ECG3_RRGAIN_AUTO_SCALE | 
        _ECG3_RTOR_EN | 
        _ECG3_PAVG_8 | 
        0x000600);

    // Read INFO Register
    uint32_t info = readRegister(_ECG3_INFO_REG);
    Serial.print("INFO Register: ");
    Serial.println(info, HEX);
}


void ECG3Click::writeRegister(uint8_t regAddr, uint32_t data) {
    selectChip();
    SPI.transfer((regAddr << 1) & 0xFE);
    SPI.transfer((data >> 16) & 0xFF);
    SPI.transfer((data >> 8) & 0xFF);
    SPI.transfer(data & 0xFF);
    deselectChip();
}

uint32_t ECG3Click::readRegister(uint8_t regAddr) {
    uint32_t result = 0;
    selectChip();
    SPI.transfer((regAddr << 1) | 0x01);
    result |= (SPI.transfer(0x00) << 16);
    result |= (SPI.transfer(0x00) << 8);
    result |= SPI.transfer(0x00);
    deselectChip();
    return result;
}

uint32_t ECG3Click::getECG() {
    uint32_t rawECG = readRegister(_ECG3_ECG_FIFO_REG);
    int32_t ecgData = ((int32_t)(rawECG << 8)) >> 14;
    return ecgData;
}

// New Functions
void ECG3Click::ecg3_swReset() {
    writeRegister(_ECG3_SW_RST_REG, _ECG3_SW_RST_CMD);
    delay(10);
    Serial.println("ECG 3 Software Reset Complete.");
}

void ECG3Click::ecg3_fifoReset() {
    writeRegister(_ECG3_FIFO_RST_REG, _ECG3_FIFO_RST_CMD);
    Serial.println("ECG 3 FIFO Reset Complete.");
}

void ECG3Click::ecg3_sync() {
    writeRegister(_ECG3_SYNC_REG, _ECG3_SYNCH_CMD);
    Serial.println("ECG 3 Synchronization Complete.");
}

void ECG3Click::selectChip() {
    SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
    digitalWrite(_csPin, LOW);
}

void ECG3Click::deselectChip() {
    digitalWrite(_csPin, HIGH);
    SPI.endTransaction();
}