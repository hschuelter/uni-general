#include "utils.hpp"

// extern vector<sf::Color> colors;

void setup(v2I& grid, vector<Ant>& ants, int tam, int items, int num, int raio, double alpha, double sigma){
    Item item = Item();
    int x, y, rx, ry;
    double a, b, c, d;
    int color;
    ifstream read("Inputs/iris.data");

    grid = v2I(tam, v1I(tam, Item()));
    y = grid.size();
    x = grid[0].size();


    srand (time(NULL));
    ants = vector<Ant>(num);
    for(int i = 0; i < num; i++){
        ants[i] = Ant(raio, tam, tam, alpha, sigma);
    }

    for(int i = 0; i < items; i++){
        read >> a >> b >> c >> d >> color;
        while(true){
            rx = rand()%x;
            ry = rand()%y;

            if(grid[ry][rx].color == 0){
                grid[ry][rx] = Item(a, b, c, d, color);
                break;
            }
        }
    }

}

void draw(v2I& grid, vector<Ant>& ants, sf::RenderWindow& win, int current, int total){

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
    // win.setFramerateLimit(30);


    win.clear(sf::Color(80, 80, 80));
    draw_map(grid, ants, win);
    win.draw(text);
    win.display();
}

void draw(v2I& grid, vector<Ant>& ants, sf::RenderWindow& win){
    sf::RectangleShape rectangle(sf::Vector2f(120, 50));
    sf::Text text;
    sf::Font font;
    font.loadFromFile("Resources/VCR_OSD.ttf");

    text.setFont(font);
    text.setCharacterSize(16);
    text.setPosition(0.f, 0.f);
    text.setString("ENDLESS MODE");

    rectangle.setSize(sf::Vector2f(WINDOW_X, WINDOW_X));
    rectangle.setPosition(0.f, 20.f);


    win.clear(sf::Color(80, 80, 80));
    draw_map(grid, ants, win);
    win.draw(text);
    win.display();
}

void draw_map(v2I& grid, vector<Ant>& ants, sf::RenderWindow& win){
    vector< tuple<int, int, int> > cores = vector< tuple<int, int, int> >(16);
    cores= {make_tuple(235,235,235),
            make_tuple( 0 ,128,255), make_tuple(255, 0 ,128), make_tuple(255,128, 0 ), make_tuple(255,255, 0 ),
            make_tuple(227, 66, 52), make_tuple(102,237, 60), make_tuple( 81, 22, 22), make_tuple( 0 ,255,255),
            make_tuple(255, 0 , 0 ), make_tuple( 0 ,255, 0 ), make_tuple( 0 , 0 ,255), make_tuple(255, 0 ,255),
            make_tuple(163,163,255), make_tuple(146, 73,255), make_tuple( 50, 50, 50)};

    int size_y, size_x;
    size_y = grid.size();
    size_x = grid[0].size();

    sf::RectangleShape item(sf::Vector2f( WINDOW_X / (float) size_y, WINDOW_X / (float) size_x));
    int cor;

    for(int x = 0; x < size_x; x++){
        for(int y = 0; y < size_y; y++){
            cor = grid[x][y].color;

            item.setFillColor(sf::Color( get<0>(cores[cor]), get<1>(cores[cor]), get<2>(cores[cor]) ));
            item.setPosition(WINDOW_X * y / (float) size_x, (WINDOW_X * x / (float) size_y) + 20);
            win.draw(item);
        }
    }

    for(int i = 0; i < (int) ants.size(); i++){
        if(ants[i].carrying){
            item.setFillColor(sf::Color(80,80,80));
        }
        else{
            item.setFillColor(sf::Color(180,180,180));
        }
        item.setPosition(WINDOW_X * ants[i].x / (float) size_x, (WINDOW_X * ants[i].y / (float) size_y) + 20);
        if(ants[i].dead == false)
            win.draw(item);
    }
}

void printColor(v2I& grid){
    cout << " ";
    for(int y = 0; y <= (int) grid.size(); y++) cout << "__";
    cout << endl;

    for(int y = 0; y < (int) grid.size(); y++){
        cout << "| ";
        for(int x = 0; x < (int) grid[y].size(); x++){
            cout << grid[y][x].color << " ";
        }
        cout << " |" << endl;
    }
    cout << " ";

    for(int y = 0; y <= (int) grid.size(); y++) cout << "--";
    cout << endl;

}

void waitKey(){
    bool pressed = false;
    while(pressed == false){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        	pressed = true;
        }
    }
    return;
}
