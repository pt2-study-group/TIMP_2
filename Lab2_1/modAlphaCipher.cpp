	/** @file
	 *  @author Прохоров В.О.
	 *  @version 1.0
	 *  @date 14.06.2019
	 *  @brief файл с реализацией класса modAlphaCipher
	 */
 
#include <vector>
#include <string>
#include <map>
#include <iostream>

#include "modAlphaCipher.h"

using namespace std;

std::wstring numAlpha = L"АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЫЪЭЮЯ";//алфавит по порядку
std::map <wchar_t, int> alphaNum; //ассоциативный массив "номер по символу"
	/**
     * @brief конструктор
     * @param [in] skey ключ, по которому формируется зашифрованный алфавит.
     * @throw cipher_error, если ключ не верный
     */
modAlphaCipher::modAlphaCipher(const std::wstring& skey) {
	for (int i = 0; i<numAlpha.size(); i++) {
		alphaNum[numAlpha[i]]=i;
	}
	key = convert(getValidKey(skey));

}
	/**
     * @brief Зашифровывание
     * @param [in] open_text Открытый текст. Не должен быть пустой строкой.
     *                       Строчные символы автоматически преобразуются к прописным.
     *                       Все не-буквы удаляются
     * @return Зашифрованная строка
     * @throw cipher_error, если текст пустой
     */
std::wstring modAlphaCipher::encrypt(const std::wstring& open_text) {
	std::vector<int> work = convert(getValidOpenText(open_text));
	for(unsigned i=0; i < work.size(); i++) {
		work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
	}
	return convert(work);
}
	/**
     * @brief Расшифрование
     * @param [in] cipher_text Закрытый текст. Не должен быть пустой строкой.
     *                       Строчные символы автоматически преобразуются к прописным.
     *                       Все не-буквы удаляются
     * @return Расшифрованная строка строка
     * @throw cipher_error, если текст пустой
     */
std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text) {
	std::vector<int> work = convert(getValidCipherText(cipher_text));
	for(unsigned i=0; i < work.size(); i++) {
		work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
	}
	return convert(work);
}
	/**
     * @brief Преобразование
     * @param [in] str Открытый текст. 
     * @return Вектор кодов символов в локальном алфавите.
     */
inline std::vector<int> modAlphaCipher::convert(const std::wstring& str) {
	std::vector<int> result;
	for(auto c:str) {
		result.push_back(alphaNum[c]);
	}
	return result;
}
 	/**
     * @brief Преобразование
     * @param [in] str Вектор кодов символов в локальном алфавите. 
     * @return Строка по новому алфавиту.
     */
inline std::wstring modAlphaCipher::convert(const std::vector<int>& v) {
	std::wstring result;
	for(auto i:v) {
		result.push_back(numAlpha[i]);
	}
	return result;
}
	/**
     * @brief Проверка ключа текста
     * @param [in] in Ключ шифрования текста.
     * @return Строка с ключем
     * @throw cipher_error, если ключ слишком маленький, пустой или имеет некоректные символы. 
     */
inline std::wstring modAlphaCipher::getValidKey(const std::wstring & in) {
	if (in.empty()) throw cipher_error("Empty key");
	
	wstring output;
	std::locale loc("ru_RU.UTF-8");
	
	for (wchar_t c : in) {
		if (c >= L'А' && c <= L'Я') {
			output += c;
		} else if (c >= L'а' && c <= L'я') {
			output += toupper(c, loc);
		} else {
			throw cipher_error("Invalid key");
		}
	}
	
	return output;
}
	/**
     * @brief Проверка Откротого текста
     * @param [in] in Открытый текст.
     * @return Строка открытого текста
     * @throw cipher_error, если строка пустая или имеет некоректные символы. 
     */
inline std::wstring modAlphaCipher::getValidOpenText(const std::wstring & in) {
	if (in.empty()) throw cipher_error("Empty Open Text");
	
	wstring output;
	std::locale loc("ru_RU.UTF-8");
	
	for (wchar_t c : in) {
		if (c >= L'А' && c <= L'Я') {
			output += c;
		} else if (c >= L'а' && c <= L'я') {
			output += toupper(c, loc);
		} else {
			throw cipher_error("Invalid Open Text");
		}
	}
	
	return output;
}
	/**
     * @brief Проверка зашифрованного текста
     * @param [in] in Зашифрованный текст.
     * @return Зашифрованная строка
     * @throw cipher_error, если текст пустой или в тексте есть что-то кроме букв алфавита
     */
inline std::wstring modAlphaCipher::getValidCipherText(const std::wstring & in){
	if (in.empty()) throw cipher_error("Empty Cipher Text");
	
	wstring output;
	std::locale loc("ru_RU.UTF-8");
	
	for (wchar_t c : in) {
		if (c > L'А' && c < L'Я') {
			output += c;
		} else {
			throw cipher_error("Invalid Open Text");
		}
	}
	
	return output;
}
