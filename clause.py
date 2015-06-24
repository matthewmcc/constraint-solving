import random

# Stores all symbols of a given clause
class Clause:
	def __init__(self, clauseStr):
		# If bool is True symbol is negated
		self.clause = {}
		cArray = clauseStr.split();
		for c in cArray:
			if c.startswith('-'):
				self.clause[c.replace("-", "")] = True
			else:
				self.clause[c] = False

	# Checks if clause satisfies given the model
	# returns --> None for incomplete or True for consistant or False for inconsistant
	def satisfies(self, model):
		result = False
		for c in self.clause:
			if model[c] == None:
				return None
			# Symbol is negated
			if self.clause[c]:
				result = not model[c]
			# Symbol is not negated
			else:
				result = model[c]

			if result != None and result:
				break

		return result

	# returns --> A unit-clause symbol or a False bool
	def isUnitClause(self, model):
		undefined = None
		amountUndefined = 0
		result = None

		# Checks if a cnf has only False values and one undefined given the model
		for c in self.clause:
			if model[c] == None:
				undefined = c
				amountUndefined += 1
			# Symbol is negated
			elif self.clause[c]:
				result = not model[c]
			# Symbol is not negated
			else:
				result = model[c]

			# If a symbol equal True or there is more than one undefined symbol False is returned
			if result == True or amountUndefined != 1:
				return False

		# Returns undefined symbol with negation symbol
		if self.clause[undefined]:
			return "-" + undefined
		else:
			return undefined

		return False

	# returns --> True if clause contains negative symbol
	# or False if postive symbol
	# or None if symbol not in clause
	def contains(self, symbol):
		if symbol in self.clause:
			return self.clause[symbol]

		return None

	# returns --> Random clause
	def randomClause(self):
		keyList = list(self.clause.keys())
		return random.choice(keyList)
