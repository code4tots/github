# some modular arithmetic stuff
# 3.4.2012

# Left Hand Side
def LHS(m):
	return ( (m ** 6) - ( 3 * (m ** 3) ) + 3 )
	
# Right Hand Side
def RHS(p):
	return (p ** 3)
	
'''
for m in range(1000):
	for p in range(1000):
		if LHS(m) == RHS(p):
			print( "m:%d=>%d, p:%d=>%d" % (m,LHS(m),p,RHS(p)) )
'''
		
m = 1
print (m ** 6) - (3 * (m ** 3) )
