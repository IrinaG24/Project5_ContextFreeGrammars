#ifndef GRAMMAR_H_
#define GRAMMAR_H_

#include "Rule.h"
#include "Vector.hpp"

class Grammar {
private:
	Vector<char> variables;
	Vector<char> alphabet;
	Vector<Rule> rules;
	char startingVariable;
	int ID;

	bool CheckIfVariableIsInArray(String, Vector<String>);
	bool IsRuleValid(Vector<char>, Rule);
	char FreeValuabe(Vector<char>);

public:
	Grammar();
	Grammar(Vector<char>, Vector<char>, Vector<Rule>, char);

	Grammar removeTheUselessVariables();
	Grammar removeTheLongRules();
	Grammar removeTheRenamingRules();
	Grammar removeTheEpsilonRules();
	Grammar makeInChomskyForm();

	void printGrammar() const;
	void addRule(const Rule&);
	void RemoveRule(const Rule&);
	bool isInChomskyForm();
	bool isTheWordInTheLanguage(const String&);
	bool empty();

	friend std::istream& operator>>(std::istream&, Grammar&);
	void SetID(const int index) {
		ID = index;
	}
	int getID()const {
		return ID;
	}

	Vector<Rule> getRules()const {
		return rules;
	}

	Vector<char> getVariables();
	Vector<char> getAlphabet()const {
		return alphabet;
	}

	char getSV()const {
		return startingVariable;
	}

	friend void saveFromFile(std::istream&, Grammar&);
	void saveInFile(std::ostream&);
	

};
#endif // !GRAMMAR_H_
