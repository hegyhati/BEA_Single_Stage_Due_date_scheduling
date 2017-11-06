#ifndef SCHEDULE_HPP
  #define SCHEDULE_HPP

  #include <vector>
  
  #include "Problem.hpp"
  
  class Schedule {
    private:
      std::vector<double> priorities;
      double lateness;
      void localsearch(int job);
      void newpriority(int job, double change);
      double calculateTotalLateness() const;
    public:
      static int localPoolSize;
      static double mutationRange;
      const Problem* problem;
      Schedule(const Problem* problem);

      double getTotalLateness();
      double getTotalLateness() const;
      void mutate();
      double getPriority(int job) const;
      Schedule operator&& (const Schedule& other) const;
      bool operator< (Schedule& other);
  };
#endif
