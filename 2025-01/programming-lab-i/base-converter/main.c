#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MAX_DIGITS 32
#define MAX_NUMBER_LENGTH 32

typedef char Digits[MAX_NUMBER_LENGTH];

typedef struct Number
{
    int length;
    int base;
    Digits digits;
} Number;

char digitsAsChar[MAX_DIGITS] = {
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    'a',
    'b',
    'c',
    'd',
    'e',
    'f',
    'g',
    'h',
    'i',
    'j',
    'k',
    'l',
    'm',
    'n',
    'o',
    'p',
    'q',
    'r',
    's',
    't',
    'u',
    'v'
};

void dropNewLineFromStr(char* str, int length)
{
    int i = 0;
    for (i = 0; i < length; ++i) {
        if (str[i] == '\n')
            str[i] = '\0';
    }
}

int findEquivalentNumberFromDigit(char digit)
{
    int i = 0;
    for (i = 0; i < MAX_DIGITS; ++i) {
        if (digitsAsChar[i] == digit)
            return i;
    }
    return 0;
}

int discoverNumberLength(char* digits)
{
    int length = 0;

    int i = 0;
    for (i = 0; i < MAX_NUMBER_LENGTH; ++i) {
        if (digits[i] == '\0') break;

        ++length;
    }

    return length;
}

void displayNumber(Number* number)
{
    printf("\n--- Number ---\n");
    printf("number: %s\n", number->digits);
    printf("base: %d\n", number->base);
    printf("length: %d\n", number->length);
    printf("\n");
}

int pow_(int base, int exponent)
{
    if (exponent == 0) return 1;

    int result = base;
    int i = 0;
    for (i = 1; i < exponent; ++i) {
        result *= base;
    }
    return result;
}

int convertToDecimal(Number* number)
{
    int result = 0;
    int i = 0;
    int j = number->length - 1;

    for (i = 0; i < number->length; ++i) {
        result +=
            findEquivalentNumberFromDigit(number->digits[j]) * pow_(number->base, i);

        --j;
    }

    return result;
}

void runTests();

int main(int argc, char** argv)
{
    Number number;
    Digits digits;
    int base = 10;
    int choice = 0;

    printf("\n####################################################\n");
    printf("\n### Welcome to 'ANY BASE TO DECIMAL' Converter ### \n");
    printf("\nRead the rules carefully:\n");
    printf("\n* The maximum allowed base is %d;\n", MAX_DIGITS);
    printf("* The digits are: 0-9 and a-v, lower-case letters only;\n");
    printf("* The number can have a maximum of %d digits;\n", MAX_NUMBER_LENGTH);
    printf("\n####################################################\n");

    while(1)
    {
        printf("\n0 - Exit\n");
        printf("1 - Convert a number to decimal\n");
        printf("99 - Run tests (dev only)\n");
        printf("Choose one option: ");
        scanf("%d", &choice);
        getchar(); // clean '\n' from buffer

        switch (choice) {
            case 1:
                printf("\nEnter a number: ");
                fgets(digits, MAX_NUMBER_LENGTH, stdin);
                dropNewLineFromStr(digits, MAX_NUMBER_LENGTH);

                printf("Enter the base of the number: ");
                scanf("%d", &base);

                if (base > MAX_DIGITS) {
                    printf("Maximum allowed base is %d.\n", MAX_DIGITS);
                    break;
                }

                printf("You chose %s (base %d), nice choice!\n", digits, base);

                number.base = base;
                strcpy(number.digits, digits);
                number.length = discoverNumberLength(number.digits);
                displayNumber(&number);

                printf("The result of the conversion is: %d\n", convertToDecimal(&number));
                break;
            case 99:
                runTests();
                break;
            default:
                printf("\nUntil next time!\n");
                return 0;
        }
    }

    return 0;
}

void runTests()
{
    printf("\n###########################################\n");
    printf("\n### TESTS ###\n\n");

    Number number;

    char* testNumbers[5] = {
        "10110100011110",
        "67016",
        "12994",
        "55bc",
        "g9ft"
    };

    int testBases[5] = {
        2,
        8,
        10,
        16,
        32
    };

    int testExpected[5] = {
        11550,
        28174,
        12994,
        21948,
        534013
    };

    int i = 0;
    int passedTests = 0;
    for (i = 0; i < 5; ++i) {
        number.length = discoverNumberLength(testNumbers[i]);
        strcpy(number.digits, testNumbers[i]);
        number.base = testBases[i];
        
        printf("Number %s (base %d) should be equal to %d (base 10): ", number.digits, number.base, testExpected[i]);

        if (convertToDecimal(&number) == testExpected[i]) {
            printf("PASSED!\n");
            ++passedTests;
        } else printf("NOT PASSED!\n");
    }

    if (passedTests == 5)
        printf("\nALL TESTS HAVE PASSED!\n");
    else
        printf("\nSOME TESTS HAVEN'T PASSED, CHECK THE IMPLEMENTATION\n");

    printf("\n### END OF TESTS ###\n");
    printf("\n###########################################\n");
}

