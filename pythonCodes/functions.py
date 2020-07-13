#!/usr/bin/python

#Function Definitions
#========================================
def add2Nums(n1, n2):
	"Function for adding 2 variables"
	result = n1 + n2
	print result
	return

def changeme(list):
	"This changes a passed list into this function"
	mylist = [1,2,3,4]
	print "Values inside the function:", mylist
	return
	
#=======================================

##########MAIN BODY ##################
	
add2Nums(2,3)

mylist = [10,20,30]
changeme(list)
print "Values outside the function: ", mylist



