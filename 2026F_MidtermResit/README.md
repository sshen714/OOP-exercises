# OOP2026[F] Midterm Exam Resit

## 檔案架構
你的檔案架構必須至少符合以下的規格，才可以讓系統編譯你的專案。
```
.
│   CMakeLists.txt
│   files.cmake
├── README.md
├── include
│   ├── BackGingerbreadMan.hpp
│   ├── BurningSpiceCookie.hpp
│   ├── Character.hpp
│   ├── ChiliPepperCookie.hpp
│   ├── CrimsonCoralCookie.hpp
│   ├── FireSpiritCookie.hpp
│   ├── FrontGingerbreadMan.hpp
│   ├── GingerbreadGroup.hpp
│   ├── GingerbreadMan.hpp
│   ├── MiddleGingerbreadMan.hpp
│   ├── MillennialTreeCookie.hpp
│   ├── SeaFairyCookie.hpp
│   ├── SeltzerCookie.hpp
│   ├── SilverbellCookie.hpp
│   └── WhiteLilyCookie.hpp
├── src
│   ├── BackGingerbreadMan.cpp
│   ├── BurningSpiceCookie.cpp
│   ├── Character.cpp
│   ├── ChiliPepperCookie.cpp
│   ├── CrimsonCoralCookie.cpp
│   ├── FireSpiritCookie.cpp
│   ├── FrontGingerbreadMan.cpp
│   ├── GingerbreadGroup.cpp
│   ├── GingerbreadMan.cpp
│   ├── MiddleGingerbreadMan.cpp
│   ├── MillennialTreeCookie.cpp
│   ├── SeaFairyCookie.cpp
│   ├── SeltzerCookie.cpp
│   ├── SilverbellCookie.cpp
│   └── WhiteLilyCookie.cpp
└── test
    ├── ut_character.cpp
    ├── ut_fire_cookies.cpp
    ├── ut_gingerbread_group.cpp
    ├── ut_gingerbread_man.cpp
    ├── ut_plant_cookies.cpp
    ├── ut_positional_gingerbread_man.cpp
    └── ut_water_cookies.cpp
```

## 題目情境
現在的你嘗試寫出一款薑餅人遊戲，腦海充斥著各式各樣的角色和機制，而絞盡了腦汁後最終打算從最基本的結構開始逐步完成它。你興致勃勃的開始向自己解釋你的需求，戰鬥開始前，玩家可以將自己的薑餅人角色放入隊伍裡，但不同的薑餅人定位都不一樣，有設計站在前面當坦克的角色、也有站中間的輸出、站在後排的法師，分別針對對應位置進行攻擊。然而戰鬥開始時，薑餅人會開始一窩蜂地向前衝，當前排的薑餅死掉後，後面的薑餅將往前替補，直到所有薑餅都死亡才算輸，也正因為這個規則，你設計了排序方式以便讓系統知道玩家希望讓血量、攻擊還是防禦高的薑餅先往前一排衝，玩家的戰略就是抓準時機以系統累積的經驗值幫角色升級同時修復血量以達成勝利。

## 目標一、設計角色類別
`Character` 是角色的抽象基底類別，用於簡化後續類別的實作，薑餅人會繼承該類別，同時也方便未來擴展敵人。
- 成員變數
  - `name`：名稱。
  - `level`：等級，預設為 `1`。
  - `damage`：攻擊力。
  - `defense`：防禦力。
  - `health`：最大生命值（生命值上限）。
  - `currHealth`：目前的生命值，預設等於 `health`。
  - `maxCritCount`：爆擊週期。
  - `maxDodgeCount`：閃避週期。
  - `critCount`：目前的爆擊週期計數，初始為 `0`。
  - `dodgeCount`：目前的閃避週期計數，初始為 `0`。
- 成員函式
  - `Character(std::string name, int damage, int defense, int health, int maxCritCount, int maxDodgeCount)`
    - 按照上述描述對所有成員變數初始化。
  - `virtual void levelUp() = 0`
    - 用來升級角色，留給後續實作。
  - `virtual bool onHit(int incomingDamage) = 0`
    - 當角色受擊時呼叫，留給後續實作。
  - `bool isCriticalHit()`
    - 用來判斷當前攻擊有沒有爆擊
    - 每呼叫該函式時，使 `critCount` + 1
      - 每累計到 `maxCritCount` 次即觸發爆擊，回傳 `true` 並將 `critCount` 重置為 `0`
      - 反之，回傳 `false`。
  - `bool isDodged()`
    - 用來判斷角色有沒有迴避
    - 每呼叫該函式時，使 `dodgeCount` + 1
      - 每累計到 `maxDodgeCount` 次即觸發閃避，回傳 `true` 並將 `dodgeCount` 重置為 `0`
      - 反之，回傳 `false`。
  - `std::string getName() const`
    - 直接回傳 `name`。
  - `int getLevel() const`
    - 直接回傳 `level`。
  - `int getDamage() const`
    - 直接回傳 `damage`。
  - `int getDefense() const`
    - 直接回傳 `defense`。
  - `int getHealth() const`
    - 直接回傳 `health`。
  - `int getCurrHealth() const`
    - 直接回傳 `currHealth`。
  - `int getMaxCritCount() const`
    - 直接回傳 `maxCritCount`。
  - `int getMaxDodgeCount() const`
    - 直接回傳 `maxDodgeCount`。

## 目標二、設計薑餅人類別
`GingerbreadMan` 繼承 `Character`，用於實作薑餅人共用的元素、升級、攻擊及受擊行為。
- `type`：元素屬性。
- `pos`：戰鬥位置。
- `critDamage`：爆擊時增加的傷害比例。
- `GingerbreadMan(std::string name, Element type, Position pos, int damage, int defense, int health, float critDamage, int maxCritCount, int maxDodgeCount)`
  - 設定薑餅人的元素、位置、爆擊傷害比例，其餘參數使用 `Character` 初始化。
- `void levelUp()`
  - 用來升級角色時呼叫
  - 將 `level` 加 `1`
  - 將 `damage` 加 `100`
  - 將 `defense` 加 `100`
  - 將`health` 加 `100`
  - 最後將 `currHealth` 設為升級後的 `health`。
- `int attack(Element enemyType)`
  - 攻擊時呼叫，傳入對方的元素屬性，計算攻擊傷害
  - 根據 `isCriticalHit()`，如果爆擊則在下一步公式計算時考慮 `critDamage`，若無爆擊則不考慮（計算時 `critDamage` 的位置以 `0` 代替）
  - 回傳 `(1 + critDamage + elementalAttack(enemyType)) * damage`。
- `bool onHit(int incomingDamage)`
  - 計算被攻擊的傷害，並降低該薑餅人血量
  - 先呼叫 `isDodged()`，判斷是否閃避，若閃避則免疫所有傷害（不扣 `currHealth`）
  - 計算造成的傷害 `incomingDamage - defense`，若小於或等於 `0`， `currHealth` 也不扣除傷害，反之，若大於 `0`，`currHealth` 必須扣除傷害
  - 透過以上的計算與判斷，若未扣除當前生命值 `currHealth`，則回傳 `true`
  - 透過以上的計算與判斷，若已扣除當前生命值 `currHealth`，則回傳 `false`。
- `std::vector<Position> getInteractPositions() const`
  - 依照該角色位置 `pos` 回傳可攻擊的敵方位置
  - 若為 `Front` 回傳 `Front`
  - 若為 `Middle` 回傳 `Front`、`Middle`
  - 若為 `Back` 回傳 `Middle`、`Back`。
- `Position getPosition() const`
  - 直接回傳 `pos`。
- `Element getElementType() const`
  - 直接回傳 `type`。
- `float getCritDamage() const`
  - 直接回傳 `critDamage`。
- `float elementalAttack(Element enemyType)`
  - 傳入對方的元素屬性，確認本薑餅人是否對該屬性克制（造成額外傷害），回傳額外傷害倍率
  - 若本薑餅人 `type` 為 `Water` 且 `enemyType` 為 `Fire` 時，回傳 `0.7`
  - 若本薑餅人 `type` 為 `Fire` 且 `enemyType` 為 `Plant` 時，回傳 `1.0`
  - 若本薑餅人 `type` 為 `Plant` 且 `enemyType` 為 `Water` 時，回傳 `0.5`
  - 若本薑餅人 `type` 與 `enemyType` 為其他元素組合，回傳 `0`。

## 目標三、設計有位置的薑餅人類別
`FrontGingerbreadMan`、`MiddleGingerbreadMan`、`BackGingerbreadMan` 皆繼承 `GingerbreadMan`，對應站在前排的薑餅人、站在中排的薑餅人、站在後排的薑餅人。

### 站在前排的薑餅人
- `FrontGingerbreadMan(std::string name, Element type, int damage, int defense, int health, float critDamage = 0.5, int maxCritCount = 3, int maxDodgeCount = 5)`
  - 使用 `GingerbreadMan` 初始化參數，其中 `pos` 為 `Front`
- `defenseBuff()`
  - 實作未來可能在各個地方呼叫的 Buff
  - 若薑餅人的 `defense` 大於自己的 `damage` 時，使 `defense` 乘上`1.1`。

### 站在中排的薑餅人
- `MiddleGingerbreadMan(std::string name, Element type, int damage, int defense, int health, float critDamage = 0.5, int maxCritCount = 3, int maxDodgeCount = 5)`
  - 使用 `GingerbreadMan` 初始化參數，其中 `pos` 為 `Middle`
- `criticalBuff()`
  - 實作未來可能在各個地方呼叫的 Buff
  - 若薑餅人的 `critDamage` 小於 `1.0` 時，則 `critDamage` 加 `0.1`。

### 站在後排的薑餅人
- `BackGingerbreadMan(std::string name, Element type, int damage, int defense, int health, float critDamage = 0.5, int maxCritCount = 3, int maxDodgeCount = 5)`
  - 使用 `GingerbreadMan` 初始化參數，其中 `pos` 為 `Back`
- `keepHealingBuff()`
  - 實作未來可能在各個地方呼叫的 Buff
  - 若薑餅人的 `health` 大於 `currHealth` 時，則 `currHealth` 加 `1`。

## 目標四、設計餅乾類別
接著我們有九種餅乾，皆繼承對應位置的薑餅人類別，各餅乾須設定初始屬性，並依規格覆寫升級、攻擊或受擊行為，請依照[薑餅人清單](#薑餅人清單)完成實作。

在開始查閱清單之前，請詳閱以下規則：
- 數值未寫的部分為預設值。
- 如同目標一與目標二，`levelUp()` 於升級角色時呼叫
  - 將 `level` 加 `1`
  - 計算成長數值，請參考**清單上所列之計算公式**，若無則不須複寫。
  - 最後將 `currHealth` 設為升級後的 `health`。
- 如同目標一與目標二，`attack(Element enemyType)` 於攻擊時呼叫，傳入對方的元素屬性，計算攻擊傷害
  - 根據 `isCriticalHit()`，如果爆擊則在下一步公式計算時考慮 `critDamage`，若無爆擊則不考慮（計算時 `critDamage` 的位置以 `0` 代替）
  - 計算結果轉為 int ，採用無條件捨去
  - 回傳傷害，請參考**清單上所列之計算公式**，若無則不須複寫。
- 如同目標一與目標二，`onHit(int incomingDamage)` 於被攻擊時呼叫，計算被攻擊的傷害，並降低該薑餅人血量
  - 先呼叫 `isDodged()`，判斷是否閃避，若閃避則免疫所有傷害（不扣 `currHealth`）
  - 計算造成的傷害，請參考**清單上所列之計算公式**，若無則不須複寫
  - 計算結果轉為 int ，採用無條件捨去
  - 計算後若小於或等於 `0`，`currHealth` 也不扣除傷害
  - 透過以上的計算與判斷，若未扣除當前生命值 `currHealth`，則回傳 `true`
  - 透過以上的計算與判斷，若已扣除當前生命值 `currHealth`，則回傳 `false`。

### 薑餅人清單

#### 千年古樹餅乾 `MillennialTreeCookie` 
![Millennial Tree Cookie](./doc/MTC.png) 
- 繼承 `FrontGingerbreadMan`。
- `name`：`Millennial Tree Cookie`。
- `type`：`Plant`。
- `damage`：`200`。
- `defense`：`150`。
- `health`：`1000`。
- `levelUp`：`damage`、`defense`、`health` 各加 `150`。
- `attack`：`(1 + critDamage + (1.0 * currHealth) / health + elementalAttack(enemyType)) * damage + 25`。
- `onHit`：`incomingDamage - defense * (1 + (1.0 * currHealth / health))`，無論閃避與否皆呼叫 `defenseBuff()`。

#### 聖百合餅乾 `WhiteLilyCookie`
![White Lily Cookie](./doc/WLC.png)
- 繼承 `MiddleGingerbreadMan`。
- `name`：`White Lily Cookie`。
- `type`：`Plant`。
- `damage`：`100`。
- `defense`：`100`。
- `health`：`1500`。
- `critDamage`：`0.2`。
- `maxCritCount`：`2`。
- `attack`：`(1 + critDamage + elementalAttack(enemyType)) * damage + critDamage * currHealth`。
- `onHit`：`incomingDamage - (defense + damage)`，無論閃避與否皆呼叫 `criticalBuff()`。

#### 風鈴草餅乾 `SilverbellCookie`
![Silverbell Cookie](./doc/SC.png)

- 繼承 `BackGingerbreadMan`。
- `name`：`Silverbell Cookie`。
- `type`：`Plant`。
- `damage`：`200`。
- `defense`：`150`。
- `health`：`900`。
- `critDamage`：`0.8`。
- `maxCritCount`：`3`。
- `maxDodgeCount`：`8`。
- `levelUp`：`damage` 加 `150`，`defense` 加 `50`，`health` 加 `150`，回滿血後呼叫 `keepHealingBuff()`。
- `onHit`：`incomingDamage - defense * (1 + level / 100.0)`。

#### 烈焰香料餅乾 `BurningSpiceCookie`
![Burning Spice Cookie](./doc/BSC.png)

- 繼承 `FrontGingerbreadMan`。
- `name`：`Burning Spice Cookie`。
- `type`：`Fire`。
- `damage`：`200`。
- `defense`：`80`。
- `health`：`1000`。
- `levelUp`：`damage` 加 `250`，`critDamage` 加 `0.05`，`health` 加 `220`。
- `attack`：`(1 + critDamage + elementalAttack(enemyType)) * (damage + 25)`。

#### 甜辣醬餅乾 `ChiliPepperCookie`
![Chili Pepper Cookie](./doc/CPC.png)

- 繼承 `MiddleGingerbreadMan`。
- `name`：`Chili Pepper Cookie`。
- `type`：`Fire`。
- `damage`：`200`。
- `defense`：`100`。
- `health`：`900`。
- `critDamage`：`0.8`。
- `maxCritCount`：`7`。
- `maxDodgeCount`：`4`。
- `levelUp`：`damage` 加 `200`，`defense` 加 `100`，`health` 加 `100`，回滿血後呼叫 `criticalBuff()`。
- `attack`：`(1 + critDamage + (1.0 * currHealth / health) + elementalAttack(enemyType)) * damage`。

#### 火精靈餅乾 `FireSpiritCookie`
![FireSpiritCookie](./doc/FSC.png)

- 繼承 `BackGingerbreadMan`。
- `name`：`Fire Spirit Cookie`。
- `type`：`Fire`。
- `damage`：`500`。
- `defense`：`20`。
- `health`：`200`。
- `critDamage`：`0.5`。
- `maxCritCount`：`2`。
- `maxDodgeCount`：`7`。
- `levelUp`：`damage` 加 `100`，`critDamage` 加 `0.1`，`health` 加 `20`、`defense` 加 `5`，回滿血後呼叫 `keepHealingBuff()`。

#### 緋紅珊瑚餅乾 `CrimsonCoralCookie`
![CrimsonCoralCookie](./doc/CCC.png)

- 繼承 `FrontGingerbreadMan`。
- `name`：`Crimson Coral Cookie`。
- `type`：`Water`。
- `damage`：`250`。
- `defense`：`500`。
- `health`：`100`。
- `critDamage`：`0.5`。
- `maxCritCount`：`5`。
- `maxDodgeCount`：`10`。
- `attack`：`(1 + critDamage + elementalAttack(enemyType)) * damage + defense + health`，計算完後呼叫 `defenseBuff()`。

#### 海妖精餅乾 `SeaFairyCookie`
![SeaFairyCookie](./doc/SFC.png)

- 繼承 `MiddleGingerbreadMan`。
- `name`：`Sea Fairy Cookie`。
- `type`：`Water`。
- `damage`：`200`。
- `defense`：`300`。
- `health`：`1000`。
- `critDamage`：`0.3`。
- `levelUp`：`damage` 加 `100`，`defense` 加 `150`，`health` 加 `160`，若 `maxCritCount` 大於 `1` 則減去 `1`，並將 `critCount` 歸零，回滿血後呼叫 `criticalBuff()`。
- `attack`：`(1 + critDamage + elementalAttack(enemyType)) * damage + critDamage * defense`。

#### 氣泡水餅乾 `SeltzerCookie`
![SeltzerCookie](./doc/SeC.png)

- 繼承 `BackGingerbreadMan`。
- `name`：`Seltzer Cookie`。
- `type`：`Water`。
- `damage`：`200`。
- `defense`：`450`。
- `health`：`700`。
- `critDamage`：`0.7`。
- `maxCritCount`：`2`。
- `maxDodgeCount`：`3`。
- `onHit`：`incomingDamage - defense * (1 + level / 100.0)`，無論閃避與否皆呼叫 `keepHealingBuff()`。

## 目標五、設計薑餅人隊伍類別
`GingerbreadGroup` 管理隊伍成員，提供成員新增、替換、排序、移除及戰鬥操作。

- 成員變數
  - `queue`：以 `std::vector<std::shared_ptr<GingerbreadMan>>` 保存隊伍成員。
  - `maxSize`：隊伍容量上限。
  - `currIndex`：下一次執行攻擊的隊員索引。
- 成員函式
  - `GingerbreadGroup(int maxSize)`
    - `maxSize` 小於 `3` 或大於 `9` 時，拋出 `std::invalid_argument`
    - `currIndex` 初始化為 `0`。
  - `std::vector<int> attack(std::vector<Element>& types)`
    - 攻擊時回傳與 `types` 長度（敵人隊伍長度）等長的傷害 vector
    - `types` 本身即告訴我們敵人餅乾的位置與他們的元素
    - 建立初始化為 `0` 的 vector 作為傷害統計的容器
    - 更新以確保 `currIndex` 介於 `0`（含）至 `queue.size()`（不含）的區間；若隊伍為空，回傳全為 `0` 的傷害 vector。
    - 紀錄 `queue[currIndex]` 作為**攻擊者**，遍歷攻擊所有 `types` 資訊的傷害，請參照以下規則：
      - 當 `types.size()` 小於 `3` 時，每位攻擊者皆可攻擊所有敵人，不進行位置區分
      - 否則敵人所在位置將被切成前、中、後，分別對應 `Position::Front`、`Position::Middle`、`Position::Back`
      - 當該敵人索引小於 `types.size()/3` 時，代表該敵人的位置為 `Position::Front`
      - 當該敵人索引大於等於 `types.size()/3` 且小於 `(types.size()/3)*2` 時，代表該敵人的位置為 `Position::Middle`
      - 當該敵人索引大於等於 `(types.size()/3)*2` 時，代表該敵人的位置為 `Position::Back`
      - 接著我們需要確認這位**攻擊者**是否能攻擊到該敵人，詳情請參照目標二的 `getInteractPositions()`
      - 如果該敵人剛好在攻擊者可以攻擊到的範圍中，則在傷害統計中與該敵人相同索引下計錄攻擊者 `attack(type)` 的數字
      - 如果該敵人未在攻擊者可以攻擊到的範圍中，則在傷害統計中與該敵人相同索引下保持數字 `0`
      - 最後請讓 `currIndex` 加 `1` 並確保隊伍非空時索引落在 `0`（含）至 `queue.size()`（不含）的區間（若輪完一遍則從頭繼續）
      - 回傳傷害統計的結果。
  - `void onHit(std::vector<int>& damages)`
    - `damages` 是敵人攻擊我方角色所造成的傷害，每個傷害的索引都對應著 `queue` 中薑餅人的索引
    - 當 `damages` 長度與目前隊伍人數不符時，直接拋出 `std::invalid_argument`
    - 遍歷 `queue` 中所有薑餅人，並依序將傷害傳給每位隊員的 `onHit(inputDamage)`
    - 最後呼叫 `removeDeadGingerbreadMan`，移除生命值小於等於 `0` 的薑餅人。

  - `void addGingerbreadMan(std::shared_ptr<GingerbreadMan> gingerbreadMan)`
    - 當要加入薑餅人進入隊伍裡時呼叫
    - 若 `gingerbreadMan` 為空指標，拋出 `std::invalid_argument`
    - 若與 `queue` 中任何成員名稱重複，拋出 `std::invalid_argument`
    - 若與 `queue` 中該位置（`Position`）超過容量，拋出 `std::invalid_argument`，關於位置的計算請參考：
      - 請根據所有薑餅人的 `pos` 統計目前的 `Position::Front`、`Position::Middle`、`Position::Back` 各有多少數量
      - 判斷加入 `gingerbreadMan` （加入統計他的 `pos`）新的薑餅人時，是否符合以下條件：
        - `Position::Front` 數量應該要小於等於 `maxSize / 3`
        - `Position::Middle` 數量應該要小於等於 `maxSize / 3`
        - `Position::Back` 數量應該要小於等於 `maxSize - 2 * (maxSize / 3)`
    - 通過檢查後，將 `gingerbreadMan` 加入 `queue` 的尾端。

  - `void replaceGingerbreadMan(int index, std::shared_ptr<GingerbreadMan> gingerbreadMan)`
    - 當希望換掉薑餅人時可以呼叫此函式，
    - 若 `index` 小於 `0` 或是大於等於 `queue.size()`，拋出 `std::out_of_range`
    - 若 `gingerbreadMan` 為空指標，拋出 `std::invalid_argument`
    - 若與 `queue` 中除被取代成員以外的其他成員名稱重複，拋出 `std::invalid_argument`
    - `gingerbreadMan` 的位置（`pos`）須與被取代的薑餅人相同，否則拋出 `std::invalid_argument`
    - 判斷結束後直接以 `gingerbreadMan` 取代被取代的薑餅人。

  - `void sortByHealth()`
    - 將 `queue` 中的薑餅人由大到小依據 `health` 排序
    - 數值相同時維持原有相對順序；排序不會改變成員的 `Position`。

  - `void sortByDamage()`
    - 將 `queue` 中的薑餅人由大到小依據 `damage` 排序
    - 數值相同時維持原有相對順序；排序不會改變成員的 `Position`。

  - `void sortByDefense()`
    - 將 `queue` 中的薑餅人由大到小依據 `defense` 排序
    - 數值相同時維持原有相對順序；排序不會改變成員的 `Position`。

  - `int countCombatPower()`
    - 回傳所有隊員的 `health`、`defense`、`damage` 總和。

  - `void removeDeadGingerbreadMan()`
    - 移除已經死掉的薑餅人 QQ
    - 遍歷檢查 `queue` 中所有薑餅人，若該薑餅人 `currHealth <= 0` 則將他移除
    - 若原本的下一位攻擊者仍留在隊伍中，調整索引使其繼續指向該隊員。
    - 若原本的下一位攻擊者被移除，則由其後第一位仍在隊伍中的隊員接替；若已到隊伍尾端則從頭循環尋找。
    - 若隊伍為空，將 `currIndex` 設為 `0`；否則確保索引落在有效範圍內。

  - `void removeGingerbreadMan(std::string name)`
    - 移除名稱相符的薑餅人
    - 遍歷檢查 `queue` 中所有薑餅人，若該薑餅人的名稱剛好等於 `name` 則將他移除
    - 若原本的下一位攻擊者仍留在隊伍中，調整索引使其繼續指向該隊員。
    - 若原本的下一位攻擊者被移除，則由其後第一位仍在隊伍中的隊員接替；若已到隊伍尾端則從頭循環尋找。
    - 若隊伍為空，將 `currIndex` 設為 `0`；否則確保索引落在有效範圍內。

  - `void removeGingerbreadMan(Element element)`
    - 移除所有元素相符的薑餅人
    - 遍歷檢查 `queue` 中所有薑餅人，若該薑餅人的元素剛好等於 `element` 則將他移除
    - 若原本的下一位攻擊者仍留在隊伍中，調整索引使其繼續指向該隊員。
    - 若原本的下一位攻擊者被移除，則由其後第一位仍在隊伍中的隊員接替；若已到隊伍尾端則從頭循環尋找。
    - 若隊伍為空，將 `currIndex` 設為 `0`；否則確保索引落在有效範圍內。

  - `std::shared_ptr<GingerbreadMan> getGingerbreadMan(int index)`
    - 回傳指定索引的薑餅人
    - 當 `index` 小於 `0` 或大於等於 `queue.size()` 時，拋出 `std::out_of_range`
    - 否則直接回傳 `queue` 中該位置的薑餅人。 

## 測試範圍與分數分配
測試程式分布於以下檔案：
- `test/ut_character.cpp`（10%）：測試目標一的所有實作。
- `test/ut_gingerbread_man.cpp`（15%）：測試目標二的所有實作。
- `test/ut_positional_gingerbread_man.cpp`（5%）：測試目標三的所有實作。
- `test/ut_fire_cookies.cpp`（15%）：測試部分目標四的火屬性餅乾實作。
- `test/ut_water_cookies.cpp`（15%）：測試部分目標四的水屬性餅乾實作。
- `test/ut_plant_cookies.cpp`（15%）：測試部分目標四的植物屬性餅乾實作。
- `test/ut_gingerbread_group.cpp`（25%）：測試目標五，`GingerbreadGroup` 的所有實作。

## 備註
- 可以依需求使用 `virtual`、純虛擬函式，以及新增 `private` 或 `protected` 成員與函式。
- `sort` 和 `exception` 的用法可參考 [cppreference](https://cppreference.com/) 或先前的作業。
