#!/usr/bin/python

#Opening a file
fo = open("sample.txt", "ab+")
print "Name of the file: ", fo.name
print "Closed or not: ", fo.closed
print "Opening mode: ", fo.mode
print "Softspace flag: ", fo.softspace

#Reading the file
str = fo.read(20)
print "Content read from the file is : ", str

#Writing content in the file
fo.write("This is the first time I am writing in a file through Python script. The experience is similar to C files\n")
#Closing the opened file
fo.close()
print "Closed or not: ", fo.closed


