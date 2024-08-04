[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver EM4100

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/em4100/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

EM4100（先前命名為H4100）是一種CMOS集成電路，用於電子只讀RF轉發器。 該電路由放置在電磁場中的外部線圈供電，並通過其中一個線圈端子從同一場獲得主時鐘。 通過打開和關閉調製電流，晶片將發送回包含在因數y預程式設計記憶體陣列中的64比特資訊。 晶片的程式設計是通過多晶矽連結的雷射熔斷來執行的，以便在每個晶片上存儲唯一的程式碼。 EM4100有多種不同的金屬刻印，用於定義程式碼類型和資料速率。 每個數據比特具有64、32和16個載波頻率週期的資料速率。 數據可以編碼為Manchester、Biphase或PSK。 由於邏輯覈心的低功耗，不需要電源緩衝電容器。 只需要一個外部線圈就可以獲得晶片功能。 晶片還集成了74pF的並聯諧振電容器。

LibDriver EM4100是LibDriver推出的EM4100全功能驅動，該驅動提供ID讀取等功能並且它符合MISRA標準。

本倉庫包含子模塊，您需要增加“--recursive”選項完整克隆整個工程。

```shell
git clone https://github.com/libdriver/em4100.git --recursive
```

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver EM4100的源文件。

/interface目錄包含了LibDriver EM4100與平台無關的RF總線模板。

/test目錄包含了LibDriver EM4100驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver EM4100編程範例。

/doc目錄包含了LibDriver EM4100離線文檔。

/datasheet目錄包含了EM4100數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的RF總線模板，完成指定平台的RF總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/em4100/index.html](https://www.libdriver.com/docs/em4100/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。
