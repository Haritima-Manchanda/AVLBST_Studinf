/*
 * BST.cpp
 *
 *  Created on: Nov 2, 2020
 *      Author: Haritima Manchanda
 */

#include <iostream>
#include "BST.hpp"
#include <stdlib.h>
using namespace std;


BST::BST() {
	root = NULL;
}

BST::BST(string sarr[]) {
	root = new TNode(sarr);
}

void BST::printTreeIO() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing In Order:" <<endl;
		printTreeIO(root);
	}
}


void BST::printTreePre() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PreOrder:" <<endl;
		printTreePre(root);
	}
}


void BST::printTreePost() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PostOrder:" <<endl;
		printTreePost(root);
	}
}


void BST::clearTree() {
	if (root == NULL) {
		cout << "Tree already empty" << endl;
	}
	else {
		cout << endl << "Clearing Tree:" << endl;
		clearTree(root);
		root = NULL;
	}
}
void BST::clearTree(TNode *tmp) {
	if (tmp == NULL) {
		return;
	}
	else {
		clearTree(tmp->left);
		clearTree(tmp->right);
		tmp->printNode();
		delete(tmp);
	}
}

bool BST::insert(string sarr[]){

	TNode *newNode = new TNode(sarr);

	if(root == NULL){
		root = newNode;
		setHeight(newNode);
		return true;
	}

	TNode *n = root;
	string l = newNode->student->last;
	string f = newNode->student->first;

	while(n != NULL){

		if(l < n->student->last){
			if(n->left == NULL){
				newNode->parent = n;
				n->left = newNode;
				setHeight(newNode);
				return true;
			}
			n = n->left;
		}

		else if(l > n->student->last){
			if(n->right == NULL){
				newNode->parent = n;
				n->right = newNode;
				setHeight(newNode);
				return true;
			}
			n = n->right;
		}

		else if(l == n->student->last){
			// last name is same. Do comparison by first name.

			if(f < n->student->first){
				if(n->left == NULL){
					newNode->parent = n;
					n->left = newNode;
					setHeight(newNode);
					return true;
				}
				n = n->left;
			}

			else if(f > n->student->first){
				if(n->right == NULL){
					newNode->parent = n;
					n->right = newNode;
					setHeight(newNode);
					return true;
				}
				n = n->right;
			}
			else
				return true;
		}

		else
			return false;
	}

	return false;
}

TNode* BST::find(string l, string f){

	int countCmp = 0;

	if(root == NULL){
		return NULL;
	}

	TNode *n = root;

	while(n != NULL){
		if(l == n->student->last){
			if(f == n->student->first)
				return n;

			else if(f > n->student->first)
				n = n->right;

			else if(f < n->student->first)
				n = n->left;
		}

		else if(l > n->student->last){
			n = n->right;
		}

		else if(l < n->student->last){
			n = n->left;
		}

		countCmp++;
	}

	return NULL;
}



void BST::printTreeIO(TNode *n){

	if(n == NULL){
		return;
	}
	else{
		printTreeIO(n->left);
		n->printNode();
		printTreeIO(n->right);
	}
}

void BST::printTreePre(TNode *n){

	if(n == NULL){
		return;
	}
	else{
		n->printNode();
		printTreePre(n->left);
		printTreePre(n->right);
	}
}

void BST::printTreePost(TNode *n){

	if(n == NULL){
		return;
	}
	else{
		printTreePost(n->left);
		printTreePost(n->right);
		n->printNode();
	}
}

void BST::setHeight(TNode* n){

	if(n == root){
		if(n->left != NULL || n->right != NULL)
			updateHeightRootOneKid(n);
		else
			updateHeightRootNoKids(n);
		return;
	}

	n->height = 1;
	TNode* tmp = n->parent;
	int updatedHeight = 0;
	int max = 0;

	while(n != root){

		if(tmp->left == NULL && tmp->right != NULL){
			max = tmp->right->height;
		}
		else if(tmp->right == NULL && tmp->left != NULL){
			max = tmp->left->height;
		}
		else if(tmp->left->height >= tmp->right->height){
			max = tmp->left->height;
		}
		else if(tmp->right->height > tmp->left->height){
			max = tmp->right->height;
		}
		updatedHeight = max + 1;

		if(tmp->height != updatedHeight){
			tmp->height = updatedHeight;

			// Call the appropriate rotation methods based on the balance of the node

			if (getBalance(tmp) < -1 && getBalance(tmp->right) == -1){
				// Left Rotation
				TNode* node = rotateLeft(tmp);
				n = tmp;
				tmp = node;
			}

			else if (getBalance(tmp) > 1 && getBalance(tmp->left) == 1){
				// Right Rotation
				TNode* node = rotateRight(tmp);
				n = tmp;
				tmp = node;
			}

			else if (getBalance(tmp) < -1 && getBalance(tmp->right) == 1){
				// RL rotation
				rotateRight(tmp->right);
				tmp = rotateLeft(tmp);
			}

			else if(getBalance(tmp) > 1 && getBalance(tmp->left) == -1){
				// LR rotation
				rotateLeft(tmp->left);
				tmp = rotateRight(tmp);
			}

			else{
				n = n->parent;
				tmp = tmp->parent;
			}
		}
		else
			return;
	}
}

void BST::updateHeightRootNoKids(TNode *temp){

	int updatedHeight = 0;
	int max = 0;

	while(temp != root){
		if(temp->left == NULL && temp->right == NULL){
			temp->height = 1;
			updatedHeight = 1;
		}
		else if(temp->left == NULL && temp->right != NULL){
			max = temp->right->height;
			updatedHeight = max + 1;
		}
		else if(temp->left != NULL && temp->right == NULL){
			max = temp->left->height;
			updatedHeight = max + 1;
		}

		temp->height = updatedHeight;

		if (getBalance(temp) < -1 && getBalance(temp->right) == -1){
			TNode* node = rotateLeft(temp);
			temp = node;
		}

		else if (getBalance(temp) > 1 && getBalance(temp->left) == 1){
			TNode* node = rotateRight(temp);
			temp = node;
		}

		else if (getBalance(temp) < -1 && getBalance(temp->right) == 1){
			rotateRight(temp->right);
			temp = rotateLeft(temp);
		}

		else if(getBalance(temp) > 1 && getBalance(temp->left) == -1){
			rotateLeft(temp->left);
			temp = rotateRight(temp);
		}
		else
			temp = temp->parent;
	}
}

void BST::updateHeightRootOneKid(TNode* n){
	int updatedHeight = 0;
	int max = 0;

	while(n != NULL){
		if(n->left == NULL && n->right != NULL){
			max = n->right->height;
		}
		else if(n->right == NULL && n->left != NULL){
			max = n->left->height;
		}
		else if(n->left->height >= n->right->height){
			max = n->left->height;
		}
		else if(n->right->height > n->left->height){
			max = n->right->height;
		}

		updatedHeight = max + 1;

		n->height = updatedHeight;

		if (getBalance(n) < -1 && getBalance(n->right) == -1){
			TNode* node = rotateLeft(n);
			n = node;
		}

		else if (getBalance(n) > 1 && getBalance(n->left) == 1){
			TNode* node = rotateRight(n);
			n = node;
		}

		else if (getBalance(n) < -1 && getBalance(n->right) == 1){
			rotateRight(n->right);
			n = rotateLeft(n);
		}

		else if(getBalance(n) > 1 && getBalance(n->left) == -1){
			rotateLeft(n->left);
			n = rotateRight(n);
		}
		else
			n = n->parent;
	}
}

int BST::getBalance(TNode* tmp){

	if(tmp == NULL || (tmp->left == NULL && tmp->right == NULL)){
		return 0;
	}

	if(tmp->left == NULL && tmp->right != NULL){
		return (-1 * tmp->right->height);
	}

	else if(tmp->right == NULL && tmp->left != NULL){
		return (tmp->left->height);
	}

	return (tmp->left->height - tmp->right->height);
}

TNode* BST::rotateLeft(TNode* tmp){

	TNode* tmp2 = tmp->right;

	//Perform rotations
	tmp->right = tmp2->left;

	if(tmp2->left != NULL)
		tmp2->left->parent = tmp;

	tmp2->left = tmp;

	if(tmp == root){
		root = tmp2;
		tmp2->parent = NULL;
		tmp->parent = tmp2;
	}

	else{
		if(tmp->parent->left == tmp)
			tmp->parent->left = tmp2;

		else if(tmp->parent->right == tmp)
			tmp->parent->right = tmp2;

		tmp2->parent = tmp->parent;
		tmp->parent = tmp2;
	}

	// Update Heights
	if(tmp->left == NULL && tmp->right == NULL)
		tmp->height = 1;

	else if(tmp->left == NULL && tmp->right != NULL)
		tmp->height = tmp->right->height + 1;

	else if(tmp->right == NULL && tmp->left != NULL)
		tmp->height = tmp->left->height + 1;

	else{
		if(tmp->left->height > tmp->right->height){
			tmp->height = tmp->left->height + 1;
		}
		else{
			tmp->height = tmp->right->height + 1;
		}
	}

	if(tmp2->left == NULL && tmp2->right == NULL)
		tmp2->height = 1;

	else if(tmp2->left == NULL && tmp2->right != NULL)
		tmp2->height = tmp2->right->height + 1;

	else if(tmp2->right == NULL && tmp2->left != NULL)
		tmp2->height = tmp2->left->height + 1;

	else{
		if(tmp2->left->height > tmp2->right->height){
			tmp2->height = tmp2->left->height + 1;
		}
		else{
			tmp2->height = tmp2->right->height + 1;
		}
	}

	return tmp2;
}

TNode* BST::rotateRight(TNode* tmp){

	TNode* tmp2 = tmp->left;

	tmp->left = tmp2->right;
	if(tmp2->right != NULL){
		tmp2->right->parent = tmp;
	}
	tmp2->right = tmp;

	if(tmp == root){
		root = tmp2;
		tmp2->parent = NULL;
		tmp->parent = tmp2;
	}

	else{
		if(tmp->parent->left == tmp)
			tmp->parent->left = tmp2;

		else if(tmp->parent->right == tmp)
			tmp->parent->right = tmp2;

		tmp2->parent = tmp->parent;
		tmp->parent = tmp2;
	}

	// Update Heights
	if(tmp->left == NULL && tmp->right == NULL)
		tmp->height = 1;

	else if(tmp->left == NULL && tmp->right != NULL)
		tmp->height = tmp->right->height + 1;

	else if(tmp->right == NULL && tmp->left != NULL)
		tmp->height = tmp->left->height + 1;

	else{
		if(tmp->left->height > tmp->right->height){
			tmp->height = tmp->left->height + 1;
		}
		else{
			tmp->height = tmp->right->height + 1;
		}
	}

	if(tmp2->left == NULL && tmp2->right == NULL)
		tmp2->height = 1;

	else if(tmp2->left == NULL && tmp2->right != NULL)
		tmp2->height = tmp2->right->height + 1;

	else if(tmp2->right == NULL && tmp2->left != NULL)
		tmp2->height = tmp2->left->height + 1;

	else{
		if(tmp2->left->height > tmp2->right->height){
			tmp2->height = tmp2->left->height + 1;
		}
		else{
			tmp2->height = tmp2->right->height + 1;
		}
	}
	return tmp2;
}

TNode* BST::remove(string l, string f){
	cout<<"Entering remove"<<endl;
	if(root == NULL){
		return NULL;
	}

	cout<<"Not a root. Going into while"<<endl;
	TNode* n = root;

	while(n != NULL){
		if(l == n->student->last && f == n->student->first){ //data to be removed is found

			// 3 Cases: Node to be removed has 0, 1 or 2 children

			// Case 1: No child
			if(n->left == NULL && n->right == NULL){
				cout<<"NO CHILD CASE"<<endl;
				TNode* deletedNode = removeNoKids(n);
				return deletedNode;
			}

			// Case 2: 1 child
			else if(n->left == NULL && n->right != NULL){
				// It has a right child
				cout<<"1 child case - RIGHT CHILD"<<endl;
				TNode* deletedNode = removeOneKid(n, false);
				return deletedNode;
			}
			else if(n->left != NULL && n->right == NULL){
				// It has a left child
				cout<<"1 child case - LEFT CHILD"<<endl;
				TNode* deletedNode = removeOneKid(n, true);
				return deletedNode;
			}

			// Case 3: It has 2 children
			else if(n->left != NULL && n->right != NULL){

				TNode *temp = rightMostLeftTree(n->left);	// Helper function to find the rightmost of the left sub-tree.
				TNode* deletedNode = new TNode();
				deletedNode->student->last = n->student->last;		// Replaces the node's data with temp's data
				deletedNode->student->first = n->student->first;
				deletedNode->student->ate = n->student->ate;
				deletedNode->student->dessert = n->student->dessert;
				deletedNode->student->invent = n->student->dessert;
				deletedNode->student->strange = n->student->strange;
				deletedNode->student->numstuff = n->student->numstuff;

				n->student->last = temp->student->last;		// Replaces the node's data with temp's data
				n->student->first = temp->student->first;
				n->student->ate = temp->student->ate;
				n->student->dessert = temp->student->dessert;
				n->student->invent = temp->student->dessert;
				n->student->strange = temp->student->strange;
				n->student->numstuff = temp->student->numstuff;

				if(temp->left == NULL && temp->right == NULL){
					removeNoKids(temp);
					cout<<"Removing No Kids"<<endl;
					return deletedNode;
				}
				else if(temp->left == NULL && temp->right != NULL){
					// It has a right child
					cout<<"Removing, No left Child"<<endl;
					removeOneKid(temp, false);
					return deletedNode;
				}
				else if(temp->left != NULL && temp->right == NULL){
					// It has a left child
					cout<<"Removing No Right Child"<<endl;
					removeOneKid(temp, true);
					cout<<"Returning deleted Node"<<endl;
					return deletedNode;
				}
			}
		}

		else if(l > n->student->last){
			n = n->right;
		}

		else if(l < n->student->first){
			n = n->left;
		}

		else if(f != n->student->first){

			if(f < n->student->first)
				n = n->left;

			else if(f > n->student->first)
				n = n->right;
		}
	}
	cout<<"End of remove"<<endl;
	return NULL;
}

TNode* BST::removeNoKids(TNode *tmp){

	// setting the parent's left or right field to NULL, depending on where tmp is present (left or right).

	if(tmp->parent->left == tmp){
		tmp->parent->left = NULL;
		if(tmp->parent->right == NULL)
			setHeight(tmp->parent);
		else
			updateHeightRootNoKids(tmp->parent);
		tmp->parent = NULL;
	}
	else if(tmp->parent->right == tmp){
		tmp->parent->right = NULL;
		if(tmp->parent->left == NULL)
			setHeight(tmp->parent);
		else
			updateHeightRootNoKids(tmp->parent);
		tmp->parent = NULL;
	}

	return tmp;
}

TNode* BST::removeOneKid(TNode *tmp, bool leftFlag){
	cout<<"Entering Remove One Kid"<<endl;
	if(leftFlag){
		tmp->left->parent = tmp->parent;

		if(tmp->parent->left == tmp){
			tmp->parent->left = tmp->left;
			setHeight(tmp->parent->left);
		}
		else{
			tmp->parent->right = tmp->left;
			setHeight(tmp->parent->right);
		}
	}

	if(!leftFlag){
		tmp->right->parent = tmp->parent;

		if(tmp->parent->left == tmp){
			tmp->parent->left = tmp->right;
			setHeight(tmp->parent->left);
		}
		else{
			tmp->parent->right = tmp->right;
			setHeight(tmp->parent->right);
		}
	}

	tmp->left = tmp->right = tmp->parent = NULL;

	cout<<"Exiting Remove One Kid"<<endl;
	return tmp;
}

TNode* BST::rightMostLeftTree(TNode* temp){
	// This function finds the rightmost node of the left sub-tree

	while(temp->right != NULL){
		temp = temp->right;
	}

	return temp;
}

