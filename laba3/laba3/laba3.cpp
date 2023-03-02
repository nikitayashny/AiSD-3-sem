#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{   
    setlocale(LC_ALL, "RUS");
    vector<int> parent(7, -1);         
    int big_num(1000000);
    int matrix[7][7] = { {0,  2,  5, 4,  0,  2,  0},      //A - 1, B - 2, C - 3, D - 4, E - 5, F - 6, G - 7, H - 8, I - 9
                         {4,  0,  0,  1,  0,  4,  1},
                         {2, 1,  0,  1,  2, 1,  1},
                         {0,  3,  0,  0,  0, 3,  2},
                         {0,  1,  0, 0, 0,  3,  4},
                         {3,  0,  0,  3,  0,  0,  1},
                         {5,  0, 2,  1,  0,  2,  0} };

    int pos[7], node[7], min(0), index_min(0);
    for (int i = 0; i < 7; ++i) {     
        pos[i] = big_num;             // заполняем путь большими числами
        node[i] = 0;                  // веришины обозначаем как непройденные
    }

    cout << "Введите стартовую вершину: ";  // назначаем вершину начала
    int start; cin >> start;
    if (start > 7 || start < 1) {
        cout << "Такая вершина в графе отсутствует" << endl;
        return 0;
    }
    pos[start-1] = 0;                 

    for (int i = 0; i < 6; ++i) {     // основной цикл
        min = big_num;
        for (int j = 0; j < 7; ++j) { // находим вершину с минимальным к ней расстоянием
            if (!node[j] && pos[j] < min)
            {
                min = pos[j];
                index_min = j;
            }
        }
        node[index_min] = true;       // помечаем выбранную вершину как пройденную
        for (int j = 0; j < 7; ++j) { // даём всем вершинам смежным с выбранной путь к ней
            if (!node[j] && matrix[index_min][j] > 0 && pos[index_min] != big_num && pos[index_min] + matrix[index_min][j] < pos[j])
            {
                pos[j] = pos[index_min] + matrix[index_min][j];
                parent.at(j) = index_min;  // запоминаем предка вершины j
            }
            // если эта вершина не пройденная и она смежна с выбранной и если сумма веса выбранной вершины и ребра к текущей будет меньше, чем
            // вес текущей на данный момент, то  - меняем значение веса текущей вершины.
        }
    }
    for (int n = 1; n <= 7; n++)
    {
        vector<int>temp;
        for (int i = n - 1; i != -1; i = parent.at(i))temp.push_back(i + 1);    // каждый раз, когда из выбранной вершины v происходит улучшение
        reverse(temp.begin(), temp.end());                                      // расстояния до некоторой вершины to, мы записываем, что предком
        cout << endl << "Путь: " << temp.at(0);                                 // вершины to является вершина v    p[to}=v
        for (int i = 1; i < temp.size(); ++i)cout << " -> " << temp.at(i);

        cout << endl << "Вес: " << pos[n - 1] << endl;                          // пройденное расстояние
    }
}