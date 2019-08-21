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
	//���� ����
	//d�� 0�� ��쿡�� ������, 1�� ��쿡�� ������, 
	//2�� ��쿡�� ������, 3�� ��쿡�� ������ �ٶ󺸰� �ִ� ���̴�.
	
	int nextd[] = { 3,0,1,2 };
	//direct[d] = ���� ���� ����
	//d�� ��ȯ ������ 0 -> 3 -> 2 -> 1 -> 0
	
	//���� ����
	int Ldx[] = { -1,0,1,0};
	int Ldy[] = { 0,-1,0,1};

	int Bdx[] = { 0,-1,0,1 };
	int Bdy[] = { 1,0,-1,0 };


	//int *dx = gdx;
	//int *dy = gdy;

	//���� ������ �׻� +
	//ans++;

	//1. ���� ��ġ û��
	board[c][r] = ans++;

	int checkCount = 0;
	while (true)
	{
		

		//2. ���� ������ �������� ���� ���� Ž��




		//2-a. ���� ���⿡ ���� û������ ���� ������ �����Ѵٸ�
		//�� �������� ȸ���ϰ� ��ĭ ����
		if (board[c + Ldx[d]][r + Ldy[d]] == 0)
		{
			//ȸ�� �� ����
			c += Ldx[d];
			r += Ldy[d];

			//���� d�� �� ������ ��ȯ 
			d = nextd[d];

			//1������ ����
			board[c][r] = ans++;
			//print();

			checkCount = 0;
			continue;
		}
		//2-b. ���� ���⿡ û���� ������ ���ٸ�, �� �������� ȸ���ϰ� 2������ �����Ѵ�.
		else
		{
			d = nextd[d];
			checkCount++;
		}

		//2.c �� ���� ��� û�Ұų� ���� ��쿡��, �� 0�� �ƴ� ��� �̸鼭
		//������ ������ä�� �� ĭ ������ ������ ��� ���� �ϰ� 2������ ���ư���.
		if (checkCount == 4)
		{
			//2.d ���� ������ ���̶�� ������ �Ұ��ϸ�, �����Ѵ�.
			if (board[c + Bdx[d]][r + Bdy[d]] == 1)
				break;

			//2.c - ���� ������ä ��ĭ ���� �� 2������ ���ư���.
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
				//��ġ�� �̵�
				c += dx[d];
				r += dy[d];

				//û��
				board[c][r] = ans++;
				//ans++;

				//ȸ��
				d = nextd[d];
				checkCount = 0;
				
			}
			//���� ������ û�Ұ� �Ұ��� �� ��쿡�� ��� �ϳ� ?
			//ȸ���Ѵ�.
			else
			{
				d = nextd[d];
				checkCount++;
			}

			//���� ���� 4���밡 �����ִ� == checkcount = 4
			if (checkCount == 4)
			{
				cout << "����" << ans<<endl;
				//�����ؾ� �Ѵ�. ������ �ڰ� �ֳ� Ȯ��
				c += bdx[d];
				r += bdy[d];

				if (board[c][r] == 1)
					break;
				checkCount = 0;
				isGo = false;

			}


		}
		//����
		else
		{
			if (board[c + bdx[d]][r + bdy[d]] == 0)
			{
				//��ġ�� �̵�
				c += bdx[d];
				r += bdy[d];

				//û��
				board[c][r] = ans++;
				//ans++;

				//ȸ��
				d = nextd[d];
				checkCount = 0;
				isGo = true;
			}
			//���� ������ û�Ұ� �Ұ��� �� ��쿡�� ��� �ϳ� ?
			//ȸ���Ѵ�.
			else
			{
				d = nextd[d];
				checkCount++;
			}

			//���� ���� 4���밡 �����ִ� == checkcount = 4
			if (checkCount == 4)
			{
				break;

			}
		}
		

		
	}
	*/
	
}