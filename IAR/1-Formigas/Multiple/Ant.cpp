#include "Ant.hpp"

Ant::Ant(){
    this->raio = 1;
    this->x = 0;
    this->y = 0;
    this->carrying = false;
    this->dead = false;
    this->last_move = rand()%8;

    this->alpha = 1.0;
    this->sigma = 1.0;

    this->item = Item();
}

Ant::Ant(int r, int x, int y, double alpha, double sigma){
    this->raio = r;
    this->x = rand()%x;
    this->y = rand()%y;
    this->carrying = false;
    this->dead = false;
    this->last_move = rand()%8;

    this->alpha = alpha;
    this->sigma = sigma;
}

void Ant::info(){
    cout << "\n--- Ant Stats ---" << endl;
    cout << "Estado: " << this->carrying << endl;
    cout << "Posicao: (" << this->x << ", " << this->y << ")" << endl;
}

void Ant::move(v2I& grid){
    int i, j;
    int n;
    int border = grid.size();
    vector< pair<int, int> > offset = vector< pair<int, int> >(8);
    offset = { {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0} };

    n = rand()%8;
    while(n == (this->last_move + 4)%8 ){
        n = rand()%8;
    }
    this->last_move = n;

    i = this->x + offset[n].first;
    j = this->y + offset[n].second;

    if (i < 0) i = border - 1 ;
    else if (i >= border) i = 0;

    if (j < 0) j = border - 1;
    else if (j >= border) j = 0;

    this->x = i;
    this->y = j;
}

float Ant::pickup(v2I& grid){
    int x, y, bx, by;

    float chance, aux;
    double rng;

    by = grid.size();
    bx = grid[0].size();
    chance = 0.0;

    if(this->dead == true){
        return -1.0;
    }

    if( (grid[this->y][this->x].color != 0) && (this->carrying == false) ){
        for(int i = - this->raio; i <= this->raio; i++){
            for(int j = - this->raio; j <= this->raio; j++){
                if(i == 0 && j == 0){
                    continue;
                }
                x = this->x + j;
                y = this->y + i;

                if (x < 0) x = bx - 1;
                if (y < 0) y = by - 1;
                if (x >= bx) x = 0;
                if (y >= by) y = 0;

                if(grid[y][x].color == 0)
                    continue;

                aux = (this->distance(grid[this->y][this->x], grid[y][x]));
                if(aux > 0 && (1.0 - aux/this->alpha) > 0 )
                    chance += ( 1.0 - aux/this->alpha );

            }
        }
    }
    else{
        return -1.0;
    }

    if(chance <= 0) chance = 0.0;
    chance = chance / pow(this->sigma,2);
    // cout << "Lift: "<< chance << endl;

    if(chance <= 1.0) chance = 1.0;
    else chance = 1.0 / (chance * chance);

    rng = ((rand() % 1000) + 1)/1000.0;

    // PEGA O ITEM
    if(rng <= chance){
        Item item;
        item = grid[this->y][this->x];

        this->carrying = true;
        this->item = item;
        grid[this->y][this->x] = Item();
    }
    return chance;
}

float Ant::drop(v2I& grid){
    int x, y, bx, by;

    float chance, aux;
    double rng;

    by = grid.size();
    bx = grid[0].size();

    chance = 0.0;
    if( (grid[this->y][this->x].color == 0) && (this->carrying == true) ){
        for(int i = - this->raio; i <= this->raio; i++){
            for(int j = - this->raio; j <= this->raio; j++){
                if(i == 0 && j == 0){
                    continue;
                }
                x = this->x + j;
                y = this->y + i;

                if (x < 0) x = bx - 1;
                if (y < 0) y = by - 1;
                if (x >= bx) x = 0;
                if (y >= by) y = 0;

                if(grid[y][x].color == 0)
                    continue;

                aux = (this->distance(this->item, grid[y][x]));
                if(aux > 0 && (1 - aux/this->alpha) > 0 )
                    chance += ( 1 - aux/this->alpha );
            }
        }
    }
    else{
        return -1.0;
    }

    if(chance <= 0) chance = 0.0;
    chance = chance / pow(this->sigma,2);

    if(chance >= 1.0) chance = 1.0;
    else chance = chance * chance * chance * chance;
    // cout << "Drop: "<< chance << endl;
    rng = ((rand() % 1000) + 1)/1000.0;

    // DROPA O ITEM
    if(rng <= chance){
        Item item;
        item = this->item;
        this->carrying = false;
        grid[this->y][this->x] = this->item;
        this->item = Item();
    }

    return chance;
}

bool Ant::forceDrop(v2I& grid){

    if(grid[this->y][this->x].color == 0){
        Item item;
        item = this->item;
        this->carrying = false;
        grid[this->y][this->x] = this->item;
        this->item = Item();

        return true;
    }

    return false;
}

double Ant::distance(Item& a, Item& b){
    double dist = 0.0;

    for(int i = 0; i < (int) a.features.size(); i++){
        dist += pow(a.features[i] - b.features[i], 2);
    }

    dist  = sqrt(dist);
    return dist;
}
