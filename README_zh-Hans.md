[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver EM4100

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/em4100/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

EM4100（先前命名为H4100）是一种CMOS集成电路，用于电子只读RF转发器。该电路由放置在电磁场中的外部线圈供电，并通过其中一个线圈端子从同一场获得主时钟。通过打开和关闭调制电流，芯片将发送回包含在因子y预编程存储器阵列中的64位信息。芯片的编程是通过多晶硅链路的激光熔断来执行的，以便在每个芯片上存储唯一的代码。EM4100有多种不同的金属刻印，用于定义代码类型和数据速率。每个数据比特具有64、32和16个载波频率周期的数据速率。数据可以编码为Manchester、Biphase或PSK。由于逻辑核心的低功耗，不需要电源缓冲电容器。只需要一个外部线圈就可以获得芯片功能。芯片还集成了74pF的并联谐振电容器。

LibDriver EM4100是LibDriver推出的EM4100全功能驱动，该驱动提供ID读取等功能并且它符合MISRA标准。

本仓库包含子模块，您需要增加“--recursive”选项完整克隆整个工程。

```shell
git clone https://github.com/libdriver/em4100.git --recursive
```

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver EM4100的源文件。

/interface目录包含了LibDriver EM4100与平台无关的RF总线模板。

/test目录包含了LibDriver EM4100驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver EM4100编程范例。

/doc目录包含了LibDriver EM4100离线文档。

/datasheet目录包含了EM4100数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的RF总线模板，完成指定平台的RF总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

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

### 文档

在线文档: [https://www.libdriver.com/docs/em4100/index.html](https://www.libdriver.com/docs/em4100/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。