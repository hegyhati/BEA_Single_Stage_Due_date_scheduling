#ifndef TEST_SCHEDULE_HPP
  #define TEST_SCHEDULE_HPP

  #include "../Schedule.hpp"

  #include <algorithm>
  #include <iostream>
  #include <vector>
  using namespace std;

  void printSchedule(Schedule schedule){
    vector<vector<unsigned int>> prodlist(schedule.problem->getUnitCount());
    for(unsigned int j=0;j<schedule.problem->getJobCount(); j++)
      prodlist[(unsigned int) schedule.getPriority(j)].push_back(j);
    for(unsigned int unit=0; unit<schedule.problem->getUnitCount(); unit++){
      if (prodlist[unit].empty())
        continue;
      sort(prodlist[unit].begin(), prodlist[unit].end(), [&](int a, int b) {
          return schedule.getPriority(a)<schedule.getPriority(b);
      });
      cout<<"U"<<unit+1<<":";
      for (const auto& itj : prodlist[unit])
        cout<<" i"<<itj+1<<"("<<schedule.getPriority(itj)<<")";
      cout<<"\n";
    }
    cout<<"Objective value: "<<schedule.getObjectiveValue()<<"\n";
  }

  void printMinEarlinessFinishTimes(Schedule schedule){
    std::vector<std::vector<unsigned int>> prodlist(schedule.problem->getUnitCount());
    for(unsigned int j=0;j<schedule.problem->getJobCount(); j++)
      prodlist[(unsigned int) schedule.getPriority(j)].push_back(j);
    for(unsigned int unit=0; unit<schedule.problem->getUnitCount(); unit++){
      if (prodlist[unit].empty())
        continue;
      std::sort(prodlist[unit].begin(), prodlist[unit].end(), [&](unsigned int a, unsigned int b) {
          return schedule.getPriority(a)<schedule.getPriority(b);
      });
      cout<<"U"<<unit+1<<":";
      double finish = schedule.problem->getDeadline(prodlist[unit].back());
      for (int j=prodlist[unit].size()-1; j>=0; --j){
        double earliness=schedule.problem->getDeadline(prodlist[unit][j])-finish;
        if (earliness < 0) {
          finish+=earliness;
          earliness=0;
        }
        double realFinish = finish;
        finish-=schedule.problem->getProcTime(prodlist[unit][j],unit); //start time == latest finish time of next (previous in time)
        printf(" i%d: %g-%g (%g);", prodlist[unit][j]+1, finish, realFinish, earliness);
        if (j>0) {
          finish-=schedule.problem->getSetupTime(prodlist[unit][j-1],prodlist[unit][j]);
        }
      }
      cout<<endl;
    }
  }

#endif
