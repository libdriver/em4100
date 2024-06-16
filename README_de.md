[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver EM4100

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/em4100/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der EM4100 (früher H4100) ist ein CMOS-integrierter Schaltkreis für den Einsatz in elektronischen schreibgeschützten RF-Transpondern. Der Schaltkreis wird von einer externen Spule gespeist, die in einem elektromagnetischen Feld platziert ist, und erhält seinen Haupttakt von demselben Feld über einen der Spulenanschlüsse. Durch Ein- und Ausschalten des Modulationsstroms sendet der Chip die 64 Bit an Informationen zurück, die in einem vorprogrammierten Speicherarray mit Faktor y enthalten sind. Die Programmierung des Chips erfolgt durch Laserverschmelzen von Polysiliziumverbindungen, um auf jedem Chip einen eindeutigen Code zu speichern. Der EM4100 verfügt über mehrere Metalloptionen, mit denen der Codetyp und die Datenrate definiert werden. Datenraten von 64, 32 und 16 Perioden Trägerfrequenz pro Datenbit sind verfügbar. Daten können als Manchester, Biphase oder PSK codiert werden. Aufgrund des geringen Stromverbrauchs des Logikkerns ist kein Versorgungspufferkondensator erforderlich. Für die Chipfunktion ist nur eine externe Spule erforderlich. Ein Parallelresonanzkondensator von 74 pF ist ebenfalls integriert.

LibDriver EM4100 ist der voll funktionsfähige Treiber von EM4100, der von LibDriver eingeführt wurde. Er bietet die Funktion zum Lesen von IDs und andere Funktionen. LibDriver ist MISRA-kompatibel.

This repository includes submodule and you shold add "--recursive" to clone the whole project.

```shell
git clone https://github.com/libdriver/em4100.git --recursive
```

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver EM4100-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver EM4100 RF.

/test enthält den Testcode des LibDriver EM4100-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver EM4100-Beispielcode.

/doc enthält das LibDriver EM4100-Offlinedokument.

/Datenblatt enthält EM4100-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige RF-Schnittstellenvorlage und stellen Sie Ihren Plattform-RF-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/em4100/index.html](https://www.libdriver.com/docs/em4100/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.