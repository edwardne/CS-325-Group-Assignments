#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <limits.h>
#include<fstream>
#include<string>
#include <sstream>
#include <math.h>

using namespace std;

struct G
{
	int V;
	struct ListV* ar;
};

struct MinH
{
	int  V;
	int H;
};

struct MinHArr
{
	int S;
	int SS;
	int *ind;
	struct MinH **arr;
};

struct NodePair
{
	int v1;
	int v2;
};

struct ListVert
{
	int V;
	int EW;
	struct ListVert* nextV;
};

struct ListV
{
	struct ListVert *Top;
};

vector<NodePair> pairs;

struct MST
{
	int weight;
	vector<NodePair> pairs;
};


void Swap(struct MinH** first, struct MinH** second)
{
struct MinH* temp = *first;

	*first = *second;
	*second = temp;
}

int isEmpty(struct MinHArr* Heap)
{
	return Heap->S == 0;
}

bool Contains(struct MinHArr *min, int V)
{
	if (min->ind[V] < min->S)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void FindMin(struct MinHArr* min, int index)
{
	int cur = index;
	int L = (index*2 + 1);
	int R = (index*2 + 2);

	MinH *SH, *ind;

    if (L < min->S && min->arr[L]->H < min->arr[cur]->H)
    {
        cur = L;
    }

    if (R < min->S && min->arr[R]->H < min->arr[cur]->H)
    {
        cur = R;
    }

    if (cur != index)
    {
        SH = min->arr[cur];
        ind = min->arr[index];

        min->ind[SH->V] = index;
        min->ind[ind->V] = cur;

        Swap(&min->arr[cur], &min->arr[index]);
        FindMin(min, cur);
    }
}

struct MinH* getMin(struct MinHArr* min)
{
	struct MinH* newmin;
	struct MinH* prev;
    if (isEmpty(min))
    {
        return 0;
    }

	newmin = min->arr[0];
	prev = min->arr[(min->S) - 1];

	min->arr[0] = prev;
	min->ind[newmin->V] = min->S - 1;
	min->ind[prev->V] = 0;
	(min->S)--;

	FindMin(min, 0);

return newmin;
}

void FindIndex(struct MinHArr* min, int v, int key)
{
	int ind = min->ind[v];
	min->arr[ind]->H = key;

    while (ind && min->arr[ind]->H < min->arr[(ind - 1) / 2]->H)
    {
        min->ind[min->arr[ind]->V] = (ind - 1) / 2;
        min->ind[min->arr[(ind - 1) / 2]->V] = ind;
        Swap(&min->arr[ind], &min->arr[(ind - 1) / 2]);
        ind = (ind - 1) / 2;
    }
}

void printArr(int arr[], int n)
{
	pairs.clear();

	for (int i = 1; i < n; ++i)
    {
		NodePair newPair;
		newPair.v1 = i;
		newPair.v2 = arr[i];
		pairs.push_back(newPair);
	}
}

struct MinHArr* createH(int SS)
{
struct MinHArr* minH = (struct MinHArr*) malloc(sizeof(struct MinHArr));
	minH->ind = (int *)malloc(SS * sizeof(int));
	minH->S = 0;
	minH->SS = SS;
	minH->arr =(struct MinH**) malloc(SS * sizeof(struct MinH*));
	return minH;
}

struct MinH* newMinH(int V, int H)
{
struct MinH* minH = (struct MinH*) malloc(sizeof(struct MinH));

	minH->V = V;
	minH->H = H;

    return minH;
}

//Prim's Algorithm
void Prim(struct G* G)
{
	int V = G->V;
	int P[V], H[V];
	struct MinHArr* min = createH(V);
	int i;

    for (i = 1; i < V; i++)
    {
        P[i] = -1;
        H[i] = INT_MAX;
        min->arr[i] = newMinH(i, H[i]);
        min->ind[i] = i;
    }

	H[0] = 0;
	min->arr[0] = newMinH(0, H[0]);
	min->ind[0] = 0;
	min->S = V;

    while (!isEmpty(min))
    {
        struct MinH* minH = getMin(min);
        int j = minH->V;
        struct ListVert* prim = G->ar[j].Top;

        while (prim != 0)
        {
            int h = prim->V;
                if (Contains(min, h) && prim->EW < H[h])
                {
                    H[h] = prim->EW;
                    P[h] = j;
                    FindIndex(min, h, H[h]);
                }
            prim = prim->nextV;
        }
    }

	printArr(P, V);
}

struct ListVert* newListVert(int V, int EW)
{
	struct ListVert* newV =	(struct ListVert*) malloc(sizeof(struct ListVert));

	newV->V = V;
	newV->EW = EW;
	newV->nextV = 0;

return newV;
}

void addEdge(struct G* newG, int VS, int DS, int EW)
{
	struct ListVert* newV = newListVert(DS, EW);
	newV->nextV = newG->ar[VS].Top;
	newG->ar[VS].Top = newV;
	newV = newListVert(VS, EW);
	newV->nextV = newG->ar[DS].Top;
	newG->ar[DS].Top = newV;
}

struct G* newGraph(int Vsize)
{
	struct G* newG = (struct G*) malloc(sizeof(struct G));
	newG->V = Vsize;
	newG->ar = (struct ListV*) malloc(Vsize * sizeof(struct ListV));

	int i;
	for (i = 0; i < Vsize; ++i)
	{
		newG->ar[i].Top = 0;
	}

return newG;
}

int main()
{
	int V, n, k, val, total;
	int mstFirst, mstSecond, mstThird;

	FILE* fp;
	fp = fopen("input.txt", "rb");
	fscanf(fp, "%d", &n);

	int Nodes[n][n];

	//get input from input.txt
	for (int i = 0;; i++)
    {
        for (int j = 0;; j++)
        {
            if (fscanf(fp, "%d", &val) == -1)
            {
                goto end;
            }
            Nodes[i][j] = val;
            if ((k = fgetc(fp)) == '\n')
            break;
        }
	}
	end:

	//Create and Fill a new graph with input's data
	V = n;
	struct G* ggraph = newGraph(V);
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < i; j++)
        {
			if (Nodes[i][j] != 0)
			{
				addEdge(ggraph, i, j, Nodes[i][j]);
			}
		}
	}

    //use prim's algrothimn
	Prim(ggraph);
	total = 0;

	for (vector<NodePair>::const_iterator i = pairs.begin(); i != pairs.end(); ++i)
    {
		total += Nodes[i->v2][i->v1];
	}

	struct MST mst;
	mst.weight = total;
	mst.pairs = pairs;

	//store weight of First MST
	mstFirst = mst.weight;
	cout << "first MST: " << mstFirst << endl;

	pairs.clear();

	vector<int> mstWeight;
	mstWeight.push_back(mst.weight);
	vector<MST> mstVec;

	for (vector<NodePair>::const_iterator iter = mst.pairs.begin(); iter != mst.pairs.end(); ++iter)
    {
		ggraph = newGraph(V);

		for (int i = 0; i < V; i++)
		{
			for (int j = 0; j <= i; j++)
            {
				if (Nodes[i][j] != 0 && !((i == iter->v1 && j == iter->v2) || (i == iter->v2 && j == iter->v1)))
                {
                    addEdge(ggraph, i, j, Nodes[i][j]);
                }
			}
		}

        //use prim's algrothimn
		Prim(ggraph);
		total = 0;

		for (vector<NodePair>::const_iterator k = pairs.begin(); k != pairs.end(); ++k)
        {
			total += Nodes[k->v1][k->v2];
		}

		struct MST m;
		m.weight = total;
		m.pairs = pairs;
		mstVec.push_back(m);

	}

	struct MST smallest = mstVec.at(0);
	int c = 0;

	for (int i = 0; i < mstVec.size(); i++)
    {
		if (mstVec.at(i).weight < smallest.weight)
		{
			if (find(mstWeight.begin(), mstWeight.end(), mstVec.at(i).weight) == mstWeight.end())
			{
				smallest = mstVec.at(i);
			}
		}
	}


	struct MST mst2 = smallest;

	//store weight of Second MST
	mstSecond = mst2.weight;
	cout << "Second MST: " << mstSecond << endl;
	mstWeight.push_back(mst2.weight);

	mstVec.clear();
	for (vector<NodePair>::const_iterator iter = mst2.pairs.begin(); iter != mst2.pairs.end(); ++iter) {
		ggraph = newGraph(V);
		for (int i = 0; i < V; i++)
            {
			for (int j = 0; j <= i; j++)
			{
				if (Nodes[i][j] != 0 && !((i == iter->v1 && j == iter->v2) || (i == iter->v2 && j == iter->v1)))
				{
					addEdge(ggraph, i, j, Nodes[i][j]);
				}
			}
		}

        //use prim's algrothimn
		Prim(ggraph);
		total = 0;
		for (vector<NodePair>::const_iterator k = pairs.begin(); k != pairs.end(); ++k)
        {
			total += Nodes[k->v1][k->v2];
		}
		struct MST mst2;
		mst2.weight = total;
		mst2.pairs = pairs;
		pairs.clear();
		mstVec.push_back(mst2);
	}
	smallest = mstVec.at(0);
	smallest.weight = INT_MAX;

	for (int i = 0; i < mstVec.size(); i++)
        {
		if (mstVec.at(i).weight < smallest.weight)
		{
			if (find(mstWeight.begin(), mstWeight.end(), mstVec.at(i).weight) == mstWeight.end())
			{
				smallest = mstVec.at(i);
			}
		}
	}
	struct MST mst3 = smallest;

	//store weight of Third MST
	mstThird = mst3.weight;
	cout << "Third MST: " << mstThird << endl;
	mstWeight.push_back(mst3.weight);

	ofstream outfile;
    outfile.open("output.txt");

    outfile << mstFirst <<"\n"<<mstSecond<<"\n"<<mstThird<<"\n";

    outfile.close();

	return 0;
}
