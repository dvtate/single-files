#!/bin/python3
# https://www.hackerrank.com/challenges/cloudy-day

import math
import os
import random
import re
import sys

#
# Complete the 'maximumPeople' function below.
#
# The function is expected to return a LONG_INTEGER.
# The function accepts following parameters:
#  1. LONG_INTEGER_ARRAY p - populations of the towns
#  2. LONG_INTEGER_ARRAY x - locations of the towns
#  3. LONG_INTEGER_ARRAY y - locations of the clouds
#  4. LONG_INTEGER_ARRAY r - ranges of the clouds
#

def maximumPeople(p, x, y, r):
    # Find population covered by each cloud
    cloud_pops = []
    cloudy_towns = set()
    for i, c in enumerate(y):
        pop = 0
        for j, town in enumerate(x):
            if town >= c - r[i] and town <= c + r[i]:
                pop += p[j]
                cloudy_towns.add(j)
        cloud_pops.append(pop)
    #print(p, x, y, r)
    #print(cloud_pops)
    #print(cloudy_towns)
    
    # Find max population covered by single cloud
    if len(cloud_pops) == 0:
        return sum(p)
    max_cloud_i = 0
    max_cloud_p = cloud_pops[0]
    for i, pop in enumerate(cloud_pops):
        if pop > max_cloud_p:
            max_cloud_p = pop
            max_cloud_i = i
    
    cloudy_towns = set()
    for i, c in enumerate(y):
        if i == max_cloud_i:
            continue
        for j, town in enumerate(x):
            if town >= c - r[i] and town <= c + r[i]:
                cloudy_towns.add(j)
        cloud_pops.append(pop)
        
        
    # Calculate population covered by altered sky
    ret = 0
    for i, pop in enumerate(p):
        if i not in cloudy_towns:
            ret += pop
    return ret
    
    
    

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input().strip())

    p = list(map(int, input().rstrip().split()))

    x = list(map(int, input().rstrip().split()))

    m = int(input().strip())

    y = list(map(int, input().rstrip().split()))

    r = list(map(int, input().rstrip().split()))

    result = maximumPeople(p, x, y, r)

    fptr.write(str(result) + '\n')

    fptr.close()
