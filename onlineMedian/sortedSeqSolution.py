import bisect
from bisect import bisect_left
import datetime

a = datetime.datetime.now()

num = []

def binary_search(a, x, lo=0, hi=None):   # can't use a to specify default for hi
	hi = hi if hi is not None else len(a) # hi defaults to len(a)   
	pos = bisect_left(a,x,lo,hi)          # find insertion position
	return (pos if pos != hi and a[pos] == x else -1) # don't walk off the end

# remove this portion
# fpIn = open('dataSet.txt', 'r')
fpOut = open('output.txt', 'w')

while 1:
#	s = fpIn.readline().splitlines()[0]
	
	s = raw_input()
	if s == 'e':
		break
	
	if s == 'm':
		length = len(num)
		if length is not 0:
			if length % 2 == 0:
				median =  ( float( num[length/2] + num[length/2 - 1] )/2 )
			else:
				median = num[(length+1)/2 - 1]
			fpOut.write( '%d\n'%median if median == int(median) else '%s'%median )
			# print median
			# print '%d\n', %median if median == int(median) else '%s'%median
	else:
		val = int(s)
		bisect.insort_left(num, val)
		length = len(num)		
# fpIn.close()
fpOut.close()

b = datetime.datetime.now()
print (b-a)
