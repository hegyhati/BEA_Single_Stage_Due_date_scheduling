#include "BEA.hpp"

#include <algorithm>
#include <random>


int BEA::populationSize=100;
int BEA::bestKeepCount=40;
int BEA::crossoverCount=15;
int BEA::newCount=20;

BEA::BEA(const Problem* problem, int size) : problem(problem){
  populationSize=size;
  std::vector<Schedule> tmp;
  for(int p=0; p<size; p++) tmp.push_back(Schedule(problem));
  for(auto it: tmp) {
    it.mutate();
  }
  population.insert(population.end(), tmp.begin(), tmp.end());
}

std::vector<double> BEA::getCurrentValues() const {
  std::vector<double> toReturn;
  for(auto it: population) toReturn.push_back(it.getObjectiveValue());
  return toReturn;
}

double BEA::getCurrentBestValue() {
  double best = population[0].getObjectiveValue();
  for(int i=1; i<population.size(); i++) {
      double lateness = population[i].getObjectiveValue();
      if(lateness<best)
        best=lateness;
    }
  return best;
}

Schedule BEA::getCurrentBestSolution() {
  int best=0;
  double bestval=population[0].getObjectiveValue();
  for(int i=1; i<population.size(); i++) {
      double lateness = population[i].getObjectiveValue();
      if(lateness<bestval) {
        best=i;
        bestval=lateness;
      }
    }
  return population[best];
}

double BEA::evolve(){
  double oldbest=getCurrentBestValue();
  std::vector<Schedule> next_population;
  
  // Mutate old ones
  for(auto it: population) {
    it.mutate();
  }
  next_population.insert(next_population.end(), population.begin(), population.end());
  
  // Insert new random ones mutated
  std::vector<Schedule> tmp_new;
  for(int p=0; p<newCount; p++) tmp_new.push_back(Schedule(problem));
  for(auto it: tmp_new) {
    it.mutate();
  }
  next_population.insert(next_population.end(), tmp_new.begin(), tmp_new.end());
  
  // Do some crossovers
  std::vector<Schedule> tmp_crossover;
  int parent1,parent2;
  std::random_device r;
  std::default_random_engine e(r());
  std::uniform_int_distribution<int> uniform_dist(0,next_population.size()-1);

  for(int p=0; p<crossoverCount; p++) {
    parent1=uniform_dist(e);
    parent2=uniform_dist(e);
    tmp_crossover.push_back(next_population[parent1]&&(next_population[parent2]));
    tmp_crossover.back().mutate();
  }
  next_population.insert(next_population.end(), tmp_crossover.begin(), tmp_crossover.end());

  //Elitism
  std::sort(next_population.begin(), next_population.end());
  population.clear();  
  int toSelect=populationSize;
  int remaining=next_population.size(); 
  double multiplier = (double) (populationSize-bestKeepCount) / (populationSize+newCount+crossoverCount-bestKeepCount);
  std::uniform_int_distribution<int> uniform_dist_2(0,remaining);
  for(auto it=next_population.begin();toSelect;it++,remaining--){
    if (toSelect>=populationSize-bestKeepCount || toSelect==remaining 
      || uniform_dist_2(e) < toSelect * multiplier) {     
      population.push_back(*it);
      toSelect--;      
    }
  }
  return getCurrentBestValue()-oldbest;
}
