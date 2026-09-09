//gcc -o addcol addcol-sqlite.c  -Wall `pkg-config --libs --cflags  sqlite3`

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <gtk/gtk.h>
#include <sqlite3.h>

int execdb( char * sql,char tt);

/*
CREATE TABLE Cli (
	Clefacc VARCHAR(12),
	Type VARCHAR(2),
	Add1 VARCHAR(50),
	Add2 VARCHAR(50),
	Add3 VARCHAR(50),
	Pays VARCHAR(4),
	Codpos VARCHAR(8),
	Add4 VARCHAR(40),

	Datcre VARCHAR(12),
	Datmod VARCHAR(12),
	Tel VARCHAR(18),
	Mail VARCHAR(40),
	Notes BLOB
);
*/
#define DIMNOTES 256
#define DIMNOCLI 512

sqlite3 *db,*dbold;
char *zErrMsg = 0;
char sqlist[]="SELECT * FROM Cli ORDER BY rowid";
static char sqlins_fcli[]="INSERT INTO Cli VALUES('%s','%s',\"%s\",\"%s\",\"%s\",'%s','%s',\"%s\", '%s','%s','%s','%s','%s',\"%s\")";

// retour de insert et maj pour toutes les tables
static int callbackmaj(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  for(i=0; i<argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}
static char zl[1024];
static int callback_p(void *pArg, int argc, char **argv, char **azColName)
{
int rc;
printf("%s\t",argv[0]);
printf("%s\t",argv[2]);
printf("%s\n",argv[3]);

 sprintf(zl,sqlins_fcli,
argv[0],argv[1],argv[2],argv[3],argv[4],argv[5],argv[6],argv[7],"siret",
argv[8],argv[9],argv[10],argv[11],argv[12],argv[13]);
rc = sqlite3_exec(db, zl,callbackmaj, 0, &zErrMsg); //maj
  if( rc!=SQLITE_OK ) {
  fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
 		 }

  return 0;
}


void listdb()
{
int rc;
rc = sqlite3_exec(dbold, sqlist, callback_p, 0, &zErrMsg);
  if( rc!=SQLITE_OK ) {
  fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
 		 }
}

int main(int argc, char **argv)
{
int rc;
if( argc!=3 ){
  fprintf(stderr, "Usage: %s DB-OLD DB-NEW  \n", argv[0]);
  return (1);
        	  }
rc = sqlite3_open(argv[1], &dbold);
if( rc ){
  fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(dbold));
  sqlite3_close(dbold);
  return (1);//exit(1);
	  }
rc = sqlite3_open(argv[2], &db);
if( rc ){
  fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
  sqlite3_close(db);
  return (1);//exit(1);
	  }

listdb();
  sqlite3_close(dbold);
  sqlite3_close(db);

    return EXIT_SUCCESS;
}

