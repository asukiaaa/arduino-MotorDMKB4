#include <MotorDMKB4_asukiaaa.hpp>

#define SERIAL_DEBUG Serial

#define PIN_RS485_DERE 5
#define SERIAL_RS485 Serial2
#define ADDRESS_MOTOR 0
#define BAUDRATE_RS485 9600
// #define ADDRESS_MOTOR 1
// #define BAUDRATE_RS485 57600

rs485_asukiaaa::ModbusRtu::Central modbus(&SERIAL_RS485, PIN_RS485_DERE,
                                          PIN_RS485_DERE);
MotorDMKB4_asukiaaa::Core motor(&modbus, ADDRESS_MOTOR);

void setup() {
  SERIAL_RS485.begin(BAUDRATE_RS485);
  modbus.beginWithoutSerial();
  SERIAL_DEBUG.begin(115200);
}

void readAndPrintVolt() {
  uint16_t volt;
  auto result = motor.readVoltate(&volt);
  if (result == 0) {
    SERIAL_DEBUG.println("volt " + String(volt));
  } else {
    SERIAL_DEBUG.println("cannot read volt. Error " + String(result));
  }
}

void readAndPrintCurrent() {
  uint16_t current;
  auto result = motor.readCurrent(&current);
  if (result == 0) {
    SERIAL_DEBUG.println("current " + String(current));
  } else {
    SERIAL_DEBUG.println("cannot read current. Error " + String(result));
  }
}

void readAndPrintRotationCount() {
  int16_t count;
  auto result = motor.readRotationCount(&count);
  if (result == 0) {
    SERIAL_DEBUG.println("rotation count " + String(count));
  } else {
    SERIAL_DEBUG.println("cannot read rotation count. Error " + String(result));
  }
}

void writeSpeedRatio(float ratio) {
  auto result = motor.writeSpeedRatio(ratio);
  if (result == 0) {
    SERIAL_DEBUG.println("wrote speed ratio " + String(ratio));
  } else {
    SERIAL_DEBUG.println("failed to write speed ratio. Error " +
                         String(result));
  }
}

void loop() {
  writeSpeedRatio(0.5);
  readAndPrintVolt();
  readAndPrintCurrent();
  readAndPrintRotationCount();
  delay(2000);
  writeSpeedRatio(1);
  readAndPrintVolt();
  readAndPrintCurrent();
  readAndPrintRotationCount();
  delay(2000);
  writeSpeedRatio(0);
  readAndPrintVolt();
  readAndPrintCurrent();
  readAndPrintRotationCount();
  SERIAL_DEBUG.println("at " + String(millis()));
  delay(2000);
}
