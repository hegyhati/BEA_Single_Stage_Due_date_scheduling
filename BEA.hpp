#ifndef BEA_HPP
  #define BEA_HPP
  
  #include "Problem.hpp"
  #include "Schedule.hpp"
  #include <vector>
  
  class BEA {
    private:
      std::vector<Schedule> population;
      const Problem* problem;
      
    public:
      static int populationSize;
      static int bestKeepCount;
      static int crossoverCount;
      static int newCount;
      
      
      BEA(const Problem* problem, int size=populationSize);
      double evolve();
      std::vector<double> getCurrentValues() const;
      double getCurrentBestValue();
      Schedule getCurrentBestSolution();
  };
#endif
