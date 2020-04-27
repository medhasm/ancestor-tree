#include <stdio.h>
#include <string>
#include<iostream>
using namespace std;
namespace family{

class Tree{

public:
Tree* mother;
Tree* father;
string name;
Tree(string name){
this->name=name;
this->father=NULL;
this->mother=NULL;

}
~Tree(){

if(this->father!=NULL){

delete this->father;
}
if(this->mother!=NULL){

delete this->mother;

}


}
Tree& addFather(string name,string fathername);

Tree& addMother(string name,string mothername);
string relation(string name);
string find(string name);
void display();
bool remove(string name);
};

}
bool removehelper(family::Tree& root,string name);
int stringSpliter(string name ,bool* a);
string RecursiveFind(family::Tree& root,int c,bool a);
int FindByName(family::Tree& root,string name,bool* a);
void displaytree(family::Tree& root,int c,bool dad);
family::Tree* get(family::Tree* root,string name);
