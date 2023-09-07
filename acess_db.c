#include<stdio.h>
#include"sqlite/sqlite3.h"
#include<string.h>

//#include"sqlite/sqlite3ext.h"
//get pinyin meaning and example
//CREATE A CALLBACK FUNCTION TO PRINT THE RESULT FROM SQLITE3_EXEC

int connDB(char* fileName, int *rc){
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


int makeQuery(int *rc, char hanzi[]) {
  sqlite3 *db;
  sqlite3_stmt *stmt;
  char query[] = "SELECT pinyin, simplified, english FROM examples WHERE simplified LIKE ";
  strncat(query, "%", 1);
  strncat(query, hanzi, 1); 
  strncat(query, "%;", 2);
  //char *sql = query;
  printf("%s", query);
  return 0;
}

int main(){
  int rc;
  int connDB(char fileName[], int *rc);
  int makeQuery(int *rc, char hanzi[]);
  if (connDB("sen_data.db", &rc) == 0) {
    printf("Database successfully connected!\n");
    makeQuery(&rc, "爱");
 
 
};

  
  /*
  //prepares a sql query statment
  sqlite3_stmt *stmt;
  char *sql = "SELECT pinyin, simplified, english FROM examples WHERE simplified LIKE '%%s%'";
  char *errMsg;
  rc = sqlite3_prepare_v2(db, sql, -1, &stmt ,&errMsg);

  if (rc != SQLITE_OK) {fprintf(stderr, "SQL error:%s\n", errMsg);}

  */
    return 0;
}

