#include <iostream>
#include <queue>
#include <algorithm>

int board[8][8];
int spreadBoard[8][8];

int N, M;
int maxCount = 0;

using namespace std;

void makeWall(int cnt);
void spreadVirus();


int main()
{

	cin >> N >> M;

	int k;
	int t = 0;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			cin >> k;
			board[j][i] = k;

		}
	}
	
	//�� �����
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			if (board[j][i] == 0)
			{
				//���� ������ = 1 �� �ٲ۴�
				board[j][i] = 1;
				//���� ���� �����.
				makeWall(1);	//�ϳ� �������ϱ� 3��° ���� �ϸ� �ɵ� ?;
				//���� ���� ���� ���� ���� �㹮��. -> 0 ���� �ٲٰ� �� ���� ĭ üũ
				board[j][i] = 0;
			}
		}
	}


	cout << maxCount << endl;
	return 0;
}

void makeWall(int cnt)
{
	if (cnt == 3)
	{
		spreadVirus();
		return;
	}

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			if (board[j][i] == 0)
			{
				//���� ������ = 1 �� �ٲ۴�
				board[j][i] = 1;
				//���� ���� �����.
				makeWall(cnt + 1);	//�ϳ� �������ϱ� 3��° ���� �ϸ� �ɵ� ?;
				//���� ���� ���� ���� ���� �㹮��. -> 0 ���� �ٲٰ� �� ���� ĭ üũ
				board[j][i] = 0;
			}
		}
	}

}

void spreadVirus()
{
	//���̷��� ��Ʈ����

	//map �ϴ� ����
	
	memcpy(spreadBoard, board, sizeof(board));

	queue<pair<int, int>> queue;

	//��ü ������ ���ؼ� ã�´�.
	//�ϴ� 2�� �κ��� ã���� dfs�� ���� ã�´�.
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (spreadBoard[j][i] == 2)
			{
				//Ž���ؾ� �� ����� queue�� ����
				queue.push({ j,i });
			}
		}
	}

	while (!queue.empty())
	{
		auto pos = queue.front();
		
		int x = pos.first;
		int y = pos.second;

		//������
		if ( x+1 < M &&  spreadBoard[x + 1][y] == 0)
		{
			spreadBoard[x + 1][y] = 2;
			queue.push({ x + 1, y });
		}
		//�Ʒ�
		if ( y + 1 < N && spreadBoard[x][y + 1] == 0)
		{
			spreadBoard[x][y + 1] = 2;
			queue.push({ x , y + 1 });
		}
		//��
		if (y - 1 >= 0 && spreadBoard[x][y - 1] == 0)
		{
			spreadBoard[x][y - 1] = 2;
			queue.push({ x, y - 1 });
		}
		//����
		if (x - 1 >= 0 && spreadBoard[x - 1][y] == 0)
		{
			spreadBoard[x - 1][y] = 2;
			queue.push({ x - 1,y });
		}
		queue.pop();
	}

	//���� ���� ���
	int count = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (spreadBoard[j][i] == 0)
			{
				count++;
			}
		}
	}

	maxCount = max(maxCount, count);

}
