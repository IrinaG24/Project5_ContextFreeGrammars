#include "Grammar.h"

///checks if a rule variables are in the grammar variables
bool Grammar::IsRuleValid(Vector<char> var, Rule rule) {
	int cnt = 0, flag = 0, cnt2 = 0;
	for (int i = 0; i < var.size(); i++) {
		if (var[i] == rule.getLeftPart()[0]) flag = 1;
	}
	if (flag == 0) return false;
	else if(rule.getRightPart()!="eps"){
		for (int i = 0; i < rule.getRightPart().Size(); i++) {
			for (int j = 0; j < var.size(); j++) {
				if (rule.getRightPart()[i] == var[j]) {
					cnt++;
				}

				
				
			}if (rule.getRightPart()[i] >= 'A' && rule.getRightPart()[i] <= 'Z') cnt2++;
		}
		if (cnt == cnt2) return true;
		else return false;
	}

}

bool Grammar::CheckIfVariableIsInArray(String var, Vector<String> arr) {
	for (int i = 0; i < arr.size(); i++)
		if (var == arr[i]) return true;
	return false;
}

///returns the first free variables that is not used
char Grammar::FreeValuabe(Vector<char> var) {
	for (int i = 65; i <= 90; i++) {
		char c = i;
		int br = 0;
		for (int j = 0; j <var.size(); j++) {
			if (c != var[j]) br++;
		}
		if (br == var.size()) return c;
	}
}

/// removes useless variables
Grammar Grammar::removeTheUselessVariables() {

	Vector<Vector<String>> Gen;
	Vector<String> s;
	Gen.add(s);
	///Gen[1] - all the variables from which we can get epsilon
	for (int i = 0; i < rules.size(); i++) {
		if (rules[i].getRightPart().Size() == 1) {
			
			char c = rules[i].getRightPart()[0];
			String toAdd = rules[i].getLeftPart(); 
			if (c >= 'a' && c <= 'z') s.add(toAdd);
			
		}
		else {
			if (rules[i].getRightPart() == "eps") {
				String toAdd(rules[i].getLeftPart());
				s.add(toAdd);
			}
		}
	}
	Gen.add(s);

	int cnt = 2;
	for (;;) {
		Vector<String> temp;
		temp = Gen[cnt - 1];
		bool isAdded = 0;
		int isInRule = 0;
		for (int i = 0; i < rules.size(); i++) {
			int br = 0;
			char left[2] = { rules[i].getLeftPart()[0], '\0' };
			String isAlreadyIn(left);
			if (CheckIfVariableIsInArray(isAlreadyIn, Gen[cnt - 1]) == false) {
				for (int j = 0; j < rules[i].getRightPart().Size(); j++) {
					char c = rules[i].getRightPart()[j];
					if (c >= 'a' && c <= 'z') br++;
					else if (c >= 'A' && c <= 'Z') {
						char check[2] = { c, '\0' };
						String toCheck(check);
						if (CheckIfVariableIsInArray(toCheck, Gen[cnt - 1]) == true) br++;
					}
				}
				if (br == rules[i].getRightPart().Size()) {
					temp.add(rules[i].getLeftPart());
				}
			}
		}
		Gen.add(temp);
		if (Gen[cnt] == Gen[cnt - 1]) {
			
			break;
		}
		cnt++;
	}

	Vector<String> neededVariables = Gen[cnt];

		Vector<char> variables1;
		for (int j = 0; j < variables.size(); j++) {

			for (int i = 0; i < neededVariables.size(); i++) {
				
				if (variables[j] == neededVariables[i][0]) {
					variables1.add(variables[j]);
					break;
				}
			}
		}

		Vector<Rule> rules1;
		for (int i = 0; i < rules.size(); i++) {
			if (IsRuleValid(variables1, rules[i])) rules1.add(rules[i]);
		}


	Vector<Vector<String>>Reach;
	
	Vector<String> temp;
	char start[2] = { startingVariable, '\0' };
	String first(start);
	temp.add(first);
	Reach.add(temp);

	cnt = 1;
	for (;;) {
		Vector<String> temp2;
		temp2 = Reach[0];
		for (int i = 0; i < variables1.size(); i++) {
			char v[2] = { variables1[i], '\0' };
			String var(v);
			for (int j = 0; j < Reach[cnt - 1].size(); j++) {
				int flag = 0;
				for (int k = 0; k < rules1.size(); k++) {
					if (rules1[k].getLeftPart() == Reach[cnt-1][j]) {
						for (int p = 0; p < rules[k].getRightPart().Size(); p++) {
							if (rules1[k].getRightPart()[p] == variables1[i]) {
								temp2.add(var);
								flag = 1;
								break;
							}
						}

					}
					
				}
				
			}
		}
		Reach.add(temp2);
		if (Reach[cnt] == Reach[cnt - 1]) break;
		cnt++;
	}
	Vector<String> reachableVariables = Reach[cnt];
	Vector <char> variables2;
	for (int j = 0; j < variables1.size(); j++) { 
		for (int i = 0; i < reachableVariables.size(); i++) {
			if (variables1[j] == reachableVariables[i][0]) {
				
				variables2.add(variables1[j]);
				
			}
		}
	}

	Vector<Rule>rules2;
	for (int i = 0; i < rules1.size(); i++) {
		if (IsRuleValid(variables2, rules1[i])) rules2.add(rules1[i]);
	}

	
	Grammar toReturn(variables2, alphabet, rules2, startingVariable);
	return toReturn;
}

/// removes the long rules
Grammar Grammar::removeTheLongRules() {
	Vector<Rule> rules1;
	Vector<char> newVar = variables;
	for (int i = 0; i < rules.size(); i++) {
		if (rules[i].getRightPart().Size() <= 2) rules1.add(rules[i]);
		else {
			String temp = rules[i].getLeftPart();
			temp += "->";
			char lastVar;
			for (int j = 0; j < rules[i].getRightPart().Size() - 2; j++) {
				char c;
				c = FreeValuabe(newVar);
				newVar.add(c);
				
				char toAdd[3] = { rules[i].getRightPart()[j], c, '\0' };
				temp += toAdd;
				std::cout << temp << std::endl;
				rules1.add(temp);
				char cToString[2] = { c, '\0' };
				String newTemp(cToString);
				temp = newTemp;
				temp += "->";
				lastVar = c;
			}
			int k = rules[i].getRightPart().Size();
			char lastToAdd[4] = { rules[i].getRightPart()[k - 2], rules[i].getRightPart()[k - 1], '\0' };
			char leftP[4] = { lastVar, '-', '->', '\0' };
			String last(leftP);
			last += lastToAdd;
			rules1.add(last);
		}

	}
	Grammar toReturn(newVar, alphabet, rules1, startingVariable);
	return toReturn;
}

Grammar Grammar::removeTheRenamingRules() {
	Vector<Vector<String> >Ren;
	Vector<String>first;
	char add[3];
	for (int i = 0; i < variables.size(); i++) {
		add[0] = variables[i];
		add[1] = variables[i];
		add[2] = '\0';
		String ad(add);
		first.add(ad);
	}
	Ren.add(first);

	int cnt = 1;
	/*for (;;) {
		Vector<char[2]> temp = Ren[cnt - 1];
		for (int i = 0; i < variables.size(); i++) {
			for (int j = 0; j < rules.size(); j++) {
				int flag = 0;
				for (int k = 0; k < rules[j].getRightPart().Size(); k++) {
					if (rules[j].getRightPart()[k] == variables[i]) {
						char a = rules[j].getLeftPart()[0];
						char c = rules[j].getRightPart()[k];
						char b;
						for (int p = 0; p < Ren[cnt - 1].size(); p++) {
							if (Ren[cnt - 1][p][0] == c) {
								b = Ren[cnt - 1][p][1];
								char toadd[2] = { a, b };
								temp.add(toadd);
							}
						}
					}
				}
			}
		}
		Ren[cnt] = temp;
		if (Ren[cnt] == Ren[cnt - 1]) break;
		cnt++;
	}

	Vector<char[2]> ren;
	ren = Ren[cnt];
	Vector<Rule> rules1;
	for (int i = 0; i < rules.size(); i++) {
		if (rules[i].getLeftPart()[0] != rules[i].getRightPart()[0]) rules1.add(rules[i]);
	}

	Vector<Rule>rules2 = rules1;
	for (int i = 0; i < variables.size(); i++) {
		char temp[4] = { variables[i], '-', '>', '\0' };
		String toAdd(temp);
		for (int j = 0; j < ren.size(); j++) {
			if (variables[i] == ren[j][0]) {
				for (int k = 0; k < rules1.size(); k++) {
					if (ren[j][1] == rules[k].getLeftPart()[0]) {
						toAdd += rules[k].getRightPart();
						rules2.add(toAdd);
					}
				}
			}
		}
	}
	*/
	Grammar toReturn;// (variables, alphabet, rules2, startingVariable, ID);
	return toReturn;
}

Grammar Grammar::removeTheEpsilonRules() {
	Vector<Vector<char>> E;
	Vector<char> temp;
	E.add(temp);
	for (int i = 0; i < rules.size(); i++) {
		if (rules[i].getRightPart() == "eps") temp.add(rules[i].getLeftPart()[0]);
	}
	E.add(temp);

	

	int cnt = 2;
	for (;;) {
		Vector<char> t;

		for (int i = 0; i < variables.size(); i++) {

			for (int j = 0; j < rules.size(); j++) {
				int br = 0;
				if (rules[j].getLeftPart()[0] == variables[i]) {
					for (int k = 0; k < rules[j].getRightPart().Size(); k++) {
						br = 0;
						for (int p = 0; p < E[cnt - 1].size(); p++) {
							if (rules[j].getRightPart()[k] == E[cnt - 1][p]) br++;
						}
						
						//	break;
						}
						if (br == rules[j].getRightPart().Size() == br) {
							t.add(variables[i]);
					}
				}
			}
		}
		E.add(t);
		system("pause");
		for (int i = 0; i < E[cnt].size(); i++) std::cout << E[cnt][i] << std::endl;
		std::cout << std::endl;
		if (E[cnt] == E[cnt - 1]) break;
		cnt++;
	}
	Vector<char> variablesE = E[cnt];

	Vector<Rule>rules1;
	for (int i = 0; i < rules.size(); i++) {
		if (!(rules[i].getRightPart() == "eps"))rules1.add(rules[i]);
	}

	int n = rules1.size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < rules1[i].getRightPart().Size(); j++) {
			String temp = rules1[i].getLeftPart();
			temp += "->";
			char c = rules1[i].getRightPart()[j];
			if (c >= 'A' && c <= 'Z') {
				bool flag = 0;
				for (int k = 0; k < variablesE.size(); k++) {
					if (variablesE[k] == c) {
						flag = 1;
						break;
					}
				}
				if (flag == 0) {
					char toAdd[2] = { c, '\0' };
					temp += toAdd;
				}
				else
				{
					String temp2 = temp;
					if (temp2.Size() > 3) rules1.add(Rule(temp2));
					char toAdd[2] = { c, '\0' };
					temp += toAdd;
				}

			}
		}
	}
	Grammar toReturn(variables, alphabet, rules1, startingVariable);
	return toReturn;
}

///checks if a grammar is in Chomsky form
bool Grammar::isInChomskyForm() {
	for (int i = 0; i < rules.size(); i++) {
		if (rules[i].getRightPart().Size() == 1) {
			char c = rules[i].getRightPart()[0];
			if (c < 'a' && c>'z') return false;
		}
		else if (rules[i].getRightPart().Size() == 2) {
			char c = rules[i].getRightPart()[0];
			char c2 = rules[i].getRightPart()[1];
			if ((c < 'A' && c>'Z') || (c2 < 'A' && c2>'Z')) return false;
		}
		else return false;
	}
	return true;
}

///checks if the launguage of the grammar is empty
bool Grammar::empty() {
	Grammar temp = (*this);
	Grammar temp2 = temp;
	if (!(temp.isInChomskyForm())) {

	 temp2 = temp.removeTheUselessVariables();
	}
	for (int i = 0; i < temp2.variables.size(); i++) {
		if (temp2.startingVariable == temp2.variables[i]) return false;
	}
	return true;
}

///default constructor
Grammar::Grammar() {
	ID = 0;
	startingVariable = ' ';
}

///constructor with parametres
Grammar::Grammar(Vector<char> variables_, Vector<char> alphabet_, Vector<Rule>rules_, char SV) {
	variables = variables_;
	alphabet = alphabet_;
	rules = rules_;
	startingVariable = SV;

}

///adds rule
void Grammar::addRule(const Rule& toAdd) {
	rules.add(toAdd);
}

///removes rule
void Grammar::RemoveRule(const Rule& toRemove) {
	rules.remove(toRemove);
}
/// prints information about the grammar
void Grammar::printGrammar() const {
	std::cout << "Variables: ";
	for (int i = 0; i < variables.size() - 1; i++)
		std::cout << variables[i] << ", ";
	std::cout << variables[variables.size() - 1] << std::endl;

	std::cout << "Letters: ";
	for (int i = 0; i < alphabet.size() - 1; i++)
		std::cout << alphabet[i] << ", ";
	std::cout << alphabet[alphabet.size() - 1] << std::endl;

	std::cout << "Rules:\n";
	for (int i = 0; i < rules.size(); i++) {
		std::cout << i << ": ";
		std::cout << rules[i].getRule() << std::endl;
	}

	std::cout << "Starting variable: " << startingVariable << std::endl;

}

///operator>>
std::istream& operator>>(std::istream& is, Grammar& toCin) {
	int lenVar, lenAlphabet, lenRules;
	String rule_;
	is >> lenVar >> lenAlphabet >> lenRules;
	for (int i = 0; i < lenVar; i++) {
		char c;
		is >> c;
		toCin.variables.add(c);
	}
	for (int i = 0; i < lenAlphabet; i++) {
		char c;
		is >> c;
		toCin.alphabet.add(c);
	}
	is.ignore();
	for (int i = 0; i < lenRules; i++) {

		is >> rule_;
		Rule toAdd(rule_);
		
		toCin.rules.add(toAdd);

	}
	is >> toCin.startingVariable;
	return is;
}

///saves information from a file
void saveFromFile(std::istream& is, Grammar& toRead)
{
	is >> toRead;
}

///saves information in a file
void Grammar::saveInFile(std::ostream& os){
	os << variables.size() << " " << alphabet.size() << " " << rules.size();
	os << "\n";
	for (int i = 0; i < variables.size() - 1; i++) os << variables[i] << " ";
	os << variables[variables.size() - 1] << "\n";
	for (int i = 0; i < alphabet.size() - 1; i++) os << alphabet[i] << " ";
	os << alphabet[alphabet.size() - 1] << "\n";
	for (int i = 0; i < rules.size(); i++) os << rules[i].getRule() << "\n";
	os << startingVariable << "\n";
}

Vector<char> Grammar::getVariables() {
	return variables;
}


/*
6 2 13
S D A B C U
a b
S->D
D->AD
D->b
A->AB
A->BC
A->a
B->AA
B->UC
C->eps
C->CA
C->a
U->eps
U->aUb
S
*/