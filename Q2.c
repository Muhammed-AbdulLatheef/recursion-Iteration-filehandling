#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_CURRENCY_NAME 10
#define MAX_CURRENCIES 5

typedef struct {
    char currency[MAX_CURRENCY_NAME];
    float buyRate;      
    float sellRate;     
} ExchangeRate;

int main(){
    
}