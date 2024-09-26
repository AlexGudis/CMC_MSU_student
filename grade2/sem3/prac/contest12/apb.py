import sys

el = 1
for i in range(1, len(sys.argv)):
    el *= int(sys.argv[i])
print(el)
