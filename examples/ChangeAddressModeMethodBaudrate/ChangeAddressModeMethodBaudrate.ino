#include <MotorDMKB4_asukiaaa.hpp>

#define MODE_TO_SET MotorDMKB4_asukiaaa::ControlMode::ClosedLoop
#define METHOD_TO_SET MotorDMKB4_asukiaaa::ControlMethod::RS485
#define BAUDRATE_TO_SET MotorDMKB4_asukiaaa::Baudrate::Baud57600
#define ADDRESS_MOTOR_TO_SET 1

#define ADDRESS_MOTOR 1
#define BAUDRATE_RS485T 9600
#define PIN_RS485_DERE 5
#define SERIAL_RS485 Serial2

rs485_asukiaaa::ModbusRtu::Central modbus(&SERIAL_RS485, PIN_RS485_DERE,
                                          PIN_RS485_DERE);
MotorDMKB4_asukiaaa::Core motor(&modbus, ADDRESS_MOTOR);

#define SERIAL_DEBUG Serial

void setup() {
  SERIAL_RS485.begin(BAUDRATE_RS485T);
  modbus.beginWithoutSerial();
  SERIAL_DEBUG.begin(115200);
}

void loop() {
  int result;
  result = motor.writeControlModeAndMethod(
      MotorDMKB4_asukiaaa::ControlMode::ClosedLoop,
      MotorDMKB4_asukiaaa::ControlMethod::RS485);
  if (result == 0) {
    SERIAL_DEBUG.println("wrote control mode and method");
  } else {
    SERIAL_DEBUG.println("failed to write control mode and method " +
                         String(result));
  }

  uint8_t id = ADDRESS_MOTOR_TO_SET;
  result = motor.writeId(id);
  if (result == 0) {
    SERIAL_DEBUG.println("write id " + String(id));
  } else {
    SERIAL_DEBUG.println("cannot write id. Error " + String(result));
  }

  result = motor.writeBaudrate(BAUDRATE_TO_SET);
  if (result == 0) {
    SERIAL_DEBUG.println("write baudrate " + String((uint16_t)BAUDRATE_TO_SET));
  } else {
    SERIAL_DEBUG.println("cannot write baudrate. Error " + String(result));
  }

  SERIAL_DEBUG.println("at " + String(millis()));
  SERIAL_DEBUG.println("Require resetting motor driver to activate configs.");
  delay(2000);
}
