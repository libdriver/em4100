[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver EM4100

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/em4100/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

EM4100 (旧称 H4100) は、電子読み取り専用 RF トランスポンダで使用する CMOS 集積回路です。この回路は、電磁場内に設置された外部コイルによって電源が供給され、コイル端子の 1 つを介して同じ場からマスター クロックを取得します。変調電流をオン/オフすることで、チップは工場出荷時にプログラムされたメモリ アレイに含まれる 64 ビットの情報を送り返します。チップのプログラミングは、各チップに固有のコードを格納するために、ポリシリコン リンクをレーザー フューズすることによって行われます。EM4100 には、コード タイプとデータ レートを定義するために使用される複数の金属オプションがあります。データ ビットあたり 64、32、および 16 キャリア周波数周期のデータ レートが利用可能です。データは、マンチェスター、バイフェーズ、または PSK としてコード化できます。ロジック コアの消費電力が低いため、電源バッファ コンデンサは必要ありません。チップ機能を得るには、外部コイルのみが必要です。74 pF の並列共振コンデンサも統合されています。

LibDriver EM4100 は、LibDriver がリリースした EM4100 のフル機能ドライバです。ID 読み取り機能やその他の機能を提供します。LibDriver は MISRA に準拠しています。

このリポジトリにはサブモジュールが含まれており、「--recursive」を追加してプロジェクト全体を複製する必要があります。

```shell
git clone https://github.com/libdriver/em4100.git --recursive
```

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver EM4100のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver EM4100用のプラットフォームに依存しないRFバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver EM4100ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver EM4100プログラミング例が含まれています。

/ docディレクトリには、LibDriver EM4100オフラインドキュメントが含まれています。

/ datasheetディレクトリには、EM4100データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないRFバステンプレートを参照して、指定したプラットフォームのRFバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/em4100/index.html](https://www.libdriver.com/docs/em4100/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。