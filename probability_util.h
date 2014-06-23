#pragma once

#include <vector>
#include <set>

typedef std::vector<double> EventsProbabilities;
typedef std::set<unsigned> NumbersSet;
typedef std::set<NumbersSet> CombinationsSet;

unsigned GetAtLeastCount();
EventsProbabilities GetEventsProbabilities();

double EventsOnlyProbability(const EventsProbabilities& probabilities,
  const NumbersSet& active_nums);

CombinationsSet MakeCombinations(const NumbersSet& numbers, int count);

NumbersSet MakeEventsIndexesSet(const EventsProbabilities& probabilities);

double AtLeastEventsProbability(const EventsProbabilities& probabilities,
                                unsigned count);
