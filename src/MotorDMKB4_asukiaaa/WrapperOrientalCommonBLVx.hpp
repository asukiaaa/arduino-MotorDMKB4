#pragma once
#if __has_include(<OrientalCommon_asukiaaa/BLx.hpp>)
#include <MotorDMKB4_asukiaaa.hpp>

namespace MotorDMKB4_asukiaaa {
namespace WrapperOrientalCommonBLVx {

class Core : public MotorDMKB4_asukiaaa::Core,
             public OrientalCommon_asukiaaa::BLx::Base {
 public:
  Core(rs485_asukiaaa::ModbusRtu::Central *modbus, uint8_t address)
      : MotorDMKB4_asukiaaa::Core(modbus, address) {}

  void begin(unsigned long baudrate,
             unsigned long config = SERIAL_8E1) override {
    MotorDMKB4_asukiaaa::Core::begin(baudrate, config);
  }
  void beginWithoutModbus() override {
    MotorDMKB4_asukiaaa::Core::beginWithoutModbus();
  }
  uint8_t writeLock() override {
    return MotorDMKB4_asukiaaa::Core::writeSpeedRatio(0);
  }
  uint8_t writeStop() override {
    return MotorDMKB4_asukiaaa::Core::writeSpeedRatio(0);
  }
  uint8_t writeSpeed32t(int32_t speed) override {
    return MotorDMKB4_asukiaaa::Core::writeSpeedRatio((float)speed /
                                                      getRpmMax());
  }
  uint8_t readAlarmU32t(uint32_t *alarm) override {
    uint16_t info;
    auto result = MotorDMKB4_asukiaaa::Core::readFaultInformation(&info);
    if (result == 0) {
      *alarm = info;
    }
    return result;
  }
  uint8_t readLoadTorquePercent(float *torquePercent) override {
    uint16_t current;
    auto result = MotorDMKB4_asukiaaa::Core::readCurrent(&current);
    if (result == 0) {
      *torquePercent = (float)current / currentMax;
    }
    return result;
  }
  uint8_t readFeedbackSpeed32t(int32_t *speed) override {
    uint16_t rpm;
    auto result = MotorDMKB4_asukiaaa::Core::readMotorSpeed(&rpm);
    if (result == 0) {
      *speed = rpm;
    }
    return result;
  }
  uint8_t writeSetupConfigIfNeeded() override { return 0; }

  rs485_asukiaaa::ModbusRtu::Central *getModbus() override {
    return MotorDMKB4_asukiaaa::Core::getModbus();
  }
  uint16_t currentMax = 40;
  uint32_t rpmMin = 100;
  uint32_t rpmMax = 3000;
  uint32_t getRpmMin() override { return rpmMin; }
  uint32_t getRpmMax() override { return rpmMax; }
};

}  // namespace WrapperOrientalCommonBLVx
}  // namespace MotorDMKB4_asukiaaa
#endif
