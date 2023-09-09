#include<stdio.h>
#include"sqlite/sqlite3.h"
#include<string.h>
#include<wchar.h>
//#include"sqlite/sqlite3ext.h"
//get pinyin meaning and example
//FIX THE PROBLEM WITH THE QUERY CONCACTENATION AND FINISH THE MAKEQUERY FUNCTION SO THAN I CAN CONVERT THAT RAW DATA

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
    //data oiubter ti yser0defubed data that you can pass to the callback function
  //argc the number of columna in the result set.
  //arv an array of strings representing the values of each column in the current row.
  //azColName an array 
  for (int i = 0; i < argc; i++){
    
    if (i == 1 && strlen(argv[i]) <= 50 ) {
      printf("argv[%d]:%s\n",i,argv[i]);
      
    
    }
  }
  return 0;
    
}

int prepQuery(char hanzi[2]) { 
  //prepare the query to find the hanzi and sent it to the db
  sqlite3 *db;
  char *err_msg = 0;
  sqlite3_stmt *stmt;
  char  query[80];
  snprintf(query, sizeof(query),"SELECT pinyin, simplified, english FROM examples WHERE simplified LIKE '%s%s%s'%s", "%",hanzi, "%", ";");
  
    char *sql = query;
    //coconnDB("sen_data.db", &(*rc));
    //(*rc) = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    int rc = sqlite3_open("sen_data.db", &db);
    printf("%s", query); 
    if (rc != SQLITE_OK){ printf("\nQuery failed!\n");} else {printf("\nQuery sucessed\n!");}

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
  int checkDB(char fileName[], int *rc);
  int prepQuery(char hanzi[2]);
  if (checkDB("sen_data.db", &rc) == 0) {
    printf("Database successfully connected!!\n");
    prepQuery("爱");
 
 
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

