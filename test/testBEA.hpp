#ifndef TEST_BEA_HPP
  #define TEST_BEA_HPP
  
  #include "../BEA.hpp"
  #include "testSchedule.hpp"

  #include <iostream>
  using namespace std;

  void testBEA(const Problem* problem, int maxIterations){
    BEA test(problem,maxIterations);
    int generation=0;
    do{
      cout<<setw(3)<<generation<<": (";
      for(auto it: test.getCurrentValues())
        cout<<it<<" ";
      cout<<")\n"; 
      generation++;     
    } while (test.evolve()!=0 || generation < 100);
    printSchedule(test.getCurrentBestSolution());
  }

#endif
