#include "utils.hpp"

void setup(v2d& mat, vector< vector<bool> >& ant_position, vector<Ant>& ants, int tam, int items, int num, int raio){
    int x, y, rx, ry;

    mat = v2d(tam, v1d(tam, 0));
    y = mat.size();
    x = mat[0].size();

    if(x*y < items){

        for(int i = 0; i < y; i++){
            for(int j = 0; j < x; j++){
                mat[i][j] = 1;
            }
        }
        return;
    }
    srand (time(NULL));

    ants = vector<Ant>(num);
    for(int i = 0; i < num; i++){
        ants[i] = Ant(raio, tam, tam);
    }

    ant_position = vector< vector<bool> >(tam, vector<bool>(tam, false));
    for(int i = 0; i < (int) ants.size(); i++){
        ant_position[ants[i].y][ants[i].x] = true;
    }

    for(int i = 0; i < items; i++){
        while(true){
            rx = rand()%x;
            ry = rand()%y;

            if(mat[ry][rx] == 0){
                mat[ry][rx] = 1;
                break;
            }
        }
    }
}

void terminalPrint(v2d& mat, vector<Ant>& ants, int op, int current, int total){
    char ch;
    switch(op){
        case 0:
            cout << "Iteracoes: " << current << " / " << (total) << endl;
            printAnts(mat, ants);
            ants[0].info();
            cout << "Go? ";
            cin >> ch;

            break;
        case 1:
            cout << "Iteracoes: " << current << " / " << (total) << endl;
            printAnts(mat, ants);
            // ants[0].info();
            usleep(50000);
            break;

        case 2:
            if( (current % 1000) == 0){
                cout << "Iteracoes: " << current << " / " << (total) << endl;
                printAnts(mat, ants);
                // ants[0].info();
            }
            break;

        case 3:
            break;

        default:
            break;

    }
}

void printAnts(v2d& mat, vector<Ant>& ants){
    bool b;

    cout << " ";
    for(int y = 0; y <= (int) mat.size(); y++) cout << "__";
    cout << endl;

    for(int y = 0; y < (int) mat.size(); y++){
        cout << "| ";
        for(int x = 0; x < (int) mat[y].size(); x++){
            b = true;

            for (int i = 0; i < (int) ants.size(); i++){
                if( (ants[i].x == x) && (ants[i].y == y) ){
                    cout << "A ";
                    b = false;
                    break;
                }
            }

            if(b){
                if(mat[y][x] == 1)
                    cout << "\u25A0" << " ";
                else if(mat[y][x] == 0)
                    cout << "  ";
            }

        }
        cout << " |" << endl;
    }
    cout << " ";
    for(int y = 0; y <= (int) mat.size(); y++) cout << "--";
    cout << endl;
}

void printRadius(v2d& mat, vector<Ant>& ants){
    bool b;
    bool r;
    float radius = ants[0].raio;
    int bx, by;

    cout << " ";
    for(int y = 0; y <= (int) mat.size(); y++) cout << "__";
    cout << endl;

    by = mat.size();
    bx = mat[0].size();
    for(int y = 0; y < by; y++){
        cout << "| ";
        for(int x = 0; x < bx; x++){
            b = true;
            r = false;

            for (int i = 0; i < (int) ants.size(); i++){
                if( (ants[i].x == x) && (ants[i].y == y) ){
                    cout << "A ";
                    b = false;
                    break;
                }
            }

            for (int i = - radius; i <= radius; i++){
                for (int j = - radius; j <= radius; j++){
                    if (i == 0 && j == 0){
                        continue;
                    }
                    int posX = x + j;
                    int posY = y + i;

                    if (posX < 0) posX = bx - 1;
                    if (posY < 0) posY = by - 1;
                    if (posX >= bx) posX = 0;
                    if (posY >= by) posY = 0;

                    for(int l = 0; l < (int) ants.size(); l++){

                        if( (ants[l].x == posX) && (ants[l].y == posY) ){
                            r = true;
                            if(mat[y][x] == 0){
                                b = false;
                            }
                            else{
                                b = true;
                            }
                        }
                    }
                }
            }

            if(b){
                if(mat[y][x] == 1){
                    cout << "\u25A0" << " ";
                }
                if(mat[y][x] == 0){
                    cout << "  ";
                }
            }
            else if(r){
                cout << "@ ";
            }

        }
        cout << " |" << endl;
    }
    cout << " ";
    for(int y = 0; y <= (int) mat.size(); y++) cout << "--";
    cout << endl;
}

void printMat(v2d& mat){

    cout << " ";
    for(int y = 0; y <= (int) mat.size(); y++) cout << "__";
    cout << endl;

    for(int y = 0; y < (int) mat.size(); y++){
        cout << "| ";
        for(int x = 0; x < (int) mat[y].size(); x++){
            if(mat[y][x] == 1)
                cout << "\u25A0" << " ";
            else if(mat[y][x] == 0)
                cout << "  ";
        }
        cout << " |" << endl;
    }
    cout << " ";
    for(int y = 0; y <= (int) mat.size(); y++) cout << "--";
    cout << endl;
}

void draw_map(v2d& mat, vector<Ant>& ants, sf::RenderWindow& win){
    int size_y, size_x;
    size_y = mat.size();
    size_x = mat[0].size();

    sf::RectangleShape item(sf::Vector2f(WINDOW_X / (float) size_y, WINDOW_X / (float) size_x));

    for(int x = 0; x < size_x; x++){
        for(int y = 0; y < size_y; y++){
            if(mat[x][y] == 0){
                item.setFillColor(sf::Color(225,225,225));
            }
            else if(mat[x][y] == 1){
                item.setFillColor(sf::Color(30,30,30));
            }
            item.setPosition(WINDOW_X * x / (float) size_x, (WINDOW_X * y / (float) size_y) + 20);
            win.draw(item);
        }
    }

    for(int i = 0; i < (int) ants.size(); i++){
        item.setFillColor(sf::Color(0,128,255));
        item.setPosition(WINDOW_X * ants[i].x / (float) size_x, (WINDOW_X * ants[i].y / (float) size_y) + 20);
        win.draw(item);
    }


}

void draw(v2d& mat, vector<Ant>& ants, sf::RenderWindow& win, int current, int total){
    sf::RectangleShape rectangle(sf::Vector2f(120, 50));
    sf::Text text;
    sf::Font font;
    font.loadFromFile("Resources/VCR_OSD.ttf");

    text.setFont(font);
    text.setCharacterSize(16);
    text.setPosition(0.f, 0.f);
    text.setString("Iteracoes: " + to_string(current) + " (" + to_string(100.0 * current/total) + ")%");

    rectangle.setSize(sf::Vector2f(WINDOW_X, WINDOW_X));
    rectangle.setPosition(0.f, 20.f);


    win.clear(sf::Color(80, 80, 80));
    draw_map(mat, ants, win);
    win.draw(text);
    win.display();
}
