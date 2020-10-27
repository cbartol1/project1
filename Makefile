CC=gcc
CFLAGS=-I.

predictors: predictors.o
  $(CC) -o predictors predictors.o
