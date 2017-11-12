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

#endif
