#include <stdio.h>
#include <cs50.h>

bool isCardNumberValid(long cardNumber);

int get2FirstDigit(long cardNumber);

/**
 * This program check if a credit card number is valid and if yes output from which organization it is
 * @author Bartoletti Brice
 * @return void
 */
int main(void)
{

    // prompt for a credit card number
    long cardNumber = get_long("enter your card number: ");

    // get 2 last digit
    int first2Digit = get2FirstDigit(cardNumber);

    // if checkSum not ok : INVALID\n
    if (!isCardNumberValid(cardNumber))
    {
        printf("INVALID\n");
    }
    // MASTERCARD\n (51, 52, 53, 54, or 55) - 16-digit
    else if (first2Digit <= 55 && first2Digit >= 51 && cardNumber > 1000000000000000 && cardNumber < 10000000000000000)
    {
        printf("MASTERCARD\n");
    }
    // AMEX\n (34 37) - 15-digit
    else if (first2Digit == 37 || first2Digit == 34 && cardNumber > 100000000000000 && cardNumber < 1000000000000000)
    {
        printf("AMEX\n");
    }
    // VISA\n (4) 13- and 16-digit
    // get the first number to check
    else if (
            ((first2Digit - (first2Digit % 10)) / 10) == 4 &&
                    (cardNumber > 1000000000000 && cardNumber < 10000000000000) ||
                    (cardNumber > 1000000000000000 && cardNumber < 10000000000000000)
            )
    {
        printf("VISA\n");
    }
    // if none of the above then INVALID\n
    else
    {
        printf("INVALID\n");
    }
}


bool isCardNumberValid(long cardNumber)
{
    int digitSum = 0;
    for (int i = 1; cardNumber > 0; ++i)
    {
        int lastExtractedDigit = cardNumber % 10;
        cardNumber = (cardNumber - lastExtractedDigit) / 10;
        // Only for even number
        if (i % 2 == 0)
        {
            lastExtractedDigit = lastExtractedDigit * 2;
        }
        digitSum += lastExtractedDigit;
    }
    if (digitSum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int get2FirstDigit(long cardNumber)
{
    while (cardNumber > 99)
    {
        int lastExtractedDigit = cardNumber % 10;
        cardNumber = (cardNumber - lastExtractedDigit) / 10;
    }
    return cardNumber;
}
