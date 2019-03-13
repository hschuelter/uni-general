class Queue:
	def __init__(self):
		self.items = []

	def put(self, item):
		self.items.append( item )

	def pop(self):
		return self.items.pop(0)

	def size(self):
		return len(self.items)

	def first(self):
		return self.items[0]

	def printIt(self):
		print( self.items )

	def isEmpty(self):
		if self.size() == 0:
			return True
		else:
			return False
