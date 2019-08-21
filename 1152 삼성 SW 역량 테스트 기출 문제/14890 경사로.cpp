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

	//줄 마다 뽑아 내기
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
	//사용된 길 체크
	bool isUsed[100] = { false, };

	//이전꺼 
	int pre = -1;

	int cont = 0;
	for (int i = 0; i < v.size(); i++)
	{
		//직진해서 가다가

		//처음
		if (pre == -1)
		{
			pre = v[i];
			cont++;
			continue;
		}

		//같다면 같은 높이 체크
		if (v[i] == pre)
		{
			pre = v[i];	//필요 없겠지 ?
			cont++;
			continue;
		}

		//위로 올라가야 한다면
		if (v[i] > pre)
		{
			//단 여기서 차이가 1 보다 크다면 return false;
			if (v[i] - pre != 1)
				return false;

			if (cont >= L)
			{
				//조건 검증
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
		//아래로 내려가야 한다면 이제 문제가 생긴다.
		if (v[i] < pre)
		{
			if (pre - v[i] != 1)
				return false;

			//현재 자기 자신 포함
			int tempcont = 1;

			//같은 애가 자신 포함 L개 있어야함
			for (int j = i + 1; j < v.size(); j++)
			{
				if (v[j] == v[i])
					tempcont++;
				else
					break;

			}
			//건설 가능하지 않을까 ?
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
	//시작
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
			//위로로 올라갈 때
			if (current > pre)
			{
				//경사로를 작성하자
				count = 1;
				pre = current;
				itr++;
				continue;
			}
			else
			{
				//이후를 체크한다.
				auto itr2 = itr;
				//현재부터 다음까지
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

		//다음 친구가 같을 경우에는
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
				//경사로 장착 !
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
