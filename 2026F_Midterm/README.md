# OOP2026[F] Midterm Exam

## 檔案架構
你的檔案架構必須至少符合以下的規格，才可以讓系統編譯你的專案。
```
.
│   CMakeLists.txt
│   files.cmake
├── README.md
├── doc
│   ├── BSC.png
│   ├── CCC.png
│   ├── CPC.png
│   ├── FSC.png
│   ├── MTC.png
│   ├── SC.png
│   ├── SeC.png
│   ├── SFC.png
│   └── WLC.png
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
│   ├── BurningSpiceCookie.cpp
│   ├── Character.cpp
│   ├── ChiliPepperCookie.cpp
│   ├── CrimsonCoralCookie.cpp
│   ├── FireSpiritCookie.cpp
│   ├── GingerbreadGroup.cpp
│   ├── GingerbreadMan.cpp
│   ├── MillennialTreeCookie.cpp
│   ├── SeaFairyCookie.cpp
│   ├── SeltzerCookie.cpp
│   ├── SilverbellCookie.cpp
│   └── WhiteLilyCookie.cpp
└── test
    ├── ut_cookies.cpp
    ├── ut_gingerbread_group.cpp
    └── ut_gingerbread_man.cpp
```

## 題目情境
現在的你嘗試寫出一款薑餅人遊戲，腦海充斥著各式各樣的角色和機制，而絞盡了腦汁後最終打算從最基本的結構開始逐步完成它。你興致勃勃的開始向自己解釋你的需求：戰鬥開始前，玩家可以將自己的薑餅人角色放入隊伍裡，但不同的薑餅人定位都不一樣，有設計站在前面當坦克的角色、也有站中間的輸出、站在後排的法師，分別針對對應位置進行攻擊。然而戰鬥開始時，薑餅人會開始一窩蜂地向前衝，當前排的薑餅死掉後，後面的薑餅將往前替補，直到所有薑餅都死亡才算輸，也正因為這個規則，你設計了三種不同排序方式以便讓系統知道玩家希望讓血量、攻擊還是防禦高的薑餅先往前一排衝，玩家的戰略就是抓準時機以系統累積的經驗值幫角色升級同時修復血量以達成勝利。

## 目標一、設計角色類別
`Character` 是角色的抽象基底類別，用於簡化後續類別的實作，同時也方便擴展未來敵人。在這裡 `GingerbreadMan` 繼承 `Character`。
- `name`：角色名稱。
- `level`：等級，預設為 `1`。
- `damage`、`defense`、`health`：攻擊力、防禦力及最大生命值。
- `currHealth`：目前生命值，預設等於 `health`。
- `critTime`、`avoidTime`：爆擊及閃避的週期。
- `currCritTime`、`currAvoidTime`：目前週期計數，初始為 `0`。
- ` Character(std::string name, int damage, int defense, int health, int critTime, int avoidTime)`
  - 初始化等級、生命值、爆擊次數、閃避次數、爆擊計數、閃避計數
- `virtual void levelUp() = 0`、`virtual bool attacked(int incomingDamage) = 0`
  - 留給後續實作
- `bool countCritTime()`
  - 每呼叫該函式時，使 `currCritTime` + 1，計數到 `critTime` 則回傳 `true` 並重置 `currCritTime`。
- `bool countAvoidTime()` 使 `currAvoidTime` + 1，計數到 `avoidTime` 則回傳 `true` 並重置 `currAvoidTime`。

## 目標二、設計薑餅人類別
`GingerbreadMan` 繼承 `Character`，用於實作薑餅人共用的元素、位置、攻擊及受擊行為。
- `type`：薑餅人的元素屬性。
- `pos`：薑餅人的戰鬥位置。
- `critDamage`：爆擊時增加的傷害比例。
- `GingerbreadMan(std::string name, Element type, Position pos, int damage, int defense, int health, float critDamage, int critTime, int avoidTime)`
  - 設定薑餅人的元素、位置、爆擊傷害比例，並使用 `Character` 初始化共用狀態。
- `levelUp()`
  - 將 `level` 加 `1`。
  - 將 `damage`、`defense`、`health` 各加 `100`。
  - 將 `currHealth` 設為升級後的 `health`。
  - 回傳 `(1 + crit) * damage`。
- `attack(Element enemyType)`
  - 呼叫一次 `countCritTime()`，並依照爆擊結果設定 `crit`。
  - 回傳 `(1 + crit + elementalAttack(enemyType)) * damage`。
- `elementalAttack(Element enemyType)`
  - Water 攻擊 Fire 時回傳 `0.5`。
  - Fire 攻擊 Plant 時回傳 `0.7`。
  - Plant 攻擊 Water 時回傳 `0.3`。
  - 其他元素組合回傳 `0`。
- `attacked(int incomingDamage)`
  - 先計算 `realDamage = incomingDamage - defense`，再呼叫一次 `countAvoidTime()`。
  - 若本次閃避或 `realDamage <= 0`，不扣除生命值並回傳 `true`。
  - 否則將 `realDamage` 自 `currHealth` 扣除，並回傳 `false`。
- `getPosition()`、`getElementType()` 分別回傳 `pos` 和 `type`。
- `getInteractPositions() const` 依照 `pos` 回傳可攻擊的敵方位置：
  - Front 只可攻擊 Front。
  - Middle 可攻擊 Front、Middle。
  - Back 可攻擊 Middle、Back。
- `FrontGingerbreadMan`、`MiddleGingerbreadMan`、`BackGingerbreadMan` 皆繼承 `GingerbreadMan`。其建構子依序接收 `name`、`type`、`damage`、`defense`、`health`；`critDamage`、`critTime`、`avoidTime` 的預設值分別為 `0.5`、`3`、`5`，並各自設定對應的 `Position`。
- 三個位置類別額外提供以下 buff：
  - `FrontGingerbreadMan::defenseBuff()`：僅當 `defense > damage` 時，將 `defense` 增加 `50`。
  - `MiddleGingerbreadMan::criticalBuff()`：僅當 `critDamage < 0.5` 時，將 `critDamage` 設為 `0.5`。
  - `BackGingerbreadMan::keepHealingBuff()`：僅當 `health > currHealth` 時，將 `currHealth` 增加 `1`。

> [!Note] 
> 請在 GingerbreadMan.hpp 中更改其中一行，使其能正常運行。

> [!Note] 
> FrontGingerbreadMan.hpp、MiddleGingerbreadMan.hpp、BackGingerbreadMan.hpp 少了三行，請新增它並使其能正常運行。

## 目標三、設計餅乾類別
九種餅乾皆繼承對應位置的薑餅人類別。各餅乾應設定下列初始屬性，並依規格覆寫升級、攻擊或受擊行為；未列為覆寫的函式沿用基底類別實作。

### 薑餅人清單

以下攻擊公式中的 `crit` 表示本次爆擊時的 `critDamage`，未爆擊時為 `0`。而受擊公式中成功閃避時即不扣血或是 `realDamage` 小於等於 `0`，直接回傳 `true`，反之，扣血並回傳 `false`。公式中未特別說明的運算依 C++ 型別規則執行。

> [!Note] 
> 請自行決定哪些方法要複寫

- ![Millennial Tree Cookie](./doc/MTC.png)
  - 名稱：Millennial Tree Cookie。
  - 繼承：`FrontGingerbreadMan`。
  - 初始屬性：位置為 Front，元素為 Plant，`damage = 200`，`defense = 100`，`health = 1000`，`critDamage = 0.5`，`critTime = 3`，`avoidTime = 5`。
  - 升級：`level` 加 `1`；`damage`、`defense`、`health` 各加 `150`；`currHealth` 回滿。
  - 攻擊：`(1 + crit + currHealth / health + elementalAttack(enemyType)) * damage`。
  - 受擊：`realDamage = incomingDamage - defense * (1 + currHealth / health)`，計算完後呼叫 `defenseBuff()`。

- ![White Lily Cookie](./doc/WLC.png)
  - 名稱：White Lily Cookie。
  - 繼承：`MiddleGingerbreadMan`。
  - 初始屬性：位置為 Middle，元素為 Plant，`damage = 100`，`defense = 100`，`health = 1500`，`critDamage = 0.2`，`critTime = 2`，`avoidTime = 5`。
  - 升級：`level` 加 `1`；`damage`、`defense`、`health` 各加 `100`；`currHealth` 回滿。
  - 攻擊：`(1 + crit + elementalAttack(enemyType)) * damage + crit * currHealth`。
  - 受擊：`realDamage = incomingDamage - (defense + damage)`，計算完後呼叫 `criticalBuff()`。

- ![Silverbell Cookie](./doc/SC.png)
  - 名稱：Silverbell Cookie。
  - 繼承：`BackGingerbreadMan`。
  - 初始屬性：位置為 Back，元素為 Plant，`damage = 200`，`defense = 150`，`health = 900`，`critDamage = 0.8`，`critTime = 3`，`avoidTime = 8`。
  - 升級：`level` 加 `1`；`damage` 加 `150`、`defense` 加 `50`、`health` 加 `100`；`currHealth` 回滿，計算完後呼叫 `keepHealingBuff()`。
  - 攻擊：`(1 + crit + elementalAttack(enemyType)) * damage`。
  - 受擊：`realDamage = incomingDamage - defense * (1 + level / 100.0)`。

- ![Burning Spice Cookie](./doc/BSC.png)
  - 名稱：Burning Spice Cookie。
  - 繼承：`FrontGingerbreadMan`。
  - 初始屬性：位置為 Front，元素為 Fire，`damage = 200`，`defense = 100`，`health = 1000`，`critDamage = 0.5`，`critTime = 3`，`avoidTime = 5`。
  - 升級：`level` 加 `1`；`damage` 加 `200`、`critDamage` 加 `0.05`、`health` 加 `150`；`currHealth` 回滿。
  - 攻擊：`(1 + crit + elementalAttack(enemyType)) * damage + 50`，計算完後呼叫 `defenseBuff()`。
  - 受擊：`realDamage = incomingDamage - defense`。

- ![Chili Pepper Cookie](./doc/CPC.png)
  - 名稱：Chili Pepper Cookie。
  - 繼承：`MiddleGingerbreadMan`。
  - 初始屬性：位置為 Middle，元素為 Fire，`damage = 200`，`defense = 100`，`health = 700`，`critDamage = 0.8`，`critTime = 7`，`avoidTime = 3`。
  - 升級：`level` 加 `1`；`damage`、`defense`、`health` 各加 `100`；`currHealth` 回滿，計算完後呼叫`criticalBuff()`。
  - 攻擊：`(1 + crit + currHealth / health + elementalAttack(enemyType)) * damage`。
  - 受擊：`realDamage = incomingDamage - defense`。

- ![Fire Spirit Cookie](./doc/FSC.png)
  - 名稱：Fire Spirit Cookie。
  - 繼承：`BackGingerbreadMan`。
  - 初始屬性：位置為 Back，元素為 Fire，`damage = 500`，`defense = 40`，`health = 200`，`critDamage = 0.5`，`critTime = 2`，`avoidTime = 7`。
  - 升級：`level` 加 `1`；`damage` 加 `100`、`critDamage` 加 `0.1`、`health` 加 `10`；`currHealth` 回滿，計算完後呼叫 `keepHealingBuff()`。
  - 攻擊：`(1 + crit + elementalAttack(enemyType)) * damage`。
  - 受擊：`realDamage = incomingDamage - defense`。

- ![Crimson Coral Cookie](./doc/CCC.png)
  - 名稱：Crimson Coral Cookie。
  - 繼承：`FrontGingerbreadMan`。
  - 初始屬性：位置為 Front，元素為 Water，`damage = 200`，`defense = 500`，`health = 100`，`critDamage = 0.5`，`critTime = 3`，`avoidTime = 10`。
  - 升級：`level` 加 `1`;`damage`、`defense`、`health` 各加 `100`;`currHealth` 回滿。
  - 攻擊：`(1 + crit + elementalAttack(enemyType)) * damage + defense + health`，計算完後呼叫 `defenseBuff()`。
  - 受擊：`realDamage = incomingDamage - defense`。

- ![Sea Fairy Cookie](./doc/SFC.png)
  - 名稱：Sea Fairy Cookie。
  - 繼承：`MiddleGingerbreadMan`；覆寫 `levelUp()`、`attack(Element)`。
  - 初始屬性：位置為 Middle，元素為 Water，`damage = 200`，`defense = 300`，`health = 1000`，`critDamage = 0.3`，`critTime = 3`，`avoidTime = 5`。
  - 升級：`level` 加 `1`；`damage` 加 `100`、`defense` 加 `200`、`health` 加 `140`；`currHealth` 回滿，計算完後呼叫 `criticalBuff()`。
  - 攻擊：`(1 + crit + elementalAttack(enemyType)) * damage + crit * defense`。
  - 受擊：`realDamage = incomingDamage - defense`。

- ![Seltzer Cookie](./doc/SeC.png)
  - 名稱：Seltzer Cookie。
  - 繼承：`BackGingerbreadMan`；覆寫 `attacked(int)`。
  - 初始屬性：位置為 Back，元素為 Water，`damage = 100`，`defense = 400`，`health = 700`，`critDamage = 0.8`，`critTime = 2`，`avoidTime = 3`。
  - 升級：`level` 加 `1`;`damage`、`defense`、`health` 各加 `100`;`currHealth` 回滿。
  - 攻擊：`(1 + crit + elementalAttack(enemyType)) * damage`。
  - 受擊：`realDamage = incomingDamage - defense * (1 + level / 100.0)`，計算完後呼叫`keepHealingBuff()`。

## 目標四、設計薑餅人隊伍類別
`GingerbreadGroup` 管理隊伍成員，提供成員新增、替換、排序、移除及戰鬥操作。
- `queue`：以 `std::vector<GingerbreadMan>` 保存隊伍成員。
- `maxSize`：隊伍容量上限，限制為 `3` 至 `9`。
- `currIndex`：下一次執行攻擊的隊員索引，初始為 `0`。
- `GingerbreadGroup(int maxSize)`
  - `maxSize` 小於 `3` 或大於 `9` 時，拋出 `std::invalid_argument`。
  - 建構後隊伍為空，不建立空槽。
  - Front、Middle 的位置容量各為 `maxSize / 3`；Back 的位置容量為 `maxSize - 2 * (maxSize / 3)`，整數除法的餘數分配給 Back。
- `std::vector<int> attack(std::vector<Element>& types)`
  - 建立與 `types` 等長且初始值皆為 `0` 的傷害陣列。
  - 若隊伍為空，直接回傳傷害陣列。
  - 由 `queue[currIndex]` 作為本次攻擊者；敵人少於三人時，攻擊者可攻擊所有敵人。
  - 敵人有三人或以上時，令 `unit = types.size() / 3`。索引 `[0, unit)` 為 Front、`[unit, 2 * unit)` 為 Middle，其餘索引為 Back。
  - 只有敵人位置位於攻擊者 `getInteractPositions()` 回傳範圍內時，才呼叫 `attack(types[i])`；未命中的傷害維持 `0`。
  - 每次呼叫只使用一位攻擊者。隊伍非空時，呼叫結束後將 `currIndex` 輪替至下一位。
- `void attacked(std::vector<float>& damages)`
  - `damages` 長度與目前隊伍人數不符時，拋出 `std::invalid_argument`，不套用傷害。
  - 依序將傷害傳給每位隊員的 `attacked()`；`float` 傷害會轉換為 `int`。
  - 套用傷害後移除所有 `currHealth <= 0` 的隊員。
- `void addGingerbreadMan(const GingerbreadMan& gingerbreadMan)`
  - 隊員名稱不可重複，且該位置不可超過容量；違反任一條件時，拋出 `std::invalid_argument`。
  - 通過檢查後，將成員複製到 `queue` 尾端。
- `void replaceGingerbreadMan(int index, const GingerbreadMan& gingerbreadMan)`
  - 以新成員取代 `queue` 中指定索引的既有成員，不用於填入空槽。
  - `index < 0` 或 `index >= queue.size()` 時，拋出 `std::out_of_range`。
  - 新成員的位置須與被取代成員相同，名稱也不可與其他隊員重複；違反時拋出 `std::invalid_argument`。
- `void sortByHealth()`、`void sortByDamage()`、`void sortByDefense()`
  - 分別依照 `health`、`damage`、`defense` 由高至低穩定排序。
  - 數值相同時維持原有相對順序；排序不會改變成員的 `Position`。
- `int countCombatPower()`
  - 回傳所有隊員的 `health + defense + damage` 總和。
  - 使用最大生命值 `health`，不使用目前生命值 `currHealth`。
- `void removeDeadGingerbreadMan()`
  - 移除所有 `currHealth <= 0` 的隊員。
  - 移除後保持 `currIndex` 有效；隊伍為空時，將 `currIndex` 設為 `0`。
- `void removeGingerbreadMan(std::string name)`
  - 移除第一個名稱相符的隊員；沒有相符隊員時不改變隊伍。
- `void removeGingerbreadMan(Element element)`
  - 移除所有元素相符的隊員。
- `GingerbreadMan getGingerbreadMan(int index)`
  - 回傳指定索引的隊員副本。
  - `index < 0` 或 `index >= queue.size()` 時，拋出 `std::out_of_range`。
- `queue` 使用 `GingerbreadMan` 值儲存隊員。加入派生餅乾時會發生物件切片，因此隊伍副本不保留餅乾覆寫的攻擊、受擊及升級行為，但會保留基底狀態、位置與元素。

## 測試範圍與分數分配
測試程式分布於以下檔案：
- `test/ut_character.cpp`（10%）：測試目標一的所有實作。
- `test/ut_gingerbread_man.cpp`（20%）：測試目標二的所有實作。
- `test/ut_fire_cookie.cpp`、`test/ut_water_cookie.cpp`、`test/ut_plant_cookie.cpp`（40%）：測試目標三，九種餅乾的所有實作。
- `test/ut_gingerbread_group.cpp`（30%）：測試目標四，`GingerbreadGroup`的所有實作。

> [!Note]
> 加分題：請自行判斷哪些函式可以進行 override。 若不經判斷，直接複寫掉所有可能不用複寫的函式，則無法獲得此加分。能正確判斷哪些函式需要在繼承後覆寫，才可獲得額外 5 分。（加分將在試後額外統計並公布）

## 備註
- 可以依需求使用 `virtual`、純虛擬函式，以及新增 `private` 或 `protected` 成員與函式。
- `sort` 和 `exception` 的用法可參考 [cppreference](https://cppreference.com/) 或先前的作業。
