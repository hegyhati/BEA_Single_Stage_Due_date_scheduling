#ifndef TEST_BEA_HPP
  #define TEST_BEA_HPP
  
  #include "../BEA.hpp"
  #include "testSchedule.hpp"

  #include <iostream>
  using namespace std;

  void testBEA(const Problem* problem, int maxIterations){
    BEA test(problem,maxIterations);
    double currentBest = -1;
    int generation=0;
    do{
      if (currentBest != test.getCurrentBestValue()) {
        currentBest = test.getCurrentBestValue();
        cout<<setw(4)<<generation<<": Found new best solution with value " << currentBest << endl;
      } else if (generation%100 == 0) {
        cout<<setw(4)<<generation<<": (";
        for(auto it: test.getCurrentValues())
          cout<<it<<" ";
        cout<<")\n";
      }
      generation++;
    } while (test.evolve()!=0 || generation < 3000);
    printSchedule(test.getCurrentBestSolution());
    printMinEarlinessFinishTimes(test.getCurrentBestSolution());
  }

#endif
