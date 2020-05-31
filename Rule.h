#ifndef RULE_H_
#define RULE_H_

#include "String.h"

class Rule {
private:
	String rule;
	String leftPart;
	String rightPart;

	void makeLeftAndRightPart();

public:
	Rule(const String = "");
	String getLeftPart()const;
	String getRightPart()const;
	String getRule()const {
		return rule;
	}
	void printRule()const;

	bool operator==(const Rule&)const;
	bool operator!=(const Rule& other)const {
		if (rule == other.rule) return false;
		else return true;
	}
};

#endif // !RULE_H_
