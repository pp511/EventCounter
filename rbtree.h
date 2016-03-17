#include <math.h>
typedef enum {BLACK, RED} nodeColor;

class Treenode{
private:
	int m_id,m_count;
	nodeColor m_color;
	Treenode *left,*right,*parent;
public:
	Treenode(int id,int count);
}

class RBTree{
private:
	Treenode* m_root;
	colorTree(Treenode* node, int level, int maxHeight);
	Treenode* sortedVectorToBST(vector<Treenode*> input);
public:
	RBTree();
	RBTree(vector<Treenode*> input);
	void RBTree::inOrder(Treenode* node)
	void treeInsert(int key, int count);
	void treeDelete(int key, int count);
	void treeSearch(int key, int count);
}
