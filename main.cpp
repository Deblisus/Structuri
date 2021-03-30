#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <stdlib.h>
using namespace std;

ifstream fin("date.txt");
ifstream fin2("date2.txt");

void fun(){
    cout << " ____ ____ ____ ____ ____ ____ \n";
    cout << "||M |||a |||t |||r |||i |||x ||\n";
    cout << "||__|||__|||__|||__|||__|||__||\n";
    cout << "|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|\n";
    cout << '\n';
}

struct numar{
    int x, y;
    int valoare;
};
struct mat_rara{
    int n, m;
    int nr_elemente;
    numar element[200];
    int val[30][30];
};

bool run = true;

int nr = 1;
mat_rara matrici[100];

int process_input(int meniu = 1, string mesaj = "Alege optiunea: "){
    cout << mesaj;

    char input[11];
    cin.get(input, 10);
    cin.get();

    int num = atoi(input);

    if(!num){
        cout << "Valoare incorecta! Incearca din nou. \n";
        return process_input(meniu, mesaj);
    }
    if(meniu){
        if(meniu == -1 && num == 0){
            cout << "Valoare incorecta! Incearca din nou. \n";
            return process_input(meniu, mesaj);
        }
        if(meniu == 1 && num > 9 || num < -1){
            cout << "Valoare incorecta! Incearca din nou. \n";
            return process_input(meniu, mesaj);
        }
    } else {
        if(num > nr || num < 1){
            cout << "Valoare incorecta! Incearca din nou. \n";
            return process_input(meniu, mesaj);
        }
    }
    return num;
}

void citire(){
    while(fin >> matrici[nr].n){
        fin >> matrici[nr].m;
        fin >> matrici[nr].nr_elemente;

        for(int i = 1; i <= matrici[nr].n; i++){
            for(int j = 1; j <= matrici[nr].m; j++){
                matrici[nr].val[i][j] = 0;
            }
        }

        for(int i = 1; i <= matrici[nr].nr_elemente; i++){
            fin >> matrici[nr].element[i].x;
            fin >> matrici[nr].element[i].y;
            fin >> matrici[nr].element[i].valoare;

            matrici[nr].val[matrici[nr].element[i].x][matrici[nr].element[i].y] = matrici[nr].element[i].valoare;
        }

        nr++;
    }
    nr--;
}

void formatare(mat_rara mat, int id){
    if(id != 1) cout << "````````````````````````````````````````````````````````````````````` \n";

    cout << "Matricea " << id << " are " << mat.n << " linii si " << mat.m << " coloane";
    cout << '\n';
    for(int i = 1; i <= mat.n; i++){
        for(int j = 1; j <= mat.m; j++){
            cout << mat.val[i][j];
            cout << ' ';
        }
        cout << '\n';
    }
    if(id != nr) cout << '\n';
}

void formatare_element(numar x){
    cout << "(" << x.x << ", " << x.y << ") = " << x.valoare << '\n';
}

void afisare(){
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    cout << '\n';
    for(int k = 1; k <= nr; k++){
        formatare(matrici[k], k);
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    cout << '\n' << '\n';
}

bool mat_simetrica(mat_rara mat){
    for(int i = 1; i <= mat.nr_elemente; i++){
        int x = mat.element[i].x;
        int y = mat.element[i].y;
        if(mat.val[x][y] != mat.val[y][x])
            return false;
    }
    return true;
}

void inmultire_cu_factor(mat_rara &mat, int factor){
    for(int i = 1; i <= mat.nr_elemente; i++){
        int x = mat.element[i].x;
        int y = mat.element[i].y;

        mat.val[x][y] *= factor;
        mat.element[i].valoare = mat.val[x][y];
    }
}

mat_rara inmultire_matrici(mat_rara mat1, mat_rara mat2){
    mat_rara mat;

    if(mat1.m != mat2.n){
        mat.n = -1;
        mat.m = -1;

        return mat;
    }

    mat.n = mat1.n;
    mat.m = mat2.m;
    mat.nr_elemente = 0;

    for(int i = 1; i <= mat.n; i++){
        for(int j = 1; j <= mat.m; j++){
            int sum = 0;
            for(int k = 1; k <= mat1.m; k++){
                sum += mat1.val[i][k] * mat2.val[k][j];
            }
            mat.val[i][j] = sum;

            if(sum != 0){
                mat.nr_elemente++;
                mat.element[mat.nr_elemente].x = i;
                mat.element[mat.nr_elemente].y = j;
                mat.element[mat.nr_elemente].valoare = mat.val[i][j];
            }
        }
    }

    return mat;
}

mat_rara suma_matrici(mat_rara mat1, mat_rara mat2, int operatie){
    mat_rara mat;
    if(mat1.n != mat2.n || mat1.m != mat2.m){
        mat.n = -1;
        mat.m = -1;

        return mat;
    }

    mat.n = mat1.n;
    mat.m = mat1.m;
    mat.nr_elemente = 0;

    for(int i = 1; i <= mat.n; i++){
        for(int j = 1; j <= mat.m; j++){
            mat.val[i][j] = mat1.val[i][j] + mat2.val[i][j] * operatie;
            if(mat.val[i][j] != 0){
                mat.nr_elemente++;
                mat.element[mat.nr_elemente].x = i;
                mat.element[mat.nr_elemente].y = j;
                mat.element[mat.nr_elemente].valoare = mat.val[i][j];
            }
        }
    }

    return mat;
}

void meniu(){
    cout << "Ce doresti sa faci?: \n";
    cout << "1. Afiseaza matricile \n";
    cout << "2. Afiseaza o singura matrice \n";
    cout << "3. Afiseaza doar valorile nenule dintr-o matrice rara \n";
    cout << "4. Verifica daca o matrice este simetrica pe diagonala principala \n";
    cout << "5. Aduna doua matrici in matrice noua \n";
    cout << "6. Scade doua matrici in matrice noua \n";
    cout << "7. Inmulteste o matrice cu un factor \n";
    cout << "8. Inmulteste doua matrici \n";
    cout << "9. Introdu o matrice noua \n";
    cout << "-1. Opreste programul \n";
    cout << '\n';
}

void procesare_input(){
    int input = process_input();
    system("CLS");

    if(input == -1){
        run = false;
    }
    if(input == 1){
        afisare();
    }
    if(input == 2){
        cout << "Ce matrice vrei sa afisezi? \n";
        int input = process_input(0);

        formatare(matrici[input], input);
        cout << "````````````````````````````````````````````````````````````````````` \n";
        cout << '\n';
    }
    if(input == 3){
        cout << "Elementele carei matrici vrei sa le afisezi? \n";
        int input = process_input(0);
        for(int i = 1; i <= matrici[input].nr_elemente; i++){
            formatare_element(matrici[input].element[i]);
        }
        cout << '\n';
    }
    if(input == 4){
        cout << "Ce matrice vrei sa verifici? \n";
        int input = process_input(0);

        cout << "````````````````````````````````````````````````````````````````````` \n";
        cout << "Matricea cu indicele " << input;
        if(!mat_simetrica(matrici[input])) cout << " nu";
        cout << " este simetrica pe diagonala principala \n";
        cout << "````````````````````````````````````````````````````````````````````` \n";
        cout << '\n';
    }
    if(input == 5){
        cout << "Ce matrici doresti sa aduni? \n";
        int mat1 = process_input(0, "Prima matrice: ");
        int mat2 = process_input(0, "A doua matrice: ");

        nr++;
        matrici[nr] = suma_matrici(matrici[mat1], matrici[mat2], 1);

        if(matrici[nr].n != -1){
            cout << '\n';
            cout << "Noua matrice: \n";
            formatare(matrici[nr], nr);
            cout << "````````````````````````````````````````````````````````````````````` \n";
            cout << '\n';
        } else {
            cout << "````````````````````````````````````````````````````````````````````` \n";
            cout << "Dimensiunile matricilor nu sunt bune pentru a le aduna! \n";
            cout << "````````````````````````````````````````````````````````````````````` \n";
            nr--;
        }
    }
    if(input == 6){
        cout << "Ce matrici doresti sa scazi? \n";
        int mat1 = process_input(0, "Prima matrice: ");
        int mat2 = process_input(0, "A doua matrice: ");

        nr++;
        matrici[nr] = suma_matrici(matrici[mat1], matrici[mat2], -1);

        if(matrici[nr].n != -1){
            cout << '\n';
            cout << "Noua matrice: \n";
            formatare(matrici[nr], nr);
            cout << "````````````````````````````````````````````````````````````````````` \n";
            cout << '\n';
        } else {
            cout << "````````````````````````````````````````````````````````````````````` \n";
            cout << "Dimensiunile matricilor nu sunt bune pentru a le aduna! \n";
            cout << "````````````````````````````````````````````````````````````````````` \n";
            nr--;
        }
    }
    if(input == 7){
        int mat = process_input(0, "Ce matrice doresti sa inmultesti: ");
        int factor = process_input(-1, "Cu ce factor?: ");
        inmultire_cu_factor(matrici[mat], factor);

        cout << '\n';
        cout << "Matricea inmultita: \n";
        formatare(matrici[mat], mat);
        cout << "````````````````````````````````````````````````````````````````````` \n";
        cout << '\n';
    }
    if(input == 8){
        cout << "Ce matrici doresti sa inmultesti? \n";
        int mat1 = process_input(0, "Prima matrice: ");
        int mat2 = process_input(0, "A doua matrice: ");

        nr++;
        matrici[nr] = inmultire_matrici(matrici[mat1], matrici[mat2]);

        if(matrici[nr].n != -1){
            cout << '\n';
            cout << "Noua matrice: \n";
            formatare(matrici[nr], nr);
            cout << "````````````````````````````````````````````````````````````````````` \n";
            cout << '\n';
        } else {
            cout << "````````````````````````````````````````````````````````````````````` \n";
            cout << "Dimensiunile matricilor nu sunt bune pentru a le inmulti! \n";
            cout << "````````````````````````````````````````````````````````````````````` \n";
            nr--;
        }
    }
    if(input == 9){
        nr++;
        cout << "Numar de randuri: ";
        cin >> matrici[nr].n;
        cout << "Numar de coloane: ";
        cin >> matrici[nr].m;
        cout << "Numarul de elemente nenule: ";
        cin >> matrici[nr].nr_elemente;

        for(int i = 1; i <= matrici[nr].n; i++){
            for(int j = 1; j <= matrici[nr].m; j++){
                matrici[nr].val[i][j] = 0;
            }
        }

        for(int i = 1; i <= matrici[nr].nr_elemente; i++){
            cout << "Coordonatele elementului " << i << ": ";
            cin >> matrici[nr].element[i].x >> matrici[nr].element[i].y;
            cout << "Valoarea elementului " << i << ": ";
            cin >> matrici[nr].element[i].valoare;

            matrici[nr].val[matrici[nr].element[i].x][matrici[nr].element[i].y] = matrici[nr].element[i].valoare;
        }

        cout << "Noua matrice: \n";
        formatare(matrici[nr], nr);
        cout << "````````````````````````````````````````````````````````````````````` \n";
        cout << '\n';
        cin.get();
    }

    if(input != -1) Sleep(1000);
}

int main()
{
    citire();
    fun();
    system("Color 8B");
    while(run){
        meniu();
        procesare_input();
    }
}
