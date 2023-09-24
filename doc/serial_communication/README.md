# シリアル通信

通信のバイナリ構造は[NX Macro Controller](https://blog.bzl-web.com/entry/2020/01/20/165719)の方式[^7]に準拠します。パッド座標は左上起点で、ニュートラルポジションは128です。右パッドは将来の更新のために予約されています。

Switchのキーボード操作に使用されている末尾3バイトをタッチスクリーン操作に割り当てます。タッチ入力座標は左上起点で1 <= x <= 320、1 <= y <= 240の値を受け付けます。いずれかが範囲外の場合、タッチ入力を解除します。

| Index | Value                     |
| ----- | ------------------------- |
| 0     | 0xAB                      |
| 1     | Button lower              |
| 2     | Button upper              |
| 3     | Hat                       |
| 4     | Left pad X-axis           |
| 5     | Left pad Y-axis           |
| 6     | (Right pad X-axis)        |
| 7     | (Right pad Y-axis)        |
| 8     | Touch screen X-axis lower |
| 9     | Touch screen X-axis upper |
| 10    | Touch screen Y-axis       |

ボタンは各ビットについて0を解放、1を押下とします。ZLとZRは将来の更新のために予約されています。対応するボタンが存在しないL ClickとR Clickには、電源とWi-Fi切替を割り当てています。

| Button (NXMC)     | Bit mask              |
| ----------------- | --------------------- |
| Y                 | 0b0000'0000'0000'0001 |
| B                 | 0b0000'0000'0000'0010 |
| A                 | 0b0000'0000'0000'0100 |
| X                 | 0b0000'0000'0000'1000 |
| L                 | 0b0000'0000'0001'0000 |
| R                 | 0b0000'0000'0010'0000 |
| (ZL)              | 0b0000'0000'0100'0000 |
| (ZR)              | 0b0000'0000'1000'0000 |
| (-) → Select      | 0b0000'0001'0000'0000 |
| (+) → Start       | 0b0000'0010'0000'0000 |
| (L Click) → Power | 0b0000'0100'0000'0000 |
| (R Click) → Wi-Fi | 0b0000'1000'0000'0000 |
| Home              | 0b0001'0000'0000'0000 |
| (Capture)         | 0b0010'0000'0000'0000 |

ハットの各方向の実体はボタンですが、押し方の組み合わせは機構上制限されています。

| Hat | Value |
| --- | ----- |
| ↑   | 0     |
| ↗   | 1     |
| →   | 2     |
| ↘   | 3     |
| ↓   | 4     |
| ↙   | 5     |
| ←   | 6     |
| ↖   | 7     |
| x   | 8     |

[^7]: https://scrapbox.io/yatsuna827827-12010999/Nintendo_Switch%E3%82%92%E6%93%8D%E4%BD%9C%E3%81%99%E3%82%8B%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%A0%E3%81%AE%E4%BB%95%E6%A7%98%E3%82%92%E8%AA%BF%E3%81%B9%E3%82%8B