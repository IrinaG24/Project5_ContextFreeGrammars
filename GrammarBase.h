#ifndef GRAMMARBASE_H_
#define GRAMMARBASE_H_

#include "Grammar.h"

class GrammarBase {
private:
	Grammar* allGrammars;
	int capacity;
	int numberOfGrammars;

	void copyData(const GrammarBase&);
	void deleteData();
	void resize();
	char FreeVar(Vector<char>, Vector<char>);

public:
	GrammarBase(int = 1);
	GrammarBase(const GrammarBase&);
	GrammarBase& operator=(const GrammarBase&);
	~GrammarBase();

	void list()const;
	void print(int) const;
	void addRule(int, const Rule&);
	void removeRule(int, int);
	bool chomsky(int)const;
	bool empty(int)const;

	void addGrammar(const Grammar&);

	Grammar concat(int, int);
	Grammar unit(int, int);

	void open(const char*);
	void save(const char*);
	void saveas(const char*);
	void close();


};
#endif // !GRAMMARBASE_H_
