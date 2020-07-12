#include <stdio.h>
#include <cs50.h>

bool isCardNumberValid(long cardNumber);

int get2FirstDigit(long cardNumber);
int getNumberOfDigit(long cardNumber);

/**
 * This program check if a credit card number is valid and if yes output from which organization it is
 * @author Bartoletti Brice
 * @return void
 */
int main(void)
{
    // prompt for a credit card number
    long cardNumber = get_long("enter your card number: ");
    printf("\n%ld - this is the card number\n", cardNumber);

    // get 2 last digit for organization identification
    int first2Digit = get2FirstDigit(cardNumber);
    printf("%d - this is the 2 first digit\n", first2Digit);

    // get number of digit
    int numberOfDigit = getNumberOfDigit(cardNumber);

    // compute checkSum: if not ok -> INVALID\n
    if (!isCardNumberValid(cardNumber))
    {
        //printf("CheckSum invalid\n");
        printf("INVALID\n");
    }
        // MASTERCARD\n (51, 52, 53, 54, or 55) - 16-digit
    else if ((first2Digit <= 55 && first2Digit >= 51) && numberOfDigit == 16)
    {
        printf("MASTERCARD\n");
    }
        // AMEX\n (34 37) - 15-digit
    else if ((first2Digit == 37 || first2Digit == 34) && numberOfDigit == 15)
    {
        printf("AMEX\n");
    }
        // get the first number to check - VISA\n (4) 13- and 16-digit
    else if ( (((first2Digit - (first2Digit % 10)) / 10) == 4) && (numberOfDigit == 13 || numberOfDigit == 16))
    {
        printf("VISA\n");
    }
        // if none of the above then INVALID\n
    else
    {
        //printf("Doesn't fit in any other category\n");
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
            if(lastExtractedDigit > 9){
                digitSum += (lastExtractedDigit % 10);
                lastExtractedDigit = (lastExtractedDigit - (lastExtractedDigit % 10)) /10;
            }
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

int getNumberOfDigit(long cardNumber){
    int numberOfDigit = 0;
    while (cardNumber > 0)
    {
        int lastExtractedDigit = cardNumber % 10;
        cardNumber = (cardNumber - lastExtractedDigit) / 10;
        numberOfDigit++;
    }
    return numberOfDigit;
}