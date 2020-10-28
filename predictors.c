#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void always_taken(char* file, int size, char* output) {

  // Temporary variables
  unsigned long long addr;
  char behavior[size];
  unsigned long long target;
  int count = 0;
  int total = 0;

  // Open file for reading
  FILE *input = fopen(file, "r");

  while(fscanf(input, "%llx %10s %llx\n", &addr, behavior, &target) != EOF) {
    if(!strncmp(behavior, "T", 2)) {
      count++;
    }
    total++;
  }
  char str1[10];
  char str2[10];
  sprintf(str1, "%d", count);
  printf("%lld, %lld\n", count, total);
  FILE *out = fopen(output, "a");
  fputs(str1, out);
  sprintf(str2, "%d", total);
  fputs(", ", out);
  fputs(str2, out);
  fputs("\n", out);
  fclose(out);
  //return 0;
}

void always_ntaken(char *file, int size, char* output) {

  // Temporary variables
  unsigned long long addr;
  char behavior[size];
  unsigned long long target;
  int count = 0;
  int total = 0;

  // Open file for reading
  FILE *input = fopen(file, "r");

  while(fscanf(input, "%llx %10s %llx\n", &addr, behavior, &target) != EOF) {
    if(strncmp(behavior, "T", 2)) {
      count++;
    }
    total++;
  }
  char str1[10];
  char str2[10];
  sprintf(str1, "%d", count);
  printf("%lld, %lld\n", count, total);
  FILE *out = fopen(output, "a");
  fputs(str1, out);
  sprintf(str2, "%d", total);
  fputs(", ", out);
  fputs(str2, out);
  fputs("\n", out);
  fclose(out);
  //return 0;
}

void bimodal_one_bit(char* file, int nlines, int nbits, char* output) {

  // Temporary variables
  unsigned long long addr;
  char behavior[nlines];
  unsigned long long target;
  int taken = 1;
  int correct = 0;
  int table[nbits];
  int index;

  for(int i = 0; i < (sizeof(table)/sizeof(table[0])); i++){
        table[i] = 1;
  }

  int mask = nbits - 1;

  // Open file for reading
  FILE *input = fopen(file, "r");

  while(fscanf(input, "%llx %10s %llx\n", &addr, behavior, &target) != EOF) {
    index = addr & mask;
    if(!strncmp(behavior, "T", 2)) {
      if(table[index] == 1){
        correct++;
      }
      table[index] = 1;
    }
    else{
      if(table[index] == 0){
        correct++;
      }
      table[index] = 0;
    }
  }
  printf("%lld, %lld; ", correct, nlines);
  char str1[10];
  char str2[10];
  sprintf(str1, "%d", correct);
  FILE *out = fopen(output, "a");
  fputs(str1, out);
  sprintf(str2, "%d", nlines);
  fputs(", ", out);
  fputs(str2, out);
  fputs("; ", out);
  fclose(out);
  //return 0;
}

void bimodal_two_bit(char* file, int nlines, int nbits, char* output) {
 // Temporary variables
  unsigned long long addr;
  char behavior[nlines];
  unsigned long long target;
  int taken = 1;
  int correct = 0;
  int table[nbits];
  int index;

  for(int i = 0; i < (sizeof(table)/sizeof(table[0])); i++){
        table[i] = 3;
  }

  int mask = nbits-1;

  // Open file for reading
  FILE *input = fopen(file, "r");

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
  printf("%lld, %lld; ", correct, nlines);
  char str1[10];
  char str2[10];
  sprintf(str1, "%d", correct);
  FILE *out = fopen(output, "a");
  fputs(str1, out);
  sprintf(str2, "%d", nlines);
  fputs(", ", out);
  fputs(str2, out);
  fputs("; ", out);
  fclose(out);
  //return 0;
}
void gshare(char* file, int nlines, int nbits, char* output) {

  // Temporary variables
  unsigned long long addr;
  char behavior[nlines];
  unsigned long long target;
  //int taken = 1;
  int correct = 0;
  int table[2048];
  int index;
  int ghr = 0;
  int mask = 1;

  for(int i = 0; i < (sizeof(table)/sizeof(table[0])); i++){
        table[i] = 3;
  }

  for(int i = 0; i < nbits-1; i++){
	mask = mask << 1;
	mask++;
  }
  //printf("mask is: %lld\n", mask);

  // Open file for reading
  FILE *input = fopen(file, "r");

  while(fscanf(input, "%llx %10s %llx\n", &addr, behavior, &target) != EOF) {
    index = addr & mask;
    ghr = ghr & mask;
    index = index ^ ghr;
    //printf(" ghr = %lld, index = %lld\n", ghr, index);
    if(!strncmp(behavior, "T", 2)) {
      if(table[index] >= 2){
        correct++;
      }
      if(table[index] != 3) table[index]++;
      ghr = ghr << 1;
      ghr++;
    }
    else{
      if(table[index] < 2){
        correct++;
      }
      if(table[index] != 0) table[index]--;
      ghr = ghr << 1;
    }
  }
  printf("%lld, %lld; ", correct, nlines);
  char str1[10];
  char str2[10];
  sprintf(str1, "%d", correct);
  FILE *out = fopen(output, "a");
  fputs(str1, out);
  sprintf(str2, "%d", nlines);
  fputs(", ", out);
  fputs(str2, out);
  fputs("; ", out);
  fclose(out);
  //return 0;
}

void tournament(char* file, int nlines, char* output) {
  unsigned long long addr;
  char behavior[nlines];
  unsigned long long target;
  //int taken = 1;
  int correct = 0;
  int gtable[2048];
  int btable[2048];
  int index;
  int ghr = 0;
  int mask = 1;
  int prefer = 0;

  for(int i = 0; i < 2048; i++){
        gtable[i] = 3;
	btable[i] = 3;
  }

  for(int i = 0; i < 10; i++){
        mask = mask << 1;
        mask++;
  }

  // Open file for reading
  FILE *input = fopen(file, "r");

  while(fscanf(input, "%llx %10s %llx\n", &addr, behavior, &target) != EOF) {
    index = addr & mask;
    ghr = ghr & mask;
    index = index ^ ghr;
    //printf(" ghr = %lld, index = %lld\n", ghr, index);
    if(prefer < 2){
      if(!strncmp(behavior, "T", 2)) {
        if(gtable[index] >= 2 && btable[index] >= 2){
          correct++;
        }
        else if(btable[index] < 2 && gtable[index] < 2){

        }
        else if(btable[index] < 2){
          correct++;
          if(prefer != 0) prefer--;
        }
        else{
          if(prefer != 3) prefer++;
        }
        if(gtable[index] != 3) gtable[index]++;
        if(btable[index] != 3) btable[index]++;
        ghr = ghr << 1;
        ghr++;
      }
      else{
        if(gtable[index] < 2 && btable[index] < 2){
          correct++;
        }
        else if(btable[index] >= 2 && gtable[index] >= 2){

        }
        else if(btable[index] >= 2){
          correct++;
          if(prefer != 0) prefer--;
        }
        else{
          if(prefer != 3) prefer++;
        }
        if(gtable[index] != 0) gtable[index]--;
        if(btable[index] != 0) btable[index]--;
        ghr = ghr << 1;
      }
    }
    else{
       if(!strncmp(behavior, "T", 2)) {
        if(gtable[index] >= 2 && btable[index] >= 2){
          correct++;
        }
        else if(btable[index] < 2 && gtable[index] < 2){

        }
        else if(gtable[index] < 2){
          correct++;
          if(prefer != 0) prefer--;
        }
        else{
          if(prefer != 3) prefer++;
        }
        if(gtable[index] != 3) gtable[index]++;
        if(btable[index] != 3) btable[index]++;
        ghr = ghr << 1;
        ghr++;
      }
      else{
        if(gtable[index] < 2 && btable[index] < 2){
          correct++;
        }
        else if(btable[index] >= 2 && gtable[index] >= 2){

        }
        else if(gtable[index] >= 2){
          correct++;
          if(prefer != 0) prefer--;
        }
        else{
          if(prefer != 3) prefer++;
        }
        if(gtable[index] != 0) gtable[index]--;
        if(btable[index] != 0) btable[index]--;
        ghr = ghr << 1;
      }
    }
  }
  printf("%lld, %lld\n", correct, nlines);
  char str1[10];
  char str2[10];
  sprintf(str1, "%d", correct);
  FILE *out = fopen(output, "a");
  fputs(str1, out);
  sprintf(str2, "%d", nlines);
  fputs(", ", out);
  fputs(str2, out);
  fputs("\n", out);
  fclose(out);
}

int main(int argc, char *argv[]) {
  FILE *fileptr;
    int count_lines = 0;
    char chr;
    fileptr = fopen(argv[1], "r");
   //extract character from file and store in chr
    chr = getc(fileptr);
    while (chr != EOF)
    {
        if (chr == '\n')
        {
            count_lines++;
        }
        chr = getc(fileptr);
    }
  fclose(fileptr);
  //printf("There are %d lines in %s  in a file\n", count_lines, argv[1]);
  always_taken(argv[1], count_lines, argv[2]);
  always_ntaken(argv[1], count_lines, argv[2]);
  for(int i = 16; i <= 2048; i = i*2){
    bimodal_one_bit(argv[1], count_lines, i, argv[2]);
  }
  fileptr = fopen(argv[2], "a");
  fputs("\n", fileptr);
  fclose(fileptr);
  printf("\n");
  for(int i = 16; i <= 2048; i = i*2){
    bimodal_two_bit(argv[1], count_lines, i, argv[2]);
  }
  fileptr = fopen(argv[2], "a");
  fputs("\n", fileptr);
  fclose(fileptr);
  printf("\n");
  for(int i = 3; i <= 11; i++){
    gshare(argv[1], count_lines, i, argv[2]);
  }
  fileptr = fopen(argv[2], "a");
  fputs("\n", fileptr);
  fclose(fileptr);
  printf("\n");
  tournament(argv[1], count_lines, argv[2]);
}
