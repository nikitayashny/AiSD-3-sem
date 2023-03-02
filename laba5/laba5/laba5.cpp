//#include <iostream>
//using namespace std;
//
//int main() {
//    setlocale(LC_ALL, "ru");
//
//    int arr[8][8] = { {0, 2,  0,  8,  2,  0,  0, 0}, 
//                      {2, 0,  3,  10, 5,  0,  0, 0},
//                      {0, 3,  0,  0,  12, 0,  0, 7},
//                      {8, 10, 0,  0,  14, 3,  1, 0},
//                      {2, 5,  12, 14, 0,  11, 4, 8},
//                      {0, 0,  0,  3,  11, 0,  6, 0},
//                      {0, 0,  0,  1,  4,  6,  0, 9},
//                      {0, 0,  7,  0,  8,  0,  9, 0} };
//
//     для Прима
//    int n = 8;
//    bool* visited = new bool[n];
//    memset(visited, false, sizeof(bool) * n);   // заполняем все false
//    visited[0] = true;  // открываем доступ первой строки матрицы
//
//     для Краскала
// 
//
//
//    
//    int choose;
//    cout << "Выберите алгоритм: 1 - Прима, 2 - Краскала" << endl; cin >> choose;
//    switch (choose) 
//    {
//        case 1:  
//            for (int l = 0; l < n - 1; l++) {   // l < n -1 потому что рёбер на 1 меньше
//                int minx = -1, miny = -1;
//                for (int i = 0; i < n; i++) {
//                    if (visited[i] == true) {   // проверяем доступна ли строка для проверки
//                        for (int j = 0; j < n; j++) {
//                            if (!visited[j] && arr[i][j] > 0 && (miny == -1 || arr[i][j] < arr[miny][minx])) {  // если столбец не посещён и элемент в нём больше 0 и либо miny = -1 либо текущий элемент меньше прошлого назначенного
//                                miny = i, minx = j; // minx строка miny столбец
//                            }
//                        }
//                    }
//                }
//                visited[minx] = true;
//                cout << miny + 1 << " -> " << minx + 1 << endl; // +1 потому что массив
//            }
//            delete[] visited;
//            break;
//        case 2:
//
//            break;
//        default:
//            cout << "Некорректные данные" << endl;
//            break;
//    }
//    system("pause");
//}


#include <iostream>
using namespace std;

struct Node {
    int n1, n2; // направление
    int w;      // вес ребра
}edges[16];

bool visited[8];

int main()
{  
    setlocale(LC_ALL, "ru");

    int length[16] = {2, 3, 8, 3, 6, 9, 7, 2, 8, 12, 11, 10, 14, 1, 5, 4};
    int EDGES[16][2] = { {1, 2},
  
                        {2, 3},
        
                        {1, 4},
       
                        {4, 6},
       
                        {6, 7},
    
                        {7, 8},
     
                        {8, 3},
    
                        {1 ,5},
     
                        {5, 8},
     
                        {3, 5},
     
                        {5, 6},
     
                        {2, 4},
       
                        {4, 5},
 
                        {4, 7},
    
                        {2, 5},

                        {5, 7}
  };

    for (int i = 0; i < 16 - 1; i++) {              // отсортировали рёбра
        for (int j = 0; j < 16 - i - 1; j++) {
            if (length[j] > length[j + 1]) {
                swap(length[j], length[j + 1]);
                swap(EDGES[j], EDGES[j + 1]);
            }
        }
    }

    for (int i = 0; i < 16; i++) {                  // добавили рёбра в структуру
        int j = 0;
        edges[i].n1 = EDGES[i][j];
        edges[i].n2 = EDGES[i][j + 1];
        edges[i].w = length[i];
    }

    int weight = 0;
    for (int i = 0; i < 16; i++)
    {
        if (!visited[edges[i].n1 - 1] || !visited[edges[i].n2 - 1])
        {
            weight += edges[i].w;
            visited[edges[i].n1 - 1] = true; 
            visited[edges[i].n2 -1 ] = true;
            cout << edges[i].n1 << " -> " << edges[i].n2 << endl;
        }
        
    }
    system("pause");
}