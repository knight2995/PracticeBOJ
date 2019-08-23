#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

struct Gear
{
	int data[8];

	//0은 12시를 가르킨다.
	int current = 0;

	int getRight() { return data[(current + 2) % 8]; }
	int getLeft() { return data[(current + 6) % 8]; }

	void rotate(int direct)
	{
		//direct = 1 -> 시계 방향
		//direct = -1 -> 반시계 방향
		if (direct == 1)
			current = (current + 7) % 8;
		else
			current = (current + 1) % 8;
	}

	int getNorth() { return data[current]; }

};
Gear gList[4];
void rotate(int gearNumber, int direction);
int main()
{


	for (int i = 0; i < 4; i++)
	{
		char temp[9];
		cin >> temp;
		for (int j = 0; j < 8; j++)
		{
			gList[i].data[j] = temp[j]- '0';
		}
			
	}

	int K;
	cin >> K;

	int a, b;
	while (K--)
	{
		cin >> a >> b;
		rotate(a, b);


		
	}
	

	int ans = 0;
	for (int i = 0; i <= 3; i++)
	{
		ans += pow(2, i) * gList[i].getNorth();
	}
	cout << ans;
}

void rotate(int gearNumber, int direction)
{
	//index + 2 는 오른쪽
	//index + 6 는 왼쪽을 뜻 한다.
	int leftDirect = direction;

	vector<pair<int, int>> rotateList;
	for (int i = gearNumber - 1; i > 0; i--)
	{
		//먼저 현재 녀석의 왼쪽 톱니바퀴의 오른쪽과
		//현재녀석의 왼쪽이 같은지 비교한다.
		if (gList[i - 1].getRight() == gList[i].getLeft())
			break;

		//같지 않을 경우 회전 시킨다.
		//나중에 한꺼번에 회전 시켜야하므로 주석
		//gList[i - 1].rotate(leftDirect = -leftDirect);
		rotateList.push_back({ i - 1, leftDirect = -leftDirect });


		//cout << "왼쪽으로 " << i-1 << endl;
	}
	int rightDirect = direction;
	for (int i = gearNumber - 1; i < 3; i++)
	{
		if (gList[i].getRight() == gList[i+1].getLeft())
			break;

		//gList[i + 1].rotate(rightDirect = -rightDirect);
		rotateList.push_back({ i + 1, rightDirect = -rightDirect });
		//cout << "오른쪽으로 " << i+1 << endl;
	}

	gList[gearNumber - 1].rotate(direction);
	for (auto c : rotateList)
		gList[c.first].rotate(c.second);
}
