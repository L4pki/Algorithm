/*
21. Имеется  информация о взаимных долгах предприятий.Если
имеется цепочка предприятий
A1(a1)-- > A2(a2)-- > ... -- > An(an)-- > A1(a1),
где Ai - наименование предприятия, а ai - размер долга, то с
каждого из предприятий можно списать долг в размере min(ai), а
предприятие с минимальным долгом исключить из списка должников
следующему в цепочке  предприятию.Требуется  найти  варианты
взаимного  списания  долгов.Предложить критерии оптимальности
и способы оптимизации(11).

Среда разработки: Visual Studio 2022
*/
  
#include <iostream> 
#include <fstream> 
#include <vector> 
#include <string> 
using namespace std;


struct Edge {
	int comp1;
	int comp2;
	int weight;
};


void WriteVector(vector<Edge> edges, string s)
{
	cout << s << endl;
	for (int i = 0; i < edges.size(); i++)
		cout << "(" << edges[i].comp1 << " " << edges[i].comp2 << " " << edges[i].weight << ")";
	cout << endl;

}

vector<vector<Edge>> GraphStructurized(vector<Edge> edges, int num)
{
	vector<Edge> forOneCompany;
	vector<vector<Edge>> graphCompany;
	for (int j = 0; j < num; j++)
	{
		for (int i = 0; i < edges.size(); i++)
		{
			if (edges[i].comp1 == j + 1)
				forOneCompany.push_back(edges[i]);
		}
		graphCompany.push_back(forOneCompany);
		forOneCompany.clear();
	}
	return graphCompany;
}

vector<vector<Edge>> Recursive(vector<vector<Edge>> ad, vector<vector<Edge>>* cyclenull, Edge ad_i, int numElement, vector<Edge> find)
{
	find.push_back(ad_i);
	if (ad_i.comp2 == numElement)
	{
		cyclenull->push_back(find);
		return *cyclenull;
	}
	for (int i = 0; i < find.size(); i++)
	{
		if (ad_i.comp2 == find[i].comp1)
			return *cyclenull;
	}
	if (ad[ad_i.comp2 - 1].size() != 0)
	{
		for (int i = 0; i < ad[ad_i.comp2 - 1].size(); i++)
		{
			Recursive(ad, cyclenull, ad[ad_i.comp2 - 1][i], numElement, find);
		}
	}
	return *cyclenull;
}

bool sravnenie(vector<Edge> q, vector<Edge> w)
{
	int dg = 0;
	for (int j = 0; j < q.size(); j++)
	{
		for (int f = 0; f < q.size(); f++)
		{
			if (q[j].comp1 == w[f].comp1 && q[j].comp2 == w[f].comp2)
			{
				dg++;
			}
		}
	}
	if (dg == q.size())
		return true;
	else
		return false;
}

bool SravnenieStruct(Edge q, Edge w)
{
	if (q.comp1 == w.comp1 && q.comp2 == w.comp2)
		return true;
	else
		return false;
}


vector<vector<Edge>> FindCycle(vector<vector<Edge>> ad, int rebro)
{
	vector<vector<Edge>> cycle;
	vector<Edge> cyclenullOne;
	vector<vector<Edge>>* cyclenull = new vector<vector<Edge>>;
	vector<Edge> find;
	for (int i = 0; i < ad.size(); i++)
	{
		for (int j = 0; j < ad[i].size(); j++)
		{
			Recursive(ad, cyclenull, ad[i][j], ad[i][j].comp1, find);
		}

	}
	while (cyclenull->size() != 0)
	{
		cyclenullOne = cyclenull[0][0];
		for (int i = 0; i < cyclenull->size(); i++)
		{
			if (cyclenullOne.size() == cyclenull[0][i].size())
			{
				if (sravnenie(cyclenullOne, cyclenull[0][i]))
				{
					cyclenull->erase(cyclenull[0].begin() + i);
					i--;
				}
			}
		}
		cycle.push_back(cyclenullOne);
	}
	return cycle;
}

void GlobalDebtReWrite(vector<Edge>* edges, vector<Edge> delEdge, vector<Edge> debtEdge, vector <string> company, int num)
{
	vector<vector<Edge>> edgesgl;

	for (int i = 0; i < edges->size(); i++)
	{

		for (int j = 0; j < debtEdge.size(); j++)
		{
			if (SravnenieStruct(debtEdge[j], edges[0][i]))
			{
				edges[0][i].weight = debtEdge[j].weight;
			}
		}
	}
	int t = 0;
	for (int i = 0; i < edges->size(); i++)
	{
		if (t != 0)
			i--;
		t = 0;
		for (int j = 0; j < delEdge.size(); j++)
		{
			if (SravnenieStruct(delEdge[j], edges[0][i]))
			{

				edges[0].erase(edges[0].begin() + i);
				t++;
			}
		}

	}
	edgesgl = GraphStructurized(*edges, num);
	cout << "----------------------------------------------" << endl;
	cout << "              Не списанные долги              " << endl;
	cout << "----------------------------------------------" << endl;
	for (int j = 0; j < edgesgl.size(); j++)
	{
		for (int r = 0; r < edgesgl[j].size(); r++)
		{
			cout << company[edgesgl[j][r].comp1 - 1] << " --> " << company[edgesgl[j][r].comp2 - 1] << " " << edgesgl[j][r].weight << "000 У.Е." << endl;
		}

	}
	cout << "----------------------------------------------" << endl;
}


int MinDebt(vector<Edge> ad)
{
	int minDebt = ad[0].weight;
	for (int i = 0; i < ad.size(); i++)
	{
		if (ad[i].weight < minDebt)
		{
			minDebt = ad[i].weight;
		}
	}
	return minDebt;
}

void ReWriteCycle(vector<vector<Edge>>* cycle, vector<Edge> delEdge, vector<Edge> debtEdge)
{
	for (int i = 0; i < cycle->size(); i++)
	{
		for (int j = 0; j < cycle[0][i].size(); j++)
		{
			for (int g = 0; g < debtEdge.size(); g++)
			{
				if (SravnenieStruct(debtEdge[g], cycle[0][i][j]))
					cycle[0][i][j].weight = debtEdge[g].weight;
			}
		}
	}
	int t = 0;
	for (int i = 0; i < cycle->size(); i++)
	{
		t = 0;
		for (int j = 0; j < cycle[0][i].size(); j++)
		{
			if (SravnenieStruct(delEdge[0], cycle[0][i][j]))
			{
				cycle[0].erase(cycle[0].begin() + i);
				t++;
				break;
			}

		}
		if (t != 0 && i != 0)
			i--;
	}

}
void MetodUser(vector<vector<Edge>> cycle, vector<Edge>* edges, vector <string> company, int num)
{
	int minDebt;
	int index = -1;
	Edge pusto;
	vector<Edge> buf;
	vector<Edge> delEdge;
	vector<Edge> debtEdge;
	vector<Edge> gldelEdge;
	vector<Edge> gldebtEdge;
	while (cycle.size() != 0)
	{
		delEdge.clear();
		debtEdge.clear();
		buf.clear();
		cout << " Выберите желаемую цепочку долговых связей: " << endl << endl;
		for (int e = 0; e < cycle.size(); e++)
		{
			cout << e + 1 << " Цепочка долгов";
			WriteVector(cycle[e], "");
		}
		cin >> index;
		minDebt = MinDebt(cycle[index - 1]);
		cout << "----------------------------------------------" << endl;
		cout << "              Списание долгов                 " << endl;
		cout << "----------------------------------------------" << endl;
		for (int j = 0; j < cycle[index - 1].size(); j++)
		{
			buf.push_back(pusto);
			buf[j].comp1 = cycle[index - 1][j].comp1;
			buf[j].comp2 = cycle[index - 1][j].comp2;
			buf[j].weight = cycle[index - 1][j].weight - minDebt;
			cout << company[buf[j].comp1 - 1] << " --> " << company[buf[j].comp2 - 1] << " " << minDebt << "000 У.Е." << endl;



			if (buf[j].weight == 0)
			{
				delEdge.push_back(buf[j]);

			}
			else
				debtEdge.push_back(buf[j]);
		}
		cout << "----------------------------------------------" << endl;
		ReWriteCycle(&cycle, delEdge, debtEdge);
		for (int q = 0; q < delEdge.size(); q++)
			gldelEdge.push_back(delEdge[q]);
		for (int q = 0; q < debtEdge.size(); q++)
			gldebtEdge.push_back(debtEdge[q]);
	}
	cout << "----------------------------------------------" << endl;
	GlobalDebtReWrite(edges, gldelEdge, gldebtEdge, company, num);
}
void MetodMaxDebt(vector<vector<Edge>> cycle, vector<Edge>* edges, vector <string> company, int num)
{
	int maxDebt;
	int minDebt;
	int index = -1;
	Edge pusto;
	vector<Edge> buf;
	vector<Edge> delEdge;
	vector<Edge> debtEdge;
	vector<Edge> gldelEdge;
	vector<Edge> gldebtEdge;
	while (cycle.size() != 0)
	{
		index = 0;
		maxDebt = -1;
		delEdge.clear();
		debtEdge.clear();
		buf.clear();
		for (int i = 0; i < cycle.size(); i++)
		{
			for (int b = 0; b < cycle[i].size(); b++)
			{
				if (cycle[i][b].weight > maxDebt)
				{
					maxDebt = cycle[i][b].weight;
					index = i;
				}
			}
		}
		minDebt = MinDebt(cycle[index]);
		cout << "----------------------------------------------" << endl;
		cout << "              Списание долгов                 " << endl;
		cout << "----------------------------------------------" << endl;
		for (int j = 0; j < cycle[index].size(); j++)
		{
			buf.push_back(pusto);
			buf[j].comp1 = cycle[index][j].comp1;
			buf[j].comp2 = cycle[index][j].comp2;
			buf[j].weight = cycle[index][j].weight - minDebt;
			cout << company[buf[j].comp1 - 1] << " --> " << company[buf[j].comp2 - 1] << " " << minDebt << "000 У.Е." << endl;



			if (buf[j].weight == 0)
			{
				delEdge.push_back(buf[j]);

			}
			else
				debtEdge.push_back(buf[j]);
		}
		ReWriteCycle(&cycle, delEdge, debtEdge);
		for (int q = 0; q < delEdge.size(); q++)
			gldelEdge.push_back(delEdge[q]);
		for (int q = 0; q < debtEdge.size(); q++)
			gldebtEdge.push_back(debtEdge[q]);
	}
	cout << "----------------------------------------------" << endl;
	GlobalDebtReWrite(edges, gldelEdge, gldebtEdge, company, num);
}
void MetodMinCycle(vector<vector<Edge>> cycle, vector<Edge>* edges, vector <string> company, int num)
{
	int minSize = 999;
	int minDebt;
	int index = -1;
	Edge pusto;
	vector<Edge> buf;
	vector<Edge> delEdge;
	vector<Edge> debtEdge;
	vector<Edge> gldelEdge;
	vector<Edge> gldebtEdge;
	while (cycle.size() != 0)
	{
		index = 0;
		delEdge.clear();
		debtEdge.clear();
		buf.clear();
		for (int i = 0; i < cycle.size(); i++)
		{
			if (cycle[i].size() < minSize)
			{
				minSize = cycle[i].size();
				index = i;
			}
		}
		minDebt = MinDebt(cycle[index]);
		cout << "----------------------------------------------" << endl;
		cout << "              Списание долгов                 " << endl;
		cout << "----------------------------------------------" << endl;
		for (int j = 0; j < cycle[index].size(); j++)
		{
			buf.push_back(pusto);
			buf[j].comp1 = cycle[index][j].comp1;
			buf[j].comp2 = cycle[index][j].comp2;
			buf[j].weight = cycle[index][j].weight - minDebt;
			cout << company[buf[j].comp1 - 1] << " --> " << company[buf[j].comp2 - 1] << " " << minDebt << "000 У.Е." << endl;




			if (buf[j].weight == 0)
			{
				delEdge.push_back(buf[j]);

			}
			else
				debtEdge.push_back(buf[j]);
		}
		ReWriteCycle(&cycle, delEdge, debtEdge);
		for (int q = 0; q < delEdge.size(); q++)
			gldelEdge.push_back(delEdge[q]);
		for (int q = 0; q < debtEdge.size(); q++)
			gldebtEdge.push_back(debtEdge[q]);
	}
	cout << "----------------------------------------------" << endl;
	GlobalDebtReWrite(edges, gldelEdge, gldebtEdge, company, num);
}

int main()
{
	vector<vector<Edge>> cycle;
	vector<vector<Edge>> graphCompany;
	setlocale(LC_ALL, "Russian");
	ifstream f2("Debts.txt");
	int rebro = 0;
	Edge drop;
	vector<Edge> edges;
	while (!f2.eof()) {
		edges.push_back(drop);
		f2 >> edges[rebro].comp1 >> edges[rebro].comp2 >> edges[rebro].weight;
		rebro++;
	};
	ifstream f1("Names.txt");
	vector <string> company;
	string pusto = "";
	int num = 0;
	while (!f1.eof())
	{
		company.push_back(pusto);
		getline(f1, company[num]);
		num++;
	}
	int number;
	cycle = FindCycle(GraphStructurized(edges, num), rebro);
	cout << "Меню выбора способа оптимизации долгов " << endl;
	cout << "Выберите способ решения: " << endl;
	cout << "1 - Метод минимального цикла" << endl << "2 - Метод наибольшего долга" << endl << "3 - Метод пользовательский" << endl;
	cout << "Введите номер: ";
	cin >> number;
	if (number == 1)
		MetodMinCycle(cycle, &edges, company, num);
	if (number == 2)
		MetodMaxDebt(cycle, &edges, company, num);
	if (number == 3)
		MetodUser(cycle, &edges, company, num);
	return 0;
}