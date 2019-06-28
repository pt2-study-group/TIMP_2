	/** @file
	 *  @author Шеманаев К.А.
	 *  @version 1.0
	 *  @date 14.06.2019
	 *  @brief файл с реализацией класса Encryptor
	 */
	 
#include "Encryptor.h"
#include <iostream>
#include <string>

using namespace std;
	/**
     * @brief Зашифровывание
     * @param [in] in Открытый текст. Не должен быть пустой строкой.
     *                       Строчные символы автоматически преобразуются к прописным.
     *                       Все не-буквы удаляются
     * @return Зашифрованная строка
     * @throw encryptException, если текст пустой
     */
string Encryptor::encrypt(string in, const int key) {
	isInvalidMsg(in, key);
	isInvalidKey(in, key);

	int array_size = in.length();
	int array_height = (array_size/key) + ((array_size%key > 0) ? 1 : 0);
	int lower_string_lenght = in.length()%key;
	int kolvo_zvezd = (lower_string_lenght > 0) ? key - lower_string_lenght : 0;
	
	char ** matrix = new char*[array_height]; for (int i =0; i<array_height; i++) matrix[i] = new char[key];
	
	std::string output;
	
	for (int i = 0; i < kolvo_zvezd; i++) {
		matrix[array_height-1][(key-1)-i] = '*';
	}
	
	int charId = 0;
	for (int i = 0; i < array_height; i++) { //по строке
		for (int j = 0; j < key; j++){ //по столбикам
			if (matrix[i][j] == '*') continue;

			matrix[i][j] = in.at(charId);
			charId++;
		}
	}
	
	
	for (int i = 0; i < key; i++) { //по строке
		for (int j = 0; j < array_height; j++){ //по столбикам
			if (matrix[j][(key-1)-i] == '*') continue;
				output+=matrix[j][(key-1)-i];
		}
	}

	for (int i = 0; i < array_height; i++) delete[] matrix[i];
	delete[] matrix;
	return output;
}
	/**
     * @brief Расшифрование
     * @param [in] in Закрытый текст. Не должен быть пустой строкой.
     *                       Строчные символы автоматически преобразуются к прописным.
     *                       Все не-буквы удаляются
     * @return Расшифрованная строка строка
     * @throw encryptException, если текст пустой
     */
string Encryptor::decrypt(string in, const int key) {
	isInvalidMsg(in, key);	
	isInvalidKey(in, key);

	
	int array_height = (in.length()/key) + ((in.length()%key > 0) ? 1 : 0);
	int lower_string_lenght = in.length()%key;
	int kolvo_zvezd = (lower_string_lenght > 0) ? key - lower_string_lenght : 0;

	char ** matrix = new char*[array_height]; for (int i =0; i<array_height; i++) matrix[i] = new char[key];

	std::string output;

	for (int i = 0; i < array_height; i++) { //по строке
		for (int j = 0; j < key; j++){ //по столбикам
			matrix[i][j] = '\0';
		}
	}
	//Записываем в матрицу звезды
	for (int i = 0; i< kolvo_zvezd; i++) {
		matrix[array_height-1][(key-1)-i] = '*';
	}

	int charId = 0;
	for (int i = 0; i < key; i++) { //по строке
		for (int j = 0; j < array_height; j++){ //по столбикам
			if (matrix[j][(key-1)-i] == '*') continue;
			
			matrix[j][(key-1)-i] = in.at(charId);
			charId++;
		}
	}
	
	for (int i = 0; i < in.length(); i++) {
		int y = i/key;
		int x = (i%key);

		char c = matrix[y][x];

		if (c != '\0') { output+=c; }

	}
	
	for (int i = 0; i < array_height; i++) delete[] matrix[i];
	delete[] matrix;
	return output;
}
	/**
     * @brief Проверка ключа текста
     * @param [in] in Ключ шифрования текста. key - ключ шифрования
     * @return Строка с ключем
     * @throw encryptException, если ключ слишком маленький, пустой или имеет некоректные символы. 
     */
void Encryptor::isInvalidKey(std::string in, const int key){
	if (key == 0) throw encryptException("Empty key");

	if (in.length()/2 < key){
		throw encryptException("Invalid key value");
	}
}
	/**
     * @brief Проверка текста
     * @param [in] in Ключ шифрования текста. key - ключ шифрования
     * @return Строка с ключем
     * @throw encryptException, если ключ слишком маленький, пустой или имеет некоректные символы. 
     */
void Encryptor::isInvalidMsg(std::string in, const int key){
	if (in.empty()) throw encryptException("Empty message");
	
	for (char c : in) {
		if (!isalpha(c)) throw encryptException("Invalid char in Text"); 
	}
}