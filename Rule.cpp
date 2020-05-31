#include "Rule.h"
#include <iostream>

///takes the string and makes left part and right part of the ru;e
void Rule::makeLeftAndRightPart() {
	char* toDo = new char[rule.Size() + 1];
	int i = 0;
	for (i = 0;; i++) {
		toDo[i] = rule[i];
		i++;
		if (rule[i] == '-') break;
	}
	toDo[i] = '\0';
	String temp(toDo);
	leftPart = temp;

	i += 2;
	int cnt_rp = 0;

	char* toDo2 = new char[rule.Size() + 1];
	for (int j = i; j < rule.Size(); j++) {
		toDo2[cnt_rp] = rule[j];
		cnt_rp++;
	}
	toDo2[cnt_rp] = '\0';
	String temp2(toDo2);
	rightPart = temp2;
}

///constructor
Rule::Rule(const String rule_) {
	rule = rule_;
	//std::cout << 1 << std::endl;
	if(!(rule==""))makeLeftAndRightPart();
}

///left part getter
String Rule::getLeftPart()const {
	return leftPart;
}

///right part getter
String Rule::getRightPart()const {
	return rightPart;
}

///prints rule
void Rule::printRule()const {
	std::cout << rule << std::endl;
}

///operator ==
bool Rule::operator==(const Rule& other)const {
	if (rule == other.rule) return true;
	else return false;
}