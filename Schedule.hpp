#ifndef SCHEDULE_HPP
  #define SCHEDULE_HPP
  
  #include "Problem.hpp"
  
  class Schedule {
    private:
      double* priorities;
      void localsearch(int job);
      void newpriority(int job, double change);
    public:
      static int localPoolSize;
      static double mutationRange;
      const Problem& problem;
      Schedule(const Problem& problem);
      Schedule(const Schedule& other);
      ~Schedule();
      double getTotalLateness() const;
      void mutate();
      double getPriority(int job) const;
      Schedule operator&& (const Schedule other) const;
  };
#endif
