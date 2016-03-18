#include <iostream>
#include <fstream>
#include <string>
#include "rbtree.h"
using namespace std;
int main(int argc, char* argv[]){
	/*if(argc!=2){
		cout<<"Incorrect command line argments. Exiting the code"<<endl;
		return 0;
	}*/
	vector<Treenode> input;
	ifstream inputfile;
	//inputfile.open(argv[1]);
//	inputfile.open("my.txt");
//	inputfile.open("test_100.txt");
	inputfile.open("test_1000000.txt");
	int id,count,numinputs;
	inputfile>>numinputs;
	cout<<"Number of Inputs"<<numinputs;

	for(int i=0;i<1000000;i++){
		int k;
		inputfile>>id;
		inputfile>>count;
	//	std::cout<<id<<" "<<count<<std::endl;
		input.push_back(Treenode(id,count));
	}
	cout<<"LOPP EXITED";
	inputfile.close();
	RBTree eventCounter;
	eventCounter.buildTree(input);// Building the tree from the given input.
//	eventCounter.inOrder();
	std::cout<<" TREE HAS BEEN BUILT. ENTERING USER INTERACTION MODE"<<std::endl;
	string command="";
	int param1=0,param2=0;
	while(1){
		break;
		cout<<"Enter your command"<<endl;
		cin>>command;
		if(command=="increase"){
			cin>>param1;
			cin>>param2;
		//	eventCounter.Increase(param1,param2);
		}
		if(command=="reduce"){
				cin>>param1;
				cin>>param2;
		//		eventCounter.Reduce(param1,param2);
		}
		if(command=="count"){
				cin>>param1;
		//		eventCounter.Count(param1);
		}
		if(command=="next"){
				cin>>param1;
		//		eventCounter.Next(param1);
		}
		if(command=="previous"){
				cin>>param1;
		//	eventCounter.Previous(param1);
		}
		if(command=="inrange"){
					cin>>param1;
					cin>>param2;
				//	eventCounter.inRange(param1,param2);
		}
		if(command=="quit"){
			break;
		}
		cout<<command<<param1<<param2;
		command="";
		param1=0;
		param2=0;
	}
	return 0;
}
