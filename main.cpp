#include "User.hpp"
#include "Utils.hpp"

int main()
{
    if (!loadDataBase()) {
        return 1;
    }
    insertDatas("Database/insertUserInfoSql.txt");
    insertDatas("Database/insertBookInfoSql.txt");
    insertDatas("Database/insertBorrowInfoSql.txt");

    User user1;
    user1.run();



    closeDataBase();
    return 0;
}