#ifndef BEA_HPP
  #define BEA_HPP
  
  #include "Problem.hpp"
  #include "Schedule.hpp"
  #include <list>
  #include <map>
  
  class BEA {
    private:
      std::map<double,Schedule> population;
      const Problem& problem;
      
    public:
      static int populationSize;
      static int bestKeepCount;
      static int crossoverCount;
      static int newCount;
      
      
      BEA(const Problem& problem, int size=populationSize);
      double evolve();
      std::list<double> getCurrentValues() const;
      double getCurrentBestValue() const;
      Schedule getCurrentBestSolution() const;
  };
#endif
