# Kopanos, G. M.; Lainez, J. M. & Puigjaner, L.
# An Efficient Mixed-Integer Linear Programming Scheduling Framework for Addressing Sequence-Dependent Setup Issues in Batch Plants
# Industrial & Engineering Chemistry Research, 2009, 48, 6346-6357


# Single stage
# sequence dependent setup times
# combined intermediate and general precedence


########################################
## Basic sets ##########################
########################################

set I; # orders
set J; # units

########################################
## Parameters ##########################
########################################

param M := 1000; # big M
param pt {i in I,  j in J} >= 0, default M;
  # processing time of order i in unit j
param csd {i in I, i2 in I, j in J: i!=i2} >=0, default 0;
  # sequence dependent setup cost
param D {i in I} >=0;
  # due date of order I
param Hor>=0, default M; # time horizon
param ro {i in I} >=0, default 0;
  # release time of order i
param ru {j in J} >=0, default 0;
  # ready time of unit j
param sd {i in I, i2 in I, j in J: i!= i2} >=0, default M;
  # sequence dependent setup time of order i an i2 in unit j
param su {j in J} >=0, default 0;
  # sequence independent setup time of unit j
param alpha {i in I} >=0, default 0;
  # weighting coefficient for earliness of order i
param beta {i in I} >=0, default 0;
  # weighting coefficient for tardiness or order i

########################################
## Derived sets ########################
########################################

set Ji {i in I} := # set of units, that can process order i
 setof { j in J: pt[i,j] != M} j;

########################################
## Variables ###########################
########################################

var C {i in I} >=0; # completion time of order i
var Pos {i in I, i2 in I, j in J: i!=i2} >=0;
  # position difference between orders i and i2 if allocated to unit j
var E {i in I} >=0; # earliness of order i

var Seq {i in I, i2 in I, j in Ji[i] inter Ji[i2]: i!= i2 }, binary;
  # order i is processed immediately before i2 in unit j
var X {i in I, i2 in I, j in Ji[i] inter Ji[i2]: i!= i2}, binary;
  # order i is processed before i2 in unit j
var Y {i in I, j in Ji[i]}, binary;
  # order i is processed in unit j


########################################
## Constraints #########################
########################################

s.t. Allocation {i in I}:
  sum{j in Ji[i]} Y[i,j] = 1;

s.t. Timing {i in I}:
  C[i] >= sum {j in Ji[i]} (Y[i,j] * (max(ru[j],ro[i]) + pt[i,j] + su[j]));

s.t. Sequencing_Timing {i in I, i2 in I, j in Ji[i] inter Ji[i2]: i!=i2}:
  C[i] + sd[i,i2,j] * Seq[i,i2,j] <=
    C[i2] - pt[i2,j] - su[j] + M * (1-X[i,i2,j]);

s.t. Sequencing_Allocation_4 {i in I, i2 in I, j in Ji[i] inter Ji[i2]: i!=i2}:
  X[i,i2,j] + X[i2,i,j] + 1 >= Y[i,j] + Y[i2,j];

s.t. Sequencing_Allocation_5 {i in I, i2 in I, j in Ji[i] inter Ji[i2]: i!=i2}:
  2* (X[i,i2,j] + X[i2,i,j]) <= Y[i,j] + Y[i2,j];

s.t. Position_difference {i in I, i2 in I, j in Ji[i] inter Ji[i2]: i!=i2}:
  Pos[i,i2,j] = sum {i3 in I: i3!=i and i3!=i2 and j in Ji[i3]} (X[i,i3,j]-X[i2,i3,j]) + M * (1-X[i,i2,j]);

s.t. Sequencing_position {i in I, i2 in I, j in Ji[i] inter Ji[i2]: i!=i2}:
  Pos[i,i2,j] + Seq[i,i2,j] >= 1;

s.t. Immediate_precedence {i in I}:
  sum {i2 in I: i != i2} sum {j in Ji[i] inter Ji[i2]} Seq[i,i2,j] <= 1;

s.t. Earliness {i in I}: E[i]>=D[i]-C[i];

s.t. Tardiness_forbidden {i in I}: C[i]<=D[i];

minimize earliness:
  sum{i in I} E[i];


end;
