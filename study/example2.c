#include <stdio.h>

int binsearch(int list[], int searchnum, int left, int right);
int compare(int x, int y);

int main() {
	int searchnum;
	int arr[7] = {1, 2, 3, 4, 5, 6, 7 };
	printf("searchnum: ");
	scanf("%d ", &searchnum);

	binsearch(arr, searchnum, 0, 6);
}

int compare(int x, int y) {
	if (x < y)
		return -1;
	else if (x == y)
		return 0;
	else
		return 1;
}

int binsearch(int list[], int searchnum, int left, int right) {
	int middle;
	while (left <= right) {
		middle = (left + right) / 2;
		switch (compare(list[middle], searchnum)) {
		case -1:
			left = middle + 1;
			break;
		case 0:
			return middle;
		case 1: 
			right = middle - 1;
		}
	}
	return -1;
}