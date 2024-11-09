#include "chess.h"
#include "figures.h"
#include "gc.h"

void display(){
  char** blackSquare = whiteSquare;
  interpreter(blackSquare);
  garbageCollector();
}
