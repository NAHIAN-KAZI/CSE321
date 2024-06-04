#include <stdio.h>

struct OrderedItems {
    char items[20];
    int quantity;
    float UnitPrice;
};

int main() {
    struct OrderedItems item1 = {"Paratha", 0, 0.0};
    struct OrderedItems item2 = {"Vegetable", 0, 0.0};
    struct OrderedItems item3 = {"Mineral Water", 0, 0.0};

    printf("Quantity of Paratha: ");
    scanf("%d", &item1.quantity);
    printf("Unit Price: ");
    scanf("%f", &item1.UnitPrice);

    printf("Quantity of Vegetables: ");
    scanf("%d", &item2.quantity);
    printf("Unit Price: ");
    scanf("%f", &item2.UnitPrice);

    printf("Quantity of Mineral Water: ");
    scanf("%d", &item3.quantity);
    printf("Unit Price: ");
    scanf("%f", &item3.UnitPrice);

    float TotalBill = (item1.quantity * item1.UnitPrice) +
                      (item2.quantity * item2.UnitPrice) +
                      (item3.quantity * item3.UnitPrice);

    int TotalPeople;
    printf("Number of people: ");
    scanf("%d", &TotalPeople);

    float individualPayment = TotalBill / TotalPeople;

    printf("Individual people will pay: %.1f tk\n", individualPayment);

    return 0;
}