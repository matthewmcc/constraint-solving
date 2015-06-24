import argparse
import re
import random
import copy
import pprint

from clause import *

# Checks if cnf given model satisifes
def SAT(clauses, model):
	for clause in clauses:
		if not clause.satisfies(model):
			return False
	return True

# WalkSAT 
def WalkSAT(clauses, p, MAXFLIPS):
	# Assigns random boolean to all possible values in clauses

	model = newModel(clauses)
	symbols = getSymbols(clauses)
	model = newModel(symbols)

	global currentFlips
	currentFlips = 0
	# test = 0

	while currentFlips < MAXFLIPS:

		# If the current model is logically true under the clause it's returned
		if SAT(clauses, model) != False:
			return model

		# Searches for a random clause the equals false given the current model
		clause = random.choice(clauses)
		while not clause.satisfies(model):
			clause = random.choice(clauses)

		r = random.uniform(0, 1)
		ran = decision(p)
		# Flips randomly selected symbol in clause
		if ran < p:
			symbol = clause.randomClause()
			model[symbol] = not model[symbol]

		# Flip whichever symbol in clause maximizes the number of satisfied clauses
		else:
			symbolsToFlip = clause.clause.keys()
			flip = None
			trueClauses = 0

			# Flips every model in clause one by one
			for symbol in symbolsToFlip:
				mod = copy.deepcopy(model)

				mod[symbol] = not mod[symbol]

				j = 0
				# Checks clauses with new model for most True clauses
				for cl in clauses:
					if cl.satisfies(mod):
						j += 1

				if j > trueClauses:
					trueClauses = j
					flip = symbol

			# Flips maximising symbol
			model[flip] = not model[flip]

		currentFlips += 1
	# Returns failure if 
	return False

# Returns random bool given probability
def decision(probability):
    return random.random() < probability

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

# Randomly assigns a boolean value for all variables in model
def newModel(symbols):
	model = {}
	for symbol in symbols:
		# Assigns random boolean value to d[i]
		model[symbol] = bool(random.getrandbits(1))

	return model

# Creates a list of all symbols in the cnf
def getSymbols(clauses):
	symbols = []

	for santa in clauses:
		for symbol in santa.clause:
			if symbol not in symbols:
				symbols.append(symbol)

	return symbols

# Command Line Parser
parser = argparse.ArgumentParser(description='Runs WalkSAT on given file and produces a table of results')
parser.add_argument('filename', action="store")
parser.add_argument('-p', action="store", default=0.5,
					help='Probability of having to do a ramdom walk')
parser.add_argument('-M', action="store", default=10**7,
					help='Number of flips allowed before giving up')
args = parser.parse_args()
locals().update(vars(args)) 

# Opens file containing clauses and parses them
f = open(filename, 'r')
clauses = parseFile(f)

plist = []

if isinstance(M, str):
	M = int(eval(M))

result = WalkSAT(clauses, p, M)

if result == False:
	print (M)
else:
	print (currentFlips)
