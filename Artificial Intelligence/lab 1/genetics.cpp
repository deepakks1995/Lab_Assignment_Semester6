/*			TSP using Genetics Algorithms
*	Name: Deepak Sharma		Roll_NO: B14107
*	Name: Kapardi Trivedi	Roll_NO: B14110
*/
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <time.h>
#include <cmath>
#include <algorithm>
using namespace std;


/*Macros used to control Program
*********************************************/
#define GROUP_SIZE 10
#define NEARBY_CITY 5
#define NEARBY_CITY_ODDS 90
#define PROBABILITY_AREA_OF_CITIES 800
#define PROBABILITY_AREA_OF_CANDIDATES 2000
#define NUMBER_OF_GENERATIONS 100000
/***********************************************/


/*Class Definition
************************************************/
class tours {
public:
	std::vector<int> v;
	double cost;
	tours() {
		cost = 0;
	}

	bool operator < (const tours& node) const {
		return (this->cost < node.cost);
	}
};
/***********************************************/


typedef tours population;

//Variable Declarations starts here...........
int N;
float **grid;
double **probabilityMatrix;
int POPULATION_SIZE;
int PER_MUTATION;
double *probabilityOfCandidates;
vector<population *> candidate;
int bestCostOfTour = 999999999;
std::vector<int> bestTour;
/*******************************************************/

/*Function Declaration starts here
********************************************************/
void getInput( );
void printTours(int , int);
void selectionProcess1();
int sortTours(tours*, tours*);
void crossoverOfCandidates(std::vector<int>& , std::vector<int>& );
void mutationOfCandidates();
void updateBestTour();
void createSequence(std::vector<int> &, std::vector<int> &);
void createOrdinalRepresentation(std::vector<int> &);
double updateCost(std::vector<int> &);
void generateRandomToursModified();
void setParameters();
bool sortfunc(const pair<double, int> &, const pair<double, int> &);
/*************************************************/


int main(int argc, char *argv[])
{
	srand(time(NULL));
	getInput();
	setParameters();
	generateRandomToursModified();
	probabilityOfCandidates = new double[POPULATION_SIZE];
	
	for(int i = 0; i<NUMBER_OF_GENERATIONS; ++i) {
		selectionProcess1();
		mutationOfCandidates();
		updateBestTour();
		printTours(bestCostOfTour,bestCostOfTour+1);
	}
	
	return 0;
}


/*Function Definition starts here
**************************************************/

void setParameters() {
	if(N==100) {
		PER_MUTATION = 8;
		POPULATION_SIZE = 2000;
	}
	else if(N==250) {
		PER_MUTATION = 8;
		POPULATION_SIZE = 1500;
	}
	else if(N==500) {
		PER_MUTATION = 10;
		POPULATION_SIZE = 2500;
	}
	else {
		PER_MUTATION = 8;
		POPULATION_SIZE = 2000;
	}
}

/***************************************************/

void generateRandomToursModified() {
	int start = -1;
	bool visitedCity[N];
	std::vector<pair<double, int> > pair;
	for(int i=0; i<POPULATION_SIZE; ++i) {
		candidate.push_back(new population());
		start = rand() % N;
		candidate[i]->v.push_back(start);
		candidate[i]->cost = 0;
		for(int j=0; j<N; ++j) {
			visitedCity[j] = 0;
		}
		visitedCity[start] = 1;
		for(int j=1; j<N; ++j) {
			int itr=0;
			start = candidate[i]->v[j-1];
			int min=999999,indexmin = -1;
			for(int it = 0; it <N; ++it) {
				if(min >= grid[start][it] && !visitedCity[it]) {
					min = grid[start][it];
					indexmin = it;
				}
			}
			candidate[i]->v.push_back(indexmin);
			candidate[i]->cost += grid[start][indexmin];
			visitedCity[indexmin] = 1;
		}
		candidate[i]->cost += grid[candidate[i]->v[N-1]][candidate[i]->v[0]];
		if(candidate[i]->cost < bestCostOfTour) {
			bestCostOfTour = candidate[i]->cost;
			bestTour = candidate[i]->v;
		}
	}
}

/******************************************/

bool sortfunc(const pair<double, int> &p1, const pair<double, int> &p2) {
	return p1.first < p2.first;
}

/*****************************************/

void selectionProcess1() {
	sort(candidate.begin(), candidate.end(),sortTours);
	bool tour[POPULATION_SIZE];
	for(int i=0; i<POPULATION_SIZE; ++i)
		tour[i] = 0;
	int i=0,index1=-1,index2 = -1;
	while(i<POPULATION_SIZE) {	
		if(!tour[i]) {
			if(index1==-1)
				index1 = i;
			else if(index2==-1)
				index2 = i;
		}
		if(index1!=-1 && index2!=-1) {
			tour[index2] = tour[index1] = 1;
			//cout<<"***index1: "<<index1<<"  index2: "<<index2<<endl;;
			crossoverOfCandidates(candidate[index1]->v, candidate[index2]->v);
			index2 = index1 = -1;
		}
		++i;
	}
}

/**********************************************/

int sortTours(tours *a, tours *b) {
	return (*a < *b);
}

/*************************************************/

void mutationOfCandidates() {
	int mutationSize = ceil ( ( PER_MUTATION * POPULATION_SIZE ) / 100 );
	int count = 0,index,swapIndex1,swapIndex2;
	bool checker[POPULATION_SIZE];
	for(int i=0; i<POPULATION_SIZE; ++i)
		checker[i] = 0;
	while(count < mutationSize) {
		index = rand() % POPULATION_SIZE;
		while(checker[index])
			index = rand() % POPULATION_SIZE;
		swapIndex1 = rand() % N;
		swapIndex2 = rand() % N;
		while(swapIndex2==swapIndex1)
			swapIndex2 = rand() % N;
		
		int temp = candidate[index]->v[swapIndex1];
		candidate[index]->v[swapIndex1] = candidate[index]->v[swapIndex2];
		candidate[index]->v[swapIndex2] = temp;
		candidate[index]->cost = 0;
		for(int itr = 1; itr <N ; ++itr) {
			candidate[index]->cost += grid[candidate[index]->v[itr-1]][candidate[index]->v[itr]];  
		}
		candidate[index]->cost += grid[candidate[index]->v[N-1]][candidate[index]->v[0]];
		++count;
	}
}

/******************************************************/

void createSequence(std::vector<int> &tour, std::vector<int> &childNode) {
    int numberOfCities = N;
    bool city[numberOfCities];
    for(int i=0; i<numberOfCities; ++i) 
        city[i] = 0;
    for(int i=0; i<numberOfCities; ++i){
        int index = tour[i],count = 0,j=0;
        while(true) {
            if(j == index && !city[j] ){
                ++count;
                childNode.push_back(count);
                city[j] = 1;
                break;
            }
            else if(!city[j])
                ++count;
            ++j;
        }
    }    
}

/**************************************************/

void createOrdinalRepresentation(std::vector<int> &childNode) {
	int numberOfCities = childNode.size();
    bool city[numberOfCities];
    for(int i=0; i<numberOfCities; ++i) 
        city[i] = 0;
    for(int i=0; i<numberOfCities; ++i) {
        int index = childNode[i] - 1;
        int j=0,count=0;
        while(true) {
            if(count == index && !city[j]){
                childNode[i] = j;
                city[j] = 1;
                break; 
            }
            else if(!city[j])
                ++count;
            ++j;
        }
    }
}

/*****************************************************/

double updateCost(std::vector<int> &childNode) {
	double cost = 0;
	for(int i=1; i<childNode.size(); ++i) {
		cost += grid[childNode[i-1]][childNode[i]];
	}
	cost += grid[childNode[N-1]][childNode[0]];
	return cost;
}

/*****************************************************/

void crossoverOfCandidates(std::vector<int> &tour1, std::vector<int> &tour2) {
    int numberOfCities = tour2.size();
    std::vector<int> childNode1,childNode2;
    createSequence(tour1, childNode1);
    createSequence(tour2, childNode2);
    int temp;
    for(int i = rand()%numberOfCities; i<numberOfCities; ++i) {
        temp = childNode2[i];
        childNode2[i] = childNode1[i];
        childNode1[i] = temp;
    }
    createOrdinalRepresentation(childNode1);
    createOrdinalRepresentation(childNode2);
    int max = 0,maxIndex1 = -1,maxIndex2 = -1;
    for(int i=0; i<POPULATION_SIZE; ++i)
    	if(candidate[i]->cost > max) {
    		max = candidate[i]->cost;
    		maxIndex1 = i;
    	}
    max = 0;
    for(int i=0; i<POPULATION_SIZE; ++i)
    	if(candidate[i]->cost > max && i!=maxIndex1) {
    		max = candidate[i]->cost;
    		maxIndex2 = i;
    	}
    double cost = updateCost(childNode1);
    if(maxIndex1!=-1 && cost < candidate[maxIndex1]->cost) {
    	candidate[maxIndex1]->cost = cost;
    	candidate[maxIndex1]->v = childNode1;
    }
    cost = updateCost(childNode2);
    if(maxIndex2!=-1 && cost < candidate[maxIndex2]->cost) {
    	candidate[maxIndex2]->cost = cost;
    	candidate[maxIndex2]->v = childNode2;
    }
}

/*********************************************************/

void getInput() {
	float a, b;
	char ch=fgetc(stdin);
	while(ch!='\n')
		ch = fgetc(stdin);
	fscanf(stdin, "%d",&N);
	for(int i=0; i<N; ++i)
		fscanf(stdin,"%f %f",&a,&b);

	grid = new float*[N];
	for(int i=0; i<N; ++i)
		grid[i] = new float[N];
	for(int i=0; i<N; ++i)
		for(int j=0; j<N; ++j)
			fscanf(stdin,"%f",&grid[i][j]);
}

/********************************************************/

void updateBestTour() {
	for(int i=0; i<POPULATION_SIZE; ++i) {
		if(candidate[i]->cost < bestCostOfTour) {
			bestCostOfTour = candidate[i]->cost;
			bestTour = candidate[i]->v;
		}
	}
}

/********************************************************/

void printTours(int low, int high) {
		for(int j=0; j<bestTour.size(); ++j)
			cout<<bestTour[j]<<" ";
		cout<<endl<<endl;
}

/************************************************************
**********END***********************************************/