#include "Problem.hpp"
#include "Schedule.hpp"
#include "BEA.hpp"

#include "test/testProblem.hpp"
#include "test/testBEA.hpp"

#include<iostream>


int main(int argc, char** argv){
  if (argc==1) {
    std::cout<<argv[0]<<" inputfile [maxiterations] [localpoolsize] [populationsize] [bestkeep] [new] [crossover]\n";
  } else {
    Problem testProblem(argv[1], Problem::TotalEarliness);
//    printProblem(testProblem);
    int iterations = 100;
    if(argc>2) iterations=atoi(argv[2]);
    if(argc>3) Schedule::localPoolSize=atoi(argv[3]);
    if(argc>4) BEA::populationSize=atoi(argv[4]);
    if(argc>5) BEA::bestKeepCount=atoi(argv[5]);
    if(argc>6) BEA::newCount=atoi(argv[6]);
    if(argc>7) BEA::crossoverCount=atoi(argv[7]);
    testBEA(&testProblem, iterations);
  }
}
