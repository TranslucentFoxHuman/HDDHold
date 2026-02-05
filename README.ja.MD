# HDDHold
## これは何?
このプログラムは、指定された秒数ごとにランダムなバイト数列をファイルに書き込むプログラムです。これによりハードディスクがアクセスがしばらく無かったときにスリープしたり、ヘッドがプラッタ外へ退避したりするのを防ぐことができます。頻繁なヘッドの退避やディスクの停止/始動はハードディスクの寿命を縮める原因となります。

Unixでは以下の「Unix上での実行」セクションにあるシェルスクリプトを実行するだけで十分でした。しかしWindowsには/dev/urandomのようなランダムな数値を吐き出す特殊なファイルはありません。そのためC言語で同じ事を行なうプログラムを開発しました。  
このような理由から、クロスプラットフォームですが主にWindows用に開発されています。

## ビルド方法
このコードはgccまたはclangでコンパイルできます。コードの改善により、Visual C++コンパイラでもコンパイル出来るようになりました。C89しかサポートしない非常に古いコンパイラでもコンパイルすることができます。
依存関係やMakefileなどは無いため、コンパイラにソースコードを渡すだけでビルドできます。

gccを使用する場合、WindowsでもUnixでも、以下のようなコマンドでコンパイルできます。  
Windows用のgccは[MinGW-w64](https://github.com/niXman/mingw-builds-binaries/releases)が使用できます。
```
gcc hddhold.c -O2 -o hddhold.exe
```

Visual C++を使用する場合は以下のようなコマンドでコンパイルします。
```
cl hddhold.c /Fehddhold.exe /MD /O2
```  

`/MD`および`/O2`オプションは必須ではありませんが、`/MD`を指定するとファイルサイズが非常に小さくなり、また`/O2`を指定すると実行が高速になります。このプログラムは常駐しバックグラウンドで動作するプログラムであるため、これらの指定は推奨されます。

OpenWatcomを使用する場合は以下のようにします。通常は推奨されませんが、Windows 9xのようなMinGWやVisual C++が利用出来ない非常に古い環境では使用することができます。
```
wcl386 -bcl=nt -fe=hddhold.exe hddhold.c
```

まったく役に立ちませんが、OpenWatcomを使用するとMS-DOS用にもコンパイルできます。  
MS-DOS用には常駐しませんから、MS-DOSでは本当にただのおもちゃです:)

## 使用方法
```
-b <bytes>    : Set size of random data by bytes. (default: 4)
-i <interval> : Set the interval to perform write accessin seconds. (default: 4)
-o <filename> : Set the filename to write random data. (default: C:\hddhold)
-h --help     : Print this help.
-v --version  : Print program version.
```

実行例:
```
hddhold.exe -b 4 -i 4 -o C:\hddhold.bin
```

プログラムを起動すると、指定された秒数(デフォルトでは4秒)ごとに指定されたバイト数(デフォルトでは4バイト)のランダムな数列を、指定されたファイル(デフォルトではC:\hddhold)に書き込み続けます。終了するにはターミナル上でCtrl + Cを押下するか、タクスマネージャーなどから停止シグナルを送信してください。

## Unix上での実行
このプログラムは一応はクロスプラットフォームに開発されていますが、Unix上ではこのようなプログラムをもはや実行する必要はありません。以下のようなシェルスクリプトで十分です。

```bash
#!/bin/sh
while true;do
    dd bs=1 count=4 if=/dev/urandom of=/hddhold 2> /dev/null
    sleep 4
done
```

# ライセンス
このプログラムはGNU General Public Lisence Version 3またはそれ以降のバージョンのもと提供されます。詳細はgpl-3.0.txtをご覧ください。