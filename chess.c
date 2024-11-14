#include <stdio.h>
#include <stdlib.h>
#include "chess.h"
#include "gc.h"

char*** local;

char** allocateMemory(int rows, size_t cols){
  char** newFig;
  memoryAlloc((void**)&newFig, sizeof(char*)*(rows + 1));
  //newFig = (char**)malloc(sizeof(char*)*(rows + 1));
  for(int i = 0; i < rows; i++)
    memoryAlloc((void**)&newFig[i], sizeof(char)*(cols + 1));
  //fprintf(stderr, "valor de newFig: %p", &newFig);
  local = &newFig;
  return newFig;
}

void unlinkMemory(char** fig){
  //fprintf(stderr, "valor que recibe desde reverso %p\n", fig);
  countMemoryEntries();
  for(int i = 0; fig[i]; i++){
    //fprintf(stderr, "valor de cada &fig[i] %p\n", &fig[i]);
    unregisterPointer((void**)&fig[i]);
  }
  countMemoryEntries();
  unregisterPointer((void**)local);
  //unregisterPointer((void**)(&(fig)+1));
  countMemoryEntries();
}

char** reverse(char** figures){
  int fila = 0;

  // Contar el número de filas
  while (figures[fila] != nullptr) {
    fila++;
  }

  // Aquí usamos allocateMemory para asignar memoria
  // Filas: 'fila' y columnas: asumimos que cada fila tiene un tamaño 'fila' también
  char** reverso = allocateMemory(fila, fila);
  //fprintf(stderr, "valor inicial de reverse %p\n", reverso);

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
  //fprintf(stderr, "valor a desvincular que se envia desde reverse %p\n", reverso);
  unlinkMemory(reverso);
  return reverso;
}

char** join(char** figura1, char** figura2){
  int fila=0;
  int columna=0;

  while(figura1[fila] != nullptr)
    fila++;
  while(figura1[0][columna] != 0)
    columna++;

  //char** juntar=(char**)malloc((fila+1)*sizeof(char*));
  char** juntar = allocateMemory(fila,columna*2);

  for(int j=0;j<fila;j++){
    for(int k=0;k<2*columna;k++){
      if(k<columna)
        juntar[j][k]=figura1[j][k];
      else
        juntar[j][k]=figura2[j][k-columna];
    }

    juntar[j][2*columna]='\0';
  }
  juntar[fila]= 0;
  unlinkMemory(juntar);
  return juntar;
}

char** repeatH(char** figure, int veces){
  int fila=0;
  int columna=0;
  while(figure[fila] != nullptr){
    fila++;
  }
  while (figure[0][columna] != 0){
    columna++;
  }
  char** repetirH = allocateMemory(fila, columna*veces);
  for(int i=0; i<fila; i++){
    for(int k=0; k<veces; k++){
      for(int j=0; j<columna; j++){
        repetirH[i][j+columna*k]=figure[i][j];
      }
    }
    repetirH[i][columna*veces]='\0';
  }
  repetirH[fila]=0;
  unlinkMemory(repetirH);
  return repetirH;
}

char** repeatV(char** figure, int veces) {
  int fila = 0;
  int columna = 0;

  while (figure[fila] != nullptr) 
    fila++;
  
  while (figure[0][columna] != '\0') 
    columna++;
  
  char** repetirV = allocateMemory(fila*veces, columna);
  
  for (int i = 0; i < fila; i++) {
    for (int k = 0; k < veces; k++) {
      for (int j = 0; j < columna; j++) {
        repetirV[i + k * fila][j] = figure[i][j];
      }
      repetirV[i + k * fila][columna] = '\0'; 
    }
  }
    
  repetirV[fila * veces] = nullptr;
  unlinkMemory(repetirV);
  return repetirV;
}
