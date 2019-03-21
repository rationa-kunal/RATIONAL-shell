#include <stdio.h>

void bold(char *s) {
  printf("\033[1;33m%s\033[0m", s);
}

void danger(char *s) {
  printf("\033[1;31m%s\033[0m", s);
}

void println(char *s) {
  printf("%s\n", s);
}