#pragma once

#include <Arduino.h>
#include <rs485_asukiaaa.h>

namespace MotorDMKB4_asukiaaa {

namespace Register {
const uint16_t MotorTargetDataA = 0x0000;
const uint16_t MotorTargetDataB = 0x0001;
const uint16_t DeviceNodeID = 0x0100;
const uint16_t CommunicationBaudRate = 0x0101;
const uint16_t CommunicationTimeoutPeriod = 0x0102;
const uint16_t ControlModeAndMethod = 0x0103;
const uint16_t RunningDirectionAndFeedbackDirection = 0x0104;
const uint16_t MaximumSpeedValue = 0x0105;
const uint16_t MinimumSpeedValue = 0x0106;
const uint16_t Voltate = 0x0200;
const uint16_t Current = 0x0201;
const uint16_t Temperature = 0x0202;
const uint16_t MotorSpeed = 0x0203;
const uint16_t MotorStatus = 0x0204;
const uint16_t FaultInformation = 0x0205;
const uint16_t RotationCount = 0x0206;
const uint16_t RestoreFactorySetting = 0x0F00;
}  // namespace Register

enum class ControlMode : uint8_t {
  OpenLoop = 0,
  ClosedLoop = 1,
};
enum class ControlMethod : uint8_t {
  Physical = 0,
  RS485 = 0x03,
};
enum class Baudrate : uint16_t {
  Baud4800 = 0,
  Baud9600 = 1,
  Baud19200 = 2,
  Baud38400 = 3,
  Baud57600 = 4,
};

class Core {
 public:
  Core(rs485_asukiaaa::ModbusRtu::Central* modbus, uint8_t address)
      : modbus(modbus), address(address) {}

  void begin(unsigned long baudrate, unsigned long config = SERIAL_8E1) {
    modbus->begin(baudrate, config);
    beginWithoutModbus();
  }

  rs485_asukiaaa::ModbusRtu::Central* getModbus() { return modbus; }

  void beginWithoutModbus() {}

  int readVoltate(uint16_t* volt) {
    return modbus->readRegistersBy16t(address, Register::Voltate, volt, 1);
  }

  int readCurrent(uint16_t* current) {
    return modbus->readRegistersBy16t(address, Register::Current, current, 1);
  }

  int readMotorSpeed(uint16_t* rpm) {
    return modbus->readRegistersBy16t(address, Register::MotorSpeed, rpm, 1);
  }

  int readRotationCount(int16_t* count) {
    return modbus->readRegistersBy16t(address, Register::RotationCount,
                                      (uint16_t*)count, 1);
  }

  int readFaultInformation(uint16_t* info) {
    return modbus->readRegistersBy16t(address, Register::FaultInformation, info,
                                      1);
  }

  int writeSpeedRatio(float ratio) {
    return writeMotorTargetDataA(ratio * 10000);
  }

  int writeMotorTargetDataA(int16_t val) {
    return modbus->writeRegisterBy16t(address, Register::MotorTargetDataA, val);
  }

  int writeMotorTargetDataB(int16_t val) {
    return modbus->writeRegisterBy16t(address, Register::MotorTargetDataB, val);
  }

  int writeControlModeAndMethod(ControlMode mode, ControlMethod method) {
    uint16_t data = ((uint16_t)mode << 8) | (uint8_t)method;
    return modbus->writeRegisterBy16t(address, Register::ControlModeAndMethod,
                                      data);
  }

  int writeId(uint16_t id) {
    return modbus->writeRegisterBy16t(address, Register::DeviceNodeID, id);
  }

  int writeBaudrate(Baudrate baudrate) {
    return modbus->writeRegisterBy16t(address, Register::CommunicationBaudRate,
                                      (uint16_t)baudrate);
  }

 private:
  uint8_t address;
  rs485_asukiaaa::ModbusRtu::Central* modbus;
};
}  // namespace MotorDMKB4_asukiaaa
