#ifndef TEST_BEA_HPP
  #define TEST_BEA_HPP
  
  #include "../BEA.hpp"
  #include "testSchedule.hpp"

  #include <iostream>
  #include <chrono>
  using namespace std;

  vector<double> Kopanos2( {3.1, 3.7, 3.3, 2.7, 2.5, 3.6, 3.2, 3.5, 2.9, 1.4, //i1-10
                            1.3, 1.2, 0.1, 3.4, 0.2, 0.4, 0.3, 1.5, 1.1, 2.3, //i11-20
                            2.6, 2.4, 2.1, 2.8, 2.2} );                       //i21-25

  void testBEA(const Problem* problem, int maxIterations, double timeLimit){
    BEA test(problem);
    double currentBest = -1;
    int generation=0, lastImprovement=0;
    auto start = chrono::high_resolution_clock::now();
    double bestTime = 0;
    chrono::duration<double> elapsed;
    do{
      elapsed = chrono::high_resolution_clock::now() - start;
      if (currentBest != test.getCurrentBestValue()) {
        bestTime = elapsed.count();
        lastImprovement = generation;
        currentBest = test.getCurrentBestValue();
        printf("%.3lf s (gen %4d): Found new best solution with value %g\n", elapsed.count(), generation, currentBest);
//      } else if (generation%100 == 0) {
//        cout<<setw(4)<<generation<<": (";
//        for(auto it: test.getCurrentValues())
//          cout<<it<<" ";
//        cout<<")\n";
      }
      generation++;
      test.evolve();
    } while (elapsed.count() < timeLimit && generation < maxIterations);

    printf("Completed %d iterations in %3.3lf sec\n", generation, elapsed.count());
    printf("Best solution was found after %d iterations in %3.3lf sec:\n", lastImprovement, bestTime);
    printSchedule(test.getCurrentBestSolution());
    printMinEarlinessFinishTimes(test.getCurrentBestSolution());

//    Schedule optimal(problem);
//    optimal.loadPriorities(Kopanos2);
//    printSchedule(optimal);
//    printMinEarlinessFinishTimes(optimal);
  }

#endif
