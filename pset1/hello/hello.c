#include <stdio.h>
//#include <cs50.h>

int main(void) {
    // Get an input
//    string name = get_string("What is your name?\n");
    char name[20];
    printf("What is your name ?\n");
    scanf("%s", &name);

    // output
    printf("hello, %s\n", name);
}

char* getStringMax120(char *message){
    printf("%s", message);
    char input[120];
    scanf("%s", &input);
    int i = 0;
    while(*(input+i) != "\0")
        i++;
    char str[i];

}