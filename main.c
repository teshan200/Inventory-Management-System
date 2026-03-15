#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 100
#define NAME_LEN 50
#define CAT_LEN 30
#define SUP_LEN 50

typedef struct {
    char supplierName[SUP_LEN];
    char phone[20];
} Supplier;

typedef struct {
    int id;
    char name[NAME_LEN];
    char category[CAT_LEN];
    int quantity;
    float unitPrice;
    Supplier supplier;
    int isActive;
} Item;

void clearInputBuffer(void);
int findItemIndexById(Item items[], int count, int id);
void addItem(Item items[], int *count);
void displayItems(const Item items[], int count);
void searchItem(const Item items[], int count);
void modifyItem(Item items[], int count);
void deleteItem(Item items[], int *count);
void issueItem(Item items[], int count);
void calculateInventoryTotals(const Item items[], int count);
void findHighestLowestValueItem(const Item items[], int count);
void countLowStockItems(const Item items[], int count);
void concatenateItemAndCategory(const Item items[], int count);
void checkSubstringInItemName(const Item items[], int count);
int showMenu(void);

int main(void) {
    Item items[MAX_ITEMS];
    int count = 0;
    int choice;

    do {
        choice = showMenu();

        switch (choice) {
            case 1:
                addItem(items, &count);
                break;
            case 2:
                displayItems(items, count);
                break;
            case 3:
                searchItem(items, count);
                break;
            case 4:
                modifyItem(items, count);
                break;
            case 5:
                deleteItem(items, &count);
                break;
            case 6:
                issueItem(items, count);
                break;
            case 7:
                calculateInventoryTotals(items, count);
                break;
            case 8:
                findHighestLowestValueItem(items, count);
                break;
            case 9:
                countLowStockItems(items, count);
                break;
            case 10:
                concatenateItemAndCategory(items, count);
                break;
            case 11:
                checkSubstringInItemName(items, count);
                break;
            case 12:
                printf("\nExiting program. Goodbye!\n");
                break;
            default:
                printf("\nInvalid option. Please choose a valid menu item.\n");
                break;
        }
    } while (choice != 12);

    return 0;
}

int showMenu(void) {
    int choice;

    printf("\n===============================================\n");
    printf("   INVENTORY MANAGEMENT SYSTEM \n");
    printf("===============================================\n");
    printf("1. Add New Item\n");
    printf("2. Display All Items\n");
    printf("3. Search Item by ID\n");
    printf("4. Modify Item\n");
    printf("5. Delete Item\n");
    printf("6. Issue Item (Reduce Stock)\n");
    printf("7. Calculate Total and Average Inventory Value\n");
    printf("8. Find Highest and Lowest Value Item\n");
    printf("9. Count Low-Stock Items\n");
    printf("10. Concatenate Item Name and Category\n");
    printf("11. Check Substring in Item Name\n");
    printf("12. Exit\n");
    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1) {
        clearInputBuffer();
        return -1;
    }

    return choice;
}

void clearInputBuffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

int findItemIndexById(Item items[], int count, int id) {
    int i;
    for (i = 0; i < count; i++) {
        if (items[i].id == id && items[i].isActive) {
            return i;
        }
    }
    return -1;
}

void addItem(Item items[], int *count) {
    Item newItem;
    int existingIndex;

    if (*count >= MAX_ITEMS) {
        printf("\nInventory is full. Maximum %d items allowed.\n", MAX_ITEMS);
        return;
    }

    printf("\nEnter Item ID: ");
    if (scanf("%d", &newItem.id) != 1) {
        clearInputBuffer();
        printf("Invalid input for ID.\n");
        return;
    }

    existingIndex = findItemIndexById(items, *count, newItem.id);
    if (existingIndex != -1) {
        printf("An active item with ID %d already exists.\n", newItem.id);
        return;
    }

    clearInputBuffer();

    printf("Enter Item Name: ");
    fgets(newItem.name, NAME_LEN, stdin);
    newItem.name[strcspn(newItem.name, "\n")] = '\0';

    printf("Enter Category: ");
    fgets(newItem.category, CAT_LEN, stdin);
    newItem.category[strcspn(newItem.category, "\n")] = '\0';

    printf("Enter Quantity: ");
    if (scanf("%d", &newItem.quantity) != 1 || newItem.quantity < 0) {
        clearInputBuffer();
        printf("Invalid quantity.\n");
        return;
    }

    printf("Enter Unit Price: ");
    if (scanf("%f", &newItem.unitPrice) != 1 || newItem.unitPrice < 0) {
        clearInputBuffer();
        printf("Invalid unit price.\n");
        return;
    }

    clearInputBuffer();

    printf("Enter Supplier Name: ");
    fgets(newItem.supplier.supplierName, SUP_LEN, stdin);
    newItem.supplier.supplierName[strcspn(newItem.supplier.supplierName, "\n")] = '\0';

    printf("Enter Supplier Phone: ");
    fgets(newItem.supplier.phone, sizeof(newItem.supplier.phone), stdin);
    newItem.supplier.phone[strcspn(newItem.supplier.phone, "\n")] = '\0';

    newItem.isActive = 1;
    items[*count] = newItem;
    (*count)++;

    printf("\nItem added successfully.\n");
}

void displayItems(const Item items[], int count) {
    int i;

    if (count == 0) {
        printf("\nNo items available in inventory.\n");
        return;
    }

    printf("\n-------------------------------------------------------------------------------------------\n");
    printf("ID   Name                 Category             Qty     Price       Supplier\n");
    printf("-------------------------------------------------------------------------------------------\n");

    for (i = 0; i < count; i++) {
        if (items[i].isActive) {
            printf("%-4d %-20s %-20s %-7d %-11.2f %-20s\n",
                   items[i].id,
                   items[i].name,
                   items[i].category,
                   items[i].quantity,
                   items[i].unitPrice,
                   items[i].supplier.supplierName);
        }
    }
}

void searchItem(const Item items[], int count) {
    int id;
    int index;

    if (count == 0) {
        printf("\nNo items to search.\n");
        return;
    }

    printf("\nEnter Item ID to search: ");
    if (scanf("%d", &id) != 1) {
        clearInputBuffer();
        printf("Invalid ID input.\n");
        return;
    }

    index = findItemIndexById((Item *)items, count, id);
    if (index == -1) {
        printf("Item with ID %d not found.\n", id);
        return;
    }

    printf("\nItem Found:\n");
    printf("ID: %d\n", items[index].id);
    printf("Name: %s\n", items[index].name);
    printf("Category: %s\n", items[index].category);
    printf("Quantity: %d\n", items[index].quantity);
    printf("Unit Price: %.2f\n", items[index].unitPrice);
    printf("Supplier: %s\n", items[index].supplier.supplierName);
    printf("Supplier Phone: %s\n", items[index].supplier.phone);
}

void modifyItem(Item items[], int count) {
    int id;
    int index;

    if (count == 0) {
        printf("\nNo items available to modify.\n");
        return;
    }

    printf("\nEnter Item ID to modify: ");
    if (scanf("%d", &id) != 1) {
        clearInputBuffer();
        printf("Invalid ID input.\n");
        return;
    }

    index = findItemIndexById(items, count, id);
    if (index == -1) {
        printf("Item with ID %d not found.\n", id);
        return;
    }

    clearInputBuffer();

    printf("Enter new Item Name: ");
    fgets(items[index].name, NAME_LEN, stdin);
    items[index].name[strcspn(items[index].name, "\n")] = '\0';

    printf("Enter new Category: ");
    fgets(items[index].category, CAT_LEN, stdin);
    items[index].category[strcspn(items[index].category, "\n")] = '\0';

    printf("Enter new Quantity: ");
    if (scanf("%d", &items[index].quantity) != 1 || items[index].quantity < 0) {
        clearInputBuffer();
        printf("Invalid quantity input.\n");
        return;
    }

    printf("Enter new Unit Price: ");
    if (scanf("%f", &items[index].unitPrice) != 1 || items[index].unitPrice < 0) {
        clearInputBuffer();
        printf("Invalid unit price input.\n");
        return;
    }

    clearInputBuffer();

    printf("Enter new Supplier Name: ");
    fgets(items[index].supplier.supplierName, SUP_LEN, stdin);
    items[index].supplier.supplierName[strcspn(items[index].supplier.supplierName, "\n")] = '\0';

    printf("Enter new Supplier Phone: ");
    fgets(items[index].supplier.phone, sizeof(items[index].supplier.phone), stdin);
    items[index].supplier.phone[strcspn(items[index].supplier.phone, "\n")] = '\0';

    printf("\nItem updated successfully.\n");
}

void deleteItem(Item items[], int *count) {
    int id;
    int index;
    int i;

    if (*count == 0) {
        printf("\nNo items available to delete.\n");
        return;
    }

    printf("\nEnter Item ID to delete: ");
    if (scanf("%d", &id) != 1) {
        clearInputBuffer();
        printf("Invalid ID input.\n");
        return;
    }

    index = findItemIndexById(items, *count, id);
    if (index == -1) {
        printf("Item with ID %d not found.\n", id);
        return;
    }

    for (i = index; i < *count - 1; i++) {
        items[i] = items[i + 1];
    }

    (*count)--;
    printf("\nItem deleted successfully.\n");
}

void issueItem(Item items[], int count) {
    int id;
    int issueQuantity;
    int index;
    float issueValue;

    if (count == 0) {
        printf("\nNo items available to issue.\n");
        return;
    }

    printf("\nEnter Item ID to issue: ");
    if (scanf("%d", &id) != 1) {
        clearInputBuffer();
        printf("Invalid ID input.\n");
        return;
    }

    index = findItemIndexById(items, count, id);
    if (index == -1) {
        printf("Item with ID %d not found.\n", id);
        return;
    }

    printf("Enter quantity to issue: ");
    if (scanf("%d", &issueQuantity) != 1 || issueQuantity <= 0) {
        clearInputBuffer();
        printf("Invalid issue quantity.\n");
        return;
    }

    if (issueQuantity > items[index].quantity) {
        printf("Not enough stock. Available quantity: %d\n", items[index].quantity);
        return;
    }

    items[index].quantity -= issueQuantity;
    issueValue = issueQuantity * items[index].unitPrice;

    printf("\nIssued %d units of %s.\n", issueQuantity, items[index].name);
    printf("Issue value: %.2f\n", issueValue);
    printf("Remaining stock: %d\n", items[index].quantity);
}

void calculateInventoryTotals(const Item items[], int count) {
    int i;
    int activeCount = 0;
    float totalValue = 0.0f;
    float averageValue;

    if (count == 0) {
        printf("\nNo items available for calculations.\n");
        return;
    }

    for (i = 0; i < count; i++) {
        if (items[i].isActive) {
            totalValue += items[i].quantity * items[i].unitPrice;
            activeCount++;
        }
    }

    if (activeCount == 0) {
        printf("\nNo active items available for calculations.\n");
        return;
    }

    averageValue = totalValue / activeCount;

    printf("\nTotal Inventory Value: %.2f\n", totalValue);
    printf("Average Value per Active Item: %.2f\n", averageValue);
}

void findHighestLowestValueItem(const Item items[], int count) {
    int i;
    int highestIndex = -1;
    int lowestIndex = -1;
    float value;

    if (count == 0) {
        printf("\nNo items available to evaluate.\n");
        return;
    }

    for (i = 0; i < count; i++) {
        if (!items[i].isActive) {
            continue;
        }

        value = items[i].quantity * items[i].unitPrice;

        if (highestIndex == -1 || value > items[highestIndex].quantity * items[highestIndex].unitPrice) {
            highestIndex = i;
        }

        if (lowestIndex == -1 || value < items[lowestIndex].quantity * items[lowestIndex].unitPrice) {
            lowestIndex = i;
        }
    }

    if (highestIndex == -1 || lowestIndex == -1) {
        printf("\nNo active items found.\n");
        return;
    }

    printf("\nHighest Value Item: %s (ID: %d, Value: %.2f)\n",
           items[highestIndex].name,
           items[highestIndex].id,
           items[highestIndex].quantity * items[highestIndex].unitPrice);

    printf("Lowest Value Item: %s (ID: %d, Value: %.2f)\n",
           items[lowestIndex].name,
           items[lowestIndex].id,
           items[lowestIndex].quantity * items[lowestIndex].unitPrice);
}

void countLowStockItems(const Item items[], int count) {
    int threshold;
    int i;
    int lowStockCount = 0;

    if (count == 0) {
        printf("\nNo items available for stock check.\n");
        return;
    }

    printf("\nEnter low-stock threshold quantity: ");
    if (scanf("%d", &threshold) != 1 || threshold < 0) {
        clearInputBuffer();
        printf("Invalid threshold value.\n");
        return;
    }

    for (i = 0; i < count; i++) {
        if (items[i].isActive && items[i].quantity < threshold) {
            lowStockCount++;
        }
    }

    printf("Items with quantity below %d: %d\n", threshold, lowStockCount);
}

void concatenateItemAndCategory(const Item items[], int count) {
    int id;
    int index;
    char combined[NAME_LEN + CAT_LEN + 5];

    if (count == 0) {
        printf("\nNo items available.\n");
        return;
    }

    printf("\nEnter Item ID for string concatenation: ");
    if (scanf("%d", &id) != 1) {
        clearInputBuffer();
        printf("Invalid ID input.\n");
        return;
    }

    index = findItemIndexById((Item *)items, count, id);
    if (index == -1) {
        printf("Item with ID %d not found.\n", id);
        return;
    }

    strcpy(combined, items[index].name);
    strcat(combined, " - ");
    strcat(combined, items[index].category);

    printf("Concatenated String: %s\n", combined);
}

void checkSubstringInItemName(const Item items[], int count) {
    char keyword[30];
    int i;
    int foundAny = 0;

    if (count == 0) {
        printf("\nNo items available.\n");
        return;
    }

    clearInputBuffer();
    printf("\nEnter substring to search in item names: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    if (strlen(keyword) == 0) {
        printf("Empty substring is not allowed.\n");
        return;
    }

    printf("\nItems containing \"%s\" in name:\n", keyword);
    for (i = 0; i < count; i++) {
        if (items[i].isActive && strstr(items[i].name, keyword) != NULL) {
            printf("ID: %d, Name: %s\n", items[i].id, items[i].name);
            foundAny = 1;
        }
    }

    if (!foundAny) {
        printf("No item names matched the substring.\n");
    }
}
