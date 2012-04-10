#!/usr/bin/python
# 4.6.2012
# codelish.py

# You can drop down to Python code whenever you need it.


# Namespace util methods
def lookupInNamespace(key,namespace):
	if not isinstance(namespace, dict):
		print('Not a proper namespace.')
		return None
	if namespace == []:
		return None
	elif key in namespace[-1]:
		return namespace[-1][key]
	else:
		return lookupInNamespace(key,namespace[:-1])

# --- Machine ---
class Machine:
	def __init__(self):
		self.program = None
			# program is a list of commands.
			# Each command is a 2-tuple,
			# Where the first entry of the command is a string
			# describing the type of command, and the second entry
			# depends on the first entry.
			
		self.namespace = None
			# namespace is a list of dicts.
			# The dict on top (i.e. namespace[-1]) represents the 
			# most local namespace, whereas
			# namespace[0] represents the global namespace.
		
		self.stack = None
			# stack (list) of function call pointers.
		
		self.pc = None
			# program counter
		
	def loadProgram(self, program):
		self.program = [cmd for cmd in program ]
		self.namespace = [ {} ]
		self.stack = []
		self.pc = 0
		return self
		
	# Execute program.
	def execute(self):
		while self.step():
			pass
		return self
		
	# Execute a single command.
	def step(self):
		# Three kinds of commands.
		
		# 1. Python Code.
		if self.program[self.pc][0] == 'PYTHON':
			exec(compile(self.program[self.pc][1],'<string>','exec'))
			self.pc += 1
		# 2. Begin function declarations.
		elif self.program[self.pc][0] == 'BEGIN':
			self.namespace[-1][self.program[self.pc][1]] = self.pc
			while self.program[self.pc][0] != 'END':
				self.pc += 1
		# 3. End function declaration.
		elif self.program[self.pc][0] == 'END':
			# Simply go on.
			self.pc += 1
		# 4. Call function.
		elif self.program[self.pc][0] == 'CALL':
			self.pc += 1
		# 5. Return from function call.
		elif self.program[self.pc][0] == 'RETURN':
			self.pc += 1
			
		# check if it is ready to end the program.
		if self.pc < 0 or self.pc >= len(self.program):
			return False
		else:
			return True
		
		
# --- Controller ---
def main():
	p = [
		('PYTHON', "print('hello world.')"),
		('PYTHON', "print(self.pc)"),
		('PYTHON', "print(self.namespace)"),
		('BEGIN', ( 'This', 'is' ) ),
		('END', 0),
		('PYTHON', "print(self.namespace)"),
	]
	m = Machine().loadProgram(p)
	m.execute()
	
if __name__ == '__main__':
	main()
