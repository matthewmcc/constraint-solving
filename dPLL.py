import argparse
import copy
import re

from clause import *

# returns --> True if given cnf is satisfiable or False
def dPLLSAT(s):
	clauses = parseFile(s)
	symbols = getSymbols(clauses)
	model = createModel(symbols)

	return dPLL(clauses, symbols, model)

# Calls DPLL algorithm
def dPLL(clauses, symbols, model):
	# All clauses are true under model
	for clause in clauses:
		result = clause.satisfies(model)
		if (result == None) or (not result): break
	if result: return True

	# Some clause is false under model
	for clause in clauses:
		result = clause.satisfies(model)
		if result != None and not result:
		 	return False

	# Finds pure symbol
	p = False
	for symbol in symbols:
		symType = None

		# Checks every clause to see if symbol is pure
		for clause in clauses:
			result = clause.contains(symbol)
			if symType == None or symType == result:
				symType = result
			else:
				result = None
				break

		# Remove from symbol list and adds the new value to model list.
		if result != None:
			symbols.remove[symbol]
			model[symbol] = not result
			p = True

	# If a pure symbol has been found then run DPLL
	if p: return dPLL(clauses, symbols, model)

	# Clauses contains a unit clause
	p = False
	for clause in clauses:
		result = clause.isUnitClause(model)

		if result != False:
			# Run dPLL with new model 
			if result.startswith('-'):
				model[result.replace("-", "")] = False
			else:
				model[result] = True

			# Remove new defined symbol from list
			symbols.remove(result.replace("-", ""))
			p = True
	
	# If a unit clause has been found then run DPLL
	if p: return dPLL(clauses, symbols, model)

	# Takes the last unused symbol and runs dPLL with the symbol equaling True and False
	sym = symbols.pop()
	model[sym] = True
	result = dPLL(clauses, symbols, model)
	if result:
		return result
	else:
		model[sym] = False
		return dPLL(clauses, symbols, model)

# Creates a None model with all symbols
def createModel(symbols):
	model = {}
	for symbol in symbols:
		model[symbol] = None

	return model

# Creates a list of all symbols in the cnf
def getSymbols(clauses):
	symbols = []

	for santa in clauses:
		for symbol in santa.clause:
			if symbol not in symbols:
				symbols.append(symbol)

	return symbols

# Parses the given CNF file in array and dimenson values. Also gathers all clauses in a list
def parseFile(f):
	line = f.readline()
	nums = re.findall(r'\d+', line)

	varNums = int(nums[0])
	numClauses = int(nums[1])

	i = 0
	clauses = []
	while i < numClauses:
		line = f.readline().rstrip()
		clause = Clause(line)
		clauses.append(clause)
		i += 1
	return clauses

# Command Line Parser
parser = argparse.ArgumentParser(description='Runs WalkSAT on given file and produces a table of results')
parser.add_argument('filename', action="store")
args = parser.parse_args()
locals().update(vars(args)) 

f = open(filename, 'r')

result = dPLLSAT(f)
if result: print "Satisfiable"
else: print "Unsatisfiable"