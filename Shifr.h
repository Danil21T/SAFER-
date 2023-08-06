#pragma once
#include "Function.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <bitset>
#include <ctime>
#include <tchar.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "C:\Users\Данил\Desktop\programm\VisualProject\SAFER+\stb\stb_image.h"
#include "C:\Users\Данил\Desktop\programm\VisualProject\SAFER+\stb\stb_image_write.h"

#define CHANNEL_NUM 3

using namespace std;

class Shifr
{
private:
	vector<unsigned char> k;
	vector<unsigned char> helper;
	vector<vector<unsigned char>> key;
	vector<unsigned char> capl;
	const char* nameFile;
	int M1[16][16] = {
	{ 2, 2, 1, 1, 16, 8, 2, 1, 4, 2, 4, 2, 1, 1, 4, 4},
	{ 1, 1, 1, 1, 8, 4, 2, 1, 2, 1, 4, 2, 1, 1, 2, 2},
	{ 1, 1, 4, 4, 2, 1, 4, 2, 4, 2, 16, 8, 2, 2, 1, 1},
	{ 1, 1, 2, 2, 2, 1, 2, 1, 4, 2, 8, 4, 1, 1, 1, 1},
	{ 4, 4, 2, 1, 4, 2, 4, 2, 16, 8, 1, 1, 1, 1, 2, 2},
	{ 2, 2, 2, 1, 2, 1, 4, 2, 8, 4, 1, 1, 1, 1, 1, 1},
	{ 1, 1, 4, 2, 4, 2, 16, 8, 2, 1, 2, 2, 4, 4, 1, 1},
	{ 1, 1, 2, 1, 4, 2, 8, 4, 2, 1, 1, 1, 2, 2, 1, 1},
	{ 2, 1, 16, 8, 1, 1, 2, 2, 1, 1, 4, 4, 4, 2, 4, 2},
	{ 2, 1, 8, 4, 1, 1, 1, 1, 1, 1, 2, 2, 4, 2, 2, 1},
	{ 4, 2, 4, 2, 4, 4, 1, 1, 2, 2, 1, 1, 16, 8, 2, 1},
	{ 2, 1, 4, 2, 2, 2, 1, 1, 1, 1, 1, 1, 8, 4, 2, 1},
	{ 4, 2, 2, 2, 1, 1, 4, 4, 1, 1, 4, 2, 2, 1, 16, 8},
	{ 4, 2, 1, 1, 1, 1, 2, 2, 1, 1, 2, 1, 2, 1, 8, 4},
	{ 16, 8, 1, 1, 2, 2, 1, 1, 4, 4, 2, 1, 4, 2, 4, 2},
	{ 8, 4, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 2, 1, 4, 2}
	};

	int M2[16][16] = {
	{ 2, 254, 1, 254, 1, 255, 4, 248, 2, 252, 1, 255, 1, 254, 1, 255},
	{252, 4, 254, 4, 254, 2, 248, 16, 254, 4, 255, 1, 255, 2, 255, 1},
	{ 1, 254, 1, 255, 2, 252, 1, 255, 1, 255, 1, 254, 2, 254, 4, 248},
	{ 254, 4, 254, 2, 254, 4, 255, 1, 255, 1, 255, 2, 252, 4, 248, 16},
	{1, 255, 2, 252, 1, 255, 1, 254, 1, 254, 1, 255, 4, 248, 2, 254},
	{ 255, 1, 254, 4, 255, 1, 255, 2, 254, 4, 254, 2, 248, 16, 252, 4},
	{ 2, 252, 1, 255, 1, 254, 1, 255, 2, 254, 4, 248, 1, 255, 1, 254},
	{ 254, 4, 255, 1, 255, 2, 255, 1, 252, 4, 248, 16, 254, 2, 254, 4},
	{ 1, 255, 1, 254, 1, 255, 2, 252, 4, 248, 2, 254, 1, 254, 1, 255},
	{ 255, 1, 255, 2, 255, 1, 254, 4, 248, 16, 252, 4, 254, 4, 254, 2},
	{ 1, 254, 1, 255, 4, 248, 2, 254, 1, 255, 1, 254, 1, 255, 2, 252},
	{ 255, 2, 255, 1, 248, 16, 252, 4, 254, 2, 254, 4, 255, 1, 254, 4},
	{ 4, 248, 2, 254, 1, 254, 1, 255, 1, 254, 1, 255, 2, 252, 1, 255},
	{ 248, 16, 252, 4, 254, 4, 254, 2, 255, 2, 255, 1, 254, 4, 255, 1},
	{ 1, 255, 4, 248, 2, 254, 1, 254, 1, 255, 2, 252, 1, 255, 1, 254},
	{254, 2, 248, 16, 252, 4, 254, 4, 255, 1, 254, 4, 255, 1, 255, 2} };

	int round;

public:
	//keyFile - имя файла, где хранится ключ
	//n - размер ключа в байтах
	//nameFile - имя файла, который нужно зашифровать в формате .png
	Shifr(const char* keyFile, int n, const char* nameFile) {
		this->nameFile = nameFile;
		ifstream fit;
		try {
			fit.open(keyFile);
		}
		catch (exception e) {
			cout << e.what();
		}
		round = 0;
		switch (n)
		{
		case(16):
			round = 8;
			break;
		case(24):
			round = 12;
			break;
		case(32):
			round = 16;
			break;
		default:
			break;
		}
		char symbol;
		int count = 0;
		while (!fit.eof()) {
			fit.get(symbol);
			if (!fit.eof()) {
				if (count < 16) {
					k.push_back(symbol);
					count++;
				}
				helper.push_back(symbol);
			}

		}
		fit.close();
		unsigned char value = helper[0];
		for (int i = 1; i < n; i++) {
			value = modPlus(value, helper[i], 2);
		}
		helper.push_back(value);
		key.push_back(k);
		k.clear();
		for (int i = 1; i <= 2 * round; i++) {
			searchkey(i);
			k.clear();
		}

	}
	//n - размер ключа в байтах
	//nameFile - имя файла, который нужно зашифровать в формате .png
	Shifr(int n, const char* nameFile) {
		this->nameFile = nameFile;
		round = 0;
		switch (n)
		{
		case(16):
			round = 8;
			break;
		case(24):
			round = 12;
			break;
		case(32):
			round = 16;
			break;
		default:
			break;
		}
		srand(time(NULL));
		int count = 0;
		for (int i = 0; i < n; i++) {
			unsigned char v = mod((unsigned char)rand(), 256);
			unsigned char o = mod((unsigned char)rand(), 10);
			if (count < 16) {
				k.push_back(v);
				capl.push_back(o);
				count++;
			}
			helper.push_back(v);
		}
		unsigned char value = helper[0];
		for (int i = 1; i < n; i++) {
			value = modPlus(value, helper[i], 2);
		}
		helper.push_back(value);
		key.push_back(k);
		k.clear();
		for (int i = 1; i <= 2 * round; i++) {
			searchkey(i);
			k.clear();
		}
		initlog();

	}
	//Шифрование файла
	void safer(const char* nameFileCoding) {
		if (((string)nameFile).find(".txt") != -1) {
			ifstream fit;
			ofstream fout;
			try {
				fit.open(nameFile, ios::in);
				fout.open(nameFileCoding, ios::out);
			}
			catch (exception e) {
				cout << e.what();
			}
			vector<unsigned  char> text;
			while (!fit.eof()) {
				char symbol;
				for (int i = 0; i < 16; i++) {
					fit.get(symbol);
					if (!fit.eof()) {
						text.push_back(symbol);
					}
				}
				if (!text.empty()) {
					text = coding(text);
					//text = ofb(text);
				}
				for (int i = 0; i < text.size(); i++) {
					fout << (char)text[i];
				}
				text.clear();
			}
		}
		else if (((string)nameFile).find(".png")) {
			int width, height, bpp;
			const char name = (const char)nameFile;
			uint8_t* rgb_image = stbi_load(nameFile, &width, &height, &bpp, 3);

			vector<unsigned  char> text;
			int count = 0;
			int i = 0;
			for (i; i < width * height * 3; i++) {
				text.push_back((unsigned char)rgb_image[i]);
				count++;
				if (count == 16) {
					text = coding(text);
					//text = ofb(text);
					for (int z = 0; z < 16; z++) {
						rgb_image[i - z] = text[15-z];
					}
					count = 0;
					text.clear();
				}
			}
			if (count < 16 && count!=0) {
				text = coding(text);
				for (int z = 0; z < 16; z++) {
					rgb_image[i - z] = text[15 - z];
				}
			}

			stbi_write_png(nameFileCoding, width, height, CHANNEL_NUM, rgb_image, width * CHANNEL_NUM);
			stbi_image_free(rgb_image);
		}


	}
	//Расшифрование файла
	void desafer(const char* nameFileDeCoding, const char* nameFileResult) {
		if (((string)nameFileDeCoding).find(".txt") != -1) {
			ifstream fin;
			ofstream fout;
			try {
				fin.open(nameFileDeCoding, ios::in);
				fout.open(nameFileResult, ios::out);
			}
			catch (exception e) {
				cout << e.what();
			}
			vector<unsigned char> text;
			while (!fin.eof()) {
				char symbol;
				for (int i = 0; i < 16; i++) {
					fin.get(symbol);
					if (!fin.eof()) {
						text.push_back((symbol));
					}
				}
				cout << endl;
				if (!text.empty()) {
					text = decoding(text);
				}
				for (int i = 0; i < text.size(); i++) {
					fout << (char)text[i];
				}
				text.clear();
			}
		}
		else if (((string)nameFileDeCoding).find(".png") != -1) {
			int width, height, bpp;
			const char name = (const char)nameFile;
			uint8_t* rgb_image = stbi_load(nameFileDeCoding, &width, &height, &bpp, 3);

			vector<unsigned  char> text;
			int count = 0;
			int i = 0;
			for (i; i < width * height * 3; i++) {
				text.push_back((unsigned char)rgb_image[i]);
				count++;
				if (count == 16) {
					text = decoding(text);
					for (int z = 0; z < 16; z++) {
						rgb_image[i - z] = text[15 - z];
					}
					count = 0;
					text.clear();
				}
			}
			if (count < 16 && count != 0) {
				text = coding(text);
				for (int z = 0; z < 16; z++) {
					rgb_image[i - z] = text[15 - z];
				}
			}

			stbi_write_png(nameFileResult, width, height, CHANNEL_NUM, rgb_image, width * CHANNEL_NUM);
			stbi_image_free(rgb_image);
		}

	}

	//Расшифрование блока данных
	vector<unsigned char> decoding(vector<unsigned  char> text) {
		vector<unsigned char> result;
		for (int i = 0; i < text.size(); i++) {
			result.push_back(text[i]);
		}

		for (int j = 0; j < result.size(); j++) {
			switch (j) {
			case(0):
			case(3):
			case(4):
			case(7):
			case(8):
			case(11):
			case(12):
			case(15):
				result[j] = result[j] ^ key[round*2][j];
				break;
			default:
				result[j] = (modMinus(result[j], key[2 * round][j], 256));
				break;
			}
		}


		for (int i = 7; i >= 0; i--) {
			result = multiply(1, result);
			int k = 2 * i + 1;

			for (int j = 0; j < result.size(); j++) {
				switch (j) {
				case(0):
				case(3):
				case(4):
				case(7):
				case(8):
				case(11):
				case(12):
				case(15):
					result[j] = (modMinus(result[j], key[k][j], 256));
					break;
				default:
					result[j] = result[j] ^ key[k][j];
					break;
				}
			}

			for (int z = 0; z < result.size(); z++) {
				result[z] = retransformation(z, result[z]);
			}

			k = 2 * i;
			for (int j = 0; j < result.size(); j++) {
				switch (j) {
				case(0):
				case(3):
				case(4):
				case(7):
				case(8):
				case(11):
				case(12):
				case(15):
					result[j] = result[j] ^ key[k][j];
					break;
				default:
					result[j] = modMinus(result[j], key[k][j], 256);
					break;
				}
			}
		}
		return result;
	}
	//Шифрование блока данных
	vector<unsigned char> coding(vector<unsigned  char> text) {
		vector<unsigned char> result;
		for (int i = 0; i < text.size(); i++) {
			result.push_back(text[i]);
		}

		for (int i = 0; i < round; i++) {
			int k = 2 * i;
			for (int j = 0; j < result.size(); j++) {
				switch (j) {
				case(0):
				case(3):
				case(4):
				case(7):
				case(8):
				case(11):
				case(12):
				case(15):
					result[j] = result[j]^key[k][j];
					break;
				default:
					result[j] = modPlus(result[j], key[k][j], 256);
					break;
				}
			}

			for (int z = 0; z < result.size(); z++) {
				result[z] = transformation(z, result[z]);
			}

			k = 2 * i + 1;
			for (int j = 0; j < result.size(); j++) {
				switch (j) {
				case(0):
				case(3):
				case(4):
				case(7):
				case(8):
				case(11):
				case(12):
				case(15):
					result[j] = (modPlus(result[j], key[k][j], 256));
					break;
				default:
					result[j] = result[j] ^ key[k][j];
					break;
				}
			}


			result = multiply(0, result);

		}
		for (int j = 0; j < result.size(); j++) {
			switch (j) {
			case(0):
			case(3):
			case(4):
			case(7):
			case(8):
			case(11):
			case(12):
			case(15):
				result[j] = result[j] ^ key[round*2][j];
				break;
			default:
				result[j] = (modPlus(result[j], key[2 * round][j], 256));
				break;
			}
		}

		return result;
	}
	//умножение матриц
	vector<unsigned char> multiply(int choise, vector<unsigned char> text) {
		vector<int> help;
		vector<unsigned char> result;
		int count = 0;
		if (text.size() < 16) {
			for (int i = text.size(); i < 16; i++) {
				text.push_back(NULL);
				count++;
			}
		}
		for (int i = 0; i < text.size(); i++) {
			help.push_back((int)(text[i]));
		}
		if (choise == 0) {
			int value = 0;
			for (int i = 0; i < 16; i++)
			{
				for (int j = 0; j < 16; j++)
				{
					value += mod((M1[i][j] * help[j]), 256);
				}
				value %= 256;
				result.push_back((unsigned char)(value));
				value = 0;
			}
		}
		else if (choise == 1) {
			int value = 0;
			for (int i = 0; i < 16; i++)
			{
				for (int j = 0; j < 16; j++)
				{
					value += mod((M2[i][j] * help[j]), 256);
				}
				value %= 256;
				result.push_back((unsigned char)(value));
				value = 0;
			}
		}
		for (int i = 0; i < count; i++) {
			result.pop_back();
		}
		return result;
	}
	//Генерация ключа
	void searchkey(int i) {
		for (int j = 0; j < helper.size(); j++) {
			helper[j] = right_shift(helper[j], 3);
		}
		int count = 0;
		for (int j = i; j < helper.size(); j++) {
			k.push_back(helper[j]);
			count++;
			if (count == 16) {
				break;
			}
		}
		if (count != 16) {
			for (int j = 0; j < 16 - count; j++) {
				k.push_back(helper[j]);
			}
		}
		for (int j = 0; j < k.size(); j++) {
			k[j] = modPlus(k[j], offsetword(i + 1, j), 256);
		}
		key.push_back(k);
	}
	//Выод полученного ключа
	void resultkey() {
		for (int i = 0; i < key.size(); i++) {
			cout << "Key " << i << ": ";
			for (int j = 0; j < key[i].size(); j++) {
				cout << (key[i][j]) << " ";
			}
			cout << endl;
		}
	}
	//Шифрование в режиме OFB
	vector<unsigned char> ofb(vector<unsigned char> text) {
		vector<unsigned char> hell;
		for (int i = 8; i < 16; i++) {
			hell.push_back(capl[i]);
		}
		capl = coding(capl);
		vector<unsigned char> res;
		for (int i = 0; i < text.size(); i++) {
			res.push_back(text[i] ^ capl[i]);
		}
		for (int i = 0; i < 8; i++) {
			hell.push_back(capl[i]);
		}

		capl = hell;

		return res;
	}
	//Расифрование в режиме OFB
	vector<unsigned char> deofb(vector<unsigned char> text) {
		vector<unsigned char> hell;
		for (int i = 0; i < 8; i++) {
			hell.push_back(0);
		}
		for (int i = 0; i < 8; i++) {
			hell.push_back(capl[i]);
		}

		vector<unsigned char> res;

		for (int i = 0; i < text.size(); i++) {
			res.push_back(text[i] ^ capl[i]);
		}
		capl = decoding(capl);
		for (int i = 0; i < 8; i++) {
			hell[i] = capl[i];
		}

		capl = hell;
		hell.clear();

		return res;
	}
};