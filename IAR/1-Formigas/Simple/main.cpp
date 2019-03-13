#include "utils.hpp"
#include "Ant.hpp"
#include "Item.hpp"

int main(void){
    int board, num, raio, items;
    vector<Ant> ants;
    v2d field;
    vector< vector<bool> > ant_position;
    ifstream read("input.in");

    int total, current = 0;
    int op;

    cout << "Menu: " << endl;
    cout << "(0) Slow" << endl;
    cout << "(1) Fast" << endl;
    cout << "(2) Faster" << endl;
    cout << "~> ";
    cin >> op;

    cout << "Tamanho do formigueiro: ";
    read >> board;
    cout << board << endl;

    cout << "Numero de formigas: ";
    read >> num;
    cout << num << endl;

    cout << "Raio de visao da formiga: ";
    read >> raio;
    cout << raio << endl;

    cout << "Numero de itens: ";
    read >> items;
    cout << items << endl;

    cout << "Numero de iteracoes: ";
    read >> total;
    cout << total << endl;


    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "Formigas");
    window.clear(sf::Color(80, 80, 80));
    setup(field, ant_position, ants, board, items, num, raio);
    draw(field, ants, window, current, total);

    string ch;
    cout << "Go? ";
    cin >> ch;

    current = 0;
    auto start = high_resolution_clock::now();
    while(current < total){
        current++;
        for(int i = 0; i < (int) ants.size(); i++){
            ants[i].move(board, ant_position);

            if(ants[i].estado){
                ants[i].drop(field);
            }
            else{
                ants[i].lift(field);
            }
        }

        if(current == total){
            while(ants.size() > 0){
                while( true ){
                    if( ants[0].estado == 0 ){
                        ants.erase(ants.begin());
                        break;
                    }
                    ants[0].move(board, ant_position);
                    ants[0].drop(field);
                }
            }
        }

        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();
        }

        switch(op){
            case 0:
                draw(field, ants, window, current, total);
                break;
            case 1:
                if(current % 5000 == 0){
                    draw(field, ants, window, current, total);
                }
                break;
        }



    }
    auto stop = high_resolution_clock::now();
    auto dur  = duration_cast<microseconds>(stop - start);

    cout << endl << "Resultado Final:" << endl;
    // printMat(field);
    draw(field, ants, window, current, total);

    cout << "Go? ";
    cin >> ch;
    window.close();

    cout << "Duracao: " << dur.count() << " microssegundos" << endl;
    cout << "Frequencia(?): " << total * (1000000.0 / dur.count()) << " iteracoes/segundo" << endl;

    return 0;
}
