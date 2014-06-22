#include "probability_util.h"

#include <iostream>

const char* kManySpaces = "                                              ";
#define PrintAtLineStart(val) std::cout << "\r" << val << kManySpaces;

unsigned GetAtLeastCount()
{
  return 3;
}

EventsProbabilities GetEventsProbabilities()
{
  double p[] = {0.5, 0.5, 0.5, 0.5,
                0.16667, 0.16667, 0.16667, 0.16667,
                0.33333, 0.33333, 0.33333, 0.33333};

  // double p[] = {0.5, 0.5, 0.5, 0.5, 0.16667, 0.33333, 0.33333, 0.23};

  return EventsProbabilities(p, p + sizeof(p)/sizeof(*p));
}

double EventsOnlyProbability(const EventsProbabilities& probabilities,
                             const EventsNumbers& active_nums)
{
  double product = 1;
  for (unsigned i = 0; i < probabilities.size(); ++i)
    if (active_nums.count(i))
      product *= probabilities[i];
    else
      product *= (1 - probabilities[i]);
  return product;
}

IntCombinationSet MakeCombinations(const EventsNumbers& numbers, int count)
{
  IntCombinationSet result;
  for (auto number = numbers.begin(); number != numbers.end(); ++number)
  {
    if (!count) throw std::exception();

    unsigned next_count = count - 1;
    bool no_more_combinations = !next_count || (numbers.size() <= 1);

    if (no_more_combinations)
    {
      IntCombination single_combination;
      single_combination.insert(*number);
      result.insert(single_combination);
    }
    else
    {
      EventsNumbers truncated_numbers = numbers;
      truncated_numbers.erase(*number);
      IntCombinationSet additions = MakeCombinations(truncated_numbers, next_count);

      for (auto addition = additions.begin(); addition != additions.end(); ++addition)
      {
        IntCombination combination = *addition;
        combination.insert(*number);
        result.insert(combination);
      }
    }
  }
  return result;
}

EventsNumbers MakeEventsIndexesSet(const EventsProbabilities& probabilities)
{
  EventsNumbers result;
  for (unsigned i = 0; i < probabilities.size(); ++i)
    result.insert(i);
  return result;
}

double AtLeastEventsProbability(const EventsProbabilities& probabilities,
                                unsigned count)
{
  EventsNumbers all_event_numbers = MakeEventsIndexesSet(probabilities);

  std::cout << "Events: " << probabilities.size() << std::endl
            << "Make combinations with events count:" << std::endl;
  IntCombinationSet combinations_set;
  for (unsigned i = count; i <= probabilities.size(); ++i)
    {
    PrintAtLineStart(i << ", total: " << combinations_set.size());

    IntCombinationSet particulat_combinations = MakeCombinations(all_event_numbers, i);
    combinations_set.insert(particulat_combinations.begin(), particulat_combinations.end());
    }

  std::cout << std::endl << "Combinations total: " << combinations_set.size() << std::endl
                         << "Calculate probability for summand:" << std::endl;

  double sum = 0;
  int combination_num = 1;
  auto combination = combinations_set.begin();

  for (;combination != combinations_set.end(); ++combination, ++combination_num)
  {
    PrintAtLineStart(combination_num);
    sum += EventsOnlyProbability(probabilities, *combination);
  }
  std::cout << std::endl;

  return sum;
}

