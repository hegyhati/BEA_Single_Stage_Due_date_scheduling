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

param M := 100; # big M
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
param su {i in I, j in J} >=0, default 0;
  # sequence independent setup time of order i in unit j
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
var E {i in I} >=0; # earliness of order i
var T {i in I} >=0; # tardiness of order i

var Seq {i in I, i2 in I, j in Ji[i] inter Ji[i2]: i!= i2 }, binary;
  # order i is processed immediately before i2 in unit j
var Y {i in I, j in Ji[i]}, binary;
  # order i is processed in unit j


########################################
## Constraints #########################
########################################

s.t. Allocation {i in I}:
  sum{j in Ji[i]} Y[i,j] = 1;

s.t. Timing {i in I}:
  C[i] >= sum {j in Ji[i]} (Y[i,j] * (max(ru[j],ro[i]) + pt[i,j] + su[i,j]));

s.t. Sequencing_Timing {i in I, i2 in I, j in Ji[i] inter Ji[i2]: i!=i2}:
  C[i]  <=
    C[i2] - sd[i,i2,j] - pt[i2,j] - su[i2,j] + M * (3-Seq[i,i2,j] - Y[i,j] - Y[i2,j]);


s.t. Immediate_precedence_1 {j in J}:
  sum{i in I, i2 in I: j in Ji[i] inter Ji[i2] and  i!=i2} Seq[i,i2,j] =
    sum {i in I: j in Ji[i]} Y[i,j] - 1;

s.t. Immediate_precedence_2 {i in I, j in Ji[i]}:
  sum {i2 in I: i != i2 and j in Ji[i2]} Seq[i,i2,j] <= Y[i,j];

s.t. Immediate_precedence_3 {i in I, j in Ji[i]}:
  sum {i2 in I: i != i2 and j in Ji[i2]} Seq[i2,i,j] <= Y[i,j];

s.t. Immediate_precedence_4 {i in I, i2 in I, j in Ji[i] inter Ji[i2]: i!=i2}:
  2*Seq[i,i2,j] <= Y[i,j] + Y[i2,j];

s.t. Earliness {i in I}: E[i]>=D[i]-C[i];

s.t. Tardiness {i in I}: T[i]>=C[i]-D[i];

minimize weighted_earliness_tardiness:
  sum{i in I} (alpha[i]*E[i] + beta[i]*T[i]);


end;
