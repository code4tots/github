#!/usr/bin/python

class TreeOfLife:
	def __init__(self):
		self.no = None
		self.yes = None
		self.question = ""
	
root = None

def answer(query):
	# If we hit uncharted territory,
	if query == None:
		
