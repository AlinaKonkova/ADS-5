// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prioritet(char znak) {
  switch (znak) {
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

int calculator(char znak, int x, int y) {
  switch (znak) {
  case '+': return (x + y);
  case '-': return (y - x);
  case '*': return (x * y);
  case '/':
    if (x != 0)
      return y / x;
  default: return 0;
  }
}

std::string infx2pstfx(std::string inf) {
  std::string result;
  char probel = ' ';
  TStack <char, 100> stack1;
  for (int i = 0; i < inf.size(); i++) {
    if (prioritet(inf[i]) == 4) {
      result.push_back(inf[i]);
      result.push_back(probel);
    } else {
      if (prioritet(inf[i]) == 0) {
        stack1.push(inf[i]);
      } else if (stack1.isEmpty()) {
          stack1.push(inf[i]);
      } else if ((prioritet(inf[i]) > prioritet(stack1.get()))) {
          stack1.push(inf[i]);
      } else if (prioritet(inf[i]) == 1) {
        while (prioritet(stack1.get()) != 0) {
          result.push_back(stack1.get());
          result.push_back(probel);
          stack1.pop();
        }
        stack1.pop();
      } else {
        char pr = prioritet(inf[i]);
        char pr2 = prioritet(stack1.get());
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
    if (prioritet(pref[i]) == 4) {
      stack2.push(pref[i] - '0');
    } else if (prioritet(pref[i]) < 4) {
      x = stack2.get();
      stack2.pop();
      y = stack2.get();
      stack2.pop();
      stack2.push(calculator(pref[i], x, y));
    }
  }
  result = stack2.get();
  return result;
  return 0;
}
