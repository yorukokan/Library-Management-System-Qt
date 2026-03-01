📚 Library Management System (Qt & SQLite)
This application is a desktop automation system developed to manage member administration, book inventory tracking, and loan/return processes. The project is built using C++ and the Qt Framework, adhering to object-oriented programming principles.

🛠️ Technical Features & Capabilities
Database Architecture: SQLite is used for data storage. The application automatically verifies the database connection upon startup.
Dynamic Data Listing: Database tables are reflected in real-time onto UI tableView components using QSqlQueryModel.

Advanced Validation:
Book Deletion: Prevents deletion if a book is currently borrowed by a member.
Member Deletion: Issues a warning and blocks deletion if a member has unreturned books.
Debt Calculation Logic: Automatically calculates an overdue fee (debt) for book returns exceeding a 15-day period.
Inventory Management: Automatically decrements the book count by 1 during a loan and updates the inventory upon return.

📂 Project Structure
mainwindow.cpp: Manages the main menu and transitions between different modules.
islemleruye.cpp: Handles member registration, deletion, and update operations.
islemlerkitap.cpp: Manages inventory and displays historical loan activities for books.
islemleroduncalma.cpp: Manages the loaning process by matching members with books.
islemleroduncteslim.cpp: Handles book returns and debt calculation.
