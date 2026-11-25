# Homework 02

> 這份作業由物件導向程式設計助教群所製。
> 如有問題，歡迎使用以下方式聯繫助教：

> Email: t112820018@ntut.org.tw 、 t112590022@ntut.org.tw 、 t113820031@ntut.org.tw
> MS Teams: 許景喬、陳駿逸、陳彥岑  
> Discord 群組  
⚠️ Due: 2026/10/27 23:59 ⚠️

## 說明

### 目標

- [ ] 了解並學會使用 C++ 編寫程式。
- [ ] 學習使用 `class`。
- [ ] 學習使用 `vector`。
- [ ] 學習使用 `sort`。
- [ ] 學習使用 `enum class`。
- [ ] 學會並撰寫 Class 中的 method。

### 檔案架構

請確認提交是否符合以下的檔案架構，否則無法進行評分。

```txt
.
│   .clang-format
│   .gitignore
│   CMakeLists.txt
│   files.cmake
│   LICENSE
│   README.md
│
├───include
│       Book.hpp
│       BookShelf.hpp
        BookSection.hpp
│
├───scripts
│       CodeCoverage.cmake
│       coverage.sh
│
├───src
│       Book.cpp
│       BookShelf.cpp
│       BookSection.cpp
│
└───test
        ut_book.cpp
        ut_book_shelf.cpp
        ut_book_section.cpp
```

## 題目評分

- ［20%］完成 `Book`。 (ut_book.cpp)
- ［50%］完成 `BookShelf`。 (ut_book_shelf.cpp)
- ［30%］完成 `BookSection`。 (ut_book_section.cpp)

作業總分為 `100` ，如果你完成 (ut_all) 的話。

## 注意事項

- 你不應該上傳 `/bin` 資料夾至專案上。
    - 你的功課不應該出現 `Memory Leak`，否則將會扣作業總分 10 分。
    - 你不應該上傳 `/bin` 資料夾至專案庫，編譯結果不應該上傳至專案庫上，若在助教確認功課評分時 `/bin` 資料夾存在在專案庫中，扣除作業總分 5 分。

## 敘述

> 嗨，歡迎參加 OOP 課程。
>
> 想必你已經完成了 OOP Concept、Class 的課程，並瞭解這門課所使用的語言 C++ 的相關語法。  
> （若還不了解的話，可以查看 Teams 的簡報）
>
> 在這個任務中，你會了解課堂上所教學的語法將如何使用。

請嘗試完成任務，並在 `OJ` 上拿到綠色的 `Correct` 勾勾。

## 題目敘述

Devin 是一個運用晚上課餘時間去圖書館打工的大二生，在整理書的過程中發現原本的書籍管理系統有許多小問題，像是不能匯入相同書名的書籍、借書時不能一次借兩本、不能更改書的實體位置等等，於是他想將課堂上所學的 OOP 概念帶入，自己寫一個方便管理圖書的小程式。

Devin 期待的圖書系統結構會有基礎的書籍，紀錄有關於該書的資訊，有可以存放同類書的書櫃，還有不同主題的區域。
在這份作業中，請幫 Devin 完成他基礎的結構。

### Task 0. 了解題目架構

- 在 `include/Book.hpp` 、 `include/BookShelf.hpp` 與 `include/BookSection.hpp` 中，是我們這次要撰寫的 `class` 與 `method`。
- 你必須要在 `src/Book.cpp` 、 `src/BookShelf.cpp` 與 `src/BookSection.cpp` 完成所有的功能，並修改 `include/Book.hpp` 使其正常運行。

### Task 1. 完成 `Book` 的建構子與其方法
請觀察 `include/Book.hpp` 後：
- 對於 `BookCategory` enum class 請完成他殘缺的結構

打開 `src/Book.cpp` 並在這裡完成你剩下的實作：
- 完成其建構子，若無傳入作者資訊，預設為`"Unknown"`
- 完成其建構子，若無傳入類別資訊，預設為`BookCategory::GENERAL`

### Task 2. 完成 `BookShelf` 的建構子與其方法
請觀察 `include/BookShelf.hpp` 後打開 `src/BookShelf.cpp` 並在這裡完成你剩下的實作：
- 完成其建構子，若無傳入空間資訊，預設為`1000`本書
- 在`setIDRange`設定書櫃中只能容納`minID`至`maxID`的書籍：
  - `minID` 不能超過 `maxID`，否則請丟出 invalid_argument
  - 設定的 ID 區間也不可以大於`bookCapacity`空間上限，否則請丟出 invalid_argument
- 在`addBook`將書籍放進書櫃中：
  - 不可以超過空間上限，否則請丟出 overflow_error
  - 一定要同個類別的書才可以放進書櫃，否則請丟出 invalid_argument
  - 書籍的 ID 一定義在書櫃定義的 ID 區間裡面，否則請丟出 invalid_argument
  - 書櫃中同樣 ID 的書籍只能有一本，否則請丟出 invalid_argument
  - 加入後請針對 ID 由小而大進行排序
- 在`remove`找到可以書籍並刪除，否則請丟出 invalid_argument
- 在`searchByBookID`可以用 ID 對書本進行搜尋，如果找不到書也麻煩丟出 invalid_argument
- 在`searchByBookName`可以用書名對書本進行搜尋，如果找不到書也麻煩丟出 invalid_argument

### Task 3. 完成 `BookSection` 的建構子與其方法
請觀察 `include/BookSection.hpp` 後打開 `src/BookSection.cpp` 並在這裡完成你剩下的實作：
- 在`addShelf`中加入書櫃，如果數量大於`bookShelfCapacity`空間上限已經滿了請丟出 invalid_argument
- 在`searchByCategory`中搜尋該類別的書櫃，如果找不到書櫃也麻煩丟出 invalid_argument

### 任務附註

- 你只需要實作任務所描述的 `class` 中的 `method` 。
- 你可以先參考 `docs` 資料夾裡的東西。
- 關於 `vector` ，你可以參考 [這篇](http://en.cppreference.com/w/cpp/container/vector) 。
- 使用 `vector` 時你應該使用 `#include<vector>` 。
- 關於 `invalid_argument()`，你可以參考 [這篇](https://en.cppreference.com/cpp/error/invalid_argument) 。
- 關於 `overflow_error()`，你可以參考 [這篇](https://en.cppreference.com/cpp/error/overflow_error) 。
- exception 內不用寫特定東西，且你應該使用 `#include<stdexcept>` 。
- 關於 `sort()` ，你可以參考 [這篇](https://en.cppreference.com/w/cpp/algorithm/sort) 。


    // 【新增元素】在容器尾端加入一個新元素
    books.push_back(60); 

    // 【移除尾端】刪除容器最後面的一個元素（不回傳值）
    books.pop_back(); 

    // 【插入元素】在指定迭代器位置插入元素（此例為插在開頭第 1 個位置）
    books.insert(books.begin(), 99); 

    // 【刪除單一元素】刪除指定迭代器位置的元素（此例為刪除第 2 個元素，索引為 1）
    books.erase(books.begin() + 1); 

    // 【刪除區間元素】刪除 [起始, 結束) 範圍內的元素（含頭不含尾）
    // books.erase(books.begin(), books.begin() + 2); 

    // 【升序排序】將元素由小到大排列（預設）
    std::sort(books.begin(), books.end()); 

    // 【降序排序】將元素由大到小排列
    std::sort(books.begin(), books.end(), std::greater<int>()); 

    // 【反轉順序】直接將目前容器內的元素前後顛倒
    std::reverse(books.begin(), books.end()); 

    // 【尋找元素】搜尋特定值，找不到會回傳 books.end()
    auto it = std::find(books.begin(), books.end(), 50);
    if (it != books.end()) {
        // 找到後直接用 erase 刪除該元素（超常見組合技！）
        books.erase(it); 
    }

    // 【清空容器】移除所有元素，size 變為 0
    books.clear(); 

    return 0;
}

- 使用 `sort()` 時你應該使用 `#include<algorithm>` 。

## Homework's meme

![HW meme](https://hackmd.io/_uploads/ryb3BJK5Gg.png)