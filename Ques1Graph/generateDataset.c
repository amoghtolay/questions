#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
 
  int m, n, emptyRatio, jewelRatio, burglarRatio;

  if (argc == 1) {
      m = 40;
      n = 40;
      emptyRatio = 20;
      jewelRatio = 60;
      burglarRatio = 100 - (emptyRatio + jewelRatio);
  } else if (argc == 6) {
    m = atoi(argv[1]);
    n = atoi(argv[2]);
    emptyRatio = atoi(argv[3]);
    jewelRatio = atoi(argv[4]);
    burglarRatio = atoi(argv[5]);
    if (emptyRatio + jewelRatio + burglarRatio != 100) {
      printf("Ratios do not add up to 100\n");
      exit(1);
    }
  } else {
    printf("Arguments are: m, n, emptyRatio, jewelRatio, burglarRatio\n");
    exit(1);
  }

  // Max weight of any cell
  int weightLimit = (m * n * 3 >= 10000 ? 10000 : m * n * 3);
  char filename[100];
  sprintf(filename, "%d-%d_%d-%d-%d.txt", m, n, emptyRatio, jewelRatio, burglarRatio);
  printf("%s\n", filename);

  FILE *file = fopen(filename, "w");
  // Write to file
  fprintf(file, "%d,%d\n", m, n);
  int i, j;
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      if ((i == 0 && j == 0) || (i == m-1 && j == n-1)) {
	fprintf(file, "0");
      } else {
	int prob = rand() % 100;
	int cellValue;
	if (prob < emptyRatio) {
	  cellValue = 0;
	} else if (prob < emptyRatio + jewelRatio) {
	  cellValue = (rand() % weightLimit) + 1; // 1 to weightLimit
	} else {
	  cellValue = -1 * ((rand() % weightLimit) + 1); // -1 to -weightLimit
	}
	fprintf(file, "%d", cellValue);
      }
      
      if (j == n - 1) {
	fprintf(file, "\n");
      } else {
	fprintf(file, ",");
      }
    }
  }

  fclose(file);
  return 0;
}
