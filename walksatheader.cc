#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <cmath>
#include <chrono>

#include "Clause.h"

class Walksat {
	std::vector<Clause> clauses;
	std::unordered_map<int, bool> model;
	Clause ranclause;

	const int MAX_FLIPS = std::pow(10, 7);
	const float RAN_WALK_PROB = 0.5;

	int _clauseCount;

public:
	void Walksat(std::string);
	int algorithm();

private:
	inline bool sat();
	inline void fliprandom();
	inline int satcounter();
	inline void flipmax();
	inline void ranfalseclause();
	void numclauses (std::string header);
	void getclauses(std::string filename);
	void newmodel();
};

// Checks if a DNF satisfies given a model
inline bool Walksat::sat() {
	for(Clause c : clauses) {
		if(!c.satisfies(model))
			return false;
	}

	return true;
}

// Flips a random value in model from clause
inline void Walksat::fliprandom() {
	int symbol = ranclause.randomClause();

	model[symbol] = !model[symbol];
	// std::cout << "flipping random: " << symbol << std::endl;
}

// Returns a count of how many clauses are satisfied by the given model
inline int Walksat::satcounter() {
	int result = 0;

	for(Clause c : clauses) {
		if(c.satisfies(model))
			result++;
	}

	return result;
}

// Flips the value of the symbol in the model that increase the most...
// ...satistied clauses.
inline void Walksat::flipmax() {
	int satcount = 0, testcount = 0;
	std::vector<int> symbols = ranclause.clauses();
	int flipsymbol;

	for (int i = 0; i < symbols.size(); i++) {
		model[symbols[i]] = !model[symbols[i]];
		testcount = satcounter();

		if(testcount > satcount) {
			satcount = testcount;
			flipsymbol = symbols[i];
		}

		model[symbols[i]] = model[symbols[i]];
		testcount = 0;
	}

	// std::cout << "flipping max: " << flipsymbol << ", " << satcount << std::endl;

	// Flips the symbol
	model[flipsymbol] = !model[flipsymbol];
}

// WalkSat algorithm
int Walksat::algorithm() {
	std::cout << "Unique symbols: " << model.size() << std::endl;

	// auto startsat = std::chrono::high_resolution_clock::now();
	// auto startflipran = std::chrono::high_resolution_clock::now();
	// auto startflipmax = std::chrono::high_resolution_clock::now();

	int currentflips = 0;
	std::cout << "MAX_FLIPS: " << MAX_FLIPS << std::endl;

	for (; currentflips < MAX_FLIPS; currentflips++) {
		std::cout << "\rCurrent flips: " << currentflips;// << std::flush; 
		// std::cout << "New model: " << currentflips << std::endl;
		// for (const auto &p : model) {
		// 	std::cout << "[" << p.first << "] = " << p.second << '\n';
		// }

		// If the current model is logically true under the clause the amount of...
		// ...flips is returned.
		// startsat = std::chrono::high_resolution_clock::now();
		if(sat(clauses, model)) {
			std::cout << '\r';
			return currentflips;
		}
		// std::cout << "Sat test: " << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now()-startsat).count() << std::endl;

		// Sets random clause from clauses
		ranfalseclause();

		// If true flip the value in model of a randomly selected symbol from clause
		// startflipran = std::chrono::high_resolution_clock::now();
		if(std::rand() / double(RAND_MAX) < RAN_WALK_PROB) {
			fliprandom();
			// std::cout << "Flipped -> " << std::endl;
			// clause.printclause(model);

			// std::cout << "Flip ran: " << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now()-startflipran).count() << std::endl;
		}

		// Flip whichever symbol in clause maximizes the number of satisfied clauses
		else {
			// startflipmax = std::chrono::high_resolution_clock::now();
			flipmax();
			// std::cout << "Flip max: " << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now()-startflipmax).count() << std::endl;
		}
	}

	return MAX_FLIPS;
}

// Returns a random clause that is false under the given model
inline void Walksat::ranfalseclause() {
	while (true) {
		Clause clause = clauses[rand() % (clauses.size() - 1)];
		if (!clause.satisfies(model)) {
			// std::cout << "False clause ->" << std::endl;
			// clause.printclause(model);
			ranclause = clause;
			break;
		}
	}
}

// Sets the number of clauses from the header of file
void Walksat::numclauses (std::string header) {
	std::istringstream iss(header);

    std::string s;
    int a[10], i = 0;

    while (getline(iss, s, ' ')) {
    	if(isdigit(s[0])) {
    		a[i] = stoi(s);
    		i++;
    	}
    }

    _clauseCount = a[1];
}

// Parses the file to clauses
void Walksat::getclauses(std::string filename) {
	// Opens file
	std::string line;
	std::ifstream f(filename);

	// Checks if file was opened correctly, if not exits.
	if (!f.is_open()) {
		std::cout << "Error opening file, program terminating" << std::endl;
		exit(0);
	}

	std::cout << "Walk prob: " << RAN_WALK_PROB << " Max Flips: " << MAX_FLIPS << std::endl;

	getline(f, line);
	std::cout << line << std::endl;
	_clauseCount = numclauses(line);

	// Pushs all clauses on to the vector
	while (getline(f, line)) {
		Clause c = Clause(line);
		clauses.push_back(c);
	}

	f.close();
}

// Creates a model based on the symbols in the 
void Walksat::newmodel() {
	std::vector<int> addclause;

	std::srand(time(NULL));
	
	// Loops through all clauses, finds individuals and adds them and...
	// ...a random bool to the unordered_map.
	for (Clause c : clauses) {
		addclause = c.clauses();

		for (int s : addclause) {

			if (model.count(s) == 0) 
				model[s] = std::rand() % 2;
		}
	}
}

// Constructor for the algorthim
void Walksat::Walksat(std::string filename) {	
	getclauses(filename);
	newmodel(clauses);
}

// Main funcition
int main (int argc, char* argv[]) {
	// Checks correct arguments have been used
	if (argc != 2) {
		std::cout << "Usage is ./WalkSAT <filename>" << std::endl;
		exit(0);
	}

	Walksat walksat = Walksat(filename);

	int result = walksat.algorthim();
	std::cout << "\rWalkSat flips: " << result << std::endl;
}	