#include "GrammarBase.h"
#include<fstream>

///copies data
void GrammarBase::copyData(const GrammarBase& other) {
    try
    {
        allGrammars = new Grammar[other.capacity];
    }
    catch (...)
    {
        std::cerr << "Allocation failed!" << std::endl;
        return;
    }
    capacity = other.capacity;
    numberOfGrammars = other.numberOfGrammars;
    for (int i = 0; i < numberOfGrammars; i++)
        allGrammars[i] = other.allGrammars[i];
}

///deletes data
void GrammarBase::deleteData() {
    delete[] allGrammars;
}

///doubles the capacity
void GrammarBase::resize() {
    Grammar* doubleGrammar;
    try
    {
        doubleGrammar = new Grammar[capacity * 2];
    }
    catch (...)
    {
        std::cerr << "Allocation failed!" << std::endl;
        return;
    }

    for (int i = 0; i < numberOfGrammars; i++)
        doubleGrammar[i] = allGrammars[i];
    capacity *= 2;
    delete[] allGrammars;
    allGrammars = doubleGrammar;
}

///return variable which is not used
char GrammarBase::FreeVar(Vector<char> v, Vector<char>v2) {
    for (int i = 65; i <= 90; i++) {
        char c = i;
        int br = 0;
        for (int j = 0; j < v.size(); j++) {
            if (c != v[j]) br++;
        }
        for (int j = 0; j < v2.size(); j++) {
            if (c != v2[j]) br++;
        }
        if (br == v.size() + v2.size()) return c;
    }
}

///constructor
GrammarBase::GrammarBase(int capacity) {

    try
    {
        allGrammars = new Grammar[capacity];
    }
    catch (...)
    {
        std::cerr << "Allocation failed!" << std::endl;
        return;
    }
    this->capacity = capacity;
    numberOfGrammars = 0;
}

///copy-constructor
GrammarBase::GrammarBase(const GrammarBase& other) {
    copyData(other);
}

///operator =
GrammarBase& GrammarBase:: operator=(const GrammarBase& other) {
    if (this != &other) {
        deleteData();
        copyData(other);
    }
    return *this;
}

/// destructor
GrammarBase::~GrammarBase() {
    deleteData();
}

///prints all the IDs of the grammars
void GrammarBase::list()const {
    for (int i = 0; i < numberOfGrammars-1; i++)
        std::cout << allGrammars[i].getID() << std::endl;
}

///prints infortion about a grammar
void GrammarBase::print(int index) const {
    for (int i = 0; i < numberOfGrammars; i++) {
        if (i == index) allGrammars[i].printGrammar();
    }
}

///adds rule in a grammar
void GrammarBase::addRule(int id, const Rule& toAdd) {
    for (int i = 0; i < numberOfGrammars; i++) {
        if (i == id) {
            allGrammars[i].addRule(toAdd);
        }
    }
}

///deletes rule from a grammar
void GrammarBase::removeRule(int id, int n) {
    for (int i = 0; i < numberOfGrammars; i++) {
        if (id == i) {
            for (int j = 0; j < allGrammars[i].getRules().size(); j++) {
                if (j == n) {
                    allGrammars[i].RemoveRule(allGrammars[i].getRules()[j]);
                    break;
                }
            }
        }
    }
}

///check if a grammar is in chomsky form
bool GrammarBase::chomsky(int id)const {
    for (int i = 0; i < numberOfGrammars; i++) {
        if (id == i) {
            if (allGrammars[i].isInChomskyForm())return  true;
            else return false;
        }
    }
}

/// check if the language of the grammar is empty
bool GrammarBase::empty(int id)const {
    for (int i = 0; i < numberOfGrammars; i++) {
        if (id == i) {
            if (allGrammars[id].empty() == true)return  true;
            else return false;
        }
    }
}

///adds grammar in the array
void GrammarBase::addGrammar(const Grammar& toAdd){
    if(capacity == numberOfGrammars)   resize();
    allGrammars[numberOfGrammars].operator=(toAdd);
    allGrammars[numberOfGrammars].SetID(numberOfGrammars);
    numberOfGrammars++;
}

///concatinates two grammars
Grammar GrammarBase::concat(int id1, int id2) {
    Grammar one;
    Grammar two;
    for (int i = 0; i < numberOfGrammars; i++) {
        if (i == id1) one = allGrammars[i];
        if (i == id2) two = allGrammars[i];
    }
    char toChange;
    char c;
    for (int i = 0; i < one.getVariables().size(); i++) {
        for (int j = 0; j < two.getVariables().size(); j++) {
            if (one.getVariables()[i] == two.getVariables()[j]) {
                c = FreeVar(one.getVariables(), two.getVariables());
                toChange = one.getVariables()[i];
                one.getVariables()[i] = c;
                break;
            }
        }  
        for (int k = 0; k < one.getRules().size(); k++) {
                    if (one.getRules()[k].getLeftPart()[0] == toChange) one.getRules()[k].getLeftPart()[0] = c;
                    for (int p = 0; p < one.getRules()[k].getRightPart().Size(); p++) {
                        if (one.getRules()[k].getRightPart()[p] == toChange)  one.getRules()[i].getRightPart()[p] = c;
                    }
        }
    }
    for (int i = 0; i < one.getVariables().size(); i++) std::cout << one.getVariables()[i] << std::endl;

    

    Vector<char> concatV;
    for (int i = 0; i < one.getVariables().size(); i++)
        concatV.add(one.getVariables()[i]);
    for (int i = 0; i < two.getVariables().size(); i++)
        concatV.add(two.getVariables()[i]);

    Vector<Rule>concatR;
    char s = FreeVar(one.getVariables(), two.getVariables());
    char st[2] = { s, '\0' };
    String newStart(st);
    newStart += "->";
    char rp[3] = { one.getSV(), two.getSV(), '\0' };

    String newStartRP(rp);
    newStart += newStartRP;
    concatR.add(Rule(newStart));
    for (int i = 0; i < one.getRules().size(); i++) concatR.add(one.getRules()[i]);
    for (int i = 0; i < two.getRules().size(); i++) concatR.add(two.getRules()[i]);

    Grammar concat(concatV, one.getAlphabet(), concatR, s);
    addGrammar(concat);
    std::cout << "Concatination done!\n";
    return concat;

   
}

///unites two grammars
Grammar GrammarBase::unit(int id1, int id2) {
    Grammar one;
    Grammar two;
    for (int i = 0; i < numberOfGrammars; i++) {
        if (i == id1) one = allGrammars[i];
        if (i == id2) two = allGrammars[i];
    }
    char toChange;
    for (int i = 0; i < one.getVariables().size(); i++) {
        for (int j = 0; j < two.getVariables().size(); j++) {
            if (one.getVariables()[i] == two.getVariables()[j]) {
                char c = FreeVar(one.getVariables(), two.getVariables());
                toChange = one.getVariables()[i];
                one.getVariables()[i] = c;

                for (int k = 0; k < one.getRules().size(); k++) {
                    if (one.getRules()[k].getLeftPart()[0] == toChange) one.getRules()[k].getLeftPart()[0] = c;
                    for (int p = 0; p < one.getRules()[k].getRightPart().Size(); p++) {
                        if (one.getRules()[k].getRightPart()[p] == toChange)  one.getRules()[i].getRightPart()[p] = c;
                    }
                }
            }
        }
    }



    Vector<char> concatV;
    for (int i = 0; i < one.getVariables().size(); i++)
        concatV.add(one.getVariables()[i]);
    for (int i = 0; i < two.getVariables().size(); i++)
        concatV.add(two.getVariables()[i]);

    Vector<Rule>concatR;
    char s = FreeVar(one.getVariables(), two.getVariables());
    char st[2] = { s, '\0' };
    String newStart(st);
    newStart += "->";
    char oneR[2] = { one.getSV(), '\0' };
    char twoR[2] = { two.getSV(), '\0' };
    String newR1(oneR);
    String newR2(twoR);

    concatR.add(Rule(newStart + newR1));
    concatR.add(Rule(newStart + newR2));
    for (int i = 0; i < one.getRules().size(); i++) concatR.add(one.getRules()[i]);
    for (int i = 0; i < two.getRules().size(); i++) concatR.add(two.getRules()[i]);

    Grammar concat(concatV, one.getAlphabet(), concatR, s);
    addGrammar(concat);
    std::cout << "Unit operation done!\n";
    return concat;

    
}

///loads information from a file
void GrammarBase::open(const char* filename) {

    std::ifstream iFile;
    iFile.open(filename);
    if (!iFile) {
        std::ofstream oFile(filename);
        oFile.close();
        iFile.open(filename);
    }
    iFile.seekg(0, std::ios::end);
    if (iFile.tellg() == 0) {
        std::cerr << "The file is empty!\n";
    }

    iFile.seekg(0, std::ios::beg);
        for (;;) {  
            if (iFile.eof()) {
                    break;
              }
            Grammar toAdd;
            saveFromFile(iFile, toAdd);
             addGrammar(toAdd);
            // toAdd.printGrammar();
           
        }

        
}

///saves information in lastly saved file
void GrammarBase::save(const char* filename) {
    std::ofstream oFile;
    oFile.open(filename, std::ios::trunc);
    for (int i = 0; i < numberOfGrammars; i++) {
        allGrammars[i].saveInFile(oFile);
    }
    oFile.close();
    std::cout << "Successfully saved " << filename << "!\n";
}

///saves information in a new file
void GrammarBase::saveas(const char* saveInNewFile) {
    std::ofstream oFile;
    oFile.open(saveInNewFile, std::ios::app);
    for (int i = 0; i < numberOfGrammars; i++)
        allGrammars[i].saveInFile(oFile);
    oFile.close();
    std::cout << "Successfully saved " << saveInNewFile << "!\n";
}

///deletes loaded information
void GrammarBase::close() {
    delete[] allGrammars;
    capacity = 1;
    numberOfGrammars = 0;
}