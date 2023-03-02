#include <iostream>
#include <iomanip>
using namespace std;

int main()
{   
    int D0[6][6] = {{0,  28,      21,      59,      12, 27     },
                    {7,  0,       24,      INT_MAX, 21, 9      },
                    {9,  32,      0,       13,      11, INT_MAX},
                    {8,  INT_MAX, 5,       0,       16, INT_MAX},
                    {14, 13,      15,      10,      0,  22     },
                    {15, 18,      INT_MAX, INT_MAX, 6,  0      }};

    int S0[6][6] = {{0, 2, 3, 4, 5, 6},
                    {1, 0, 3, 4, 5, 6},
                    {1, 2, 0, 4, 5, 6},
                    {1, 2, 3, 0, 5, 6},
                    {1, 2, 3, 4, 0, 6},
                    {1, 2, 3, 4, 5, 0}};

    for (int k = 0; k < 6; k++) {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                int D = D0[i][k] + D0[k][j];    // путь из i в j если добавим промежуточную k
                if (D0[i][j] > D) {     // если путь без k длиннее то 
                    D0[i][j] = D;       // ставим новое расстояние 
                    S0[i][j] = k + 1;   // +1 потому что проход цикла 0-5, а действия 1-6
                }
            }
        }
    }

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            cout << setw(3) << D0[i][j];
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            cout << setw(3) << S0[i][j];
        }
        cout << endl;
    }
    cout << endl;

    system("pause");
}