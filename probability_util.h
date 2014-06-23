#pragma once

#include <vector>
#include <set>

typedef std::vector<double> EventsProbabilities;
typedef std::set<unsigned> EventsNumbers;
typedef std::set<unsigned> IntCombination;
typedef std::set<IntCombination> IntCombinationSet;

unsigned GetAtLeastCount();
EventsProbabilities GetEventsProbabilities();

double EventsOnlyProbability(const EventsProbabilities& probabilities,
                             const EventsNumbers& active_nums);

IntCombinationSet MakeCombinations(const EventsNumbers& numbers, int count);

EventsNumbers MakeEventsIndexesSet(const EventsProbabilities& probabilities);

double AtLeastEventsProbability(const EventsProbabilities& probabilities,
                                unsigned count);
