[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver EM4100

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/em4100/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The EM4100 (previously named H4100) is a CMOS integrated circuit for use in electronic Read Only RF Transponders. The circuit is powered by an external coil placed in an electromagnetic field, and gets its master clock from the same field via one of the coil terminals. By turning on and off the modulation current, the chip will send back the 64 bits of information contained in a factor y preprogrammed memory array. The programming of the chip is performed by laser fusing of polysilicon links in order to store a unique code on each chip. The EM4100 has several metal options which are used to define the code type and data rate. Data rates of 64, 32 and 16 periods of carrier frequency per data bit are available. Data can be coded as Manchester, Biphase or PSK. Due to low power consumption of the logic core, no supply buffer capacitor is required. Only an external coil is needed to obtain the chip function. A parallel resonance capacitor of 74 pF is also integrated. 

LibDriver EM4100 is the full function driver of EM4100 launched by LibDriver.It provides the function of ID reading and other functions. LibDriver is MISRA compliant.

This repository includes submodule and you shold add "--recursive" to clone the whole project.

```shell
git clone https://github.com/libdriver/em4100.git --recursive
```
### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver EM4100 source files.

/interface includes LibDriver EM4100 RF platform independent template.

/test includes LibDriver EM4100 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver EM4100 sample code.

/doc includes LibDriver EM4100 offline document.

/datasheet includes EM4100 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface RF platform independent template and finish your platform RF driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_em4100_basic.h"

uint8_t res;
uint8_t id[5];

/* basic init */
res = em4100_basic_init();
if (res != 0)
{
    return 1;
}

...
    
/* search */
res = em4100_basic_search(id, 100);
if (res != 0)
{
    (void)em4100_basic_deinit();
    em4100_interface_debug_print("timeout.\n");

    return 1;
}

...
    
/* print */
(void)em4100_basic_print(id);

...
    
/* basic deinit */
(void)em4100_basic_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/em4100/index.html](https://www.libdriver.com/docs/em4100/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.