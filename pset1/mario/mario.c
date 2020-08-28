// refactored with recursion and in loop declaration
#include <stdio.h>
#include <cs50.h>

int promptForHeight(void);
void draw(int n, int height);

int main(void)
{
    int height = promptForHeight();
    int lineSize = (height * 2) + 2;

    // draw the whole pyramid
    draw(height, height);

}

/**
 * Function that prompt for a valable height
 */
int promptForHeight(void)
{
    int height;
    do
    {
        // prompt user for height
        height = get_int("Height: ");
        printf("\n");
        // check if height is between 1 and 8
    }
    while (height < 1 || height > 8);
    return height;
}

void draw(int n, int height)
{
    // base case: nothing to draw
    if (n == 0)
    {
        return;
    }
    // draw previous line
    draw(n - 1, height);
    // if not base case
    for (int i = 0, k = height - n; i < k; ++i)
    {
        printf(" ");
    }
    for (int i = 0; i < n; ++i)
    {
        printf("#");
    }
    for (int i = 0; i < 2; ++i)
    {
        printf(" ");
    }
    for (int i = 0; i < n; ++i)
    {
        printf("#");
    }
    printf("\n");
}


// First attempt

//#include <stdio.h>
//#include <cs50.h>
//
//int promptForHeight(void);
//
//int main(void)
//{
//    int height = promptForHeight();
//    int lineSize = (height * 2) + 2;
//
//    // draw the whole pyramid
//    for (int i = 0; i < height; i++)
//    {
//        // variables used to calculate the number of required space and fence
//        int nbSpace = height - i - 1;
//        int nbSharp = height - nbSpace;
//        // draw the line
//        for (int j = 0; j < lineSize; j++)
//        {
//            if (j < nbSpace)
//            {
//                printf(" ");
//            }
//            else if (j < (nbSpace + nbSharp))
//            {
//                printf("#");
//            }
//            else if (j < (nbSpace + nbSharp + 2))
//            {
//                printf(" ");
//            }
//            else if (j < (nbSpace + (2 * nbSharp) + 2))
//            {
//                printf("#");
//            }
//        }
//        // end of the line: carryback
//        printf("\n");
//    }
//
//}
//
///**
// * Function that prompt for a valable height
// */
//int promptForHeight(void)
//{
//    int height;
//    do
//    {
//        // prompt user for height
//        height = get_int("Heith: ");
//        printf("\n");
//        // check if height is between 1 and 8
//    }
//    while (height < 1 || height > 8);
//    return height;
//}