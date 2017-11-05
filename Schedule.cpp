#include "Schedule.hpp"

#include <random>
#include <cmath>
#include <algorithm> 
#include <map>

Schedule::Schedule(const Problem& problem):problem(problem){
  priorities = new double[problem.getJobCount()];
  
  std::random_device r;
  std::default_random_engine e(r());
  std::uniform_real_distribution<double> uniform_dist(0,problem.getUnitCount());
  
  for (int j=0; j<problem.getJobCount(); j++) {
    do {
      priorities[j]=uniform_dist(e);
    } while (! problem.getProcTime(j, (int) priorities[j]));
  }
}

Schedule::~Schedule(){ delete [] priorities; }

double Schedule::getTotalLateness() const {
  double lateness=0;
  double finish;
  std::map <int,std::map<double,int>> prodlist;
  for(int j=0;j<problem.getJobCount(); j++)
    prodlist[(int) priorities[j]][priorities[j]] = j;
  for(const auto& itu : prodlist){
    finish=0;
    for (const auto& itj : prodlist[itu.first]){
      finish+=problem.getProcTime(itj.second,itu.first);
      lateness+=std::max(0.0,finish-problem.getDeadline(itj.second));
    }
  }
  return lateness;
}

void Schedule::localsearch(int job) {return;}

void Schedule::mutate() {
  for (int j=0; j<problem.getJobCount(); j++)
    localsearch(j);
}

double Schedule::getPriority(int job) const {return priorities[job%problem.getJobCount()];}
