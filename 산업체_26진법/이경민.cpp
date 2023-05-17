#include <stdio.h>
#define STRING_SIZE 12800
#define PARAM_SIZE 100
#define DEPTH_SIZE 127


int charToInt(char ch) {
	if (ch == '+') {
		return -1;
	}
	else if (ch == '-') {
		return -2;
	}
	else if (ch >= 'A' && ch <= 'Z') {
		return ch - 'A';
	}
	else {
		return -3;
	}
}

char intToChar(int num) {
	if (num == -1) {
		return '+';
	}
	else if (num == -2) {
		return '-';
	}
	else if (num >= 0 && num <= 25) {
		return 'A' + num;
	}
	else {
		return '\0';
	}
}

void recordGreatestDigit(char* temp, int col, int* index) {
	if (temp[col] == 'A' && temp[col - 1] != 'A') index[100] = col;
}

void performAddition(char temp[], int carry, int index[], int row, char arr[][DEPTH_SIZE + 1]) {
	for (int col = 1; col < STRING_SIZE; col++) {
		int sum = charToInt(temp[col]) + carry - 26;
		if (index[row] - 1 >= 1)
			sum += charToInt(arr[row][index[row] - 1]);
		if (sum >= 0)
			carry = 1;
		else {
			sum += 26;
			carry = 0;
		}

		temp[col] = intToChar(sum);
		recordGreatestDigit(temp, col, index);
		index[row]--;
	}
}

void performDstSubtraction(char temp[], int borrow, int index[], int row, char arr[][DEPTH_SIZE + 1]) {
	for (int col = 1; col < STRING_SIZE; col++) {
		int diff = charToInt(arr[row][index[row] - 1]) - charToInt(temp[col]) - borrow;

		if (diff < 0) {
			borrow = 1;
			diff += 26;
		}
		else {
			borrow = 0;
		}
		if (index[row] - 1 < 1);
		else {
			temp[col] = intToChar(diff);
		}
		recordGreatestDigit(temp, col, index);
		index[row]--;
	}
}

void performSrcSubtraction(char temp[], int borrow, int index[], int row, char arr[][DEPTH_SIZE + 1]) {
	for (int col = 1; col < STRING_SIZE; col++) {
		int diff = charToInt(temp[col]) - charToInt(arr[row][index[row]-1]) - borrow;

		if (diff < 0) {
			borrow = 1;
			diff += 26;
		}
		else {
			borrow = 0;
		}
		if (index[row] - 1 < 1);
		else {
			temp[col] = intToChar(diff);
		}
		recordGreatestDigit(temp, col, index);
		index[row]--;
	}
}

void finalize(char temp[], int index[], char arr[]) {
	int i, j;
	for (i = index[100]-1, j = 1; i >= 1; i--, j++) {
		arr[j] = temp[i];
		printf("%c", arr[j]);
	}
	arr[0] = temp[0];
}

void test_main(char answer[STRING_SIZE], const char question[STRING_SIZE]) {

	char arr[PARAM_SIZE][DEPTH_SIZE + 1] = { '+' };
	int index[PARAM_SIZE + 1] = { 0 };
	char temp[STRING_SIZE] = {};
	temp[0] = '+';
	index[100] = 1;

	int i = 0;
	int row = 0;
	int col = 1;
	int reset = 0;
	while (i < STRING_SIZE) {
		char letter = question[i];
		if (letter == '+' || letter == '-') {
			index[row] = col;
			row++; col = 0;
			arr[row][0] = letter;
		}
		else {
			arr[row][col] = letter;
		}
		col++;i++;
		temp[i] = 'A';

		if (letter == NULL) {
			index[row] = col-1;
			reset = row + 1;
			break;
		}
	}

	for (int row = reset; row < PARAM_SIZE; row++) {
		index[row] = 0;
	}

	for (int row = 0; row <= reset; row++) {
		int carry = 0;
		int borrow = 0;
		if (temp[0] == '+') {
			if (arr[row][0] == '+') { // 양수 + 양수
				performAddition(temp, carry, index, row, arr);

			}
			else { // 양수 - 양수
				if (index[row] - 1 >= index[100]) { // 자리수가 같을 때
					if (arr[row][index[row] - 1] >= temp[index[100]]) { // 양수 - 양수 = 음수
						performDstSubtraction(temp, borrow, index, row, arr);
						if (temp[index[100]-1] == 'A') temp[0] = '+'; // 결과 값이 0 일 때
						else { // 결과 값이 음수일 때
							temp[0] = '-';
						}
					}
				}
				else { // 양수 - 양수 = 양수
					performSrcSubtraction(temp, borrow, index, row, arr);
					temp[0] = '+';
				}
			}
		}
		else {
			if (index[100] == index[row] - 1) {
				if (temp[index[100]] >= arr[row][index[row] - 1]) {
					performSrcSubtraction(temp, borrow, index, row, arr);
					temp[0] = '-';
				}
				else {
					performDstSubtraction(temp, borrow, index, row, arr);
					temp[0] = '+';
				}
			}
			if (index[100] > index[row] - 1) {
				performSrcSubtraction(temp, borrow, index, row, arr);
				temp[0] = '-';
			}
			else {
				performDstSubtraction(temp, borrow, index, row, arr);
				temp[0] = '+';
			}
		}
		index[row]--;
	}

	finalize(temp, index, answer);
	return;
}
