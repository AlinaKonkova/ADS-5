// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int Prioritet(char prior) {
  switch (prior) {
  case '(': return 0;
  case ')': return 1;
  case '-': return 2;
  case '+': return 2;
  case '*': return 3;
  case '/': return 3;
  case ' ': return 5;
  default: return 4;
  }
}

int Calculator(char prior, int x, int y) {
    switch (prior) {
    case '-': return x - y;
    case '+': return x + y;
    case '*': return x * y;
    case '/': return x / y;
    default: return 0;
    }
}

std::string infx2pstfx(std::string inf) {
  std::string result;
  char probel = ' ';
  TStack <char, 100> stack1;
  for (int i = 0; i < inf.size(); i++) {
    if (Prioritet(inf[i]) == 4) {
      result.push_back(inf[i]);
      result.push_back(probel);
    } else {
      if (Prioritet(inf[i]) == 0) {
        stack1.push(inf[i]);
      } else if (stack1.isEmpty()) {
          stack1.push(inf[i]);
      } else if ((Prioritet(inf[i]) > Prioritet(stack1.get()))) {
          stack1.push(inf[i]);
      } else if (Prioritet(inf[i]) == 1) {
        while (Prioritet(stack1.get()) != 0) {
          result.push_back(stack1.get());
          result.push_back(probel);
          stack1.pop();
        }
        stack1.pop();
      } else {
        char pr = Prioritet(inf[i]);
        char pr2 = Prioritet(stack1.get());
        while ((pr <= pr2) && (!stack1.isEmpty())) {
          result.push_back(stack1.get());
          result.push_back(probel);
          stack1.pop();
        }
        stack1.push(inf[i]);
      }
    }
  }
  while (!stack1.isEmpty()) {
    result.push_back(stack1.get());
    result.push_back(probel);
    stack1.pop();
  }
  for (int i = 0; i < result.size(); i++) {
    if (result[result.size() - 1] == ' ')
      result.erase(result.size() - 1);
  }
  return result;
}


int eval(std::string pref) {
  TStack <int, 100> stack2;
  int result = 0;
  int x = 0;
  int y = 0;
  for (int i = 0; i < pref.size(); i++) {
    if (Prioritet(pref[i]) == 4) {
      stack2.push(pref[i] - '0');
    } else if (Prioritet(pref[i]) < 4) {
      x = stack2.get();
      stack2.pop();
      y = stack2.get();
      stack2.pop();
      stack2.push(Calculator(pref[i], x, y));
    }
  }
  result = stack2.get();
  return result;
}
