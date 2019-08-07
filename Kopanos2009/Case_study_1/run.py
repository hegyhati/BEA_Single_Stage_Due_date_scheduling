#!/usr/bin/env python

import sys
import subprocess
from gurobipy import *

glpsolArgs = ["glpsol", "-m", "..\\Kopanos2009_me.m", "--check", "--wlp", "converted.lp", "-d"]

for size in range(15, 26):
    subprocess.check_call(glpsolArgs + [ "%d.d" % (size) ])

    model = read("converted.lp")
    model.Params.timeLimit = 300.0
    model.optimize()
    if model.SolCount == 0:
        print "No feasible solution was found. Aborting..."
        quit()
    model.write("solution%d.sol" % (size))