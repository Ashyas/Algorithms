/* Assignment: 4
Campus: Beer Sheva
Author: Asher Yasia, ID: 310273370
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct Tree
{
	int Key;
	struct Tree* Parent;
	struct Tree* Left;
	struct Tree* Right;
	int hight;
	int balance;
}Tree;

Tree* Node_Maker();                    // functions declariation
void Insert(struct Tree* Node, int key);
Tree* Remove_Key(struct Tree* Root, int key);
void Preorder(struct Tree* Node);
void Inorder(struct Tree* Node);
void Postorder(struct Tree* Node);
void Levelorder(struct Tree* Node);
Tree* Find_Node(struct Tree* Node, int key);
Tree* Find_Max(struct Tree* Node);
Tree* Find_Min(struct Tree* Node);
Tree* BST_Successor(struct Tree* Node);
int Height(struct Tree* Node);
void Print_Level(struct Tree* Root, int height);
void Convert_Preorder_Dubly_Link_List(struct Tree *leaf, struct Tree *root);
int Get_Balance(struct Tree* Node);
Tree* Left_Rotatation(struct Tree* Node);
Tree* Right_Rotation(struct Tree* Node);
void Arrange_AVL_Balance(struct Tree* Root);
void Print_Balance(struct Tree* Node);

int main()
{
	Tree* node = NULL, *p = NULL, *w = NULL, *temp = NULL;
	int choise = 0, sos = 0, flag = 0, num ,i, r;
	;
	while (choise != 14)                //switch for menue
	{
		printf("1. Load AVL\n2. Insert New Node\n3. Delete Node\n4. Print Levelorder\n");
		printf("5. Print Preorder\n6. Print Inorder\n7. Print Postorder\n8. AVL-Search Key\n");
		printf("9. Print Tree-Minimum\n10. Print Tree-Maximum\n11. Print Tree-Successor by Key\n");
		printf("12. Convert to Preorder Doubly Linked List\n13. Print Balance\n14. Exit\n");
		scanf("%d", &choise);
		switch (choise)
		{
		case 1:
			node = Node_Maker();   //defalult values for the first initialaized
			printf("Enter the number of the Tree\t");
			scanf("%d", &num);
			for (i = 0; i < num; i++) {
				r = rand() % 99;
				Insert(node, r);
			}
			/*Insert(node, 11);
			Insert(node, 6);
			Insert(node, 19);
			Insert(node, 4);
			Insert(node, 8);
			Insert(node, 5);
			Insert(node, 10);
			Insert(node, 17);
			Insert(node, 43);
			Insert(node, 31);
			Insert(node, 49);*/
			printf("The Tree has been loaded\n");
			flag = 1;
			break;
		case 2:
			if (flag) {
				printf("Insert a Node\t");
				scanf("%d", &sos);
				Insert(node, sos);
				printf("The node has been inserted\n");

			}
			else
				printf("\n You must laod the tree first!\n");
			break;
		case 3:
			if (flag) {
				printf("Pick a Node to Remove\t");
				scanf("%d", &sos);
				Remove_Key(node, sos);
				printf("The node has been removed\n");
			}
			else
				printf("\n You must laod the tree first!\n");
			break;
		case 4:
			if (flag) {
				printf("Level-Order\n");
				Levelorder(node);
				printf("\n");
			}
			else
				printf("\n You must laod the tree first!\n");
			break;
		case 5:
			if (flag) {
				printf("Pre-Order\n");
				Preorder(node);
				printf("\n");
			}
			else
				printf("\n You must laod the tree first!\n");
			break;
		case 6:
			if (flag) {
				printf("In-Order\n");
				Inorder(node);
				printf("\n");
			}
			else
				printf("\n You must laod the tree first!\n");
			break;
		case 7:
			if (flag) {
				printf("Post-Order\n");
				Postorder(node);
				printf("\n");
			}
			else
				printf("\n You must laod the tree first!\n");
			break;
		case 8:
			if (flag) {
				printf("Pick a Node to Find\t");
				scanf("%d", &sos);
				p = Find_Node(node, sos);
				printf("Your Key is: %d\n", p->Key);
			}
			else
				printf("\n You must laod the tree first!\n");
			break;
		case 9:
			if (flag) {
				p = Find_Min(node);
				printf("The Minimum Node is: %d\n", p->Key);
			}
			else
				printf("\n You must laod the tree first!\n");
			break;
		case 10:
			if (flag) {
				p = Find_Max(node);
				printf("The Maximum Node is: %d\n", p->Key);
			}
			else
				printf("\n You must laod the tree first!\n");
			break;
		case 11:
			if (flag) {
				printf("Choose a Node\t");
				scanf("%d", &sos);
				p = Find_Node(node, sos);  //call for asistance function
				w = BST_Successor(p);
				printf("The Successor is: %d\n", w->Key);
			}
			else
				printf("\n You must laod the tree first!\n");
			break;
		case 12:
			if (flag) {
				Convert_Preorder_Dubly_Link_List(node, node);
			}
			else
				printf("\n You must laod the tree first!\n");
			break;
		case 13:
			if (flag) {
				printf("Print Node Balance:\n");
				Print_Balance(node);
				printf("\n");
			}
			else
				printf("\n You must laod the tree first!\n");
			break;
		case 14:
			printf("\nBye Bye!!\n\n");
			break;
		default:
			printf("Worong Key, Try Again!!\n");
			break;
		}
		printf("\n");
	}
	return 0;
}

Tree* Node_Maker()
{
	Tree* Node = (Tree*)malloc(sizeof(Tree));  //allocating new memory to the node
	if (Node == NULL)
	{
		printf("EROR!!, not enough memory\n"); //in case of not enough memory
		return 0;
	}
	Node->Left = NULL;  //intialiazing each field to null
	Node->Right = NULL;
	Node->Parent = NULL;
	Node->Key = 0;
	Node->hight = 1;
	Node->balance = 0;
	return Node;  //returns empty node pointer
}
void Insert(struct Tree* Node, int key)  //inserrt function //you gotta fix the bug when inserting nodes randomly
{
	Tree* temp = NULL;
	Tree * help = Node;
	while (help->Key != NULL)   //a loop to find the finest location to insert the leaf
	{
		temp = help;
		if (help->Left == NULL || help->Right == NULL)
			break;
		if (key < help->Key)  //checks if the key is higer or lower then its sons inorder to find the correct sub-tree
			help = help->Left;
		else
			help = help->Right;
	}
	if (temp == NULL)  //if is the first insertion
	{
		help->Key = key;
		return;
	}

	else if (temp->Right != NULL && temp->Left == NULL)  //if is not the first time, create a new node and initialize it
	{
		temp = temp->Right;
		Tree* leaf = Node_Maker();
		leaf->Key = key;

		if (key > temp->Key)
		{
			temp->Right = leaf;
			leaf->Parent = temp;
		}
		else if (key<temp->Key&&key>temp->Parent->Key)
		{
			temp->Left = leaf;
			leaf->Parent = temp;
		}
		else
		{
			temp = temp->Parent;
			temp->Left = leaf;
			leaf->Parent = temp;
		}
	}
	else
	{
		Tree* leaf = Node_Maker();
		leaf->Key = key;
		leaf->Parent = temp;
		if (key < help->Key)
			temp->Left = leaf;
		else
			temp->Right = leaf;
		while (leaf->Parent != NULL)
		{
			leaf->Parent->hight += 1;
			leaf = leaf->Parent;
			leaf->balance = Get_Balance(leaf);
		}

		temp = help;
	}
	Arrange_AVL_Balance(temp);

}
Tree* Remove_Key(struct Tree* Root, int key)  //removing function
{
	Tree *temp = NULL, *help = NULL;
	Tree* Target = Find_Node(Root, key);  //creating a new node for the key, inorder to finde its location in the tree
	if (Target->Left == NULL || Target->Right == NULL)  //in case the key has no sons
		temp = Target;
	else
		temp = BST_Successor(Target);  //else calling to the next-item function (successor)
	if (temp->Left != NULL)
		help = temp->Left;
	else
		help = temp->Right;
	if (help != NULL)
		help->Parent = temp->Parent;
	if (temp->Parent == NULL)
		Root = help;
	else if (temp->Key == temp->Parent->Left->Key)
		temp->Parent->Left = help;
	else
		temp->Parent->Right = help;
	if (temp->Key != Target->Key)
		Target->Key = temp->Key;
	free(temp);  //free memory
	Arrange_AVL_Balance(help);
	/*if (Height(Target->Left) > Height(Target->Right))
		Target->hight = Height(Target->Left) + 1;
	else
		Target->hight = Height(Target->Right) + 1;

	Target->balance = Get_Balance(Target);

	if (Target->balance > 1 && Get_Balance(Target->Left) >= 0)
		return Right_Rotation(Target);

	// Left Right Case
	if (Target->balance > 1 && Get_Balance(Target->Right) < 0)
	{
		Target->Left = Left_Rotatation(Target->Left);
		return Right_Rotation(Target);
	}

	// Right Right Case
	if (Target->balance < -1 && Get_Balance(Target->Right) <= 0)
		return Left_Rotatation(Target);

	// Right Left Case
	if (Target->balance < -1 && Get_Balance(Target->Right) > 0)
	{
		Target->Right = Right_Rotation(Target->Right);
		return Left_Rotatation(Target);
	}*/

	//return Target;
}
void Preorder(struct Tree* Node)  //recursive function to print: root,left and then right sub tree
{
	if (Node != NULL)
	{
		printf("%d ", Node->Key);
		Preorder(Node->Left);
		Preorder(Node->Right);
	}

}
void Inorder(struct Tree* Node)   //recursive function to print: left,root and then right sub tree
{
	if (Node != NULL)
	{

		Inorder(Node->Left);
		printf("%d ", Node->Key);
		Inorder(Node->Right);
	}
}
void Postorder(struct Tree* Node)  //recursive function to print
{
	if (Node != NULL)
	{

		Postorder(Node->Left);
		Postorder(Node->Right);
		printf("%d ", Node->Key);

	}
}
void Levelorder(struct Tree* Root)  //recursive function to print leafs by thier hight
{
	int h = Height(Root);
	int i;
	for (i = 1; i <= h; i++)
		Print_Level(Root, i);
	printf("\n");
}
Tree* Find_Node(struct Tree* Node, int key)  //a function to get a spesific node by its key
{
	Tree *temp = Node;
	while (temp != NULL)
	{
		if (key == temp->Key)
			return temp;
		else if (key > temp->Key)
			temp = temp->Right;
		else
			temp = temp->Left;
	}
	printf("Not Found\n");
	return;
}
Tree* Find_Max(struct Tree* Node)  //function to print the max value in the whole tree
{
	if (Node == NULL)
		return Node;
	Tree* temp = Node;
	while (temp->Right != NULL)
		temp = temp->Right;
	return temp;

}
Tree* Find_Min(struct Tree* Node)  //function to print the min value in the whole tree
{
	if (Node == NULL)
		return Node;
	Tree* temp = Node;
	while (temp->Left != NULL)
		temp = temp->Left;
	return temp;
}
Tree* BST_Successor(struct Tree* Node)  //function to get succsessor of a spesific node
{
	if (Node->Right != NULL)
		return Find_Min(Node->Right);
	Tree* temp = Node->Parent;
	while (temp != NULL && Node == temp->Right)
	{
		Node = temp;
		temp = Node->Parent;
	}
	return temp;
}
void Print_Level(struct Tree* Root, int height)  //a recursive additional function to help to print the level order
{
	if (Root == NULL)
		return;
	if (height == 1)
		printf("%d ", Root->Key);
	else if (height > 1)
	{
		Print_Level(Root->Left, height - 1);
		Print_Level(Root->Right, height - 1);
	}
}
int Height(struct Tree* Node)  //a recursive additional function to help to print the level order
{
	// returns the height of a node
	if (Node == NULL)
		return 0;
	else
	{
		int left, right;
		left = Height(Node->Left);
		right = Height(Node->Right);

		if (left > right)
			return (left + 1);
		else
			return (right + 1);
	}
}
int Get_Balance(struct Tree* Node)
{
	//return the height of the left sub tree minus the right sub tree ( balance)
	if (Node == NULL)
		return 0;
	return Height(Node->Left) - Height(Node->Right);
}
Tree* Right_Rotation(struct Tree* Node)
{
	//// Perform a single right rotation
	Tree* N_L = Node;
	Node = Node->Parent;
	N_L->Parent = Node->Parent;
	Tree* temp = N_L->Parent;
	temp->Left = N_L;

	N_L->Right = Node;
	Node->Parent = N_L;
	Node->Left = NULL;

	// Update heights
	if (Height(Node->Left) > Height(Node->Right))
		Node->hight = Height(Node->Left) + 1;
	else
		Node->hight = Height(Node->Right) + 1;

	if (Height(N_L->Left) > Height(N_L->Right))
		N_L->hight = Height(N_L->Left) + 1;
	else
		N_L->hight = Height(N_L->Right) + 1;
	// Return new root
	return N_L;
}
Tree* Left_Rotatation(struct Tree* Node)
{
	// Perform a single left rotation
	Tree* N_R = Node;
	Node = Node->Parent;
	N_R->Parent = Node->Parent;
	Tree* temp = N_R->Parent;

	temp->Right = N_R;
	N_R->Left = Node;
	Node->Parent = N_R;
	Node->Right = NULL;

	//  Update heights
	if (Height(Node->Left) > Height(Node->Right))
		Node->hight = Height(Node->Left) + 1;
	else
		Node->hight = Height(Node->Right) + 1;

	if (Height(N_R->Left) > Height(N_R->Right))
		N_R->hight = Height(N_R->Left) + 1;
	else
		N_R->hight = Height(N_R->Right) + 1;
	// Return new root
	return N_R;
}
void Arrange_AVL_Balance(struct Tree* Root)
{
	/* checkes the balance factor and sends the tree to rotation functions when the balance is valied  */

	if (Root == NULL)
		return;
	Tree* temp = Root;

	temp->balance = Get_Balance(temp->Parent);

	// Left Left Case
	if (temp->balance > 1 && Get_Balance(temp->Left) >= 0)
		temp = Right_Rotation(temp);

	// Left Right Case
	if (temp->balance > 1 && Get_Balance(temp->Right) < 0)
	{
		temp->Left = Left_Rotatation(temp->Left);
		temp = Right_Rotation(temp);
	}

	// Right Right Case
	if (temp->balance < -1 && Get_Balance(temp->Right) <= 0)
		temp = Left_Rotatation(temp);

	// Right Left Case
	if (temp->balance < -1 && Get_Balance(temp->Right) > 0)
	{
		temp->Right = Right_Rotation(temp->Right);
		temp = Left_Rotatation(temp);
	}

}
void Convert_Preorder_Dubly_Link_List(struct Tree *leaf, struct Tree *root)
{
	/*
	* connect the right pointer of the maximum node in the left sub tree to the leaf's right node.
	* All the right pointers points to the next node according to the preorder display of the Tree.
	*/
	if (leaf == root)
		leaf = leaf->Left;
	Tree* Max_Node = NULL, *temp;
	if (leaf != NULL)
	{
		if (leaf->Right == NULL)
			Max_Node = leaf;
		else
			while (leaf != NULL)
			{
				if (leaf->Right == NULL)
				{
					Max_Node = leaf;
					leaf = leaf->Right;
				}
				else
					leaf = leaf->Right;
			}
	}
	leaf = root;
	Max_Node->Right = root->Right;
	root->Right = root->Left;
	root->Left = NULL;
	temp = root;
	while (temp != NULL)
	{
		leaf = temp;
		if (leaf->Left == NULL)
		{

			temp = temp->Right;
		}
		else
		{
			leaf = leaf->Left;
			while (leaf != NULL)
			{
				if (leaf->Right == NULL)
				{
					Max_Node = leaf;
					leaf = leaf->Right;
				}
				else
					leaf = leaf->Right;
			}

			Max_Node->Right = temp->Right;
			temp->Right = temp->Left;
			temp->Left = NULL;
			temp = temp->Right;
		}

	}

	temp = root;
	leaf = root->Right;
	while (leaf != NULL)
	{
		leaf->Left = temp;
		leaf = leaf->Right;
		temp = temp->Right;
	}
	leaf = root;
	while (leaf != NULL)
	{
		printf("The Key is: %d ", leaf->Key);
		if (leaf->Left != NULL)
			printf("Left Child is: %d ", leaf->Left->Key);
		else
			printf("There is No Left Child.\n");
		if (leaf->Right != NULL)
			printf("Right Child is: %d \n", leaf->Right->Key);
		else
			printf("There is No Right child.\n");
		leaf = leaf->Right;
	}


}
void Print_Balance(struct Tree* Node)
{
	// prints the node's key and its balance factor in inorder order
	if (Node != NULL)
	{

		Print_Balance(Node->Left);
		printf("Key: [ %d ], Balance Factor: [ %d ]\n ", Node->Key, Get_Balance(Node));
		Print_Balance(Node->Right);
	}
}