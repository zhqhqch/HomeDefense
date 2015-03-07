/*
 * EncyptUtil.cpp
 *
 *  Created on: 2015年3月7日
 *      Author: hqch
 */

#include "EncyptUtil.h"
#include "aes.h"

unsigned char key[] = "83a16bbf7480499fc4fc4c6349a381b8";

std::string EncyptUtil::encrypt(const std::string& content) {
	char miwen_hex[1024];
	AES *aes = new AES(key);
	aes->Cipher(const_cast<char*>(content.c_str()), miwen_hex);
	getchar();
	return miwen_hex;
}


std::string EncyptUtil::decrypt(const std::string& content) {
	char result[1024];
	AES *aes = new AES(key);
	aes->InvCipher(const_cast<char*>(content.c_str()), result);
	getchar();
	return result;
}
