#!/usr/bin/python
# __author__ = "Kunal Sinha"

import sys

def euclid(a, b):
    if b == 0:
        return a
    else:
        return euclid(b, a%b)
    
def main():
    while(True):
        print "Enter numbers whose gcd has to be calculated (-1 to end):"
        a = int(raw_input("Enter first number: "))
        if a == -1:
            sys.exit(1)
        b = int(raw_input("Enter second number: "))
        print euclid(a, b)

if __name__ == '__main__':
    main()
