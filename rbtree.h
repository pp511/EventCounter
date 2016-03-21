#include <math.h>
#include <vector>

typedef enum {BLACK, RED} nodeColor;

struct Treenode{
//public:
	int m_id,m_count;
	nodeColor m_color;
	Treenode *left,*right,*parent;
	//Constructor
	Treenode(int id,int count);
};

class RBTree{
private:
	Treenode* m_root, *m_treeNil;
	int m_maxid, m_minid;
	void colorTree(Treenode* node, int level, int maxHeight);
	Treenode* sortedVectorToBST(std::vector<Treenode*> &input, int start, int end);
	void inOrderUtil(Treenode* root);
	void deleteTree(Treenode* root);
	void rotateLeft(Treenode* &root, Treenode* &currnode);
	void rotateRight(Treenode* &root, Treenode* &currnode);
    Treenode* grandparent(Treenode* node);
    Treenode* uncle(Treenode* node);
    Treenode* searchNode(int key);
    Treenode* maximumNode(Treenode* node);
    void insertFixup(Treenode* &root, Treenode* &currnode);
    Treenode* insertNode(Treenode* root, Treenode* currnode);
    void deleteNode( Treenode* &root, Treenode* &toDelete);
    void deleteFixup(Treenode* &root,Treenode* &currnode);
    Treenode* minimumNode(Treenode* node);
    Treenode* inorderSuccessor(Treenode* node);
    Treenode* inorderPredecessor(Treenode* node);
    void inRangeUtil(Treenode* temp,int key1, int key2,int &keySum);
    Treenode* nextprevUtil(int key, Treenode* &prev, bool &isright);

public:
	RBTree();
	~RBTree();
	void buildTree(std::vector<Treenode*> &input);
	void inOrder();
	void Increase(int key,int count);
	void Reduce(int key, int count);
	int Count(int key);
	void inRange(int key1, int key2);
	Treenode* Next(int key);
	Treenode* Previous(int key);
};
