#include "User.hpp"
#include "Utils.hpp"
//#include "Dependencies/Bcrypt/BCrypt.hpp"

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


    //std::string right_password = "abcde";
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

//#include <SFML/Graphics.hpp>
//#include <filesystem>
//#include <vector>
//#include <string>
//#include <iostream>
//
//// Namespace alias for easier filesystem handling
//namespace fs = std::filesystem;
//
//int main() {
//    // Create the SFML window
//    sf::RenderWindow window(sf::VideoMode(800, 600), "Simple File Dialog");
//
//    // Font for rendering text
//    sf::Font font;
//    if (!font.loadFromFile("Font/simhei.ttf")) {
//        std::cerr << "Error loading font" << std::endl;
//        return -1;
//    }
//
//    // Get the list of files in the current directory
//    std::vector<sf::Text> fileEntries;
//    int yOffset = 0;
//
//    for (const auto& entry : fs::directory_iterator(".")) {
//        sf::Text text;
//        text.setFont(font);
//        text.setString(entry.path().filename().string());
//        text.setCharacterSize(24);
//        text.setFillColor(sf::Color::White);
//        text.setPosition(10, yOffset);
//        fileEntries.push_back(text);
//        yOffset += 30; // Spacing between file entries
//    }
//
//    std::string selectedFile;
//
//    // Main loop
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//
//            if (event.type == sf::Event::MouseButtonPressed) {
//                if (event.mouseButton.button == sf::Mouse::Left) {
//                    for (auto& fileEntry : fileEntries) {
//                        if (fileEntry.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
//                            selectedFile = fileEntry.getString();
//                            std::cout << "Selected file: " << selectedFile << std::endl;
//                            // Here you could load the selected file or do something else with it
//                        }
//                    }
//                }
//            }
//        }
//
//        // Clear the window
//        window.clear(sf::Color::Black);
//
//        // Draw file entries
//        for (auto& fileEntry : fileEntries) {
//            window.draw(fileEntry);
//        }
//
//        // Display the window
//        window.display();
//    }
//
//    return 0;
//}