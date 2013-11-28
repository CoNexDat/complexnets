"""Script which fits a power law to the input data.

Data is read from stdin and should be formatted as:
line1
line2
...
Degrees:
1 2 3 ..... 4 5 
line k
line k+1
....
eof

The script will echo any line that is unrecognized.

The script requires several dependencies, mainly powerlaw 
and any transitive dependencies, which include:

-powerlaw
-numpy
-scipy
-mpmath

Check the appropiate readme for instructions.


"""
import sys
import powerlaw

flag = False
data = []
for line in sys.stdin.readlines():
    if line.startswith('Degrees:'):
	flag = True
    elif flag:
	data = [int(x) for x in line.split()]
	flag = False
    else:
	print line
results = powerlaw.Fit(data, discrete=True)
print 'Exponent of power law:'
print results.power_law.alpha
print 'xmin of power law:'
print results.power_law.xmin
R, p = results.distribution_compare('power_law', 'lognormal')
print 'loglikehood ratio of powerlaw and normal distribution:'
print R
print 'p-value of powerlaw vs lognormal'
print p