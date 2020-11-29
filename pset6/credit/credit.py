"""
credit.py: This program check if a credit card number is valid and if yes output from which organization it is
"""
__author__ = "Brice Bartoletti"

if __name__ == "__main__":
    # get input until it is valid
    strCardNumber = str()
    while True:
        try:
            strCardNumber = str(int(input("enter your card number: ")))
            break
        except ValueError:
            continue

    # get 2 last digit for organization identification
    first2Digit = int(strCardNumber[:2])
    numberOfDigits = len(strCardNumber)

    # CheckSum : multiply by digit by 2 starting from the end for odd index and add all digits together
    checkSum = sum([
        2 * int(v) % 10 + 2 * int(v) // 10 if i % 2 != 0 else int(v)
        for i, v in enumerate(strCardNumber[::-1])
    ])

    # verifies the numbers depending on the organisation
    if checkSum % 10 != 0:
        print("INVALID")
    elif first2Digit in range(51, 56) and numberOfDigits == 16:
        print("MASTERCARD")
    elif first2Digit in (34, 37) and numberOfDigits == 15:
        print("AMEX")
    elif int(str(first2Digit)[0]) == 4 and (numberOfDigits in (13, 16)):
        print("VISA")
    else:
        print("INVALID")
