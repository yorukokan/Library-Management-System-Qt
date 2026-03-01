# 📚 Library Management System (Qt & SQLite)

This is a **professional-grade** desktop automation system designed to manage **member records**, **book inventory**, and **loan/return workflows**. The architecture is built on **C++** and **Qt**, following strict **OOP principles**.
---

## 📺 Gameplay Demonstration
Experience the action-packed slicing mechanics:

[▶️ **Click to Watch Gameplay Video**](Library-Management.mp4)

> **Note:** To view the video directly in your browser, simply click on the `Library-Management.mp4` file within the repository.

---

## 🛠️ Core Capabilities & Technical Depth
* **Robust Database Integration:** Powered by **SQLite**. The system performs an **automatic connection handshake** upon startup.
* **Live Data Synchronization:** Utilizes `QSqlQueryModel` to reflect database changes to the **UI TableViews** in real-time.
* **Advanced Logic & Validation:**
    * **Book Protection:** Prevents deletion of books that are currently marked as **"On Loan"**.
    * **Member Integrity:** Blocks account deletion if the member has **outstanding/unreturned** books.
* **Automated Debt Calculation:** Features a built-in logic to compute **overdue fees** for returns exceeding the **15-day limit**.
* **Smart Inventory Tracking:** Automatically manages stock levels, decrementing on loan and incrementing on return.

## 📂 Project Architecture
* `mainwindow.cpp`: Central hub for **navigation** and module switching.
* `islemleruye.cpp`: Dedicated module for **Member CRUD** operations.
* `islemlerkitap.cpp`: Inventory management and **historical loan tracking**.
* `islemleroduncalma.cpp`: Workflow for matching **members with assets**.
* `islemleroduncteslim.cpp`: Core logic for **returns and financial penalties**.
---
