# Inventory Management System (Console C)

This project is a menu-driven console application written in C.

## Features Implemented

### Data Management (5)
1. Add new item
2. Display all items
3. Search item by ID
4. Modify item
5. Delete item
6. Issue item (reduce stock)

### Logical/Processing Activities (5)
7. Calculate total and average inventory value
8. Find highest and lowest value item
9. Count low-stock items based on a threshold
10. Concatenate item name and category
11. Check substring existence in item names

## Requirement Coverage
- Uses 2 structures: `Supplier` and `Item`
- Uses array of structures: `Item items[MAX_ITEMS]` where `MAX_ITEMS = 100`
- Uses strings and string functions: `fgets`, `strcpy`, `strcat`, `strlen`, `strstr`, `strcspn`
- Uses calculations, conditions, and loops
- Uses function-based modular design and menu-driven flow

## Files
- `main.c` - complete source code

## Build and Run

### GCC (MinGW)
```powershell
gcc -Wall -Wextra -pedantic -std=c11 main.c -o inventory.exe
.\inventory.exe
```

### MSVC (Developer Command Prompt)
```powershell
cl /W4 main.c
main.exe
```
