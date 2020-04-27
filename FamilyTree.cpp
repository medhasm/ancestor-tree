#include "FamilyTree.hpp"
#include <stdio.h>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "string"
#define TRUE 1
#define FALSE 0

using namespace family;
using namespace std;
void tokenize(std::string const &str, const char delim,
			std::vector<std::string> &out);
Tree& Tree::addFather(string name,string fathername){
Tree* root=get(this,name);
if(root==NULL){
throw runtime_error( "name is not exist1");
}
if(root->father!=NULL){
throw runtime_error( "father is already exist");

}

root->father=new Tree(fathername);

return *this;


}




Tree& Tree::addMother(string name,string mothername){

Tree* root=get(this,name);
if(root==NULL){
throw runtime_error( "name is not exist1");
}
if(root->mother!=NULL){
throw runtime_error( "mother is already exist");

}

root->mother=new Tree(mothername);





return *this;
}
string Tree::relation(string name){
bool dady=false;
bool* dad=&dady;
int x=FindByName(*this,name,dad);

if(x==-1) return "unrelated";

if(x==0) return "me";
if(x==1){

if(*dad==true) return "father";

if(*dad==false) return "mother";
}
string str="";

for(int i=1 ; i<=(x-1);i++){

if(i==(x-1)){
if (*dad==true) str=str+ "grandfather";
if (*dad==false) str=str+ "grandmother";
}
else{
str=str+"great-";
}
}
return str;
}
string Tree::find(string relation){
bool dady=FALSE;
bool* dad=&dady;

int x=stringSpliter(relation,dad);


if(x==-2){
throw runtime_error( "The tree cannot handle the "+relation+" relation");
}

string name=RecursiveFind(*this, x, *dad);

if(name=="notfound"){
throw runtime_error( "The tree cannot handle the "+relation+" relation");
return "the tree dont have this  relation ->"+relation+"in his/her family";
}
return name;
}
void Tree::display(){
displaytree(*this,0,false);
}
bool Tree::remove(string name){

if(this->name==name) throw runtime_error( "root cant be deleted"+name);
if(removehelper(*this,name)==true) return true;
else throw runtime_error( "name is not exist1"+name);
return false;
}

int stringSpliter(string relation , bool* ifdad){
int c=0;
int* counter =&c;
vector<string> result;
const char a='-';
//split(relation,a,result);
tokenize(relation, a,result);
if(result.size()==1){

if(result[0]=="me"){
return -1;
}
if(result[0]=="father"){
*counter=1;
*ifdad=true;
return *counter;
}
if(result[0]=="mother"){
*counter=1;

*ifdad=false;

return *counter;
}
if(result[0]=="grandfather"){
*counter=2;
*ifdad=true;
return *counter;
}
if(result[0]=="grandmother"){
*counter=2;
*ifdad=false;
return *counter;
}
}
if(result.size()>1){

for(size_t i=0 ;i<result.size();i++){

if(result[i]=="great"){
*counter +=1;
}
if(result[i]=="grandfather" && i==result.size()-1){
*counter+=2;
*ifdad=true;
return *counter;
}
if(result[i]=="grandmother" && i==result.size()-1){
*counter+=2;
*ifdad=false;
return *counter;
}

}
}
return -2;
}
string RecursiveFind(Tree& root,int c,bool dad){
if(c==-1) return root.name ;
if(c==1 && dad==true && (root.father!=NULL)) return root.father->name;
if(c==1 && dad==false && (root.mother!=NULL)) return root.mother->name;
if(c==2 ){
if(dad==false){
if((root.mother!=NULL) && (root.mother->mother!=NULL)) return root.mother->mother->name;
if((root.father!=NULL) && (root.father->mother!=NULL)) return root.father->mother->name;

return "notfound";



}
if(dad==true){
if((root.mother!=NULL) && (root.mother->father!=NULL)) return root.mother->father->name;
if((root.father!=NULL) && (root.father->father!=NULL)) return root.father->father->name;
return "notfound";
}
}
if(c>2){
if(root.father!=NULL){
string fath=RecursiveFind(*(root.father),(c-1),dad);
if(fath!="notfound") return fath;
}
if(root.mother!=NULL){
string moth=RecursiveFind(*(root.mother),(c-1),dad);

if(moth!="notfound") return moth;
}
}
return "notfound";
}


int FindByName(family::Tree& root,string name,bool* dad){
if(root.name!=name) { //add else 
if(root.father!=NULL) {
int fath;
if(root.father->name==name){
*dad=true;
int x=1;

return x;
}
if(FindByName(*(root.father),name,dad)!=-1){
fath=FindByName(*(root.father),name,dad)+1;
return fath;
}

}
if(root.mother!=NULL) {
int moth;
if(root.mother->name==name){
*dad=false;
int x=1;
int *y=&x;
return x;
}
if(FindByName(*(root.mother),name,dad)!=-1){
moth=FindByName(*(root.mother),name,dad)+1;
return moth;
}
}
}//close if root.name
else{// else rootname
int x=FALSE;

return x;
}
 return -1;
}
void displaytree(family::Tree& root,int c,bool dad){
if(c==0){
cout<<root.name<<" the youngest child"<<endl;
}
if(c==1 &&dad==true){
cout<<root.name<<" father"<<endl;
}
if(c==1 &&dad==false){
cout<<root.name<<" mother"<<endl;
}
if(c>1){
string str="";
for(int i=1 ; i<=(c-1);i++){

if(i==(c-1)){
if (dad==true) str=str+ " grandfather";
if (dad==false) str=str+ " grandmother";
}
else{
str=str+" great-";
}
}
cout<<root.name<<str<<endl;
}

if(root.father!=NULL){
displaytree(*(root.father),c+1,true);
}
if(root.mother!=NULL){
displaytree(*(root.mother),c+1,false);
}
return;
}




bool removehelper(Tree& root,string name){
if(root.name==name) {


if(root.father!=NULL){
delete root.father;
}
if(root.mother!=NULL){
delete root.mother;
}
return true;
}
if(root.father!=NULL && removehelper(*(root.father),name)){
if(root.father->name==name){

root.father=NULL;
}
return true;
}

if(root.mother!=NULL && removehelper(*(root.mother),name)){
if(root.mother->name==name){

root.mother=NULL;

}
return true;
}





return false;
}



Tree* get(family::Tree* root,string name){
if(root->name==name){
return root;
}
if(root->father!=NULL && get(root->father,name)!=NULL ){
return get(root->father,name);
}
if(root->mother!=NULL && get(root->mother,name)!=NULL ){
return get(root->mother,name);

}
return NULL;
}

void tokenize(std::string const &str, const char delim,
			std::vector<std::string> &out)
{
	size_t start;
	size_t end = 0;

	while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}


