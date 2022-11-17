#include "metromap.h"
#include <QApplication>

//------------
#include <QVector>
#include <QDebug>
#include <QHash>
#include <QSet>
#include <QPair>
#include <QQueue>
#include <memory>
#include "line.h"
#include "station.h"

void print(QVector<QPair<int, int> >& v_){
    QString res;
    QString s;
    for(auto v: v_){
        res += s.setNum(v.second) + '    ';
    }
    qDebug() << res;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MetroMap w;
    w.show();

    return a.exec();


    //=====================//
    //initialization of matrix
/*    QVector<QVector<int> > matrix;
    matrix.resize(11);
    for (auto& v: matrix){
        v.resize(11);
    }

    for(auto i = 0; i < matrix.size(); i++){
        for(auto j = 0; j < matrix[i].size(); j++){
            matrix [i][j] = -1;
            if(i == j){
                matrix[i][j] = 0;
            }
        }
    }

    matrix[0][1] = 4; matrix[1][0] = 4;
    matrix[0][2] = 7; matrix[2][0] = 7;
    matrix[0][3] = 1; matrix[3][0] = 1;
    matrix[1][4] = 2; matrix[4][1] = 2;
    matrix[2][4] = 8; matrix[4][2] = 8;
    matrix[2][5] = 5; matrix[5][2] = 5;
    matrix[2][6] = 6; matrix[6][2] = 6;
    matrix[3][6] = 3; matrix[6][3] = 3;
    matrix[4][7] = 9; matrix[7][4] = 9;
    matrix[5][8] = 1; matrix[8][5] = 1;
    matrix[6][8] = 3; matrix[8][6] = 3;
    matrix[6][9] = 2; matrix[9][6] = 2;
    matrix[7][10] = 6; matrix[10][7] = 6;
    matrix[9][10] = 4; matrix[10][9] = 4;


    int start = 7;
    QVector<QPair<int, int> > vertex_coasts_;
    for(int i = start; i < start + matrix.size(); i++){
        vertex_coasts_.append(qMakePair(i%matrix.size(),1000));
    }

    vertex_coasts_[0].second = 0;

    QQueue<QPair<int, int> > q;
    QSet<QPair<int, int> > visited;
    for(auto& vertex: vertex_coasts_){
        int i = vertex_coasts_[0].first;
        int j = vertex.first;
        if(i != j and matrix[i][j] != -1){
            if(matrix[i][j] + vertex_coasts_[0].second < vertex.second){
                vertex.second = matrix[i][j] + vertex_coasts_[0].second;
            }
            q.enqueue(vertex);
        }
    }
    visited.insert(vertex_coasts_[0]);




    while(!q.empty()){
        QPair<int, int> vertex = q.dequeue();
        if(visited.find(vertex) == visited.end()){
            visited.insert(vertex);
            int i = vertex.first;
            for(auto& vertex_neighbor: vertex_coasts_){
                int j = vertex_neighbor.first;
                if(matrix[i][j] != -1 and matrix[i][j] + vertex.second < vertex_neighbor.second){
                    vertex_neighbor.second = matrix[i][j] + vertex.second;
                    q.enqueue(vertex_neighbor);
                }
            }
        }
    }

    Line line("first");
    Station* st = line.addStation("st");
    Station* st2 = line.addStation("2th", st);
    qDebug() <<"end creating" << st << st2;

    auto l = std::make_shared<Line>("first line");

    return 0;*/
}
