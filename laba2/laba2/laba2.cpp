#include <iostream>
#include <fstream>
#include <list> 
#include <algorithm> 

using namespace std;
int dfs(int** graph, const int n, int from, const int to, int* visited, int* path);
bool bfs(int** graph, int n, int to, int* visited, list<int>& buffer, int* parents); 
void print_path(int from, int to, int* parents, ofstream& ofst); 

int main() {
    setlocale(LC_ALL, "rus");
    char filenamein[] = "in.txt";
    char filenameout[] = "out.txt";

    ifstream fin(filenamein);
    ofstream fout(filenameout);
    if (!fin || !fout) {
        cout << "ошибка при открытие файла\n";
        system("pause");
        return 1;
    }

    int n, m;
    fin >> n >> m;
    int from, to;
    fin >> from >> to;
    from--; to--;

    int** graph = new int* [n];
    int* visited = new int[n];
    int* path = new int[n];
    int* parents = new int[n]; 

    for (int i = 0; i < n; i++) {
        graph[i] = new int[n];
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    for (int i = 0; i < m; i++)
    {
        int a, b;
        fin >> a >> b;
        graph[a - 1][b - 1] = graph[b - 1][a - 1] = 1;
    }

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    int choose;
    cout << "Выберите вид поиска: 1 - в глубину, 2 - в ширину." << endl;
    cin >> choose;

    int path_size;

    list<int> buffer;
    buffer.push_back(from);

    switch (choose)
    {
    case(1):
        path_size = dfs(graph, n, from, to, visited, path);
        if (path_size < 0) {
            fout << "Путь не существует";
        }
        else {
            for (int i = path_size; i >= 0; --i) {
                fout << path[i] + 1;
                if (i == 0)
                    fout << endl;
                else
                    fout << " -> ";
            }
        }
        break;
    case(2):
        if (false == bfs(graph, n, to, visited, buffer, parents)) {
            fout << "Путь не существует" << endl;
        }
        else {
            print_path(from, to, parents, fout);
        }
        break;
    default:
        break;
    }

    for (int i = 0; i < n; i++)
        delete[] graph[i];

    delete[] graph;
    delete[] visited;
    delete[] path;
    delete[] parents;

    fin.close();
    fout.close();
}

int dfs(int** graph, const int n, int from, const int to, int* visited, int* path) {
    if (visited[from] == true)
        return -1;
    visited[from] = true;

    if (from == to) {
        path[0] = to;
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        if (graph[from][i] == 0)
            continue;
        int path_size = dfs(graph, n, i, to, visited, path);
        if (path_size < 0)
            continue;
        path[path_size + 1] = from;
        return path_size + 1;
    }
    return -1;
}

bool bfs(int **graph, int n, int to, int* visited, list<int>& buffer, int* parents) {
    if (buffer.empty())
        return false;
    int from = buffer.front();
    buffer.pop_front();
    visited[from] = true;
    if (from == to) {
        return true;
    }
    for (int i = 0; i < n; ++i) {
        if (graph[from][i] == 0)
            continue;
        if (visited[i] == true)
            continue;
        if (find(buffer.begin(), buffer.end(), i) != buffer.end())
            continue;
        parents[i] = from;
        buffer.push_back(i);
    }
    return bfs(graph, n, to, visited, buffer, parents);
}
void print_path(int from, int to, int* parents, ofstream& ofst) {
    if (to == from) {
        ofst << to+1;
        return;
    }
    int prefrom = parents[to];
    print_path(from, prefrom, parents, ofst);
    ofst << " -> " << to+1;
}