import sys

def SystemInclude(line):
    return (line.find("#include") != -1 and line.find(".hpp") == -1)

def UserInclude(line):
    return (line.find("#include") != -1 and line.find(".hpp") != -1)

def Add(fileName, addedFiles, includeSet, usingSet, mergedCode):
    addedFiles.add(fileName)
    for line in open(fileName, "r").readlines():
        if (SystemInclude(line)):
            includeSet.add(line)
            continue
        if (UserInclude(line)):
            # Need to include the contents of this file
            begin = line.find("<") + 1
            end = line.find(">")
            includedFile = line[begin:end]
            if not includedFile in addedFiles:
                Add(includedFile, addedFiles, includeSet, usingSet, mergedCode)
            continue
        if (line.find("using") != -1):
            usingSet.add(line)
            continue
        if (line.find("#pragma once") == -1):
            mergedCode.append(line)
            continue

firstFile = sys.argv[1]
addedFiles = set()
includeSet = set()
usingSet = set()
mergedCode = []
Add(firstFile, addedFiles, includeSet, usingSet, mergedCode)

output = open("final.cpp", "w")
for line in sorted(list(includeSet)):
    output.write(line)
for line in sorted(list(usingSet)):
    output.write(line)

lastEmpty = False
for line in mergedCode:
    if (not lastEmpty or len(line) > 1):
        output.write(line)
    if (len(line) == 1):
        lastEmpty = True
    else:
        lastEmpty = False
output.close()
