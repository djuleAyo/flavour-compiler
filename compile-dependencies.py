import sys
import os.path

#compile given module - this will generate .d in build
os.system("make build/"+sys.argv[1] + ".o")

#open generated .d file
neededHeadersFile = open("build/" + sys.argv[1] + ".d", "r")
neededHeaders = neededHeadersFile.read()

dependencies = []

for header in neededHeaders[2:].split(' '):
    if os.path.isfile(header.replace("include", "src").replace(".h", ".c")):
        objPath = header.replace("include", "build").replace(".h", ".o")
        if objPath[-2:] == ".o":
            print "========================================"
            print objPath
            print "========================================"

            os.system("make "+objPath)
            dependencies.append(objPath)

compileTest = "gcc -g -Iinclude -Wall -Wextra " + sys.argv[1]+"Test.o -o test/"+sys.argv[1]

for dep in dependencies:
    compileTest += " "+dep

print "========================================"
print compileTest
print "========================================"

os.system(compileTest);
