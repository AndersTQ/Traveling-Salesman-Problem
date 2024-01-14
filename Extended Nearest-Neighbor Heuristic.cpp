/*Extended Nearest Neighbor Strategy for TSP Problems 

solved by Tao*/

/*
	Extended Nearest neighbor strategy: Starting from city 0, choose the nearest one to the starting city 1 and from starting city 2. So it works in both directions and is extended Nearest neighbor strategy. 
*/
using namespace std;
#include<iostream>
#include<string>
#include<iomanip>
#include<deque>
#include <math.h>
#include <stdlib.h> 
#include <time.h> 

//class TSP
class TSP
{
	private:
		int city_number;	//city_number
		int **distance;		//city distance matrix
		int start;		//starting city
		int *flag;		//mark array, judge if the city can join Hamilton circuit
		int TSPLength;		//length
	public:
		TSP(int city_num);	//construct function
		void correct();		//correct city distance matrix
		void printCity();       //print inputted city distance
		void TSP1();		//greedy method to solve the ATSP
};
 
//construct function
TSP::TSP(int city_num)
{
	int i=0,j=0;
	
	city_number=city_num;
 
	//initializing city distance matrix
	/*
	distance=new int*[city_number];
	cout<<"Input distances between each city:"<<endl;
	for(i=0;i<city_number;i++)
	{
		distance[i]=new int[city_number];
		for(j=0;j<city_number;j++)
			cin>>distance[i][j];
	}
 */
	//initializing marked array
	flag=new int[city_number];
	for(i=0;i<city_number;i++)
	{
		flag[i]=0;
	}
 
	TSPLength=0;
	 distance=new int*[city_number];

cout<<"Please input a number, 1 or 2. Number 1 meaning that you input matrix self. Number 2 means that system generates en matrix for you.";
int number;
cin>>number;
if (number==1)
{
//Old code
    
	
	cout<<"Input distances between each city:"<<endl;
	for(int i=0;i<city_number;i++)
	{
		distance[i]=new int[city_number];
		for(int j=0;j<city_number;j++)
			cin>>distance[i][j];
	}
 
    for(int k=0;k<city_number;k++)
	{
		distance[k][k]=0;
	}

  return;
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
 return;
}

cout<<endl; 
 
}
 
//correct inputted city distance matrix
void TSP::correct()
{
	int i;
	for(i=0;i<city_number;i++)
	{
		distance[i][i]=0;
	}
}
 
//print inputted city distance
void TSP::printCity()
{
	int i,j;
	
	cout<<"The distances matrix you inputted"<<endl;
	for(i=0;i<city_number;i++)
	{
		for(j=0;j<city_number;j++)
		cout<<setw(3)<<distance[i][j];
		cout<<endl;
	}
}
 
 
//greedy method to solve the ATSP
void TSP::TSP1()
{
	int edgeCount=0;// the number of atsp
	int min1,j,min2,k;
	int start_city1=0;	//start_city 1, but before start_city 2 in next case. In the first case, they are same.
	int start_city2=0;  //start_city 2, but after start_city 2 in next case.
	int next_city, previous_city;			
	flag[start_city1]=1;
	
	deque<int> d;//create a deque, so save the cities in the sequence
	
	d.push_back(0);
	
	cout<<"The shortest path:"<<endl;
	//cout<<start;
	while(edgeCount<city_number)//the number of atsp cycled to city_number-1
	{
		min1=1000,min2=1000;
		for(j=0;j<city_number;j++)//find the minimal distance from start_city2
		{
			if((flag[j]==0) && (distance[start_city2][j] != 0) && (distance[start_city2][j] < min2))
			{
				//next_city=j;
				min2=distance[start_city2][j];
				next_city=j;
				//cout<<"from city"<<start_city2<<"to city"<<j<<",distance is"<<distance[start_city2][j]<<endl;

			}
		}

		for(k=0;k<city_number;k++)//find the minimal distance to the start_city1
		{
			if((flag[k]==0) && (distance[k][start_city1] != 0) && (distance[k][start_city1]< min1))
			{
				//
				min1=distance[k][start_city1];
				previous_city=k;
				//cout<<"from city"<<k<<"to city"<<start_city1<<",distance is"<<distance[k][start_city1]<<endl;
			}
		}
        // compare the two and select the minimal distance 
		if (min2<=min1){
            
			int old_start_city2=start_city2;
			start_city2=next_city;
			flag[start_city2]=1;
			d.push_back(next_city);
			TSPLength+=distance[old_start_city2][next_city];
			//cout<<"--1-->"<<next_city;
			cout<<old_start_city2<<"-->"<<next_city<<", the distance is:"<<distance[old_start_city2][next_city]<<endl;

		}else if (min2>min1){
			int old_start_city1=start_city1;
			start_city1=previous_city;
			d.push_front(previous_city);
			//start_city2=start_city2;
			flag[start_city1]=1;
			TSPLength+=distance[previous_city][old_start_city1];
            //cout<<"--2-->"<<previous_city;
			cout<<previous_city<<"-->"<<old_start_city1<<",the distance is:"<<distance[previous_city][old_start_city1]<<endl;
		    
		}
		
		edgeCount++;
	
	}
 
	cout<<"Shortest Path in summary:"<<endl;
	for(int i = 0; i < d.size(); i++)
	{
		if(i<d.size()-1){
		cout<<d.at(i)<<"-->";
		}else if(i=d.size()-1){
		cout<<d.at(i)<<"\t";
	}
	}
	cout<<endl;
	cout<<"Path length:"<<TSPLength;
 
}
 
 
//main function
int main()
{   
	int city_number;
	cout<<"Welcome to Extended Nearest Neighbor Strategy for TSP Problems,Please input city nummer:";
	
	while(cin>>city_number)
	{
		//TSP *process=new TSP[city_number];	//the shortest tsp
		TSP tsp(city_number);	//initializing
		//tsp.correct();			   //correct city distance matrix
		tsp.printCity();		   //print inputted city distance
		tsp.TSP1();			   //solve the problem
	}
 
	return 0;
}