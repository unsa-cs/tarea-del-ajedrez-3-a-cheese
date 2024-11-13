#include "chess.h"
#include "figures.h"
#include "gc.h"

void display(){
  char** juntar = join(whiteSquare,bishop);
  interpreter(juntar);
  garbageCollector();
}
