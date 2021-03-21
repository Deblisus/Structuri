#include <iostream>
#include <fstream>
#include <map>
using namespace std;

ifstream fin("date.txt");
ifstream fin2("date2.txt");


struct numar{
    int x, y;
    int valoare;
};
struct mat_rara{
    int n, m;
    int nr_elemente;
    numar element[200];
    map<pair<int, int>, int> perechi;
};

int nr = 0;
mat_rara matrici[100];



void citire(){
    while(fin >> matrici[nr].n){
        fin >> matrici[nr].m;
        fin >> matrici[nr].nr_elemente;

        for(int i = 0; i < matrici[nr].nr_elemente; i++){
            fin >> matrici[nr].element[i].x;
            fin >> matrici[nr].element[i].y;
            fin >> matrici[nr].element[i].valoare;

            matrici[nr].perechi[make_pair(matrici[nr].element[i].x, matrici[nr].element[i].y)] = matrici[nr].element[i].valoare;
        }

        nr++;
    }
}

void formatare(mat_rara mat){
    cout << "Matricea are " << mat.n << " linii si " << mat.m << " coloane";
    cout << '\n';
    for(int i = 1; i <= mat.n; i++){
        for(int j = 1; j <= mat.m; j++){
            if(mat.perechi[make_pair(i, j)]){
                cout << mat.perechi[make_pair(i, j)];
            } else {
                cout << 0;
            }
            cout << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

void afisare(){
    for(int k = 0; k < nr; k++){
        formatare(matrici[k]);
    }
}

mat_rara suma_matrici(mat_rara mat1, mat_rara mat2, int operatie){
    mat_rara mat;
    if(mat1.n != mat2.n || mat1.m != mat2.m){
        return mat;
    }

    mat.n = mat1.n;
    mat.m = mat1.m;
    mat.nr_elemente = 0;
    for(int i = 0; i < mat1.nr_elemente; i++){
        pair<int, int> pairr = make_pair(mat1.element[i].x, mat1.element[i].y);
        if(mat2.perechi[pairr]){
            mat.element[mat.nr_elemente].x = mat1.element[i].x;
            mat.element[mat.nr_elemente].y = mat1.element[i].y;
            mat.element[mat.nr_elemente].valoare = mat1.element[i].valoare + mat2.perechi[pairr]*operatie;

            mat.perechi[pairr] = mat.element[mat.nr_elemente].valoare;
        } else {
            mat.element[mat.nr_elemente].x = mat1.element[i].x;
            mat.element[mat.nr_elemente].y = mat1.element[i].y;
            mat.element[mat.nr_elemente].valoare = mat1.element[i].valoare;

            mat.perechi[pairr] = mat.element[mat.nr_elemente].valoare;
        }
        mat.nr_elemente++;
    }
    for(int i = 0; i < mat2.nr_elemente; i++){
        pair<int, int> pairr = make_pair(mat2.element[i].x, mat2.element[i].y);
        if(mat1.perechi[pairr] && !(mat.perechi[pairr])){
            mat.element[mat.nr_elemente].x = mat2.element[i].x;
            mat.element[mat.nr_elemente].y = mat2.element[i].y;
            mat.element[mat.nr_elemente].valoare = mat2.element[i].valoare + mat1.perechi[pairr]*operatie;

            mat.perechi[pairr] = mat.element[mat.nr_elemente].valoare;
            mat.nr_elemente++;
        } else if (!(mat.perechi[pairr])) {
            mat.element[mat.nr_elemente].x = mat2.element[i].x;
            mat.element[mat.nr_elemente].y = mat2.element[i].y;
            mat.element[mat.nr_elemente].valoare = mat2.element[i].valoare;

            mat.perechi[pairr] = mat.element[mat.nr_elemente].valoare;
            mat.nr_elemente++;
        }
    }

    return mat;
}

int main()
{
    bool run = true;
    citire();
    matrici[nr] = suma_matrici(matrici[0], matrici[1], -1);
    nr++;
    afisare();
}
