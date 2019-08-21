#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int N;
int L;

int board[100][100];

int solve(vector<vector<int>>& v);
bool isPath(vector<int>& v);
int main()
{
	cin >> N >> L;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> board[j][i];
		}
	}

	//�� ���� �̾� ����
	vector<vector<int>> vec;

	for (int i = 0; i < N; i++)
	{
		vector<int> v;
		for (int j = 0; j < N; j++)
		{
			v.push_back(board[j][i]);
		}
		vec.push_back(v);
	}
	for (int i = 0; i < N; i++)
	{
		vector<int> v;
		for (int j = 0; j < N; j++)
		{
			v.push_back(board[i][j]);
		}
		vec.push_back(v);
	}
	
	/*
	for (auto c : vec)
	{
		//if (c.at(0) >= c.at(c.size() - 1))
		//	std::reverse(c.begin(), c.end());
		for (auto i : c)
		{
			cout << i << " ";
		}
		cout << " -> " << isPath(c) << endl;
		
	}
	*/
	
	vector<int> k = { 3,2,2,2,3,3};
	isPath(k);
	

	cout << solve(vec) << endl;
	return 0;
}
int solve(vector<vector<int>>& v)
{
	int count = 0;
	for (auto c : v)
	{
		if (isPath(c))
			count++;
	}
	return count;
}

bool isPath(vector<int>& v)
{
	//���� �� üũ
	bool isUsed[100] = { false, };

	//������ 
	int pre = -1;

	int cont = 0;
	for (int i = 0; i < v.size(); i++)
	{
		//�����ؼ� ���ٰ�

		//ó��
		if (pre == -1)
		{
			pre = v[i];
			cont++;
			continue;
		}

		//���ٸ� ���� ���� üũ
		if (v[i] == pre)
		{
			pre = v[i];	//�ʿ� ������ ?
			cont++;
			continue;
		}

		//���� �ö󰡾� �Ѵٸ�
		if (v[i] > pre)
		{
			//�� ���⼭ ���̰� 1 ���� ũ�ٸ� return false;
			if (v[i] - pre != 1)
				return false;

			if (cont >= L)
			{
				//���� ����
				int t = 0;
				for (int j = i-1; j > 0; j--)
				{
					if (t == L)
						break;
					if (isUsed[j] == true)
						return false;
					t++;
				}
				isUsed[i - 1] = true;
				cont = 1;
				pre = v[i];
				continue;
			}
			else
				return false;
		}
		//�Ʒ��� �������� �Ѵٸ� ���� ������ �����.
		if (v[i] < pre)
		{
			if (pre - v[i] != 1)
				return false;

			//���� �ڱ� �ڽ� ����
			int tempcont = 1;

			//���� �ְ� �ڽ� ���� L�� �־����
			for (int j = i + 1; j < v.size(); j++)
			{
				if (v[j] == v[i])
					tempcont++;
				else
					break;

			}
			//�Ǽ� �������� ������ ?
			if (tempcont >= L)
			{
				for (int j = 0; j < L; j++)
				{
					isUsed[j + i] = true;
				}
				i += L;
				cont = 1;
				pre = v[i - 1];
				i -= 1;
				
			}
			else
				return false;

		}
	}
	return true;
}

bool isPathV1(vector<int>& v)
{
	//����
	auto itr = v.begin();

	int current = -1;
	int pre = -1;
	int count = 0;
	while (itr != v.end())
	{
		if (pre == -1)
		{
			pre = *itr;
			count++;
			itr++;
			continue;
		}

		current = *itr;

		if (pre == current)
		{
			count++;
			itr++;
			pre = current;
			continue;
		}
		if ( abs(current - pre) != 1)
		{
			return false;
		}
		else
		{
			if (count < L)
				return false;
			//���η� �ö� ��
			if (current > pre)
			{
				//���θ� �ۼ�����
				count = 1;
				pre = current;
				itr++;
				continue;
			}
			else
			{
				//���ĸ� üũ�Ѵ�.
				auto itr2 = itr;
				//������� ��������
				int tempCount = 0;
				while (itr2 != v.end())
				{
					if (*itr2 != current)
						return false;

					tempCount++;
					itr2++;
					if (tempCount >= L)
						break;
				}
				count = 1;
				pre = current;
				itr ++;
				continue;
			}
		}
		
	}


	/*
	int current = *itr;
	itr++;

	int count = 1;
	while(itr != v.end())
	{
		int next = *itr;

		//���� ģ���� ���� ��쿡��
		if (next == current)
		{
			count += 1;
			itr++;
		}
		else if (abs(next - current) != 1)
		{
			return false;
		}
		else
		{
			if (count >= L)
			{
				//���� ���� !
				current = next;
				count = 1;
				itr++;
			}
			else
				return false;
		}
	}
	*/
	
	return true;
}
