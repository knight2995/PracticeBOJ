#include <iostream>
#include <set>
#include <vector>

using namespace std;

void draw(int x, int y, int d, int g);
void insert(int x, int y);
int check();

set<pair<int, int>> ans;
/*
0: x��ǥ�� �����ϴ� ���� (��)
1: y��ǥ�� �����ϴ� ���� (��)
2: x��ǥ�� �����ϴ� ���� (��)
3: y��ǥ�� �����ϴ� ���� (��)
*/

int dx[] = { 1,0,-1,0 };
int dy[] = { 0,-1,0,1 };

vector<int> vec;

//Ŀ�� 0 : 0			1
//Ŀ�� 1 : 1			1
//Ŀ�� 2 : 2 1			2
//Ŀ�� 3 : 2 3 2 1		4
//Ŀ�� 0 : 0
//Ŀ�� 1 : 0 1
//Ŀ�� 2 : 0 1 2 1
//Ŀ�� 3 : 0 1 2 1 2 3 2 1

// + 1 �� �ϰ� �ݴ�� ����

int result = 0;
int main()
{
	int testcase;
	cin >> testcase;

	while (testcase--)
	{
		int x, y, d, g;
		cin >> x >> y >> d >> g;
		draw(x,y,d,g);
		insert(x,y);
	}

	

	for (int i = 0; i <= 99; i++)
	{
		for (int j = 0; j <= 99; j++)
		{
			//���� �� ���� �������� ���� ������ �밢���� ���� ��쿡 �߰�
			if (ans.count({ i, j }) && ans.count({ i + 1, j }) && ans.count({ i, j + 1 }) &&
				ans.count({ i + 1, j + 1 }))
			{
				result++;
			}


		}
	}
	cout << result;
}

void draw(int x, int y, int d, int g)
{
	if (g == 0)
	{
		vec.push_back(d);
		return;
	}

	draw(x, y, d, g - 1);

	//int i = vec.size() - 1;
	for (int i = vec.size()-1; i >= 0; i--)
	{

		vec.push_back( (vec[i] + 1) % 4  );
	}

}

void insert(int x, int y)
{
	ans.insert({ x,y });
	for (auto c : vec)
	{
		ans.insert({ x += dx[c], y += dy[c] });
	}
	vec.clear();
}
