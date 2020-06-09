/*
Problem 35. Космическая экспедиция
Input file name: input.txt
Output file name: output.txt
Time limit: 1 s
Memory limit: no
В 2004 году обитатели планеты Кремонид организовали космическую экспедицию для полета в соседнюю галактику, где по их расчетам существует планета, пригодная для жизни. На космическом корабле был сконструирован жилой комплекс, куда заселили множество ученых. Жилой комплекс имеет форму прямоугольного параллелепипеда, размера n × m × k. Комплекс разбит на кубические отсеки с размера 1 × 1 × 1, всего n × m × k отсеков. Каждый отсек имеет координаты (x, y, z), соответствующие положению отсека в комплексе, где 1 ≤ x ≤ n, 1 ≤ y ≤ m, 1 ≤ z ≤ k.

Расстоянием между двумя отсеками с координатами (x1, y1, z1) и (x2, y2, z2) назовём число |x1 − x2| + |y1 − y2| + |z1 − z2|. Два отсека находятся в одном ряду, если их координаты отличаются ровно одной компонентой (например, (2, 4, 3) и (2, 6, 3) находятся в одном ряду). Два отсека являются соседними, если расстояние между ними равно 1.

В каждый отсек был установлен персональный компьютер. После взлета жители комплекса решили объединить свои компьютеры в сеть. Был разработан план прокладывания сети, который представляет собой следующую процедуру:

Выбираются два отсека, находящихся в одном ряду. Первый отсек назовем начальным, второй — конечным. Робот, прокладывающий сеть, стартует в начальном отсеке.
На каждом шаге робот передвигается в тот соседний отсек, расстояние от которого до конечного минимально.
При этом он соединяет пары компьютеров в соседних отсеках, через которые он проходит, если это не приводит к образованию цикла. (Циклом называется последовательность компьютеров, в которой первый связан со вторым, второй с третьим и т. д., а последний — с первым.)
Если же соединение приводит к образованию цикла, то робот запоминает координаты этой пары соседних отсеков и не соединяет компьютеры в них между собой.
Робот перемещается, пока не достигнет конечного отсека.
Указанная процедура повторяется t раз. Необходимо определить, какие пары отсеков запомнил робот.
Input
Первая строка содержит четыре числа n, m, k и t, разделённых одним или несколькими пробелами (2 ≤ n, m, k ≤ 100, 1 ≤ t ≤ 20 000). Далее следует t строк, из которых (i + 1)-я описывает пару отсеков, между которыми продвигается робот, и содержит шесть чисел, разделённых одним или несколькими пробелами: первые три числа — координаты начального отсека, оставшиеся три числа — координаты конечного отсека.
Output
Выведите последовательность строк, описывающих пары отсеков, которые запомнил робот в хронологическом порядке. В каждой строке выведите шесть чисел — координаты отсеков в паре в порядке прохождения их роботом. Числа разделены одним пробелом.
Examples
input.txt	
3 3 2 4
1 1 1 2 1 1
1 2 1 2 2 1
1 3 1 1 1 1
2 1 1 2 3 1
output.txt
2 1 1 2 2 1
input.txt	
4 5 6 6
1 1 1 1 1 3
1 1 4 1 4 4
1 1 2 1 1 4
4 1 1 4 1 4
1 1 1 4 1 1
1 1 4 4 1 4
output.txt
1 1 2 1 1 3
3 1 4 4 1 4
*/
#include <iostream>
#include <vector>
#include <fstream>

struct Point
{
    int x;
    int y;
    int z;

};

bool operator == (const Point &c1, const Point &c2)
{
    return (c1.x == c2.x &&
            c1.y== c2.y && c1.z == c2.z);
}


bool operator!= (const Point &c1, const Point &c2)
{
    return !(c1==c2);
}

Point parent[200][200][200];

Point find_set (Point v) {
    if (v == parent[v.x][v.y][v.z])
        return v;
    return find_set (parent[v.x][v.y][v.z]);
}

void union_sets (Point a, Point b) {
    a = find_set (a);
    b = find_set (b);
    if (a != b)
        parent[b.x][b.y][b.z] = a;
}

int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    int n, m, k, t;
    int x1, y1, z1, x2, y2, z2;
    fin >> n >> m >> k >> t;
    for (int i=1; i<=n; i++)
    {
        for (int j =1; j<=m; j++)
        {
            for (int l = 1; l <=k; l++)
            {
                Point point{};
                point.x = i;
                point.y = j;
                point.z = l;
                parent[i][j][l] = point;
            }
        }
    }

    for (int i=0; i<t; i++)
    {
        fin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
        if(x1!=x2)
        {
            int x_min = std::min(x1,x2);
            int x_max= std::max(x1,x2);
            if (x1<x2)
            {
                for (int j = x_min; j<x_max; j++)
                {
                    if(find_set(parent[j][y1][z1])!=find_set(parent[j+1][y1][z1]))
                        union_sets(parent[j][y1][z1],parent[j+1][y2][z1]);
                    else
                        fout << j << ' ' << y1 << ' ' << z1 << ' ' << j + 1 << ' ' << y2 << ' ' << z2 << "\n";

                }


            } else {
                for (int j = x_max; j > x_min; j--) {
                    if(find_set(parent[j][y1][z1])!=find_set(parent[j-1][y1][z1]))
                        union_sets(parent[j][y1][z1],parent[j-1][y1][z1]);
                    else
                        fout << j << ' ' << y1 << ' ' << z1 << ' ' << j-1 << ' ' << y2 << ' ' << z2 << "\n";

                }
            }

        }
        else if(y1!=y2)
        {
            int y_min = std::min(y1,y2);
            int y_max= std::max(y1,y2);
            if (y1<y2)
            {
                for (int j = y_min; j<y_max; j++)
                {
                    if(find_set(parent[x1][j][z1])!=find_set(parent[x1][j+1][z1]))
                        union_sets(parent[x1][j][z1],parent[x1][j+1][z1]);
                    else
                        fout << x1 << ' ' << j << ' ' << z1 << ' ' << x1 << ' ' << j+1 << ' ' << z2 << "\n";
                }

            } else {
                for (int j = y_max; j > y_min; j--) {
                    if(find_set(parent[x1][j][z1])!=find_set(parent[x1][j-1][z1]))
                        union_sets(parent[x1][j][z1],parent[x1][j-1][z1]);
                    else
                        fout << x1 << ' ' << j << ' ' << z1 << ' ' << x1 << ' ' << j-1 << ' ' << z2 << "\n";


                }
            }

        }
        else{
            int z_min = std::min(z1, z2);
            int z_max = std::max(z1, z2);
            if (z1 < z2) {
                for (int j = z_min; j < z_max; j++) {
                    if(find_set(parent[x1][y1][j])!=find_set(parent[x1][y1][j+1]))
                        union_sets(parent[x1][y1][j],parent[x1][y1][j+1]);
                    else
                        fout << x1 << ' ' << y1 << ' ' << j << ' ' << x1 << ' ' << y1 << ' ' << j+1 << "\n";

                }

            } else {
                for (int j = z_max; j > z_min; j--) {
                    if(find_set(parent[x1][y1][j])!=find_set(parent[x1][y1][j-1]))
                        union_sets(parent[x1][y1][j],parent[x1][y1][j-1]);
                    else
                        fout << x1 << ' ' << y1 << ' ' << j << ' ' << x1 << ' ' << y1 << ' ' << j-1 << "\n";

                }
            }
        }
    }
    return 0;
}
