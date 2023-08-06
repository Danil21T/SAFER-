#pragma once
#include <cmath>
#include <bitset>
#include <vector>

float logbase(float x, float base);

void initlog();

unsigned char transformation(int index, unsigned char c);

unsigned char retransformation(int index, unsigned char c);

unsigned char modPlus(unsigned char symbol1, unsigned char symbol2, int modl);

unsigned char modMinus(unsigned char symbol1, unsigned char symbol2, int modl);

unsigned char offsetword(int i, int j);

unsigned char right_shift(unsigned char n, int k);

int mod(int v, int mod);