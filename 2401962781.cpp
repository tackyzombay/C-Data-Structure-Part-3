#include <stdio.h>
#include <stdlib.h>

struct Node{
	int value, height;
	Node *left, *right;
}*temp = NULL;

Node *createNode(int value){
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->value = value;
	newNode->height = 1;
	newNode->left = newNode->right = NULL;
	
	return newNode;
}

int max(int a, int b){
	if(a > b){
		return a;
	}
	else return b;
}

int getHeight(Node *node){
	if(node == NULL){
		return 0;
	}
	else return node->height;
}

int getBalanceFactor(Node *node){
	if(node == NULL){
		return 0;
	}
	return getHeight(node->left) - getHeight(node->right);
}

Node *rightRotate(Node *node){
	Node *curr = node->left;
	Node *right = curr->right;
	
	curr->right = node;
	node->left = right;
	
	node->height = max(getHeight(node->left), getHeight(node->right))+1;
	curr->height = max(getHeight(curr->left), getHeight(curr->right))+1;
	return curr;
}

Node *leftRotate(Node *node){
	Node *curr = node->right;
	Node *left = curr->left;
	
	curr->left = node;
	node->right = left;
	
	node->height = max(getHeight(node->left), getHeight(node->right))+1;
	curr->height = max(getHeight(curr->left), getHeight(curr->right))+1;
	return curr;
}

Node *getPredeccessor(Node *node){
	while(node->right){
		node = node->right;
	}
	return node;
}

Node *insertNode(Node *node, int value){
	if(!node){
		return createNode(value);
	}else if(node->value < value){
		node->right = insertNode(node->right, value);
	}else if(node->value > value){
		node->left = insertNode(node->left, value);
	}else{
		return node;
	}
	int leftHeight = getHeight(node->left);
	int rightHeight = getHeight(node->right);
	
	node->height = max(leftHeight, rightHeight) + 1;
	int balanceFactor = getBalanceFactor(node);
	
	if(balanceFactor > 1 && getBalanceFactor(node->left) >= 0){
		return rightRotate(node);
	}
	
	if(balanceFactor < -1 && getBalanceFactor(node->right) <= 0){
		return leftRotate(node);
	}
	
	if(balanceFactor > 1 && getBalanceFactor(node->left) < 0){
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	
	if(balanceFactor < -1 && getBalanceFactor(node->left) > 0){
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	return node;
}

Node *deleteNode(Node *node, int value){
	if(!node){
		return node;
	}else if(node->value < value){
		node->right = deleteNode(node->right, value);
	}else if(node->value > value){
		node->left = deleteNode(node->left, value);
	}else{
		
		if(node->left == NULL || node->right == NULL){
			Node *curr = NULL;
			if(node->left != NULL){
				curr = node->left;
			}else if (node->right != NULL){
				curr = node->right;
			}
			if (curr == NULL){
				curr = node;
				node = NULL;
				free(node);
			}else{
				node = curr;
				curr = NULL;
				free(curr);
			}
		}
		else{
			Node *predecessor = getPredeccessor(node->left);
			
			node->value = predecessor->value;
			node->left = deleteNode(node->left, predecessor->value);
		}if(node == NULL){
			return node;
		}
		
		int leftHeight = getHeight(node->left);
		int rightHeight = getHeight(node->right);
		
		node->height = max(leftHeight, rightHeight) + 1;
		int balanceFactor = getBalanceFactor(node);
		
		if(balanceFactor > 1 && getBalanceFactor(node->left) >= 0){
		return rightRotate(node);
		}
	
		if(balanceFactor < -1 && getBalanceFactor(node->right) <= 0){
			return leftRotate(node);
		}
	
		if(balanceFactor > 1 && getBalanceFactor(node->left) < 0){
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}
	
		if(balanceFactor < -1 && getBalanceFactor(node->left) > 0){
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}
		return node;
			
	}
}

struct Node* searchData(struct Node* temp, int searchValue){
	if(!temp){
		return NULL;
	}else if(searchValue < temp->value){
		temp->left = searchData(temp->left, searchValue);
	}else if(searchValue > temp->value){
		temp->right = searchData(temp->right, searchValue);
	}
	return temp;
}

void inOrder(Node* curr){
	if(curr!=NULL){
		inOrder(curr->left);
		printf("%d ", curr->value);
		inOrder(curr->right);
	}
}

int main(){
	
	int x;
	char a[100][100];
	char m[100][100];
	
	scanf("%d", &x);
	
	for(int i=0; i<x; i++){
		scanf("[^ ]", a[x]);
		
		if(a[x]=='ADD'){
			scanf("[^\n]", m[x]);
		}else if(a[x]=='DEL-LANG'){
			free(m[x]);
		}else if(a[x]=='SHOW-ALL'){
			inOrder();
		}
		
	}
	
	
	
}
