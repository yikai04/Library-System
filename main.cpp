#include "User.hpp"
#include "Utils.hpp"
#include "Dependencies/Bcrypt/BCrypt.hpp"

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

    //std::string right_password = "right_password";
    //std::string wrong_password = "wrong_password";
    //std::cout << "generate hash... " << std::flush;
    //std::string hash = BCrypt::generateHash(right_password, 12);
    //std::cout << hash << " done." << std::endl;
    //std::cout << "checking right password: " << std::flush
    //    << BCrypt::validatePassword(right_password, hash) << std::endl;
    //std::cout << "checking wrong password: " << std::flush
    //    << BCrypt::validatePassword(wrong_password, hash) << std::endl;

    closeDataBase();
    return 0;
}