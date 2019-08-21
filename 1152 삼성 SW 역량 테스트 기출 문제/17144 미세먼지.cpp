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
	//�ݽð�
	int ccwdx[] = { 0,-1,0,1 };//��
	int ccwdy[] = { 1,0,-1,0 }; //��
	//�ð�
	int cwdx[] = { 0,1,0,-1 };//��
	int cwdy[] = { 1,0,-1,0 }; //��
	while (t--)
	{
		spread();
		//show();
		//�ݽð�
		whip(p1,ccwdx,ccwdy); 

		//�ð�
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
	//changeBoard�� ���� �ڿ� �̸� ������ �����ϴ� �������� �Ѵ�.
	
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			int spread = board[i][j] / 5;
			int spreadCount = 0;
			//������ 5���� ����// = direct�� ǥ���ؼ� �ص� �ǰ�, �׳� �밡�ٷ� �ص� ����

			//���� Ȯ�� ���� ����
			if (j - 1 >= 0 && f(i, j - 1))
			{
				changeBoard[i][j - 1] += spread;
				spreadCount++;
			}
			//�������� Ȯ�� ���� ����
			if (i - 1 >= 0 && f(i - 1, j))
			{
				changeBoard[i - 1][j] += spread;
				spreadCount++;
			}
			//�Ʒ��� Ȯ�� ���� ����
			if (j + 1 < c && f(i, j + 1))
			{
				changeBoard[i][j+1] += spread;
				spreadCount++;
			}
			//���������� Ȯ�� ���� ����
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
	//changeBoard�� ���� �ڿ� �̸� ���� board�� ���� ����� �������� �Ѵ�.


	int cx = p.x;
	int cy = p.y;

	for (int i = 0; i < 4; i++)
	{

		while (true)
		{
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			//������ Ż�� �� �� - �ٱ����� �Ѿ �� ���� ����
			if (nx >= r || nx < 0 || ny >= c || ny < 0)
				break;

			//��������ųʸ� ������ ��
			if (nx == p.x && ny == p.y)
				break;

			//�� �ܿ��� ���� ���� �������ش�.
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
			//����ؾ� �ϴ°� ���� Ž���ϰ� �ִ� ��ġ�� ����û������ ��ġ���� ��������̴�.
			//����û����� ���� ���� ��쿡�� ������ �и�
			//������ ���� ��� ����û���� ��ġ�� ����


			
			//���� û����� ���� ���� ��쿡
			if ( (i == p1.x || i == p2.x)  && p1.y != j && p2.y != j )
				changeBoard[i][j + 1] = board[i][j];

			//������ ���� �� �̵�
			if (j == c - 1)
			{
				if (i <= p1.x && i > 0)
					changeBoard[i - 1][j] = board[i][j];
				else if (i >= p2.x && i < r)
					changeBoard[i + 1][j] = board[i][j];
			}

			//ù��° ���� ���
			if (j == 0)
			{
				if (i <= p1.x && i > 0)
					changeBoard[i + 1][j] = board[i][j];
				else if (i >= p2.x && i < r)
					changeBoard[i - 1][j] = board[i][j];

			}

			//ù��° �� / ������ ��
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

			//�� ���� û���Ⱑ �ִ� ���̶�� ������ 0���� �ٲ������.
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