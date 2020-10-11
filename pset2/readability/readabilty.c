#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int test(string text)
{
    //    string text = "When he was nearly thirteen, my brother Jem got his arm badly broken at the elbow. When it healed, and Jem's fears of never being able to play football were assuaged, he was seldom self-conscious about his injury. His left arm was somewhat shorter than his right; when he stood or walked, the back of his hand was at right angles to his body, his thumb parallel to his thigh.";
    //string text = get_string("Text: ");

    int letter = 0;
    // word start at 1 because the last word is never counted
    int word = 1;
    int sentence = 0;
    int textLength = strlen(text);

    for (int i = 0; i < textLength; ++i)
    {
        if (isalnum(text[i]))
        {
            letter++;
            //printf("%c", text[i]);
        }
        else if ((int) text[i] == ' ')
        {
            word++;
            //printf("%d%c", word, text[i]);
        }
        else if (((int) text[i] == (int) '.') || ((int) text[i] == (int) '!') || ((int) text[i] == (int) '?'))
        {
            sentence++;
            //printf("%c\n", text[i]);
        }

    }

    // Coleman-Liau Index : 0.0588 * (avg length for 100 words) - 0.96 * (avg Sentences for 100 words) - 15.8
    // index = 0.0588 * L - 0.296 * S - 15.8
    // where L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.
    double avgLength = ((double) letter / word) * 100;
    double avgSentence = ((double) sentence / word) * 100;

    int grade = round((0.0588 * avgLength) - (0.296 * avgSentence) - 15.8);
    //printf("textLength: %d\nletter: %d word: %d sentence: %d\ngrade : %d\navgLenght: %f avgSentence: %f\n", textLength,
    //       letter, word, sentence, grade, avgLength, avgSentence);

    printf("letters: %d, words: %d, sentences: %d\n", letter, word, sentence);
    printf("avgLength: %f, avgSentence: %f\n", avgLength, avgSentence);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }

    return 0;
}

int main(void)
{
    test("One fish. Two fish. Red fish. Blue fish.");
    printf("should be: Before Grade 1\n");
    test("Would you like them here or there? I would not like them here or there. I would not like them anywhere.");
    printf("should be: Grade 2\n");
    test("Congratulations! Today is your day. You're off to Great Places! You're off and away!");
    printf("should be: Grade 3\n");
    test("Harry Potter was a highly unusual boy in many ways. For one thing, he hated the summer holidays more than any other time of year. For another, he really wanted to do his homework, but was forced to do it in secret, in the dead of the night. And he also happened to be a wizard.");
    printf("should be: Grade 5\n");
    test("In my younger and more vulnerable years my father gave me some advice that I've been turning over in my mind ever since.");
    printf("should be: Grade 7\n");
    test("When he was nearly thirteen, my brother Jem got his arm badly broken at the elbow. When it healed, and Jem's fears of never being able to play football were assuaged, he was seldom self-conscious about his injury. His left arm was somewhat shorter than his right when he stood or walked, the back of his hand was at right angles to his body, his thumb parallel to his thigh.");
    printf("should be: Grade 8\n");
    test("There are more things in Heaven and Earth, Horatio, than are dreamt of in your philosophy.");
    printf("should be: Grade 9\n");
    test("It was a bright cold day in April, and the clocks were striking thirteen. Winston Smith, his chin nuzzled into his breast in an effort to escape the vile wind, slipped quickly through the glass doors of Victory Mansions, though not quickly enough to prevent a swirl of gritty dust from entering along with him.");
    printf("should be: Grade 10\n");
    test("A large class of computational problems involve the determination of properties of graphs, digraphs, integers, arrays of integers, finite families of finite sets, boolean formulas and elements of other countable domains.");
    printf("should be: Grade 16+\n");
}