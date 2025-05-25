#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Product {
    int id;
    char name[50];
    int quantity;
    float price;

    int height;
    struct Product* left;
    struct Product* right;
} Product;

// Utility functions
int height(Product* node) {
    return node ? node->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Product* createProduct(int id, const char* name, int quantity, float price) {
    Product* node = (Product*)malloc(sizeof(Product));
    node->id = id;
    strcpy(node->name, name);
    node->quantity = quantity;
    node->price = price;
    node->height = 1;
    node->left = node->right = NULL;
    return node;
}

Product* rightRotate(Product* y) {
    Product* x = y->left;
    Product* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

Product* leftRotate(Product* x) {
    Product* y = x->right;
    Product* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

int getBalance(Product* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Insert
Product* insert(Product* node, int id, const char* name, int quantity, float price) {
    if (!node) return createProduct(id, name, quantity, price);

    if (id < node->id)
        node->left = insert(node->left, id, name, quantity, price);
    else if (id > node->id)
        node->right = insert(node->right, id, name, quantity, price);
    else {
        printf("Product with ID %d already exists.\n", id);
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && id < node->left->id)
        return rightRotate(node);
    if (balance < -1 && id > node->right->id)
        return leftRotate(node);
    if (balance > 1 && id > node->left->id) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && id < node->right->id) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Minimum value node
Product* minValueNode(Product* node) {
    Product* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Delete
Product* deleteNode(Product* root, int id) {
    if (!root) return root;

    if (id < root->id)
        root->left = deleteNode(root->left, id);
    else if (id > root->id)
        root->right = deleteNode(root->right, id);
    else {
        if (!root->left || !root->right) {
            Product* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            Product* temp = minValueNode(root->right);
            root->id = temp->id;
            strcpy(root->name, temp->name);
            root->quantity = temp->quantity;
            root->price = temp->price;
            root->right = deleteNode(root->right, temp->id);
        }
    }

    if (!root) return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// In-order display
void displayInventory(Product* root) {
    if (root) {
        displayInventory(root->left);
        printf("ID: %d | Name: %s | Qty: %d | Price: ₹%.2f\n", root->id, root->name, root->quantity, root->price);
        displayInventory(root->right);
    }
}

// Search
Product* search(Product* root, int id) {
    if (!root || root->id == id)
        return root;
    if (id < root->id)
        return search(root->left, id);
    return search(root->right, id);
}

// Update
void updateProduct(Product* root, int id) {
    Product* p = search(root, id);
    if (!p) {
        printf("Product not found.\n");
        return;
    }
    printf("Updating Product ID: %d (%s)\n", p->id, p->name);
    printf("Enter new name: ");
    scanf(" %[^\n]", p->name);
    printf("Enter new quantity: ");
    scanf("%d", &p->quantity);
    printf("Enter new price: ");
    scanf("%f", &p->price);
    printf("Product updated.\n");
}

// Restock
void restockProduct(Product* root, int id, int qty) {
    Product* p = search(root, id);
    if (p) {
        p->quantity += qty;
        printf("Restocked. New quantity: %d\n", p->quantity);
    } else {
        printf("Product not found.\n");
    }
}

// Low stock alert
void lowStockAlert(Product* root, int threshold) {
    if (root) {
        lowStockAlert(root->left, threshold);
        if (root->quantity < threshold)
            printf("LOW STOCK - ID: %d | Name: %s | Qty: %d\n", root->id, root->name, root->quantity);
        lowStockAlert(root->right, threshold);
    }
}

// Calculate total value
float calculateTotalValue(Product* root) {
    if (!root) return 0.0;
    return root->quantity * root->price +
           calculateTotalValue(root->left) +
           calculateTotalValue(root->right);
}

// Main
int main() {
    Product* root = NULL;
    int choice, id, quantity;
    float price;
    char name[50];

    while (1) {
        printf("\n==== Inventory Menu ====\n");
        printf("1. Insert Product\n");
        printf("2. Display Products\n");
        printf("3. Search by ID\n");
        printf("4. Update Product\n");
        printf("5. Delete Product\n");
        printf("6. Restock Product\n");
        printf("7. Low Stock Report\n");
        printf("8. Calculate Total Value\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter ID: "); scanf("%d", &id);
                printf("Enter Name: "); scanf(" %[^\n]", name);
                printf("Enter Quantity: "); scanf("%d", &quantity);
                printf("Enter Price: "); scanf("%f", &price);
                root = insert(root, id, name, quantity, price);
                break;

            case 2:
                printf("Inventory:\n");
                displayInventory(root);
                break;

            case 3:
                printf("Enter ID to search: "); scanf("%d", &id);
                Product* found = search(root, id);
                if (found)
                    printf("Found: %s | Qty: %d | Price: ₹%.2f\n", found->name, found->quantity, found->price);
                else
                    printf("Product not found.\n");
                break;

            case 4:
                printf("Enter ID to update: "); scanf("%d", &id);
                updateProduct(root, id);
                break;

            case 5:
                printf("Enter ID to delete: "); scanf("%d", &id);
                root = deleteNode(root, id);
                printf("Product deleted (if it existed).\n");
                break;

            case 6:
                printf("Enter ID to restock: "); scanf("%d", &id);
                printf("Enter quantity to add: "); scanf("%d", &quantity);
                restockProduct(root, id, quantity);
                break;

            case 7:
                printf("Enter threshold: "); scanf("%d", &quantity);
                printf("Low Stock Products (Qty < %d):\n", quantity);
                lowStockAlert(root, quantity);
                break;

            case 8:
                printf("Total Inventory Value: ₹%.2f\n", calculateTotalValue(root));
                break;

            case 9:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}
