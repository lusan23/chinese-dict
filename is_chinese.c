#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<wchar.h>
#include<stdbool.h>

//it needs to handle special characters inputs
int is_chinese(char  string[12]) {
  /*if the string is the alphabet and your*/
  bool  it_is = false;
  wchar_t cc[13];
  swprintf(cc, 12, L"%ls", string);

  wchar_t hanziStart = 0x4E00;
  wchar_t hanziEnd = 0x9FFF;

  int size = wcslen(cc);

  for (int i = 0; i <size; i++) {
    if (cc[i] >= hanziStart && cc[i] <= hanziEnd) {
      it_is = true;
    } else {it_is = false;}
  }
  if (it_is) {return 0;} else {return -1;}
}
int main(){
  char  input[12];
  fgets(input, 12, stdin);
  input[strcspn(input, "\n")] = 0;
  if (is_chinese(input)) {printf("é hanzi carai.\n");}
  
  return 0;
}
