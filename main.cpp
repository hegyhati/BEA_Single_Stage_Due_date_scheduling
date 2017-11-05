#include "Problem.hpp"
#include "Schedule.hpp"
#include "BEA.hpp"

#include "test/testProblem.hpp"
#include "test/testBEA.hpp"

#include<iostream>
using namespace std;

int main(int argc, char** argv){
  if (argc==1) return 1;
  else {
    Problem testProblem(argv[1]);
    printProblem(testProblem);
    testBEA(testProblem);
  }
}
