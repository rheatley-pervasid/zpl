#!/bin/zsh

g++ -pthread -g -Wall -Wextra -Wno-unused-function -Wno-missing-field-initializers -std=c++11 -I../include $1 -lm -ldl
