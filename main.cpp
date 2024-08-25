#include "User.hpp"
#include "Utils.hpp"

int main()
{
    loadDataBase();
    insertDatas("Database/insertBookInfoSql.txt");

    User user1;
    //std::vector<Book> books = user1.searchBooksInfoByName(L"了", L"传记与回忆录");
    user1.run();

    

    closeDataBase();
    return 0;
}