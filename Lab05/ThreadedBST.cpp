#include "ThreadedBST.h"

///-----------------------------------------------
/// Erases all nodes in the tree
/// 
void ThreadedBST::eraseTreeNodes(BSTNode* node) {
	BSTNode* curr = this->min();

	while (curr != NULL) {
		BSTNode* n = this->next(curr);
		delete curr;
		curr = n;
	} // end-while

} //end-eraseTreeNodes

///-----------------------------------------------
/// Adds a given key to the BST
/// 
void ThreadedBST::add(int key) {
	BSTNode* newNode = new BSTNode(key);
	BSTNode* temp = root;
	if (root == NULL) {
		root = newNode;
		return;
	}

	while (1) {
		if (temp->key == key) {
			return;
		}
		else if (temp->key > key) {
			if (temp->leftLinkType == CHILD) {
				temp = temp->left;
			}
			else {
				temp->leftLinkType = CHILD;
				newNode->left = temp->left;
				newNode->right = temp;
				temp->left = newNode;
				break;
			}
		}
		else if (temp->key < key) {
			if (temp->rightLinkType == CHILD) {
				temp = temp->right;
			}
			else {
				temp->rightLinkType = CHILD;
				newNode->right = temp->right;
				newNode->left = temp;
				temp->right = newNode;
				break;
			}
		}
	}

} // end-add

BSTNode* deleteLeaf(BSTNode* root, BSTNode* par, BSTNode* ptr)
{
	// If Node to be deleted is root
	if (par == NULL)
		root = NULL;

	// If Node to be deleted is left
	// of its parent
	else if (ptr == par->left) {
		par->leftLinkType = THREAD;
		par->left = ptr->left;
	}
	else {
		par->rightLinkType = THREAD;
		par->right = ptr->right;
	}

	delete ptr;
	return root;
}

BSTNode* delete1Child(BSTNode* root, BSTNode* par, BSTNode* ptr)
{
	BSTNode* child;
	ThreadedBST bst;

	if (ptr->leftLinkType == CHILD)
		child = ptr->left;

	// Node to be deleted has right child.
	else
		child = ptr->right;

	// Node to be deleted is root Node.
	if (par == NULL)
		root = child;

	// Node is left child of its parent.
	else if (ptr == par->left)
		par->left = child;
	else
		par->right = child;

	// Find successor and predecessor
	BSTNode* s = bst.next(ptr);
	BSTNode* p = bst.previous(ptr);

	// If node has left subtree.
	if (ptr->leftLinkType == CHILD)
		p->right = s;

	// If node has right subtree.
	else {
		if (ptr->rightLinkType == CHILD)
			s->left = p;
	}
	delete ptr;
	return root;
}

BSTNode* delete2Child(BSTNode* root, BSTNode* par, BSTNode* ptr)
{
	BSTNode* parsucc = ptr;
	BSTNode* succ = ptr->right;

	while (succ->leftLinkType == CHILD) {
		parsucc = succ;
		succ = succ->left;
	}

	ptr->key = succ->key;

	if (succ->leftLinkType == THREAD && succ->rightLinkType == THREAD)
		root = deleteLeaf(root, parsucc, succ);
	else
		root = delete1Child(root, parsucc, succ);
	return root;
}
///-----------------------------------------------
/// Removes a given key from the BST (if it exists)
///
void ThreadedBST::remove(int key) {
	// Fill this in
	BSTNode* parent = NULL, * curr = root;
	int found = 0;
	while (curr != NULL) {
		if (key == curr->key) {
			found = 1;
			break;
		}
		parent = curr;
		if (key < curr->key) {
			if (curr->leftLinkType == CHILD)
				curr = curr->left;
			else
				break;
		}
		else {
			if (curr->rightLinkType == CHILD)
				curr = curr->right;
			else
				break;
		}
	}
	if (found == 0)
		return;
	// Two Children
	else if (curr->leftLinkType == CHILD && curr->rightLinkType == CHILD)
		delete2Child(root, parent, curr);

	// Only Left Child
	else if (curr->leftLinkType == CHILD)
		delete1Child(root, parent, curr);

	// Only Right Child
	else if (curr->rightLinkType == CHILD)
		delete1Child(root, parent, curr);

	// No child
	else
		deleteLeaf(root, parent, curr);

} // end-remove

///-----------------------------------------------
/// Searches a given key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::find(int key) {
	BSTNode* node = root;
	while (node->key != key && node != NULL) {
		if ((node->key > key && node->leftLinkType == THREAD) || (node->key < key && node->rightLinkType == THREAD))
			return NULL;
		else if (node->key > key)
			node = node->left;
		else if (node->key < key)
			node = node->right;
	}
	return node;
} // end-find

///-----------------------------------------------
/// Returns the minimum key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::min() {
	BSTNode* node = root;
	if (node == nullptr)
		return nullptr;
	while (node->left) {
		node = node->left;
	}
	return node;
} // end-min

///-----------------------------------------------
/// Returns the maximum key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::max() {
	BSTNode* node = root;
	while (node->right) {
		node = node->right;
	}
	return node;
} // end-max

///-----------------------------------------------
/// Given a valid pointer to a node in ThreadedBST,
/// returns a pointer to the node that contains the inorder predecessor
/// If the inorder predecessor does not exist, returns NULL
/// 
BSTNode* ThreadedBST::previous(BSTNode* node) {
	if (node->leftLinkType == THREAD) {
		return node->left;
	}
	else {
		node = node->left;
		while (node->rightLinkType == CHILD) {
			node = node->right;
		}
		return node;
	}
} // end-previous

///-----------------------------------------------
/// Given a valid pointer to a node in the ThreadedBST,
/// returns a pointer to the node that contains the inorder successor
/// If the inorder successor does not exist, returns NULL
/// 
BSTNode* ThreadedBST::next(BSTNode* node) {
	if (node->rightLinkType == THREAD) {
		return node->right;
	}
	else {
		node = node->right;
		while (node->leftLinkType == CHILD) {
			node = node->left;
		}
		return node;
	}
} // end-next