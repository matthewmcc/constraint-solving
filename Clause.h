#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>

class Clause {
	int cArray[3];
	bool typeArray[3]; // false if negated else true
	public:
		Clause (std::string);

		// TESTING //
		void printclause(const std::unordered_map<int, bool> &model) const {
			for (int j = 0; j < 3; j++) {
				std::cout << cArray[j] << " | " << typeArray[j] << " | " << model.at(cArray[j]) << std::endl;
			}
		}

		// Returns a vector of the symbols
		std::vector<int> clauses() const {
			std::vector<int> c;

			for (int s : cArray) {
				c.push_back(s);
			}

			return c;
		}

		// Returns the clauses value under the given model.
		bool satisfies (const std::unordered_map<int, bool> &model) const {
			for (int i = 0; i < 3; i++) {
				if (model.at(cArray[i]) == typeArray[i]) {
					return true;
				}
			}
			return false;
		}

		// Return a random clause symbol
		int randomClause() const {
			return cArray[std::rand() % 3];
		}
};

// Constructor of the Clause class
Clause::Clause(std::string clause) {
	std::istringstream iss(clause);
	std::string s;
	int i = 0;

	while (getline(iss, s, ' ')) {
		if(s[0] == '-') {
			typeArray[i] = false;
			cArray[i] = stoi(s.substr(1, s.size() - 1));
		}
		else {
			typeArray[i] = true;
			cArray[i] = stoi(s);
		}
		i++;
	}
}