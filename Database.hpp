#include "Dependencies/sqlite3/sqlite3.h"

const char* const INSERT_BOOK_INFO_SQLCMD_FILE = "Database/insertBookInfoSql.txt";
const char* const INSERT_USER_ACC_SQLCMD_FILE = "Database/insertUserAccSql.txt";

const char* const CREATE_BOOK_INFO_TABLE_SQLCMD = "CREATE TABLE IF NOT EXISTS `book_info` ( \
									`id` INT(11) NOT NULL , \
									`book_name` varchar(200) DEFAULT NULL , \
									`author` varchar(50) DEFAULT NULL , \
									`publishing_house` varchar(50) DEFAULT NULL , \
									`translator` varchar(50) DEFAULT NULL , \
									`publish_date` date DEFAULT NULL , \
									`pages` int(10) DEFAULT '100' , \
									`ISBN` varchar(20) DEFAULT NULL , \
									`price` double DEFAULT '1' , \
									`brief_introduction` varchar(15000) DEFAULT '' , \
									`author_introduction` varchar(5000) DEFAULT '' , \
									`img_url` varchar(200) DEFAULT NULL , \
									`del_flg` int(1) DEFAULT '0' , \
									PRIMARY KEY(`id`) \
									);";


class Database
{
	public:
		Database();
		~Database();
		bool addUser();
		bool modifyUser();
		bool deleteUser();
		void getUserData();
		bool addBook();
		bool modifyBook();
		bool deleteBook();
		void getBookData();
		void findBook();

	private:
		sqlite3* mDatabase;
		static int callback(void* index, int coloums, char** head, char** data);
		bool createTable(const char *sqlCmd);
		bool insertData(const char* filename);
};