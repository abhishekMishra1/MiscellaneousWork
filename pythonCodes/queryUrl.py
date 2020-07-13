#!/usr/bin/python

import urllib.parse
import urllib.request

url 		= 'http://start.csail.mit.edu/'
values 		= {'query':'What is the capital of China?'}

data 		= urllib.parse.urlencode(values)
binary_data = data.encode('ascii')
req 		= urllib.request.Request(url, binary_data)
response	= urllib.request.urlopen(req)
the_page	= response.read()

print (the_page)
