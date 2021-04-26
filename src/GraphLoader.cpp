//
// Created by pedro on 26/04/21.
//

#include "GraphLoader.h"

static int callback(void *data, int argc, char **argv, char **azColName){
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for(i = 0; i<argc; i++){
        if(strcmp(argv[i], ""))
            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

void GraphLoader::loadMap(string filename) {
    const char* filenameC = filename.c_str();
    sqlite3 *db;

    char *zErrMsg = 0;
    int rc;
    char *sql;
    const char* data = "Callback function called";
    /* Open database */
    rc = sqlite3_open(filenameC, &db);
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }

    /* Create SQL statement */
    sql = (char*)"SELECT name from roads";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Operation done successfully\n");
    }

    sqlite3_close(db);
}