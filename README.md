# Inventory Management System

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
