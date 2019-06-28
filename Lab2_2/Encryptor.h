	/** @file
	 *  @author Шеманаев К.А.
	 *  @version 1.0
	 *  @date 14.06.2019
	 *  @brief файл заголовком класса Encryptor
	 */
	 
#pragma once

#include <string>
#include <map>

class Encryptor {
public:
	std::string encrypt(std::string in, const int key);
	std::string decrypt(std::string in, const int key);
private: 
	void isInvalidKey(std::string in, const int key);
	void isInvalidMsg(std::string in, const int key);

};

class encryptException: public std::invalid_argument {
	
public:
    explicit encryptException (const std::string& what_arg): //explicit запрещает компилятору приравнивать "Object a = 5" и "Object a(5)".
														//Делает доступным только второе
        std::invalid_argument(what_arg) {}
    explicit encryptException (const char* what_arg):
        std::invalid_argument(what_arg) {}
};