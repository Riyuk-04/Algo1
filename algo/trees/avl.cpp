#include<iostream>
#include<fstream>

using namespace std;

char *correction(char input[],char *temp){
	int i = 1;
	int j = 1;
	temp[0] = input[0];
	while(input[i]!='\0'){
		if(input[i] == input[i-1])
			i++;
		else{
			temp[j] = input[i];
			i++;
			j++;
		}
	}
	temp[j] = '\0';
return temp;	
}

int compare(char *string1, char *string2){
	int i = 0;
	while(string1[i] !='\0' && string2[i] !='\0'){

		if(string1[i] > string2[i])
			return 1;
		if(string1[i] < string2[i])
			return 0;
		else	i++;
	}
return -1;
}

typedef struct _treenode {

	char * route ;
	struct _treenode * left = NULL;
	struct _treenode * right = NULL;
	int balancefactor = 0;

} AVLtreenode ;

typedef AVLtreenode * AVLtree ;

int main(){
	char input[20];
	char *string;
	string = input;

	fstream file;
	char filename[] = "Routes.txt";
	file.open(filename);
	int n;
	file>>n;

	AVLtreenode temp;
	AVLtree root,head;
	root = (AVLtree )malloc(sizeof(AVLtreenode));
	head = root;
	while (file >> input)
    {  
    	string = correction(input,string);
        //cout<<string<<endl;
        temp.route = string;
        temp.balancefactor = 0;
        *root = temp;
        //root = (AVLtree )malloc(sizeof(AVLtreenode));
    }
    cout<<head->route;
    file.close();
    
return 0;
}