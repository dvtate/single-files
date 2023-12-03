#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'timeConversion' function below.
#
# The function is expected to return a STRING.
# The function accepts STRING s as parameter.
#

def timeConversion(s):
    L = s.split(':')
    lint = int(L[0])
    if L[2][2] == 'P':
        if lint == 12:
            return '%s:%s:%s' % (L[0], L[1], L[2][0:2])
        lint += 12
        return '%s:%s:%s' % (lint, L[1], L[2][0:2])
    else:
        if lint == 12:
            return '00:%s:%s' % (L[1], L[2][0:2])
        else:
            return '%s:%s:%s' % (L[0], L[1], L[2][0:2])
    
if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    s = input()

    result = timeConversion(s)

    fptr.write(result + '\n')

    fptr.close()
