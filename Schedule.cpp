#include "Schedule.hpp"

#include <random>
#include <cmath>
#include <algorithm> 
#include <map>


int Schedule::localPoolSize=5;
double Schedule::mutationRange=0.5;

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

Schedule::Schedule(const Schedule& other) : problem(other.problem){
  priorities = new double[problem.getJobCount()];
  for (int j=0; j<problem.getJobCount(); j++) 
    priorities[j]=other.priorities[j];
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

void Schedule::localsearch(int job) {
  double old=priorities[job];
  double best=old;
  double bestvalue=getTotalLateness();
  std::random_device r;
  std::default_random_engine e(r());
  std::uniform_real_distribution<double> uniform_dist(-mutationRange,mutationRange);
  for (int l=0; l<localPoolSize; l++) {
    newpriority(job,uniform_dist(e));
    if(getTotalLateness()<bestvalue){
      best=priorities[job];
      bestvalue=getTotalLateness();
    }
    priorities[job]=old;
  }
  priorities[job]=best;  
}

void Schedule::newpriority(int job, double change){
  priorities[job]+=change;
  if (priorities[job]<0) priorities[job]+=problem.getUnitCount();
  else if (priorities[job]>=problem.getUnitCount()) priorities[job]-=problem.getUnitCount();
  if (!problem.getProcTime(job,(int) priorities[job])){
    if (change<0) do {
      priorities[job]-=1;
      if (priorities[job]<0) priorities[job]+=problem.getUnitCount();
    } while (!problem.getProcTime(job,(int) priorities[job])); 
    else do {
      priorities[job]+=1;
      if (priorities[job]>=problem.getUnitCount()) priorities[job]-=problem.getUnitCount();
    } while (!problem.getProcTime(job,(int) priorities[job]));
  }
} 

void Schedule::mutate() {
  for (int j=0; j<problem.getJobCount(); j++)
    localsearch(j);  
}

double Schedule::getPriority(int job) const {return priorities[job%problem.getJobCount()];}


Schedule Schedule::operator&& (const Schedule other) const {
  Schedule toReturn(problem);
  std::random_device r;
  std::default_random_engine e(r());
  std::uniform_int_distribution<int> uniform_dist(0,1);
  for(int j=0; j<problem.getJobCount(); j++)
    if(uniform_dist(e)) toReturn.priorities[j]=priorities[j];
    else toReturn.priorities[j]=other.priorities[j];
  return toReturn;
}
