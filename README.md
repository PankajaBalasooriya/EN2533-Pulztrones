# EN2533-Pulztrones
## EN2533 Robot Design and Competition

## 📖 Project Overview

Our robot was designed to complete a series of challenges inspired by the *Stranger Things* universe. The competition featured tasks such as line navigation, maze-solving, box manipulation, and terrain traversal. The project involved extensive hardware and software development, with the final product demonstrating the capability to autonomously navigate and solve challenges within a specified arena.


### Group Members
| Name | Index Number |Email|
|------|--------------|--------------|
| Balasooriya B A P I | 220054N | balasooriyabapi.22@uom.lk
| Liyanage D L B B | 220362G |banuka2002liyanage@gmail.com|
| Pathirana P D R O | 220448C |oshadha1619@gmail.com|
| Fernando A R D | 220161N |rusirufernando513@gmail.com|
| Dineshara M C | 220128V |chandupadineshara@gmail.com|


# Pin Assignment
| **Pin Number** | **Mode**             | **Assigned Name**     |
|----------------|----------------------|-----------------------|
| 0              | Digital I/O (UART RX) |                       |
| 1              | Digital I/O (UART TX) |                       |
| 2              | Digital I/O, PWM      |                       |
| 3              | Digital I/O, PWM      |  B2 (Select)          |
| 4              | Digital I/O, PWM      |        enbPin         |
| 5              | Digital I/O, PWM      |        enaPin         |
| 6              | Digital I/O, PWM      |    mechanism gripper  |
| 7              | Digital I/O           |  arm servo      |
| 8              | Digital I/O           |  coin  servo    |
| 9              | Digital I/O, PWM      |                       |
| 10             | Digital I/O, PWM      |                       |
| 11             | Digital I/O, PWM      |                       |
| 12             | Digital I/O           |                       |
| 13             | Digital I/O           |                       |
| 14             | Digital I/O (UART TX) |                       |
| 15             | Digital I/O (UART RX) |                       |
| 16             | Digital I/O (UART TX) |       Bluetooth       |
| 17             | Digital I/O (UART RX) |       Bluetooth       |
| 18             | Digital I/O (UART TX) |   RIGHT_ENCODER_PIN_A |
| 19             | Digital I/O (UART RX) |    LEFT_ENCODER_PIN_A |
| 20             | Digital I/O (I2C SDA) |          I2C   MUX    |
| 21             | Digital I/O (I2C SCL) |          I2C   MUX    |
| 22             | Digital I/O           |   rightMotorBackward  |
| 23             | Digital I/O           |   rightMotorForward   |
| 24             | Digital I/O           |   leftMotorBackward   |
| 25             | Digital I/O           |   leftMotorForward    |
| 26             | Digital I/O           |   RIGHT_ENCODER_PIN_B |
| 27             | Digital I/O           |   LEFT_ENCODER_PIN_B  |
| 28 >>31        | Digital I/O           |    Ultrasonic Eco     |
| 29 >>32        | Digital I/O           |    Ultrasonic Trigger |
| 30             | Digital I/O           |         Buzzer        |
| 31             | Digital I/O           |      I2c MUX A0       |
| 32             | Digital I/O           |    I2c MUX A1         |
| 33             | Digital I/O           |    I2c MUX A2         |
| 34             | Digital I/O           |       B1 (UP/NEXT)    |
| 35             | Digital I/O           |                       |
| 36             | Digital I/O           |       B3 (Back)       |
| 37             | Digital I/O           |       BLUE LED        |
| 38             | Digital I/O           |       S0              |
| 39             | Digital I/O           |        OUT            |
| 40             | Digital I/O           |         S2            |
| 41             | Digital I/O           |           S3          |
| 42             | Digital I/O           |            S1         |
| 43             | Digital I/O           |                       |
| 44             | Digital I/O, PWM      |                       |
| 45             | Digital I/O, PWM      |                       |
| 46             | Digital I/O, PWM      |                       |
| 47             | Digital I/O           |                       |
| 48             | Digital I/O           |                       |
| 49             | Digital I/O           |                       |
| 50             | Digital I/O (SPI MISO)|      Mosfet 2         |
| 51             | Digital I/O (SPI MOSI)|                       |
| 52             | Digital I/O (SPI SCK) |      Mosfet 1 (arm)        |
| 53             | Digital I/O (SPI SS)  |      RED LED          |
| A0             | Analog Input          |      Raykha A0        |
| A1             | Analog Input          |      Raykha A1        |
| A2             | Analog Input          |      Raykha A2        |
| A3             | Analog Input          |      Raykha A3        |
| A4             | Analog Input          |      Raykha A4        |
| A5             | Analog Input          |      Raykha A5        |
| A6             | Analog Input          |      Raykha A6        |
| A7             | Analog Input          |      Raykha A7        |
| A8             | Analog Input          |    MArker sensor  R   |
| A9             | Analog Input          |    MArker sensor  L   |
| A10            | Analog Input          |                       |
| A11            | Analog Input          |                       |
| A12            | Analog Input          |                       |
| A13            | Analog Input          |                       |
| A14            | Analog Input          |                       |
| A15            | Analog Input          |                       |
