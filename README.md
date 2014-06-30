# Groonga regex function plugin
Groongaに出力結果を整形する正規表現の関数を追加します。

## 関数
### regex_extract

指定したカラムの文字列から正規表現のパターンに一致する文字列を抽出します。

* 実行例

```
>select Entries --output_columns 'regex_extract(title, " (.*) ", "<extract>\\\\1</extract>")' --command_version 2
[[0,0.0,0.0],[[[1],[["regex_extract","Object"]],["<extract>and</extract>"]]]]
```

* 入力形式

| arg        | description |
|:-----------|:------------|
| 1     | カラムを指定 |
| 2     | 抽出する正規表現パターン | 
| 3   | 出力パターン(省略時は1つ目にマッチした文字列) |

* 出力形式  
パターンにマッチするものがあれば、出力パターンに沿った文字列が出力されます。  
パターンにマッチするものがなければ、入力したカラムの文字列が出力されます。


### regex_replace

指定したカラムの文字列から正規表現のパターンに一致する文字列を全置換します。

* 実行例

```
>select Entries --output_columns 'regex_replace(title, " (.*) ", " or ")' --command_version 2
[[0,0.0,0.0],[[[1],[["regex_replace","Object"]],["groonga or MySQL"]]]]
```

* 入力形式

| arg        | description |
|:-----------|:------------|
| 1     | カラムを指定 |
| 2     | 抽出する正規表現パターン | 
| 3   | 置換する文字列 |

* 出力形式  
置換された文字列が出力されます。  


## インストール
本プラグインは、Groongaの4.0.3以降のバージョンが必要です。

本プラグインは、RE2ライブラリを利用しています。あらかじめ、これらのライブラリをインストールしてください。CentOSであれば、yumのepelリポジトリでインストールすることができます。

    % yum -y install re2 re2-devel

プラグインをビルドしてインストールしてください。

    % sh autogen.sh
    % ./configure
    % make
    % sudo make install

Groongaのプラグインは共有ライブラリのため、ライブラリパスに注意してください。

## 使い方

Groongaのデータベースに``functions/regex``プラグインを登録してください。データベースごとにこの作業が1回だけ必要です。

    % groonga DB
    > register functions/regex

これにより、Groongaのデータベースに上記の関数が登録されて、上記の関数が利用できるようになります。

## Author

Naoya Murakami naoya@createfield.com

## License

LGPL 2.1. See COPYING-LGPL-2.1 for details.

