#include "Ant.hpp"

Ant::Ant(){
    this->raio = 1;
    this->x = 0;
    this->y = 0;
    this->estado = false;
}

Ant::Ant(int r, int x, int y){
    this->raio = r;
    this->x = rand()%x;
    this->y = rand()%y;
    this->estado = false;
}

void Ant::info(){
    cout << "\n--- Ant Stats ---" << endl;
    cout << "Estado: " << this->estado << endl;
    cout << "Posicao: (" << this->x << ", " << this->y << ")" << endl;
}

void Ant::move(int border, vector< vector<bool> >& ant_position){
    int i, j;
    int n;
    vector< pair<int, int> > offset = vector< pair<int, int> >(8);
    offset = { {-1, -1}, { 0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1} };

    n = rand()%8;

    i = this->x + offset[n].first;
    j = this->y + offset[n].second;

    if (i < 0) i = border - 1 ;
    else if (i >= border) i = 0;

    if (j < 0) j = border - 1;
    else if (j >= border) j = 0;

    ant_position[this->y][this->x] = false;
    this->x = i;
    this->y = j;
    ant_position[this->y][this->x] = true;
}

float Ant::lift(v2d& mat){
    int max, num;
    int x, y, bx, by;

    float chance;
    int rng;

    num = 0;
    max = (2*this->raio + 1) * (2*this->raio + 1) - 1;

    by = mat.size();
    bx = mat[0].size();

    if( (mat[this->y][this->x] == 1) && (this->estado == false) ){
        for(int i = - this->raio; i <= this->raio; i++){
            for(int j = - this->raio; j <= this->raio; j++){
                x = this->x + j;
                y = this->y + i;

                if (x < 0) x = bx - 1;
                if (y < 0) y = by - 1;
                if (x >= bx) x = 0;
                if (y >= by) y = 0;

                num += mat[y][x];
            }
        }
    }
    else{
        return -1.0;
    }

    chance = (1.0 - ( (float) num / max));
    chance = chance * chance * 100.0;

    if(chance == 0)   chance += 0.5;
    if(chance == 100) chance -= 0.5;

    rng = (rand() % 100);

    // PEGA O ITEM
    if(rng <= chance){
        this->estado = true;
        mat[this->y][this->x] = 0;
    }
    return chance;
}

float Ant::drop(v2d& mat){
    int max, num;
    int x, y, bx, by;

    float chance;
    int rng;

    num = 0;
    max = (2*this->raio + 1) * (2*this->raio + 1) - 1;

    by = mat.size();
    bx = mat[0].size();

    if( (mat[this->y][this->x] == 0) && (this->estado == true) ){
        for(int i = - this->raio; i <= this->raio; i++){
            for(int j = - this->raio; j <= this->raio; j++){
                x = this->x + j;
                y = this->y + i;

                if (x < 0) x = bx - 1;
                if (y < 0) y = by - 1;
                if (x >= bx) x = 0;
                if (y >= by) y = 0;

                num += mat[y][x];
            }
        }
    }
    else{
        return -1.0;
    }

    chance = ( (float) num / max);
    chance = chance * chance * 100.0;
    if(chance == 0)   chance += 0.05;
    if(chance == 100) chance -= 0.05;
    rng = rand() % 100;

    // DROPA O ITEM
    if(rng <= chance){
        this->estado = false;
        mat[this->y][this->x] = 1;
    }
    return chance;
}

bool Ant::forceDrop(v2d& mat){
    if( (mat[this->y][this->x] == 0) && (this->estado == true) ){
        this->estado = false;
        mat[this->y][this->x] = 1;
        return false;
    }
    return true;
}
