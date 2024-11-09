//#include <stdio.h>
#include <stdlib.h>
#include "chess.h"
#include "gc.h"

char** allocateMemory(int rows, size_t cols){
  char** newFig;
  memoryAlloc((void**)&newFig, sizeof(char*)*(rows + 1));
  for(int i = 0; i < rows; i++)
    memoryAlloc((void**)&newFig[i], sizeof(char)*(cols + 1));
  return newFig;
}

void unlinkMemory(char** fig){
  countMemoryEntries();
  for(int i = 0; fig[i]; i++)
    unregisterPointer((void**)&fig[i]);
  countMemoryEntries();
  unregisterPointer((void**)&fig);
  countMemoryEntries();
}
/*
char** reverse(char** fig){
  int rows = 0;
  while(fig[++rows]);
  
  int cols = 0;
  while(fig[0][++cols]);

  char** newFig = allocateMemory(rows, cols);

  for(int i = 0; fig[i]; i++){
    for(int j = 0; fig[0][j]; j++)
      newFig[i][j] = fig[i][j];
    newFig[i][cols] = 0;
  }
  newFig[rows] = 0;
  unlinkMemory(newFig);
  return newFig;
}
*/

char** reverse(char** figures){
  int fila = 0;

  // Contar el número de filas
  while (figures[fila] != nullptr) {
    fila++;
  }

  // Aquí usamos allocateMemory para asignar memoria
  // Filas: 'fila' y columnas: asumimos que cada fila tiene un tamaño 'fila' también
  char** reverso = allocateMemory(fila, fila);

  // Cambiar el contenido de los caracteres
  for (int i = 0; i < fila; i++) {
    for (int j = 0; j < fila; j++) {
      if (figures[i][j] == '.' || figures[i][j] == '_') {
        reverso[i][j] = '@';
      }
      else if (figures[i][j] == '@') {
        reverso[i][j] = '.';
      }
      else {
        reverso[i][j] = figures[i][j];
      }
    }
    reverso[i][fila] = '\0'; // Terminar las cadenas en cada fila
  }

  // Aseguramos que la última fila también esté terminada correctamente
  reverso[fila] = NULL;
  unlinkMemory(reverso);
  return reverso;
}

