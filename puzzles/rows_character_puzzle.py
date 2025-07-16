import math
import itertools
import functools

letters_map = ['A','B','C','D','E','F','X']

# all letters available
# letters = ['A','B','C','D','E','F','X']
letters = [0, 1, 2, 3, 4, 5, 6]

# Print row in readable format
def print_row(*cells):
    ret = ''
    for c in cells:
        for l in c:
            ret += letters_map[l]
        ret += ' '
    print(ret)

# letters available for each cell at given column index
cell_letters = []
for i in range(6):
    l = letters.copy()
    del l[i]
    cell_letters.append(l)


def list_has_dups(l):
    return len(l) != len(set(l))

def check_slots_slow(*cells):
    for slot in range(6):
        elems = list(map(lambda c: c[slot], cells))
        if list_has_dups(elems):
            return False
    return True
        

# Make sure no cell has same letter in same slot as another cell
def check_slots(*cells):
    slots = [0,0,0, 0,0,0, 0]
    for c in range(len(cells)):
        for s in range(6):
            l = cells[c][s]
            if slots[l] & (1 << s):
                return False
            slots[l] |= (1 << s)
    return True

# Generate all possible rows
for c0 in itertools.permutations(cell_letters[0]):
    for c1 in itertools.permutations(cell_letters[1]):
        if not check_slots(c0, c1):
            continue
        for c2 in itertools.permutations(cell_letters[2]):
            if not check_slots(c0, c1, c2):
                continue
            for c3 in itertools.permutations(cell_letters[3]):
                if not check_slots(c0, c1, c2, c3):
                    continue
                for c4 in itertools.permutations(cell_letters[4]):
                    if not check_slots(c0, c1, c2, c3, c4):
                        continue
                    for c5 in itertools.permutations(cell_letters[5]):
                        if not check_slots(c0, c1, c2, c3, c4, c5):
                            continue
                        print_row(c0, c1, c2, c3, c4, c5)
