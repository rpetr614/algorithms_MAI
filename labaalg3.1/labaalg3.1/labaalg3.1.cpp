/********************************************************************
*               Информатика и вычислительная техника                *
*-------------------------------------------------------------------*
* Project Type : Win32 Console Application                          *
* Project Name : alglaba3.1                                         *
* File Name : alglaba3.1.cpp                                        *
* Language : C/C++                                                  *
* Programmer(s) : М3О-209Б-22                                       *
*                 Романов П.А                                       *
*                 Усачев Д.А.                                       *
* Modifyed By :                                                     *
* Created : 02.11.2023                                              *
* Comment(s) : ПЕРВАЯ ПРОГРАММА                                     *
*                                                                   *
*                                                                   *
*********************************************************************/
//Подключнеие библиотек
#include <iostream>
#include <climits>
#include <map>
using namespace std;
int const size = 10;
#define INF 99999
/********************************************************************
*             ПРОТОТИПЫ ФУНКЦИЙ                                     *
*********************************************************************/
//Алгоритм Дейкстры
void Dijkstra(int shortest[], int pred[], int Graph[10][10], int start);
//Алгоритм Беллмана-Форда
void BF(int shortest[], int pred[], int start, int Graph[10][10]);
//Алгоритм Флойда-Уоршелла
void FU(int shortest[10][10], int pred[10][10], int Graph[10][10]);
//Печать таблиц pred и shortest
void PrintTable(int Vershina[], int shortest[], int pred[]);
//Печать таблиц pred и shortest(двумерных)
void PrintArrays(int pred[10][10], int shortest[10][10]);
//Алгоритм Прима
void Prima(int Graph[10][10]);
//Алгоритм Крускала
void Kruskal(int Graph[10][10]);
//Поиск мн-ва вершин i
int find(int i);
//Объединение i и j
void unite(int i, int j);
/******************************************************************
*             ОСНОВНАЯ ПРОГРАММА                                  *
*******************************************************************/
int main()
{
    setlocale(LC_ALL, "Russian");//Локализация
    int Vershina[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };//Массив номеров вершин
    int Graph1[10][10] = {{0, 10, 0, 1, 0, 2, 0, 0, 0, 0},//Ориентированный граф (отсутствие путей показано нулями)
                            {0, 0, 5, 0, 0, 0, 0, 0, 0, 9},
                            {0, 0, 0, 0, 3, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 1, 0, 5, 0, 0},
                            {0, 0, 0, 0, 0, 2, 7, 1, 0, 0},
                            {0, 0, 0, 0, 0, 0, 2, 0, 0, 0},
                            {0, 0, 3, 0, 0, 0, 0, 2, 4, 10},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
                            {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                            {3, 0, 3, 0, 0, 0, 0, 0, 0, 0} };
    //Инициализируем массивы shortest1 и pred1 (кратчайших длин и предшествующих вершин)
    int shortest1[10] = {};
    int pred1[10] = {};
    int start1 = 0;
    cout << "Дейкстра" << endl;
    cout << "Введите стартовую вершину: ";
    //Запрашиваем стартовую вершину для алгоритма Дейкстры
    cin >> start1;
    //Выполняем алгоритм Дейкстры и выводим результат
    Dijkstra(shortest1, pred1, Graph1, start1);
    PrintTable(Vershina, shortest1, pred1);
    system("pause");
    //Инициализируем массивы shortest2 и pred2 (кратчайших длин и предшествующих вершин)
    int shortest2[10] = {};
    int pred2[10] = {};
    int start2 = 0;
    cout << endl << "Беллман-Форд" << endl;
    cout << "Введите стартовую вершину: ";
    //Запрашиваем стартовую вершину для алгоритма Беллмана-Форда
    cin >> start2;
    //Выполняем алгоритм Беллмана-Форда и выводим результат
    BF(shortest2, pred2, start2, Graph1);
    PrintTable(Vershina, shortest2, pred2);
    system("pause");
    //Создаем новый граф Graph2 с бесконечными значениями INF
    int Graph2[10][10] = {{0, 10, INF, 1, INF, 2, INF, INF, INF, INF},
                            {INF, 0, 5, INF, INF, INF, INF, INF, INF, 9},
                            {INF, INF, 0, INF, 3, INF, INF, INF, INF, INF},
                            {INF, INF, INF, 0, INF, 1, INF, 5, INF, INF},
                            {INF, INF, INF, INF, 0, 2, 7, 1, INF, INF},
                            {INF, INF, INF, INF, INF, 0, 2, INF, INF, INF},
                            {INF, INF, 3, INF, INF, INF, 0, 2, 4, 10},
                            {INF, INF, INF, INF, INF, INF, INF, 0, INF, 2},
                            {INF, 1, INF, INF, INF, INF, INF, INF, 0, INF},
                            {3, INF, 3, INF, INF, INF, INF, INF, INF, 0} };
    //Инициализируем массивы shortest3 и pred3 (кратчайших длин и предшествующих вершин)
    int shortest3[10][10] = {};
    int pred3[10][10] = {};
    cout << endl << "Флойд-Уоршелл" << endl;
    //Выполняем алгоритм Флойда-Уоршелла и выводим результат
    FU(shortest3, pred3, Graph2);
    PrintArrays(pred3, shortest3);
    system("pause");
    //Создаем новый неориентированный граф Graph3
    int Graph3[10][10] = {
        {0, 10, INF, 1, INF, 2, INF, INF, INF, 3},
        {10, 0, 5, INF, INF, INF, INF, INF, 1, 9},
        {INF, 5, 0, INF, 3, INF, 3, INF, INF, 3},
        {1, INF, INF, 0, INF, 1, INF, 5, INF, INF},
        {INF, INF, 3, INF, 0, 2, 7, 1, INF, INF},
        {2, INF, INF, 1, 2, 0, 2, INF, INF, INF},
        {INF, INF, 3, INF, 7, 2, 0, 2, 4, 10},
        {INF, INF, INF, 5, 1, INF, 2, 0, INF, 2},
        {INF, 1, INF, INF, INF, INF, 4, INF, 0, INF},
        {3, 9, 3, INF, INF, INF, 10, 2, INF, 0}
    };
    //Выполняем алгоритмы Прима и Крускала
    cout << endl << "Прима" << endl;
    Prima(Graph3);
    cout << endl << "Крускал" << endl;
    Kruskal(Graph3);
    return 0;
}//Конец main
//Алгоритм Дейкстры
void Dijkstra(int shortest[], int pred[], int Graph[10][10], int start)
{
    //Инициализация начальной вершины
    shortest[start] = 0;
    pred[start] = -1;
    //Инициализация остальных вершин
    for (int i = 0; i < 10; i++)
    {
        if (i != start)
        {
            shortest[i] = INT_MAX;// Устанавливаем бесконечное расстояние для всех остальных вершин
            pred[i] = -1;//Устанавливаем отсутствие предшественника
        }
    }
    bool visited[10] = { false };//Массив для отслеживания посещенных вершин
    //Проход по всем вершинам
    for (int i = 0; i < 10; i++)
    {
        int u = -1;
        //Поиск непосещенной вершины с наименьшим кратчайшим расстоянием
        for (int j = 0; j < 10; j++)
        {
            if (!visited[j] && (u == -1 || shortest[j] < shortest[u]))
            {
                u = j;//Если вершина не посещена и имеет меньшее расстояние, чем текущая u, то обновляем u
            }
        }
        visited[u] = true;//Помечаем вершину как посещенную
        //Вывод информации о текущем шаге
        cout << "Шаг " << i + 1 << ": Выбрана вершина " << u << ", shortest[" << u << "] = " << shortest[u] << ", pred[" << u << "] = " << pred[u] << endl;
        //Обновление кратчайших расстояний и предшественников соседних вершин
        for (int v = 0; v < 10; v++)
        {
            if (Graph[u][v] != 0)
            {
                //Если есть ребро между u и v
                if (!visited[v] && shortest[u] + Graph[u][v] < shortest[v])
                {
                    //Если новый путь короче, обновляем кратчайшее расстояние и предшественника
                    shortest[v] = shortest[u] + Graph[u][v];
                    pred[v] = u;
                }
            }
        }
    }
    cout << "\nКратчайшие пути:\n";
    for (int i = 0; i < 10; ++i) 
    {
        if (i != start) 
        {
            cout << "Кратчайший путь из " << start << " в " << i << ": ";
            int v = i;
            while (v != start) 
            {
                cout << v << " <- ";
                v = pred[v];
            }
            cout << start << " (Длина пути: " << shortest[i] << ")\n";
        }
    }
}
//Конец Dijkstra
//Алгоритм Беллмана-Форда
void BF(int shortest[], int pred[], int start, int Graph[10][10])
{
    //Инициализация начальной вершины
    shortest[start] = 0;
    pred[start] = -1;
    //Инициализация остальных вершин
    for (int v = 0; v < 10; v++)
    {
        if (v != start)
        {
            //Устанавливаем бесконечное расстояние и отсутствие предшественника для остальных вершин
            shortest[v] = INT_MAX;
            pred[v] = -1;
        }
    }
    //Релаксация ребер для поиска кратчайших путей
    for (int i = 0; i < 10 - 1; i++)
    {
        for (int u = 0; u < 10; u++)
        {
            for (int v = 0; v < 10; v++)
            {
                if (Graph[u][v] != 0 && shortest[u] != INT_MAX && shortest[u] + Graph[u][v] < shortest[v])
                {
                    //Если найден более короткий путь, обновляем кратчайшее расстояние и предшественника
                    shortest[v] = shortest[u] + Graph[u][v];
                    pred[v] = u;
                }
            }
        }
        //Вывод текущих кратчайших расстояний и предшественников после каждой итерации
        cout << endl;
        for (int i = 0; i < 10; ++i)
        {
            cout << "Вершина " << i << ": Кратчайшее расстояние = " << shortest[i] << ", Pred = " << pred[i] << endl;
        }
        cout << endl;
    }
    //Проверка наличия циклов с отрицательным весом
    for (int u = 0; u < 10; u++)
    {
        for (int v = 0; v < 10; v++)
        {
            if (Graph[u][v] != 0 && shortest[u] + Graph[u][v] < shortest[v])
            {
                //Используем алгоритм Беллмана-Форда для обнаружения циклов с отрицательным весом
                bool visited[10] = { false };
                int x = v;
                while (!visited[x])
                {
                    //Помечаем вершины в цикле
                    visited[x] = true;
                    x = pred[x];
                }
                v = pred[x];
                //Восстановление цикла с отрицательным весом
                int cycle[10] = { 0 };
                int index = 0;
                do
                {
                    cycle[index] = v;
                    v = pred[v];
                    index++;
                } while (v != x);
                //Вывод цикла с отрицательным весом
                cout << "Цикл с отрицательным весом: ";
                for (int i = index - 1; i >= 0; --i)
                {
                    cout << cycle[i] << " ";
                }
                cout << endl;
                //Прерываем выполнение после обнаружения первого цикла
                break;
            }
        }
    }
    cout << "\nКратчайшие пути:\n";
    for (int i = 0; i < 10; ++i) 
    {
        if (i != start && pred[i] != -1) 
        {
            cout << "Кратчайший путь из " << start << " в " << i << ": ";
            int v = i;
            while (v != start) 
            {
                cout << v << " <- ";
                v = pred[v];
            }
            cout << start << " (Длина пути: " << shortest[i] << ")\n";
        }
    }
}//Конец BF
//Алгоритм Флойда-Уоршелла
void FU(int shortest[10][10], int pred[10][10], int Graph[10][10])
{
    //Инициализация кратчайших расстояний и предшественников матрицы предшественников
    for (int u = 0; u < 10; u++)
    {
        for (int v = 0; v < 10; v++)
        {
            //Исходно устанавливаем кратчайшее расстояние как вес ребра и предшественника как текущую вершину u
            shortest[u][v] = Graph[u][v];
            if (Graph[u][v] != INF && u != v)
            {
                pred[u][v] = u;
            }
            else
            {
                pred[u][v] = -1;
            }
        }
    }
    //Используем алгоритм Флойда-Уоршелла для нахождения кратчайших путей между всеми парами вершин
    int i, j, k;
    for (k = 0; k < 10; k++)
    {
        for (i = 0; i < 10; i++)
        {
            for (j = 0; j < 10; j++)
            {
                //Если существует более короткий путь через вершину k, обновляем кратчайшее расстояние и предшественника
                if (shortest[i][j] > (shortest[i][k] + shortest[k][j]) && (shortest[k][j] != INF && shortest[i][k] != INF))
                {
                    shortest[i][j] = shortest[i][k] + shortest[k][j];
                    pred[i][j] = pred[k][j];
                }
            }
        }
        //Вывод промежуточных результатов после каждой итерации
        cout << "Итерация: " << k + 1 << ", Промежуточный результат:\n";
        cout << "Shortest:\n";
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 10; y++) {
                if (shortest[x][y] == INF)
                {
                    cout << "INF" << " ";
                }
                else
                {
                    cout << shortest[x][y] << "\t";
                }
            }
            cout << endl;
        }
        cout << "Pred:\n";
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 10; y++) {
                cout << pred[x][y] << " ";
            }
            cout << endl;
        }
    }
    cout << "\nКратчайшие пути:\n";
    for (int i = 0; i < 10; ++i) 
    {
        for (int j = 0; j < 10; ++j) 
        {
            if (i != j && pred[i][j] != -1) 
            {
                cout << "Кратчайший путь из " << i << " в " << j << ": ";
                int v = j;
                while (v != i) 
                {
                    cout << v << " <- ";
                    v = pred[i][v];
                }
                cout << i << " (Длина пути: " << shortest[i][j] << ")\n";
            }
        }
    }
}//Конец FU
//Алгоритм Прима
void Prima(int Graph[10][10])
{
    int versh = 0;//Начальная вершина для построения остовного дерева
    int selected[10] = { false };//Массив для отслеживания выбранных вершин в остовном дереве
    selected[0] = true;//Начинаем с первой вершины
    //Переменные для хранения выбранных ребер
    int x;
    int y;
    int sum_path = 0;//Переменная для хранения суммарного веса пути в остовном дереве
    cout << "Соединенные вершины" << " : " << "Вес пути";
    cout << endl;
    //Построение остовного дерева
    while (versh < 9)
    {
        int min = INF;//Инициализация минимального веса
        //Поиск минимального веса среди ребер, соединяющих выбранные и невыбранные вершины
        x = 0;
        y = 0;
        for (int i = 0; i < 10; i++)
        {
            if (selected[i])
            {
                for (int j = 0; j < 10; j++)
                {
                    if (!selected[j] && Graph[i][j])
                    {
                        //Если нашли ребро с меньшим весом, обновляем переменные
                        if (min > Graph[i][j])
                        {
                            min = Graph[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }
        //Вывод соединенных вершин и веса ребра
        cout << x << " - " << y << " : " << Graph[x][y];
        cout << endl;
        selected[y] = true;//Помечаем выбранную вершину как выбранную
        sum_path = sum_path + Graph[x][y];//Обновляем суммарный вес пути в остовном дереве
        versh++;//Увеличиваем количество выбранных вершин
    }
    //Выводим минимальный вес остовного дерева
    cout << "Минимальный вес остовного дерева: " << sum_path << endl;
}//Конец Prima
int parent[10];
//Поиск мн-ва вершин i
int find(int i) 
{
    //Ищем корень множества
    while (parent[i] != i)
        i = parent[i];
    return i;
}//Конец find
//Объединение i и j
void unite(int i, int j) 
{
    //Находим корни множеств
    int a = find(i);
    int b = find(j);
    parent[a] = b;//Присваиваем одно множество другому
}//Конец unite
//Алгоритм Крускала
void Kruskal(int Graph[10][10]) 
{
    //Инициализация переменных для хранения минимального веса и выбранных вершин
    int mincost = 0;
    int versh_count = 0;
    //Инициализация массива родителей
    for (int i = 0; i < 10; i++)
    {
        parent[i] = i;
    }
    //Построение остовного дерева
    while (versh_count < 9) 
    {
        //Инициализация переменных для хранения минимального веса и выбранных вершин
        int min = INT_MAX; 
        int a = -1;
        int b = -1;
        //Поиск минимального веса среди всех рёбер
        for (int i = 0; i < 10; i++) 
        {
            for (int j = 0; j < 10; j++) 
            {
                //Если вершины не принадлежат одному множеству и вес ребра меньше текущего минимума
                if (find(i) != find(j) && Graph[i][j] < min) 
                {
                    //Обновляем минимум и выбранные вершины
                    min = Graph[i][j];
                    a = i;
                    b = j;
                }
            }
        }
        unite(a, b);//Объединяем множества, содержащие вершины a и b
        cout << "Вершина " << versh_count++ << ":(" << a << ", " << b << ") вес: " << min << endl;//Выводим информацию о выбранном ребре и его весе
        mincost += min;//Обновляем суммарный вес остовного дерева
    }
    cout << "\n Минимальный вес остовного дерева = " << mincost;//Выводим общий минимальный вес остовного дерева
}//Конец Kruskal
//Печать таблиц pred и shortest
void PrintTable(int Vershina[], int shortest[], int pred[])
{
    cout << "Pred" << endl;
    //Вывод номеров вершин
    for (int i = 0; i < 10; i++)
    {
        cout << Vershina[i] << " ";
    }
    cout << endl;
    //Вывод массива предшественников
    for (int i = 0; i < 10; i++)
    {
        cout << pred[i] << " ";
    }
    cout << endl;
    cout << "Shortest" << endl;
    //Вывод номеров вершин
    for (int i = 0; i < 10; i++)
    {
        cout << Vershina[i] << " ";
    }
    cout << endl;
    //Вывод массива кратчайших путей
    for (int i = 0; i < 10; i++)
    {
        cout << shortest[i] << " ";
    }
}//Конец PrintTable
//Печать таблиц pred и shortest(двумерных)
void PrintArrays(int pred[10][10], int shortest[10][10])
{
    //Вывод матрицы предшественников
    cout << "Pred: \n";
    for (int u = 0; u < 10; u++)
    {
        for (int v = 0; v < 10; v++)
        {
            cout << pred[u][v] << "\t";
        }
        cout << endl;
    }
    //Вывод матрицы кратчайших путей
    cout << "\nShortest:\n";
    for (int u = 0; u < 10; u++)
    {
        for (int v = 0; v < 10; v++)
        {
            if (shortest[u][v] == INF)
            {
                cout << "INF" << " ";
            }
            else
            {
                cout << shortest[u][v] << "\t";
            }
        }
        cout << endl;
    }
}//Конец PrintArrays
