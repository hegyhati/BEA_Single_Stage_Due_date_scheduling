#ifndef PROBLEM_HPP
  #define PROBLEM_HPP

  #include <string> 
  
  class Problem {
    public:
      enum ObjectiveFunction {
        TotalLateness,
        TotalEarliness
      };
    private:
      int nJobs;
      int nUnits;
      double ** procTime;
      double ** setupTime;
      double * deadline;
      ObjectiveFunction objFunct;
    public:
      Problem(std::string filename, ObjectiveFunction obj);
      ~Problem();
      int getJobCount() const;
      int getUnitCount() const;
      double getProcTime(int job, int unit) const;
      double getSetupTime(int job1, int job2) const;
      double getDeadline(int job) const;
      ObjectiveFunction getObjective() const;
  };

#endif
