import copy
import itertools
import numpy

def PowerSet(iterable):
    return list(itertools.chain.from_iterable(itertools.combinations(iterable, r) \
                    for r in range(len(iterable)+1)))

# Reads one line of integers into a single list
def ReadIntegers():
    return [int(e) for e in input().split()]

# Reads number N and N integers to follow from a single line
def ReadCountAndIntegers():
    integers = ReadIntegers()
    return integers[0], ingerers[1:]

def Array(N, value = 0):
    return numpy.full(N, copy.deepcopy(value))

def List(N, value = 0):
    return [copy.deepcopy(value) for _ in range(N)]

def List2D(N, M, value = 0):
    return List(N, List(M, value))

