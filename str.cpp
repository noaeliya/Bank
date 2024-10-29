#include "str.h"

using namespace std;
Str::Str() {
	const char* temp = "none";
	m_str = new char[strlen(temp) + 1];
	strcpy(m_str, temp);
}
Str::Str(const Str& other) {
	m_str = new char[strlen(other.m_str) + 1];
	strcpy(m_str, other.m_str);
}
Str::Str(const char* str) {
	m_str = new char[strlen(str) + 1];
	strcpy(m_str, str);
}
Str::~Str() {
	delete[] m_str;
}

bool Str::operator == (const Str& other) const {

		if (strcmp(m_str, other.m_str) == 0)
			return true;
		return false;
	
}

bool Str::operator!=(const Str& other) const {
	if (strcmp(m_str, other.m_str) == 0)
		return false;
	return true;
}

bool Str:: operator>(const Str& other) const {

	if (strcmp(m_str, other.m_str) > 0)
		return true;
	else {
		if (strcmp(m_str, other.m_str) < 0 || strcmp(m_str, other.m_str) == 0)
			return false;
	}

}

bool Str::operator<(const Str& other) const {
	if (strcmp(m_str, other.m_str) <  0)
		return true;
	else {
		if (strcmp(m_str, other.m_str) > 0 || strcmp(m_str, other.m_str) == 0)
			return false;
	}
}


const Str& Str :: operator=(const Str& other) {
	delete[] m_str;
	m_str = NULL;
	m_str = new char[strlen(other.m_str) + 1];
	strcpy(m_str, other.m_str);

}
const Str& Str :: operator=(const char* str) {
	delete[] m_str;
	m_str = NULL;
	m_str = new char[strlen(str) + 1];
	strcpy(m_str, str);
}
char& Str ::operator[](int index) const { return m_str[index]; }

const Str& Str :: operator++() {

	for (int i = 0; m_str[i] != '\0'; i++) {
		m_str[i] = m_str[i] + 1;
	}
	return *this;
}

Str	Str :: operator++(int) {
	Str temp(*this);
	for (int i = 0; m_str[i] != '\0'; i++) {
		m_str[i] = m_str[i] + 1;
	}
	return temp;
}

Str ::operator int() const {//cast
	return strlen(m_str);
}

int	Str ::operator ()(char ch) const {
	for (int i = 0; i <= strlen(m_str); i++) {
		if (m_str[i] == ch)
			return i;
	}
	return -1;
}

Str	Str ::operator+(const Str& other) const {
	int newsize = strlen(m_str) + strlen(other.m_str);
	char* newStr = new char[newsize + 1];
	strcpy(newStr,m_str);
	strcat(newStr, other.m_str);

	Str result(newStr);
	delete[] newStr;
	return result;

}
const Str& Str:: operator+=(const Str& other) {
	int newsize = strlen(m_str) + strlen(other.m_str);
	char* newStr = new char[newsize + 1];
	strcpy(newStr, m_str);
	strcat(newStr, other.m_str);

	//delete[] m_Str;
	m_str = newStr;

	return *this;
}
Str operator+(const char* str, const Str& other) {
	int newsize = strlen(str) + strlen(other.m_str);
	char* newStr = new char[newsize + 1];
	strcpy(newStr,str);
	strcat(newStr, other.m_str);

	Str result(newStr);
	delete[] newStr;
	return result;
}

Str operator*(int num, const Str& other) {

	if (num <= 0)
		return Str("");

	int size = num*strlen(other.m_str);

	char* newStr = new char[size + 1];
	newStr[0] = '\0';
	strcpy(newStr, other.m_str);

	for (int i = 0; i < num-1; i++) {
		strcat(other.m_str, other.m_str);
	}

	Str result(newStr);
	delete[] newStr;
	return result;


}

