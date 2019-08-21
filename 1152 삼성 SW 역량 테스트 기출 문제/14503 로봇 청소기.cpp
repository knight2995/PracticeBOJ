#include <iostream>
#include <iomanip>
using namespace std;

int N, M;
int r, c, d;
int board[50][50];

void clean();
void print()
{
	cout << endl << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cout << setw(2) << board[j][i] << " ";
		}
		cout << endl;
	}
}
int ans = 2;
int main()
{
	cin >> N >> M;
	cin >> r >> c >> d;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> board[j][i];
		}
	}

	clean();
	cout << ans-2;
	//cout << endl <<endl;

	//print();

}

void clean()
{
	//현재 방향
	//d가 0인 경우에는 북쪽을, 1인 경우에는 동쪽을, 
	//2인 경우에는 남쪽을, 3인 경우에는 서쪽을 바라보고 있는 것이다.
	
	int nextd[] = { 3,0,1,2 };
	//direct[d] = 다음 진행 방향
	//d의 순환 구조는 0 -> 3 -> 2 -> 1 -> 0
	
	//왼쪽 방향
	int Ldx[] = { -1,0,1,0};
	int Ldy[] = { 0,-1,0,1};

	int Bdx[] = { 0,-1,0,1 };
	int Bdy[] = { 1,0,-1,0 };


	//int *dx = gdx;
	//int *dy = gdy;

	//하이 시작은 항상 +
	//ans++;

	//1. 현재 위치 청소
	board[c][r] = ans++;

	int checkCount = 0;
	while (true)
	{
		

		//2. 현재 방향을 기준으로 왼쪽 방향 탐색




		//2-a. 왼쪽 방향에 아직 청소하지 않은 공간이 존재한다면
		//그 방향으로 회전하고 한칸 전진
		if (board[c + Ldx[d]][r + Ldy[d]] == 0)
		{
			//회전 및 전진
			c += Ldx[d];
			r += Ldy[d];

			//방향 d를 그 쪽으로 변환 
			d = nextd[d];

			//1번으로 진행
			board[c][r] = ans++;
			//print();

			checkCount = 0;
			continue;
		}
		//2-b. 왼쪽 방향에 청소할 공간이 없다면, 그 방향으로 회전하고 2번으로 진행한다.
		else
		{
			d = nextd[d];
			checkCount++;
		}

		//2.c 네 방향 모두 청소거나 벽일 경우에는, 즉 0이 아닐 경우 이면서
		//방향을 유지한채로 한 칸 후진이 가능할 경우 후진 하고 2번으로 돌아간다.
		if (checkCount == 4)
		{
			//2.d 뒤쪽 방향이 벽이라면 후진이 불가하며, 종료한다.
			if (board[c + Bdx[d]][r + Bdy[d]] == 1)
				break;

			//2.c - 방향 유지한채 한칸 후진 후 2번으로 돌아간다.
			checkCount = 0;
			c += Bdx[d];
			r += Bdy[d];
			continue;
		}
		


	}




	/*


	int checkCount = 0;

	bool isGo = true;
	while (true)
	{
		if (isGo)
		{
			if (board[c + dx[d]][r + dy[d]] == 0)
			{
				//위치를 이동
				c += dx[d];
				r += dy[d];

				//청소
				board[c][r] = ans++;
				//ans++;

				//회전
				d = nextd[d];
				checkCount = 0;
				
			}
			//왼쪽 방향이 청소가 불가능 할 경우에는 어떻게 하나 ?
			//회전한다.
			else
			{
				d = nextd[d];
				checkCount++;
			}

			//만약 방향 4군대가 막혀있다 == checkcount = 4
			if (checkCount == 4)
			{
				cout << "후진" << ans<<endl;
				//후진해야 한다. 그전에 뒤가 있나 확인
				c += bdx[d];
				r += bdy[d];

				if (board[c][r] == 1)
					break;
				checkCount = 0;
				isGo = false;

			}


		}
		//후진
		else
		{
			if (board[c + bdx[d]][r + bdy[d]] == 0)
			{
				//위치를 이동
				c += bdx[d];
				r += bdy[d];

				//청소
				board[c][r] = ans++;
				//ans++;

				//회전
				d = nextd[d];
				checkCount = 0;
				isGo = true;
			}
			//왼쪽 방향이 청소가 불가능 할 경우에는 어떻게 하나 ?
			//회전한다.
			else
			{
				d = nextd[d];
				checkCount++;
			}

			//만약 방향 4군대가 막혀있다 == checkcount = 4
			if (checkCount == 4)
			{
				break;

			}
		}
		

		
	}
	*/
	
}