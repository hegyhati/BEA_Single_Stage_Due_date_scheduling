#ifndef SCHEDULE_HPP
  #define SCHEDULE_HPP

  #include <vector>
  
  #include "Problem.hpp"
  
  class Schedule {
    private:
      std::vector<double> priorities;
      double objective;
      void localsearch(unsigned int job);
      void newpriority(unsigned int job, double change);

      double calculateObjectiveValue() const;
      double calculateTotalLateness() const;
      double calculateTotalEarliness() const;

    public:
      static unsigned int localPoolSize;
      static double mutationRange;
      const Problem* problem;
      Schedule(const Problem* problem);

      double getObjectiveValue();
      void mutate();
      void loadPriorities(const std::vector<double> &priorities);

      double getPriority(unsigned int job) const;
      Schedule operator&& (const Schedule& other) const;
      bool operator< (Schedule& other);
  };
#endif
