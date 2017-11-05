#ifndef SCHEDULE_HPP
  #define SCHEDULE_HPP
  
  #include "Problem.hpp"
  
  class Schedule {
    private:
      double* priorities;
      void localsearch(int job);
    public:
      const Problem& problem;
      Schedule(const Problem& problem);
      ~Schedule();
      double getTotalLateness() const;
      void mutate();
      double getPriority(int job) const;
  };
#endif
