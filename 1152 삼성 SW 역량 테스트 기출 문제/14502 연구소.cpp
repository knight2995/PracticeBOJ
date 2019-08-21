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
	
	//벽 세우기
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			if (board[j][i] == 0)
			{
				//벽을 세우자 = 1 로 바꾼다
				board[j][i] = 1;
				//다음 벽을 세운다.
				makeWall(1);	//하나 세웠으니까 3개째 종료 하면 될듯 ?;
				//이제 가장 먼저 세운 벽을 허문다. -> 0 으로 바꾸고 그 다음 칸 체크
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
				//벽을 세우자 = 1 로 바꾼다
				board[j][i] = 1;
				//다음 벽을 세운다.
				makeWall(cnt + 1);	//하나 세웠으니까 3개째 종료 하면 될듯 ?;
				//이제 가장 먼저 세운 벽을 허문다. -> 0 으로 바꾸고 그 다음 칸 체크
				board[j][i] = 0;
			}
		}
	}

}

void spreadVirus()
{
	//바이러스 퍼트리기

	//map 일단 복사
	
	memcpy(spreadBoard, board, sizeof(board));

	queue<pair<int, int>> queue;

	//전체 영역에 대해서 찾는다.
	//일단 2인 부분을 찾으면 dfs를 통해 찾는다.
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (spreadBoard[j][i] == 2)
			{
				//탐색해야 될 놈들을 queue에 삽입
				queue.push({ j,i });
			}
		}
	}

	while (!queue.empty())
	{
		auto pos = queue.front();
		
		int x = pos.first;
		int y = pos.second;

		//오른쪽
		if ( x+1 < M &&  spreadBoard[x + 1][y] == 0)
		{
			spreadBoard[x + 1][y] = 2;
			queue.push({ x + 1, y });
		}
		//아래
		if ( y + 1 < N && spreadBoard[x][y + 1] == 0)
		{
			spreadBoard[x][y + 1] = 2;
			queue.push({ x , y + 1 });
		}
		//위
		if (y - 1 >= 0 && spreadBoard[x][y - 1] == 0)
		{
			spreadBoard[x][y - 1] = 2;
			queue.push({ x, y - 1 });
		}
		//왼쪽
		if (x - 1 >= 0 && spreadBoard[x - 1][y] == 0)
		{
			spreadBoard[x - 1][y] = 2;
			queue.push({ x - 1,y });
		}
		queue.pop();
	}

	//안전 영역 계산
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
