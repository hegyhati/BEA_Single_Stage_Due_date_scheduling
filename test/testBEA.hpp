#ifndef TEST_BEA_HPP
  #define TEST_BEA_HPP
  
  #include "../BEA.hpp"
  #include "testSchedule.hpp"

  #include <iostream>
  using namespace std;

  vector<double> Kopanos2( {3.1, 3.7, 3.3, 2.7, 2.5, 3.6, 3.2, 3.5, 2.9, 1.4, //i1-10
                            1.3, 1.2, 0.1, 3.4, 0.2, 0.4, 0.3, 1.5, 1.1, 2.3, //i11-20
                            2.6, 2.4, 2.1, 2.8, 2.2} );                       //i21-25

  void testBEA(const Problem* problem, int maxIterations){
    BEA test(problem);
    double currentBest = -1;
    int generation=0, lastImprovement=0;
    do{
      if (currentBest != test.getCurrentBestValue()) {
        lastImprovement = generation;
        currentBest = test.getCurrentBestValue();
        cout<<setw(4)<<generation<<": Found new best solution with value " << currentBest << endl;
//      } else if (generation%100 == 0) {
//        cout<<setw(4)<<generation<<": (";
//        for(auto it: test.getCurrentValues())
//          cout<<it<<" ";
//        cout<<")\n";
      }
      generation++;
    } while (test.evolve()!=0 || generation < maxIterations);

    cout<<"Completed "<<generation<<" iterations. Best solution was found after "<<lastImprovement<<" iterations:\n";
    printSchedule(test.getCurrentBestSolution());
    printMinEarlinessFinishTimes(test.getCurrentBestSolution());

//    Schedule optimal(problem);
//    optimal.loadPriorities(Kopanos2);
//    printSchedule(optimal);
//    printMinEarlinessFinishTimes(optimal);
  }

#endif
