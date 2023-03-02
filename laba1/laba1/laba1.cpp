#include <iostream>
#include <Windows.h>
using namespace std;

void hanoi(int i, int k, int n)
{
    if (n == 1) {
        cout << "Передвинуть диск 1 со стержня " << i << " на стержень " << k << ".\n";
    }
    else {
        int tmp = 6 - i - k; 			
        hanoi(i, tmp, n - 1);
        cout << "Передвинуть диск " << n << " со стержня " << i << " на стержень " << k << ".\n";
        hanoi(tmp, k, n - 1);
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int n,k;

    cout << "Введите число дисков: \n";
    cin >> n;
    cout << "Введите стержень: \n";
    cin >> k;

    hanoi(1, k, n);
}