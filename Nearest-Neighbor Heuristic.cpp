/*Nearest Neighbor Strategy for TSP Problems
solved by Tao*/

/*
	Nearest neighbor strategy: Starting from city 0, choose the nearest one in the city that has not been visited each time,
Until all the cities have been passed, and finally return to the starting city
*/

#include<iostream>
#include<string>
#include<iomanip>
#include <math.h>
#include <stdlib.h> 
#include <time.h> 

using namespace std;

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

		void printCity();       //print inputted city distance
		void TSP1();		//greedy method to solve the ATSP
		//void matrixMaker(int city_number);
};
 
//construct function
TSP::TSP(int city_num)
{
	//int i=0,j=0;
	//int start_city;
	city_number=city_num;
 
	//start_city=0;
	//start=start_city;
	start=0;
	//initializing marked array
	flag=new int[city_number];
	for(int i=0;i<city_number;i++)
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
 
/*
void TSP::matrixMaker(int city_number){
	
int **distance;		//city distance matrix
//initializing city distance matrix
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

   // initialize random seed: 
    srand (time(NULL));
	cout<<"Random distances between each city:"<<endl;
	for(int i=0;i<city_number;i++)
	{
		cout<<endl;
		distance[i]=new int[city_number];
		for(int j=0;j<city_number;j++)
		{
	      
			// generate secret number between 1 and 10: 
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
*/
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
	int min,j;
	int start_city=start;	//start_city
	int next_city;			// next_city
	flag[start]=1;
	
	cout<<"The shortest path:"<<endl;
	cout<<start_city;
	while(edgeCount<city_number-1)//the number of atsp cycled to city_number-1
	{
		min=100;
		for(j=0;j<city_number;j++)//find the minimal distance in the first try
		{
			if((flag[j]==0) && (distance[start_city][j] != 0) && (distance[start_city][j] < min))
			{
				next_city=j;
				min=distance[start_city][j];
			}
		}
		TSPLength+=distance[start_city][next_city];
		flag[next_city] = 1;//let the next_city join Hamilton circuit
		edgeCount++;
		cout<<"-->"<<next_city;
		
		start_city=next_city;//starting from next_city next times
	}
 
	cout<<"-->"<<start<<endl;//last tsp
	TSPLength+=distance[start_city][start];
	cout<<"Path length:"<<TSPLength;
 
}
 
 
//main function
int main()
{   
	int city_number;
	cout<<"Welcome to Nearest Neighbor Strategy for TSP Problems, Please input city nummer:";
	
	while(cin>>city_number)
	{
		TSP tsp(city_number);	//initializing
		tsp.printCity();		   //print inputted city distance
		tsp.TSP1();			   //solve the problem
	}
 
	return 0;
}