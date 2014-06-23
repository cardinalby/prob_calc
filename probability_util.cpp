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
  double p[] = { 0.5, 0.5, 0.5, 0.5,
                 0.16667, 0.16667, 0.16667, 0.16667,
                 0.33333, 0.33333, 0.33333, 0.33333 };

  return EventsProbabilities(p, p + sizeof(p)/sizeof(*p));
}

double EventsOnlyProbability(const EventsProbabilities& probabilities,
                             const NumbersSet& active_nums)
{
  double product = 1;
  for (unsigned i = 0; i < probabilities.size(); ++i)
    if (active_nums.count(i))
      product *= probabilities[i];
    else
      product *= (1 - probabilities[i]);
  return product;
}

long long Fact(int arg)
{
  if (arg <= 1)
    return 1;
  return arg * Fact(arg - 1);
}

long long CombinationsCount(int k, int n)
{
  if (k > n) throw std::exception();

  return Fact(n) / (Fact(k) * Fact(n - k));
}

CombinationsSet MakeCombinations(const NumbersSet& numbers, int count)
{
  CombinationsSet result;
  
  if (!count) throw std::exception();

  if (count == numbers.size())
  {
    result.insert(NumbersSet(numbers.begin(), numbers.end()));
    return result;
  }

  // combinations with 1 element
  if (!(count - 1) || (numbers.size() <= 1))
  {
    for (auto number = numbers.begin(); number != numbers.end(); ++number)
    {
      NumbersSet single_combination;
      single_combination.insert(*number);
      result.insert(single_combination);
    }
    return result;
  }
    
  // Combinations with (count - 1) without current number
  unsigned first_num = *numbers.begin();
  NumbersSet truncated_numbers = numbers;
  truncated_numbers.erase(first_num);
  CombinationsSet subcombinations = MakeCombinations(truncated_numbers, count - 1);

  for (auto subcombination = subcombinations.begin(); subcombination != subcombinations.end(); ++subcombination)
  {
    NumbersSet cmb = *subcombination;
    // Add current number
    cmb.insert(first_num);
    result.insert(cmb);
  }

  // Combinations with (count) without current number
  subcombinations = MakeCombinations(truncated_numbers, count);
  result.insert(subcombinations.begin(), subcombinations.end());

  return result;
}

NumbersSet MakeEventsIndexesSet(const EventsProbabilities& probabilities)
{
  NumbersSet result;
  for (unsigned i = 0; i < probabilities.size(); ++i)
    result.insert(i);
  return result;
}

double AtLeastEventsProbability(const EventsProbabilities& probabilities,
                                unsigned count)
{
  NumbersSet all_event_numbers = MakeEventsIndexesSet(probabilities);

  std::cout << "Events: " << probabilities.size() << std::endl
            << "Make combinations with events count:" << std::endl;
  CombinationsSet combinations_set;
  for (unsigned i = count; i <= probabilities.size(); ++i)
    {
    CombinationsSet particulat_combinations = MakeCombinations(all_event_numbers, i);
    auto combinations_by_formula = CombinationsCount(i, all_event_numbers.size());

    if (particulat_combinations.size() != combinations_by_formula)
      throw std::exception();

    combinations_set.insert(particulat_combinations.begin(), particulat_combinations.end());

    PrintAtLineStart(i << ", total: " << combinations_set.size());
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

