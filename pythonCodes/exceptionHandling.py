#!/usr/bin/python

def division(num1, num2):
	assert(num2>0), "Division not possible by 0!!"
	return (num1/num2)
	
print(division(3,2))
print division(3,0)
