
/*
		Author: Asher Yasia

		This program opens a text file, filters it's value and conducts a sorting process
		on an the assigned araay by three optional data structure sortting algorithms:

			1. quick sort
			2. merge sort
			3. insertion sort

*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define N 25
#define row 3
#define col 10

typedef struct Player
{
	char Name[N];
	char Team[N];
	char Height[N];
	char Weight[N];
	char Position[N];
	int age;
}Player;

char* Char_Filter(char[N]);
int Convert_str_weight_to_int(char*);
float Convert_str_height_to_float(char*);
void Merge_Sort(Player*, int, int);
void Insertion_Sort(Player*);
void Merge(Player*, int, int, int);
int Partition(Player*, int, int);
void Quick_Sort(Player*, int, int);
void Print_Mat(Player*);

int main(){
	

	char c = 0, temp[N * 3], str[N];
	Player arr[10], orginal[10];
	FILE* ptr = NULL;              //declaring a file pointer
	ptr = fopen("list _of_players.txt", "r");    //opens  the text file
	if (ptr == NULL){
		printf("ERORR!!, The file could not be open!\n");  //output in case the file dosen't open
		exit(1);
	}
	int i = 0, k = 0;
	while (c != EOF) {  //loop for intialize the struct array by the file's data
		c = fgetc(ptr);
		temp[k] = c;
		k++;
		if (temp[k - 1] == 'e'&&temp[k - 2] == 'm'&&temp[k - 3] == 'a'&&temp[k - 4] == 'n'){
			fgets(str, N, ptr);
			strcpy(arr[i].Name, Char_Filter(str));
			k = 0;
		}
		else if (temp[k - 1] == 'm'&&temp[k - 2] == 'a'&&temp[k - 3] == 'e'&&temp[k - 4] == 't'){
			fgets(str, N, ptr);
			strcpy(arr[i].Team, Char_Filter(str));
			k = 0;
		}
		else if (temp[k - 1] == 't'&&temp[k - 2] == 'h'&&temp[k - 3] == 'g'&&temp[k - 4] == 'i'&&temp[k - 5] == 'e'&&temp[k - 6] == 'h'){
			fgets(str, N, ptr);
			strcpy(arr[i].Height, Char_Filter(str));
			k = 0;
		}
		else if (temp[k - 1] == 't'&&temp[k - 2] == 'h'&&temp[k - 3] == 'g'&&temp[k - 4] == 'i'&&temp[k - 5] == 'e'&&temp[k - 6] == 'w'){
			fgets(str, N, ptr);
			strcpy(arr[i].Weight, Char_Filter(str));
			k = 0;
		}
		else if (temp[k - 1] == 'n'&&temp[k - 2] == 'o'&&temp[k - 3] == 'i'&&temp[k - 4] == 't'&&temp[k - 5] == 'i'&&temp[k - 6] == 's'&&temp[k - 7] == 'o'&&temp[k - 8] == 'p'){
			fgets(str, N, ptr);
			strcpy(arr[i].Position, Char_Filter(str));
			k = 0;
		}
		else if (temp[k - 1] == 'e'&&temp[k - 2] == 'g'&&temp[k - 3] == 'a'){
			fgets(str, N, ptr);
			char gil[4];
			strcpy(gil, Char_Filter(str));
			arr[i].age = (gil[0] - '0') * 10 + (gil[1] - '0'); // converting string type to int
			i++;
			k = 0;
		}
	}//while
	fclose(ptr);

	/*copying the original order of the file to an additional array*/
	for (int i = 0; i < col; i++)
		orginal[i] = arr[i];
	int choice = 0;
	while (choice != 5) {  //program menu
	
		printf("Enter your choice:\n");
		printf("1. Show List of Players\n2. Show Sorted List By Height\n");
		printf("3 .Show Sorted List By Weight\n4. Show Sorted List By Age\n5. Exit\n");
		scanf("%d", &choice);
		switch (choice){
		case 1:
			printf("\nPlayers List by Role (Original Order):\n");
			Print_Mat(orginal);
			for (int i = 0; i < col; i++)
				printf("[%s]  ", orginal[i].Position);
			printf("\n\n");
			break;
		case 2:
			printf("\nQuick Sort by Height:\n");
			Quick_Sort(arr, 0, 9);
			Print_Mat(arr);
			for (int i = 0; i < col; i++)
				printf("[%s]\t  ", arr[i].Height);
			printf("\n\n");
			break;
		case 3:
			printf("\nMerge Sort by Weight:\n");
			Merge_Sort(arr, 0, 9);
			Print_Mat(arr);
			for (int i = 0; i < col; i++)
				printf("[%s]\t  ", arr[i].Weight);
			printf("\n\n");
			break;
		case 4:
			printf("\nInsertion Sort by Age:\n");
			Insertion_Sort(arr, 0, 9);
			Print_Mat(arr);
			for (int i = 0; i < col; i++)
				printf("[%d]\t\t   ", arr[i].age);
			printf("\n\n");
			break;
		case 5:
			printf("\nBye Bye!!\n\n");
			break;
		default:
			printf("\nWorong Choice, Try Again!!\n\n");
			break;
		}//switch
	}//while

	return 0;
}

char* Char_Filter(char str[N]){
	/*This function removes unwanted charechters from a string*/
	int i = 0, k = 0;
	char temp[N];
	while (str[i] != '\0'){
		if (str[i] >= 'A'&&str[i] <= 'Z' || str[i] >= 'a'&&str[i] <= 'z' || str[i] == ' ' || str[i] >= '0'&&str[i] <= '9' || str[i] == '-'){
			temp[k] = str[i];
			k++;
		}
		i++;
	}
	temp[k] = '\0';
	return temp;
}
int Convert_str_weight_to_int(char* str){
	/*This program filters a string by converting only diggits to int*/
	int size = strlen(str), i = 0;
	while (i < size){
		if (str[i] >= '0'&&str[i] <= '9')
			i++;
		else
			break;
	}
	size = 1;
	int weight = 0, temp = 1;
	while (size < i){
		temp *= 10;
		size++;
	}
	for (int k = 0; k < i; k++){
		weight += (str[k] - '0') * temp;  //preform the int convertion
		temp /= 10;
	}
	return weight;
}
float Convert_str_height_to_float(char* str){
	/*This program filters a string by converting only diggits to float*/
	int size = strlen(str), i = 2;
	char temp[4];
	temp[0] = str[0];
	temp[1] = '.';
	while (i < size){
		if (str[i] >= '0'&&str[i] <= '9'){
			temp[2] = str[i];
			break;
		}
		i++;
	}
	temp[3] = '\0';
	float height = 0;
	height = strtof(temp, NULL);    //float convertion
	return height;
}

void Insertion_Sort(Player* arr){  //sort by age
	/*sorts the array with no additional memory or temp array
	by comparing tow element each time*/
	Player temp;
	for (int j = 1; j < 10; j++){
		temp = arr[j];
		int i = j - 1;
		while (i >= 0 && arr[i].age > temp.age){
			arr[i + 1] = arr[i];
			i--;
		}
		arr[i + 1] = temp;
	}
}

void Merge_Sort(Player* arr, int l, int r){ //sort by weight

	/*sorts the array by divide and conqure technique
	and by another additional function*/
	if (l < r){
		int mid = (l + r) / 2;
		Merge_Sort(arr, l, mid);
		Merge_Sort(arr, mid + 1, r);
		Merge(arr, l, mid, r);
	}
}
void Merge(Player* arr, int left, int mid, int right){
	/*merges two parts of the array*/
	Player temp[N];
	int i = left, j = mid + 1, k = 0;

	while (i <= mid && j <= right){
		if (Convert_str_weight_to_int(arr[i].Weight) < Convert_str_weight_to_int(arr[j].Weight)){
			temp[k] = arr[i];
			i++;
		}
		else{
			temp[k] = arr[j];
			j++;
		}
		k++;
	}
	while (i <= mid){
		temp[k] = arr[i];
		i++;
		k++;
	}
	while (j <= right){
		temp[k] = arr[j];
		j++;
		k++;
	}
	for (i = left, j = 0; i <= right; i++, j++)
		arr[i] = temp[j];
}

void Quick_Sort(Player* A, int p, int r){
	if (p < r){
		int q = Partition(A, p, r);
		Quick_Sort(A, p, q - 1);
		Quick_Sort(A, q + 1, r);
	}
}
int Partition(Player* A, int p, int r){
	Player temp;
	float pivot = Convert_str_height_to_float(A[r].Height);
	int i = p, j = r + 1;
	while (1){
		do
			++i;
		while (Convert_str_height_to_float(A[i].Height) <= pivot && i <= r);
		do
			--j;
		while (Convert_str_height_to_float(A[j].Height) > pivot);
		if (i >= j)
			break;
		temp = A[i];
		A[i] = A[j];
		A[j] = temp;
	}
	temp = A[p];
	A[p] = A[j];
	A[j] = temp;
	return j;
}

void Print_Mat(Player* arr){
	/*function to print the elements*/
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			if (i == 0)
				printf("Player num: %d\t   ", j + 1);
			else if (i == 1)
				printf("[%s]  ", arr[j].Name);
		}
		if (i < 2)
			printf("\n");
	}
}