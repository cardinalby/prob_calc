#include <QCoreApplication>
#include <iostream>
#include "probability_util.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  EventsProbabilities probs = GetEventsProbabilities();

  std::cout << AtLeastEventsProbability(probs,  GetAtLeastCount()) << std::endl;

  char c;
  std::cin >> c;

  return a.exec();
}
