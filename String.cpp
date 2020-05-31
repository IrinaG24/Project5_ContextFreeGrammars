#define _CRT_SECURE_NO_WARNINGS
#include "String.h"
#include<cstring>
#include<iostream>

///копира даден низ в желания
void String::copyString(const String& other) {
	try {
		arr = new char[strlen(other.arr) + 1];
	}
	catch (...) {
		std::cerr << "Allocation failed!" << std::endl;
		return;
	}
	strcpy(arr, other.arr);
	lenght = other.lenght;
}

///добавя елемент към низа
void String::addToString(const char c) {
	char charToAdd[2];
	charToAdd[0] = c;
	charToAdd[1] = '\0';
	String strToAdd(charToAdd);
	(*this) += charToAdd;
}

///голямата четворка

String::String(const char* str) {
	try {
		arr = new char[strlen(str) + 1];
	}
	catch (...) {
		std::cerr << "Allocation failed!" << std::endl;
		return;
	}
	strcpy(arr, str);
	lenght = strlen(str);
}
String::String(const String& other) {
	copyString(other);
}
String& String::operator=(const String& other) {
	if (this != &other) {
		//deleteString();
		delete[] arr;
		copyString(other);
	}
	return *this;
}
String::~String() {
	delete[] arr;
}

/// връща дължината на низа
int String::Size()const {
	return lenght;
}

/// предефиниране на оператора ==
bool String::operator==(const String& other)const {
	if (strcmp(arr, other.arr) == 0) return true;
	else return false;
}

/// предефиниране на оператора []
char& String::operator[](const int index) {
	return arr[index];
}
const char& String::operator[](const int index)const {
	return arr[index];
}

/// предефиниране на оператора +
String String:: operator+(const String& toAdd) {
	String temp(*this);
	temp += toAdd;
	return temp;
}

///
String& String::operator+=(const String& toAdd) {
	String c;
	lenght += toAdd.lenght;
	char* temp;
	temp= new char[lenght + 1];
	try {
		temp= new char[lenght + 1];
	}
	catch (...) {
		std::cerr << "Allocation failed!" << std::endl;
		return c;
	}
	strcpy(temp, arr);
	//deleteString(); 
	delete[] arr;
	strcat(temp, toAdd.arr);
	arr = temp;
	return *this;
}

bool String::operator>(const String& other) const {
	if (strcmp(arr, other.arr) > 0) return true;
	else return false;
}
bool String::operator<(const String& other) const {
	if (strcmp(arr, other.arr) < 0) return true;
	else return false;
}

/// предефиниране на оператори за въвеждане
std::istream& operator>>(std::istream& is, String& toCin) {
	String toRead;
	char element;

	is.get(element);
	while (element != ' ' && element != '\n' && element != '\t') {
		toRead.addToString(element);
		is.get(element);
	}
	toCin = toRead;
	return is;
}

void getline(std::istream& is, String& toCin) {
	String toRead;
	char element;

	is.get(element);
	while (element != '\n') {
		toRead.addToString(element);
		is.get(element);
	}
	toCin = toRead;
}

/// предефиниране на оператор за извеждане
std::ostream& operator<<(std::ostream& os, const String& toCout) {
	os << toCout.arr;
	return os;
}

