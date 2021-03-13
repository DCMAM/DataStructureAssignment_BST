/*
 *	created : April 5th 2020
 *	by		: David Christian M. A. M. (2301932172)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int total = 0;

struct node{
	int rating;
	char movie[25];
	struct node *left;
	struct node *right;	
};

struct node *newNode(int x, char n[]){  // create new node
	struct node *currNewNode = (struct node*)malloc(sizeof(struct node));
	currNewNode->rating = x;
	strcpy(currNewNode->movie, n);
	currNewNode->left = NULL;
	currNewNode->right = NULL;
	
	return currNewNode;
}

struct node *insert(struct node *root, int x, char n[]){
	if(root == NULL){ // if node is empty
		return newNode(x, n);
	}	
	int i=0;
	do{
		if(n[i] < root->movie[i]){ // insert to the left of the root
			root->left = insert(root->left, x, n);
			break;
		}
		else if(n[i] > root->movie[i]){ // insert to the right of the root
			root->right = insert(root->right, x, n);
			break;
		}
		i++;
	}while(1);
	total++;
	return root;
}

void printAll(struct node *root){ // print with infix method
	if(root == NULL){
		return;
	}
	printAll(root->left);
	printf("| %-20s %d\n", root->movie, root->rating);

	printAll(root->right);
}

void viewByRating(struct node *root, int rating){
	if(root == NULL){
		return;
	}
	viewByRating(root->left, rating);
	if(root->rating == rating){
		printf("| %-20s %d\n", root->movie, root->rating);
	}
	viewByRating(root->right, rating);
}

bool onTheList(struct node *root, char n[]){
	if(root == NULL){
		return false;
	}
	onTheList(root->left, n);
	if(strcmp(root->movie, n) == 0){
		return true;
	}
	onTheList(root->right, n);
}

struct node *predecessor(struct node *root){
	struct node *curr = root->left;
	while(curr->right != NULL){
		curr = curr->right;
	}
	return curr;
}

struct node *deleteMovie(struct node *root, int x, char n[]){
	if(root == NULL){
		return NULL;
	}
	int i = 0;
	do{
		if(n[i] < root->movie[i] ){ // delete the left value of the root
			root->left = deleteMovie(root->left, x, n);
			break;
		}
		else if(n[i] > root->movie[i]){ // delete the right value of the root
			root->right = deleteMovie(root->right, x, n);
			break;
		}
		else if(strcmp(n, root->movie) == 0){
			// data found
			// case 1 & 2
			if(root->left == NULL || root->right == NULL){
				struct node *temp = NULL;
				if(root->left != NULL){
					temp = root->left;
				}
				else{
					temp = root->right;
				}
				//case 1
				if(temp == NULL){
					temp = root;
					root = NULL;	
				}
				//case 2
				else{
					*root = *temp;
				}
				free(temp);
			}
			// case 3 (has 2 child)
			else{
				// predecessor: greatest node of left sub tree
				struct node *temp = predecessor(root);
				root->rating = temp->rating;
				strcpy(root->movie, temp->movie);
				//delete
				root->left = deleteMovie(root->left, temp->rating, temp->movie);
			}
			break;
		}
		i++;
	} while(1);
	return root;
}

int main(){
	struct node *root = NULL;
	do{
	
		int menu = 0;
		printf(".. Cinema 20-1 ..\n\n");
		printf("1. View All Movies (by Name Ascending)\n");
		printf("2. View Movie by Rating\n");
		printf("3. Add New Movie\n");
		printf("4. Delete Movie\n");
		printf("5. Exit\n");
		printf(".. Choice : ");
		scanf("%d", &menu);
		
		if(menu == 1){
			if(total == 0){
				printf("| Movie Name           Rating\n");
				printf("| -                    -\n");
			}
			else{
				printAll(root);
			}
		}
		else if(menu == 2){
			if(total == 0){
				printf("No Movie\n");
			}
			else{
				int rating = 0;
				do{
					printf("Rating [1..10] : ");
					scanf("%d", &rating);
				}while(rating > 10 || rating < 1);
				viewByRating(root, rating);
			}
		}
		else if(menu == 3){
			char movie[24];
			int rating;
			do{
				printf("MovieName [max 20 char] : ");
				scanf("%s", &movie);
			}while(strlen(movie) > 20);
			do{
				printf("Rating [1..10] : ");
				scanf("%d", &rating);
			}while(rating > 10 || rating < 1);
			root = insert(root, rating, movie);
			total++;
			printf("\nSuccessfully add new movie!\n");
		}
		else if(menu == 4){
			if(total == 0){
				printf("No Movie\n");	
			}
			else{
				printf("| Movie Name           Rating\n");
				char movie[24];
				int rating;
				printAll(root);
				do{
					printf("MovieName [max 20 char] : ");
					scanf("%s", &movie);
				}while( !(onTheList(root, movie)) );
				root = deleteMovie(root, rating, movie);
				printf("successfully delete %s!\n", movie);
				total--;
			}
		}
		else if(menu == 5){
			printf("Thank You!\n");
			free(root);
			break;
		}
		else{
			printf("You should input 1-5\n");
		}
		system("pause");
		system("cls");
	}while(1);
	
	return 0;
}
