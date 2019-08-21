#include <iostream>
#include <string.h>
using namespace std;

struct Point
{
	int x, y;
};
void spread();
void whip(Point p, int dx[], int dy[]);
void show();

int r, c, t;
Point p1{ -1,0 }, p2{ -1,0 };
int board[51][51];
int changeBoard[51][51];

int main()
{

	cin >> r >> c >> t;

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			cin >> board[i][j];
			if (board[i][j] == -1)
				if (p1.x != -1)
					p2 = { i,j };
				else
					p1 = { i,j };
		}
	}
	//반시계
	int ccwdx[] = { 0,-1,0,1 };//행
	int ccwdy[] = { 1,0,-1,0 }; //열
	//시계
	int cwdx[] = { 0,1,0,-1 };//행
	int cwdy[] = { 1,0,-1,0 }; //열
	while (t--)
	{
		spread();
		//show();
		//반시계
		whip(p1,ccwdx,ccwdy); 

		//시계
		whip(p2,cwdx,cwdy);
		//show();
	}
	
	int sum = 2;

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			sum += board[i][j];
		}
	}
	cout << sum << endl;
}

void spread()
{
	memset(changeBoard, 0, sizeof(changeBoard));

	auto f = [&](int i, int j)
	{ if (p1.x == i && p1.y == j)
		return false;
	if (p2.x == i && p2.y == j)
		return false;
	return true;
	};
		//(bool check(Point p,int i, int j)
	//changeBoard를 만든 뒤에 이를 실제로 적용하는 방향으로 한다.
	
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			int spread = board[i][j] / 5;
			int spreadCount = 0;
			//방향은 5가지 방향// = direct로 표현해서 해도 되고, 그냥 노가다로 해도 가능

			//위로 확산 가능 여부
			if (j - 1 >= 0 && f(i, j - 1))
			{
				changeBoard[i][j - 1] += spread;
				spreadCount++;
			}
			//왼쪽으로 확산 가능 여부
			if (i - 1 >= 0 && f(i - 1, j))
			{
				changeBoard[i - 1][j] += spread;
				spreadCount++;
			}
			//아래로 확산 가능 여부
			if (j + 1 < c && f(i, j + 1))
			{
				changeBoard[i][j+1] += spread;
				spreadCount++;
			}
			//오른쪽으로 확산 가능 여부
			if (i + 1 < r && f(i + 1, j))
			{
				changeBoard[i + 1][j] += spread;
				spreadCount++;
			}
			changeBoard[i][j] -= spread * spreadCount;
		}
	}
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			board[i][j] += changeBoard[i][j];
		}
	}
}
void whip(Point p,int dx[],int dy[])
{
	memset(changeBoard, -1, sizeof(changeBoard));

	//(bool check(Point p,int i, int j)
	//changeBoard를 만든 뒤에 이를 실제 board로 덮어 씌우는 방향으로 한다.


	int cx = p.x;
	int cy = p.y;

	for (int i = 0; i < 4; i++)
	{

		while (true)
		{
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			//조건을 탈출 할 때 - 바깥으로 넘어갈 때 다음 방향
			if (nx >= r || nx < 0 || ny >= c || ny < 0)
				break;

			//에어컨디셔너를 만났을 때
			if (nx == p.x && ny == p.y)
				break;

			//그 외에는 값을 새로 셋팅해준다.
			changeBoard[nx][ny] = board[cx][cy];

			cx = nx;
			cy = ny;

		}
	}



	//
	/*
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			//고려해야 하는건 현재 탐색하고 있는 위치와 공기청정기의 위치와의 상관관계이다.
			//공기청정기와 같은 행일 경우에는 옆으로 밀며
			//마지막 열일 경우 공기청정기 위치에 따라서


			
			//공기 청정기와 같은 행일 경우에
			if ( (i == p1.x || i == p2.x)  && p1.y != j && p2.y != j )
				changeBoard[i][j + 1] = board[i][j];

			//마지막 열의 값 이동
			if (j == c - 1)
			{
				if (i <= p1.x && i > 0)
					changeBoard[i - 1][j] = board[i][j];
				else if (i >= p2.x && i < r)
					changeBoard[i + 1][j] = board[i][j];
			}

			//첫번째 열일 경우
			if (j == 0)
			{
				if (i <= p1.x && i > 0)
					changeBoard[i + 1][j] = board[i][j];
				else if (i >= p2.x && i < r)
					changeBoard[i - 1][j] = board[i][j];

			}

			//첫번째 행 / 마지막 행
			if (i == 0)
			{
				if (j != 0)
					changeBoard[i][j - 1] = board[i][j];
			}
			if (i == r - 1)
			{
				if (j != c )
					changeBoard[i][j - 1] = board[i][j];
			}

			//단 공기 청정기가 있던 곳이라면 무조건 0으로 바꿔버린다.
			changeBoard[p1.x][p1.y] = -1;
			changeBoard[p2.x][p2.y] = -1;

			changeBoard[p1.x][p1.y+1] = 0;
			changeBoard[p2.x][p2.y+1] = 0;


		}
	}
	*/
	//apply
	changeBoard[p.x][p.y + 1] = 0;
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			if(changeBoard[i][j] != -1)
				board[i][j] = changeBoard[i][j];
		}
	}
	
}

void show()
{
	cout << endl;
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}