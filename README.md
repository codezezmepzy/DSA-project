# DSA-project
# 🎬 Movie Watchlist Organizer

A modular, menu-driven console application developed in **Standard C** as an S3 B.Tech Computer Science Engineering mini-project (following the KTU 2024 scheme). This project demonstrates the practical application of fundamental **Data Structures and Algorithms (DSA)** to solve a real-world media organization problem.

---

## 🚀 Features & Implemented Data Structures

Every data structure in this project has a specific, meaningful role and interacts seamlessly using a **pointer-based architecture** ("Single Source of Truth"):

1. **Doubly Linked List (DLL)**: Acts as the master database for the movie watchlist. Supports dynamic insertion, deletion, updating, forward/backward traversal, and title-based searching without fixed-size constraints.
2. **Hash Table (with Separate Chaining)**: Uses the movie ID as the key for lightning-fast $O(1)$ average-time searching and deletion, handling collisions gracefully via separate chaining.
3. **Binary Search Tree (BST)**: Organizes movies hierarchically based on their **ratings**. Supports Inorder, Preorder, and Postorder traversals, where **Inorder traversal** outputs movies in strictly increasing order of rating.
4. **Queue (Circular Array)**: Manages the **"Next Movies to Watch"** playlist using the **FIFO** (First In, First Out) principle.
5. **Stack (Array-based)**: Manages the **"Recently Watched History"** using the **LIFO** (Last In, First Out) principle. Powers the core workflow behavior: *"Watch Next Movie"* (Dequeues from Queue $\rightarrow$ Marks Watched $\rightarrow$ Pushes to Stack $\rightarrow$ Updates DLL).
6. **Merge Sort**: A divide-and-conquer sorting algorithm that allows users to sort movies by **Rating**, **Release Year**, or **Title** in ascending or descending order with $O(N \log N)$ efficiency.

---

## 🛠️ Project Architecture & Pointer Design

To avoid memory waste and data inconsistency, **no movie data is duplicated**. 
* The **Doubly Linked List** owns the dynamically allocated `Movie` memory.
* The Hash Table, BST, Queue, and Stack store lightweight **memory pointers (`Movie*`)** pointing directly to the master nodes. 
* Updating or modifying a movie record once updates it globally across all structures instantly.

---

## 📋 Main Menu Options

```text
==============================
      MOVIE WATCHLIST         
==============================
1. Add Movie
2. Delete Movie
3. Update Movie
4. Display Watchlist
5. Search Movie
6. Sort Movies
7. Add Movie to Watch Queue
8. View Next Movie
9. Watch Next Movie
10. Recently Watched
11. Add/Remove Favorite
12. Display Favorites
13. BST Operations (Inorder/Pre/Post)
14. Hash Table Search
15. Statistics
16. Exit
