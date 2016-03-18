#include "rbtree.h"
#include <cstddef>
#include <iostream>
#include <math.h>



Treenode::Treenode(int id,int count){
	m_id = id;
	m_count = count;
	right=left=parent=NULL;
	m_color = RED; //Default color given to a node is red.
}

/* A utility function to print preorder traversal of BST */
void RBTree::inOrderUtil(Treenode* root)
{
    if (root == NULL)
        return;
    inOrderUtil(root->left);
    	std::cout<<root->m_id<<" "<<root->m_count<<" Color="<<root->m_color<<std::endl;
    inOrderUtil(root->right);
}

void RBTree::inOrder(){
	std::cout<<"Inorder Traversal"<<std::endl;
	inOrderUtil(m_root);
}

/* A function that constructs Balanced Binary Search Tree from a sorted array */
Treenode* RBTree::sortedVectorToBST(std::vector<Treenode>input, int start, int end)
{
    /* Base Case */
    if (start > end)
      return NULL;

    /* Get the middle element and make it root */
    int mid = start + (end - start) / 2;
    Treenode *root = new Treenode(input[mid].m_id,input[mid].m_count);
    root->left =  sortedVectorToBST(input, start, mid-1);
    if(root->left)
    	root->left->parent = root;
    root->right = sortedVectorToBST(input, mid+1, end);
    if(root->right)
    	root->right->parent = root;
    return root;
}

/* A utility teh colors the balanced BST builf from the input file*/
void RBTree::colorTree(Treenode* root, int level, int maxHeight)
{
    if (root == NULL)
        return;
    if(level == maxHeight)
    	root->m_color = RED;
    else
    	root->m_color = BLACK;
  //  std::cout<<root->m_id<<" "<<root->m_count<<" Color="<<root->m_color<<std::endl;
   	colorTree(root->left,level+1,maxHeight);
    colorTree(root->right,level+1,maxHeight);
}
//Constructor
void RBTree::buildTree(std::vector<Treenode> nodes){
	m_root = sortedVectorToBST(nodes,0,nodes.size()-1);// Construct the BBST from the sorted input.
	int numNodes=nodes.size();
	int maxHeight=(int)log2(double(numNodes));

	// Complete Binary Tree. Since any number n if power of two can be cheked by n&(n-1)==0.
	//A complete binary tre has k=n-1 number of nodes wheren is the power ot 2.
	//If it is the case we have already colored all the nodes black and hence we satisfy all
	std::cout<<"NumNodes ="<<numNodes<<std::endl;

	//if((numNodes+1)&(numNodes) != 0){
		colorTree(m_root,0,maxHeight);// Incomplete tree. Color leaf nodes as red
	//}
	std::cout<<"Max Height ="<<maxHeight<<" Tree Building is Finished"<<std::endl;

}
//Default Constructor
RBTree::RBTree(){
	m_root = NULL;
}

void RBTree::deleteTree(Treenode *node){
    if(node != NULL) {
    	deleteTree(node->left);
    	deleteTree(node->right);
    }
    delete node;
}

RBTree::~RBTree(){
	deleteTree(m_root);
}



Treenode* RBTree::grandparent(Treenode *node)
{
	 if ((node != NULL) && (node->parent != NULL))
	  return node->parent->parent;
	 else
	  return NULL;
}

Treenode* RBTree::uncle(Treenode *node)
{
	Treenode *g = grandparent(node);
	if (g == NULL)
		return NULL; // No uncle
	if (node->parent == g->left)
		return g->right;
	else
		return g->left;
}

/*
 * Replace a node
 */
void RBTree::replaceNode(Treenode* oldNode, Treenode* newNode)
{
    if (oldNode->parent == NULL)
    {
        m_root = newNode;
    }
    else
    {
        if (oldNode == oldNode->parent->left)
        	oldNode->parent->left = newNode;
        else
        	oldNode->parent->right = newNode;
    }
    if (newNode != NULL)
    {
    	newNode->parent = oldNode->parent;
    }
}

/*
 * Rotate left
 */
void RBTree::rotateLeft(Treenode* node)
{
    Treenode* rightNode = node->right;
    replaceNode(node, rightNode);
    node->right = rightNode->left;
    if (rightNode->left != NULL)
    {
    	rightNode->left->parent = node;
    }
    rightNode->left = node;
    node->parent = rightNode;
}

/*
 * Rotate right
 */
void RBTree::rotateRight(Treenode* node)
{
	Treenode* leftNode = node->left;
	replaceNode(node, leftNode);
    node->left = leftNode->right;
    if (leftNode->right != NULL)
    {
    	leftNode->right->parent = node;
    }
    leftNode->right = node;
    node->parent = leftNode;
}

/*
 * Case 5: The parent P is red but the uncle U is black, the current node N is the left child of P,
 * and P is the left child of its parent G. In this case, a right rotation on G is performed;Symmetrically
 * in the other direction. Resultant  is a tree where the former parent P is now the parent of both
 *  the current node N and the former grandparent G
 */

void RBTree::insert_case5(Treenode *node)
{
	Treenode *g = grandparent(node);

	node->parent->m_color = BLACK;
	g->m_color = RED;
	if (node == node->parent->left)
		rotateRight(g);
	else
		rotateLeft(g);
}
/*
 * Case 4: The parent P is red but the uncle U is black; also the current node N is the right child of P,
 * and P in turn is the left child of its parent G. In this case, a left rotation on P that switches the
 * roles of the current node N and its parent P can be performed. Similar is the case when left and right
 * and left pointers mentioned above are opposite the case can be handled by totation in oppposite direction.
 * However two consecutive nodes get red color after rotation and they have to be fixed in case 5.
 */
void RBTree::insert_case4(Treenode *node)
{
	Treenode *g = grandparent(node);

	if ((node == node->parent->right) && (node->parent == g->left)) {
		rotateLeft(node->parent);

		node = node->left;
	}
	else if ((node == node->parent->left) && (node->parent == g->right)) {
		rotateRight(node->parent);
		node = node->right;
	}
	insert_case5(node);
}

/*
*Case 3: If both the parent P and the uncle U are red, then both of
*them can be repainted black and the grandparent G becomes
*red. The grandparent G may now violate properties
*(The root is black) (Both children of every red node are black)
*(property 4 possibly being violated since G may have a red parent)
*To fix this, the entire procedure is recursively performed on G from case 1.
*/
void RBTree::insert_case3(Treenode *node)
{
	Treenode *u = uncle(node), *g;

	if ((node != NULL) && (node->m_color == RED)) {
		node->parent->m_color = BLACK;
		u->m_color = BLACK;
		g = grandparent(node);
		g->m_color = RED;
		insert_case1(g);
	}
	else {
		insert_case4(node);
	}
}

/*
 * Case 2: The current node  has a black parent. Their is no
 * violation in this case and all RBT properties are stiefied.
 */
void RBTree::insert_case2(Treenode *node)
{
	if (node->parent->m_color == BLACK)
		return; /* Tree is still valid */
	else
		insert_case3(node);
}

/*
 * Case 1: The current node  is at the root of the tree. In this case,
 * it is repainted black to satisfy property 2 (the root is black).
 */
void RBTree::insert_case1(Treenode *node)
{
	if (node->parent == NULL)
		node->m_color = BLACK;
	else
		insert_case2(node);
}

Treenode* RBTree::sibling(Treenode *node)
{
	if ((node == NULL) || (node->parent == NULL))
		return NULL; // no parent means no sibling
	if (node == node->parent->left)
		return node->parent->right;
	else
		return node->parent->left;
}

/*
 * Returns Maximum node
 */
Treenode* RBTree::maximumNode(Treenode* node)
{
	if(node == NULL)
		return NULL;
    while (node->right != NULL)
    {
    	node = node->right;
    }
    return node;
}


void RBTree::delete_case6(Treenode *node)
{
	Treenode *s = sibling(node);

	s->m_color = node->parent->m_color;
	node->parent->m_color = BLACK;

	if (node == node->parent->left) {
		s->right->m_color = BLACK;
		rotateLeft(node->parent);
	}
	else {
		s->left->m_color = BLACK;
		rotateRight(node->parent);
	}
}

void RBTree::delete_case5(Treenode *node)
	{
	Treenode *s = sibling(node);

	if  (s->m_color == BLACK) { /* this if statement is trivial,
		due to case 2 (even though case 2 changed the sibling to a sibling's child,
		the sibling's child can't be red, since no red parent can have a red child). */
		/* the following statements just force the red to be on the left of the left of the parent,
		or right of the right, so case six will rotate correctly. */
		if ((node == node->parent->left) &&
			(s->right->m_color == BLACK) &&
			(s->left->m_color == RED)) { /* this last test is trivial too due to cases 2-4. */
			s->m_color = RED;
				s->left->m_color = BLACK;
				rotateRight(s);
		}
		else if ((node == node->parent->right) &&
			 (s->left->m_color == BLACK) &&
			 (s->right->m_color == RED)) {/* this last test is trivial too due to cases 2-4. */
				s->m_color = RED;
				s->right->m_color = BLACK;
				rotateLeft(s);
		}
	}
	delete_case6(node);
}

void RBTree::delete_case4(Treenode *node)
{
	Treenode *s = sibling(node);

	if ((node->parent->m_color == RED) &&
	    (s->m_color == BLACK) &&
	    (s->left->m_color == BLACK) &&
	    (s->right->m_color == BLACK)) {
			s->m_color = RED;
			node->parent->m_color = BLACK;
	}
	else
		delete_case5(node);
}
void RBTree::delete_case3(Treenode *node)
{
	Treenode *s = sibling(node);

	if ((node->parent->m_color == BLACK) &&
		(s->m_color == BLACK) &&
	    (s->left->m_color == BLACK) &&
	    (s->right->m_color == BLACK)) {
			s->m_color = RED;
			delete_case1(node->parent);
	}
	else
		delete_case4(node);
}

/*
 * Case 1: N is the new root. In this case, we are done.
*/
void RBTree::delete_case2(Treenode *node)
{
	 Treenode *s = sibling(node);

	 if (s->m_color == RED) {
		 node->parent->m_color = RED;
		 s->m_color = BLACK;
		 if (node == node->parent->left)
			 rotateLeft(node->parent);
		 else
			 rotateRight(node->parent);
	 }
	 delete_case3(node);
}

/*
 * Case 1: N is the new root. In this case, we are done.
 */
void RBTree::delete_case1(Treenode *node)
{
	if (node->parent != NULL)
		delete_case2(node);
}

/*
 * Search for a given ID in the tree. If the ID is present then the value of present is set to true
 * and the pointer to that node is returned. If the ID is not present present is set to false and the
 * pointer of the potential parent is returned.
 */
void RBTree::Increase(int key, int count)
{
	 Treenode* currnode = new Treenode(key, count);
	    if (m_root == NULL)
	    {
	        m_root = currnode;
	        std::cout<<"Inserted Node with ID ="<<key<<" Current Count="<<count<<std::endl;
	    }
	    else
	    {
	        Treenode* temp = m_root;
	        while (1)
	        {
	            if (temp->m_id == key)
	            {
	            	temp->m_count += count;
	                std::cout<<"Increased Node with ID ="<<key<<" found. Current Count="<<count<<std::endl;
	                delete currnode;
	                return;
	            }
	            else if (temp->m_id > key)
	            {
	                if (temp->left == NULL)
	                {
	                	temp->left = currnode;
	                    std::cout<<"Inserted Node with ID ="<<key<<" Current Count="<<count<<std::endl;
	                    break;
	                }
	                else
	                {
	                    temp = temp->left;
	                }
	            }
	            else
	            {
	                if (temp->right == NULL)
	                {
	                    temp->right = currnode;
	                    std::cout<<"Inserted Node with ID ="<<key<<" Current Count="<<count<<std::endl;
	                    break;
	                }
	                else
	                {
	                    temp = temp->right;
	                }
	            }
	        }
	        currnode->parent = temp;
	    }
	    // RBTree Fixup
	    insert_case1(currnode);
}

Treenode* RBTree::searchNode(int key)
{
	 Treenode* temp = m_root;
	    while (temp != NULL)
	    {
	    	std::cout<<"Search Iteration "<<temp->m_id;
	        if (temp->m_id == key)
	        {
	            return temp;
	        }
	        else if (temp->m_id > key)
	        {
	        	std::cout<<" temp=temp->left"<<std::endl;
	            temp = temp->left;
	        }
	        else
	        {
	        	std::cout<<" temp=temp->right"<<std::endl;
	        	temp = temp->right;
	        }
	    }
    return temp;
}

void RBTree::Reduce(int key, int count){

	Treenode* temp=searchNode(key);

	if(temp !=NULL){
		 temp->m_count -= count;
		 if(temp->m_count > 0){
			 std::cout<<"Decreased Node with ID ="<<key<<" Current Count="<<count<<std::endl;
			 return;
	      }
	}
	else{
		 std::cout<<"Node with ID ="<<key<<" is not preset Count = 0"<<std::endl;
		 return;
	}
	std::cout<<"Deleting Node with ID ="<<key<<" Count =0"<<std::endl;

	if (temp->left != NULL && temp->right != NULL)
	{
		Treenode* pred = maximumNode(temp->left);
		temp->m_id   = pred->m_id;
		temp->m_count = pred->m_count;
		temp = pred;
	}

	Treenode *child = temp->right == NULL ? temp->left  : temp->right;

	if (temp->m_color == BLACK)
	{
		temp->m_color = child->m_color;
		delete_case1(temp);
	}
	replaceNode(temp,child);
	delete(temp);
}

int RBTree::Count(int key){
	std::cout<<"FUNCTION COUNT. Key that the user is looking for is "<<key<<std::endl;
	Treenode* temp=searchNode(key);
	if(temp == NULL){
		std::cout<<"temp == NULL. Incorrect ID. Count = 0"<<std::endl;
		return 0;

	}
	std::cout<<" Count of ID "<<key<<" is"<<temp->m_count<<std::endl;
	return temp->m_count;
}



Treenode* RBTree::minimumNode(Treenode* node) {
  Treenode* current = node;
   while (current->left != NULL) {
    current = current->left;
  }
  return current;
}

Treenode* RBTree::inorderSuccessor(Treenode* node)
{
	  if (node == NULL)
	    return NULL;
	  if( node->right != NULL )
	    return minimumNode(node->right);

	 Treenode *p = node->parent;
	  while(p != NULL && node == p->right)
	  {
	     node = p;
	     p = p->parent;
	  }
	  return p;
}

Treenode* RBTree::inorderPredecessor(Treenode* node)
{
	if (node == NULL)
		return NULL;

	if (node->left != NULL)
		return maximumNode(node->left);

	Treenode *p = node->parent;
	while (p != NULL && node == p->left)
	{
		node = p;
		p = p->parent;
	}
	return p;
}


/*void RBTree::inRange(int key1, int key2){
	Treenode* key1node=searchNode(key1);
	Treenode* tempnode = key1node;
	while(tempnode && tempnode->m_id!=key2){
		std::cout<<"InRange Query "<<tempnode->m_id<<std::endl;
		key2node = inorderSuccessor(key2node);
	}
	std::cout<<"InRange Query "<<tempnode->m_id<<std::endl;
	return;
}*/

void RBTree::inRangeUtil(Treenode* temp,int key1, int key2)
{
   /* base case */
   if (m_root == NULL)
      return;

   /* Since the desired o/p is sorted, recurse for left subtree first
      If root->data is greater than k1, then only we can get o/p keys
      in left subtree */
   if ( key1 < temp->m_id)
	   inRangeUtil(temp->left, key1, key2);

   /* if root's data lies in range, then prints root's data */
   if ( key1 <= temp->m_id && key2 >= temp->m_id)
		std::cout<<"InRange Query "<<temp->m_id<<std::endl;

  /* If root->data is smaller than k2, then only we can get o/p keys
      in right subtree */
   if ( key2 > temp->m_id)
	   inRangeUtil(temp->right, key1, key2);
}
void RBTree::inRange(int key1, int key2){
	inRangeUtil(m_root,key1,key2);
}

Treenode* RBTree::Next(int key){
	Treenode* keynode=searchNode(key);
	Treenode* next = inorderSuccessor(keynode);
	if(next != NULL)
		std::cout<<"Next of "<<key<<" is"<<next->m_id<<" With Count ="<<next->m_count<<std::endl;
	else
		std::cout<<"Next of "<<key<<" is 0"<<" With Count =0"<<std::endl;
}

Treenode* RBTree::Previous(int key){
	Treenode* keynode=searchNode(key);
	Treenode* previous = inorderPredecessor(keynode);
	if(previous != NULL)
		std::cout<<"Previous of "<<key<<" is"<<previous->m_id<<" With Count ="<<previous->m_count<<std::endl;
	else
		std::cout<<"Previous of "<<key<<" is 0"<<" With Count =0"<<std::endl;
}



