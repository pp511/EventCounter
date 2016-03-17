Treenode::Treenode(int id,int count){
	m_id = id;
	m_count = count;
	m_root->right=m->left=NULL=m_root->parent=NULL;
	m_color = BLACK; //Default color given to a node is black.
}

/*RBTree::RBTree(int key, int count){
	if(!m_root)
		m_root = new Treenode();
	m_root->m_id = key;
	m_root->m_count = count;
	m_root->right=m->left=NULL=m_root->parent=NULL;
}*/

/* A utility function to print preorder traversal of BST */
void RBTree::inOrder(Treenode* node)
{
    if (node == NULL)
        return;
    inOrder(node->left);
    	cout<< node->m_id<<" "<<node->m_count<<endl;
    inOrder(node->right);
}

/* A function that constructs Balanced Binary Search Tree from a sorted array */
Treenode* sortedVectorToBST(vector<Treenode *> &input, int start, int end)
{
    /* Base Case */
    if (start > end)
      return NULL;

    /* Get the middle element and make it root */
    int mid = start + (end - start) / 2;
    Treenode *root = Treenode(input[mid]->m_id,input[mid]->m_count);
    root->left =  sortedVectorToBST(input, start, mid-1);
    if(root->left)
    	root->left->parent = root;
    root->right = sortedVectorToBST(input, mid+1, end);
    if(root->right)
    	root->right->parent = root;
    return root;
}

/* A utility teh colors the balanced BST builf from the input file*/
void RBTree::colorTree(Treenode* node, int level, int maxHeight)
{
    if (node == NULL)
        return;
    if(level == maxHeight)
    	node->m_color = RED;
    colorTree(node->left,level+1,maxHeight);
    colorTree(node->right,level+1,maxHeight);
}

RBTree::RBTree(vector<Treenode *> nodes){
	m_root = sortedVectorToBST(input,0,input.size()-1);// Construct the BBST from the sorted input.
	int numNodes=node.size();
	int maxHeight=0;
	// Complete Binary Tree. Since any number n if power of two can be cheked by n&(n-1)==0.
	//A complete binary tre has k=n-1 number of nodes wheren is the power ot 2.
	//If it is the case we have already colored all the nodes black and hence we satisfy all
	//the conditions for RBT. If not there is a need to color all the leaf nodes as Red.
	if((numNodes+1)&(numNodes) != 0)
		maxHeight= (int)log2(double(numNodes)) + 1;
	colorTree(m_root,0,maxHeight);// Incomplete tree. Color leaf nodes as red.
}

void RBTree::treeInsert(int key, int count){
}
void RBTree::treeDelete(int key, int count);
void RBTree::treeSearch(int key, int count);

