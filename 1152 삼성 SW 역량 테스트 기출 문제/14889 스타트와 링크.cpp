#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int N;
int board[20][20];
bool isUsed[20] = { false, };
int ans = INT_MAX;
int a = 0;

void makeTeam(int idx,int cnt);
void cal();
int main()
{

	cin >> N;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> board[i][j];

	
	makeTeam(0,0);

	cout << ans << endl;
}
void printIndex()
{
	for (int i = 0; i < N; i++)
	{
		if (isUsed[i])
			cout << i << " ";
	}
	cout << endl;
}
void makeTeam(int idx,int cnt)
{
	//ÆÀ ¿Ï¼º
	if (cnt == N / 2)
	{
		//cout << "Ãâ·Â" << endl;
		//a++;
		cal();
		//printIndex();
		return;
	}

	for (int i = idx; i < N; i++)
	{
		if (isUsed[i] == true)
			continue;
		isUsed[i] = true;
		makeTeam(i, cnt + 1);
		isUsed[i] = false;
		
	}

		
}

void cal()
{
	//½ºÅ¸Æ®ÆÀ
	int start = 0;
	int link = 0;

	vector<int> startTeam;
	vector<int> linkTeam;

	for (int i = 0; i < N; i++)
	{
		if (isUsed[i])
			startTeam.push_back(i);
		else
			linkTeam.push_back(i);
	}

	for (int i = 0; i < N / 2; i++)
	{
		for (int j = i + 1; j < N / 2; j++)
		{
			start += board[startTeam.at(i)][startTeam.at(j)];
			start += board[startTeam.at(j)][startTeam.at(i)];
		}
	}
	for (int i = 0; i < N / 2; i++)
	{
		for (int j = i + 1; j < N / 2; j++)
		{
			link += board[linkTeam.at(i)][linkTeam.at(j)];
			link += board[linkTeam.at(j)][linkTeam.at(i)];
		}
	}


	ans = min(ans, abs(start - link));
}
