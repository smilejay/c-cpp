#include <stdio.h>
#include <string.h>

void reverse(char *s, int left, int right)
{
    while (left < right) {
        char c = s[left];
        s[left] = s[right];
        s[right] = c;
        left += 1;
        right -= 1;
    }
}

/* reverse2: reverse a string using no extral varible */
void reverse2(char *s, int left, int right)
{
    while (left < right) {
        s[left] ^= s[right];
        s[right] ^= s[left];
        s[left] ^= s[right];
        left += 1;
        right -= 1;
    }
}

void reverseWords(char *s)
{
    int start = 0;
    for(int i=0; i<=strlen(s); i++)
    {
        if(s[i] == ' ' || s[i] == '\0')
        {
            // reverse(s, start, i-1);
            reverse2(s, start, i-1);
            start = i+1;
        }
    }
    // reverse(s, 0, strlen(s) - 1 );
    reverse2(s, 0, strlen(s) - 1 );
}

int main(int argc, char const *argv[])
{
    // char my_str[] = "hello, this is Tom";
    char my_str[] = "  hello world!  ";
    // reverse(my_str, 0, strlen(my_str) - 1);
    reverseWords(my_str);
    printf("%s\n", my_str);
    return 0;
}