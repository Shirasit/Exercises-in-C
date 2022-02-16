#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include <stdio.h>
#define r1 3
#define c1 2
#define r2 2
#define c2 3
typedef struct Trio
{
	int sumIandJ;
	int i;
	int j;
}Trio;

typedef struct Item
{
	struct Trio three;
	struct Item *next;
}Item;
typedef struct list
{
	int data;
	struct list *next;
}list;

/* Function declarations */

void Ex1();
void Ex2();
void Ex3();
void Ex4();
void Ex5();

/* Declarations of other functions */
unsigned int*powerArray(int n);
int** matrixMultiplication(int Matrix1[][c1], int Matrix2[][c2], int row1, int col1, int row2, int col2);
void free_matrix(int **Matrix, int n);
Trio createThree(int x, int y, int value);
Item* createThreeList(Item* lst, Trio* pos);
Trio* createThreeArr(Trio* arr, Trio object, int index);
int createArrayAndList(int** Matrix, int row, int col, Trio**arr, Item** lst);
void printArr(Trio* arr, int size);
void printList(Item* lst);
int** create_matrix(int row, int col);
list* insertTolist(list* lst, list* pos);
list* inputList();
void printlst(list* lst);
list* DeleteItem(list* pos);
list* createList(list** lst);
list* createList2(list** lst);
/* ------------------------------- */

int main()
{
	int select = 0, i, all_Ex_in_loop = 0;
	printf("Run menu once or cyclically?\n(Once - enter 0, cyclically - enter other number) ");
	if (scanf("%d", &all_Ex_in_loop) == 1)
		do
		{
			for (i = 1; i <= 5; i++)
				printf("Ex%d--->%d\n", i, i);
			printf("EXIT-->0\n");
			do {
				select = 0;
				printf("please select 0-5 : ");
				scanf("%d", &select);
			} while ((select < 0) || (select > 5));
			switch (select)
			{
			case 1: Ex1(); break;
			case 2: Ex2(); break;
			case 3: Ex3(); break;
			case 4: Ex4(); break;
			case 5: Ex5(); break;
			}
		} while (all_Ex_in_loop && select);
		return 0;
}


/* Function definitions */

/* ------------------- */



void Ex1()
{
	unsigned int* powArr;
	int size, i;
	printf("enter please size of arr:\n");
	scanf("%d", &size);
	powArr = powerArray(size);
	printf("your arr is: \n");
	for (i = 0; i < size; i++)
	{
		printf("%u \n", powArr[i]);
	}
	free(powArr);
}
unsigned int* powerArray(int n)
{
	int i, x = 1;
	unsigned int* arr = (unsigned int*)malloc(sizeof(unsigned int)*n);
	if (arr == NULL)
	{
		printf("There is not enough space in memory");
		exit(0);
	}
	for (i = 0; i < n; i++)
	{
		if (i % 32 == 0)
			x = 1;

		arr[i] = x;
		x *= 2;
	}
	return arr;
}
void Ex2()
{
	int i, j;
	int matrix1[r1][c1] = { {5,1},{2,3},{3,4} };
	int matrix2[r2][c2] = { {1,2,0},{4,3,-1} };
	int**newMat = matrixMultiplication(matrix1, matrix2, r1, c1, r2, c2);
	printf("your new Martix - after Multiplication is: \n");

	for (i = 0; i < r1; i++)
	{
		for (j = 0; j < c2; j++)
		{
			printf("%3d", newMat[i][j]);
		}
		printf("\n");
	}
	free_matrix(newMat, r1);

}
void free_matrix(int **Matrix, int n)
{
	int i;
	for (i = 0; i < n; i++)
		free(Matrix[i]);
	free(Matrix);
}

int** matrixMultiplication(int Matrix1[][c1], int Matrix2[][c2], int row1, int col1, int row2, int col2)
{
	int i, j, k, sum = 0;
	if (col1 != row2)
	{
		printf("It is not possible to multiply the Matrixs- the size is not valid");
		exit(0);
	}
	int** MultiMatrix = (int**)malloc(sizeof(int*)*row1);
	if (!MultiMatrix)
		return NULL;
	for (i = 0; i < row1; i++)
	{
		MultiMatrix[i] = (int*)malloc(sizeof(int)*col2);
		if (!MultiMatrix[i])
		{
			free_matrix(MultiMatrix, i);
			return NULL;
		}
	}

	for (i = 0; i < row1; i++)
	{
		for (j = 0; j < col2; j++)
		{
			for (k = 0; k < row2; k++)
			{
				sum += Matrix1[i][k] * Matrix2[k][j];
			}
			MultiMatrix[i][j] = sum;
			sum = 0;
		}


	}
	return MultiMatrix;
}



void Ex3()
{
	int countSame;
	int** matrix;
	matrix = create_matrix(r2, c2);
	Trio* arr;
	Item* lst;
	countSame = createArrayAndList(matrix, r2, c2, &arr, &lst);
	printf("the numbers of Trio is: %d \n ", countSame);
	printArr(arr, countSame);
	printList(lst);
	free_matrix(matrix, r2);
	free(lst);
	free(arr);
}

int** create_matrix(int row, int col)
{
	int i, j;
	int** matrix = (int**)malloc(sizeof(int*)*row);
	if (!matrix)
		return NULL;
	for (i = 0; i < r2; i++)
	{
		matrix[i] = (int*)malloc(sizeof(int)*col);
		if (!matrix[i])
		{
			free_matrix(matrix, i);
			return NULL;
		}
	}
	printf("enter please numbers to matrix: %d on %d \n", row, col);
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			scanf("%d", &matrix[i][j]);
		}
	}
	return matrix;
}



Trio createThree(int x, int y, int value)
{
	Trio object;
	object.i = x;
	object.j = y;
	object.sumIandJ = value;
	return object;
}

Item* createThreeList(Item* lst, Trio* pos)
{
	Item* pos1 = (Item*)malloc(sizeof(Item));

	pos1->three = *pos;
	pos1->next = NULL;
	if (lst == NULL)
	{
		return pos1;
	}
	Item* temp = lst;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = pos1;
	return lst;
}

Trio* createThreeArr(Trio* arr, Trio object, int index)
{
	arr[index] = object;
	return arr;
}


int createArrayAndList(int** Matrix, int row, int col, Trio**arr, Item** lst)
{
	Item* temp;
	Trio object;
	int i, j, count = 0, count2 = 0;
	*lst = NULL;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (Matrix[i][j] == (i + j))
			{
				count++;
				object = createThree(i, j, (i + j));
				*lst = createThreeList(*lst, &object);
			}
		}
	}
	temp = *lst;
	*arr = (Trio*)malloc(sizeof(Trio)*count);
	while (temp != NULL)
	{
		*arr = createThreeArr(*arr, temp->three, count2);
		count2++;
		temp = temp->next;
	}
	return count;
}
void printArr(Trio* arr, int size)
{
	int i;
	printf("your arr is: \n");
	for (i = 0; i < size; i++)
	{
		printf(" i = %d ", arr[i].i);
		printf("j = %d ", arr[i].j);
		printf("sum = %d \n", arr[i].sumIandJ);
	}
}
void printList(Item* lst)
{
	Item* temp = lst;
	printf("your list is: \n");
	printf("i --> j --> sum \n");
	while (temp != NULL)
	{
		printf("%d --> ", (temp->three).i);
		printf("%d --> ", (temp->three).j);
		printf("%d --> NULL \n", (temp->three).sumIandJ);
		temp = temp->next;
	}
}
void Ex4()
{
	list* lst1;
	list* oddlist;
	lst1 = inputList();
	printf("before changes the list is:\n");
	printlst(lst1);
	oddlist = createList(&lst1);
	printf("after changes the list is:\n");
	printlst(lst1);
	printf("the odd list is:\n");
	printlst(oddlist);

}

list* insertTolist(list* lst, list* pos)
{
	list* pos1 = (list*)malloc(sizeof(list));
	pos1->data = pos->data;
	pos1->next = NULL;
	if (lst == NULL)
	{
		return pos1;
	}
	list* temp = lst;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = pos1;
	return lst;
}

list* inputList()
{
	list* lst = NULL;
	list* currPos;
	int num;
	printf("enter please numbers until -1 \n");
	scanf("%d", &num);
	if (num == -1)
	{
		printf("their is no list");
		return lst;
	}
	else
	{
		lst = (list*)malloc(sizeof(list));
		currPos = lst;
		currPos->data = num;
	}
	while (num != -1)
	{
		scanf("%d", &num);
		if (num == -1)
		{
			break;
		}
		currPos->next = (list*)malloc(sizeof(list));
		currPos = currPos->next;
		currPos->data = num;
	}
	currPos->next = NULL;
	return lst;
}

void printlst(list* lst)
{
	list* temp = lst;
	while (temp != NULL)
	{
		printf("%d --> ", temp->data);
		temp = temp->next;
	}
	printf("NULL \n");
}

list* DeleteItem(list* pos)
{
	list *temp = pos->next;
	free(pos);
	return temp;
}

list* createList(list** lst)
{
	list* oddList = NULL;
	list* temp = *lst;
	while (temp->next != NULL)
	{
		if ((temp->next)->data % 2 == 1)
		{
			oddList = insertTolist(oddList, temp->next);
			temp->next = DeleteItem(temp->next);
		}
		if (temp->next != NULL && (temp->next)->data % 2 == 0)
			temp = temp->next;
		if (temp == NULL)
			break;
	}

	if ((*lst)->data % 2 == 1)
	{
		list* posOdd = (list*)malloc(sizeof(list));
		posOdd->data = (*lst)->data;
		posOdd->next = oddList;
		temp = *lst;
		*lst = (*lst)->next;
		free(temp);
		return posOdd;
	}
	else
		return oddList;
}
void Ex5()
{
	list* lst2;
	list* oddlist2;
	lst2 = inputList();
	printf("before changes the list is:\n");
	printlst(lst2);
	oddlist2 = createList2(&lst2);
	printf("after changes the list is:\n");
	printlst(lst2);
	printf("the odd list is:\n");
	printlst(oddlist2);
}
list* createList2(list** lst)
{
	list* oddlist = NULL;
	list* oddtemp = oddlist;
	list* evenlist = NULL;
	list* eventemp = evenlist;
	int flageven=0,flagodd=0;
	while (*lst)
	{

		if ((*lst)->data % 2 == 0)
		{
			if (flageven == 0)
			{
				evenlist = (*lst);
				flageven = 1;
				eventemp= evenlist;
			}
			else
			{
				eventemp->next = (*lst);
				eventemp = eventemp->next;
			}
		}
		else
		{
			if (flagodd == 0)
			{
				oddlist = (*lst);
				flagodd = 1;
				oddtemp = oddlist;
			}
			else
			{
				oddtemp->next = (*lst);
				oddtemp = oddtemp->next;
			}
		}
		(*lst) = (*lst)->next;
	}
	if (eventemp != NULL)
		eventemp->next = NULL;
	(*lst) = evenlist;
	if(oddtemp!=NULL)
		oddtemp->next = NULL;
	return oddlist;
}