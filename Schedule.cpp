#include "Schedule.hpp"

#include <random>
#include <cmath>
#include <algorithm>


int Schedule::localPoolSize=5;
double Schedule::mutationRange=0.5;

Schedule::Schedule(const Problem* problem) : problem(problem),
  priorities(problem->getJobCount()), objective(-1.) {
  std::random_device r;
  std::default_random_engine e(r());
  std::uniform_real_distribution<double> uniform_dist(0,problem->getUnitCount());
  
  for (int j=0; j<problem->getJobCount(); j++) {
    do {
      priorities[j]=uniform_dist(e);
    } while (! problem->getProcTime(j, (int) priorities[j]));
  }
}

double Schedule::getObjectiveValue() {
  if (objective == -1.) objective = calculateObjectiveValue();
  return objective;
}

void Schedule::localsearch(int job) {
  double old=priorities[job];
  double best=old;
  double bestvalue=getObjectiveValue();
  std::random_device r;
  std::default_random_engine e(r());
  std::uniform_real_distribution<double> uniform_dist(-mutationRange,mutationRange);
  for (int l=0; l<localPoolSize; l++) {
    newpriority(job,uniform_dist(e));
    double newvalue=getObjectiveValue();
    if(newvalue<bestvalue){
      best=priorities[job];
      bestvalue=newvalue;
    }
    priorities[job]=old;
    objective = -1.;
  }
  priorities[job]=best;
  objective = bestvalue;
}

void Schedule::newpriority(int job, double change) {
  objective = -1.;
  priorities[job]+=change;
  if (priorities[job]<0) priorities[job]+=problem->getUnitCount();
  else if (priorities[job]>=problem->getUnitCount()) priorities[job]-=problem->getUnitCount();
  if (!problem->getProcTime(job,(int) priorities[job])){
    if (change<0) do {
      priorities[job]-=1;
      if (priorities[job]<0) priorities[job]+=problem->getUnitCount();
    } while (!problem->getProcTime(job,(int) priorities[job]));
    else do {
      priorities[job]+=1;
      if (priorities[job]>=problem->getUnitCount()) priorities[job]-=problem->getUnitCount();
    } while (!problem->getProcTime(job,(int) priorities[job]));
    }
}

double Schedule::calculateObjectiveValue() const
{
  switch (problem->getObjective()) {
    case Problem::TotalLateness:
      return calculateTotalLateness();
    case Problem::TotalEarliness:
      return calculateTotalEarliness();
    default:
      return -1;
    }
}

double Schedule::calculateTotalLateness() const {
  double lateness=0;
  std::vector<std::vector<int>> prodlist(problem->getUnitCount());
  for(int j=0;j<problem->getJobCount(); j++)
    prodlist[(int) priorities[j]].push_back(j);
  for(int unit=0; unit<problem->getUnitCount(); unit++){
    std::sort(prodlist[unit].begin(), prodlist[unit].end(), [&](int a, int b) {
        return priorities[a]<priorities[b];
    });
    double finish=0;
    for (int j=0; j<prodlist[unit].size(); ++j){
      if (j>0){
        finish+=problem->getSetupTime(prodlist[unit][j-1],prodlist[unit][j]);
      }
      finish+=problem->getProcTime(prodlist[unit][j],unit);
      lateness+=std::max(0.0,finish-problem->getDeadline(prodlist[unit][j]));
    }
  }
  return lateness;
}

double Schedule::calculateTotalEarliness() const
{
  double earliness=0;
  std::vector<std::vector<int>> prodlist(problem->getUnitCount());
  for(int j=0;j<problem->getJobCount(); j++)
    prodlist[(int) priorities[j]].push_back(j);
  for(int unit=0; unit<problem->getUnitCount(); unit++){
    if (prodlist[unit].empty())
      continue;
    std::sort(prodlist[unit].begin(), prodlist[unit].end(), [&](int a, int b) {
        return priorities[a]<priorities[b];
    });
    double finish = problem->getDeadline(prodlist[unit].back());
    for (int j=prodlist[unit].size()-1; j>=0; --j){
      double jobEarliness=problem->getDeadline(prodlist[unit][j])-finish;
      if (jobEarliness < 0) {
        finish+=jobEarliness;
      } else {
        earliness+=jobEarliness;
      }
      //calculate latest possible finish time for job j-1
      finish-=problem->getProcTime(prodlist[unit][j],unit);
      if (j>0) {
        finish-=problem->getSetupTime(prodlist[unit][j-1],prodlist[unit][j]);
      }
      if (finish<0) {
        //schedule infeasible add infeasibility to obj value as a penalty
        earliness += -finish;
      }
    }
  }
  return earliness;
}

void Schedule::mutate() {
  for (int j=0; j<problem->getJobCount(); j++)
    localsearch(j);  
}

double Schedule::getPriority(int job) const {return priorities[job%problem->getJobCount()];}


Schedule Schedule::operator&& (const Schedule &other) const {
  Schedule toReturn(problem);
  std::random_device r;
  std::default_random_engine e(r());
  std::uniform_int_distribution<int> uniform_dist(0,1);
  for(int j=0; j<problem->getJobCount(); j++)
    if(uniform_dist(e)) toReturn.priorities[j]=priorities[j];
    else toReturn.priorities[j]=other.priorities[j];
  return toReturn;
}

bool Schedule::operator< (Schedule &other)
{
  return getObjectiveValue() < other.getObjectiveValue();
}
