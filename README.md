# CS 300: Academic Advising System (Data Structures and Algorithms)

## Project Overview
This repository contains a command-line academic advising utility designed for ABCU's Computer Science department. The software parses external course data, handles input validation, and maps out a complex curriculum of course codes, titles, and prerequisite relationships. 

The repository showcases two core components of computer science proficiency:
1. **Architectural Analysis:** A comprehensive evaluation of algorithmic runtime and memory layouts for various data structures.
2. **Working Implementation:** A clean, modular C++ application utilizing a Binary Search Tree (BST) to manage, search, and sort academic course records efficiently.

---

## Technical Reflection & Journal

### 1. What was the problem you were solving in the projects for this course?
The primary challenge was designing an academic advising system capable of handling large datasets of interconnected course information. The system needed to securely ingest raw text data, validate that all referenced prerequisites were legitimate, and provide advisors with near-instantaneous search lookups. Additionally, it required the capability to print the entire computer science curriculum in an alphanumerically sorted order (`ABCD100` before `ABCD200`). The overarching goal was balancing file ingest speeds, memory overhead, and search/sort execution times to build a highly scalable solution.

### 2. How did you approach the problem? Consider why data structures are important to understand.
Data structures dictate how efficiently an application utilizes memory and processing cycles. Choosing the wrong framework can cause an application to fail or hang as data scales. I approached the problem by analyzing three separate data structures: Vectors, Hash Tables, and Binary Search Trees (BST). 

While Vectors offer fast sequential access, they require a costly linear search $O(n)$ to locate items and a manual sorting pass to arrange records. Hash Tables provide rapid, near-constant time $O(1)$ lookup speeds but scatter data randomly, forcing an expensive $O(n \log n)$ external sort to fulfill the sorted catalog requirement. I selected a Binary Search Tree because it naturally arranges data in a sorted layout upon insertion. This structure balanced the operational trade-offs, enabling efficient $O(\log n)$ targeted queries and a linear $O(n)$ In-Order traversal to print the sorted list seamlessly.

### 3. How did you overcome any roadblocks you encountered while going through the activities or project?
A major roadblock during development was implementing robust file-parsing logic that wouldn't crash when encountering missing attributes or malformed inputs. To resolve this, I introduced defensive programming strategies, such as strict string tokenization, whitespace trimming, and validation pre-scans. I also encountered pointer-handling issues when navigating tree memory nodes. I resolved these structural challenges by running iterative print statements, utilizing the debugger to step through execution lines, and isolating node manipulation from the main interface loop.

### 4. How has your work on this project expanded your approach to designing software and developing programs?
This project completely shifted my software engineering philosophy away from simply writing code that "works" and toward prioritizing early architectural design. I now evaluate Big-O asymptotic runtime complexity and memory utilization profiles *before* implementing an application. This systematic mindset ensures that scalability and resource management are embedded directly into the software's foundational architecture rather than treated as an afterthought.

### 5. How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?
My development standards have matured significantly in terms of maintainability and clean-code practices. I focused heavily on the **Separation of Concerns** principle by decoupling the user menu interface, the file loading engine, and the core BST mechanics. This ensures that changes can be made to the user interface without breaking the tree architecture. Furthermore, using explicit naming conventions, self-documenting code, and modular object encapsulation means the codebase can be adapted effortlessly—such as expanding the `Course` object to include credit hours or instructor variables—without disturbing the underlying algorithmic framework.

---

## Comparative Algorithmic Complexity Profile

The architectural tradeoffs analyzed in the initial design phase of the project are detailed below:

| Storage Target | File Load Complexity | Individual Lookup (Option 3) | Catalog Sort/Print (Option 2) | Memory Overhead Profile |
| :--- | :--- | :--- | :--- | :--- |
| **Vector** | $O(n^2)$ | $O(n)$ | $O(n^2)$ | **Minimal:** Dense, localized continuous storage blocks. |
| **Hash Table** | $O(n^2)$ | $O(n)$ (With Collisions) | $O(n \log n)$ | **Moderate:** Linked-list pointer nodes plus unused index slots. |
| **Binary Search Tree** | $O(n^2)$ (Unbalanced) | $O(n)$ (Unbalanced) | $O(n)$ | **High:** Every node maintains explicit left/right structural addresses. |

---

## File Structure & Directory Navigation
* **`CS 300 Project One.docx`**: The original comprehensive algorithmic analysis and runtime documentation.
* **`Project_Two_Solution.cpp`**: The complete, compilable C++ source code containing the working Binary Search Tree implementation, file parser, and user menu.
* **`abcu_courses.txt`**: The raw text dataset containing course keys, titles, and prerequisite listings used to test the application.
