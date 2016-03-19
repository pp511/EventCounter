#include "rbtree.h"
#include <cstddef>
#include <iostream>
#include <climits>
#include <math.h>

/*
 * Treenode Constructor Definition.
 */
Treenode::Treenode(int id,int count){
	m_id = id;
	m_count = count;
	right=left=parent=NULL;
	m_color = RED; //Default color given to a node is red.
}

/* A utility function to print inorder traversal of BST */
void RBTree::inOrderUtil(Treenode* root)
{
    if (root == m_treeNil)
        return;
    inOrderUtil(root->left);
    	std::cout<<root->m_id<<" "<<root->m_count<<" Color="<<root->m_color<<std::endl;
    inOrderUtil(root->right);
}

/* Inorder traversal of BST */
void RBTree::inOrder(){
	std::cout<<"Inorder Traversal"<<std::endl;
	inOrderUtil(m_root);
}

/* A function that constructs Balanced Binary Search Tree from a sorted array */
Treenode* RBTree::sortedVectorToBST(std::vector<Treenode*>&input, int start, int end)
{
    /* Base Case */
    if (start > end)
      return m_treeNil;

    /* Get the middle element and make it root */
    int mid = start + ((end - start) >> 1);
  //std::cout<<" sortedVectorToBST .Current node index "<<mid<<std::endl;
    Treenode *root = input[mid];

    root->left =  sortedVectorToBST(input, start, mid-1);
    if(root->left)
    	root->left->parent = root;
    root->right = sortedVectorToBST(input, mid+1, end);
    if(root->right)
    	root->right->parent = root;
    return root;
}

/* A utility that colors the balanced BST builf from the input file
 * Tree that is built by sortedVectorToBST is a balanced BST. In order
 * to make sure that black height is same for an imcomplete tree
 * we color the last internal nodes as RED.
 */
void RBTree::colorTree(Treenode* root, int level, int maxHeight)
{
    if (root == NULL || root == m_treeNil)
        return;
    if(level == maxHeight)
    	root->m_color = RED;
    else
    	root->m_color = BLACK;
    std::cout<<root->m_id<<" "<<root->m_count<<" Color="<<root->m_color<<std::endl;
   	colorTree(root->left,level+1,maxHeight);
    colorTree(root->right,level+1,maxHeight);
}
// RBTree Constructor
void RBTree::buildTree(std::vector<Treenode*> &nodes){
	m_root = sortedVectorToBST(nodes,0,nodes.size()-1);// Construct the BBST from the sorted input.
	m_root->parent = m_treeNil;
	int numNodes=nodes.size();
	int maxHeight=(int)log2(double(numNodes));

	//std::cout<<"NumNodes ="<<numNodes<<std::endl;

	colorTree(m_root,0,maxHeight);//  Color leaf nodes as red
	//std::cout<<"Max Height ="<<maxHeight<<" Tree Building is Finished"<<std::endl;

}
//Default RBTree Constructor
RBTree::RBTree(){
	m_root = NULL;
    m_treeNil = new Treenode(INT_MIN,INT_MIN);
    m_treeNil->m_color = BLACK; // NILL node is always kept as black.
    m_treeNil->parent=m_treeNil->left=m_treeNil->right=m_treeNil;
}

void RBTree::deleteTree(Treenode *node){
    if(node != m_treeNil) {
    	deleteTree(node->left);
    	deleteTree(node->right);
    	delete node;
    }

}
/*RBTree Destructor*/
RBTree::~RBTree(){
	deleteTree(m_root);
	delete m_treeNil;
}

/*
 * Return grandparent of aa given node.
 */

Treenode* RBTree::grandparent(Treenode *node)
{
	 if ((node != NULL) && (node->parent != NULL))
	  return node->parent->parent;
	 else
	  return NULL;
}

/*
 * Return Uncle of aa given node.
 */
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
void RBTree::rotateLeft(Treenode* &root, Treenode* &currnode)
{
    Treenode* rightNode = currnode->right;
    currnode->right = rightNode->left;

    if(currnode->right != m_treeNil)
    	currnode->right->parent = currnode;

    rightNode->parent = currnode->parent;

    if(currnode->parent == m_treeNil)
        root = rightNode;
    else if(currnode->parent->left == currnode)
    	currnode->parent->left = rightNode;
    else
    	currnode->parent->right = rightNode;
   rightNode->left = currnode;
   currnode->parent = rightNode;

}

/*
 * Rotate right
 */
void RBTree::rotateRight(Treenode* &root, Treenode* &currnode)
{
    Treenode* leftNode = currnode->left;
    currnode->left = leftNode->right;

    if(currnode->left != m_treeNil)
    	currnode->left->parent = currnode;

    leftNode->parent = currnode->parent;

    if(currnode->parent == m_treeNil)
        root = leftNode;
    else if(currnode->parent->left == currnode)
    	currnode->parent->left = leftNode;
    else
    	currnode->parent->right = leftNode;

    leftNode->right = currnode;
    currnode->parent = leftNode;
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



void RBTree::insertFixup(Treenode* &root, Treenode* &currnode)
{
    while(currnode != root && currnode->parent->m_color == RED) {
        Treenode* p = currnode->parent;
        Treenode* g = grandparent(currnode);
        Treenode* u = uncle(currnode);
        if(g->left == p) // parent is left child
        {
            if(u->m_color == RED)//case 1: CLRS
            {
                g->m_color = RED;
                u->m_color = BLACK;
                p->m_color = BLACK;
                currnode = g;
            }
            else
            {
                if(currnode == p->right) // case 2 :CLRS
                {
                    rotateLeft(root,p);
                    currnode = p;
                    p = currnode->parent;
                }
                p->m_color = BLACK;
                g->m_color = RED;
                rotateRight(root, g);
            }
        }
        else{ // Symmetic case when parent is a right child
            if(u && u->m_color == RED)
            {
                g->m_color = RED;
                u->m_color = BLACK;
                p->m_color = BLACK;
                currnode = g;
            }
            else
            {
                if(currnode == p->left) // case 3 : CLRS
                {
                    rotateRight(root,p);
                    currnode = p;
                    p = currnode->parent;
                }
                p->m_color = BLACK;
                g->m_color = RED;
                rotateLeft(root, g);
            }
        }
    }
    root->m_color = BLACK; // Root shoud alway be black.
    m_root = root;
}


Treenode* RBTree::insertNode(Treenode* root, Treenode* currnode)
{
    if(root == NULL || root == m_treeNil)
        	return currnode;

    if(root->m_id < currnode->m_id){
	   root->right = insertNode(root->right, currnode);
	   root->right->parent = root;
   }
    else if(root->m_id > currnode->m_id){
        root->left = insertNode(root->left,currnode);
        root->left->parent = root;
    }
    else // For genericity.This condition must never reach in out context.
        root->m_count += currnode->m_count;
    return root;
}

/*
 * Search for a given ID in the tree. If the ID is present then the value of present is set to true
 * and the pointer to that node is returned. If the ID is not present present is set to false and the
 * pointer of the potential parent is returned.
 */
void RBTree::Increase(int key, int count)
{
	Treenode* toIncrease = searchNode(key);
    if(toIncrease == NULL){
        //insertNode(key, count);
    	toIncrease = new Treenode(key, count);
    	toIncrease->left=toIncrease->right=m_treeNil;
        m_root = insertNode(m_root,toIncrease);
        m_root->parent = m_treeNil;
        insertFixup(m_root,toIncrease);

        std::cout<<count<<std::endl;
    }
    else{
    	toIncrease->m_count += count;
        std::cout<<toIncrease->m_count<<std::endl;
    }

}

void RBTree::deleteFixup(Treenode* &root,Treenode* &currnode)
{
    while( currnode!= root &&  currnode->m_color == BLACK)
    {
    	Treenode* p = currnode->parent;
    	Treenode* s = NULL;
        if(currnode = p->left)
        {
            s = p->right;
            if(s->m_color == RED) // case 1
            {
                s->m_color = BLACK;
                p->m_color = RED;
                rotateLeft(root,p);
                s = p->right;
            }
            if(s->left->m_color == BLACK && s->right->m_color == BLACK)//case 2
            {
                s->m_color = RED;
                currnode = p;
            }
            else
            {
                if(s->right->m_color == BLACK)//case 3
                s->left->m_color = BLACK;
                s->m_color = RED;
                rotateRight(root,s);
                s = p->right;

            s->m_color = p->m_color;//case 4
            p->m_color = BLACK;
            s->right->m_color = BLACK;
            rotateLeft(root,p);
            currnode = root;
            }
        }
        else // symmetric case if currnodeent is right child of its parent, symmetric to left case
        {
            s = p->left;
            if(s->m_color == RED)
            {
                s->m_color = BLACK;
                p->m_color = RED;
                rotateRight(root,p);
                s = p->left;
            }
            if(s->right->m_color == BLACK && s->left->m_color == BLACK)
            {
                s->m_color = RED;
                currnode = p;
            }
            else
            {
                if(s->left->m_color == BLACK)
                s->right->m_color = BLACK;
                s->m_color = RED;
                rotateLeft(root,s);
                s = p->left;

            s->m_color = p->m_color;
            p->m_color = BLACK;
            s->left->m_color = BLACK;
            rotateRight(root,p);
            currnode = root;
            }
        }
    }
    currnode->m_color = BLACK; // at end set root as black
}

void RBTree::deleteNode(Treenode* &toDelete, Treenode* &root, int key)
{
    if(toDelete == NULL)
    {
        return;
    }
    Treenode* willbeDeleted = NULL;
    if(toDelete->left == m_treeNil || toDelete->right == m_treeNil)
        willbeDeleted = toDelete;
    else
        willbeDeleted = inorderSuccessor(toDelete);
    Treenode* child = willbeDeleted->left == m_treeNil?willbeDeleted->right : willbeDeleted->left;
    child->parent = willbeDeleted->parent;
    if(willbeDeleted->parent == m_treeNil) // node to be deleted is root
        root = child;
    //attach child at appropriate postion
    if(willbeDeleted->parent->left == willbeDeleted)
        willbeDeleted->parent->left = child;
    else
        willbeDeleted->parent->right = child;
   //cout<<"before fixup"<<std::endl;
    if(toDelete != willbeDeleted)
    {
        toDelete->m_id = willbeDeleted->m_id;
        toDelete->m_color = willbeDeleted->m_color;
    }
    if(willbeDeleted->m_color == BLACK) // call fixup only when deleted node is black as it will violate black node count invarient
    {
        //cout<<"deleteFixup call"<<std::endl;
        deleteFixup(root,child);
    }
    delete willbeDeleted;
}

Treenode* RBTree::searchNode(int key)
{
	 if(m_root == NULL)
		 return NULL;

	 Treenode* temp = m_root;
	while (temp != NULL)
	{
		//std::cout<<"Search Iteration "<<temp->m_id;
		if (temp->m_id == key)
		{
			return temp;
		}
		else if(temp==m_treeNil)
		{
			return NULL;
		}
		else if (temp->m_id > key)
		{
			//std::cout<<" temp=temp->left"<<std::endl;
			temp = temp->left;
		}
		else
		{
			//std::cout<<" temp=temp->right"<<std::endl;
			temp = temp->right;
		}
	}
    return temp;// Redundant
}

void RBTree::Reduce(int key, int count){

    Treenode* toDecrease = searchNode(key);
    if(toDecrease == NULL)
    {
        std::cout<<"0"<<std::endl;
        return;
    }
    toDecrease->m_count -= count;
    if(toDecrease->m_count > 0)
    {
        std::cout<<toDecrease->m_count<<std::endl;
        return;
    }
    else{
        deleteNode(toDecrease,m_root, key);
        std::cout<<"0"<<std::endl;
    }

}

int RBTree::Count(int key){
//	std::cout<<"FUNCTION COUNT. Key that the user is looking for is "<<key<<std::endl;
	Treenode* temp=searchNode(key);
	if(temp == NULL){
		//std::cout<<"temp == NULL. Incorrect ID. Count = 0"<<std::endl;
		std::cout<<"0"<<std::endl;
		return 0;

	}
	//std::cout<<" Count of ID "<<key<<" is"<<temp->m_count<<std::endl;
	std::cout<<temp->m_count<<std::endl;
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
	  if(node->right != m_treeNil)
	    return minimumNode(node->right);

	 Treenode *p = node->parent;
	  while(p != m_treeNil && node == p->right)
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

	if (node->left != m_treeNil)
		return maximumNode(node->left);

	Treenode *p = node->parent;
	while (p != m_treeNil && node == p->left)
	{
		node = p;
		p = p->parent;
	}
	return p;
}

/*
 *
 */
/*
void RBTree::inRange(int key1, int key2){
	if(key2 < key1){
		std::cout<<"Make sure to keep key2 <= key1"<<std::endl;
		return;
	}
	Treenode* key1node=searchNode(key1);
	Treenode* tempnode = key1node;
	while(tempnode && tempnode->m_id!=key2){
		std::cout<<"InRange Query "<<tempnode->m_id<<std::endl;
		tempnode = inorderSuccessor(tempnode);
	}
	std::cout<<"InRange Query "<<tempnode->m_id<<std::endl;
	return;
}
*/

void RBTree::inRangeUtil(Treenode* temp,int key1, int key2,int &keySum)
{
   /* base case */
   if (temp == NULL || temp == m_treeNil)
      return;

   if ( key1 < temp->m_id)
	   inRangeUtil(temp->left, key1, key2,keySum);

   if ( key1 <= temp->m_id && key2 >= temp->m_id){
	  keySum+=temp->m_count;
	//  std::cout<<temp->m_id<<std::endl;
   }

   if ( key2 > temp->m_id)
	   inRangeUtil(temp->right, key1, key2,keySum);
}

void RBTree::inRange(int key1, int key2){
	if(key2 < key1){
		//std::cout<<"Make sure to keep key2 <= key1"<<std::endl;
		return;
	}
	int keySum=0;
	inRangeUtil(m_root,key1,key2,keySum);
	std::cout<<keySum<<std::endl;
}

Treenode* RBTree::Next(int key){
	Treenode* keynode=searchNode(key);
	Treenode* next = inorderSuccessor(keynode);
	if(next != NULL)
		std::cout<<next->m_id<<" "<<next->m_count<<std::endl;
	else
		std::cout<<key<<" 0"<<std::endl;
}

Treenode* RBTree::Previous(int key){
	Treenode* keynode=searchNode(key);
	Treenode* previous = inorderPredecessor(keynode);
	if(previous != NULL)
		std::cout<<previous->m_id<<" "<<previous->m_count<<std::endl;
	else
		std::cout<<key<<" 0"<<std::endl;
}



