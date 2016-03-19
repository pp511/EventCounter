#include <iostream>
#include <fstream>
#include <string>
#include "rbtree.h"
using namespace std;
int main(int argc, char* argv[]){
	if(argc!=2){
		cout<<"Incorrect command line argments. Exiting the code"<<endl;
		return 0;
	}
	vector<Treenode*> input;
	ifstream inputfile;
	inputfile.open(argv[1]);
	int id,count,numinputs;
	inputfile>>numinputs;
//	cout<<"Number of Inputs"<<numinputs<<endl;
	for(int i=0;i<numinputs;i++){
		inputfile>>id;
		inputfile>>count;
		//std::cout<<id<<" "<<count<<" Pushed at Index"<<i<<std::endl;
		Treenode* temp=new Treenode(id,count);
		input.push_back(temp);
	}
	//Closing the input file.
	inputfile.close();
//	cout<<"All inputs have been read from the file.Building the tree now"<<endl;

	//Instance of RBTree being used as the even counter.
	RBTree eventCounter;
	// Building the tree from the given input.
	eventCounter.buildTree(input);
//	std::cout<<" TREE HAS BEEN BUILT. ENTERING USER INTERACTION MODE"<<std::endl;
	string command="";
	int param1=0,param2=0;
	cout<<"Choose the command "<<endl;
	cout<<"-------------------"<<endl;
	cout<<"increase <id> <m>"<<endl;
	cout<<"reduce  <id> <m>"<<endl;
	cout<<"count <id>"<<endl;
	cout<<"next <id>"<<endl;
	cout<<"previous <id>"<<endl;
	cout<<"inrange <id1> <id2>"<<endl;
	cout<<"inorder : Inorder traversal of the given tree."<<endl;
	cout<<"quit : Halt the current execution"<<endl;
	cout<<"-------------------"<<endl;

	eventCounter.Increase(350,100);
	eventCounter.Reduce(350,50);
	eventCounter.Count(350);
	eventCounter.inRange(300,1000);
	eventCounter.inRange(200,299);
	eventCounter.inRange(200,1000);
	eventCounter.inRange(300,349);
	eventCounter.inRange(350,350);
	eventCounter.inRange(349,350);
	eventCounter.Next(300);
	eventCounter.Next(349);
	eventCounter.Next(360);
	eventCounter.Previous(360);
	eventCounter.Previous(350);
	eventCounter.Previous(0);
	eventCounter.Reduce(271,6);
	eventCounter.Previous(350);

	eventCounter.Reduce(271,3);
	eventCounter.Previous(350);
	eventCounter.Previous(150);


	while(1){
		break;
		cout<<"Enter your command"<<endl;
		cin>>command;
		if(command=="increase"){
			cin>>param1;
			cin>>param2;
			eventCounter.Increase(param1,param2);
		}
		if(command=="reduce"){
				cin>>param1;
				cin>>param2;
				eventCounter.Reduce(param1,param2);
		}
		if(command=="count"){
			   cout<<command<<" command is executing"<<endl;
				cin>>param1;
				eventCounter.Count(param1);
		}
		if(command=="next"){
				cin>>param1;
				eventCounter.Next(param1);
		}
		if(command=="previous"){
				cin>>param1;
			eventCounter.Previous(param1);
		}
		if(command=="inrange"){//To be tested
					cin>>param1;
					cin>>param2;
					eventCounter.inRange(param1,param2);
		}
		if(command=="inorder"){
			eventCounter.inOrder();
		}

		if(command=="quit"){
			break;
		}
		command="";
		param1=0;
		param2=0;
	}
	return 0;
}
