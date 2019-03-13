#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <unistd.h>
#include "class/mapatrem.h"
#include "class/threads/thread.h"
#include "class/threadtest.h"

using namespace std;

#define MIN(a, b) ((a < b) ? a:b)
#define MAX(a, b) ((a > b) ? a:b)

#define ONE 49
#define TWO 50
#define Q 113
#define W 119

#define MAX_SPEED 10000
#define MIN_SPEED 100000

typedef vector<int> v1d;
typedef vector<v1d> v2d;

void setup();
void printNet();
void printState();
void changeState(int transition);
int  verifyState(int trem);
void applyFunction(int move, int trem);
void readUser(int key);

void first_path (int train, int flag);
void second_path(int train, int flag);
void third_path (int train, int flag);
void fourth_path(int train, int flag);
void fifth_path (int train, int flag);

pthread_mutex_t _lock;

pthread_t threads[2];
MapaTrem trens; 
v2d pn;
v1d state;

void * simula_trem_1(void *args) {
    while(1){
        int position = verifyState(1);
        if(position == 0){
            readUser(ONE);
        } else if(position == 6){
            readUser(Q);
        }
        applyFunction(position, 1);
    }
}

void * simula_trem_2(void *args){
    // int key;
    while(1){
        int position = verifyState(2);
        cout << position << endl;
        if(position == 19){
            readUser(TWO);
        } else if(position == 14){
            readUser(W);
        }
        applyFunction(position, 2);
    }
}

int main(int argc, char **argv) {
    setup();
    printNet();
    
    // ThreadTest teste(4);
    
    // Thread::SleepMS(speed);
    
    // return 0;
    
    trens.Gate(1);
    
    pthread_create(&(threads[0]), NULL, simula_trem_1, NULL);
    pthread_create(&(threads[1]), NULL, simula_trem_2, NULL);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_mutex_destroy(&_lock);
    
    return 0;
}

/****************/

// Faz (Lucerne/Sarnen) <--> (a1/a2)
void first_path(int train, int flag){
    float start = -1, end = -0.85;
    float passo = 0.01;

    float ini_speed = MIN_SPEED;
    float top_speed = MIN_SPEED;

    int iterations = (end - start)/(2*passo);

    if (flag){
        float aux;
        aux = start;
        start = end;
        end = aux;
        passo *= -1;

        ini_speed = MAX_SPEED;
        top_speed = MIN_SPEED;
    }

    float cur_speed = ini_speed;

    if(train == 1){        
        for(float p = start; flag ? (p >= end) : (p <= end); p += passo){                
            trens.Trem1Pos((-1) * p, 1);

            cur_speed += (top_speed - ini_speed) / iterations;
            usleep(MAX(cur_speed, MAX_SPEED));
            
            trens.Trem1Txt ("a1="  + to_string((int) trens.A1()) + 
                            " a2=" + to_string((int) trens.A2()) + 
                            " b1=" + to_string((int) trens.B1()) + 
                            " b2=" + to_string((int) trens.B2()) + 
                            " c="  + to_string((int) trens.C()));
        }
    }

    else{
        for(float p = start; flag ? (p >= end) : (p <= end); p += passo){
            trens.Trem2Pos((-1) * p, 2);

            cur_speed += (top_speed - ini_speed) / iterations;
            usleep(MAX(cur_speed, MAX_SPEED));
            
            trens.Trem2Txt ("a1="  + to_string((int) trens.A1()) + 
                            " a2=" + to_string((int) trens.A2()) + 
                            " b1=" + to_string((int) trens.B1()) + 
                            " b2=" + to_string((int) trens.B2()) + 
                            " c="  + to_string((int) trens.C()));
        }
    }
}

// Faz (a1/a2) <--> (b1/b2)
void second_path(int train, int flag){
    float start = -0.85, end = -0.5;
    float passo = 0.01;

    float ini_speed = MIN_SPEED;
    float top_speed = MAX_SPEED;

    int iterations = (end - start)/(3*passo);

    if (flag){
        float aux;
        aux = start;
        start = end;
        end = aux;
        passo *= -1;

        ini_speed = MAX_SPEED;
        top_speed = MAX_SPEED;
    }

    float cur_speed = ini_speed;

    if(train == 1){
        for(float p = start; flag ? (p >= end) : (p <= end); p += passo){                
            trens.Trem1Pos((-1) * p, 1);

            cur_speed += (top_speed - ini_speed) / iterations;
            usleep(MAX(cur_speed, MAX_SPEED));
            
            trens.Trem1Txt ("a1="  + to_string((int) trens.A1()) + 
                            " a2=" + to_string((int) trens.A2()) + 
                            " b1=" + to_string((int) trens.B1()) + 
                            " b2=" + to_string((int) trens.B2()) + 
                            " c="  + to_string((int) trens.C()));
        }
    }

    else{
        for(float p = start; flag ? (p >= end) : (p <= end); p += passo){    
            trens.Trem2Pos((-1) * p, 2);

            cur_speed += (top_speed - ini_speed) / iterations;
            usleep(MAX(cur_speed, MAX_SPEED));
            
            trens.Trem2Txt ("a1="  + to_string((int) trens.A1()) + 
                            " a2=" + to_string((int) trens.A2()) + 
                            " b1=" + to_string((int) trens.B1()) + 
                            " b2=" + to_string((int) trens.B2()) + 
                            " c="  + to_string((int) trens.C()));
        }
    }   
}

// Faz (b1/b2) <--> ponte
void third_path(int train, int flag){
    float start = -0.5, end = -0.2;
    float passo = 0.01;

    float top_speed = MIN_SPEED;
    float ini_speed = MAX_SPEED;

    int iterations = (end - start)/(passo);

    if (flag){
        float aux;
        aux = start;
        start = end;
        end = aux;
        passo *= -1;

        top_speed = MAX_SPEED;
        ini_speed = MAX_SPEED;
    }

    float cur_speed = ini_speed;

    if(train == 1){
        for(float p = start; flag ? (p >= end) : (p <= end); p += passo){                
            trens.Trem1Pos((-1) * p, 1);

            cur_speed += (top_speed - ini_speed) / iterations;
            usleep(MAX(cur_speed, MAX_SPEED));
            
            trens.Trem1Txt ("a1="  + to_string((int) trens.A1()) + 
                            " a2=" + to_string((int) trens.A2()) + 
                            " b1=" + to_string((int) trens.B1()) + 
                            " b2=" + to_string((int) trens.B2()) + 
                            " c="  + to_string((int) trens.C()));
        }        
    }

    else{
        for(float p = start; flag ? (p >= end) : (p <= end); p += passo){           
            trens.Trem2Pos((-1) * p, 2);

            cur_speed += (top_speed - ini_speed) / iterations;
            usleep(MAX(cur_speed, MAX_SPEED));
            
            trens.Trem2Txt ("a1="  + to_string((int) trens.A1()) + 
                            " a2=" + to_string((int) trens.A2()) + 
                            " b1=" + to_string((int) trens.B1()) + 
                            " b2=" + to_string((int) trens.B2()) + 
                            " c="  + to_string((int) trens.C()));
        }
    }
}

// Faz ponte <--> c
void fourth_path(int train, int flag){
    float start = -0.2, end = 0.75;
    float passo = 0.01;

    float top_speed = MAX_SPEED;
    float ini_speed = MIN_SPEED;

    int iterations = (end - start)/(3*passo);

    if (flag){
        float aux;
        aux = start;
        start = end;
        end = aux;
        passo *= -1;

        top_speed = MAX_SPEED;
        ini_speed = MAX_SPEED;
    }
    float cur_speed = ini_speed;

    if(train == 1){
        for(float p = start; flag ? (p >= end) : (p <= end); p += passo){
            if(p < 0){
                trens.Trem1Pos((-1) * p, 1);
            }
            else{
                trens.Trem1Pos(p, 0);
            }

            cur_speed += (top_speed - ini_speed) / iterations;
            usleep(MAX(cur_speed, MAX_SPEED));
            
            trens.Trem1Txt ("a1="  + to_string((int) trens.A1()) + 
                            " a2=" + to_string((int) trens.A2()) + 
                            " b1=" + to_string((int) trens.B1()) + 
                            " b2=" + to_string((int) trens.B2()) + 
                            " c="  + to_string((int) trens.C()));
        }
    }

    else{
        for(float p = start; flag ? (p >= end) : (p <= end); p += passo){
            if(p < 0){
                trens.Trem2Pos((-1) * p, 2);
            }
            else{
                trens.Trem2Pos(p, 0);
            }

            cur_speed += (top_speed - ini_speed) / iterations;
            usleep(MAX(cur_speed, MAX_SPEED));
            
            trens.Trem2Txt ("a1="  + to_string((int) trens.A1()) + 
                            " a2=" + to_string((int) trens.A2()) + 
                            " b1=" + to_string((int) trens.B1()) + 
                            " b2=" + to_string((int) trens.B2()) + 
                            " c="  + to_string((int) trens.C()));           
        }
    }
}

// Faz c <--> Engelberg
void fifth_path(int train, int flag){
    float start = 0.75, end = 1.0;
    float passo = 0.01;

    float top_speed = MIN_SPEED;
    float ini_speed = MAX_SPEED;

    int iterations = (end - start)/(2*passo);

    if (flag){
        float aux;
        aux = start;
        start = end;
        end = aux;
        passo *= -1;

        top_speed = MAX_SPEED;
        ini_speed = MIN_SPEED;
    }
    float cur_speed = ini_speed;

    if(train == 1){
        for(float p = start; flag ? (p >= end) : (p <= end); p += passo){
            trens.Trem1Pos(p, 0);

            cur_speed += (top_speed - ini_speed) / iterations;
            usleep(MAX(cur_speed, MAX_SPEED));
            
            trens.Trem1Txt ("a1="  + to_string((int) trens.A1()) + 
                            " a2=" + to_string((int) trens.A2()) + 
                            " b1=" + to_string((int) trens.B1()) + 
                            " b2=" + to_string((int) trens.B2()) + 
                            " c="  + to_string((int) trens.C()));
        }
    }

    else{
        for(float p = start; flag ? (p >= end) : (p <= end); p += passo){

            if(p < 0){
                trens.Trem2Pos((-1) * p, 2);
            }
            else{
                trens.Trem2Pos(p, 0);
            }

            cur_speed += (top_speed - ini_speed) / iterations;
            usleep(MAX(cur_speed, MAX_SPEED));
            
            trens.Trem2Txt ("a1="  + to_string((int) trens.A1()) + 
                            " a2=" + to_string((int) trens.A2()) + 
                            " b1=" + to_string((int) trens.B1()) + 
                            " b2=" + to_string((int) trens.B2()) + 
                            " c="  + to_string((int) trens.C()));
        }
    }
}

/****************/
void setup(){
    pn = v2d(23, v1d(22, 0));
    state = v1d(23, 0);

    /*
        T0 = Ir_Para_Direita_R_1
        T1 = Desacelerar_1
        T2 = Requisitar_Ponte_1
        T3 = Ir_Para_Direita_R_2
        T4 = Desacelerar_2
        T5 = Desembarcar_Embarcar_Passageiros_2
        T6 = Ir_Para_Esquerda_L_1
        T7 = Liberar_Ponte_1
        T9 = Ir_Para_Esquerda_L_2
        T8 = Desacelerar_3
        T10 = Desembarcar_Embarcar_Passageiros_1
        T11 = Requisitar_Ponte_2
        T12 = Ir_Para_Direita_R_3
        T13 = Desacelerar_4
        T14 = Desembarcar_Embarcar_Passageiros_3
        T15 = Ir_Para_Esquerda_L_3
        T16 = Liberar_Ponte_2
        T17 = Ir_Para_Esquerda_L_4
        T18 = Desacelerar_5
        T19 = Desembarcar_Embarcar_Passageiros_4
        T20 = Ir_Para_Direita_R_4
        T21 = Desacelerar_6
    */

    pn =
        // 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21
        {{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 0 - Lucerne_Parado_S
         {1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 1 - Ativou_b1
         {0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 2 - Parado_S_1
         {0, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0,-1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, // 3 - Mutex_Controla_Ponte
         {0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 4 - Passou_Ponte_Stans_1
         {0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 5 - Ativou_c_1
         {0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 6 - Parado_Engelberg_S_1
         {0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 7 - Desembarque_Embarque_Completo_2
         {0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 8 - Chega_na_Ponte_Stans_1
         {0, 0, 0, 0, 0, 0, 0, 0, -1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 9 - Ativou_a1
         {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 10 - Desembarque_Embarque_Completo_1
         {0, 0, 0, 0, 0, 0, 0, 1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 11 - Ponte_Liberada_1
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0},  // 12 - Chega_na_Ponte_Stans_2
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0},  // 13 - Desembarque_Embarque_Completo_4
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0},  // 14 - Parado_Engelberg_S_2
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0},  // 15 - Ativou_c2
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 16 - Passou_Ponte_Stans_2
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0},  // 17 - Ponte_Liberada_2
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0},  // 18 - Ativou_a2
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, 0, 0},  // 19 - Sarnen_Parado_S
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, 0},  // 20 - Desembarque_Embarque_Completo_3
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1},  // 21 - Ativou_b2
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}}; // 22 - Parado_S_2

    state = {1,  // Lucerne_Parado_S
             0,  // Ativou_b1
             0,  // Parado_S_1
             1,  // Mutex_Controla_Ponte
             0,  // Passou_Ponte_Stans_1
             0,  // Ativou_c_1
             0,  // Parado_Engelberg_S_1
             0,  // Desembarque_Embarque_Completo_2
             0,  // Chega_na_Ponte_Stans_1
             0,  // Ativou_a1
             0,  // Desembarque_Embarque_Completo_1
             0,  // Ponte_Liberada_1
             0,  // Chega_na_Ponte_Stans_2
             0,  // Desembarque_Embarque_Completo_4
             0,  // Parado_Engelberg_S_2
             0,  // Ativou_c2
             0,  // Passou_Ponte_Stans_2
             0,  // Ponte_Liberada_2
             0,  // Ativou_a2
             1,  // Sarnen_Parado_S
             0,  // Desembarque_Embarque_Completo_3
             0,  // Ativou_b2
             0}; // Parado_S_2

    pthread_mutex_init(&_lock, NULL);
    trens.Trem1Pos(1, 1);
    trens.Trem2Pos(1, 2);
}

void changeState(int transition){
    for(int i = 0; i < (int) state.size(); i++){
        state[i] += pn[i][transition];
    }
    printState();
}

/****************/

void printNet(){
    cout << "==========" << endl;
    cout << "Rede:" << endl << endl;    
    for(int i=0; i < (int) pn.size(); i++){
        for(int j=0; j < (int) pn[i].size(); j++){
            cout << pn[i][j] << " ";
        }
        cout << endl;
    }
    cout << "==========" << endl;

}

void printState(){
    cout << "==========" << endl;
    cout << "Estado atual:" << endl;
    cout << "| ";
    for(int i=0; i < (int) state.size(); i++){
        cout << state[i] << " | ";
    }
    cout << "\n==========" << endl;

}

int verifyState(int trem){
    if(trem == 1){ // Estados de interesse: 0 -> 10
        if(state[2] == 1){
            pthread_mutex_lock(&_lock);
            int f = 0;
            if(state[3] == 1){
                f = 1;
            }
            pthread_mutex_unlock(&_lock);
            if(f) return 2;
            return -1;
        } else {
            for(int i = 0; i <= 11; i++){
                if(i == 3) continue;
                if(state[i]){
                    return i;
                }
            }
        }
    } else {
        if (state[22] == 1){
            pthread_mutex_lock(&_lock);
            int f = 0;
            if (state[3] == 1){
                f = 1;
            }
            pthread_mutex_unlock(&_lock);
            if (f) return 22;
            return -1;
        }
        else {
            for (int i = 12; i <= 22; i++){
                if (state[i]){
                    return i;
                }
            }
        }
    }
}

void applyFunction(int move, int trem){
    switch (move){
        case 0:
            changeState(10);
            first_path(trem, 0);
            break;
        case 1:
            changeState(1);
            third_path(trem, 0);
            break;
        case 2:
            changeState(2);
            break;
        case 3:
            // Nada
            break;
        case 4:
            changeState(3);
            trens.Gate(1);
            fourth_path(trem, 0);
            break;
        case 5:
            changeState(4);
            fifth_path(trem, 0);
            break;
        case 6:
            changeState(5);
            fifth_path(trem, 1);
            break;
        case 7:
            changeState(6);
            fourth_path(trem, 1);
            break;
        case 8:
            changeState(7);
            third_path(trem, 1);
            break;
        case 9:
            changeState(8);
            first_path(trem, 1);
            break;
        case 10:
            changeState(0);
            second_path(trem, 0);
            break;
        case 11:
            changeState(9);
            second_path(trem, 1);
            break;
        case 12:
            changeState(16);
            third_path(trem, 1);
            break;
        case 13:
            changeState(15);
            fourth_path(trem, 1);
            break;
        case 14:
            changeState(14);
            fifth_path(trem, 1);
            break;
        case 15:
            changeState(13);
            fifth_path(trem, 0);
            break;
        case 16:
            changeState(12);
            trens.Gate(0);
            fourth_path(trem, 0);
            break;
        case 17:
            changeState(17);
            second_path(trem, 1);
            break;
        case 18:
            changeState(18);
            first_path(trem, 1);
            break;
        case 19:
            changeState(19);
            first_path(trem, 0);
            break;
        case 20:
            changeState(20);
            second_path(trem, 0);
            break;
        case 21:
            changeState(21);
            third_path(trem, 0);
            break;
        case 22:
            changeState(11);
            break;
    }
}

void readUser(int k){
    int key;
    key = 0;
    while (key != k){
        key = trens.GetLastKey();
        if(k == ONE){
            trens.Trem1Txt("Trem 1 aguardando Lucerne");
        } else if(k == Q){
            trens.Trem1Txt("Trem 1 aguardando Engelberg");
        } else if(k == TWO){
            trens.Trem2Txt("Trem 2 aguardando Sarnen");
        } else {
            trens.Trem2Txt("Trem 2 aguardando Engelberg");
        }
        Thread::SleepMS(200);
    }
}