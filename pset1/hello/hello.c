#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Get an input
    string name = get_string("What is your name?\n");
    // output
    printf("hello, %s\n", name);
}