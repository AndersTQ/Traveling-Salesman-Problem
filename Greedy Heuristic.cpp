/*Greedy Method for ATSP Problem solved by Tao*/
/*
	The TSP problem means that the traveler needs to travel n cities, and each city is required to pass through and only once.
Then go back to the starting city, and take the shortest path.
*/
/*
	Select the shortest edge in the entire matrix each time and add it to the solution set, ensuring that the edges in the solution set eventually form a Hamiltonian circuit

*/
#include<iostream>
#include<string>
#include<iomanip>
#include<algorithm>
#include<deque>
#include <math.h>
#include <stdlib.h> 
#include <time.h> 
using namespace std;
/*TSP CLASS*/
class TSP
{
	public:
        int start_city;		                //starting city
		int end_city;			//ending city 
		int distance;			//distance between starting city and ending city
		TSP(int sta,int end,int dis);	//construct function
		TSP();				//default construct function
		void init(int sta,int end,int dis);	//initializing function
		void printfInfo();			//print information
};
/*function prototype declaration*/
int cmp(TSP t1,TSP t2);							//sorting 
int TSP2(TSP *t,int city_num,int cities,TSP *process);  //greedy method for solving TSP

int find(int x,int *pre);						//find previous node
int find2(int x,int *pre);	
void join(int x,int y,int *pre);					//merge the nodes

int matrixMaker(int city_number,TSP *t);

//construct function
TSP::TSP(int sta,int end,int dis)
{
	start_city=sta;
    end_city=end;
	distance=dis;
}
//default construct function
TSP::TSP()
{
}
//initializing function
void TSP::init(int sta,int end,int dis)
{
    start_city=sta;
    end_city=end;
	distance=dis;
}
//function for printing information
void TSP::printfInfo()
{
	cout<<start_city<<"\t"<<end_city<<"\t"<<distance<<"\t\n";
}
 
//sorting rules
int cmp(TSP t1,TSP t2)
{
	return t1.distance<t2.distance;
}
 
//greedy method for solving TSP
int TSP2(TSP *t,int city_num,int cities,TSP *process)
{
	int TSPLength=0;
	int i=0,j=0,k=0;
	int *flag=new int[city_num];	//record if there exist en next node
	int *flag2=new int[city_num];	//record the level of the node
	int *pre=new int[city_num];		// record previous node
	for(i=0;i<city_num;i++)
	{
		flag[i]=0;					// all nodes have no next node
		flag2[i]=0;	                // all level of all nodes are 0
		pre[i]=i;					//previous initial node is itself
	}
	do{
		for(i=0;i<cities;i++)
		{
			if(j<city_num-1){
			if(find(t[i].start_city,pre)!=find(t[i].end_city,pre))//if their previous initial are not same 
			{
				
                if(flag2[t[i].end_city]<=2 && flag2[t[i].start_city]<=2 && flag[t[i].start_city]==0 && find(t[i].end_city,pre)==t[i].end_city)//不会产生分支
				{
					
					flag[t[i].start_city]++;	// find a next node
				    //flag[t[i].end_city]++;
					flag2[t[i].start_city]++;	//level increased with 1
				    flag2[t[i].end_city]++;// level increased with 1
					TSPLength+=t[i].distance;	//sum of TSPLength
					//cout<<"The row of TSP"<<" "<<i<<" "<<"from city"<<t[i].start_city<<"to city"<<t[i].end_city<<"The distance is"<<" "<<t[i].distance<<endl;
					//save the chosen TSP
					process[k].start_city=t[i].start_city;
					process[k].end_city=t[i].end_city;
					process[k].distance=t[i].distance;
					j++;
					k++;
					join(t[i].start_city,t[i].end_city,pre);//connecting two cities
					//cout<<"next TSP>>>>>>>>>>>>>>";
				}
			}
			}else if(j==city_num-1){

				if(find(t[i].start_city,pre)==find(t[i].end_city,pre))//if their previous initial are same 
			{
				
                if(flag2[t[i].end_city]<=2 && flag2[t[i].start_city]<=2 && flag[t[i].start_city]==0 && find(t[i].end_city,pre)==t[i].end_city)//不会产生分支
				{
					//cout<<"The row of TSP"<<" "<<i<<" "<<"from city"<<t[i].start_city<<"to city"<<t[i].end_city<<"The distance is"<<" "<<t[i].distance<<endl;
					flag[t[i].start_city]++;	
				    //flag[t[i].end_city]++;// 
					flag2[t[i].start_city]++;	//
				    flag2[t[i].end_city]++;// 
					TSPLength+=t[i].distance;	//
					//
					process[k].start_city=t[i].start_city;
					process[k].end_city=t[i].end_city;
					process[k].distance=t[i].distance;
					j++;
					k++;
					join(t[i].start_city,t[i].end_city,pre);
					
				}
			}

			}
		}
	}while(j<city_num);


	return TSPLength;
	
}
 
//find previous node
int find(int x,int *pre)
{
    int r=x;
    while(pre[r]!=r)
    r=pre[r];		//find previous node
	
    int i=x,j;
	    while(i!=r)		
    {
        j=pre[i];	//record previous node
        pre[i]=r;	//将i的前导结点设置为r根节点
        i=j;
    }
	
    return r;
}

int find2(int x,int *pre)
{
    int r=x;
    while(pre[r]!=r){
    r=pre[r];	
	}	
    return r;
}
 
//merge the nodes
void join(int x,int y,int *pre)
{
    int a=find(x,pre);	//x root node is a
    int b=find(y,pre);	//y root node is b
    if(a!=b)			
    {
        //connecting ab, and set a previous node b
		pre[y]=x;
    }
}


int matrixMaker(int city_number,TSP *t){
	
int **distance;		//city distance matrix
//initializing city distance matrix
distance=new int*[city_number];

cout<<"Please input a number, 1 or 2. Number 1 meaning that you input matrix self. Number 2 means that system generates en matrix for you.";
int number;
cin>>number;
if (number==1)
{
//Old code
    int m=0;
	
	cout<<"Input distances between each city:"<<endl;
	for(int i=0;i<city_number;i++)
	{
		distance[i]=new int[city_number];
		for(int j=0;j<city_number;j++){
			cin>>distance[i][j];
			}
	}
 
    for(int k=0;k<city_number;k++)
	{
		distance[k][k]=0;
	}

		for(int i=0;i<city_number;i++)
	{
		
		for(int j=0;j<city_number;j++){
			t[m].start_city=i;
			t[m].end_city=j;
			t[m].distance=distance[i][j];
			m++;
			}
	}
			
			 return 0;
}
else if (number==2){
//Generate matrix 
    int iSecret;

   /* initialize random seed: */
    srand (time(NULL));
	cout<<"Random distances between each city:"<<endl;
	for(int i=0;i<city_number;i++)
	{
		cout<<endl;
		distance[i]=new int[city_number];
		for(int j=0;j<city_number;j++)
		{
	      
			 /* generate secret number between 1 and 10: */
			iSecret = rand() % 10+ 1;
			//iSecret = rand() % 10 + 1;
			//cout<<"Please input city nummer:"<<iSecret;
			distance[i][j]=iSecret;
			if(i==j){
				distance[i][j]=0;
			}
		    cout<<distance[i][j]<<" ";
		}
	}
	cout<<endl; 
	int m=0;
			for(int i=0;i<city_number;i++)
	{
		
		for(int j=0;j<city_number;j++){
			t[m].start_city=i;
			t[m].end_city=j;
			t[m].distance=distance[i][j];
			m++;
			}
	}
    return 0;
   }

cout<<endl; 
}
 
//main function
int main()
{
	cout<<"welcome to greedy method for ATSP, please input city nummer:"<<"";
	int city_number,cities=0; 
	
	while(cin>>city_number)
	{
		int i,j,k=0;
		cities=(city_number) * (city_number);
		//cities=cities*cities/4;
		TSP *tsp=new TSP[cities];			//record all cities tsp
		TSP *process=new TSP[city_number];	//the shortest tsp
        int **distance;
		matrixMaker(city_number,tsp);
	    //initializing the matrix
		
		//sort
		sort(tsp,tsp+cities,cmp);
	
		cout<<"-------------------------------------"<<endl;
		//
		cout<<"shortest path:"<<endl;
        int length=TSP2(tsp,city_number,cities,process);
		cout<<"start \t"<<"end \t"<<"distance\t"<<endl;
		for(i=0;i<city_number;i++)
		{
		    process[i].printfInfo();	
		}

		deque<int> d;//create a deque, so save the cities in the sequence with solved solution
	    d.push_back(process[0].start_city);
		d.push_back(process[0].end_city);
	    		
		int previous_city=process[0].start_city, next_city=process[0].end_city;
        //previous_city is the starting city in the sequence,next_city is the ending city in the sequence
        int f=0;
		do{
			//cycle to the second last process
        for (int i = 1; i < city_number; ++i) {
			

			if(process[i].start_city==next_city){
			d.push_back(process[i].end_city);
			next_city =process[i].end_city;
			f++;
			//cout<<"-->"<<next_city;
			}else if (process[i].end_city==previous_city && process[i].start_city!=next_city){
			d.push_front(process[i].start_city);
			previous_city =process[i].start_city;
			f++;
			//cout<<"-->"<<previous_city<<"-->";
			}
			}
		}while(f<city_number-2);
        
        //take acre of the last process
		if (f==city_number-2){

				if(process[i].start_city==next_city){
			d.push_back(process[i].end_city);
			next_city =process[i].end_city;
			//f++;
			//cout<<"-->"<<next_city;
			}

		}

		//do{}while(d.size()<city_number)
               
		cout<<"Shortest Path in summary:"<<endl;
	for(int i = 0; i < d.size(); i++)
	{
		if(i<d.size()-1){
		cout<<d.at(i)<<"-->";
		}else if(i==d.size()-1){
		cout<<d.at(i)<<"\t"<<endl;
	}
	}

		cout<<"Total length:"<<length<<endl;
        delete[] tsp;
	}
	return 0;
}