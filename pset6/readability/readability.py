"""
readability.py: This program rate the text grade
"""
__author__ = "Brice Bartoletti"

if __name__ == "__main__":
    text = str(input("Text: "))

    letter = 0
    # word start at 1 because the last word is never counted
    word = 1
    sentence = 0
    textLength = len(text)

    for char in text:
        if char.isalpha():
            letter += 1
        elif char.isspace():
            word += 1
        elif char in ('.', '!', '?'):
            sentence += 1

    # Coleman-Liau Index : 0.0588 * (avg length for 100 words) - 0.96 * (avg Sentences for 100 words) - 15.8
    # index = 0.0588 * L - 0.296 * S - 15.8
    # where L is the average number of letters per 100 words in the text, and S is the average number of sentences
    # per 100 words in the text.
    avgLength = float(letter) / word * 100
    avgSentence = float(sentence) / word * 100

    grade = round(0.0588 * avgLength - 0.296 * avgSentence - 15.8)

    if grade < 1:
        print("Before Grade 1")
    elif grade > 15:
        print("Grade 16+")
    else:
        print(f'Grade {grade}')
