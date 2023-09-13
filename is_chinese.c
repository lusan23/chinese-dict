#include<stdio.h>
#include<string.h>
#include <ctype.h>

//it needs to handle special characters inputs
int is_chinese(char string[12]) {
  /*if the string is the alphabet and your*/
  int it_is;
  for (int i = 0; string[i] != '\0'; i++) {
    
    if (!isalpha(string[i]) ){
      if (!isdigit(string[i])) {
	if ((sizeof(char) * strlen(string)) % 3 == 0) {
	  it_is = 1;
      
      }}
    else{
        it_is = 0;
      }
  }
  } if (it_is == 1) {return 0;} else {return 1;}
}
int main(){
  char  input[12];
  scanf("%s", input);
  printf("%d", is_chinese(input));
  
  return 0;
}
