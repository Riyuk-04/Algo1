/* Name-Yashica Patodia
 * Roll No-19CS10067
 * Group-G6
 * Assignment
*/
#include<iostream>
#include<string.h>
#include<stdio.h>
#define LEN 200
using namespace std;

//Structure definition
typedef struct node
{
	char *symbol;
	int frequency;
	 node *left;
	 node *right;
	 node *next;
	
}node;

//Creating a new node and passing its pointer
node *create(node *head,char ch,int fre)

{
	node *nn=(node*)malloc(sizeof(node));
	nn->symbol=(char*)malloc(LEN*sizeof(char));
	nn->symbol[0]=ch;
	nn->symbol[1]='\0';
	nn->frequency=fre;
	nn->left=NULL;
	nn->right=NULL;
	return nn;

}
//Returns true if it is a alphanumber character
bool ischar(char ch)
{
	if(ch>='a' && ch<='z')
		return true;
	return false;
}
//Returns true if it is a digit
bool isdigit(char ch)
{
	if(ch>='0' && ch<='9')
		return true;
	return false;
}
// Returns -1 if v1 should come before v2 and 1 if opposite
int comp(char ch1,int v1,char ch2,int v2)
{
	//cout<<ch1<<" "<<v1<<" "<<ch2<<" "<<v2<<endl;
	if(v1<v2)
		return -1;
	else if(v1>v2)
		return 1;


	if(ischar(ch1) && ischar(ch2))
	{
		if(ch1<ch2)
			return -1;
		else 
			return 1;

	}
	else if(isdigit(ch1) && isdigit(ch2))
	{
		if(ch1<ch2)
			return -1;
		else
		 return 1;
	}
	else if(ischar(ch1))
		return -1;
	else 
		return 1;

}
//Returns -1 if a should come before b and 1 if a should come after b
int comp2(node *a,node *b)
{
	if(a->frequency<b->frequency)
		return -1;
	else if(a->frequency>b->frequency)
		return 1;
	if(a->symbol[0]=='N')
	{
		if(b->symbol[0]=='N')
		{
			if(a->symbol<b->symbol)
				return -1;
			return 1;
		}
		else
			return -1;
	}
	if(b->symbol[0]=='N')
		return 1;
	char ch1=a->symbol[0];
	char ch2=b->symbol[0];
	if(ischar(ch1) && ischar(ch2))
	{
		if(ch1<ch2)
			return -1;
		else 
			return 1;

	}
	else if(isdigit(ch1) && isdigit(ch2))
	{
		if(ch1<ch2)
			return -1;
		else
		 return 1;
	}
	else if(ischar(ch1))
		return -1;
	else 
		return 1;



}
//Sorting condition for merging into a super node
void sort2(node **head,node *nn)
{
	if(*head==NULL)
	{
		nn->next=NULL;
		*head=nn;
		return;
	}
	// else if(nn->symbol[0]>='a' && nn->symbol[0]<='z')
	// {
	// 	if((*head)->symbol[0])
	// }
	//else if(ischar(nn->symbol[0]) && ischar((*head)->symbol[0])
	if(comp2((*head),nn)==1)
	{
		//cout<<"hi"<<" "<<(*head)->sym[0]<<" "<<nn->sym[0]<<endl;
		nn->next=*head;
		*head=nn;
		return;
	}
	else
	{
		node *curr=*head;
	///	cout<<"pii"<<" "<<nn->sym[0]<<" "<<nn->fre<<endl;
		while(curr->next!=NULL && comp2(curr->next,nn)==-1)
		{
			//cout<<"hi2"<<" "<<curr->next->fre<<endl;
			curr=curr->next;
		}
		nn->next=curr->next;
		curr->next=nn;
	}

}
//Sorting condition for linked lists
void sort(node **head,node *nn)
{
	if(*head==NULL)
	{
		nn->next=NULL;
		*head=nn;
		return;
	}
	// else if(nn->symbol[0]>='a' && nn->symbol[0]<='z')
	// {
	// 	if((*head)->symbol[0])
	// }
	//else if(ischar(nn->symbol[0]) && ischar((*head)->symbol[0])
	if(comp((*head)->symbol[0],(*head)->frequency,nn->symbol[0],nn->frequency)==1)
	{
		//cout<<"hi"<<" "<<(*head)->sym[0]<<" "<<nn->sym[0]<<endl;
		nn->next=*head;
		*head=nn;
		return;
	}
	else
	{
		node *curr=*head;
	///	cout<<"pii"<<" "<<nn->sym[0]<<" "<<nn->fre<<endl;
		while(curr->next!=NULL && comp(nn->symbol[0],nn->frequency,curr->next->symbol[0],curr->next->frequency)==1)
		{
			//cout<<"hi2"<<" "<<curr->next->fre<<endl;
			curr=curr->next;
		}
		nn->next=curr->next;
		curr->next=nn;
	}

}
//Finding the symbol of the super node
char *convert(int ind)
{
	char *ch=(char*)malloc(LEN*sizeof(char));

	ch[0]='N';
	char *rev=(char*)malloc(LEN*sizeof(char));

	int i=0;
	while(ind!=0)
	{
		int d=ind%10;
		rev[i]=(char)(d+'0');
		ind/=10;
		i++;
	}
	rev[i]='\0';
	for(int j=1;j<=i;j++)
	{
		ch[j]=rev[i-j];
	}
	ch[i+1]='\0';
	//cout<<ch<<"crete"<<endl;
	return ch;
}
//Creating a supernode by merging 
node *create2(char *ch,int fre,node *n1,node *n2)
{
	node *nn=(node*)malloc(sizeof(node));
	nn->symbol=(char*)malloc(LEN*sizeof(char));
	// nn->sym[0]=ch;
	// nn->sym[1]='\0';
	int i=0;
	while(ch[i]!='\0')
	{
		nn->symbol[i]=ch[i];
		i++;

	}
	//cout<<nn->sym<<  "    p"<<endl;
	nn->frequency=fre;
	//cout<<nn->fre<<endl;
	nn->left=n1;
	nn->right=n2;
	return nn;
}
//Printing preorder traversal of the Huffman Tree
void preorder(node *root)
{
	if(root!=NULL)
	{
		cout<<root->symbol<<"("<<root->frequency<<")"<<" ";
		preorder(root->left);
		preorder(root->right);
	}
}
//Travrsing the tree for obtaining the Huffman Codes
void TreeTraverse(node *temp,string H[36],string C)
{
	if(ischar(temp->symbol[0]) )
		H[temp->symbol[0]-'a']=C;
	else if(isdigit(temp->symbol[0]))
		H[temp->symbol[0]-'0'+26]=C;
	else
	{
		if(temp->left!=NULL)
			TreeTraverse(temp->left,H,C+'0');
		if(temp->right!=NULL)
			TreeTraverse(temp->right,H,C+'1');
	}




}
//Part 3 implementation finding the Huffman Code of given string
void encode(char *message,char *encodedMessage,string H[36])
{
	int i=0;
	string str="";
	while(message[i]!='\0')
	{
		if(ischar(message[i]))
			str+=H[message[i]-'a'];
		else if(isdigit(message[i]))
			str+=H[message[i]-'0'+26];
		i++;


	}
	cout<<str<<endl;


}
// //Part 4 implementation 
// void decode(char *encodedMessage,char *decodedoutput,string H[36])
// {
// 	string ans="";
// 	int i=0;
// 	while(encodedMessage[i]!='\0')
// 	{
// 		for(int j=0;j<36  && encodedMessage[i]!='\0';j++)
// 		{
// 			int len=H[j].length();
// 			//char huff[LEN*100];
// 			//cout<<H[j]<<endl;
// 			//strcpy(huff,H[j]);
// 			//cout<<len<<endl;
// 			int f=1;
// 			for(int k=i;k<=len+i-1;k++)
// 			{
// 				if(encodedMessage[k]==H[j][k-i])
// 					continue;
// 				else
// 				{
// 					f=0;
// 					break;
// 				}

// 			}
// 			if(f==1)
// 			{
// 				i=i+len;
// 				if(j<26)
// 					ans+=(j+'a');
// 				else 
// 					ans+=(j-26+'0');
// 				break;

// 			}


// 		}

// 	}
// 	// while(encodedMessage[i]!='\0')
// 	// {

// 	// }
// 	cout<<ans<<endl;
// }

int main()
{
	
	freopen("log.txt","r",stdin);//Taking input from the log file
	freopen("output.txt","w",stdout);//Printing output in the output.txt file
	int n;
	cin>>n;
	char arr[n][200];
	int frea[26],fren[10];
	for(int i=0;i<26;i++)
		frea[i]=0;
	for(int i=0;i<10;i++)
		fren[i]=0;
	int len[n];
	//Implmenting Part1 of finding the frequency distribution
	for(int i=0;i<n;i++)
	{
		cin>>arr[i];
		int j=0;
		while(arr[i][j]!='\0')
		{
			if(arr[i][j]>='a' && arr[i][j]<='z')
				frea[arr[i][j]-'a']++;
			else
				fren[arr[i][j]-'0']++;
			j++;
		}
		len[i]=j;


	}
	//PART 1 printing the frequency distribution
	for(int i=0;i<26;i++)
		cout<<(char(i+'a'))<<" = "<<frea[i]<<",";
	for(int i=0;i<9;i++)
		cout<<char(i+'0')<<"= "<<fren[i]<<",";
	cout<<char('0'+9)<<" = "<<fren[9]<<endl;

	//PART 2 finding the sorted linked list
	node *head=NULL;
	for(int i=0;i<26;i++)
	{
		node *nn=create(head,(char(i+'a')),frea[i]);
		sort(&head,nn);


	}

	for(int i=0;i<10;i++)
	{
		node *nn=create(head,(char(i+'0')),fren[i]);
		sort(&head,nn);
	}
	node *curr=head;
	cout<<endl;
	int cnt=0;
	//Finfing the number of nodes in the variable count
	while(curr!=NULL)
	{
		//if(curr->fre>0)
			cnt++;
		//cout<<curr->sym[0]<<" "<<curr->fre<<endl;
		curr=curr->next;
	}
	int ind=1;
	//Till count is greater than 1 making the Huffman Tree
	while(cnt>=2)
	{
		node *temp=head;
		char *str=(char*)malloc(LEN*sizeof(char));
		strcpy(str,convert(ind));
		//cout<<str<<endl;
		int x=temp->frequency;
		int y=temp->next->frequency;
		//cout<<x<<" "<<y<<endl;
		node *nn=create2(str,x+y,temp,temp->next);
		head=head->next->next;
		sort2(&head,nn);
		cnt--;
		ind++;
	}

	node *head2=head;
	node *head3=head;
	preorder(head2);
	string H[36];
	string ans="";
	cout<<endl;
	TreeTraverse(head2,H,ans);
	for(int i=0;i<26;i++)
	{
		cout<<(char)(i+'a')<<" "<<H[i]<<endl;
	}
	for(int i=0;i<10;i++)
		cout<<(char)(i+'0')<<" "<<H[i+26]<<endl;
//PART 3
	
	
	freopen("encode.txt","r",stdin);
	int en;
	cin>>en;
	for(int i=0;i<en;i++)
	{
		char ch[LEN];
		cin>>ch;
		char enc[LEN];
		encode(ch,enc,H);

	}
	
	//freopen("decode.txt","r",stdin);
	//PART 4

	// int dec;
	// cin>>dec;
	// cout<<dec<<endl;
	// for(int i=0;i<dec;i++)
	// {
	// 	char ch[LEN];
	// 	cin>>ch;
	// 	//cout<<ch<<endl;
	// 	char decod[LEN];
	// 	decode(ch,decod,H);

	// }


}