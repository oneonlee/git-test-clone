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
	//배열에 랜덤한 값을 넣어준다. 지금예시는 값을 인위적으로 넣기 위해 주석처리를 해주었다.
	
	for (int c = 0; c < col; c++)
		dp[0][c] = arr[0][c];
	//처음 0행의 dp값은 배열의 첫 행들의 값과 일치하므로 단순 대입을 해준다.
	for (int r = 1; r < row; r++) {
		for (int c = 0; c < col; c++) {
			//0행에서 점점 올라가면서 전 행의 대각선 전, 바로 전들의 경우를 가져와서 비교한다.
			//b_c는 전 열의 위치를 뜻한다.
			for (int i = 0; i < 3; i++) {
				int b_c = c + d_col[i];
				if (b_c < 0 || b_c >= col)
					continue;
				//현재 r,c의 dp값을 계산, 최대값을 넣어줄때 위치도 저장을 하기 위해 
				//back_tracking에 위치를 저장한다.
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
	//역 추적하면서 위치를 loc 벡터 자료구조에 넣는다.
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