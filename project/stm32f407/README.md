### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

GPIO Pin: CLK/SHD/DEMOD_OUT/MOD PB0/PB2/PA8/PB1.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. MIFARE_CLASSIC

#### 3.1 Command Instruction

1. Show em4100 chip and driver information.

   ```shell
   em4100 (-i | --information)
   ```

2. Show em4100 help.

   ```shell
   em4100 (-h | --help)
   ```

3. Show em4100 pin connections of the current board.

   ```shell
   em4100 (-p | --port)
   ```

4. Run em4100 card test.

   ```shell
   em4100 (-t card | --test=card)
   ```

5. Run chip read function.

   ```shell
   em4100 (-e read | --example=read)
   ```

#### 3.2 Command Example

```shell
em4100 -i

em4100: chip is EM Microelectronic EM4100.
em4100: manufacturer is EM Microelectronic.
em4100: interface is RF.
em4100: driver version is 1.0.
em4100: min supply voltage is 1.5V.
em4100: max supply voltage is 7.5V.
em4100: max current is 10.00mA.
em4100: max temperature is 85.0C.
em4100: min temperature is -40.0C.
```

```shell
em4100 -p

em4100: CLK connected to GPIOB PIN0.
em4100: SHD connected to GPIOB PIN2.
em4100: DEMOD_OUT connected to GPIOA PIN8.
em4100: MOD connected to GPIOB PIN1.
```

```shell
em4100 -t card

em4100: chip is EM Microelectronic EM4100.
em4100: manufacturer is EM Microelectronic.
em4100: interface is RF.
em4100: driver version is 1.0.
em4100: min supply voltage is 1.5V.
em4100: max supply voltage is 7.5V.
em4100: max current is 10.00mA.
em4100: max temperature is 85.0C.
em4100: min temperature is -40.0C.
em4100: start card test.
id: 0x39 0x00 0x47 0x73 0x94.
0004682644 071, 29588.
em4100: finish card test.
```

```shell
em4100 -e read

id: 0x39 0x00 0x47 0x73 0x94.
0004682644 071, 29588.
```

```shell
em4100 -h

Usage:
  em4100 (-i | --information)
  em4100 (-h | --help)
  em4100 (-p | --port)
  em4100 (-t card | --test=card)
  em4100 (-e read | --example=read)

Options:
  -e <read>, --example=<read>   Run the driver example.
  -h, --help                    Show the help.
  -i, --information             Show the chip information.
  -p, --port                    Display the pin connections of the current board.
  -t <card>, --test=<card>      Run the driver test.
```
