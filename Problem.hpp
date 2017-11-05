#ifndef PROBLEM_HPP
  #define PROBLEM_HPP

  #include <string> 
  
  class Problem {
    private:
      int nJobs;
      int nUnits;
      double ** procTime;
      double * deadline;
    public:
      Problem(std::string filename);
      ~Problem();
      int getJobCount() const;
      int getUnitCount() const;
      double getProcTime(int job, int unit) const;
      double getDeadline(int job) const;      
  };

#endif
