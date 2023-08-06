#include "Function.h"
#include <iostream>

int logi[256];
//Вспомогательные математические функции
float logbase(float x, float base) {
	return log(x) / log(base);
}

int degree(int i,int x) {
	if (i == 1) {
		x = 45;
	}
	else if (i == 0) {
		x = 1;
	}
	else if (i == 2) {
		x *= 45;
		x %= 257;
	}
	else {
		for (int z = i - 1; z > 0; z--) {
			x *= 45;
			x %= 257;
		}
	}
	return x;
}

void initlog() {
	for (int i = 0; i < 256; i++) {
		logi[i]=degree(i, 45);
		if (logi[i] == 256) {
			logi[i] = 0;
		}
	}
}

int search(int x) {
	int i = 0;
	for ( i; i < 256; i++) {
		if (logi[i] == x) {
			break;
		}
	}
	return i;
}

unsigned char transformation(int index, unsigned char c) {
	float x = (float)(c);
	switch (index) {
	case(0):
	case(3):
	case(4):
	case(7):
	case(8):
	case(11):
	case(12):
	case(15):
		x = degree(x,45);
		if (x == 256) {
			x = 0;
		}
		break;
	default:
		if (x == 0) {
			x = 128;
		}
		else {
			x = search(x);
		}
		break;
	}
	return (unsigned char)(x);
}

unsigned char modPlus(unsigned char symbol1, unsigned char symbol2, int modl) {
	int s1 = (int)(symbol1);
	int s2 = (int)(symbol2);
	int result = s1 + s2;

	return (unsigned char)mod(result, modl);
}

unsigned char offsetword(int i, int j) {
	if (i < 18) {
		int z = (17 * i + j) % 257;
		int k = degree(z, 45);
		int res = degree(k, 45);
		if (res == 256) {
			res = 0;
		}
		return (unsigned  char)(res);
	}
	else {
		int res = degree(17 * i + j, 45);
		if (res == 256) {
			res = 0;
		}
		return (unsigned char)(res);
	}
}

unsigned  char right_shift(unsigned char n, int k) {
	int res = (int)(n);
	std::bitset<8> h1(res >> k);
	std::bitset<8> h2(res << (8 - k));
	h1 |= h2;
	n = (int)(h1.to_ullong());
	n = (unsigned char)(n);
	return n;

}

unsigned  char retransformation(int index, unsigned  char c) {
	float x = (float)(c);
	//std::cout <<index<<" : "<< x << " | ";
	switch (index) {
	case(0):
	case(3):
	case(4):
	case(7):
	case(8):
	case(11):
	case(12):
	case(15):
		if (x == 0) {
			x = 128;
		}
		else {
			x = search(x);
		}
		//std::cout << x << std::endl;
		break;
	
	default:
		x = degree(x,45);
		if (x == 256) {
			x = 0;
		}
		//std::cout << x << std::endl;
		break;
	}
	//std::cout <<" " << x << " ";
	return (unsigned char)(x);
}

unsigned char modMinus(unsigned char symbol1, unsigned char symbol2, int modl) {
	int s1 = (int)(symbol1);
	int s2 = (int)(symbol2);
	int result = s1 - s2;
	return (unsigned char)mod(result, modl);
	
}

int mod(int v, int mod) {
	int x = v % mod;
	if (x < 0) {
		x += mod;
	}
	return x;
}