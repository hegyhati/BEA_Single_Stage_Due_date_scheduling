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
      unsigned int nJobs;
      unsigned int nUnits;
      double ** procTime;
      double ** setupTime;
      double * deadline;
      ObjectiveFunction objFunct;
    public:
      Problem(std::string filename, ObjectiveFunction obj);
      ~Problem();
      unsigned int getJobCount() const;
      unsigned int getUnitCount() const;
      double getProcTime(int job, int unit) const;
      double getSetupTime(int job1, int job2) const;
      double getDeadline(int job) const;
      ObjectiveFunction getObjective() const;
  };

#endif
