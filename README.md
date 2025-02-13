# arduino-MotorDMKB4 (MotorDMKB4_asukiaaa)

A library to control motor driver DMKB4 or DMKB5 by arduino.

## Fault information

Bit (int) | Role
-- | --
0 (1) | Over voltage
1 (2) | Under voltage
2 (4) | Controller over tempearture
3 (8) | Controller under tempearture
4 (16) | Over current
5 (32) | Over load
6 (64) | Hall Signal Faulty
7 (128) | Motor Stall

## License

MIT

## References

- [Beginner’s Guide to DMKB4/DMKB5 BLDC Motor Driver](https://beudmke.com/beginners-guide-to-dmkb4-dmkb5-bldc-motor-driver/)
