#include<stdio.h>
#include"sqlite/sqlite3.h"
#include<string.h>
#include<stdlib.h>

//get pinyin meaning and example
//tomorrow the pinyin and translatation plus create the data structure to store these data.



typedef  struct {
  char *hanzi;
  char *english;
  char *sentence;
} dict_cell;

static dict_cell hanzi_data;
static sqlite3 *db;
static int rc;


int checkDB(char* fileName){
  //open a connection to the data base.
  char *user_entry;

  rc = sqlite3_open(fileName, &db);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database %s\n", sqlite3_errmsg(db));
    return 1;
  }
  return 0;
}
static int callback(void* data, int argc, char** argv, char** azColName) {
  //get the retrieved data from db and stores it dinamically in hanzi_data struct

  //space complexity O(n)
  hanzi_data.hanzi = malloc(strlen(argv[0]) * sizeof(char));
  hanzi_data.sentence = malloc(strlen(argv[1]) * sizeof(char));
  hanzi_data.english = malloc(strlen(argv[2]) * sizeof(char));
  
  strncpy(hanzi_data.hanzi, argv[0], strlen(argv[0]));
  strncpy(hanzi_data.sentence, argv[1], strlen(argv[1]));
  strncpy(hanzi_data.english, argv[2], strlen(argv[2]));

  return 0;
    
}

int prepQuery(char hanzi[2]) { 
  //prepare the query string to find the hanzi and check its syntax
  char *err_msg = 0;
  sqlite3_stmt *stmt;
  char  query[250];
  //potentially customazible
  snprintf(query, sizeof(query),"SELECT DISTINCT pinyin, simplified, english FROM examples WHERE simplified LIKE '%s%s%s' AND LENGTH(simplified) <= 30  AND  english IS NOT NULL ORDER BY pinyin ASC LIMIT 1%s", "%",hanzi, "%", ";");
  
    char *sql = query;
    
    printf("\n%s\n", query);
    
    if (rc != SQLITE_OK){
      printf("\nQuery failed!\n");
    }
    
    else{
      printf("\nQuery sucessed!\n");
    }

    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    } 
    
    
  return 0;
}


int main(){
  //int rc;
  int checkDB(char fileName[]);
  int prepQuery(char hanzi[2]);
  char user_input[10];

  printf("Please insert the chinese word/pinyin/english word:");
  fgets(user_input, 9, stdin);
  user_input[strcspn(user_input, "\n")] = 0;
  
  printf("%s\n", user_input);
  if (checkDB("sen_data.db") == 0) {
    printf("Database successfully connected!!\n");
    prepQuery(user_input);
    printf("--------------------------------\n");
    printf("\n1:%s\n2:%s\n3:%s\n", hanzi_data.hanzi, hanzi_data.sentence, hanzi_data.english);
 
    free(hanzi_data.hanzi);
    free(hanzi_data.sentence);
    free(hanzi_data.english);
};

    return 0;
}

