#include<iostream>
#include<iomanip>
#include "Rule.h"
#include "Grammar.h"
#include "GrammarBase.h"

using namespace std;
int main() {


	GrammarBase base;
	String command, lastOpenedFile;
	for (;;) {
	
		cout << ">";
		cin >> command;
		if (command == "list") base.list();
		else if (command == "print") {
			int id;
			cin >> id;
			cin.ignore();
			base.print(id);
		}
		else if (command == "addRule") {
			int id;
			String r;
			cin >> id;
			cin.ignore();
			cin >> r;
			Rule R(r);
			base.addRule(id, R);
			std::cout << "Rule added!\n";
		}
		else if (command == "removeRule") {
			int id, n;
			cin >> id >> n;
			cin.ignore();
			base.removeRule(id, n);
			std::cout << "Rule removed!\n";
		}
		else if (command == "chomsky") {
			int id;
			cin >> id;
			cin.ignore();
			if (base.chomsky(id)) cout << "The Grammar is in Chomsky form!\n";
			else cout << "The Grammar is not in Chomsky form!\n";
		}
		else if (command == "empty") {
			int id;
			cin >> id;
			cin.ignore();
			if (base.empty(id)==true) cout << "The language of the grammar is empty!\n";
			else cout << "The language of the grammar is not empty!\n";
		}
		else if (command == "concat") {
			int id1, id2;
			cin >> id1 >> id2;
			cin.ignore();
			Grammar newG = base.concat(id1, id2);
			//newG.printGrammar();

		}
		else if (command == "union") {
			int id1, id2;
			cin >> id1 >> id2;
			cin.ignore();
			Grammar newG = base.unit(id1, id2);
		}
		else if (command == "open") {
			String fileToOpen;
			cin >> fileToOpen;

			///convert string into char*
			int n = fileToOpen.Size();
			char* toOpen = new char[n + 1];
			for (int i = 0; i < n; i++) toOpen[i] = fileToOpen[i];
			toOpen[n] = '\0';

			base.open(toOpen);
			lastOpenedFile = fileToOpen;
			cout << "Successfully opened "<<fileToOpen<< "!"<<endl;
			
		}
		else if (command == "save") {
			int n = lastOpenedFile.Size();
			char* toOpen = new char[n + 1];
			for (int i = 0; i < n; i++) toOpen[i] = lastOpenedFile[i];
			toOpen[n] = '\0';
			base.save(toOpen);
			cout << "Successfully saved " << lastOpenedFile << "!" << endl;
		}
		else if (command == "saveas") {
			String newFile;
			cin >> newFile;
			int n = newFile.Size();
			char* toOpen = new char[n + 1];
			for (int i = 0; i < n; i++) toOpen[i] = newFile[i];
			toOpen[n] = '\0';
			base.saveas(toOpen);
			cout << "Successfully saved another " << newFile << "!" << endl;
		}
		else if (command == "close") {
			base.close();
			cout << "Successfully closed " << lastOpenedFile << "!" << endl;
		}
		else if (command == "help") {
			cout << "The following commands are supported:\n";
			cout << "open <file> " << setw(20) << "opens<file>\n";
			cout << "close " << setw(47) << "closes the currently opened file\n";
			cout << "save " << setw(47) << "saves the currently opened file\n";
			cout << "saveas <file> " << setw(48) << "saves the currently opened file in <file>\n";
			cout << "help " << setw(39) << "prints this information\n";
			cout << "exit " << setw(33) << "exits the program\n";
		}
		else if (command == "exit") {
			cout << "Exiting the program....\n";
			return 0;
		}
		
	}
	
	return 0;
}