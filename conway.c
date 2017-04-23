#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 21
#define ROWS 10
#define COLUMNS 10

char getCharAtPosition(int row, int column, char currentGeneration[ROWS][COLUMNS]) {
  if ((row < 0) || (row >= ROWS) || (column < 0) || (column >= COLUMNS)) {
    return '0';
  }

  if (currentGeneration[row][column] == '0') {
    return '0';
  } else {
    return '1';
  }
}

char computeNewCellStatus(int row, int column, char currentGeneration[ROWS][COLUMNS]) {
  int livingNeighbors = 0;
  int i;
  int n;

  for (i = row - 1; i <= row + 1; i++) {
    for (n = column - 1; n <= column + 1; n++) {
      if (!(row == i && column == n)) {
        if (getCharAtPosition(i, n, currentGeneration) == '1') {
          livingNeighbors++;
        }
      }
    }
  }

  // printf("row: %d, column: %d, neighbor count: %d\n", row, column, livingNeighbors);

  if (currentGeneration[row][column] == '0') {
    if (livingNeighbors == 3) {
      return '1';
    } else {
      return '0';
    }
  } else {
    if (livingNeighbors < 2 || livingNeighbors > 3) {
      return '0';
    } else {
      return '1';
    }
  }
}

int main(int argc, char *argv[]) {
  FILE *fp = fopen(argv[2], "r");
  char buffer[BUFFER_SIZE];
  char rows[ROWS];
  char columns[COLUMNS];
  int generationLimit;
  int i;
  int n;
  int row;
  int column;
  char newGenerationPlaceholder[ROWS][COLUMNS];
  char currentGeneration[ROWS][COLUMNS];
  int generationCounter = 0;
  int rowCounter = 0;

  if (argc < 3) {
    printf("Intended usage:\n");
    printf("    ./conway 5 inputfile.txt\n");
    printf("             ^generations to run         \n");
    exit(1);
  }

  // BEGIN IMPORTING DATA FROM FILE
  while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
    int columnCounter = 0;

    for (i = 0; i < BUFFER_SIZE; i++) {
      if (i % 2 == 0 && i < BUFFER_SIZE - 1) {
        currentGeneration[rowCounter][columnCounter] = buffer[i];
        columnCounter++;
      }
    }

    rowCounter++;
  }

  fclose(fp);
  // END IMPORTING DATA FROM FILE

  generationLimit = atoi(argv[1]);
  if (generationLimit < 1) {
    printf("Please choose at least one generation.");
    exit(1);
  }

  while (generationCounter < generationLimit) {
    for (row = 0; row < ROWS; row++) {
      for (column = 0; column < COLUMNS; column++) {
        newGenerationPlaceholder[row][column] = computeNewCellStatus(row, column, currentGeneration);
      }
    }

    for (row = 0; row < ROWS; row++) {
      for (column = 0; column < COLUMNS; column++) {
        currentGeneration[row][column] = newGenerationPlaceholder[row][column];
      }
    }

    generationCounter++;
  }

  char newFileName[50];
  strcpy(newFileName, argv[2]);
  char extension[] = ".out";
  strcat(newFileName, extension);

  FILE *output_file = fopen(newFileName, "w+");

  for (i = 0; i < ROWS; i++) {
    for (n = 0; n < COLUMNS; n++) {
      if (n == COLUMNS - 1) {
        fprintf(output_file, "%c", currentGeneration[i][n]);
      } else {
        fprintf(output_file, "%c ", currentGeneration[i][n]);
      }
    }

    if (i < ROWS - 1) {
      fprintf(output_file, "\n");
    }
  }

  fclose(output_file);

  // for (size_t i = 0; i < ROWS; i++) {
  //   for (size_t n = 0; n < COLUMNS; n++) {
  //     printf("%c ", currentGeneration[i][n]);
  //   }
  //
  //   printf("\n");
  // }
}
