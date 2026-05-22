// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() : countOp(0), first(nullptr) {}
Train::~Train() {
  if (first == nullptr) {
    return;
  }
  Car* current = first->next;
  while (current != first) {
    Car* next_car = current->next;
    delete current;
    current = next_car;
  }
  delete first;
}
void Train::addCar(bool light) {
  Car* new_car = new Car{light, nullptr, nullptr};
  if (first == nullptr) {
    first = new_car;
    first->next = first;
    first->prev = first;
    return;
  }
  Car* last = first->prev;
  last->next = new_car;
  new_car->prev = last;
  new_car->next = first;
  first->prev = new_car;
}
int Train::getLength() {
  if (first == nullptr) {
    return 0;
  }
  countOp = 0;
  Car* start = first;
  start->light = true;
  int steps = 0;
  Car* current = start;
  while (true) {
    current = current->next;
    steps++;
    countOp++;
    if (current->light) {
      current->light = false;
      Car* back = current;
      for (int i = 0; i < steps; ++i) {
        back = back->prev;
        countOp++;
      }
      if (!back->light) {
        return steps;
      }
      current = back;
      steps = 0;
    }
  }
}
int Train::getOpCount() const {
  return countOp;
}
