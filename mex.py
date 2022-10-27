# Minimum int not in the arr
def mex(arr):
	s = set(arr)
	m = max(arr)
	for i in range(0, m):
		if i not in s:
			return i
	return 0	
	
# highest possible mex accheivable by reducing ints in array
# O(N^3) - there is probably a better algorithm
def game(arr):
	# Elements < mex need to be in order
	ls = sorted(arr)						# ls = sorted list of elements
	for i in range(0, len(arr)):			# For each n on 0 .. len 
		if i not in ls:						# If not in list
			for j in range(len(ls)):		# Find first element greater than this to reduce
				if ls[j] > i:
					ls[j] = 0
					break
			else:							# No elements greater than this thus it's mex
				return i
	else:									# Edge case: all elements included in order
		return len(arr)
			
print(game([3,2,3]))			# 3
print(game([0,0,2,3,4,6,7]))	# 6
print(game([55,0,1,2,1,9,11])) # 6


