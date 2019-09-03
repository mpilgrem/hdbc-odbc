#include "hdbc-odbc-helper.h"
#include <sqlext.h>
#include <stdio.h>
#include <stdlib.h>

SQLLEN nullDataHDBC = SQL_NULL_DATA;

int sqlSucceeded(SQLRETURN ret) {
  return SQL_SUCCEEDED(ret);
}

void *getSqlOvOdbc3(void) {
  return (void *)SQL_OV_ODBC3;
}

SQLRETURN simpleSqlTables(SQLHSTMT stmt, SQLCHAR *tabletype,
                          SQLSMALLINT ttlen) {
  return SQLTables(stmt, NULL, 0, NULL, 0, (SQLCHAR *)"%", 1, tabletype, ttlen);
}

/* Microsoft's ODBC documentation states that if TableType is
SQL_ALL_TABLE_TYPES (that is, "%") and CatalogName, SchemaName, and TableName
are empty strings (see below), the result set contains a list of valid table
types for the data source. (All columns except the TABLE_TYPE column contain
NULLs.)

Empty strings are not NULL pointers.*/
SQLRETURN simpleSqlTableTypes(SQLHSTMT stmt) {
  return SQLTables(stmt, (SQLCHAR *)"", 0, (SQLCHAR *)"", 0, (SQLCHAR *)"", 0,
                   (SQLCHAR *)"%", 1);
}

SQLRETURN simpleSqlColumns(SQLHSTMT stmt, SQLCHAR *tablename,
                           SQLSMALLINT tnlen) {
  return SQLColumns(stmt, NULL, 0, NULL, 0, tablename, tnlen, (SQLCHAR *)"%", 1);
}
