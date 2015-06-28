#include <stdio.h>

void print_hex(const char *s)
{
  while(*s)
    printf("%02x", (unsigned int) *s++);
  printf("\n");
}

int main(int argc, char* argv[])
{
  char* str = "abc";
  printf("%s\n", str);
  print_hex(str);
  printf("%x\n", str[0]);
  printf("%x\n", str[1]);
}
