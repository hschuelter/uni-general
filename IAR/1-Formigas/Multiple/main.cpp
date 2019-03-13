#include "utils.hpp"
#include "Ant.hpp"
#include "Item.hpp"

int main(void){
    int board, num, raio, items;
    double alpha, sigma;
    vector<Ant> ants;
    v2I grid;
    sf::Event event;

    ifstream read("Inputs/input.in");

    int total, current = 0;
    int deathcount = 0;
    int it = 0;
    int op;

    cout << "Menu: " << endl;
    cout << "(0) Slowest" << endl;
    cout << "(1) Slow" << endl;
    cout << "(2) Fast" << endl;
    cout << "(3) Infinite" << endl;
    cout << "~> ";  cin >> op;

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

    cout << "Alpha: ";
    read >> alpha;
    cout << alpha << endl;

    cout << "Sigma: ";
    read >> sigma;
    cout << sigma << endl;


    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "Formigas");
    window.clear(sf::Color(80, 80, 80));
    setup(grid, ants, board, items, num, raio, alpha, sigma);

    if(op == 4)
        draw(grid, ants, window);
    else
        draw(grid, ants, window, current, total);

    waitKey();

    current = 0;
    while(current < total){
        current++;
        for(int i = 0; i < (int) ants.size(); i++){
            ants[i].move(grid);

            if(ants[i].carrying){
                ants[i].drop(grid);
            }
            else{
                ants[i].pickup(grid);
            }
        }
        // Once we reached the total iterations and there are ants with items
        if(current == total){
            if( (int) ants.size() == deathcount)
                break;

            for(int i = 0; i < (int) ants.size(); i++){
                if(ants[i].carrying == false and ants[i].dead == false){
                    ants[i].dead = true;
                    deathcount++;
                }
                if(it == 5000 and ants[i].dead == false){

                    while(!ants[i].forceDrop(grid)){
                        ants[i].move(grid);
                    }
                    ants[i].dead = true;
                    deathcount++;
                }
            }
            draw(grid, ants, window, it, 5000);
            current--;
            it++;
        }

        // Window doesn't crash
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // Drawing
        switch(op){
            case 0:
                draw(grid, ants, window, current, total);
                waitKey();
                break;

            case 1:
                draw(grid, ants, window, current, total);
                break;

            case 2:
                if(current % 3000 == 0){
                    draw(grid, ants, window, current, total);
                }
                break;

            default:
                if(current % 500 == 0){
                    draw(grid, ants, window);
                    current -= 500;
                }
                break;
        }

    }
    cout << endl << "Resultado Final:" << endl;
    draw(grid, ants, window, current, total);

    waitKey();
    window.close();

    return 0;
}
