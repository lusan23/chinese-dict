#include<stdio.h>
#include"sqlite/sqlite3.h"
#include<string.h>
#include<wchar.h>
//#include"sqlite/sqlite3ext.h"
//get pinyin meaning and example
//tomorrow the pinyin and translatation plus create the data structure to store these data.

typedef  struct {
  char hanzi[70];
  char english[70];
  char sentence[70];
} dict_cell;

static dict_cell hanzi_data;

int checkDB(char* fileName, int *rc){
  //open a connection to the data base.
  sqlite3 *db;
  char *user_entry;

  (*rc) = sqlite3_open(fileName, &db);

  if ((*rc) != SQLITE_OK) {
    fprintf(stderr, "Cannot open database %s\n", sqlite3_errmsg(db));
    return 1;
  }
  return 0;
}
static int callback(void* data, int argc, char** argv, char** azColName) {
  //argc the number of columna in the result set.
  //arv an array of strings representing the values of each column in the current row.
  //azColName an array
  //show me the sentence, pinyin and meaning of the example

  //store the info on the static variable
  strncpy(hanzi_data.hanzi, argv[0], sizeof(hanzi_data.hanzi));
  strncpy(hanzi_data.sentence, argv[1], sizeof(hanzi_data.sentence));
  strncpy(hanzi_data.english, argv[2], sizeof(hanzi_data.english));
  
  return 0;
    
}

int prepQuery(char hanzi[2]) { 
  //prepare the query to find the hanzi and sent it to the db
  sqlite3 *db;
  char *err_msg = 0;
  sqlite3_stmt *stmt;
  char  query[200];
  snprintf(query, sizeof(query),"SELECT pinyin, simplified, english FROM examples WHERE simplified LIKE '%s%s%s' AND english IS NOT NULL ORDER BY pinyin ASC LIMIT 1%s", "%",hanzi, "%", ";");
  
    char *sql = query;

    int rc = sqlite3_open("sen_data.db", &db);
    printf("\n%s\n", query); 
    if (rc != SQLITE_OK){ printf("\nQuery failed!\n");}
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
  int rc;
  int checkDB(char fileName[], int * rc);
  int prepQuery(char hanzi[2]);
  char user_input[4];

  printf("Please insert the chinese word you are looking for:");
  scanf("%s", user_input);
  
  if (checkDB("sen_data.db", &rc) == 0) {
    printf("Database successfully connected!!\n");
    prepQuery(user_input);

    printf("\n%s\n%s\n%s\n", hanzi_data.hanzi, hanzi_data.sentence, hanzi_data.english);
 
 
};

    return 0;
}

