#include "raylib.h"

float altura = 500;
float largura = 500;
Sound somPonto;
Sound somBatida;
Sound somBatida2;
Color azul = {0,0,135,250};
Color verde = {0,70,0,250};
Color vermelho ={135,0,0,250};
int estado = 0;
int menu = 0;
int ia = 1;
int j2 = 2;

int ponto_1 = 0;
int ponto_2 = 0;

// classes
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

// funcoes de tratamento de evento
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

// funcoes de atualizacao de posicoes
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
        reto2.y += reto2.velocidade_y;
    }
    if(bola.y < reto2.y){
        reto2.y -= reto2.velocidade_y;
    }
}

// funcoes de desenhar
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

// main
int main() {
    // tela
    SetConfigFlags(FLAG_WINDOW_HIDDEN | FLAG_WINDOW_RESIZABLE);
    InitWindow(largura, altura, "qualquer");

    int monitor = GetCurrentMonitor();
    largura = GetMonitorWidth(monitor);
    altura = GetMonitorHeight(monitor);
    SetWindowSize(largura, altura);
    SetWindowPosition(0, 0);
    ClearWindowState(FLAG_WINDOW_HIDDEN);

    // sons
    InitAudioDevice();
    somPonto = LoadSound("ponto.wav.wav");
    somBatida = LoadSound("raquete.wav.wav");
    somBatida2 = LoadSound("soun.wav.wav");

    SetTargetFPS(150);

    botao.cor = azul;
    botao.xx = 500;
    botao.x = largura /2 - 250;
    botao.yy = 100;
    botao.y = altura /2 - 50 - 100;

    botao2.cor = vermelho;
    botao2.xx = 500;
    botao2.x = largura /2 - 250;
    botao2.yy = 100;
    botao2.y = altura /2 + 50 + 60;

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

    // loop
    while(!WindowShouldClose()){
        largura = GetScreenWidth();
        altura = GetScreenHeight();

        // tratamento de eventos
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

        // atualizacao de posicoes
        if(estado == ia){
            pingPong(reto, reto2, reto3, reto4, bola);
            if(bola.x > largura / 2){
                Ia(bola, reto2);
            }
        }
        if(estado == j2){
            pingPong(reto, reto2, reto3, reto4, bola);
        }

        // desenhar
        BeginDrawing();
        if(estado == menu){
            ClearBackground(BLACK);
            DrawlReto(botao);
            DrawlReto(botao2);
            DrawText(TextFormat("pong de mesa"),largura /3, 0, 100, WHITE);
            DrawText(TextFormat("modo ia"),largura /2 - 100, botao.y + 20, 50, WHITE);
            DrawText(TextFormat("modo 2 jogadores"),largura /2 - 220, botao2.y + 20, 50, WHITE);
        }
        else if(estado == ia){
            ClearBackground(verde);
            DrawlReto(reto);
            DrawlReto(reto2);
            DrawLine(largura / 2, 0, largura/2, altura, WHITE);
            DrawCircleLines(largura /2, altura/2, 300, WHITE);
            DrawlReto(reto3);
            DrawlReto(reto4);
            DrawText(TextFormat("%d",ponto_1),largura /3, 0, 80, WHITE);
            DrawText(TextFormat("%d",ponto_2),largura /1.5, 0, 80, WHITE);
            Drawl(bola);
        }
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
            Drawl(bola);
        }

        EndDrawing();
    }

    UnloadSound(somBatida);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}

