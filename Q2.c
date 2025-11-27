#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_CURRENCIES 3
#define MAX_CURRENCY_NAME 4

typedef struct {
    char currency[MAX_CURRENCY_NAME];
    float buyRate;      
    float sellRate;     
} ExchangeRate;

void displayRates(ExchangeRate rates[], int count);
void curr_change(float amCur1, float amMax, float excRate, float *amCur2, float *leftOver);

int main(){
    ExchangeRate rates[MAX_CURRENCIES] = {
        {"USD", 3.67, 3.75},
        {"EUR", 4.10, 4.20},
        {"GBP", 4.50, 4.60},
    };
    int count = 0;

    char localcurrency[MAX_CURRENCY_NAME] = "AED";
    int maxAmount = 10000;

    printf("Welcome to the Currency Exchange Service!\n");
    displayRates(rates, MAX_CURRENCIES);

    char sourceCurrency[MAX_CURRENCY_NAME];
    printf("Enter the currency you want to exchange from (example: USD, EUR): ");
    scanf("%s", sourceCurrency);

    char targetCurrency[MAX_CURRENCY_NAME];
    printf("Enter the currency you want to exchange to (example: USD, EUR): ");
    scanf("%s", targetCurrency);

    float amount;
    float exchangedRate;
    float exchangedAmount;
    float leftoverAmount;
    int found = 0;
    if ((strcmp(sourceCurrency, localcurrency) == 0 && strcmp(targetCurrency, localcurrency) == 0) ||
        (strcmp(sourceCurrency, localcurrency) != 0 && strcmp(targetCurrency, localcurrency) != 0)) {
        printf("Exchanges must be between %s and one supported international currency.\n", localcurrency);
        return 0;
    } else {
        for (int i = 0; i < MAX_CURRENCIES; i++) {
            if (strcmp(rates[i].currency, targetCurrency) == 0) {
                found = 1;
                printf("Enter the amount in %s to exchange (max %d): ", localcurrency, maxAmount);
                scanf("%f", &amount);

                if (amount > maxAmount) {
                    printf("Amount exceeds maximum limit of %d %s.\n", maxAmount, localcurrency);
                } else {
                    exchangedRate = 1.0f / rates[i].buyRate;
                    curr_change(amount, (float)maxAmount, exchangedRate, &exchangedAmount, &leftoverAmount);
                    printf("Rate used: 1 %s = %.4f %s\n", localcurrency, exchangedRate, rates[i].currency);
                    printf("You will receive %.4f %s for %.2f %s.\n",
                           exchangedAmount, rates[i].currency, amount, localcurrency);
                    printf("Leftover returned: %.4f %s\n", leftoverAmount, localcurrency);
                }
                break;
            } else if (strcmp(rates[i].currency, sourceCurrency) == 0) {
                found = 1;
                printf("Enter the amount in %s to exchange (max %d): ", sourceCurrency, maxAmount);
                scanf("%f", &amount);

                if (amount > maxAmount) {
                    printf("Amount exceeds maximum limit of %d %s.\n", maxAmount, sourceCurrency);
                } else {
                    exchangedRate = rates[i].sellRate;
                    curr_change(amount, (float)maxAmount, exchangedRate, &exchangedAmount, &leftoverAmount);
                    printf("Rate used: 1 %s = %.4f %s\n", sourceCurrency, exchangedRate, localcurrency);
                    printf("You will receive %.4f %s for %.2f %s.\n",
                           exchangedAmount, localcurrency, amount, sourceCurrency);
                    printf("Leftover returned: %.4f %s\n", leftoverAmount, sourceCurrency);
                }
                break;
            }
        }

        if (!found) {
            printf("Currency not found.\n");
        }
    }


    return 0;
}

void displayRates(ExchangeRate rates[], int count) {
    printf("Available Exchange Rates:\n");
    for (int i = 0; i < count; i++) {
        printf("Currency: %s, Buy Rate: %.2f, Sell Rate: %.2f\n",
               rates[i].currency, rates[i].buyRate, rates[i].sellRate);
    }
}

void curr_change(float amCur1, float amMax, float excRate, float *amCur2, float *leftOver) {
    float convertedAmount = amCur1 * excRate;
    if (convertedAmount > amMax) {
        *amCur2 = amMax;
        *leftOver = (convertedAmount - amMax) / excRate;
    } else {
        *amCur2 = convertedAmount;
        *leftOver = 0.0f;
    }
}
