#include <math.h>
#include <vector>


typedef enum {BLACK, RED} nodeColor;

class Treenode{
public://Data to be changed to private. Improper OOP practice.
	int m_id,m_count;
	nodeColor m_color;
	Treenode *left,*right,*parent;
	//Constructor
	Treenode(int id,int count);
};

class RBTree{
private:
	Treenode* m_root;
	void colorTree(Treenode* node, int level, int maxHeight);
	Treenode* sortedVectorToBST(std::vector<Treenode> input, int start, int end);
	void inOrderUtil(Treenode* root);
	void deleteTree(Treenode* root);
	void replaceNode(Treenode* oldNode, Treenode* newNode);
	void rotateLeft(Treenode* node);
	void rotateRight(Treenode* node);
    void insert_case1(Treenode* node);
    void insert_case2(Treenode* node);
    void insert_case3(Treenode* node);
    void insert_case4(Treenode* node);
    void insert_case5(Treenode* node);
    Treenode* grandparent(Treenode* node);
    Treenode* sibling(Treenode* node);
    Treenode* uncle(Treenode* node);
    Treenode* searchNode(int key);
    Treenode* maximumNode(Treenode* node);
    void delete_case1(Treenode* node);
    void delete_case2(Treenode* node);
    void delete_case3(Treenode* node);
    void delete_case4(Treenode* node);
    void delete_case5(Treenode* node);
    void delete_case6(Treenode* node);
    Treenode* minimumNode(Treenode* node);
    Treenode* inorderSuccessor(Treenode* node);
    Treenode* inorderPredecessor(Treenode* node);
    void inRangeUtil(Treenode* temp,int key1, int key2);


public:
	RBTree();
	~RBTree();
	void buildTree(std::vector<Treenode> input);
	void inOrder();
	void Increase(int key,int count);
	void Reduce(int key, int count);
	int Count(int key);
	void inRange(int key1, int key2);
	Treenode* Next(int key);
	Treenode* Previous(int key);

};
