#include "raylib.h"
#include "random"
using namespace std;
float altura = 500;
float largura = 500;
//variavel aleatoria
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> evento(0, 1);
Sound somPonto;
Sound somBatida;
Sound somBatida2;
Color azul = {0,0,135,250};
Color verde = {0,70,0,250};
Color vermelho ={135,0,0,250};
Color nada = {0,0,0,0,};

int frame = 0;
int evento_tempo = 150 * 7;
int aleatorio2 = 0;
int aleatorio3 = 0;
int aleatorio = 0;
int numero_de_eventos = 0;
bool evento_acontecendo = false;
int nu_meteoro = 1;
int estado = 0;
int menu = 0;
int ia = 1;
int j2 = 2;


int atualx = 0;
int atualy = 0;
int frame_fps = 0;

int ponto_1 = 0;
int ponto_2 = 0;


//classes
class Meteoro{
    public:
    float x, y;
    int atualx = 0;
    int atualy = 0;
    int frame_fps;
    bool ativo = false;

};
class Reto{
public:
    float x, y, xx, yy;
    int velocidade_x, velocidade_y;
    Color cor = WHITE;
};

class Bola{
public:
    float x, y;
    float velocidade_x, velocidade_y, raio;
    Color cor = WHITE;
};


//funçoes de tratamento de evento
void Mouse(Reto botao, int estadoReal){
    Vector2 mouse = GetMousePosition();
    if(CheckCollisionPointRec(mouse, Rectangle{botao.x, botao.y, botao.xx, botao.yy}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        estado = estadoReal;
    }
}
void mov(Reto &reto){
    if(IsKeyDown(KEY_W)){
        reto.y -= reto.velocidade_y;
    }
    if(IsKeyDown(KEY_S)){
        reto.y += reto.velocidade_y;
    }
}

void Mov2(Reto &reto){
    if(IsKeyDown(KEY_UP)){
        reto.y -= reto.velocidade_y;
    }
    if(IsKeyDown(KEY_DOWN)){
        reto.y += reto.velocidade_y;
    }
}

//funçoes de atualizacao de posicoes
void pingPong(Reto &reto, Reto &reto2, Reto &reto3, Reto &reto4, Bola &bola){
     if(CheckCollisionCircleRec(Vector2{bola.x, bola.y}, bola.raio, Rectangle{reto.x, reto.y, reto.xx, reto.yy})){
            if(bola.velocidade_x < 0){
               PlaySound(somBatida);
               bola.velocidade_y = 0.075 * (bola.y -(reto.y + (reto.yy /2)));
             bola.velocidade_x *= -1.08;
            }

        }
        if(bola.velocidade_x > 25){
                bola.velocidade_x = 25;
            }
            if(bola.velocidade_x < -25){
                bola.velocidade_x = -25;
            }
        if(CheckCollisionCircleRec(Vector2{bola.x, bola.y}, bola.raio, Rectangle{reto2.x, reto2.y, reto2.xx, reto2.yy})){
            if(bola.velocidade_x > 0){
               PlaySound(somBatida);

               bola.velocidade_y = 0.075 * (bola.y -(reto2.y + (reto2.yy /2)));
               bola.velocidade_x *= -1.08;
}
        }
       if(bola.velocidade_x > 25){
                bola.velocidade_x = 25;
            }
            if(bola.velocidade_x < -25){
                bola.velocidade_x = -25;
            }
        if(CheckCollisionCircleRec(Vector2{bola.x, bola.y}, bola.raio, Rectangle{reto3.x, reto3.y, reto3.xx, reto3.yy})){
            ponto_2 += 1;
            PlaySound(somPonto);
            bola.x = largura /2;
            bola.y = altura /2;
            bola.velocidade_x = 3;
            bola.velocidade_y = 3;
        }
        if(CheckCollisionCircleRec(Vector2{bola.x, bola.y}, bola.raio, Rectangle{reto4.x, reto4.y, reto4.xx, reto4.yy})){
            ponto_1 += 1;
            PlaySound(somPonto);
            bola.velocidade_x = 3;
            bola.velocidade_y = 3;
            bola.x = largura /2;
            bola.y = altura /2;
        }

        bola.x += bola.velocidade_x;
        bola.y += bola.velocidade_y;



        if(bola.y >= altura - bola.raio){
            PlaySound(somBatida2);

            bola.velocidade_y *= -1;

        }
        if(bola.y <= + bola.raio){
            PlaySound(somBatida2);

            bola.velocidade_y *= -1;
        }
        if(reto.y <= 0 ){
            reto.y += reto.velocidade_y;
        }
        if(reto.y >= altura - reto.yy){
            reto.y -= reto.velocidade_y;
        }
        if(reto2.y <= 0 ){
            reto2.y += reto2.velocidade_y;
        }
        if(reto2.y >= altura - reto2.yy){
            reto2.y -= reto2.velocidade_y;
        }
        }
void Ia(Bola &bola, Reto &reto2){
        if(bola.y > reto2.y){
               reto2.y += reto2.velocidade_y;}
              if(bola.y < reto2.y){
              reto2.y -= reto2.velocidade_y;}
}

//funcoes de desenhar
Meteoro chuva[5];
Reto boom;
Reto botao2;
Reto botao;
Reto reto4;
Reto reto3;
Reto reto2;
Reto reto;

void DrawlReto(Reto reto){
    DrawRectangle(reto.x, reto.y, reto.xx, reto.yy, reto.cor);
};

Bola bola;

void Drawl(Bola bola){
    DrawCircle(bola.x, bola.y, bola.raio, bola.cor);
};

void meteoros(Texture2D meteoro,Meteoro chuva[5], Reto &boom) {
    if(evento_acontecendo == true){
    for(int i = 0; i < 5; i++){
        if(chuva[i].ativo == false){
            chuva[i].atualx = 0;
            chuva[i].atualy = 0;
            chuva[i].frame_fps = 0;
            uniform_int_distribution<int> ale_largura(300, largura - 300);
            uniform_int_distribution<int> ale_altura(300, altura - 300);
            chuva[i].x = ale_largura(gen);
            chuva[i].y = ale_altura(gen);
            chuva[i].ativo = true;
        }
    }
    evento_acontecendo = false;
    }

    for(int i = 0; i <5; i++){
      if(chuva[i].ativo == true){

       chuva[i].frame_fps++;
    if(chuva[i].frame_fps == 10){
       chuva[i].frame_fps = 0;
       chuva[i].atualx++;


    if(chuva[i].atualx > 4 ){
        chuva[i].atualx = 0;
        chuva[i].atualy++;

    }

     if(chuva[i].atualy > 2){
        chuva[i].atualx = 0;
        chuva[i].atualy = 0;
        chuva[i].ativo = false;

    }


    }
    if(chuva[i].ativo == true) {
    float imagem_origemx = chuva[i].atualx * boom.xx * 2.5;
    float imagem_origemy = chuva[i].atualy * boom.yy * 2.5;
    boom.x = chuva[i].x;
    boom.y = 0;
    DrawlReto(boom);
    DrawTexturePro(meteoro, (Rectangle){imagem_origemx, imagem_origemy, boom.xx * 2.5 , boom.yy * 2.5}, (Rectangle){chuva[i].x, 0, boom.xx , boom.yy }, {0,0}, 0, WHITE);
}
}
}
}
//////////////////main.
int main() {
    /////////////main.
    ///////////tela.

    SetConfigFlags(FLAG_WINDOW_HIDDEN | FLAG_WINDOW_RESIZABLE);
    InitWindow(largura, altura, "qualquer");

    int monitor = GetCurrentMonitor();
    largura = GetMonitorWidth(monitor);
    altura = GetMonitorHeight(monitor);
    SetWindowSize(largura, altura);
    SetWindowPosition(0, 0);
    ClearWindowState(FLAG_WINDOW_HIDDEN);   //////////tela.


    //texturas
    Texture2D meteoro = LoadTexture("meteoro.png.png");

     //sons
    InitAudioDevice();
    somPonto = LoadSound("ponto.wav.wav");
    somBatida = LoadSound("raquete.wav.wav");
    somBatida2 = LoadSound("soun.wav.wav");




    SetTargetFPS(150);

    botao.cor = azul;
    botao.xx = 400;
    botao.x = largura /2 - 200;
    botao.yy = 70;
    botao.y = altura /2 - 35 - 100;

    botao2.cor = vermelho;
    botao2.xx = 200;
    botao2.x = largura /2 - 100;
    botao2.yy = 70;
    botao2.y = altura /2 + 35 + 60;

    reto.cor = WHITE;
    reto.velocidade_x = 7;
    reto.velocidade_y = 7;
    reto.x = 50;
    reto.xx = 30;
    reto.y = altura /2 - 50;
    reto.yy = 100;

    reto2.cor = WHITE;
    reto2.velocidade_x = 7;
    reto2.velocidade_y = 7;
    reto2.xx = 30;
    reto2.x = largura - 30 - 50;
    reto2.y = altura /2 - 50;
    reto2.yy = 100;

    reto3.cor = BLACK;
    reto3.xx = 10;
    reto3.x = 0;
    reto3.y = 0;
    reto3.yy = altura;

    reto4.cor = BLACK;
    reto4.xx = 10;
    reto4.x = largura - 10;
    reto4.y = 0;
    reto4.yy = altura;

    bola.velocidade_x = 3;
    bola.velocidade_y = 3;
    bola.x = largura /2;
    bola.y = altura /2;
    bola.raio = 20;
    bola.cor = WHITE;

    boom.cor = BLACK;
    boom.velocidade_x = 7;
    boom.velocidade_y = 7;
    boom.x = 0;
    boom.xx = (float)meteoro.width /5 * 0.4;
    boom.y = 0;
    boom.yy = (float)meteoro.height /3 * 0.4;

    //loop
    while(!WindowShouldClose()){
        largura = GetScreenWidth();
        altura = GetScreenHeight();




        //tratamento de eventos
        frame++;

        if(frame == evento_tempo ){
            aleatorio = evento(gen);
            numero_de_eventos = aleatorio;
            if(numero_de_eventos != 0){
            evento_acontecendo = true;
            frame_fps = 0;
            }
            else{
            evento_acontecendo = false;

            }
            frame = 0;
        }
        if(estado == menu){
            Mouse(botao, ia);
            Mouse(botao2, j2);
        }
        if(estado == ia){

        mov(reto);

        }
        else if(estado == j2){
             mov(reto);
        Mov2(reto2);
        }
        //atualizacao de posicoes
        if(estado == ia){
            pingPong(reto, reto2, reto3, reto4, bola);
            if(bola.x > largura / 2){
            Ia(bola, reto2);
        }
        }
        if(estado == j2){
            pingPong(reto, reto2, reto3, reto4, bola);
        }
        //desenhar
        BeginDrawing();
        if(estado == menu){
            ClearBackground(BLACK);
            DrawlReto(botao);
            DrawlReto(botao2);
             DrawText(TextFormat("1j"),largura /3, 0, 80, WHITE);
        }
        else if(estado == ia){
            ClearBackground(verde);
        DrawlReto(reto);
        DrawlReto(reto2);
        DrawLine(largura / 2, 0, largura/2, altura, WHITE);
        DrawCircleLines(largura /2, altura/2, 300, WHITE);
        DrawlReto(reto3);
        DrawlReto(reto4);
        if(numero_de_eventos == nu_meteoro){
                meteoros(meteoro,chuva, boom);
            }

        DrawText(TextFormat("%d",ponto_1),largura /3, 0, 80, WHITE);
        DrawText(TextFormat("%d",ponto_2),largura /1.5, 0, 80, WHITE);
        Drawl(bola);}


        else if(estado == j2){
        ClearBackground(verde);
        DrawlReto(reto);
        DrawlReto(reto2);
        DrawLine(largura / 2, 0, largura/2, altura, WHITE);
        DrawCircleLines(largura /2, altura/2, 300, WHITE);
        DrawlReto(reto3);
        DrawlReto(reto4);
        DrawText(TextFormat("%d",ponto_1),largura /3, 0, 80, WHITE);
        DrawText(TextFormat("%d",ponto_2),largura /1.5, 0, 80, WHITE);
        Drawl(bola);}

        EndDrawing();
    }
    UnloadTexture(meteoro);
    UnloadSound(somBatida);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
