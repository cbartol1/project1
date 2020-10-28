
#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int main(int argc, char *argv[]) {

  // Temporary variables
  unsigned long long addr;
  char behavior[10];
  unsigned long long target;
  int taken = 1;
  int correct = 0;
  int table[16];
  int index;

  for(int i = 0; i < (sizeof(table)/sizeof(table[0])); i++){
	table[i] = 3;
  }

  int mask = 0xF;

  // Open file for reading
  FILE *input = fopen("./test_input.txt", "r");

  // The following loop will read a hexadecimal number and a string each
  // time and then output them
  while(fscanf(input, "%llx %10s %llx\n", &addr, behavior, &target) != EOF) {
    index = addr & mask;
    if(!strncmp(behavior, "T", 2)) {
      if(table[index] >= 2){
	correct++;
      }
      if(table[index] != 3) table[index]++;
    }
    else{
      if(table[index] < 2){
        correct++;
      }
      if(table[index] != 0) table[index]--;
    }
  }
  printf("%lld\n", correct);
  return 0;
}

