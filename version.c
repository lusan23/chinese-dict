#include "/usr/include/mysql/mysql.h"
#include <stdio.h>
#include <stdlib.h>

int  readDB(FILE * file) {
  if ((*file) == NULL) {
    fprintf(stderr, "Cannot open SQL file\n");
    return 1;
  } else {printf("SQL file opened!!!\n");}
  return 0;
}


int main () {
   FILE  *file = fopen("sen_data.db", "r");
  
  readDB(file);
}
