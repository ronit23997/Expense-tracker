#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPENSES 1000
#define MAX_DESC 100
#define MAX_CAT 30
#define MAX_CUR 4

typedef struct {
    char date[11]; // Format: YYYY-MM-DD
    char category[MAX_CAT];
    float amount;
    char currency[4]; // e.g., USD, EUR, INR
    char description[MAX_DESC];
} Expense;

Expense expenses[MAX_EXPENSES];
int expense_count = 0;

// Hardcoded exchange rates to USD
float get_rate_to_usd(const char *currency) {
    if (strcmp(currency, "USD") == 0) return 1.0;
    if (strcmp(currency, "EUR") == 0) return 1.1; // 1 EUR = 1.1 USD
    if (strcmp(currency, "INR") == 0) return 0.012; // 1 INR = 0.012 USD
    if (strcmp(currency, "GBP") == 0) return 1.3; // 1 GBP = 1.3 USD
    return 1.0; // default
}

void add_expense();
void view_expenses();
void search_expenses();
void show_statistics();
void save_expenses();
void load_expenses();
void view_expenses_by_month();

int main() {
    int choice;
    load_expenses();
    do {
        printf("\n--- Personal Expense Tracker ---\n");
        printf("1. Add Expense\n2. View All Expenses\n3. Search Expenses by Category\n4. Show Statistics\n5. View Expenses by Month\n6. Save & Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline
        switch(choice) {
            case 1: add_expense(); break;
            case 2: view_expenses(); break;
            case 3: search_expenses(); break;
            case 4: show_statistics(); break;
            case 5: view_expenses_by_month(); break;
            case 6: save_expenses(); printf("Goodbye!\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 6);
    return 0;
}

void add_expense() {
    if (expense_count >= MAX_EXPENSES) {
        printf("Expense limit reached!\n");
        return;
    }
    printf("Enter date (YYYY-MM-DD): ");
    scanf("%10s", expenses[expense_count].date);
    printf("Enter category: ");
    scanf("%29s", expenses[expense_count].category);
    printf("Enter amount: ");
    scanf("%f", &expenses[expense_count].amount);
    printf("Enter currency (USD, EUR, INR, GBP): ");
    scanf("%3s", expenses[expense_count].currency);
    getchar(); // consume newline
    printf("Enter description: ");
    fgets(expenses[expense_count].description, MAX_DESC, stdin);
    expenses[expense_count].description[strcspn(expenses[expense_count].description, "\n")] = 0; // remove newline
    expense_count++;
    printf("Expense added!\n");
}

void view_expenses() {
    printf("\n--- All Expenses ---\n");
    for (int i = 0; i < expense_count; i++) {
        printf("%d. %s | %s | %.2f %s | %s\n", i+1, expenses[i].date, expenses[i].category, expenses[i].amount, expenses[i].currency, expenses[i].description);
    }
}

void search_expenses() {
    char search[MAX_CAT];
    printf("Enter category to search: ");
    scanf("%29s", search);
    printf("\n--- Expenses in category '%s' ---\n", search);
    for (int i = 0; i < expense_count; i++) {
        if (strcmp(expenses[i].category, search) == 0) {
            printf("%d. %s | %.2f %s | %s\n", i+1, expenses[i].date, expenses[i].amount, expenses[i].currency, expenses[i].description);
        }
    }
}

void show_statistics() {
    char base_currency[4];
    printf("Enter base currency for statistics (USD, EUR, INR, GBP): ");
    scanf("%3s", base_currency);
    float base_rate = get_rate_to_usd(base_currency);
    float total = 0, max = 0, min = 1e9;
    int max_idx = -1, min_idx = -1;
    if (expense_count == 0) {
        printf("No expenses to show statistics.\n");
        return;
    }
    for (int i = 0; i < expense_count; i++) {
        float amount_in_usd = expenses[i].amount * get_rate_to_usd(expenses[i].currency);
        float amount_in_base = amount_in_usd / base_rate;
        total += amount_in_base;
        if (amount_in_base > max) {
            max = amount_in_base;
            max_idx = i;
        }
        if (amount_in_base < min) {
            min = amount_in_base;
            min_idx = i;
        }
    }
    printf("Total spent: %.2f %s\n", total, base_currency);
    printf("Average expense: %.2f %s\n", total/expense_count, base_currency);
    printf("Highest expense: %.2f %s (%s, %s)\n", max, base_currency, expenses[max_idx].category, expenses[max_idx].date);
    printf("Lowest expense: %.2f %s (%s, %s)\n", min, base_currency, expenses[min_idx].category, expenses[min_idx].date);
}

void view_expenses_by_month() {
    char month[8]; // YYYY-MM
    printf("Enter month (YYYY-MM): ");
    scanf("%7s", month);
    printf("\n--- Expenses for %s ---\n", month);
    int found = 0;
    for (int i = 0; i < expense_count; i++) {
        if (strncmp(expenses[i].date, month, 7) == 0) {
            printf("%d. %s | %s | %.2f %s | %s\n", i+1, expenses[i].date, expenses[i].category, expenses[i].amount, expenses[i].currency, expenses[i].description);
            found = 1;
        }
    }
    if (!found) {
        printf("No expenses found for this month.\n");
    }
}

void save_expenses() {
    FILE *fp = fopen("expenses.dat", "wb");
    if (!fp) {
        printf("Error saving expenses!\n");
        return;
    }
    fwrite(&expense_count, sizeof(int), 1, fp);
    fwrite(expenses, sizeof(Expense), expense_count, fp);
    fclose(fp);
    printf("Expenses saved successfully.\n");
}

void load_expenses() {
    FILE *fp = fopen("expenses.dat", "rb");
    if (!fp) return;
    fread(&expense_count, sizeof(int), 1, fp);
    fread(expenses, sizeof(Expense), expense_count, fp);
    fclose(fp);
}
