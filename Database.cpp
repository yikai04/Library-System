#include "Database.hpp"
#include "Config.h"
#include <iostream>
#include <fstream>
#include <string>

Database::Database()
{
    int rc;
    rc = sqlite3_open(DATABASE_FILE, &mDatabase);

    if (rc) {
        std::cout << "Can't open database : " << sqlite3_errmsg(mDatabase) << std::endl;
    }
    else {
        std::cout << "Opened database successfully" << std::endl;
    }
    //int a = 1;
    //rc = sqlite3_exec(mDatabase, "SELECT img_url FROM book_info;", callback, &a, NULL);

    //if (rc) {
    //    std::cout << "Failed : " << sqlite3_errmsg(mDatabase) << std::endl;
    //}
    //else {
    //    std::cout << "Sucess" << std::endl;
    //}

    //rc = sqlite3_exec(mDatabase, "", callback, &a, NULL);

    //if (rc) {
    //    std::cout << "Failed : " << sqlite3_errmsg(mDatabase) << std::endl;
    //}
    //else {
    //    std::cout << "Sucess" << std::endl;
    //}

    std::cout << createTable(CREATE_BOOK_INFO_TABLE_SQLCMD);
}

Database::~Database()
{
    sqlite3_close(mDatabase);
}

int Database::callback(void* index, int coloums, char** data, char** head)
{
    std::ofstream fout("output.txt");
    fout << "Index: " << *(int*)index << std::endl;
    fout << "Coloums: " << coloums << std::endl;
    
    for (int i = 0; i < coloums; i++) {
        fout << "Head: " << head[i] << std::endl;
        fout << "Data: " << data[i] << std::endl;
    }
    fout.close();

    return SQLITE_OK;
}

bool Database::addBook()
{
    int rc;
    rc = sqlite3_exec(mDatabase, "INSERT INTO books", NULL, NULL, NULL);

    if (rc) {
        return false;
    }
    else {
        return true;
    }
}

void Database::getBookData()
{

}

bool Database::createTable(const char *sqlCmd)
{
    int rc = 1;
    rc = sqlite3_exec(mDatabase, sqlCmd, NULL, NULL, NULL);

    if (rc) {
        std::cout << "Failed : " << sqlite3_errmsg(mDatabase) << std::endl;
        return false;
    }
    else {
        return true;
    }
}

bool Database::insertData(const char* filename)
{
    int rc = 1;
    char sqlCmd[10000];
    std::ifstream fin(filename, std::ios_base::in);
    
    if (!fin) {
        std::cerr << "Can't open input.txt" << std::endl;
        return false;
    }

    while (fin.getline(sqlCmd, 10000)) {
        
        rc = sqlite3_exec(mDatabase, sqlCmd, NULL, NULL, NULL);

        if (rc) {
            std::cout << "Failed : " << sqlite3_errmsg(mDatabase) << std::endl;
            return false;
        }

    }

    return true;
}