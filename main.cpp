#include "Problem.hpp"
#include "Schedule.hpp"
#include "BEA.hpp"

#include "test/testProblem.hpp"
#include "test/testBEA.hpp"

#include<iostream>


int main(int argc, char** argv){
  if (argc==1) {
    std::cout<<"./a.out inputfile [localpoolsize] [population] [besteep] [new] [crosover]\n";
  } else {
    Problem testProblem(argv[1]);
    printProblem(testProblem);
    if(argc>2) Schedule::localPoolSize=atoi(argv[2]);
    if(argc>3) BEA::populationSize=atoi(argv[3]);
    if(argc>4) BEA::bestKeepCount=atoi(argv[4]);
    if(argc>5) BEA::newCount=atoi(argv[5]);
    if(argc>6) BEA::crossoverCount=atoi(argv[6]);
    testBEA(testProblem);
  }
}
