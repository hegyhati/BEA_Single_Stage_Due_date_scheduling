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
      static unsigned int populationSize;
      static unsigned int bestKeepCount;
      static unsigned int crossoverCount;
      static unsigned int newCount;
      
      
      BEA(const Problem* problem, unsigned int size=populationSize);
      double evolve();
      std::vector<double> getCurrentValues() const;
      double getCurrentBestValue();
      Schedule getCurrentBestSolution();
  };
#endif
