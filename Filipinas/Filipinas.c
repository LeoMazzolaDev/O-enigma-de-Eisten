#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

// screen configurations
const int width_screen = 1280;
const int height_screen = 720;

// games configurations
const float gravity_felipe = 0.4;
const float floor = 500;
const float FPS = 60.0;

// sprite felipe configurations
const int width_sprite_felipe = 150;
const int height_sprite_felipe = 150;
const int speed_felipe = 5; // Velocidade de andar 
const float jump_height = -10.0;
const int num_walk_sprites_felipe = 2;
const int num_jump_sprites_felipe = 1;

// sprite bowling ball
float pos_bowling_ball_x = 58; //Aqui decidimos aonde queremos começar a cortar a imagem a partir canto superior esquerdo
float pos_bowling_ball_y = 58; // Altura para cortarmos no y
int bowling_ball_x = -50; // Canto superior esquerdo onde será desenhado o sprite na tela
int bowling_ball_y = 20; // Altura do sprite que ser desenhado
int gravity_bowling_ball = 10; // Velocidade de queda do sprite
int count_bowling_ball = 0;

// sprite pity
float pos_pity_x = 400;  // Mesmas explicações do sprite acima 
float pos_pity_y = 0;
int pity_x = 0;
int pity_y = -50;
int gravity_pity = 5;

// LUGAR ERRADO {
// Coordenadas do botão de início
const int start_button_x1 = 520;
const int start_button_x2 = 750;
const int start_button_y1 = 580;
const int start_button_y2 = 680;
// }

int main() {
    al_init();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    srand(time(NULL));

    // Criar a tela e verificar sucesso
    ALLEGRO_DISPLAY* display = al_create_display(width_screen, height_screen);
    if (!display) {
        fprintf(stderr, "Falha ao criar a tela.\n");
        return -1;
    }

    // Criar o timer
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
    al_start_timer(timer);

    // Carregar o sprite do personagem
    ALLEGRO_BITMAP* sprite_felipe = al_load_bitmap("src/felipe-150-sprites.png");
    if (!sprite_felipe) {
        fprintf(stderr, "Falha ao carregar o sprite do personagem.\n");
        al_destroy_display(display);
        return -1;
    }

    // Carregar o sprite da bola de boliche
    ALLEGRO_BITMAP* sprite_bowling_ball = al_load_bitmap("src/boliche.png");
    if (!sprite_bowling_ball) {
        fprintf(stderr, "Falha ao carregar o sprite da bola de boliche.\n");
        al_destroy_display(display);
        return -1;
    }

    // Carregar o sprite da bola de boliche
    ALLEGRO_BITMAP* sprite_pity = al_load_bitmap("src/pena.png");
    if (!sprite_pity) {
        fprintf(stderr, "Falha ao carregar o sprite da pena.\n");
        al_destroy_display(display);
        return -1;
    }

    //Carregar as imagens da introdução
    ALLEGRO_BITMAP* introducao1 = al_load_bitmap("src/introducao1-2.png");
    ALLEGRO_BITMAP* introducao2 = al_load_bitmap("src/introducao2.png");
    ALLEGRO_BITMAP* introducao3 = al_load_bitmap("src/introducao3-2.png");
    ALLEGRO_BITMAP* introducao4 = al_load_bitmap("src/introducao4.png");
    ALLEGRO_BITMAP* introducao6 = al_load_bitmap("src/introducao6.png");
    ALLEGRO_BITMAP* introducao7 = al_load_bitmap("src/introducao7.png");
    ALLEGRO_BITMAP* introducao8 = al_load_bitmap("src/introducao8.png");
    ALLEGRO_BITMAP* introducao9 = al_load_bitmap("src/fase1 intro.png");


    //Carregar imagem da explicação
    ALLEGRO_BITMAP* explicacao1 = al_load_bitmap("src/explicacao1.png");
    ALLEGRO_BITMAP* explicacao2 = al_load_bitmap("src/fase1 conclusão.png");


    //Carregar as imagens da conclusão (Fase 2)
    ALLEGRO_BITMAP* conclusao1 = al_load_bitmap("src/fase2 - 1.png");
    ALLEGRO_BITMAP* conclusao2 = al_load_bitmap("src/fase 2 - 2.png");
    ALLEGRO_BITMAP* conclusao3 = al_load_bitmap("src/fase2 - 3.png");
    ALLEGRO_BITMAP* conclusao4 = al_load_bitmap("src/fase 2 encontro.png");
    ALLEGRO_BITMAP* conclusao5 = al_load_bitmap("src/fase 2 fala 1.png");
    ALLEGRO_BITMAP* conclusao6 = al_load_bitmap("src/fase 2 fala 2.png");
    ALLEGRO_BITMAP* conclusao7 = al_load_bitmap("src/fase 2 fala 3.png");




    //Carregar imagem do fim
    ALLEGRO_BITMAP* fimpng = al_load_bitmap("src/bg-fim.png");
    ALLEGRO_BITMAP* restart = al_load_bitmap("src/restart.png");




    // Carregar as imagens de fundo das fases
    ALLEGRO_BITMAP* level_1 = al_load_bitmap("src/fase1-semPorta.png");
    ALLEGRO_BITMAP* level_parede1 = al_load_bitmap("src/fase1-porta.png");
    ALLEGRO_BITMAP* level_2 = al_load_bitmap("src/fase1-semPorta.png");
    ALLEGRO_BITMAP* level_parede2 = al_load_bitmap("src/fase1-porta.png");
    ALLEGRO_BITMAP* level_3 = al_load_bitmap("src/fase1-semPorta.png");
    ALLEGRO_BITMAP* level_parede3 = al_load_bitmap("src/fase1-porta.png");


    if (!introducao1 || !introducao2 || !introducao3 || !introducao4 || !introducao6 || !introducao7 || !introducao8 || !introducao9 ||
        !explicacao1 || !explicacao2 || !conclusao1 || !conclusao2 || !conclusao3 || !conclusao4 || !conclusao5 || !conclusao6 || !conclusao7 ||
        !fimpng || !level_1 || !level_parede1 || !level_2 || !level_parede2 || !level_3 || !level_parede3) {
        fprintf(stderr, "Falha ao carregar a tela de fim de jogo.\n");
        al_destroy_bitmap(sprite_felipe);
        al_destroy_bitmap(sprite_bowling_ball);
        al_destroy_bitmap(sprite_pity);
        al_destroy_bitmap(sprite_pity);
        al_destroy_bitmap(introducao1);
        al_destroy_bitmap(introducao2);
        al_destroy_bitmap(introducao3);
        al_destroy_bitmap(introducao4);
        al_destroy_bitmap(introducao6);
        al_destroy_bitmap(introducao7);
        al_destroy_bitmap(introducao8);
        al_destroy_bitmap(introducao9);
        al_destroy_bitmap(explicacao1);
        al_destroy_bitmap(explicacao2);
        al_destroy_bitmap(conclusao1);
        al_destroy_bitmap(conclusao2);
        al_destroy_bitmap(conclusao3);
        al_destroy_bitmap(conclusao4);
        al_destroy_bitmap(conclusao5);
        al_destroy_bitmap(conclusao6);
        al_destroy_bitmap(conclusao7);
        al_destroy_bitmap(fimpng);
        al_destroy_bitmap(restart);
        al_destroy_bitmap(level_parede1);
        al_destroy_bitmap(level_parede2);
        al_destroy_bitmap(level_parede3);
        al_destroy_bitmap(level_1);
        al_destroy_bitmap(level_2);
        al_destroy_bitmap(level_3);


        al_destroy_display(display);
        return -1;
    }

    // Carregar a tela de fim de jogo
    ALLEGRO_BITMAP* end_screen = al_load_bitmap("src/restart.png");
    if (!end_screen) {
        fprintf(stderr, "Falha ao carregar a tela de fim de jogo.\n");
        al_destroy_bitmap(sprite_felipe);
        al_destroy_bitmap(sprite_bowling_ball);
        al_destroy_bitmap(sprite_pity);
        al_destroy_bitmap(sprite_pity);
        al_destroy_bitmap(introducao1);
        al_destroy_bitmap(introducao2);
        al_destroy_bitmap(introducao3);
        al_destroy_bitmap(introducao4);
        al_destroy_bitmap(introducao6);
        al_destroy_bitmap(introducao7);
        al_destroy_bitmap(introducao8);
        al_destroy_bitmap(introducao9);
        al_destroy_bitmap(explicacao1);
        al_destroy_bitmap(explicacao2);
        al_destroy_bitmap(conclusao1);
        al_destroy_bitmap(conclusao2);
        al_destroy_bitmap(conclusao3);
        al_destroy_bitmap(conclusao4);
        al_destroy_bitmap(conclusao5);
        al_destroy_bitmap(conclusao6);
        al_destroy_bitmap(conclusao7);
        al_destroy_bitmap(fimpng);
        al_destroy_bitmap(restart);
        al_destroy_bitmap(level_parede1);
        al_destroy_bitmap(level_parede2);
        al_destroy_bitmap(level_parede3);
        al_destroy_bitmap(level_1);
        al_destroy_bitmap(level_2);
        al_destroy_bitmap(level_3);


        al_destroy_display(display);
        return -1;
    }

    // Carregar a tela inicial
    ALLEGRO_BITMAP* start_screen = al_load_bitmap("src/menu_final.png");
    if (!start_screen) {
        fprintf(stderr, "Falha ao carregar a tela inicial.\n");
        al_destroy_bitmap(sprite_felipe);
        al_destroy_bitmap(sprite_bowling_ball);
        al_destroy_bitmap(sprite_pity);
        al_destroy_bitmap(introducao1);
        al_destroy_bitmap(introducao2);
        al_destroy_bitmap(introducao3);
        al_destroy_bitmap(introducao4);
        al_destroy_bitmap(introducao6);
        al_destroy_bitmap(introducao7);
        al_destroy_bitmap(introducao8);
        al_destroy_bitmap(introducao9);
        al_destroy_bitmap(explicacao1);
        al_destroy_bitmap(explicacao2);
        al_destroy_bitmap(conclusao1);
        al_destroy_bitmap(conclusao2);
        al_destroy_bitmap(conclusao3);
        al_destroy_bitmap(conclusao4);
        al_destroy_bitmap(conclusao5);
        al_destroy_bitmap(conclusao6);
        al_destroy_bitmap(conclusao7);
        al_destroy_bitmap(fimpng);
        al_destroy_bitmap(restart);
        al_destroy_bitmap(level_parede1);
        al_destroy_bitmap(level_1);
        al_destroy_bitmap(level_2);
        al_destroy_bitmap(level_3);
        al_destroy_bitmap(level_parede2);
        al_destroy_bitmap(level_parede3);
        al_destroy_display(display);
        al_destroy_bitmap(end_screen);
        return -1;
    }

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    bool start_game = false;
    bool exit = false;
    bool draw = true;
    int level = 1;

    // Loop da tela inicial
    while (!start_game && !exit) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        // Verificar saída do jogo
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            exit = true;
        }
        // Verificar clique do mouse
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mouse_x = event.mouse.x;
            int mouse_y = event.mouse.y;

            // Verificar se o clique do mouse está dentro da área do botão start
            if (mouse_x >= start_button_x1 && mouse_x <= start_button_x2 &&
                mouse_y >= start_button_y1 && mouse_y <= start_button_y2) {
                start_game = true;
            }
        }

        // draw a tela inicial
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap(start_screen, 0, 0, 0);
        al_flip_display();
    }

    // Verificar se o jogador escolheu exit do jogo
    if (exit) {
        al_destroy_bitmap(sprite_felipe);
        al_destroy_bitmap(sprite_bowling_ball);
        al_destroy_bitmap(sprite_pity);
        al_destroy_bitmap(introducao1);
        al_destroy_bitmap(introducao2);
        al_destroy_bitmap(introducao3);
        al_destroy_bitmap(introducao4);
        al_destroy_bitmap(introducao6);
        al_destroy_bitmap(introducao7);
        al_destroy_bitmap(introducao8);
        al_destroy_bitmap(introducao9);
        al_destroy_bitmap(explicacao1);
        al_destroy_bitmap(explicacao2);
        al_destroy_bitmap(conclusao1);
        al_destroy_bitmap(conclusao2);
        al_destroy_bitmap(conclusao3);
        al_destroy_bitmap(conclusao4);
        al_destroy_bitmap(conclusao5);
        al_destroy_bitmap(conclusao6);
        al_destroy_bitmap(conclusao7);
        al_destroy_bitmap(fimpng);
        al_destroy_bitmap(restart);
        al_destroy_bitmap(level_parede1);
        al_destroy_bitmap(level_1);
        al_destroy_bitmap(level_2);
        al_destroy_bitmap(level_3);
        al_destroy_bitmap(level_parede2);
        al_destroy_bitmap(level_parede3);
        al_destroy_bitmap(start_screen);
        al_destroy_bitmap(end_screen);
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        al_destroy_timer(timer);
        return 0;
    }

    // Destruir a tela inicial, pois não será mais necessária
    al_destroy_bitmap(start_screen);


    // Variáveis do Felipe
    float felipe_x = 20;
    float felipe_y = floor;
    float speed_felipe_y = 0;
    bool flag_jump = false;
    bool sprite_right_rotation = true;
    int frame_x = 0;
    int frame_y = 0;
    int count_frames = 0;
    int time_between_frames = 8;

    bool right_key = false;
    bool left_key = false;

    // Loop principal do jogo
    while (!exit) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            exit = true;
        }
        else if (event.type == ALLEGRO_EVENT_TIMER) {
            // Atualizar a posição do personagem com base nas teclas pressionadas
            if (right_key) {
                felipe_x += speed_felipe;
                sprite_right_rotation = true;
                if (!flag_jump) frame_y = 300;
            }

            if (left_key) {
                felipe_x -= speed_felipe;
                sprite_right_rotation = false;
                if (!flag_jump) frame_y = 450;
            }

            // Aplicar gravity enquanto no ar
            if (flag_jump) {
                speed_felipe_y += gravity_felipe;
                frame_y = sprite_right_rotation ? 601 : 751; // Animação de pulo no sprite
            }
            felipe_y += speed_felipe_y;

            // Verificar colisão com o chão
            if (felipe_y >= floor) {
                felipe_y = floor;
                speed_felipe_y = 0;
                flag_jump = false;
                frame_y = sprite_right_rotation ? 300 : 450; // Voltar à animação de andar
            }

            // Verificar se o jogador chegou ao final da fase
            if (felipe_x >= width_screen - width_sprite_felipe) {
                //Aumenta a fase atual
                if (level < 20) {
                    felipe_x = 10;
                    level++;
                }
                else {
                    // Ir para a tela de fim de jogo após completar a última fase
                    break;
                }
            }

            // Alternar entre os frames de animação de andar
            count_frames++;
            if (count_frames >= time_between_frames) {
                if (right_key || left_key) {
                    frame_x = (frame_x + 1) % num_walk_sprites_felipe;
                }
                else if (flag_jump) {
                    frame_x = (frame_x + 1) % num_jump_sprites_felipe;
                }
                count_frames = 0;
            }

            draw = true;
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                exit = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                right_key = true;
                break;
            case ALLEGRO_KEY_LEFT:
                left_key = true;
                break;
            case ALLEGRO_KEY_SPACE:
                if (!flag_jump) {
                    speed_felipe_y = jump_height;
                    flag_jump = true;
                }
                break;
            }
        }
        else if (event.type == ALLEGRO_EVENT_KEY_UP) {
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_RIGHT:
                right_key = false;
                break;
            case ALLEGRO_KEY_LEFT:
                left_key = false;
                break;
            }
        }

        //Implementação da tecla enter e as fases que ela pode ser usada

        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                if (level == 2) {

                    level += 5;
                }

            }
        }
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                if (level == 1 || level == 3 || level == 5 || level == 6 || level == 8 || level == 11 || level == 12 || level == 13 || level == 14 || level == 15 || level == 17
                    || level == 18 || level == 19 || level == 20) {

                    level++;
                }

            }
        }







        // desenha a tela apenas quando necessário
        if (draw && al_is_event_queue_empty(event_queue)) {
            draw = false;

            // Limpar a tela
            al_clear_to_color(al_map_rgb(0, 0, 0));

            //Telas da introdução
            //Tela 1 - Introdução
            if (level == 1) {
                al_draw_bitmap(introducao1, 0, 0, 0);
                felipe_y = 1200;

            }

            //Tela 2 - Introdução
            if (level == 2) {
                al_draw_bitmap(introducao2, 0, 0, 0);



            }

            //Tela 3 - Introdução
            if (level == 3) {
                al_draw_bitmap(introducao3, 0, 0, 0);
                felipe_y = 1200;
                felipe_x = 20;

            }

            //Tela 4 - Introdução
            if (level == 4) {
                al_draw_bitmap(introducao4, 0, 0, 0);

                if (felipe_x == 700) {
                    level++;
                }

            }


            //Tela 5 - Introdução
            if (level == 5) {
                al_draw_bitmap(introducao6, 0, 0, 0);
                felipe_y = 1200;
                felipe_x = 20;

            }

            //Tela 6 - Introdução
            if (level == 6) {
                al_draw_bitmap(introducao7, 0, 0, 0);
                felipe_y = 1200;
                felipe_x = 20;

            }

            //Tela 7 - Introdução
            if (level == 7) {
                al_draw_bitmap(introducao8, 0, 0, 0);



                if (felipe_x == 1000) {
                    felipe_x = 20;
                    level++;
                }

            }
            //Tela 8 - Introdução
            if (level == 8) {
                al_draw_bitmap(introducao9, 0, 0, 0);
                felipe_y = 1200;
                felipe_x = 20;

            }




            // desenha o cenário da fase atual

            //fase 1

            if (level == 9) {
                al_draw_bitmap(level_parede1, 0, 0, 0);

                //ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);
              // al_draw_filled_rectangle(felipe_x + 15, felipe_y, felipe_x + width_sprite_felipe - 20, felipe_y + height_sprite_felipe, red);
              /* al_draw_filled_rectangle(pos_pity_x, pos_pity_y - pity_y, pos_pity_x + 57, pos_pity_y - pity_y + 25, red);
               al_draw_filled_rectangle(pos_bowling_ball_x + 48, pos_bowling_ball_y - bowling_ball_y, pos_bowling_ball_x + 106, pos_bowling_ball_y - bowling_ball_y + 58, red); */

                if (bowling_ball_y <= -750) {
                    pos_bowling_ball_x = 100 + rand() % (950 - 100 + 200);
                    bowling_ball_y = -50;
                    bowling_ball_y -= gravity_bowling_ball;
                    count_bowling_ball++;
                    printf("%d ", count_bowling_ball);
                }

                if (pity_y <= -750) {
                    pos_pity_x = 100 + rand() % (950 - 100 + 200);
                    pity_y = -50;
                    pity_y -= gravity_pity;
                }

                //Limita a parede da esquerda
                if (felipe_x <= -10) {
                    left_key = false;
                    felipe_x += speed_felipe;
                }

                //Limita a parede da direita e libera a passagem após a bola de boliche cair 10 vezes
                if (count_bowling_ball <= 10) {
                    if (felipe_x >= 1100) {
                        right_key = false;
                        felipe_x -= speed_felipe;
                    }
                }

                //Muda o cenário quando a bola de boliche chega 10 vezes ao chão
                if (count_bowling_ball > 10) {
                    al_draw_bitmap(level_1, 0, 0, 0);
                }

                if (felipe_x + width_sprite_felipe - 20 >= pos_pity_x + 57 &&
                    felipe_x <= pos_pity_x &&
                    felipe_y + height_sprite_felipe >= pos_pity_y - pity_y + 25 &&
                    felipe_y <= pos_pity_y - pity_y) {
                    printf("Colidiu");
                    al_draw_bitmap(restart, 0, 0, 0);
                    exit = true;
                }



                if (felipe_x + width_sprite_felipe - 20 >= pos_bowling_ball_x + 106 &&
                    felipe_x <= pos_bowling_ball_x + 48 &&
                    felipe_y + height_sprite_felipe >= pos_bowling_ball_y - bowling_ball_y + 58 &&
                    felipe_y <= pos_bowling_ball_y - bowling_ball_y) {
                    al_draw_bitmap(restart, 0, 0, 0);
                    exit = true;
                }

                al_draw_bitmap_region(sprite_bowling_ball, bowling_ball_x, bowling_ball_y, 5000, 5000, pos_bowling_ball_x, pos_bowling_ball_y, 0);
                al_draw_bitmap_region(sprite_pity, pity_x, pity_y, 5000, 5000, pos_pity_x, pos_pity_y, 0);

                bowling_ball_y -= gravity_bowling_ball;
                pity_y -= gravity_pity;

            }

            //fase2

            else if (level == 10) {
                al_draw_bitmap(level_parede2, 0, 0, 0);
                int gravity_bowling_ball = 15;
                int gravity_pity = 8;

                if (bowling_ball_y <= -750) {
                    pos_bowling_ball_x = 100 + rand() % (950 - 100 + 200);
                    bowling_ball_y = -50;
                    bowling_ball_y -= gravity_bowling_ball;
                    count_bowling_ball++;
                    printf("%d ", count_bowling_ball);
                }

                if (pity_y <= -750) {
                    pos_pity_x = 100 + rand() % (950 - 100 + 200);
                    pity_y = -50;
                    pity_y -= gravity_pity;
                }

                if (felipe_x + width_sprite_felipe - 20 >= pos_pity_x + 57 &&
                    felipe_x <= pos_pity_x &&
                    felipe_y + height_sprite_felipe >= pos_pity_y - pity_y + 25 &&
                    felipe_y <= pos_pity_y - pity_y) {
                    printf("Colidiu");
                    al_draw_bitmap(restart, 0, 0, 0);
                    exit = true;
                }

                if (felipe_x + width_sprite_felipe - 20 >= pos_bowling_ball_x + 106 &&
                    felipe_x <= pos_bowling_ball_x + 48 &&
                    felipe_y + height_sprite_felipe >= pos_bowling_ball_y - bowling_ball_y + 58 &&
                    felipe_y <= pos_bowling_ball_y - bowling_ball_y) {
                    al_draw_bitmap(restart, 0, 0, 0);
                    exit = true;
                }



                //Limita a parede da esquerda
                if (felipe_x <= -10) {
                    left_key = false;
                    felipe_x += speed_felipe;
                }

                //Limita a parede da direita e libera a passagem após a bola de boliche cair 10 vezes
                if (count_bowling_ball <= 20) {
                    if (felipe_x >= 1100) {
                        right_key = false;
                        felipe_x -= speed_felipe;
                    }
                }

                //Muda o cenário quando a bola de boliche chega 20 vezes ao chão
                if (count_bowling_ball > 20) {
                    al_draw_bitmap(level_2, 0, 0, 0);
                }

                al_draw_bitmap_region(sprite_bowling_ball, bowling_ball_x, bowling_ball_y, 5000, 5000, pos_bowling_ball_x, pos_bowling_ball_y, 0);
                al_draw_bitmap_region(sprite_pity, pity_x, pity_y, 5000, 5000, pos_pity_x, pos_pity_y, 0);

                bowling_ball_y -= gravity_bowling_ball;
                pity_y -= gravity_pity;

            }

            //fase 3

            else if (level == 11) {
                al_draw_bitmap(level_parede3, 0, 0, 0);
                int gravity_bowling_ball = 18;
                int gravity_pity = 10;


                if (bowling_ball_y <= -750) {
                    pos_bowling_ball_x = 100 + rand() % (950 - 100 + 200);
                    bowling_ball_y = -50;
                    bowling_ball_y -= gravity_bowling_ball;
                    count_bowling_ball++;
                    printf("%d ", count_bowling_ball);
                }

                if (pity_y <= -750) {
                    pos_pity_x = 100 + rand() % (950 - 100 + 200);
                    pity_y = -50;
                    pity_y -= gravity_pity;
                }

                if (felipe_x + width_sprite_felipe - 20 >= pos_pity_x + 57 &&
                    felipe_x <= pos_pity_x &&
                    felipe_y + height_sprite_felipe >= pos_pity_y - pity_y + 25 &&
                    felipe_y <= pos_pity_y - pity_y) {
                    printf("Colidiu");
                    al_draw_bitmap(restart, 0, 0, 0);
                    exit = true;
                }

                if (felipe_x + width_sprite_felipe - 20 >= pos_bowling_ball_x + 106 &&
                    felipe_x <= pos_bowling_ball_x + 48 &&
                    felipe_y + height_sprite_felipe >= pos_bowling_ball_y - bowling_ball_y + 58 &&
                    felipe_y <= pos_bowling_ball_y - bowling_ball_y) {
                    al_draw_bitmap(restart, 0, 0, 0);
                    exit = true;
                }

                //Limita a parede da esquerda
                if (felipe_x <= -10) {
                    left_key = false;
                    felipe_x += speed_felipe;
                }

                //Limita a parede da direita e libera a passagem após a bola de boliche cair 10 vezes
                if (count_bowling_ball <= 40) {
                    if (felipe_x >= 1100) {
                        right_key = false;
                        felipe_x -= speed_felipe;
                    }
                }

                //Muda o cenário quando a bola de boliche chega 40 vezes ao chão
                if (count_bowling_ball > 40) {
                    al_draw_bitmap(level_3, 0, 0, 0);
                }

                al_draw_bitmap_region(sprite_bowling_ball, bowling_ball_x, bowling_ball_y, 5000, 5000, pos_bowling_ball_x, pos_bowling_ball_y, 0);
                al_draw_bitmap_region(sprite_pity, pity_x, pity_y, 5000, 5000, pos_pity_x, pos_pity_y, 0);

                bowling_ball_y -= gravity_bowling_ball;
                pity_y -= gravity_pity;
            }

            if (level == 12) {
                al_draw_bitmap(explicacao1, 0, 0, 0);
                felipe_x = 20;
                felipe_y = 1200;



            }

            if (level == 13) {
                al_draw_bitmap(explicacao2, 0, 0, 0);
                felipe_x = 20;
                felipe_y = 1200;



            }
            if (level == 14) {
                al_draw_bitmap(conclusao1, 0, 0, 0);
                felipe_x = 20;
                felipe_y = 1200;

            }

            if (level == 15) {
                al_draw_bitmap(conclusao3, 0, 0, 0);
                felipe_x = 20;

            }
            if (level == 16) {
                al_draw_bitmap(conclusao2, 0, 0, 0);


            }

            if (level == 17) {
                al_draw_bitmap(conclusao4, 0, 0, 0);
                felipe_y = 1200;


            }

            if (level == 18) {
                al_draw_bitmap(conclusao5, 0, 0, 0);
                felipe_y = 1200;


            }
            if (level == 19) {
                al_draw_bitmap(conclusao6, 0, 0, 0);
                felipe_y = 1200;


            }

            if (level == 20) {
                al_draw_bitmap(conclusao7, 0, 0, 0);
                felipe_y = 1200;

            }

            if (level == 21) {
                felipe_y = 1200;
                exit = true;
            }



            // draw o personagem
            al_draw_bitmap_region(sprite_felipe, frame_x * width_sprite_felipe, frame_y, width_sprite_felipe, height_sprite_felipe, felipe_x, felipe_y, 0);

            // Atualizar a tela
            al_flip_display();
        }
    }

    // Exibir a tela de fim de jogo
    bool fim_jogo = true;
    while (fim_jogo) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            fim_jogo = false;
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN || event.type == ALLEGRO_EVENT_KEY_DOWN) {
            fim_jogo = false;
        }

        // draw a tela de fim

        if (level >= 20) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(fimpng, 0, 0, 0);
            al_flip_display();
        }
    }

    // Destruir recursos
    al_destroy_bitmap(sprite_felipe);
    al_destroy_bitmap(sprite_bowling_ball);
    al_destroy_bitmap(sprite_pity);
    al_destroy_bitmap(introducao1);
    al_destroy_bitmap(introducao2);
    al_destroy_bitmap(introducao3);
    al_destroy_bitmap(introducao4);
    al_destroy_bitmap(introducao6);
    al_destroy_bitmap(introducao7);
    al_destroy_bitmap(introducao8);
    al_destroy_bitmap(introducao9);
    al_destroy_bitmap(explicacao1);
    al_destroy_bitmap(explicacao2);
    al_destroy_bitmap(conclusao1);
    al_destroy_bitmap(conclusao2);
    al_destroy_bitmap(conclusao3);
    al_destroy_bitmap(conclusao4);
    al_destroy_bitmap(conclusao5);
    al_destroy_bitmap(conclusao6);
    al_destroy_bitmap(conclusao7);
    al_destroy_bitmap(fimpng);
    al_destroy_bitmap(restart);
    al_destroy_bitmap(level_parede1);
    al_destroy_bitmap(level_1);
    al_destroy_bitmap(level_2);
    al_destroy_bitmap(level_3);
    al_destroy_bitmap(level_parede2);
    al_destroy_bitmap(level_parede3);
    al_destroy_bitmap(end_screen);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);

    return 0;
}