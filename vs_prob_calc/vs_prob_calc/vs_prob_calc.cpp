#include "stdafx.h"
#include <iostream>
#include "../../probability_util.h"

int _tmain(int argc, _TCHAR* argv[])
{	
  EventsProbabilities probs = GetEventsProbabilities();

  std::cout << AtLeastEventsProbability(probs, GetAtLeastCount()) << std::endl;

  char c;
  std::cin >> c;

  
  return 0;
}

