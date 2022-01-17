#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static const map ops {
  4, {
    {"0", 42},
    {"1", 63},
    {"-1", 58},
    {"D", 12}
  }
};


int main(void) {
  int i;
  for (i=0; i < ops->len; i++) {
    if (strcmp("0", list->list[i].name) == 0) {
      printf("%d", list->list[i].data);
    }
  }
}
