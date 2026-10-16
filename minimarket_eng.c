#include <stdio.h>
#include <string.h>

typedef struct { char name[50]; int price; int stock; } Product;
typedef struct { char name[50]; int points; } Member;

void checkProduct(Product db[], int size) {
    printf("\n--- Product Catalog ---\n");
    for(int i = 0; i < size; i++) {
        printf("%d. %s - Rp%d (Stock: %d)\n", i+1, db[i].name, db[i].price, db[i].stock);
    }
}

void checkMember(Member db[], int size) {
    printf("\n--- Member Data ---\n");
    for(int i = 0; i < size; i++) {
        printf("%d. %s - Points: %d\n", i+1, db[i].name, db[i].points);
    }
}

void buyProduct(Product *p, Member *m, int qty) {
    if (p->stock >= qty) {
        p->stock -= qty;
        int total = p->price * qty;
        printf("\n[TRANSACTION] %d %s Sold. Total: Rp%d\n", qty, p->name, total);
        if (total >= 20000 && m != NULL) {
            m->points += 100;
            printf("  -> Member %s earned +100 Points!\n", m->name);
        }
    } else {
        printf("\n[FAILED] Stock for %s (Remaining: %d) is not enough to buy %d!\n", p->name, p->stock, qty);
    }
}

// --- CHALLENGE 1: Update Product Price ---
void updatePrice(Product *p, int newPrice) {
    p->price = newPrice;
    printf("\n[ADMIN] Price of %s changed to Rp%d\n", p->name, p->price);
}

// --- CHALLENGE 2: Update Product Name ---
void updateName(Product *p, char newName[]) {
    strcpy(p->name, newName);
    printf("\n[ADMIN] Product name changed to %s\n", p->name);
}

int main() {
    // 1. Setup Database
    Product dbProduct[5] = { {"Soap", 5000, 10}, {"Shampoo", 15000, 5}, {"Bread", 12000, 8}, {"Milk", 25000, 15}, {"Coffee", 22000, 20} };
    Member dbMember[2] = { {"Anisa", 500}, {"Budi", 100} };

    printf("=== WELCOME TO THE MINIMARKET ===\n");
    checkProduct(dbProduct, 5);
    checkMember(dbMember, 2);

    // 2. Transaction Simulation
    buyProduct(&dbProduct[3], &dbMember[1], 2); // Budi buys 2 Milk (50k) -> gets points
    buyProduct(&dbProduct[0], &dbMember[0], 1); // Anisa buys 1 Soap (5k) -> no points
    buyProduct(&dbProduct[2], NULL, 3);         // Non-member buys 3 Bread (36k)

    // Mini-Challenge 6: Budi buys 10 Shampoo (fails, stock is only 5)
    buyProduct(&dbProduct[1], &dbMember[1], 10);

    // 3. Challenges 1 & 2 (admin features)
    updatePrice(&dbProduct[0], 7000);          // Soap: 5000 -> 7000
    updateName(&dbProduct[4], "Coffee Latte"); // Coffee -> Coffee Latte

    // 4. Prove that the data has been modified
    printf("\n=== DATA UPDATE AFTER TRANSACTIONS ===");
    checkProduct(dbProduct, 5);
    checkMember(dbMember, 2);

    return 0;
}
