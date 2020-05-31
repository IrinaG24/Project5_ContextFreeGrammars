#define _CRT_SECURE_NO_WARNINGS
#include "String.h"
#include<cstring>
#include<iostream>

///������ ����� ��� � �������
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

///������ ������� ��� ����
void String::addToString(const char c) {
	char charToAdd[2];
	charToAdd[0] = c;
	charToAdd[1] = '\0';
	String strToAdd(charToAdd);
	(*this) += charToAdd;
}

///�������� ��������

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

/// ����� ��������� �� ����
int String::Size()const {
	return lenght;
}

/// ������������� �� ��������� ==
bool String::operator==(const String& other)const {
	if (strcmp(arr, other.arr) == 0) return true;
	else return false;
}

/// ������������� �� ��������� []
char& String::operator[](const int index) {
	return arr[index];
}
const char& String::operator[](const int index)const {
	return arr[index];
}

/// ������������� �� ��������� +
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

/// ������������� �� ��������� �� ���������
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

/// ������������� �� �������� �� ���������
std::ostream& operator<<(std::ostream& os, const String& toCout) {
	os << toCout.arr;
	return os;
}

