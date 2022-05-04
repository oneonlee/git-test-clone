#include<iostream>
#include<vector>
#define INF 104
using namespace std;

int dp[INF][INF];
int arr[INF][INF]={
{3, 4, 9, -2, 2, 51, -23, 2, -1},
{223, 7, 8, -11, 5, -99, 2, 3, -4},
{2, 51, -23, -23, 6, 3, 2, 4, 5},
{5, -99, 2, -1, 32, 2, 5, -99, 2},
{6, 3, 3, -4, 2, -1, 6, 3, 3},
{32, 2, 4, 5, 3, -4, 2, -1, 4},
{4, 4, 23, 6, 2, -1, 3, -4, 34},
{78, 32, 1, 7, 3, -4, -23, -23, 6},
};
pair<int, int> back_tracking[INF][INF];
int row, col;
int d_col[3] = { -1,0,1 };

int main() {
	cin >> row >> col;
	/*
	srand(time(NULL));
	for (int r = 0; r < row; r++)
		for (int c = 0; c < col; c++)
			arr[r][c] = rand() % 40;
	*/		
	//�迭�� ������ ���� �־��ش�. ���ݿ��ô� ���� ���������� �ֱ� ���� �ּ�ó���� ���־���.
	
	for (int c = 0; c < col; c++)
		dp[0][c] = arr[0][c];
	//ó�� 0���� dp���� �迭�� ù ����� ���� ��ġ�ϹǷ� �ܼ� ������ ���ش�.
	for (int r = 1; r < row; r++) {
		for (int c = 0; c < col; c++) {
			//0�࿡�� ���� �ö󰡸鼭 �� ���� �밢�� ��, �ٷ� ������ ��츦 �����ͼ� ���Ѵ�.
			//b_c�� �� ���� ��ġ�� ���Ѵ�.
			for (int i = 0; i < 3; i++) {
				int b_c = c + d_col[i];
				if (b_c < 0 || b_c >= col)
					continue;
				//���� r,c�� dp���� ���, �ִ밪�� �־��ٶ� ��ġ�� ������ �ϱ� ���� 
				//back_tracking�� ��ġ�� �����Ѵ�.
				if (dp[r - 1][b_c] > dp[r][c]) {
					dp[r][c] = dp[r - 1][b_c];
					back_tracking[r][c] = { r - 1,b_c };
				}
				dp[r][c] = max(dp[r][c], dp[r - 1][b_c]);
			}
			dp[r][c] += arr[r][c];
		}
	}
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < col; c++) {
			cout << arr[r][c] << " ";
		}
		cout << "\n";
	}
	cout << "\n\n";
	int result = 0;
	pair<int, int> max_loc;
	vector<pair<int, int>> loc_list;
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < col; c++) {
			cout << dp[r][c] << " ";
			if (result < dp[r][c]) {
				result = dp[r][c];
				max_loc = { r,c };
			}
		}
		cout << "\n";
	}
	//�� �����ϸ鼭 ��ġ�� loc ���� �ڷᱸ���� �ִ´�.
	pair<int, int> loc = max_loc;
	loc_list.push_back({ max_loc.first,max_loc.second });
	while (true) {
		loc = back_tracking[loc.first][loc.second];
		loc_list.push_back({ loc.first,loc.second });
		if (loc.first == 0)
			break;
	}
	for (int i = loc_list.size() - 1; i >= 0; i--) {
		cout << loc_list[i].first << " " << loc_list[i].second << "\n";
	}
	return 0;
}