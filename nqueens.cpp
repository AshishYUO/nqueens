#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

short int ChessBoard[100][100] = {0};
short int Location[100] = {0};
short int startRow = 1;
bool Row[100] = {0};
bool FrontSlashedDiagonal[201] = {0};
bool BackSlashedDiagonal[201] = {0};

bool ifDanger(short int i, short int j, short int n) {
    return !Row[i] && !FrontSlashedDiagonal[i+j] && !BackSlashedDiagonal[((n<<1)-1)+i-j];
}

void MarkDangerScore(short int i, short int j, short int n, bool mark_with) {
    FrontSlashedDiagonal[i+j] = mark_with;
    BackSlashedDiagonal[((n<<1)-1)+i-j] = mark_with;
    Row[i] = mark_with;
}

short int Start (short int n) {
    int i = startRow;
    while (i <= n && Row[i]) {++i;}
    return i > 0 ? i : 1;
}

bool NQueensBranching(short int n, short int j) {
    for(short int i = startRow; i <= n; i++) {
        ChessBoard[i][j] = 1;
        Location[j] = i;
        if(ifDanger(i, j, n)) {
            if(j == n) 
                return true;
            int temp = startRow;
            MarkDangerScore(i, j, n, true);
            startRow = Start(n);
            bool ans = NQueensBranching(n, j+1);
            if(!ans) {
                Location[j] = 0;
                MarkDangerScore(i, j, n, false);
                startRow = temp;
                ChessBoard[i][j] = 0;
            }
            else 
                return true;
        }
        else {
            Location[j] = 0;
            ChessBoard[i][j] = 0;
        }
    }
    return false;
}

bool IsAtDiagonal1(short int i, short int j, short int n) {
    for(short int k = 1; k <= n; k++) {
        if(k != j && Location[k] != 0 && abs(Location[k]-i) == abs(k-j))
            return true;
    }
    return false;
}

bool NQueens(short int n, short int j) {
    for(short int i = 1; i <= n; i++) {
        ChessBoard[i][j] = 1;
        Location[j] = i;
        if(!Row[i] && !IsAtDiagonal1(i, j, n)) {
            if(j == n) 
                return true;
            Row[i] = true;
            bool ans = NQueens(n, j+1);
            if(ans == false) {
                Location[j] = 0;
                Row[i] = false;
                ChessBoard[i][j] = 0;
            }
            else 
                return true;
        }
        else {
            Location[j] = 0;
            ChessBoard[i][j] = 0;
        }
    }
    return false;
}

int main() {
    short int n;
    cin >> n;

    time_point <system_clock> start, end; 

    for(short int i = 1; i <= n; i++)
        Location[i] = 0;
    
    start = system_clock::now();
    bool ans = NQueensBranching(n, 1);
    end = system_clock::now();
    for(short int i = 1; i <= n; i++) {
        for(short int j = 1; j <= n; j++)
            cout << ChessBoard[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";
    duration <double> time = (end-start);

    cout << "Time using Branch and Bound: " << time.count() << "s" << endl;
    startRow = 1;
    for(short int i = 1; i <= n; i++) {
        Location[i] = 0;
        Row[i] = false;
        for(short int j = 0; j < n; j++)
            ChessBoard[i][j] = 0;
    }

    start = system_clock::now();
    ans = NQueens(n, 1);
    end = system_clock::now();

    for(short int i = 1; i <= n; i++) {
        for(short int j = 1; j <= n; j++) 
            cout << ChessBoard[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";
    time = (end-start);

    cout << "Time using backtracking: " << time.count() << "s" << endl;

    cin >> n;
    return 0;
}