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

/* prototypes */
void displayRates(ExchangeRate rates[], int count);
void curr_change(float amCur1, float amMax, float excRate, float *amCur2, float *leftOver);

static void strtoupper(char *s) {
    for (; *s; ++s) *s = (char) toupper((unsigned char)*s);
}

int main(){
    ExchangeRate rates[MAX_CURRENCIES] = {
        {"USD", 3.67f, 3.75f},
        {"EUR", 4.10f, 4.20f},
        {"GBP", 4.50f, 4.60f},
    };
    int count = 0;

    char localcurrency[MAX_CURRENCY_NAME] = "AED";
    int maxAmount = 10000;

    printf("Welcome to the Currency Exchange Service!\n");
    displayRates(rates, MAX_CURRENCIES);

    char sourceCurrency[MAX_CURRENCY_NAME];
    printf("Enter the currency you want to exchange from (example: USD, EUR): ");
    if (scanf("%3s", sourceCurrency) != 1) return 0;
    strtoupper(sourceCurrency);

    char targetCurrency[MAX_CURRENCY_NAME];
    printf("Enter the currency you want to exchange to (example: USD, EUR): ");
    if (scanf("%3s", targetCurrency) != 1) return 0;
    strtoupper(targetCurrency);

    float amount;
    float exchangedRate;
    float exchangedAmount;
    float leftoverAmount;
    int found = 0;
    if (strcmp(sourceCurrency, localcurrency) == 0 && strcmp(targetCurrency, localcurrency) == 0) {
        printf("Exchanges must be between %s and one supported international currency.\n", localcurrency);
        return 0;
    } else {
        for (int i = 0; i < MAX_CURRENCIES; i++) {
            /* target is foreign -> converting local -> foreign (use buyRate)
               amount entered is in local currency */
            if (strcmp(rates[i].currency, targetCurrency) == 0) {
                found = 1;
                printf("Enter the amount in %s to exchange (max %d): ", localcurrency, maxAmount);
                if (scanf("%f", &amount) != 1) return 0;

                if (amount > maxAmount) {
                    printf("Amount exceeds maximum limit of %d %s.\n", maxAmount, localcurrency);
                } else {
                    /* use buyRate: local per 1 foreign -> conversion factor local->foreign = 1 / buyRate */
                    exchangedRate = 1.0f / rates[i].buyRate;
                    curr_change(amount, (float)maxAmount, exchangedRate, &exchangedAmount, &leftoverAmount);
                    printf("Rate used: 1 %s = %.4f %s\n", localcurrency, exchangedRate, rates[i].currency);
                    printf("You will receive %.4f %s for %.2f %s.\n",
                           exchangedAmount, rates[i].currency, amount, localcurrency);
                    printf("Leftover returned: %.4f %s\n", leftoverAmount, localcurrency);
                }
                break;
            /* source is foreign -> converting foreign -> local (use sellRate)
               amount entered is in foreign currency */
            } else if (strcmp(rates[i].currency, sourceCurrency) == 0) {
                found = 1;
                printf("Enter the amount in %s to exchange (max %d): ", sourceCurrency, maxAmount);
                if (scanf("%f", &amount) != 1) return 0;

                if (amount > 0.0f) {
                    /* convert foreign amount to local first (foreign * sellRate = local) */
                    float potentialLocal = amount * rates[i].sellRate;
                    float convertedLocal = 0.0f;
                    float leftoverLocal = 0.0f;
                    curr_change(potentialLocal, (float)maxAmount, 1.0f, &convertedLocal, &leftoverLocal);
                    /* leftoverLocal is in local currency; convert leftover back to foreign to return to customer */
                    leftoverAmount = leftoverLocal / rates[i].sellRate;
                    exchangedAmount = convertedLocal; /* in local currency */
                    printf("Rate used: 1 %s = %.4f %s\n", rates[i].currency, rates[i].sellRate, localcurrency);
                    printf("You will receive %.4f %s for %.2f %s.\n",
                           exchangedAmount, localcurrency, amount, sourceCurrency);
                    printf("Leftover returned: %.4f %s\n", leftoverAmount, sourceCurrency);
                } else {
                    printf("Amount must be positive.\n");
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
    /* amCur1 and amMax are expected to be in the same currency units when called.
       excRate converts amCur1 -> amCur2 (amCur2 = amCur1 * excRate).
       If amCur1 <= amMax -> full conversion, leftover = 0.
       If amCur1 > amMax -> convert only up to amMax, leftover = amCur1 - amMax. */
    if (amCur1 <= amMax) {
        *amCur2 = amCur1 * excRate;
        *leftOver = 0.0f;
    } else {
        *amCur2 = amMax * excRate;
        *leftOver = amCur1 - amMax;
    }
}