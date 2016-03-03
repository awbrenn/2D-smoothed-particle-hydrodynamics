//
// Created by awbrenn on 3/3/16.
//

#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>

void handleError(const char *error_message, bool kill) {
  std::cerr << error_message << std::endl;
  if (kill) exit(-1);
}

#endif //UTILITY_H
