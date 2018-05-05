#include <allegro.h>
#include <jpgalleg.h>
#include <stdio.h>



// =======================================================================================  Declaração de Constantes  ========================================================================================= //
// Tamanho Personagem do Jogador //
#define SPRITE_LARGURA 35
#define SPRITE_ALTURA 50

// Tamanho dos NPC ou Sprites Diversos //
#define SPRITE_NPC_LARGURA 25
#define SPRITE_NPC_ALTURA 10

// Velocidade da Corrida usando SHIFT do personagem //
#define VELOCIDADE_AUMENTADA 8

// Tipo dos Terrenos // 
#define TERRENO_ARENOSO 2;
#define TERRENO_NORMAL 5;
#define TERRENO_AEREO 7;

// Tamanho da Screen //
#define TELA_LARGURA 800
#define TELA_ALTURA 600

// Taxa de Frames por Segundo //
#define FPS 15


//  ================================================================================================================================================================================================// 
// =========================================================================== Outras Funções e Váriáveis Globais para Temporizadores  ======================================================================== //
//  Inicializadores e Finalizadores //
void init();
void deinit();


// Variavel Global (Timers) // 
volatile int fps_jogo;


//  ================================================================================================================================================================================================// 
//  ==============================================================================================  Temporizador  ============================================================================================ //
// Função Temporizador FPS //
void Estabilizador_FPS (){
        fps_jogo++;
}
END_OF_FUNCTION(Estabilizador_FPS);  


//  ================================================================================================================================================================================================// 
//  =====================================================================================  Conjunto de Structs (Registradores)  =============================================================================== //
// Struct de Informações sobre Sprites  //
struct informacaoSprite {
    int x;
    int y;
    int largura;
    int altura;
    int lado;
    int animacao;
    int delayanimacao;
    int terreno;
    int vigor;
    int energia;
    int colisao_para_conversar;
    int posicao_conversa;
    int velocidade_animacao;
    int moedas;
    int loot;
    int fala;
    int nivel;
    int habilidade1;
    int habilidade2;
    int habilidade3;
    int habilidade4;
    int habilidade5;
    int experiencia_atual;
    int experiencia_proximo_nivel;
    int experiencia_atual_porcentagem;
    int obter_experiencia;
    BITMAP *ataque1 [3];
    BITMAP *face [3];
};

// Struct de Interação com Objetos //
struct interacaoObjeto {
    int x;
    int y;
    int estado;
    int animacao;
    int animacao_delay;
    int animacao_brilho;
    int animacao_brilho_delay;
    int recompensaHabilidade;
    int recompensaVigor;
};

// Informações sobre o jogo de carta //
typedef struct {
    int ComparaId[2];
    int x;
    int y;
    int C1;
    int L1;
    int L2;
    int C2;
    int estadoClique;
    int Ponto;
    int colisao;
    int contClique;
    int testa_fim;   
} informacaoJogoCarta;

// Struct de Cartas //
typedef struct {
    int posicaoX;
    int posicaoY;
    int estado;
    int id;
    BITMAP *CartasSel;
} TCartas[4][4];

// Define Tipo Ranking //
typedef struct {
    char nome [15];
    int  ponto;
} Treg_ranking;

// Define Arquivo //
typedef FILE *Tarq_ranking;

//  ================================================================================================================================================================================================// 
//  =============================================================================================  Protótips de Funções  ====================================================================================== //
void titulo_jogo (BITMAP *buffer_atual, int posicao_x, int posicao_y);
void quem_somos  (BITMAP *buffer_atual);
void menu_inicial_abrindo (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *efeito_sonoro);
void menu_inicial_fechando (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *efeito_sonoro); 
void pontuacao_corrida (BITMAP *buffer_atual, int pontuacao_jogador, int pontuacao_adversario);
void pontuacao_cartas (BITMAP *buffer_atual, int pontuacao);
void efeito_ponto_positivo (BITMAP *buffer_atual, int *animacao, int *delay_animacao, int posicao_x, int posicao_y);
void efeito_ponto_negativo (BITMAP *buffer_atual, int *animacao, int *delay_animacao, int posicao_x, int posicao_y); 
void jogo_memoria (BITMAP *buffer_atual, TCartas informacaoCarta, informacaoJogoCarta *dadosJogoCarta, int *delay_ver_cartas, int *animacao, int *delay_animacao, int *posicao_x_efeito_carta_selecionada, int *posicao_y_efeito_carta_selecionada, int *efeito_carta_selecionada, int *efeito_ponto_positivo, int *efeito_ponto_negativo);
void efeito_carta_selecionada (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao);
void jogo_pergunta_resposta (BITMAP *buffer_atual, int *opcao_escolhida, int *pergunta, int *ponto, int *animacao_acerto_esquerda, int *animacao_acerto_esquerda_delay, int *animacao_acerto_direita, int *animacao_acerto_direita_delay, int *animacao_erro_esquerda, int *animacao_erro_esquerda_delay, int *animacao_erro_direita, int *animacao_erro_direita_delay,  int *animacao_cursor, int *delay_animacao_cursor, int *animacao_ponto_positivo, int *animacao_ponto_positivo_delay, int *animacao_ponto_negativo, int *animacao_ponto_negativo_delay);
void jogo_pergunta_resposta_pontuacao (BITMAP *buffer_atual, int pontuacao); 
void efeito_erro_esquerda (BITMAP *buffer_atual, int *animacao, int *delay_animacao);
void efeito_erro_direita (BITMAP *buffer_atual, int *animacao, int *delay_animacao);
void efeito_acerto_esquerda (BITMAP *buffer_atual, int *animacao, int *delay_animacao);  
void efeito_acerto_direita (BITMAP *buffer_atual, int *animacao, int *delay_animacao);
void resultado_corrida (BITMAP *buffer_atual, int resultado_corrida, int *animacao, int *delay_animacao);
void nivel_corrida (BITMAP *buffer_atual, int nivel);
void efeito_texto_sonho (BITMAP *buffer_atual, int *animacao, int *delay_animacao, int posicao_x, int posicao_y);
void movimentarJogador (int *x, int *y, int *lado, int *animacao, int *terreno, int *animacao_andar_delay);
void movimentarSpriteAutomaticamente(int *x, int *y, int *lado, int *animacao, int *delayanimacao, int terreno, int sentido, int posicao_inicial, int posicao_final, int tempo_espera, int *delayanimacao_2, int velocidade_animacao);
void fadeout (int velocidade);
void fadein(BITMAP *bmp_orig, int velocidade);
void interacaoNpc (int ladoPersonagem, int *ladoNpc, BITMAP *fala_sprite, BITMAP *buffer_atual, BITMAP *face_sprite, char texto_fala_lin_1 [50], char texto_fala_lin_2 [50], char texto_fala_lin_3 [50], char texto_fala_lin_4 [50], char texto_fala_lin_5 [50], DATAFILE *fonte, int continuidade_conversa, int *atual_conversa, int *animacao_tecla, int *animacao_tecla_delay, int mudar_fala, int *personagem_fala);
void interacaoIniciadaAutomaticamenteNpc (int ladoPersonagem, int *ladoNpc, BITMAP *fala_sprite, BITMAP *buffer_atual, BITMAP *face_sprite, char texto_fala_lin_1 [50], char texto_fala_lin_2 [50], char texto_fala_lin_3 [50], char texto_fala_lin_4 [50], char texto_fala_lin_5 [50], DATAFILE *fonte, int continuidade_conversa, int *atual_conversa, int *animacao_tecla, int *animacao_tecla_delay);
void efeito_ceu_parallax (BITMAP *buffer_atual, int *animacao_ceu_1_parallax, int *animacao_ceu_1_parallax_delay, int *animacao_ceu_2_parallax, int *animacao_ceu_2_parallax_delay );
void efeito_nuvens_parallax (BITMAP *buffer_atual, int *animacao);
void efeito_pressione_enter (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao);
void efeito_tutorial_parallax (BITMAP *buffer_atual, int *animacao);
void efeito_vitoria_parallax (BITMAP *buffer_atual, int *animacao);
void efeito_estrelas_parallax (BITMAP *buffer_atual, int *animacao);
void efeito_bola_parallax (BITMAP *buffer_atual, int *animacao);
void efeito_faixa_ranking_parallax (BITMAP *buffer_atual, int *animacao);
void efeito_fim (BITMAP *buffer_atual);
void tutorial_minigame_ginasio_0 (BITMAP *buffer_atual, int posicao_tutorial);
void tutorial_minigame_ginasio_1 (BITMAP *buffer_atual, int posicao_tutorial);
void tutorial_minigame_ginasio_fim (BITMAP *buffer_atual, int posicao_tutorial);
void tutorial_minigame_memoria (BITMAP *buffer_atual, int posicao_tutorial);
void jogo_memoria_fim (BITMAP *buffer_atual);
void tutorial_habilidade1 (BITMAP *buffer_atual, int posicao_tutorial);
void tutorial_chuva (BITMAP *buffer_atual);
void animacao_tecla_esc (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *animacao_delay);
void animacao_tecla_enter (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *animacao_delay);
void efeito_sombra_ginasio (BITMAP *buffer_atual, int posicao_x, int posicao_y); 
void efeito_agua (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao_1, int *delay_animacao_1, int *animacao_2, int *delay_animacao_2);
void efeito_fogo(BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao);
void efeito_chuva_noite (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao);
void efeito_relampago(BITMAP *buffer_atual, int *animacao, int *delay_animacao);
void efeito_luz_poste (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao); 
void efeito_pilar_de_fogo_azul(BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao);
void efeito_pilar_de_fogo_amarelo(BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao);
void efeito_balao_exclamacao(BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao);
void efeito_balao_reticencias (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao);
void efeito_balao_gota (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao);
void efeito_balao_nervoso (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao);
void efeito_balao_coracao (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao);
void efeito_subiu_nivel (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao); 
void efeito_torcedora(BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao);
void efeito_geovana (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao);
void efeito_jogadores_direita_ginasio (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao);
void efeito_jogadores_esquerda_ginasio (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao);
void efeito_jogadores_embaixo_ginasio (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao);
void efeito_jogadores_encima_ginasio (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao);
void efeito_choro(BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao);
void efeito_barra_de_status_personagem (BITMAP *buffer_atual, int vigor_personagem, int energia_personagem, int *animacao, int *delay_animacao, int moedas, DATAFILE *fonte, int porcentagem_experiencia, int nivel);
void efeito_ataque (BITMAP *buffer_atual, int *posicao_bola_x, int *posicao_bola_y, int *delayanimacao, int *energia, int lado_personagem, int *animacao_personagem, BITMAP *bola [3], int *animacao, int *animacao_2); 
void efeito_moeda(BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao);
void efeito_bau (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao, int *animacao_brilho, int *delay_animacao_brilho, int acao_abrir); 
void efeito_ganhar_habilidade (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao); 
void efeito_habilidade_1_ativa (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao);
void efeito_contagem_regressiva (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao);
void detectarColisaoEntrarSair(int *x1, int *y1, int *altura1, int *largura1, int x2, int y2, int altura2, int largura2,int *mapa_atual, int mapa_destino);
void detectarColisaoInteracaoObjetoCima(int *x1, int *y1, int *altura1, int *largura1, int x2, int y2, int altura2, int largura2,int lado_personagem, int *acao);
void ranking_nomes (BITMAP *buffer_atual);
void rotina_ler_teclado(char nome [], int *indice_vetor);
void efeito_numeros (BITMAP *buffer_atual, int *animacao, int *delay_animacao, int posicao_x, int posicao_y);
void ordenaVetor(Treg_ranking vet[]);
void salvar_ranking (BITMAP *buffer_atual, int ponto, char nome [15]);
void mostrar_pontuacao_ranking (BITMAP *buffer_atual, DATAFILE *fonte);

int detectarColisaoCartas (int x1, int y1, int altura1, int largura1,int x2, int y2, int altura2, int largura2);
int detectarColisaoMoeda(BITMAP *buffer_atual, int x1, int y1, int altura1, int largura1, int x2, int y2, int altura2, int largura2, int *moeda_personagem, int moeda_adquirida); 
int detectarColisao (int *x1, int *y1, int *altura1, int *largura1,int x2, int y2, int altura2, int largura2, int terreno, int lado, int *animacao);
int detectarColisaoSprite (int *x1, int *y1, int *altura1, int *largura1, int x2, int y2, int altura2, int largura2, int terreno, int *animacao);
int detectarColisaoNociva(int *x1, int *y1, int *altura1, int *largura1, int lado, int x2, int y2, int altura2, int largura2, int terreno, int *animacao, int *vigor);
int detectarColisaoAtaquePersonagem (BITMAP *buffer_atual, int *x1, int *y1, int *altura1, int *largura1, int lado, int x2, int y2, int altura2, int largura2, int terreno, int *animacao, int *vigor);
int detectarTerrenoArenoso(int *x1, int *y1, int *altura1, int *largura1, int x2, int y2, int altura2, int largura2, int *terreno, int lado);
int efeito_nuvens (BITMAP *buffer, int teste_efeito,  int velocidade_nuvem, int altura_nuvem, int tempo_espera, int *animacao_1, int *animacao_1_delay, int *animacao_2, int *animacao_2_delay, int *animacao_3, int *animacao_3_delay);
int efeito_bola_opcao_menu_principal (BITMAP *buffer_atual, int opcao_escolhida, int *animacao, int *delay_animacao);
int efeito_bola_opcao_menu_pequeno (BITMAP *buffer_atual, int opcao_escolhida, int *animacao, int *delay_animacao);
int efeito_bola_opcao_fim_de_jogo (BITMAP *buffer_atual, int opcao_escolhida, int *animacao, int *delay_animacao);
int pausa_menu (BITMAP *buffer_atual, int opcao_pausa_menu, int *animacao, int *animacao_delay);

float composicaoPonto(int, int);
//  =========================================================================================================================================================================================================== //
//  ===============================================================================================   INICIO DO PROGRAMA   ==================================================================================== //      
//  =========================================================================================================================================================================================================== //
int main() {
    
    init();
    jpgalleg_init();
    
    // Carrega estilos de fontes //
    DATAFILE *datFontes = NULL;
    datFontes = load_datafile("fontes.dat");

    
    // Criação de Variáveis //
    BITMAP *personagem   [4][8];
    BITMAP *mariana      [4][4];
    BITMAP *roberto      [4][4];
    BITMAP *alexandre    [4][4];
    BITMAP *ligeirinho   [4][4];
    BITMAP *inimigo      [4][4];
    BITMAP *npc1         [4][4];
    BITMAP *npc2         [4][4];
    BITMAP *npc3         [4][4];
    BITMAP *cachorro     [4][4];
    BITMAP *vespa        [4][4];
    BITMAP *desconhecido [4][4];
    BITMAP *fala_personagem [2];
    BITMAP *tela_inicial;
    BITMAP *porta [2];
    BITMAP *portao_ginasio [2];
    BITMAP *personagem_desmaiado;
    BITMAP *borda_menu;
    BITMAP *fundo_menu;
    BITMAP *cenario;
    BITMAP *cenario_efeito;
    BITMAP *nuvem_mapa;
    BITMAP *buffer = NULL;
    BITMAP *efeito_moeda_tela;

    // Sons //
    MIDI *audio_fundo; // Midi é usado para músicas de fundo.    
    SAMPLE *audio_efeito [10];     // Sample é usado para efeitos de som no jogo.
    
    audio_fundo = load_midi("Audios/Fundo/musica_abertura.mid");
    
    audio_efeito [0] = load_sample("Audios/Efeito/efeito_dormir.wav"); 
    audio_efeito [1] = load_sample("Audios/Efeito/efeito_apito.wav");
    audio_efeito [2] = load_sample("Audios/Efeito/efeito_escolha.wav");
    audio_efeito [3] = load_sample("Audios/Efeito/efeito_voltar.wav");
    audio_efeito [4] = load_sample("Audios/Efeito/efeito_abreporta.wav");
    audio_efeito [5] = load_sample("Audios/Efeito/efeito_aprendeuhabilidade.wav");
    audio_efeito [6] = load_sample("Audios/Efeito/efeito_uhuu.wav");
    audio_efeito [7] = load_sample("Audios/Efeito/efeito_chuva.wav");                                             
    
    // Double Buffer //
    buffer = create_bitmap(TELA_LARGURA,TELA_ALTURA);

    // Variáveis //
    int mapa_atual                           = 0;
    int progresso_global                     = 0;
    int progresso                            = 0;
    int animacao_local                       = 0;
    int cena_animada                         = 0;
    int cena_animada_informacoes_iniciais    = 0;
    int musica                               = 0;
    int caso_colisao                         = 0; // Através dessa variável recebo o retorno da fundação detectarColisao, que cria um quadradro imaginário para haver colisão.
    int caso_colisao_sprite                  = 0; // Através dessa variável recebo o retorno da função detectarColisaoSprite, que cria um quadradro imaginário em que qunado há colisão o Npc simplesmente para de andar (como um sensor)
    int caso_colisao_nociva                  = 0;
    int opcao                                = 0;
    int velocidade_tempo;
    int comparador_tempo;
    int velocidade_fps                       = 0;
    int posicao_tutorial                     = 0;   
    int teste_efeito_nuvem                   = 0;
    int altura_nuvem_1                       = 0;
    srand(time(NULL));
    int altura_nuvem_2                       = 1 + (int)( 550.0 * rand() / ( RAND_MAX + 1.0 ) );
    int cont                                 = 0;
    int interacao                            = 0;
    int efeito                               = 0;
    int efeito_sonoro                        = 0;
    int cont_destruir_x                      = 0;
    int cont_destruir_y                      = 0;
                        
    int mini_game_lado_quadra_jogador        = 0;
    int mini_game_ponto_jogador              = 0;
    
    int mini_game_lado_quadra_adversario     = 0;
    int mini_game_ponto_adversario           = 0;
    
    int mini_game_corrida_resultado          = 0;
    int mini_game_corrida_nivel              = 0;
    
    int mini_game_pergunta_resposta_opcao    = 0;
    int mini_game_pergunta_resposta_pergunta = 0;
    int mini_game_pergunta_resposta_ponto    = 0;
    
    // Variaveis Tela Inicial //
    int entrar               = 1;
    int entrar_2             = 0;
    int entrar_3             = 0;
    int entrar_4             = 0;
    int entrar_5             = 0;
    
    // Variaveis Introdução //
    int introducao_posicao   = 0;
    
    // Variavel Experiência //
    int experiencia_total    =  0;
    
    // Variaveis para Animações //
    int animacao_personagem_delay                  = 0;
    int animacao_npc_delay                         = 0;
    int animacao_vespa_delay                       = 0;
    
    int animacao_menu_abrindo                      = 0;
    int animacao_menu_abrindo_audio                = 0;
    
    int animacao_pressione_enter                   = 0;
    int animacao_pressione_enter_delay             = 0;
    
    int animacao_bola                              = 0;
    int animacao_bola_delay                        = 0;
    
    int animacao_ceu_1_parallax_delay              = 0;
    int animacao_ceu_1_parallax                    = 0;
    
    int animacao_ceu_2_parallax_delay              = 0;
    int animacao_ceu_2_parallax                    = 0;
    
    int animacao_tutorial_parallax                 = 0;
    int animacao_parallax_quem_somos               = 0;
    
    int animacao_choro                             = 0;
    int animacao_choro_delay                       = 0;
    
    int animacao_status                            = 0;
    int animacao_status_delay                      = 0;
    
    int animacao_chuva_noite                       = 0;
    int animacao_chuva_noite_delay                 = 0;
    
    int animacao_efeito_ataque                     = 0;
    int animacao_efeito_ataque_2                   = 0;
    
    int animacao_relampago                         = 0;
    int animacao_relampago_delay                   = 0;  
    
    int animacao_fogo [4];
    int animacao_fogo_delay [4];
    
    int animacao_luz_poste                         = 0;
    int animacao_luz_poste_delay                   = 0;
    
    int animacao_balao                             = 0;
    int animacao_balao_delay                       = 0; 
    
    int animacao_subiu_nivel                       = 21;
    int animacao_subiu_nivel_delay                 = 0;
    
    int animacao_torcedora [2];         
    int animacao_torcedora_delay [2];
    animacao_torcedora [0]                         = 0;
    animacao_torcedora [1]                         = 0; 
    animacao_torcedora_delay [0]                   = 0;
    animacao_torcedora_delay [1]                   = 5;
    
    int jogadores_direita_ginasio                  = 0;
    int jogadores_direita_ginasio_delay            = 0;
    int jogadores_esquerda_ginasio                 = 0;
    int jogadores_esquerda_ginasio_delay           = 0;
    
    int animacao_agua_1                            = 0;   
    int animacao_agua_1_delay                      = 0;
    int animacao_agua_2                            = 0;   
    int animacao_agua_2_delay                      = 0;
    
    int animacao_1_sombra_nuvem                    = 0;
    int animacao_1_sombra_nuvem_delay              = 0;
    int animacao_2_sombra_nuvem                    = 0;
    int animacao_2_sombra_nuvem_delay              = 0;
    int animacao_3_sombra_nuvem                    = 0;
    int animacao_3_sombra_nuvem_delay              = 0;
    
    int animacao_tecla_enter_pulsando              = 0;
    int animacao_tecla_enter_pulsando_delay        = 0;
    
    int animacao_tecla_esc_pulsando                = 0;
    int animacao_tecla_esc_pulsando_delay          = 0;
    
    int animacao_moeda                             = 0;
    int animacao_moeda_delay                       = 0;
    
    int animacao_ganha_habilidade                  = 0;
    int animacao_ganha_habilidade_delay            = 0;
    
    int animacao_habilidade1                       = 0;
    int animacao_habilidade1_delay                 = 0;
    
    int animacao_contagem_regressiva               = 0;
    int animacao_contagem_regressiva_delay         = 0;
    
    int animacao_mini_game_corrida_resultado       = 0;
    int animacao_mini_game_corrida_resultado_delay = 0;
    
    int delay_ver_carta                            = 0;
    int posicao_x_efeito_carta_selecionada         = 0;
    int posicao_y_efeito_carta_selecionada         = 0;
    int animacao_carta_selecionada                 = 9;
    int animacao_carta_selecionada_delay           = 0;
    
    int animacao_ponto_positivo                    = 11;
    int animacao_ponto_positivo_delay              = 0;
    
    int animacao_ponto_negativo                    = 11;
    int animacao_ponto_negativo_delay              = 0;
    
    int animacao_cursor_pergunta_resposta          = 0;
    int animacao_cursor_pergunta_resposta_delay    = 0;
    
    int animacao_acerto_esquerda                   = 16;
    int animacao_acerto_esquerda_delay             = 0;
    
    int animacao_acerto_direita                    = 16;
    int animacao_acerto_direita_delay              = 0;
    
    int animacao_erro_esquerda                     = 16;
    int animacao_erro_esquerda_delay               = 0;
    
    int animacao_erro_direita                      = 16;
    int animacao_erro_direita_delay                = 0;
    
    int animacao_texto_sonho                       = 11;
    int animacao_texto_sonho_delay                 = 0;
    
    int animacao_numeros_aleotorios                = 0;
    int animacao_numeros_aleotorios_delay          = 0;
    
    int indice_vetor                               = 0;
    
    char fala_sprite [50];
   
    
    // Carregando Personagem  //
    personagem [0][0] = load_bitmap("Imagens/Personagens/Principal/frente11.bmp",NULL);
    personagem [0][1] = load_bitmap("Imagens/Personagens/Principal/frente12.bmp",NULL);
    personagem [0][2] = load_bitmap("Imagens/Personagens/Principal/frente13.bmp",NULL);
    personagem [0][3] = load_bitmap("Imagens/Personagens/Principal/frente14.bmp",NULL);
    personagem [0][4] = load_bitmap("Imagens/Personagens/Principal/frente17.bmp",NULL);
    personagem [0][5] = load_bitmap("Imagens/Personagens/Principal/frente15.bmp",NULL);
    personagem [0][6] = load_bitmap("Imagens/Personagens/Principal/frente17.bmp",NULL);
    personagem [0][7] = load_bitmap("Imagens/Personagens/Principal/frente16.bmp",NULL);
    
    personagem [1][0] = load_bitmap("Imagens/Personagens/Principal/direita11.bmp",NULL);
    personagem [1][1] = load_bitmap("Imagens/Personagens/Principal/direita12.bmp",NULL);
    personagem [1][2] = load_bitmap("Imagens/Personagens/Principal/direita13.bmp",NULL);
    personagem [1][3] = load_bitmap("Imagens/Personagens/Principal/direita14.bmp",NULL);
    personagem [1][4] = load_bitmap("Imagens/Personagens/Principal/direita17.bmp",NULL);
    personagem [1][5] = load_bitmap("Imagens/Personagens/Principal/direita15.bmp",NULL);
    personagem [1][6] = load_bitmap("Imagens/Personagens/Principal/direita17.bmp",NULL);
    personagem [1][7] = load_bitmap("Imagens/Personagens/Principal/direita16.bmp",NULL);
        
    personagem [2][0] = load_bitmap("Imagens/Personagens/Principal/costas11.bmp",NULL);
    personagem [2][1] = load_bitmap("Imagens/Personagens/Principal/costas12.bmp",NULL);
    personagem [2][2] = load_bitmap("Imagens/Personagens/Principal/costas13.bmp",NULL);
    personagem [2][3] = load_bitmap("Imagens/Personagens/Principal/costas14.bmp",NULL);
    personagem [2][4] = load_bitmap("Imagens/Personagens/Principal/costas17.bmp",NULL);
    personagem [2][5] = load_bitmap("Imagens/Personagens/Principal/costas15.bmp",NULL);
    personagem [2][6] = load_bitmap("Imagens/Personagens/Principal/costas17.bmp",NULL);
    personagem [2][7] = load_bitmap("Imagens/Personagens/Principal/costas16.bmp",NULL);
    
    personagem [3][0] = load_bitmap("Imagens/Personagens/Principal/esquerda11.bmp",NULL);
    personagem [3][1] = load_bitmap("Imagens/Personagens/Principal/esquerda12.bmp",NULL);
    personagem [3][2] = load_bitmap("Imagens/Personagens/Principal/esquerda13.bmp",NULL);
    personagem [3][3] = load_bitmap("Imagens/Personagens/Principal/esquerda14.bmp",NULL);
    personagem [3][4] = load_bitmap("Imagens/Personagens/Principal/esquerda17.bmp",NULL);
    personagem [3][5] = load_bitmap("Imagens/Personagens/Principal/esquerda15.bmp",NULL);
    personagem [3][6] = load_bitmap("Imagens/Personagens/Principal/esquerda17.bmp",NULL);
    personagem [3][7] = load_bitmap("Imagens/Personagens/Principal/esquerda16.bmp",NULL);
    
    personagem_desmaiado = load_bitmap("Imagens/Personagens/Principal/personagem_desmaiado.bmp", NULL);
    
    // Carregando Objetos de Interface //
    borda_menu = load_bitmap("Imagens/ObjetosDeInterface/borda_menu_1.bmp",NULL);
    fundo_menu = load_jpg("Imagens/ObjetosDeInterface/fundo_menu_1.jpg",NULL);

    // Criação do Personagem Principal e Atribuições Iniciais às Coordenadas //
    struct informacaoSprite informacaoPersonagem;
    informacaoPersonagem.x                             =   0;
    informacaoPersonagem.y                             =   0;
    informacaoPersonagem.lado                          =   0;
    informacaoPersonagem.animacao                      =   0;
    informacaoPersonagem.terreno                       =   TERRENO_NORMAL;
    informacaoPersonagem.largura                       =   informacaoPersonagem.x + SPRITE_LARGURA;
    informacaoPersonagem.altura                        =   informacaoPersonagem.y + SPRITE_ALTURA;
    informacaoPersonagem.vigor                         =   6;
    informacaoPersonagem.energia                       =   3;
    informacaoPersonagem.face [0]                      =   load_bitmap ("Imagens/Personagens/Principal/Faces/face_joao_0.tga", NULL);
    informacaoPersonagem.face [1]                      =   load_bitmap ("Imagens/Personagens/Principal/Faces/face_joao_1.tga", NULL);
    informacaoPersonagem.ataque1 [0]                   =   load_bitmap ("Imagens/Personagens/Principal/Ataque1/bola_0.bmp", NULL);
    informacaoPersonagem.ataque1 [1]                   =   load_bitmap ("Imagens/Personagens/Principal/Ataque1/bola_1.bmp", NULL);
    informacaoPersonagem.ataque1 [2]                   =   load_bitmap ("Imagens/Personagens/Principal/Ataque1/bola_2.bmp", NULL);
    informacaoPersonagem.moedas                        =   10;
    informacaoPersonagem.nivel                         =   1;
    informacaoPersonagem.habilidade1                   =   0;
    informacaoPersonagem.experiencia_atual             =   0;
    informacaoPersonagem.experiencia_proximo_nivel     =   50 * informacaoPersonagem.nivel;
    informacaoPersonagem.experiencia_atual_porcentagem =   (informacaoPersonagem.experiencia_atual * 100) / informacaoPersonagem.experiencia_proximo_nivel;
    
    
    // Criação do Alexandre //
    struct informacaoSprite informacaoAlexandre;
    informacaoAlexandre.x                      = 0;
    informacaoAlexandre.y                      = 0;
    informacaoAlexandre.lado                   = 0;
    informacaoAlexandre.animacao               = 0;
    informacaoAlexandre.posicao_conversa       = 0;
    
    // Criação de Ligeirinho ou José //
    struct informacaoSprite informacaoLigeirinho;
    informacaoLigeirinho.x                      =   0;
    informacaoLigeirinho.y                      =   0;
    informacaoLigeirinho.lado                   =   0;
    informacaoLigeirinho.animacao               =   0;
    informacaoLigeirinho.delayanimacao          =   0;
    informacaoLigeirinho.posicao_conversa       =   0;
    informacaoLigeirinho.terreno                =   1;
    informacaoLigeirinho.largura                =   informacaoLigeirinho.x + SPRITE_NPC_LARGURA;
    informacaoLigeirinho.altura                 =   informacaoLigeirinho.y + SPRITE_NPC_ALTURA;
    informacaoLigeirinho.colisao_para_conversar =   0;
    informacaoLigeirinho.velocidade_animacao    =   3;
    informacaoLigeirinho.fala                   =   0;
    informacaoLigeirinho.posicao_conversa       =   0;
    
    // Criação do Inimigo do Jogo //
    struct informacaoSprite informacaoInimigo;
    informacaoInimigo.x                      =   0;
    informacaoInimigo.y                      =   0;
    informacaoInimigo.lado                   =   0;
    informacaoInimigo.animacao               =   0;
    informacaoInimigo.delayanimacao          =   0;
    informacaoInimigo.posicao_conversa       =   0;
    informacaoInimigo.terreno                =   TERRENO_ARENOSO;
    informacaoInimigo.largura                =   informacaoInimigo.x + SPRITE_NPC_LARGURA;
    informacaoInimigo.altura                 =   informacaoInimigo.y + SPRITE_NPC_ALTURA;
    informacaoInimigo.colisao_para_conversar =   0;
    informacaoInimigo.velocidade_animacao    =   2;
    informacaoInimigo.fala                   =   0;
    informacaoInimigo.posicao_conversa       =   0;
    
    // Criação do Desconhecido do Jogo //
    struct informacaoSprite informacaoDesconhecido;
    informacaoDesconhecido.x                      =   0;
    informacaoDesconhecido.y                      =   0;
    informacaoDesconhecido.lado                   =   0;
    informacaoDesconhecido.animacao               =   0;
    informacaoDesconhecido.delayanimacao          =   0;
    informacaoDesconhecido.posicao_conversa       =   0;
    informacaoDesconhecido.terreno                =   TERRENO_ARENOSO;
    informacaoDesconhecido.largura                =   informacaoDesconhecido.x + SPRITE_NPC_LARGURA;
    informacaoDesconhecido.altura                 =   informacaoDesconhecido.y + SPRITE_NPC_ALTURA;
    informacaoDesconhecido.colisao_para_conversar =   0;
    informacaoDesconhecido.velocidade_animacao    =   2;
    informacaoDesconhecido.fala                   =   0;
    informacaoDesconhecido.posicao_conversa       =   0;
    
    // Criação da Geovana //
    struct informacaoSprite informacaoGeovana;
    informacaoGeovana.x                      =   0;
    informacaoGeovana.y                      =   0;
    informacaoGeovana.lado                   =   0;
    informacaoGeovana.animacao               =   0;
    informacaoGeovana.terreno                =   TERRENO_ARENOSO;
    informacaoGeovana.fala                   =   0;
    informacaoGeovana.velocidade_animacao    =   2;
    informacaoGeovana.delayanimacao          =   0;
    informacaoGeovana.posicao_conversa       =   0;
    
    // Criação do Roberto //
    struct informacaoSprite informacaoRoberto;
    informacaoRoberto.x                      =   0;
    informacaoRoberto.y                      =   0;
    informacaoRoberto.lado                   =   0;
    informacaoRoberto.animacao               =   0;
    informacaoRoberto.terreno                =   TERRENO_ARENOSO;
    informacaoRoberto.fala                   =   0;
    informacaoRoberto.velocidade_animacao    =   2;
    informacaoRoberto.delayanimacao          =   0;
    informacaoRoberto.posicao_conversa       =   0;
    
    // Criação do Mariana //
    struct informacaoSprite informacaoMariana;
    informacaoMariana.x                      =   0;
    informacaoMariana.y                      =   0;
    informacaoMariana.lado                   =   0;
    informacaoMariana.animacao               =   0;
    informacaoMariana.delayanimacao          =   50;
    informacaoMariana.terreno                =   TERRENO_ARENOSO;
    informacaoMariana.largura                =   informacaoMariana.x + SPRITE_NPC_LARGURA;
    informacaoMariana.altura                 =   informacaoMariana.y + SPRITE_NPC_ALTURA;
    informacaoMariana.colisao_para_conversar =   0;
    informacaoMariana.velocidade_animacao    =   2;
    informacaoMariana.fala                   =   0;
    informacaoMariana.posicao_conversa       =   0;
    
    // Criação do NPC1 //
    struct informacaoSprite informacaoNpc1;
    informacaoNpc1.x                      =   0;
    informacaoNpc1.y                      =   0;
    informacaoNpc1.lado                   =   0;
    informacaoNpc1.animacao               =   0;
    informacaoNpc1.delayanimacao          =   50;
    informacaoNpc1.terreno                =   TERRENO_ARENOSO;
    informacaoNpc1.largura                =   informacaoNpc1.x + SPRITE_NPC_LARGURA;
    informacaoNpc1.altura                 =   informacaoNpc1.y + SPRITE_NPC_ALTURA;
    informacaoNpc1.colisao_para_conversar =   0;
    informacaoNpc1.velocidade_animacao    =   2;
    informacaoNpc1.fala                   =   0;
    informacaoNpc1.posicao_conversa       =   0;
	
    // Criação do NPC2 //
    struct informacaoSprite informacaoNpc2;
    informacaoNpc2.x                      =   0;
    informacaoNpc2.y                      =   0;
    informacaoNpc2.lado                   =   0;
    informacaoNpc2.animacao               =   0;
    informacaoNpc2.delayanimacao          =   0;
    informacaoNpc2.terreno                =   TERRENO_ARENOSO;
    informacaoNpc2.largura                =   informacaoNpc1.x + SPRITE_NPC_LARGURA;
    informacaoNpc2.altura                 =   informacaoNpc1.y + SPRITE_NPC_ALTURA;
    informacaoNpc2.colisao_para_conversar =   0;
    informacaoNpc2.velocidade_animacao    =   2;
    informacaoNpc2.fala                   =   0;
    informacaoNpc2.posicao_conversa       =   0;
    
    // Criação do NPC3 //
    struct informacaoSprite informacaoNpc3;
    informacaoNpc3.x                      =   0;
    informacaoNpc3.y                      =   0;
    informacaoNpc3.lado                   =   0;
    informacaoNpc3.animacao               =   0;
    informacaoNpc3.delayanimacao          =   50;
    informacaoNpc3.terreno                =   TERRENO_ARENOSO;
    informacaoNpc3.largura                =   informacaoNpc1.x + SPRITE_NPC_LARGURA;
    informacaoNpc3.altura                 =   informacaoNpc1.y + SPRITE_NPC_ALTURA;
    informacaoNpc3.colisao_para_conversar =   0;
    informacaoNpc3.velocidade_animacao    =   2;
    informacaoNpc3.fala                   =   0;
    informacaoNpc3.posicao_conversa       =   0;
    
    // Criação do Cachorro//
    struct informacaoSprite informacaoCachorro;
    informacaoCachorro.x                      =   0;
    informacaoCachorro.y                      =   0;
    informacaoCachorro.lado                   =   0;
    informacaoCachorro.animacao               =   0;
    informacaoCachorro.delayanimacao          =   20;
    informacaoCachorro.terreno                =   TERRENO_ARENOSO;
    informacaoCachorro.largura                =   informacaoNpc1.x + SPRITE_NPC_LARGURA;
    informacaoCachorro.altura                 =   informacaoNpc1.y + SPRITE_NPC_ALTURA;
    informacaoCachorro.colisao_para_conversar =   0;
    informacaoCachorro.velocidade_animacao    =   2;
    informacaoCachorro.fala                   =   0;
    informacaoCachorro.posicao_conversa       =   0;

	// Criação Vespa 1 //
    struct informacaoSprite informacaoVespa1;
    informacaoVespa1.x                       =   0;
    informacaoVespa1.y                       =   0;
    informacaoVespa1.lado                    =   0;
    informacaoVespa1.animacao                =   0;
    informacaoVespa1.delayanimacao           =   0;
    informacaoVespa1.terreno                 =   TERRENO_AEREO;
    informacaoVespa1.largura                 =   informacaoVespa1.x + SPRITE_NPC_LARGURA;
    informacaoVespa1.altura                  =   informacaoVespa1.y + SPRITE_NPC_ALTURA;
    informacaoVespa1.vigor                   =   1;
    informacaoVespa1.velocidade_animacao     =   0;
    informacaoVespa1.loot                    =   1;
    informacaoVespa1.moedas                  =   5;
    informacaoVespa1.experiencia_atual       =   25;
    informacaoVespa1.obter_experiencia       =   0;
    
    // Criação Vespa 2 //
    struct informacaoSprite informacaoVespa2;
    informacaoVespa2.x                       =   0;
    informacaoVespa2.y                       =   0;
    informacaoVespa2.lado                    =   0;
    informacaoVespa2.animacao                =   0;
    informacaoVespa2.delayanimacao           =   0;
    informacaoVespa2.terreno                 =   TERRENO_AEREO;
    informacaoVespa2.largura                 =   informacaoVespa2.x + SPRITE_NPC_LARGURA;
    informacaoVespa2.altura                  =   informacaoVespa2.y + SPRITE_NPC_ALTURA;
    informacaoVespa2.vigor                   =   1;
    informacaoVespa2.velocidade_animacao     =   0;
    informacaoVespa2.loot                    =   1;
    informacaoVespa2.moedas                  =   5;
    informacaoVespa2.experiencia_atual       =   25;
    informacaoVespa2.obter_experiencia       =   0;
    
    // Criação Bola para Atacar //
    struct informacaoSprite informacaoBola;
    informacaoBola.x             =   0;
    informacaoBola.y             =   0;
    informacaoBola.lado          =   0;
    informacaoBola.animacao      =   0;
    informacaoBola.delayanimacao =   0;
    informacaoBola.terreno       =   TERRENO_NORMAL;
    informacaoBola.largura       =   informacaoBola.x + SPRITE_LARGURA;
    informacaoBola.altura        =   informacaoBola.y + SPRITE_ALTURA;
    
    // Criação da Moeda //
    struct informacaoSprite informacaoMoeda;
    informacaoMoeda.x             =   0;
    informacaoMoeda.y             =   0;
    informacaoMoeda.largura       =   informacaoMoeda.x + SPRITE_NPC_LARGURA;
    informacaoMoeda.altura        =   informacaoMoeda.y + SPRITE_NPC_ALTURA;
    informacaoMoeda.animacao      =   0;
    informacaoMoeda.delayanimacao =   0;
       
    // Criação de Baú 1 //
    struct interacaoObjeto interacaoBau1;
    interacaoBau1.x                     = 0;
    interacaoBau1.y                     = 0;
    interacaoBau1.estado                = 0;
    interacaoBau1.animacao              = 0;
    interacaoBau1.animacao_delay        = 0;
    interacaoBau1.animacao_brilho       = 0;
    interacaoBau1.animacao_brilho_delay = 0;
    interacaoBau1.recompensaHabilidade  = 1;
    interacaoBau1.recompensaVigor       = 0;
    
    
    // Criação de Cartas //
    TCartas VetCartas;
    informacaoJogoCarta informacaoJogoCarta1;
    
    VetCartas[0][0].id=1;
    VetCartas[0][1].id=5;
    VetCartas[0][2].id=3;
    VetCartas[0][3].id=2;
    VetCartas[1][0].id=4;
    VetCartas[1][1].id=4;
    VetCartas[1][2].id=1;
    VetCartas[1][3].id=5;
    VetCartas[2][0].id=2;
    VetCartas[2][1].id=6;
    VetCartas[2][2].id=8;
    VetCartas[2][3].id=7;
    VetCartas[3][0].id=3;
    VetCartas[3][1].id=7;
    VetCartas[3][2].id=8;
    VetCartas[3][3].id=6;
    
    for (cont_destruir_x = 0; cont_destruir_x <4; cont_destruir_x ++) {
        for (cont_destruir_y = 0; cont_destruir_y < 4; cont_destruir_y ++) {
            VetCartas [cont_destruir_x] [cont_destruir_y].estado = 0;
        }
    }
    
    // Informações sobre o jogo de carta //
    informacaoJogoCarta1.ComparaId[0] = 0;
    informacaoJogoCarta1.ComparaId[1] = 0;
    informacaoJogoCarta1.x            = 0;
    informacaoJogoCarta1.y            = 0;
    informacaoJogoCarta1.C1           = 0;
    informacaoJogoCarta1.C2           = 0;
    informacaoJogoCarta1.L1           = 0;
    informacaoJogoCarta1.L2           = 0;
    informacaoJogoCarta1.estadoClique = 0;
    informacaoJogoCarta1.Ponto        = 0;
    informacaoJogoCarta1.colisao      = 0;
    informacaoJogoCarta1.contClique   = 0;
    informacaoJogoCarta1.testa_fim    = 0;
    
    // Criação do ponto e nome do jogador atual //
    Treg_ranking PontoNomeJogador;
    PontoNomeJogador.ponto = 0;
    strcpy (PontoNomeJogador.nome,"");
    
    char nome [15];
    char pontos [10]; 
    
    //Estrutura de Repetição do Jogo //
    while (opcao != -1) {
        
        // Instalação do timer de fps do jogo (restringindo a velocidade do jogo ao FPS indicado //        
        LOCK_VARIABLE(fps_jogo);
        LOCK_FUNCTION(Estabilizador_FPS);
        install_int_ex(Estabilizador_FPS, MSEC_TO_TIMER(1000/FPS));
        
        if (fps_jogo >= velocidade_fps) {
            velocidade_fps = fps_jogo + 1;
            
        // Agora o loop depende da condição de velocidade que estabeleci anteriormente //    
//  =============================================================================================  Tela Inicial  ====================================================================================== //
            if (mapa_atual == 0) {                  
                if (entrar == 1) {          
                    if (musica == 0) {
                        efeito_nuvens_parallax (buffer, &animacao_parallax_quem_somos);
                        titulo_jogo (buffer,5,10);
                        efeito_pressione_enter (buffer, 225, 350, &animacao_pressione_enter, &animacao_pressione_enter_delay);
                        play_midi(audio_fundo, 1);                 // Toca Música Tela Inicial //  
                        musica = 1;
                        fadein (buffer, 3);                        //Lembrando que o cenário ja deve estár desenhado no buffer, ou seja, deve estár preparado para ser desenhado na screen, quanto menor o valor, mais devagar
                    } 
                    
                    efeito_nuvens_parallax (buffer, &animacao_parallax_quem_somos);
                    titulo_jogo (buffer,5,10);
                    efeito_pressione_enter (buffer, 225, 350, &animacao_pressione_enter, &animacao_pressione_enter_delay);
                    
                    if (key[KEY_ENTER]) { 
                        entrar = 0;  
                        entrar_2 = 1;
                        play_sample (audio_efeito [1], 500, 128, 1000, 0);
                    }
                }
               
                if (entrar_2 == 1) {             // Efeito Abrir Janela Opcao
                    efeito_nuvens_parallax (buffer, &animacao_parallax_quem_somos);
                    titulo_jogo (buffer,5,10);   
                    if (animacao_menu_abrindo < 15) {
                        menu_inicial_abrindo (buffer, 276, 310, &animacao_menu_abrindo, &animacao_menu_abrindo_audio); 
                    } else {
                        entrar_2 = 0;
                        entrar_3 = 1;
                    }      
                }    
        
        
                if (entrar_3 == 1) {
                    efeito_nuvens_parallax (buffer, &animacao_parallax_quem_somos);
                    titulo_jogo (buffer,5,10);    
                    menu_inicial_abrindo (buffer, 276, 310, &animacao_menu_abrindo, &animacao_menu_abrindo_audio);
                    opcao = efeito_bola_opcao_menu_principal (buffer, opcao, &animacao_bola, &animacao_bola_delay);      
                    if (key[KEY_ENTER]) {
                        entrar_3 = 0;
                        entrar_4 = 1;
                        play_sample (audio_efeito [1], 500, 128, 1000, 0);
                        animacao_pressione_enter = 18;
                    }    
                }
                
                if (entrar_4 == 1) {           // Efeito Fechar Janela Opcao
                    if (animacao_menu_abrindo > -1) {
                        efeito_nuvens_parallax (buffer, &animacao_parallax_quem_somos);
                        titulo_jogo (buffer,5,10);
                        if (animacao_menu_abrindo > 0) {    
                            menu_inicial_fechando (buffer, 276, 310, &animacao_menu_abrindo, &animacao_menu_abrindo_audio);
                        } else {
                            animacao_menu_abrindo = animacao_menu_abrindo - 1;
                        }
                    } else {    
                        entrar_4 = 2;
                    }
                }
                
                // Novo Jogo//
                if ((entrar_4 == 2) && (opcao == 0)) {
                    mapa_atual = -1;
                    musica = -1;
                    opcao = 0;
                }
                
                // Opcao Continuar //
                if ((entrar_4 == 2) && (opcao == 1)) {
                    mapa_atual = -1;
                    musica = -1;
                    opcao = 0;   
                }
                
                
                // Opcao Quem Somos //
                if ((entrar_4 == 2) && (opcao == 2)) {
                    if (efeito == 0) {
                        fadeout(5);
                        efeito = 1;
                        efeito_nuvens_parallax (buffer, &animacao_parallax_quem_somos);
                        quem_somos (buffer);
                        animacao_tecla_esc (buffer, 670, 500, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay); 
                        fadein(buffer, 5);
                    }
                    efeito_nuvens_parallax (buffer, &animacao_parallax_quem_somos);
                    quem_somos (buffer);
                    animacao_tecla_esc (buffer, 670, 500, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay); 
                    if (key[KEY_ESC]) {
                        efeito = 0;
                        entrar_4 = 0;
                        entrar_2 = 1;
                        play_sample (audio_efeito [2], 500, 128, 1000, 0);
                        fadeout(5);
                        clear (buffer);
                        efeito_nuvens_parallax (buffer, &animacao_parallax_quem_somos);
                        titulo_jogo (buffer,5,10);
                        fadein(buffer, 5);
                        animacao_menu_abrindo = 0;
                    }
                }          
                
                // Opcao Ranking //
                if ((entrar_4 == 2) && (opcao == 3)) {
                     if (efeito == 0) {
                        fadeout(5);
                        efeito = 1;
                        ranking_nomes (buffer);
                        efeito_faixa_ranking_parallax (buffer, &animacao_tutorial_parallax);
                        animacao_tecla_esc (buffer, 720, 552, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay); 
                        fadein(buffer, 5);
                    }
                    ranking_nomes (buffer);
                    efeito_faixa_ranking_parallax (buffer, &animacao_tutorial_parallax);
                    animacao_tecla_esc (buffer, 720, 552, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);
                    mostrar_pontuacao_ranking (buffer, datFontes); 
                    if (key[KEY_ESC]) {
                        efeito = 0;
                        entrar_4 = 0;
                        entrar_2 = 1;
                        play_sample (audio_efeito [2], 500, 128, 1000, 0);
                        fadeout(5);
                        clear (buffer);
                        efeito_nuvens_parallax (buffer, &animacao_parallax_quem_somos);
                        titulo_jogo (buffer,5,10);
                        fadein(buffer, 5);
                        animacao_menu_abrindo = 0;
                    }
                }
                draw_sprite(screen, buffer, 0,  0);                  
            }
//  ================================================================================================================================================================================================//           
//  =============================================================================================  Mapa Vila  ====================================================================================== //        
            if (mapa_atual == -1) {
                if (introducao_posicao == 0) {
                    if (musica == -1) {
                        fadeout (3);
                        clear (buffer);
                        stop_midi ();
                        rest (3000);
                        audio_fundo = load_midi("Audios/Fundo/musica_introducao.mid");
                        play_midi(audio_fundo, 1);
                        cenario = load_jpg("Imagens/Introducao/intro_0.jpg",NULL);
                        draw_sprite(buffer, cenario, 0,  0);
                        animacao_tecla_enter (buffer, 50, 30, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                        animacao_tecla_esc   (buffer, 700, 50, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);  
                        fadein (buffer, 1);
                        musica = 2;
                    }
                    draw_sprite(buffer, cenario, 0,  0);
                    animacao_tecla_enter (buffer, 50, 30, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                    animacao_tecla_esc   (buffer, 700, 50, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);
                    if (key[KEY_ENTER]) {
                        introducao_posicao = 1;
                        fadeout (3);
                        clear (buffer);
                        cenario = load_jpg("Imagens/Introducao/intro_1.jpg",NULL);
                        draw_sprite(buffer, cenario, 0,  0);
                        animacao_tecla_enter (buffer, 50, 30, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                        animacao_tecla_esc   (buffer, 700, 50, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);  
                        fadein (buffer, 3);
                    }
                }
                if (introducao_posicao == 1) {
                    draw_sprite(buffer, cenario, 0,  0);
                    animacao_tecla_enter (buffer, 50, 30, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                    animacao_tecla_esc   (buffer, 700, 50, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);  
                    if (key[KEY_ENTER]) {
                        introducao_posicao = 2;
                        fadeout (3);
                        clear (buffer);
                        cenario = load_jpg("Imagens/Introducao/intro_2.jpg",NULL);
                        draw_sprite(buffer, cenario, 0,  0);
                        animacao_tecla_enter (buffer, 50, 30, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                        animacao_tecla_esc   (buffer, 700, 50, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);  
                        fadein (buffer, 3);
                    }    
                }
                if (introducao_posicao == 2) {
                    draw_sprite(buffer, cenario, 0,  0);
                    animacao_tecla_enter (buffer, 50, 30, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                    animacao_tecla_esc   (buffer, 700, 50, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);    
                    if (key[KEY_ENTER]) {
                        introducao_posicao = 3;
                        fadeout (3);
                        clear (buffer);
                        cenario = load_jpg("Imagens/Introducao/intro_3.jpg",NULL);
                        draw_sprite(buffer, cenario, 0,  0);
                        animacao_tecla_enter (buffer, 50, 30, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                        animacao_tecla_esc   (buffer, 700, 50, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);  
                        fadein (buffer, 3);
                    }  
                }
                if (introducao_posicao == 3) {
                    draw_sprite(buffer, cenario, 0,  0);
                    animacao_tecla_enter (buffer, 50, 30, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                    animacao_tecla_esc   (buffer, 700, 50, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);    
                    if (key[KEY_ENTER]) {
                        introducao_posicao = 4;
                        fadeout (3);
                        clear (buffer);
                        cenario = load_jpg("Imagens/Introducao/intro_4.jpg",NULL);
                        draw_sprite(buffer, cenario, 0,  0);
                        animacao_tecla_enter (buffer, 50, 30, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                        animacao_tecla_esc   (buffer, 700, 50, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);  
                        fadein (buffer, 3);
                    }  
                }
                if (introducao_posicao == 4) {
                    draw_sprite(buffer, cenario, 0,  0);
                    animacao_tecla_enter (buffer, 50, 30, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                    animacao_tecla_esc   (buffer, 700, 50, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);  
                    if (key[KEY_ENTER]) {
                        introducao_posicao = 5;
                        fadeout (3);
                        clear (buffer);
                        cenario = load_jpg("Imagens/Introducao/intro_5.jpg",NULL);
                        draw_sprite(buffer, cenario, 0,  0);
                        animacao_tecla_enter (buffer, 50, 30, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                        animacao_tecla_esc   (buffer, 700, 50, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);  
                        fadein (buffer, 3);
                    }    
                }
                if (introducao_posicao == 5) {
                    draw_sprite(buffer, cenario, 0,  0);
                    animacao_tecla_enter (buffer, 50, 30, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                    animacao_tecla_esc   (buffer, 700, 50, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);  
                    if (key[KEY_ENTER]) {
                        introducao_posicao = 6;
                        fadeout (3);
                        clear (buffer);
                        cenario = load_jpg("Imagens/Introducao/intro_6.jpg",NULL);
                        draw_sprite(buffer, cenario, 0,  0);
                        animacao_tecla_enter (buffer, 50, 30, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                        animacao_tecla_esc   (buffer, 700, 50, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);  
                        fadein (buffer, 3);
                    }    
                }
                if (introducao_posicao == 6) {
                    draw_sprite(buffer, cenario, 0,  0);
                    animacao_tecla_enter (buffer, 50, 30, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                    animacao_tecla_esc   (buffer, 700, 50, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);  
                    if (key[KEY_ENTER]) {
                        introducao_posicao = 7;
                        fadeout (3);
                        clear (buffer);
                        cenario = load_jpg("Imagens/Introducao/intro_7.jpg",NULL);
                        draw_sprite(buffer, cenario, 0,  0);
                        animacao_tecla_enter (buffer, 50, 30, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                        animacao_tecla_esc   (buffer, 700, 50, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);  
                        fadein (buffer, 3);
                    }    
                }
                if (introducao_posicao == 7) {
                    draw_sprite(buffer, cenario, 0,  0);
                    animacao_tecla_enter (buffer, 50, 30, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                    animacao_tecla_esc   (buffer, 700, 50, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);  
                    if (key[KEY_ENTER]) {
                        introducao_posicao = 8;
                        fadeout (3);
                        clear (buffer);
                        cenario = load_jpg("Imagens/Introducao/intro_8.jpg",NULL);
                        draw_sprite(buffer, cenario, 0,  0);
                        animacao_tecla_enter (buffer, 50, 30, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                        animacao_tecla_esc   (buffer, 700, 50, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);  
                        fadein (buffer, 3);
                    }    
                }
                if (introducao_posicao == 8) {
                    draw_sprite(buffer, cenario, 0,  0);
                    animacao_tecla_enter (buffer, 50, 30, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                    animacao_tecla_esc   (buffer, 700, 50, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);  
                    if (key[KEY_ENTER]) {
                        introducao_posicao = 9;
                        fadeout (3);
                        clear (buffer);
                        cenario = load_jpg("Imagens/Introducao/intro_9.jpg",NULL);
                        draw_sprite(buffer, cenario, 0,  0);
                        animacao_tecla_enter (buffer, 50, 30, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                        animacao_tecla_esc   (buffer, 700, 50, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);  
                        fadein (buffer, 3);
                    }    
                }
                if (introducao_posicao == 9) {
                    draw_sprite(buffer, cenario, 0,  0);
                    animacao_tecla_enter (buffer, 50, 30, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                    animacao_tecla_esc   (buffer, 700, 50, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);  
                    if (key[KEY_ENTER]) {
                        introducao_posicao = 10;
                        fadeout (3);
                        clear (buffer);
                        cenario = load_jpg("Imagens/Introducao/intro_10.jpg",NULL);
                        draw_sprite(buffer, cenario, 0,  0);
                        animacao_tecla_enter (buffer, 50, 30, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                        animacao_tecla_esc   (buffer, 700, 50, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);  
                        fadein (buffer, 3);
                    }    
                }
                if (introducao_posicao == 10) {
                    draw_sprite(buffer, cenario, 0,  0);
                    animacao_tecla_enter (buffer, 50, 30, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                    animacao_tecla_esc   (buffer, 700, 50, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);  
                    if (key[KEY_ENTER]) {
                        introducao_posicao = 11;
                        fadeout (3);
                        clear (buffer);
                        cenario = load_jpg("Imagens/Introducao/intro_11.jpg",NULL);
                        draw_sprite(buffer, cenario, 0,  0);
                        animacao_tecla_enter (buffer, 50, 30, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                        animacao_tecla_esc   (buffer, 700, 50, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);  
                        fadein (buffer, 3);
                    }    
                }
                if (introducao_posicao == 11) {
                    draw_sprite(buffer, cenario, 0,  0);
                    animacao_tecla_enter (buffer, 50, 30, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                    animacao_tecla_esc   (buffer, 700, 50, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);  
                    if (key[KEY_ENTER]) {
                        introducao_posicao = 12;
                        fadeout (3);
                        clear (buffer);
                        cenario = load_jpg("Imagens/Introducao/intro_12.jpg",NULL);
                        draw_sprite(buffer, cenario, 0,  0);
                        animacao_tecla_enter (buffer, 50, 30, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                        animacao_tecla_esc   (buffer, 700, 50, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);  
                        fadein (buffer, 3);
                    }    
                }
                if (introducao_posicao == 12) {
                    draw_sprite(buffer, cenario, 0,  0);
                    animacao_tecla_enter (buffer, 50, 30, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                    animacao_tecla_esc   (buffer, 700, 50, &animacao_tecla_esc_pulsando, &animacao_tecla_esc_pulsando_delay);  
                    if (key[KEY_ENTER]) {
                        cenario = load_jpg("Imagens/Introducao/intro_13.jpg",NULL);
                        cenario_efeito = load_jpg("Imagens/Introducao/intro_14.jpg",NULL);
                        for (cont = 255; cont > 0; cont = (cont - 1)) {
                            set_trans_blender(0,0,0,cont);
                            draw_sprite(buffer, cenario_efeito, 0, 0); 
                            draw_trans_sprite(buffer, cenario, 0, 0);
                            draw_sprite(screen, buffer , 0, 0);
                            clear (buffer);
                            introducao_posicao = introducao_posicao + 1;
                        }
                        if (introducao_posicao > 20) {
                            introducao_posicao = 0;
                            rest (2000);
                            fadeout (1);
                            mapa_atual = 2; 
                            audio_fundo = load_midi("Audios/Fundo/musica_vila.mid");            // Load na musica do mapa 1.
                            play_midi(audio_fundo, 1);  
                        }
                    }    
                }
                if (key[KEY_ESC]) {
                    mapa_atual = 2;
                    stop_midi();
                    audio_fundo = load_midi("Audios/Fundo/musica_vila.mid");            // Load na musica do mapa 1.
                    play_midi(audio_fundo, 1);  
                }
                draw_sprite(screen, buffer, 0,  0);
                clear (buffer); 
            }                                                                                        
//  ================================================================================================================================================================================================//           
//  =============================================================================================  Mapa Vila  ====================================================================================== //        
            if (mapa_atual == 1) {
                // Load dos Sprites que serão usados neste mapa //
                // Vespa //
                vespa [0][0] = load_bitmap("Imagens/Personagens/Vespa/frente61.bmp",NULL);
                vespa [0][1] = load_bitmap("Imagens/Personagens/Vespa/frente62.bmp",NULL);
                vespa [0][2] = load_bitmap("Imagens/Personagens/Vespa/frente63.bmp",NULL);
                vespa [0][3] = load_bitmap("Imagens/Personagens/Vespa/frente64.bmp",NULL);
    
                vespa [1][0] = load_bitmap("Imagens/Personagens/Vespa/direita61.bmp",NULL);
                vespa [1][1] = load_bitmap("Imagens/Personagens/Vespa/direita62.bmp",NULL);
                vespa [1][2] = load_bitmap("Imagens/Personagens/Vespa/direita63.bmp",NULL);
                vespa [1][3] = load_bitmap("Imagens/Personagens/Vespa/direita64.bmp",NULL);
        
                vespa [2][0] = load_bitmap("Imagens/Personagens/Vespa/costas61.bmp",NULL);
                vespa [2][1] = load_bitmap("Imagens/Personagens/Vespa/costas62.bmp",NULL);
                vespa [2][2] = load_bitmap("Imagens/Personagens/Vespa/costas63.bmp",NULL);
                vespa [2][3] = load_bitmap("Imagens/Personagens/Vespa/costas64.bmp",NULL);
    
                vespa [3][0] = load_bitmap("Imagens/Personagens/Vespa/esquerda61.bmp",NULL);
                vespa [3][1] = load_bitmap("Imagens/Personagens/Vespa/esquerda62.bmp",NULL);
                vespa [3][2] = load_bitmap("Imagens/Personagens/Vespa/esquerda63.bmp",NULL);
                vespa [3][3] = load_bitmap("Imagens/Personagens/Vespa/esquerda64.bmp",NULL);
                    
                    
                // Npc //
                npc1 [0][0] = load_bitmap("Imagens/Personagens/Npc1/frente21.bmp",NULL);
                npc1 [0][1] = load_bitmap("Imagens/Personagens/Npc1/frente22.bmp",NULL);
                npc1 [0][2] = load_bitmap("Imagens/Personagens/Npc1/frente23.bmp",NULL);
                npc1 [0][3] = load_bitmap("Imagens/Personagens/Npc1/frente24.bmp",NULL);
    
                npc1 [1][0] = load_bitmap("Imagens/Personagens/Npc1/direita21.bmp",NULL);
                npc1 [1][1] = load_bitmap("Imagens/Personagens/Npc1/direita22.bmp",NULL);
                npc1 [1][2] = load_bitmap("Imagens/Personagens/Npc1/direita23.bmp",NULL);
                npc1 [1][3] = load_bitmap("Imagens/Personagens/Npc1/direita24.bmp",NULL);
        
                npc1 [2][0] = load_bitmap("Imagens/Personagens/Npc1/costas21.bmp",NULL);
                npc1 [2][1] = load_bitmap("Imagens/Personagens/Npc1/costas22.bmp",NULL);
                npc1 [2][2] = load_bitmap("Imagens/Personagens/Npc1/costas23.bmp",NULL);
                npc1 [2][3] = load_bitmap("Imagens/Personagens/Npc1/costas24.bmp",NULL);
    
                npc1 [3][0] = load_bitmap("Imagens/Personagens/Npc1/esquerda21.bmp",NULL);
                npc1 [3][1] = load_bitmap("Imagens/Personagens/Npc1/esquerda22.bmp",NULL);
                npc1 [3][2] = load_bitmap("Imagens/Personagens/Npc1/esquerda23.bmp",NULL);
                npc1 [3][3] = load_bitmap("Imagens/Personagens/Npc1/esquerda24.bmp",NULL);
                            
                informacaoNpc1.face [0] =   load_bitmap ("Imagens/Personagens/Npc1/Faces/face_npc1_0.tga", NULL);
	            informacaoNpc1.face [1] =   load_bitmap ("Imagens/Personagens/Npc1/Faces/face_npc1_1.tga", NULL); 
                informacaoNpc1.face [2] =   load_bitmap ("Imagens/Personagens/Npc1/Faces/face_npc1_2.tga", NULL); 
                
                // Portas //
                porta [0] = load_bitmap("Imagens/EstilosCenarios/Objetos/Portas/porta_0.bmp",NULL);
                porta [1] = load_bitmap("Imagens/EstilosCenarios/Objetos/Portas/porta_2.bmp",NULL);
                
                portao_ginasio [0] = load_bitmap("Imagens/EstilosCenarios/Objetos/Portas/portao_0.jpg",NULL);
                portao_ginasio [1] = load_bitmap("Imagens/EstilosCenarios/Objetos/Portas/portao_2.jpg",NULL);
                
                if (progresso == 3) {
                    // Desconhecido //
                    desconhecido [0][0] = load_bitmap("Imagens/Personagens/Desconhecido/frente_0.tga",NULL);
                    desconhecido [0][1] = load_bitmap("Imagens/Personagens/Desconhecido/frente_1.tga",NULL);
                    desconhecido [0][2] = load_bitmap("Imagens/Personagens/Desconhecido/frente_2.tga",NULL);
                    desconhecido [0][3] = load_bitmap("Imagens/Personagens/Desconhecido/frente_3.tga",NULL);
    
                    desconhecido [1][0] = load_bitmap("Imagens/Personagens/Desconhecido/direita_0.tga",NULL);
                    desconhecido [1][1] = load_bitmap("Imagens/Personagens/Desconhecido/direita_1.tga",NULL);
                    desconhecido [1][2] = load_bitmap("Imagens/Personagens/Desconhecido/direita_2.tga",NULL);
                    desconhecido [1][3] = load_bitmap("Imagens/Personagens/Desconhecido/direita_3.tga",NULL);
        
                    desconhecido [2][0] = load_bitmap("Imagens/Personagens/Desconhecido/costas_0.tga",NULL);
                    desconhecido [2][1] = load_bitmap("Imagens/Personagens/Desconhecido/costas_1.tga",NULL);
                    desconhecido [2][2] = load_bitmap("Imagens/Personagens/Desconhecido/costas_2.tga",NULL);
                    desconhecido [2][3] = load_bitmap("Imagens/Personagens/Desconhecido/costas_3.tga",NULL);
    
                    desconhecido [3][0] = load_bitmap("Imagens/Personagens/Desconhecido/esquerda_0.tga",NULL);
                    desconhecido [3][1] = load_bitmap("Imagens/Personagens/Desconhecido/esquerda_1.tga",NULL);
                    desconhecido [3][2] = load_bitmap("Imagens/Personagens/Desconhecido/esquerda_2.tga",NULL);
                    desconhecido [3][3] = load_bitmap("Imagens/Personagens/Desconhecido/esquerda_3.tga",NULL);
                    
                    informacaoDesconhecido.face [0] = load_bitmap ("Imagens/Personagens/Desconhecido/Faces/face_desconhecido_0.tga", NULL); 
                }
                
                if (progresso_global == 1) {          
                    if (musica == 1) {
                        // Localização Inicial dos NPCs Mapa Vila
                        informacaoNpc1.x          =  575;
                        informacaoNpc1.y          =  237;
                        
                        informacaoDesconhecido.x  =  560;
                        informacaoDesconhecido.y  =  495;
                    
                        // Localização Inicial dos Inimigos Mapa Vila //
                        informacaoVespa1.x                 =  120;             
                        informacaoVespa1.y                 =  300;
                        informacaoVespa1.vigor             =  1;
                        informacaoVespa1.loot              =  1;
                        informacaoVespa1.obter_experiencia = 0;
                    
                        informacaoVespa2.x                 =  530;             
                        informacaoVespa2.y                 =  390;                   
                        informacaoVespa2.vigor             =  1;
                        informacaoVespa2.loot              =  1;
                        informacaoVespa2.obter_experiencia =  0;
                    
                        // Efeito de Fadeout e Limpa Tela, carregando a imagem referente ao mapa
                        fadeout (8);      
                        clear (buffer);
                        cenario = load_jpg("Imagens/EstilosCenarios/novo_cenario_principal.jpg",NULL);
                                                           
                        // Desenho das Primitivas do Jogo //
                        draw_sprite(buffer, cenario, 0,  0);
                        draw_sprite (buffer, porta [0], 160, 131);
                        draw_sprite (buffer, portao_ginasio [0], 543, 191); 
                    
                        teste_efeito_nuvem = efeito_nuvens (buffer, teste_efeito_nuvem, 0, altura_nuvem_1, 3, &animacao_1_sombra_nuvem , &animacao_1_sombra_nuvem_delay, &animacao_2_sombra_nuvem, &animacao_2_sombra_nuvem_delay, &animacao_3_sombra_nuvem, &animacao_3_sombra_nuvem_delay);  //2º Parametro - Imagem da Nuvem
                        teste_efeito_nuvem = efeito_nuvens (buffer, teste_efeito_nuvem, 0, altura_nuvem_2, 25, &animacao_1_sombra_nuvem , &animacao_1_sombra_nuvem_delay, &animacao_2_sombra_nuvem, &animacao_2_sombra_nuvem_delay, &animacao_3_sombra_nuvem, &animacao_3_sombra_nuvem_delay);  //3º Parametro - Velocidade (quanto menor o valor, maior a velocidade)
                
                        draw_sprite(buffer, npc1 [informacaoNpc1.lado][informacaoNpc1.animacao], informacaoNpc1.x, informacaoNpc1.y);
                        draw_sprite(buffer, personagem [informacaoPersonagem.lado][informacaoPersonagem.animacao], informacaoPersonagem.x, informacaoPersonagem.y);
                        if (informacaoVespa1.vigor > 0) {
                            draw_sprite (buffer, vespa [informacaoVespa1.lado][informacaoVespa1.animacao], informacaoVespa1.x, informacaoVespa1.y);
                        }
                    
                        if (informacaoVespa2.vigor > 0) {
                            draw_sprite (buffer, vespa [informacaoVespa2.lado][informacaoVespa2.animacao], informacaoVespa2.x, informacaoVespa2.y);
                        }
                        
                        if (progresso == 3) {
                            set_alpha_blender();
                            draw_trans_sprite(buffer, desconhecido [informacaoDesconhecido.lado][informacaoDesconhecido.animacao], informacaoDesconhecido.x, informacaoDesconhecido.y);
                        }
                        
                        efeito_sombra_ginasio (buffer, 419, 195); 
                        efeito_fogo (buffer, 513, 210, &animacao_fogo [0], &animacao_fogo_delay [0]);
                        efeito_fogo (buffer, 610, 210, &animacao_fogo [1], &animacao_fogo_delay [1]);
                        efeito_agua (buffer, 190, 440, &animacao_agua_1, &animacao_agua_1_delay, &animacao_agua_2, &animacao_agua_2_delay);
                        efeito_barra_de_status_personagem (buffer, informacaoPersonagem.vigor, informacaoPersonagem.energia, &animacao_status, &animacao_status_delay, informacaoPersonagem.moedas, datFontes, informacaoPersonagem.experiencia_atual_porcentagem, informacaoPersonagem.nivel);          
                        
                        // Desenhos as habilidades da barra de habilidades //
                        if (informacaoPersonagem.habilidade1 == 1) efeito_habilidade_1_ativa (buffer, 5 + 2, 120 + 2, &animacao_habilidade1, &animacao_habilidade1_delay);
                                        
                    
                        // Efeitos de Fadein utilizando as primitivas desenhadas no buffer anteriormente //
                        fadein (buffer, 8);                                                   // Fadeout do cenário anterior, quanto menor o valor mais rápido é
                        musica = 2;                                                           // Incrementa música para o próximo cenário e para não repetir mais esta estrutura.                                                                  // Lembrando que o cenário ja deve estár desenhado no buffer, ou seja, deve estár preparado para ser desenhado na screen, quanto menor o valor, mais devagar
                    } 
                    
                    // Atualiza Nivel do Personagem Caso Evolua //
                    if (informacaoPersonagem.experiencia_atual >= informacaoPersonagem.experiencia_proximo_nivel) {
                        if (informacaoPersonagem.nivel != 99) {
                            informacaoPersonagem.nivel                     = informacaoPersonagem.nivel + 1;
                            informacaoPersonagem.experiencia_atual         = informacaoPersonagem.experiencia_atual - informacaoPersonagem.experiencia_proximo_nivel; 
                            informacaoPersonagem.experiencia_proximo_nivel = informacaoPersonagem.experiencia_proximo_nivel * informacaoPersonagem.nivel;
                            informacaoPersonagem.vigor                     = 6;
                            animacao_subiu_nivel                           = 0;
                        }    
                    }
                    
                    // Atualiza Porcentagem de Experiência do Personagem //
                    informacaoPersonagem.experiencia_atual_porcentagem = (informacaoPersonagem.experiencia_atual * 100) / informacaoPersonagem.experiencia_proximo_nivel;

                    // Atualiza Largura e Altura do Personagem Principal //
                    informacaoPersonagem.largura = informacaoPersonagem.x + SPRITE_LARGURA;
                    informacaoPersonagem.altura  = informacaoPersonagem.y + SPRITE_ALTURA;
            
                    // Atualiza Largura e Altura do NPC //
                    informacaoNpc1.largura = informacaoNpc1.x + SPRITE_NPC_LARGURA;
                    informacaoNpc1.altura  = informacaoNpc1.y + SPRITE_NPC_ALTURA;
                    
                    // Atualiza Largura e Altura do Desconhecido //
                    informacaoDesconhecido.largura = informacaoDesconhecido.x + SPRITE_NPC_LARGURA;
                    informacaoDesconhecido.altura  = informacaoDesconhecido.y + SPRITE_NPC_ALTURA;
                
                    // Atualiza Largura e Altura dos Inimigos //
                    informacaoVespa1.largura = informacaoVespa1.x + SPRITE_NPC_LARGURA;
                    informacaoVespa1.altura  = informacaoVespa1.y + SPRITE_NPC_ALTURA;
                
                    informacaoVespa2.largura = informacaoVespa2.x + SPRITE_NPC_LARGURA;
                    informacaoVespa2.altura  = informacaoVespa2.y + SPRITE_NPC_ALTURA;
                
                    // Atualiza Informação sobre Ataque do Personagem //
                    informacaoBola.x = informacaoPersonagem.x + 10;
                    informacaoBola.y = informacaoPersonagem.y + 25;       
            
                    // Testes de Colisões Mapa Cidade//            
                    // Toda Parte Esquerda //
                    
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 15, 0, 25, 600, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                
                    // Toda Parte Baixa //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 65, 545, 800, 600, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    
                    // Com árvores Sáida da Direita //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 775, 325, 800, 410, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    
                    // Para Não Deixar Sair Pela Direita //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 800, 410, 800, 545, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                
                    // Parte Esquerda do Ginásio //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 325, 0, 505, 310, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                
                    // Parte Direita do Ginásio //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 650, 0, 800, 310, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                
                    // Restante do Ginásio
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 510, 0, 645, 220, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                
                    // Dois Pedestais com Fogo //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 510, 230, 535, 255, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 620, 230, 645, 255, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                
                    // Com Cerca e Plantas de Cima da Casa //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 30, 0, 150, 160, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 140, 0, 190, 130, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 200, 0, 220, 160, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                
                    // Restante das Plantas, Arvores e Madeiras da Direita //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 225, 0, 320, 30, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 295, 60, 320, 220, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 30, 230, 145, 215, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 240, 230, 290, 215, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                
                    // Chafariz e Mesas da Praça e Postes //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 145, 525, 435, 545, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 170, 420, 410, 560, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 82, 445, 85, 480, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 40, 465, 110, 467, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    
                    // Com NPC's //
                    informacaoNpc1.colisao_para_conversar = detectarColisaoSprite (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, (informacaoNpc1.x + 1) , (informacaoNpc1.y + 35), informacaoNpc1.largura + 5, informacaoNpc1.altura + 5, informacaoPersonagem.terreno, &informacaoNpc1.animacao);
                    caso_colisao        = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, (informacaoNpc1.x + 6) , (informacaoNpc1.y + 40), informacaoNpc1.largura, informacaoNpc1.altura, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    
                    // Com Desconhecido //
                    informacaoDesconhecido.colisao_para_conversar = detectarColisaoSprite (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, (informacaoDesconhecido.x + 1) , (informacaoDesconhecido.y + 35), informacaoDesconhecido.largura + 5, informacaoDesconhecido.altura + 5, informacaoPersonagem.terreno, &informacaoDesconhecido.animacao);
                    caso_colisao        = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, (informacaoDesconhecido.x + 6) , (informacaoDesconhecido.y + 40), informacaoDesconhecido.largura, informacaoDesconhecido.altura, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                
                    
                    // Com Inimigos //
                    if (informacaoVespa1.vigor > 0) {
                        caso_colisao_nociva = detectarColisaoNociva(&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, informacaoPersonagem.lado, (informacaoVespa1.x + 12), (informacaoVespa1.y + 5), (informacaoVespa1.largura - 10), (informacaoVespa1.altura - 10), informacaoPersonagem.terreno, &informacaoPersonagem.animacao, &informacaoPersonagem.vigor); 
                    }
                
                    if (informacaoVespa2.vigor > 0) {
                        caso_colisao_nociva = detectarColisaoNociva(&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, informacaoPersonagem.lado, (informacaoVespa2.x + 12), (informacaoVespa2.y + 5), (informacaoVespa2.largura - 10), (informacaoVespa2.altura - 10), informacaoPersonagem.terreno, &informacaoPersonagem.animacao, &informacaoPersonagem.vigor); 
                    }
                
                    // Para Mudar Cenário //
                    detectarColisaoEntrarSair(&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 140, 20, 190, 140, &mapa_atual, 2); //Ultimos dois parametros referem-se ao mapa atual e o mapa destino respectivamente.
                    if (((informacaoVespa1.vigor <= 0) && (informacaoVespa2.vigor <= 0) && (progresso != 3))) {
                        detectarColisaoEntrarSair(&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 525, 20, 585, 228, &mapa_atual, 4);
                    }
                    
                    // Desenhos em Variaveis //
                    // Desenha Cenário no Buffer //
                    draw_sprite(buffer, cenario, 0,  0);
                
                    // Abre Porta Casa//
                    if (mapa_atual == 2) {
                       clear (buffer);
                       draw_sprite(buffer, cenario, 0,  0);
                       draw_sprite (buffer, porta [1], 160, 131);
                       play_sample (audio_efeito [4], 500, 128, 1000, 0);
                       musica = 1;
                    } else {
                        draw_sprite (buffer, porta [0], 160, 131);
                    }
                    
                    // Abre Porta Ginásio //
                    if (mapa_atual == 4) {
                        clear (buffer);
                        draw_sprite(buffer, cenario, 0,  0);
                        draw_sprite (buffer, portao_ginasio [1], 543, 191);
                        draw_sprite (buffer, porta [0], 160, 131);
                        play_sample (audio_efeito [4], 500, 128, 1000, 0);
                        musica = 1;
                    } else {
                        draw_sprite (buffer, portao_ginasio [0], 543, 191);
                    }
                    
                    
                
                    // Desenha Inimigos  e Itens Animados //
                    if (informacaoVespa1.vigor > 0) {
                        draw_sprite(buffer, vespa [informacaoVespa1.lado][informacaoVespa1.animacao], informacaoVespa1.x, informacaoVespa1.y);
                    }
                
                    if (informacaoVespa2.vigor > 0) {
                        draw_sprite(buffer, vespa [informacaoVespa2.lado][informacaoVespa2.animacao], informacaoVespa2.x, informacaoVespa2.y);
                    }
                
                    // Ataque da Bola  desenhada Atras do Sprite //
                    if (informacaoPersonagem.habilidade1 == 1) { 
                        if (informacaoPersonagem.lado == 2) {
                            if (informacaoBola.delayanimacao <= 0) {
                                efeito_ataque (buffer, &informacaoBola.x, &informacaoBola.y, &informacaoBola.delayanimacao, &informacaoPersonagem.energia, informacaoPersonagem.lado, &informacaoPersonagem.animacao, informacaoPersonagem.ataque1, &animacao_efeito_ataque, &animacao_efeito_ataque_2);
                                informacaoPersonagem.energia = informacaoPersonagem.energia + 1;
                            } else if (informacaoBola.delayanimacao > 0) {
                            efeito_ataque (buffer, &informacaoBola.x, &informacaoBola.y, &informacaoBola.delayanimacao, &informacaoPersonagem.energia, informacaoPersonagem.lado, &informacaoPersonagem.animacao, informacaoPersonagem.ataque1, &animacao_efeito_ataque, &animacao_efeito_ataque_2);
                            }
                            if (informacaoPersonagem.energia  > 3) {
                                informacaoPersonagem.energia = 3;
                            }
                         }
                    }               
              
                   // Movimento Inimigos //
                   // Vespa 1 //
                   if (informacaoVespa1.vigor > 0) {
                         movimentarSpriteAutomaticamente(&informacaoVespa1.x, &informacaoVespa1.y, &informacaoVespa1.lado, &informacaoVespa1.animacao, &informacaoVespa1.delayanimacao, informacaoVespa1.terreno, 2, 120, 200, 0, &animacao_vespa_delay, informacaoVespa1.velocidade_animacao);
                   } else {
                       if (informacaoVespa1.obter_experiencia == 0) {
                            informacaoPersonagem.experiencia_atual = informacaoPersonagem.experiencia_atual + informacaoVespa1.experiencia_atual;
                            experiencia_total = experiencia_total + informacaoVespa1.experiencia_atual;
                            informacaoVespa1.obter_experiencia = 1;
                       }
                       if (informacaoVespa1.loot == 1) {
                            informacaoVespa1.loot = detectarColisaoMoeda(buffer, informacaoPersonagem.x, informacaoPersonagem.y, informacaoPersonagem.altura, informacaoPersonagem.largura, (informacaoVespa1.x + 12), (informacaoVespa1.y + 5), (informacaoVespa1.largura - 10), (informacaoVespa1.altura - 10), &informacaoPersonagem.moedas, informacaoVespa1.moedas);  
                            efeito_moeda(buffer, informacaoVespa1.x + 10, informacaoVespa1.y + 10, &animacao_moeda, &animacao_moeda_delay);
                        
                       }      
                   }
                
                   // Vespa 2 //
                   if (informacaoVespa2.vigor > 0) {
                       movimentarSpriteAutomaticamente(&informacaoVespa2.x, &informacaoVespa2.y, &informacaoVespa2.lado, &informacaoVespa2.animacao, &informacaoVespa2.delayanimacao, informacaoVespa2.terreno, 1, 390, 450, 0, &animacao_vespa_delay, informacaoVespa2.velocidade_animacao);
                   } else {
                       if (informacaoVespa2.obter_experiencia == 0) {
                           informacaoPersonagem.experiencia_atual = informacaoPersonagem.experiencia_atual + informacaoVespa2.experiencia_atual;
                           experiencia_total = experiencia_total + informacaoVespa1.experiencia_atual; 
                           informacaoVespa2.obter_experiencia = 1;
                       }
                       if (informacaoVespa2.loot == 1) {
                           informacaoVespa2.loot = detectarColisaoMoeda(buffer, informacaoPersonagem.x, informacaoPersonagem.y, informacaoPersonagem.altura, informacaoPersonagem.largura, (informacaoVespa2.x + 12), (informacaoVespa2.y + 5), (informacaoVespa2.largura - 10), (informacaoVespa2.altura - 10), &informacaoPersonagem.moedas, informacaoVespa2.moedas);  
                           efeito_moeda(buffer, informacaoVespa2.x + 10, informacaoVespa2.y + 10, &animacao_moeda, &animacao_moeda_delay);
                       }
                   }
                   
                   // Desenha personagem e NPC's testando se estão em cima ou embaixo um do outro // 
                    if (informacaoPersonagem.y >  informacaoNpc1.y){
                        draw_sprite(buffer, npc1 [informacaoNpc1.lado][informacaoNpc1.animacao], informacaoNpc1.x, informacaoNpc1.y);
                        draw_sprite(buffer, personagem [informacaoPersonagem.lado][informacaoPersonagem.animacao], informacaoPersonagem.x, informacaoPersonagem.y);
                    } else {
                        draw_sprite(buffer, personagem [informacaoPersonagem.lado][informacaoPersonagem.animacao], informacaoPersonagem.x, informacaoPersonagem.y);
                        draw_sprite(buffer, npc1 [informacaoNpc1.lado][informacaoNpc1.animacao], informacaoNpc1.x, informacaoNpc1.y);
                    }
                    
                    if (progresso == 3) {
                        set_alpha_blender();
                        draw_trans_sprite(buffer, desconhecido [informacaoDesconhecido.lado][informacaoDesconhecido.animacao], informacaoDesconhecido.x, informacaoDesconhecido.y);
                    }
                                                                                                                                                     
                    // Ataque da Bola  desenhada na Frente do Sprite //
                    if (informacaoPersonagem.habilidade1 == 1) {
                        if (informacaoPersonagem.lado != 2) {
                            if (informacaoBola.delayanimacao <= 0) {
                                efeito_ataque (buffer, &informacaoBola.x, &informacaoBola.y, &informacaoBola.delayanimacao, &informacaoPersonagem.energia, informacaoPersonagem.lado, &informacaoPersonagem.animacao, informacaoPersonagem.ataque1, &animacao_efeito_ataque, &animacao_efeito_ataque_2);
                                informacaoPersonagem.energia = informacaoPersonagem.energia + 1;
                            } else if (informacaoBola.delayanimacao > 0) {
                                efeito_ataque (buffer, &informacaoBola.x, &informacaoBola.y, &informacaoBola.delayanimacao, &informacaoPersonagem.energia, informacaoPersonagem.lado, &informacaoPersonagem.animacao, informacaoPersonagem.ataque1, &animacao_efeito_ataque, &animacao_efeito_ataque_2);
                            }
                            if (informacaoPersonagem.energia  > 3) {
                                informacaoPersonagem.energia = 3;
                            }
                        }
                    } 
                    informacaoBola.delayanimacao = informacaoBola.delayanimacao - 1;  
                    
                    // Atualiza Altura da Bola após Mudança das coordenadas X e Y //
                    informacaoBola.largura = informacaoBola.x + SPRITE_LARGURA;
                    informacaoBola.altura  = informacaoBola.y + SPRITE_ALTURA;
                
                
                    // Colisão dos Ataques com os monstros // 
                    if (informacaoVespa1.vigor > 0) {
                        detectarColisaoAtaquePersonagem(buffer, &informacaoBola.x, &informacaoBola.y, &informacaoBola.altura, &informacaoBola.largura, informacaoBola.lado, (informacaoVespa1.x + 30), (informacaoVespa1.y + 40), informacaoVespa1.largura - 10, informacaoVespa1.altura + 10, informacaoBola.terreno, &informacaoBola.animacao, &informacaoVespa1.vigor); 
                    }
                
                    if (informacaoVespa2.vigor > 0) {
                        detectarColisaoAtaquePersonagem(buffer, &informacaoBola.x, &informacaoBola.y, &informacaoBola.altura, &informacaoBola.largura, informacaoBola.lado, (informacaoVespa2.x + 30), (informacaoVespa2.y + 40), informacaoVespa2.largura - 10, informacaoVespa2.altura + 10, informacaoBola.terreno, &informacaoBola.animacao, &informacaoVespa2.vigor); 
                    }
                    
                    
                    // Testa Posição do Personagem Caso Mude de Cenário //
                    if (mapa_atual == 2){
                        informacaoPersonagem.x = 640;
                        informacaoPersonagem.y = 500;
                    }
 
                    if (mapa_atual == 4){
                        informacaoPersonagem.x = 380;
                        informacaoPersonagem.y = 520;
                    }
                    
                    // Desenha Animações //
                    efeito_agua (buffer, 190, 440, &animacao_agua_1, &animacao_agua_1_delay, &animacao_agua_2, &animacao_agua_2_delay);
                    efeito_sombra_ginasio (buffer, 419, 195); 
                    efeito_fogo (buffer, 513, 210, &animacao_fogo [0], &animacao_fogo_delay [0]);
                    efeito_fogo (buffer, 610, 210, &animacao_fogo [1], &animacao_fogo_delay [1]);
                    
                    
                    // Animacao Caso Suba de Nível //
                    if (animacao_subiu_nivel <= 20) {
                        efeito_subiu_nivel (buffer, informacaoPersonagem.x, informacaoPersonagem.y, &animacao_subiu_nivel, &animacao_subiu_nivel_delay); 
                    }
                    
                    // Desenha Nuvens (máximo duas nuvens por mapa) //
                    // Inicio do Efeito //         
                    srand(time(NULL));
                    if (entrar == 0) {
                        altura_nuvem_1 = (int)( 300.0 * rand() / ( RAND_MAX + 1.0 ) );
                        altura_nuvem_2 = 1 + (int)( 550.0 * rand() / ( RAND_MAX + 1.0 ) );
                        entrar = 1;
                    }
                    teste_efeito_nuvem = efeito_nuvens (buffer, teste_efeito_nuvem, 0, altura_nuvem_1, 3, &animacao_1_sombra_nuvem , &animacao_1_sombra_nuvem_delay, &animacao_2_sombra_nuvem, &animacao_2_sombra_nuvem_delay, &animacao_3_sombra_nuvem, &animacao_3_sombra_nuvem_delay);  //2º Parametro - Imagem da Nuvem
                    teste_efeito_nuvem = efeito_nuvens (buffer, teste_efeito_nuvem, 0, altura_nuvem_2, 25, &animacao_1_sombra_nuvem , &animacao_1_sombra_nuvem_delay, &animacao_2_sombra_nuvem, &animacao_2_sombra_nuvem_delay, &animacao_3_sombra_nuvem, &animacao_3_sombra_nuvem_delay);  //3º Parametro - Velocidade (quanto menor o valor, maior a velocidade)
                    if (teste_efeito_nuvem == 1) {                                                                                                                                                                                                                                          //4º Parametro - Altura da nuvem na tela                        
                        entrar = 0;                                                                                                                                                                                                                                                         //5º Tempo de espera para nuvem aparecer
                    }                                                                                        
                    // Fim do Efeito //
                    
                    // Desenha Barra de Status do Personagem// 
                    efeito_barra_de_status_personagem (buffer, informacaoPersonagem.vigor, informacaoPersonagem.energia, &animacao_status, &animacao_status_delay, informacaoPersonagem.moedas,  datFontes, informacaoPersonagem.experiencia_atual_porcentagem, informacaoPersonagem.nivel);
                    
                    // Desenhos as habilidades da barra de habilidades //
                    if (informacaoPersonagem.habilidade1 == 1) efeito_habilidade_1_ativa (buffer, 5 + 2, 120 + 2, &animacao_habilidade1, &animacao_habilidade1_delay);
                
                    // Movimento do Personagem // 
                    // Se não estiver em PAUSE, Ou sendo ATACADO, Ou ATACANDO // 
                    if (((informacaoBola.delayanimacao <= 0) &&  (opcao == 0)) && (informacaoNpc1.posicao_conversa == 0)) {
                         movimentarJogador (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.lado, &informacaoPersonagem.animacao, &informacaoPersonagem.terreno, &animacao_personagem_delay);
                    }
                
                    // Movimento do Npc e Interação  //
                    if (informacaoNpc1.colisao_para_conversar == 0) {
                        informacaoNpc1.posicao_conversa = 0;
                        movimentarSpriteAutomaticamente(&informacaoNpc1.x, &informacaoNpc1.y, &informacaoNpc1.lado, &informacaoNpc1.animacao, &informacaoNpc1.delayanimacao, informacaoNpc1.terreno, 1, 237, 300, 50, &animacao_npc_delay, informacaoNpc1.velocidade_animacao);    // Parametros Numéricos//                                                                                                                                                                                                           // 7º Parametro responsável pelo sentido "1" para Vertical ou "2" para Horizontal
                    } else {                                                                                                                                                                                                                                                        // 1º = Sentido (1 Para Vertical) (2 Para Horizontal)
                        informacaoNpc1.animacao = 0; 
                        if (progresso != 3) {                                                                                                                                                                                                                                                                    // 2º = coordenada da posical Inicial da locomoção (geralmente onde o sprite inicia na tela) *Lembre-se que é a coordenada X ou Y, especificada de acordo com o sentido.
                            if (informacaoNpc1.fala == 0) {                                                                                                                                                                                                                             // 3º = coordenada da posicao Final da locomoção. 
                                if ((informacaoNpc1.posicao_conversa == 0) && ((informacaoVespa1.vigor > 0) || (informacaoVespa2.vigor > 0)))  {                                                                                                                                                                                                                          // 4º = Tempo de Espera          
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoNpc1.lado, fala_personagem [1], buffer, informacaoNpc1.face [1],"",                                                                                                                            // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                           
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoNpc1.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoNpc1.fala);
                                } else if ((informacaoNpc1.posicao_conversa == 1) && ((informacaoVespa1.vigor > 0) || (informacaoVespa2.vigor > 0))) {
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoNpc1.lado, fala_personagem [1], buffer, informacaoNpc1.face [1],"João você não pode entrar no ginásio sem",
                                                                                                                                                  "antes me ajudar com aqueles zangões... é que", 
                                                                                                                                                  "eu tenho alergia á insetos, e uma picada me",
                                                                                                                                                  "deixaria de cama a semana toda, por favor", 
                                                                                                                                                  "espante eles para mim!", datFontes, 0, &informacaoNpc1.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 1, &informacaoNpc1.fala);    
                                    efeito_balao_exclamacao(buffer, informacaoNpc1.x, informacaoNpc1.y, &animacao_balao, &animacao_balao_delay); 
                                } else {
                                    informacaoNpc1.fala = 1;
                                    animacao_balao = 0;
                                }
                        
                            } else if (informacaoNpc1.fala == 1) {                                                                                                                                                                                                                         
                                if (informacaoNpc1.posicao_conversa == 0)   {                                                                                                                                                                                                                             
                                    animacao_balao = 0;
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoNpc1.lado, fala_personagem [1], buffer, informacaoNpc1.face [0],"",                                                                                                                                 
                                                                                                                                                  "",                                                                                                                                  
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoNpc1.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 1, &informacaoNpc1.fala);
                                } else if ((informacaoNpc1.posicao_conversa == 1) && ((informacaoVespa1.vigor > 0) || (informacaoVespa2.vigor > 0))) {
                                    efeito_balao_exclamacao(buffer, informacaoNpc1.x, informacaoNpc1.y, &animacao_balao, &animacao_balao_delay); 
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoNpc1.lado, fala_personagem [1], buffer, informacaoNpc1.face [1],"Por favor!!!",
                                                                                                                                                  "Eu não vou aguentar ter que ficar deitado", 
                                                                                                                                                  "uma semana inteira de novo...",
                                                                                                                                                  "Use uma bola de futebol pra espantar eles.", 
                                                                                                                                                  "Ficarei muito grato pela sua ajuda.", datFontes, 0, &informacaoNpc1.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 1, &informacaoNpc1.fala);    
                                } else if ((informacaoNpc1.posicao_conversa == 1) && ((informacaoVespa1.vigor <= 0) && (informacaoVespa2.vigor <= 0))) {
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoNpc1.lado, fala_personagem [1], buffer, informacaoNpc1.face [0],"Uffa sem aqueles zangões eu fico bem",
                                                                                                                                                  "mais tranquilo...", 
                                                                                                                                                  "Obrigado por ajudar, quando precisar de algo",
                                                                                                                                                  "estarei a disposição amigo. Agora vá para o", 
                                                                                                                                                  "treino, não quero te atrasar mais...", datFontes, 2, &informacaoNpc1.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 1, &informacaoNpc1.fala);    
                                } else if ((informacaoNpc1.posicao_conversa == 2) && (informacaoVespa1.vigor <= 0) && (informacaoVespa2.vigor <= 0)) {
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoNpc1.lado, fala_personagem [1], buffer, informacaoNpc1.face [2],"Manda um abraço para o treinador Roberto.",
                                                                                                                                                  "Ahhh, e o Alexandre está lá... Fiquei", 
                                                                                                                                                  "sabendo que vocês competem entre si desde",
                                                                                                                                                  "que se conheceram... então tome cuidado.", 
                                                                                                                                                  "Até mais. Boa sorte!", datFontes, 0, &informacaoNpc1.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 2, &informacaoNpc1.fala);    
                               
                                } 
                            } else if (informacaoNpc1.fala == 2) {                                                                                                                                                                                                                         
                                if (informacaoNpc1.posicao_conversa == 0)   {                                                                                                                                                                                                                             
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoNpc1.lado, fala_personagem [1], buffer, informacaoNpc1.face [0],"",                                                                                                                                 
                                                                                                                                                  "",                                                                                                                                  
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoNpc1.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 2, &informacaoNpc1.fala);
                                } else if ((informacaoNpc1.posicao_conversa == 1) && ((informacaoVespa1.vigor <= 0) && (informacaoVespa2.vigor <= 0))) {
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoNpc1.lado, fala_personagem [1], buffer, informacaoNpc1.face [2],"Boa sorte no treino João.",
                                                                                                                                                  "Manda um abraço para o treinador Roberto.", 
                                                                                                                                                  "Eu avisei você sobre o Alexandre porque",
                                                                                                                                                  "você sabe como é... pra ganhar ele é", 
                                                                                                                                                  "capaz de qualquer coisa. Então, tome cuidado.", datFontes, 0, &informacaoNpc1.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 2, &informacaoNpc1.fala);    
                                }
                            }
                        } else {                                                                                                                                                                                                                     // 3º = coordenada da posicao Final da locomoção. 
                            if (informacaoNpc1.posicao_conversa == 0)  {                                                                                                                                                                                                                          // 4º = Tempo de Espera          
                                interacaoNpc (informacaoPersonagem.lado, &informacaoNpc1.lado, fala_personagem [1], buffer, informacaoNpc1.face [1],"",                                                                                                                            // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                           
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoNpc1.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoNpc1.fala);
                            } else if (informacaoNpc1.posicao_conversa == 1)  {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoNpc1.lado, fala_personagem [1], buffer, informacaoNpc1.face [1],"Hoje não tem treino...",
                                                                                                                                                  "Ei João, você viu?", 
                                                                                                                                                  "Tem um cara ali embaixo...",
                                                                                                                                                  "Estranho... nunca vi ele por aqui antes.", 
                                                                                                                                                  "Deve ser algum viajante...", datFontes, 0, &informacaoNpc1.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 1, &informacaoNpc1.fala);    
                        
                            }   
                        } 
                    }
                    
                    // Movimento do Desconhecido e Interação  //
                    if (informacaoDesconhecido.colisao_para_conversar == 0) {
                        informacaoDesconhecido.posicao_conversa = 0;
                        movimentarSpriteAutomaticamente(&informacaoDesconhecido.x, &informacaoDesconhecido.y, &informacaoDesconhecido.lado, &informacaoDesconhecido.animacao, &informacaoDesconhecido.delayanimacao, informacaoDesconhecido.terreno, 2, 560, 700, 50, &animacao_npc_delay, informacaoNpc1.velocidade_animacao);    // Parametros Numéricos//                                                                                                                                                                                                           // 7º Parametro responsável pelo sentido "1" para Vertical ou "2" para Horizontal
                    } else {                                                                                                                                                                                                                                                        // 1º = Sentido (1 Para Vertical) (2 Para Horizontal)
                        informacaoDesconhecido.animacao = 0;                                                                                                                                                                                                                                                                     // 2º = coordenada da posical Inicial da locomoção (geralmente onde o sprite inicia na tela) *Lembre-se que é a coordenada X ou Y, especificada de acordo com o sentido.
                        if (informacaoDesconhecido.fala == 0) {                                                                                                                                                                                                                             // 3º = coordenada da posicao Final da locomoção. 
                            if (informacaoDesconhecido.posicao_conversa == 0)  {                                                                                                                                                                                                                          // 4º = Tempo de Espera          
                                interacaoNpc (informacaoPersonagem.lado, &informacaoDesconhecido.lado, fala_personagem [1], buffer, informacaoDesconhecido.face [1],"",                                                                                                                            // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                           
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoDesconhecido.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoDesconhecido.fala);
                            } else if (informacaoDesconhecido.posicao_conversa == 1) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoDesconhecido.lado, fala_personagem [1], buffer, informacaoDesconhecido.face [0],"Bom dia garotinho!!!",
                                                                                                                                                  "Você me parece preocupado, eu posso te", 
                                                                                                                                                  "ajudar com alguma coisa?",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 2, &informacaoDesconhecido.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoDesconhecido.fala);  
                            } else if (informacaoDesconhecido.posicao_conversa == 2) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoDesconhecido.lado, fala_personagem [1], buffer, informacaoPersonagem.face [1],"Bom dia senhor!",
                                                                                                                                                  "É... eu estou um pouco preocupado sim...", 
                                                                                                                                                  "",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 3, &informacaoDesconhecido.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoDesconhecido.fala);  
                            } else if (informacaoDesconhecido.posicao_conversa == 3) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoDesconhecido.lado, fala_personagem [1], buffer, informacaoDesconhecido.face [0],"E com que você esta preocupado?",
                                                                                                                                                  "", 
                                                                                                                                                  "",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 4, &informacaoDesconhecido.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoDesconhecido.fala);  
                            } else if (informacaoDesconhecido.posicao_conversa == 4) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoDesconhecido.lado, fala_personagem [1], buffer, informacaoPersonagem.face [1],"É com meu pai... Ele desapareceu",
                                                                                                                                                  "faz alguns anos...", 
                                                                                                                                                  "Mas até hoje ninguém sabe o que aconteceu",
                                                                                                                                                  "com ele...", 
                                                                                                                                                  "", datFontes, 5, &informacaoDesconhecido.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoDesconhecido.fala);  
                            } else if (informacaoDesconhecido.posicao_conversa == 5) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoDesconhecido.lado, fala_personagem [1], buffer, informacaoDesconhecido.face [0],"Hmm... Entendo... Você então",
                                                                                                                                                  "deve ser filho de Ligeirinho, não é?", 
                                                                                                                                                  "",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 7, &informacaoDesconhecido.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoDesconhecido.fala);  
                            } else if (informacaoDesconhecido.posicao_conversa == 6) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoDesconhecido.lado, fala_personagem [1], buffer, informacaoDesconhecido.face [0],"Hmm... Entendo... Você então",
                                                                                                                                                  "deve ser filho de Ligeirinho, não é?", 
                                                                                                                                                  "",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 7, &informacaoDesconhecido.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoDesconhecido.fala);  
                            } else if (informacaoDesconhecido.posicao_conversa == 7) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoDesconhecido.lado, fala_personagem [1], buffer, informacaoPersonagem.face [1],"Sim... Sou eu mesmo...",
                                                                                                                                                  "", 
                                                                                                                                                  "",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 8, &informacaoDesconhecido.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoDesconhecido.fala);  
                            } else if (informacaoDesconhecido.posicao_conversa == 8) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoDesconhecido.lado, fala_personagem [1], buffer, informacaoDesconhecido.face [0],"Hmm... talvez eu possa lhe ajudar...",
                                                                                                                                                  "", 
                                                                                                                                                  "",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 9, &informacaoDesconhecido.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoDesconhecido.fala);  
                            } else if (informacaoDesconhecido.posicao_conversa == 9) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoDesconhecido.lado, fala_personagem [1], buffer, informacaoPersonagem.face [0],"Sério!?",
                                                                                                                                                  "Mas como?", 
                                                                                                                                                  "",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 10, &informacaoDesconhecido.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoDesconhecido.fala);  
                            } else if (informacaoDesconhecido.posicao_conversa == 10) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoDesconhecido.lado, fala_personagem [1], buffer, informacaoDesconhecido.face [0],"Eu sou um viajante... E nós",
                                                                                                                                                  "viajantes escutamos muitas coisas por ae...", 
                                                                                                                                                  "Eu posso te dar algumas informações",
                                                                                                                                                  "sobre boatos que escutei...", 
                                                                                                                                                  "Talvez ajude você a encontra-lo...", datFontes, 11, &informacaoDesconhecido.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoDesconhecido.fala);  
                            } else if (informacaoDesconhecido.posicao_conversa == 11) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoDesconhecido.lado, fala_personagem [1], buffer, informacaoPersonagem.face [0],"Sim, com certeza!",
                                                                                                                                                  "", 
                                                                                                                                                  "",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 12, &informacaoDesconhecido.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoDesconhecido.fala);  
                            } else if (informacaoDesconhecido.posicao_conversa == 12) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoDesconhecido.lado, fala_personagem [1], buffer, informacaoDesconhecido.face [0],"Então... mas para isso, você",
                                                                                                                                                  "tem que me ajudar a te ajudar...entendeu?", 
                                                                                                                                                  "Pra rir tem que fazer rir pow!",
                                                                                                                                                  "Me entregue 130 moedas de ouro,", 
                                                                                                                                                  "dessa forma, eu te dou as informações!", datFontes, 13, &informacaoDesconhecido.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoDesconhecido.fala);  
                            } else if (informacaoDesconhecido.posicao_conversa == 13) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoDesconhecido.lado, fala_personagem [1], buffer, informacaoPersonagem.face [1],"130 moedas!!!!",
                                                                                                                                                  "É muita moeda... mas vou tentar", 
                                                                                                                                                  "conseguir essa quantia.",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 15, &informacaoDesconhecido.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoDesconhecido.fala);  
                            } else if (informacaoDesconhecido.posicao_conversa == 14) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoDesconhecido.lado, fala_personagem [1], buffer, informacaoPersonagem.face [1],"130 moedas!!!!",
                                                                                                                                                  "É muita moeda... mas vou tentar", 
                                                                                                                                                  "conseguir essa quantia.",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 15, &informacaoDesconhecido.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoDesconhecido.fala);  
                            } else if (informacaoDesconhecido.posicao_conversa == 15) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoDesconhecido.lado, fala_personagem [1], buffer, informacaoDesconhecido.face [0],"Sim... Quando você conseguir",
                                                                                                                                                  "juntar essa quantia, volte a falar comigo.", 
                                                                                                                                                  "Agora, com sua licensa...",
                                                                                                                                                  "", 
                                                                                                                                                "", datFontes, 16, &informacaoDesconhecido.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoDesconhecido.fala);  
                            } else if (informacaoDesconhecido.posicao_conversa == 16) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoDesconhecido.lado, fala_personagem [1], buffer, informacaoDesconhecido.face [0],"Sim... Quando você conseguir",
                                                                                                                                                  "juntar essa quantia, volte a falar comigo.", 
                                                                                                                                                  "Agora, com sua licensa...",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 17, &informacaoDesconhecido.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoDesconhecido.fala);  
                                informacaoDesconhecido.posicao_conversa = 0;
                                informacaoDesconhecido.fala = 1;   
                            }
                        } else if (informacaoDesconhecido.fala == 1) {
                            if (informacaoPersonagem.moedas >= 130) {
                                if (informacaoDesconhecido.posicao_conversa == 0)  {                                                                                                                                                                                                                          // 4º = Tempo de Espera          
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoDesconhecido.lado, fala_personagem [1], buffer, informacaoDesconhecido.face [0],"",                                                                                                                            // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                           
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoDesconhecido.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 1, &informacaoDesconhecido.fala);
                                } else if (informacaoDesconhecido.posicao_conversa == 1) {
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoDesconhecido.lado, fala_personagem [1], buffer, informacaoDesconhecido.face [0],"Nossa... Parece que você",
                                                                                                                                                  "já conseguiu o dinheiro mesmo heim...", 
                                                                                                                                                  "",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 2, &informacaoDesconhecido.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 1, &informacaoDesconhecido.fala);  
                                } else if (informacaoDesconhecido.posicao_conversa == 2) {
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoDesconhecido.lado, fala_personagem [1], buffer, informacaoPersonagem.face [1],"Sim!",
                                                                                                                                                  "Está certinho ae!", 
                                                                                                                                                  "",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 3, &informacaoDesconhecido.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 1, &informacaoDesconhecido.fala);  
                                } else if (informacaoDesconhecido.posicao_conversa == 3) {
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoDesconhecido.lado, fala_personagem [1], buffer, informacaoDesconhecido.face [0],"Hmmm... Então agora eu vou te contar tudo",
                                                                                                                                                  "que sei a respeito de seu pai...", 
                                                                                                                                                  "Os boatos são que ele está...",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 4, &informacaoDesconhecido.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 1, &informacaoDesconhecido.fala);  
                                } else if (informacaoDesconhecido.posicao_conversa == 4) {
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoDesconhecido.lado, fala_personagem [1], buffer, informacaoDesconhecido.face [0],"Hmmm... Então agora eu vou te contar tudo",
                                                                                                                                                  "que sei a respeito de seu pai...", 
                                                                                                                                                  "Os boatos são que ele está...",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 5, &informacaoDesconhecido.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 1, &informacaoDesconhecido.fala);  
                                    mapa_atual = 13;
                                    musica = 1;
                                } 
                            } else {
                                if (informacaoDesconhecido.posicao_conversa == 0)  {                                                                                                                                                                                                                          // 4º = Tempo de Espera          
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoDesconhecido.lado, fala_personagem [1], buffer, informacaoDesconhecido.face [0],"",                                                                                                                            // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                           
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoDesconhecido.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 1, &informacaoDesconhecido.fala);
                                } else if (informacaoDesconhecido.posicao_conversa == 1) {
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoDesconhecido.lado, fala_personagem [1], buffer, informacaoDesconhecido.face [0],"Você ainda não conseguiu!",
                                                                                                                                                  "Volte quando tiver juntado todas as moedas", 
                                                                                                                                                  "que pedi...",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 0, &informacaoDesconhecido.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 1, &informacaoDesconhecido.fala);  
                                }
                            }
                        }
                    }
                    
                    
                    if (opcao == 0) {
                        if (key[KEY_ESC]) {                              //Abre Menu                                                                                                                                                                                                                                                                                                                                           
                            opcao = 1;
                            play_sample (audio_efeito [3], 500, 128, 1000, 0);
                        }
                    }
                
                    if (opcao != 0) {
                        opcao = pausa_menu (buffer, opcao, &animacao_bola, &animacao_bola_delay);        
                    }
                
                    if (informacaoPersonagem.vigor <= 0){
                        clear (buffer);
                        draw_sprite(buffer, cenario, 0,  0);
                        efeito_agua (buffer, 190, 440, &animacao_agua_1, &animacao_agua_1_delay, &animacao_agua_2, &animacao_agua_2_delay);
                        efeito_fogo (buffer, 513, 210, &animacao_fogo [0], &animacao_fogo_delay [0]);
                        efeito_fogo (buffer, 610, 210, &animacao_fogo [1], &animacao_fogo_delay [1]);
                        draw_sprite (buffer, porta [0], 160, 131);
                        draw_sprite (buffer, portao_ginasio [0], 543, 191); 
                        if (informacaoVespa1.vigor > 0) {
                            draw_sprite(buffer, vespa [informacaoVespa1.lado][informacaoVespa1.animacao], informacaoVespa1.x, informacaoVespa1.y);
                        }
                        if (informacaoVespa2.vigor > 0) {
                            draw_sprite(buffer, vespa [informacaoVespa2.lado][informacaoVespa2.animacao], informacaoVespa2.x, informacaoVespa2.y);
                        }
                        draw_sprite(buffer, personagem_desmaiado, informacaoPersonagem.x , informacaoPersonagem.y);
                        draw_sprite(buffer, npc1 [informacaoNpc1.lado][informacaoNpc1.animacao], informacaoNpc1.x, informacaoNpc1.y);
                        if (progresso == 3) {
                            set_alpha_blender();
                            draw_trans_sprite(buffer, desconhecido [informacaoDesconhecido.lado][informacaoDesconhecido.animacao], informacaoDesconhecido.x, informacaoDesconhecido.y);
                        }
                        teste_efeito_nuvem = efeito_nuvens (buffer, teste_efeito_nuvem, 0, altura_nuvem_1, 3, &animacao_1_sombra_nuvem , &animacao_1_sombra_nuvem_delay, &animacao_2_sombra_nuvem, &animacao_2_sombra_nuvem_delay, &animacao_3_sombra_nuvem, &animacao_3_sombra_nuvem_delay);  //2º Parametro - Imagem da Nuvem
                        teste_efeito_nuvem = efeito_nuvens (buffer, teste_efeito_nuvem, 0, altura_nuvem_2, 25, &animacao_1_sombra_nuvem , &animacao_1_sombra_nuvem_delay, &animacao_2_sombra_nuvem, &animacao_2_sombra_nuvem_delay, &animacao_3_sombra_nuvem, &animacao_3_sombra_nuvem_delay);  //3º Parametro - Velocidade (quanto menor o valor, maior a velocidade)
                        efeito_sombra_ginasio (buffer, 419, 195); 
                        efeito_barra_de_status_personagem (buffer, informacaoPersonagem.vigor, informacaoPersonagem.energia, &animacao_status, &animacao_status_delay, informacaoPersonagem.moedas, datFontes, informacaoPersonagem.experiencia_atual_porcentagem, informacaoPersonagem.nivel); 
                        
                        // Desenhos as habilidades da barra de habilidades //
                        if (informacaoPersonagem.habilidade1 == 1) efeito_habilidade_1_ativa (buffer, 5 + 2, 120 + 2, &animacao_habilidade1, &animacao_habilidade1_delay);
                        
                        mapa_atual = 3;
                        musica = 3;
                    }
                    // Limpa Buffer //
                    draw_sprite(screen, buffer, 0, 0);
                    clear (buffer);
                
                }
                 //   -----------------------------------------------------     FIM PROGRESSO 1    ------------------------------------------------------------------- //
 
                // Destroi Imagens //
                for (cont_destruir_x = 0; cont_destruir_x != 4; cont_destruir_x++) {
                    for (cont_destruir_y = 0; cont_destruir_y != 4; cont_destruir_y++) {
                        destroy_bitmap (npc1 [cont_destruir_x][cont_destruir_y]);
                        destroy_bitmap (vespa [cont_destruir_x][cont_destruir_y]);
                    }
                }
                
                for (cont_destruir_x = 0; cont_destruir_x < 2; cont_destruir_x++) { 
                    destroy_bitmap (porta [cont_destruir_x]);
                    destroy_bitmap (portao_ginasio [cont_destruir_x]);    
                }
                
                if (progresso == 3){
                    for (cont_destruir_x = 0; cont_destruir_x != 4; cont_destruir_x++) {
                        for (cont_destruir_y = 0; cont_destruir_y != 4; cont_destruir_y++) {
                            destroy_bitmap (desconhecido[cont_destruir_x][cont_destruir_y]);
                        }
                    }
                    destroy_bitmap (informacaoDesconhecido.face [0]); 
                }  
                
                destroy_bitmap (informacaoNpc1.face [0]);
                destroy_bitmap (informacaoNpc1.face [1]);
                destroy_bitmap (informacaoNpc1.face [2]);            
                    
             } // FIM MAPA 1
//  ================================================================================================================================================================================================================= //               
//  =============================================================================================  CENÁRIO CASA DO PERSONAGEM  ====================================================================================== //              
            if (mapa_atual == 2) {   
            // Load dos sprites que serão usados neste mapa //
            // Mariana //
            mariana [0][0] = load_bitmap("Imagens/Personagens/Mariana/frente31.bmp",NULL);
            mariana [0][1] = load_bitmap("Imagens/Personagens/Mariana/frente32.bmp",NULL);
            mariana [0][2] = load_bitmap("Imagens/Personagens/Mariana/frente33.bmp",NULL);
            mariana [0][3] = load_bitmap("Imagens/Personagens/Mariana/frente34.bmp",NULL);
    
            mariana [1][0] = load_bitmap("Imagens/Personagens/Mariana/direita31.bmp",NULL);
            mariana [1][1] = load_bitmap("Imagens/Personagens/Mariana/direita32.bmp",NULL);
            mariana [1][2] = load_bitmap("Imagens/Personagens/Mariana/direita33.bmp",NULL);
            mariana [1][3] = load_bitmap("Imagens/Personagens/Mariana/direita34.bmp",NULL);
        
            mariana [2][0] = load_bitmap("Imagens/Personagens/Mariana/costas31.bmp",NULL);
            mariana [2][1] = load_bitmap("Imagens/Personagens/Mariana/costas32.bmp",NULL);
            mariana [2][2] = load_bitmap("Imagens/Personagens/Mariana/costas33.bmp",NULL);
            mariana [2][3] = load_bitmap("Imagens/Personagens/Mariana/costas34.bmp",NULL);
    
            mariana [3][0] = load_bitmap("Imagens/Personagens/Mariana/esquerda31.bmp",NULL);
            mariana [3][1] = load_bitmap("Imagens/Personagens/Mariana/esquerda32.bmp",NULL);
            mariana [3][2] = load_bitmap("Imagens/Personagens/Mariana/esquerda33.bmp",NULL);
            mariana [3][3] = load_bitmap("Imagens/Personagens/Mariana/esquerda34.bmp",NULL);
            
            // Cachorro Snoop //
            cachorro [0][0] = load_bitmap("Imagens/Personagens/Cachorro/frente41.bmp",NULL);
            cachorro [0][1] = load_bitmap("Imagens/Personagens/Cachorro/frente42.bmp",NULL);
            cachorro [0][2] = load_bitmap("Imagens/Personagens/Cachorro/frente43.bmp",NULL);
            cachorro [0][3] = load_bitmap("Imagens/Personagens/Cachorro/frente44.bmp",NULL);
    
            cachorro [1][0] = load_bitmap("Imagens/Personagens/Cachorro/direita41.bmp",NULL);
            cachorro [1][1] = load_bitmap("Imagens/Personagens/Cachorro/direita42.bmp",NULL);
            cachorro [1][2] = load_bitmap("Imagens/Personagens/Cachorro/direita43.bmp",NULL);
            cachorro [1][3] = load_bitmap("Imagens/Personagens/Cachorro/direita44.bmp",NULL);
        
            cachorro [2][0] = load_bitmap("Imagens/Personagens/Cachorro/costas41.bmp",NULL);
            cachorro [2][1] = load_bitmap("Imagens/Personagens/Cachorro/costas42.bmp",NULL);
            cachorro [2][2] = load_bitmap("Imagens/Personagens/Cachorro/costas43.bmp",NULL);
            cachorro [2][3] = load_bitmap("Imagens/Personagens/Cachorro/costas44.bmp",NULL);
    
            cachorro [3][0] = load_bitmap("Imagens/Personagens/Cachorro/esquerda41.bmp",NULL);
            cachorro [3][1] = load_bitmap("Imagens/Personagens/Cachorro/esquerda42.bmp",NULL);
            cachorro [3][2] = load_bitmap("Imagens/Personagens/Cachorro/esquerda43.bmp",NULL);
            cachorro [3][3] = load_bitmap("Imagens/Personagens/Cachorro/esquerda44.bmp",NULL);
            
            informacaoMariana.face [0] = load_bitmap ("Imagens/Personagens/Mariana/Faces/face_mariana_0.tga", NULL);
	        informacaoMariana.face [1] = load_bitmap ("Imagens/Personagens/Mariana/Faces/face_mariana_1.tga", NULL);
                
                
                
                 //   ------------------------------------------------------       Cena Animada       ------------------------------------------------------------------- //  
                if (cena_animada == 0) {
                    if (cena_animada_informacoes_iniciais == 0) {
                        informacaoPersonagem.x    =  125;
                        informacaoPersonagem.y    =  320;
                        informacaoPersonagem.lado =  1;
                        
                        informacaoMariana.x             =  500;
                        informacaoMariana.y             =  410;
                        informacaoMariana.lado          =  3;
                        informacaoMariana.delayanimacao =  0;
                        
                        informacaoCachorro.x             =  500;
                        informacaoCachorro.y             =  250;
                        informacaoCachorro.lado          =  3;
                        informacaoCachorro.delayanimacao =  0;
                        
                        interacaoBau1.x = 310;
                        interacaoBau1.y = 120;
                        
                        fadeout (8);      
                        clear (buffer);
                        cenario = load_jpg("Imagens/EstilosCenarios/cenario_casa_personagem.jpg",NULL);
                        
                        draw_sprite(buffer, cenario, 0,  0);  
                        efeito_bau (buffer, interacaoBau1.x, interacaoBau1.y, &interacaoBau1.animacao, &interacaoBau1.animacao_delay, &interacaoBau1.animacao_brilho, &interacaoBau1.animacao_brilho_delay, interacaoBau1.estado);
                        draw_sprite(buffer, personagem [informacaoPersonagem.lado][informacaoPersonagem.animacao], informacaoPersonagem.x, informacaoPersonagem.y);
                        draw_sprite(buffer, cachorro [informacaoCachorro.lado][informacaoCachorro.animacao], informacaoCachorro.x, informacaoCachorro.y);
                        draw_sprite(buffer, mariana [informacaoMariana.lado][informacaoMariana.animacao], informacaoMariana.x, informacaoMariana.y);
                        efeito_barra_de_status_personagem (buffer, informacaoPersonagem.vigor, informacaoPersonagem.energia, &animacao_status, &animacao_status_delay, informacaoPersonagem.moedas, datFontes, informacaoPersonagem.experiencia_atual_porcentagem, informacaoPersonagem.nivel);
                        fadein (buffer, 8);  
                        informacaoMariana.terreno = 7;  
                        cena_animada_informacoes_iniciais = 1;
                    }
                    if (informacaoMariana.x >= 200) {
                        movimentarSpriteAutomaticamente(&informacaoMariana.x, &informacaoMariana.y, &informacaoMariana.lado, &informacaoMariana.animacao, &informacaoMariana.delayanimacao, informacaoMariana.terreno,  2, 100, 500, 50, &animacao_npc_delay, informacaoMariana.velocidade_animacao);  
                    } else {
                        cena_animada = 1;
                        informacaoMariana.colisao_para_conversar = 1; 
                    }
                    
                    movimentarSpriteAutomaticamente(&informacaoCachorro.x, &informacaoCachorro.y, &informacaoCachorro.lado, &informacaoCachorro.animacao, &informacaoCachorro.delayanimacao, informacaoCachorro.terreno,  2, 100, 500, 50, &animacao_npc_delay, informacaoCachorro.velocidade_animacao);
                    
                    draw_sprite(buffer, cenario, 0,  0);
                    efeito_bau (buffer, interacaoBau1.x, interacaoBau1.y, &interacaoBau1.animacao, &interacaoBau1.animacao_delay, &interacaoBau1.animacao_brilho, &interacaoBau1.animacao_brilho_delay, interacaoBau1.estado);    
                    draw_sprite(buffer, mariana [informacaoMariana.lado][informacaoMariana.animacao], informacaoMariana.x, informacaoMariana.y);
                    draw_sprite(buffer, cachorro [informacaoCachorro.lado][informacaoCachorro.animacao], informacaoCachorro.x, informacaoCachorro.y);
                    draw_sprite(buffer, personagem [informacaoPersonagem.lado][informacaoPersonagem.animacao], informacaoPersonagem.x, informacaoPersonagem.y);
                    efeito_barra_de_status_personagem (buffer, informacaoPersonagem.vigor, informacaoPersonagem.energia, &animacao_status, &animacao_status_delay, informacaoPersonagem.moedas, datFontes, informacaoPersonagem.experiencia_atual_porcentagem, informacaoPersonagem.nivel);
                    draw_sprite (screen, buffer, 0, 0);
                } else if (progresso_global == 0) {
               
                //   -----------------------------------------------------      INICIO PROGRESSO 0    ------------------------------------------------------------------- //  

                    // Atualiza Figuras no Buffer //
                    draw_sprite(buffer, cenario, 0,  0);    
                    efeito_bau (buffer, interacaoBau1.x, interacaoBau1.y, &interacaoBau1.animacao, &interacaoBau1.animacao_delay, &interacaoBau1.animacao_brilho, &interacaoBau1.animacao_brilho_delay, interacaoBau1.estado);
                    draw_sprite(buffer, mariana [informacaoMariana.lado][informacaoMariana.animacao], informacaoMariana.x, informacaoMariana.y);
                    draw_sprite(buffer, cachorro [informacaoCachorro.lado][informacaoCachorro.animacao], informacaoCachorro.x, informacaoCachorro.y);
                    draw_sprite(buffer, personagem [informacaoPersonagem.lado][informacaoPersonagem.animacao], informacaoPersonagem.x, informacaoPersonagem.y);
                    
                    // Desenha Barra de vigor do Personagem// 
                    efeito_barra_de_status_personagem (buffer, informacaoPersonagem.vigor, informacaoPersonagem.energia, &animacao_status, &animacao_status_delay, informacaoPersonagem.moedas, datFontes, informacaoPersonagem.experiencia_atual_porcentagem, informacaoPersonagem.nivel);
                    
                    movimentarSpriteAutomaticamente(&informacaoCachorro.x, &informacaoCachorro.y, &informacaoCachorro.lado, &informacaoCachorro.animacao, &informacaoCachorro.delayanimacao, informacaoCachorro.terreno, 1, 237, 300, 50, &animacao_npc_delay, informacaoCachorro.velocidade_animacao);    // Parametros Numéricos//                                                                                                                                                                                                           // 7º Parametro responsável pelo sentido "1" para Vertical ou "2" para Horizontal
                    
                    if (informacaoMariana.colisao_para_conversar == 0) {
                        informacaoMariana.posicao_conversa = 0;
                        movimentarSpriteAutomaticamente(&informacaoMariana.x, &informacaoMariana.y, &informacaoMariana.lado, &informacaoMariana.animacao, &informacaoMariana.delayanimacao, informacaoMariana.terreno, 1, 237, 300, 50, &animacao_npc_delay, informacaoMariana.velocidade_animacao);    // Parametros Numéricos//                                                                                                                                                                                                           // 7º Parametro responsável pelo sentido "1" para Vertical ou "2" para Horizontal
                    } else {                                                                                                                                                                                                                                                                                 // 1º = Sentido (1 Para Horizontal) (2 Para Vertical)
                        informacaoMariana.animacao = 0;
                        informacaoMariana.terreno  = TERRENO_ARENOSO;                                                                                                                                                                                                                                        // 2º = coordenada da posical Inicial da locomoção (geralmente onde o sprite inicia na tela) *Lembre-se que é a coordenada X ou Y, especificada de acordo com o sentido.
                        if (informacaoMariana.posicao_conversa == 0)   {                                                                                                                                                                                                                                                       // 3º = coordenada da posicao Final da locomoção.
                             animacao_balao = 0;
                             interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoMariana.face [1],"",                                                                                                                               // 4º = Tempo de Espera
                                                                                                                                                  "",                                                                                                                                                        // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                        } else if (informacaoMariana.posicao_conversa == 1) {
                            efeito_balao_exclamacao(buffer, informacaoPersonagem.x, informacaoPersonagem.y, &animacao_balao, &animacao_balao_delay); 
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoMariana.face [1],"João! Vai acabar se atrasando para o treino.",
                                                                                                                                                                             "Melhor você se apressar ou não poderá entrar.", 
                                                                                                                                                                             "",
                                                                                                                                                                             "", 
                                                                                                                                                                             "", datFontes, 2, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);    
                        } else if (informacaoMariana.posicao_conversa == 2) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoPersonagem.face [0],"Ok mamãe, já estou indo!",
                                                                                                                                                                                "Não posso perder meu primeiro treino", 
                                                                                                                                                                                "por nada!",
                                                                                                                                                                                "", 
                                                                                                                                                                                "", datFontes, 3, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay); 
                        } else if (informacaoMariana.posicao_conversa == 3) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoMariana.face [0],"Ta bom meu filho, mas tome cuidado.",
                                                                                                                                                                             "Antes de você ir deixa eu te dar", 
                                                                                                                                                                             "algumas dicas importantes, ok?",
                                                                                                                                                                             "Você vai precisar delas sempre, então", 
                                                                                                                                                                             "por favor, preste muita atenção:", datFontes, 4, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay); 
                        } else if (informacaoMariana.posicao_conversa == 4) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer,  informacaoMariana.face [0],"Para andar pressione as setas do teclado.",
                                                                                                                                                                              "Para correr segure a tecla 'SHIFT' enquanto anda.", 
                                                                                                                                                                              "Para interagir com as pessoas e objetos",
                                                                                                                                                                              "pressione a tecla 'Z'.", 
                                                                                                                                                                              "Para acessar o menu tecle 'ESC.'", datFontes, 5, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay); 
                        } else if (informacaoMariana.posicao_conversa == 5) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer,  informacaoMariana.face [0],"Fique atento também a sua barra de",
                                                                                                                                                                           "informações localizada na parte superior da tela.", 
                                                                                                                                                                           "Ela indica coisas importantes sobre você, tais como,",
                                                                                                                                                                           "o estado de seu vigor, sua energia, seu nível,", 
                                                                                                                                                                           "habilidades e também sua condição financeira.", datFontes, 6, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                        } else if (informacaoMariana.posicao_conversa == 6) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer,  informacaoMariana.face [0],"A barra da parte inferior da tela mostra",
                                                                                                                                                                           "quanto de experiência que você possui.", 
                                                                                                                                                                           "Quando esta barra estiver completamente",
                                                                                                                                                                           "cheia você subirá de nível.", 
                                                                                                                                                                           "Quanto maior seu nível, mais forte será.", datFontes, 7, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                        } else if (informacaoMariana.posicao_conversa == 7) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer,  informacaoMariana.face [0],"Ah, e abra o baú que está no meu quarto.",
                                                                                                                                                                           "Tem uma coisa importante para você lá.", 
                                                                                                                                                                           "Depois de ter pego vá, não quero que",
                                                                                                                                                                           "se atrase no primeiro dia de treinamento!", 
                                                                                                                                                                           "", datFontes, 8, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                        }
                    }
                    
                    if (opcao != 0) {
                        opcao = pausa_menu (buffer, opcao, &animacao_bola, &animacao_bola_delay);        
                    }
                
                    // Desenha na Tela //
                    draw_sprite(screen, buffer, 0, 0);
                    clear (buffer);
                                        
                    if (informacaoMariana.posicao_conversa > 7) {
                        informacaoMariana.posicao_conversa = 0;
                        progresso_global = 1;
                    }
                } //   -----------------------------------------------------      FIM PROGRESSO 0    ------------------------------------------------------------------- //
               
                  //   -----------------------------------------------------     INICIO PROGRESSO 1    ------------------------------------------------------------------- //
               
               if (progresso_global == 1) {   
                    if (musica == 1) {
                        cenario = load_jpg("Imagens/EstilosCenarios/cenario_casa_personagem.jpg",NULL); 
                        
                        // Localização Inicial dos NPCs Da Casa do Personagem
                        if (progresso == 0) {
                            informacaoMariana.x                      =  400;
                            informacaoMariana.y                      =  100;
                        } else if (progresso == 1) {
                            informacaoMariana.x                      =  400;
                            informacaoMariana.y                      =  200;
                            stop_sample (audio_efeito [7]);                         
                            play_sample (audio_efeito [7], 70, 128, 1000, 1);   
                        } else if (progresso == 3) {
                            informacaoAlexandre.posicao_conversa = 0; //Prepara para falar automáticamente ao entrar no mapa da vila. 
                        }
                        informacaoMariana.colisao_para_conversar =  0;
                        informacaoMariana.lado                   =  0;
                    
                        // Efeito de Fadeout e Limpa Tela
                        fadeout (8);      
                        clear (buffer);

                        // Objetos Interativos
                        interacaoBau1.x = 310;
                        interacaoBau1.y = 120;
                    
                        // Desenho das Primitivas do Jogo No Buffer //
                        draw_sprite(buffer, cenario, 0,  0);  
                        efeito_bau (buffer, interacaoBau1.x, interacaoBau1.y, &interacaoBau1.animacao, &interacaoBau1.animacao_delay, &interacaoBau1.animacao_brilho, &interacaoBau1.animacao_brilho_delay, interacaoBau1.estado);
                        draw_sprite(buffer, personagem [informacaoPersonagem.lado][informacaoPersonagem.animacao], informacaoPersonagem.x, informacaoPersonagem.y);
                        draw_sprite(buffer, mariana [informacaoMariana.lado][informacaoMariana.animacao], informacaoMariana.x, informacaoMariana.y);
                        draw_sprite(buffer, cachorro [informacaoCachorro.lado][informacaoCachorro.animacao], informacaoCachorro.x, informacaoCachorro.y);
                        efeito_barra_de_status_personagem (buffer, informacaoPersonagem.vigor, informacaoPersonagem.energia, &animacao_status, &animacao_status_delay, informacaoPersonagem.moedas, datFontes, informacaoPersonagem.experiencia_atual_porcentagem, informacaoPersonagem.nivel);                  
                        
                        // Desenhos as habilidades da barra de habilidades //
                        if (informacaoPersonagem.habilidade1 == 1) efeito_habilidade_1_ativa (buffer, 5 + 2, 120 + 2, &animacao_habilidade1, &animacao_habilidade1_delay);
                    
                        // Efeitos de Fadein utilizando as primitivas desenhadas no buffer anteriormente //
                        fadein (buffer, 8);                                                  // Fadeout do cenário anterior, quanto menor o valor mais rápido é
                        musica = 2;          
                    }

                    
                    // Atualiza Largura e Altura do Personagem Principal //
                    informacaoPersonagem.largura = informacaoPersonagem.x + SPRITE_LARGURA;
                    informacaoPersonagem.altura  = informacaoPersonagem.y + SPRITE_ALTURA;
            
                    // Atualiza Largura e Altura de Mariana //
                    informacaoMariana.largura = informacaoMariana.x + SPRITE_NPC_LARGURA;
                    informacaoMariana.altura  = informacaoMariana.y + SPRITE_NPC_ALTURA;
                    
                    // Atualiza Largura e Altura do Cachorro //
                    informacaoCachorro.largura = informacaoCachorro.x + SPRITE_NPC_LARGURA;
                    informacaoCachorro.altura  = informacaoCachorro.y + SPRITE_NPC_ALTURA;
                    
                    // Atualiza Informação sobre Ataque do Personagem //
                    informacaoBola.x = informacaoPersonagem.x + 10;
                    informacaoBola.y = informacaoPersonagem.y + 25;       
            
                    // Testes de Colisões Cecario Casa Personagem//            
                    // Toda Parte Em Volta//
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 65, 480, 630, 565, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 680, 480, 735, 565, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 70, 30, 90, 475, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 70, 30, 745, 90, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 710, 40, 740, 475, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    
                    // Paredes da Esquerda //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 360, 275, 375, 400, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 130, 255, 375, 315, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                
                    // Paredes do Norte //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 360, 145, 375, 180, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 380, 160, 500, 180, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 555, 160, 740, 180, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 680, 95, 705, 145, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                
                    // Com Mesa ~ Roupa ~ Estante do Quarto ~ Cama ~ do Personagem //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 170, 355, 245, 350, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);                            
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 255, 330, 355, 335, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao); 
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 95, 345, 115, 365, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao); 
                
                    // Com Mesa Maior ~ Mesa Menor ~ Chapéu ~ Cama - da Mãe do Personagem //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 95, 160, 115, 185, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao); 
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 205, 130, 245, 145, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao); 
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 170, 110, 190, 115, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao); 
                
                    // Com Mesa Grande Entrada e Cadeiras//
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 525, 320, 660, 380, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao); 
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 495, 360, 620, 335, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao); 
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 700, 360, 735, 335, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);      
                    
                    // Com Bau 1 /
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, interacaoBau1.x + 5, interacaoBau1.y - 5, interacaoBau1.x + 15, interacaoBau1.y - 5, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);      
                    
                    // Testa Interacao com Bau 1 (Que contem habilidade) //
                    detectarColisaoInteracaoObjetoCima(&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, interacaoBau1.x + 5, interacaoBau1.y, interacaoBau1.x + 15, interacaoBau1.y + 1, informacaoPersonagem.lado, &interacaoBau1.estado);
                        
                    // Para Mudar de Mapa //
                    if (progresso == 0) {
                        detectarColisaoEntrarSair(&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 640, 580, 670, 590, &mapa_atual, 1);
                    } else if (progresso == 1) {
                        detectarColisaoEntrarSair(&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 640, 580, 670, 590, &mapa_atual, 7);
                    } else if (progresso == 2) {
                        caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 640, 580, 670, 590, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);      
                    } else if (progresso == 3) {
                        detectarColisaoEntrarSair(&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 640, 580, 670, 590, &mapa_atual, 1);
                    }
                    // Com NPC's //
                    informacaoMariana.colisao_para_conversar = detectarColisaoSprite  (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, (informacaoMariana.x + 1) , (informacaoMariana.y + 35), informacaoMariana.largura + 5, informacaoMariana.altura + 5, informacaoPersonagem.terreno, &informacaoMariana.animacao);
                    caso_colisao  = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, (informacaoMariana.x + 6) , (informacaoMariana.y + 40), informacaoMariana.largura, informacaoMariana.altura, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao  = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, (informacaoCachorro.x + 12) , (informacaoCachorro.y + 4), informacaoCachorro.largura - 10, informacaoCachorro.altura  - 16, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    informacaoCachorro.colisao_para_conversar = detectarColisaoSprite (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, (informacaoCachorro.x) , (informacaoCachorro.y - 5), informacaoCachorro.largura + 5, informacaoCachorro.altura + 5, informacaoPersonagem.terreno, &informacaoCachorro.animacao);
                    
                    // Atualiza Figuras no Buffer //
                    draw_sprite(buffer, cenario, 0,  0);    
                    efeito_bau (buffer, interacaoBau1.x, interacaoBau1.y, &interacaoBau1.animacao, &interacaoBau1.animacao_delay, &interacaoBau1.animacao_brilho, &interacaoBau1.animacao_brilho_delay, interacaoBau1.estado);
                    draw_sprite(buffer, cachorro [informacaoCachorro.lado][informacaoCachorro.animacao], informacaoCachorro.x, informacaoCachorro.y);
                    
                    // Ataque da Bola  desenhada Atras do Sprite //
                    if (informacaoPersonagem.habilidade1 == 1) { 
                        if (informacaoPersonagem.lado == 2) {
                            if (informacaoBola.delayanimacao <= 0) {
                                efeito_ataque (buffer, &informacaoBola.x, &informacaoBola.y, &informacaoBola.delayanimacao, &informacaoPersonagem.energia, informacaoPersonagem.lado, &informacaoPersonagem.animacao, informacaoPersonagem.ataque1, &animacao_efeito_ataque, &animacao_efeito_ataque_2);
                                informacaoPersonagem.energia = informacaoPersonagem.energia + 1;
                            } else if (informacaoBola.delayanimacao > 0) {
                            efeito_ataque (buffer, &informacaoBola.x, &informacaoBola.y, &informacaoBola.delayanimacao, &informacaoPersonagem.energia, informacaoPersonagem.lado, &informacaoPersonagem.animacao, informacaoPersonagem.ataque1, &animacao_efeito_ataque, &animacao_efeito_ataque_2);
                            }
                            if (informacaoPersonagem.energia  > 3) {
                                informacaoPersonagem.energia = 3;
                            }
                         }
                    }   
                    
                    if (informacaoPersonagem.y >  informacaoMariana.y){
                        draw_sprite(buffer, mariana [informacaoMariana.lado][informacaoMariana.animacao], informacaoMariana.x, informacaoMariana.y);
                        draw_sprite(buffer, personagem [informacaoPersonagem.lado][informacaoPersonagem.animacao], informacaoPersonagem.x, informacaoPersonagem.y);
                    } else {
                        draw_sprite(buffer, personagem [informacaoPersonagem.lado][informacaoPersonagem.animacao], informacaoPersonagem.x, informacaoPersonagem.y);
                        draw_sprite(buffer, mariana [informacaoMariana.lado][informacaoMariana.animacao], informacaoMariana.x, informacaoMariana.y);
                    }
                    
                    // Ataque da Bola  desenhada na Frente do Sprite //
                    if (informacaoPersonagem.habilidade1 == 1) {
                        if (informacaoPersonagem.lado != 2) {
                            if (informacaoBola.delayanimacao <= 0) {
                                efeito_ataque (buffer, &informacaoBola.x, &informacaoBola.y, &informacaoBola.delayanimacao, &informacaoPersonagem.energia, informacaoPersonagem.lado, &informacaoPersonagem.animacao, informacaoPersonagem.ataque1, &animacao_efeito_ataque, &animacao_efeito_ataque_2);
                                informacaoPersonagem.energia = informacaoPersonagem.energia + 1;
                            } else if (informacaoBola.delayanimacao > 0) {
                                efeito_ataque (buffer, &informacaoBola.x, &informacaoBola.y, &informacaoBola.delayanimacao, &informacaoPersonagem.energia, informacaoPersonagem.lado, &informacaoPersonagem.animacao, informacaoPersonagem.ataque1, &animacao_efeito_ataque, &animacao_efeito_ataque_2);
                            }
                            if (informacaoPersonagem.energia  > 3) {
                                informacaoPersonagem.energia = 3;
                            }
                        }
                    } 
                    informacaoBola.delayanimacao = informacaoBola.delayanimacao - 1;  
                    
                    // Desenha Barra de vigor do Personagem// 
                    efeito_barra_de_status_personagem (buffer, informacaoPersonagem.vigor, informacaoPersonagem.energia, &animacao_status, &animacao_status_delay, informacaoPersonagem.moedas, datFontes, informacaoPersonagem.experiencia_atual_porcentagem, informacaoPersonagem.nivel);
                    
                    // Desenhos as habilidades da barra de habilidades //
                    if (informacaoPersonagem.habilidade1 == 1) efeito_habilidade_1_ativa (buffer, 5 + 2, 120 + 2, &animacao_habilidade1, &animacao_habilidade1_delay);
                    
                    // Tutorial Para Usar Habilidade //
                    if (animacao_habilidade1 == 5) {   // 60 é o tempo para acabar o efeito sonoro
                        mapa_atual = 5;
                    } 
                    
                    // Teste Para caso Pegue Habilidade do Baú 1 //
                    if (interacaoBau1.animacao >= 3) {
                        efeito_ganhar_habilidade (buffer, -8, 103, &animacao_ganha_habilidade, &animacao_ganha_habilidade_delay);
                        if (animacao_ganha_habilidade == 10){
                            informacaoPersonagem.habilidade1 = 1;
                        }
                    }
                    
                    if (informacaoCachorro.colisao_para_conversar == 0) {
                        informacaoCachorro.posicao_conversa = 0;
                        movimentarSpriteAutomaticamente(&informacaoCachorro.x, &informacaoCachorro.y, &informacaoCachorro.lado, &informacaoCachorro.animacao, &informacaoCachorro.delayanimacao, informacaoCachorro.terreno, 1, 260, 350, 30, &animacao_npc_delay, informacaoCachorro.velocidade_animacao);    // Parametros Numéricos//                                                                                                                                                                                                           // 7º Parametro responsável pelo sentido "1" para Vertical ou "2" para Horizontal
                    } else {
                        informacaoCachorro.animacao = 0;         
                        if (informacaoCachorro.posicao_conversa == 0)   {
                            animacao_balao = 0;                                                                                                                                                                                                                              // 3º = coordenada da posicao Final da locomoção.
                            interacaoNpc (informacaoPersonagem.lado, &informacaoCachorro.lado, fala_personagem [1], buffer, informacaoPersonagem.face [0],"",                                                                                                                           // 4º = Tempo de Espera
                                                                                                                                                  "",                                                                                                                           // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoCachorro.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoCachorro.fala);
                        
                        } else if (informacaoCachorro.posicao_conversa == 1) {
                            efeito_balao_coracao(buffer, informacaoCachorro.x, informacaoCachorro.y, &animacao_balao, &animacao_balao_delay); 
                            interacaoNpc (informacaoPersonagem.lado, &informacaoCachorro.lado, fala_personagem [1], buffer, informacaoPersonagem.face [0],"E ae Snoop!! Beleza amigão!?",
                                                                                                                                                  "Esse cachorrinho foi um grande", 
                                                                                                                                                  "presente do meu pai...",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 0, &informacaoCachorro.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoCachorro.fala);    
                        }    
                    }
                    
                    
                    if (informacaoMariana.colisao_para_conversar == 0) {
                        informacaoMariana.posicao_conversa = 0;     
                        movimentarSpriteAutomaticamente(&informacaoMariana.x, &informacaoMariana.y, &informacaoMariana.lado, &informacaoMariana.animacao, &informacaoMariana.delayanimacao, informacaoMariana.terreno, 2, 400, 625, 50, &animacao_npc_delay, informacaoMariana.velocidade_animacao);    // Parametros Numéricos//                                                                                                                                                                                                           // 7º Parametro responsável pelo sentido "1" para Vertical ou "2" para Horizontal
                    } else {                                                                                                                                                                                                                                                        // 1º = Sentido (1 Para Vertical) (2 Para Horizontal)
                        informacaoMariana.animacao = 0; 
                        if (progresso == 0) {                                                                                                                                                                                                                               // 2º = coordenada da posical Inicial da locomoção (geralmente onde o sprite inicia na tela) *Lembre-se que é a coordenada X ou Y, especificada de acordo com o sentido.
                            if (informacaoMariana.posicao_conversa == 0)   {                                                                                                                                                                                                                              // 3º = coordenada da posicao Final da locomoção.
                                animacao_balao = 0;
                                interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoMariana.face [1],"",                                                                                                                           // 4º = Tempo de Espera
                                                                                                                                                  "",                                                                                                                           // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);
                            } else if (informacaoMariana.posicao_conversa == 1) {
                                efeito_balao_exclamacao(buffer, informacaoMariana.x, informacaoMariana.y, &animacao_balao, &animacao_balao_delay); 
                                interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoMariana.face [1],"O que você ta fazendo aqui ainda?",
                                                                                                                                                  "Vá rápido!", 
                                                                                                                                                  "",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 0, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);    
                            } 
                        } else if (progresso == 1) {
                            if (informacaoMariana.posicao_conversa == 0)   {                                                                                                                                                                                                                              // 3º = coordenada da posicao Final da locomoção.
                                animacao_balao = 0;
                                interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoPersonagem.face [0],"",                                                                                                                           // 4º = Tempo de Espera
                                                                                                                                                  "",                                                                                                                           // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);
                            } else if (informacaoMariana.posicao_conversa == 1) {
                                efeito_balao_exclamacao(buffer, informacaoPersonagem.x, informacaoPersonagem.y, &animacao_balao, &animacao_balao_delay); 
                                interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoPersonagem.face [0],"Mãe! Você não vai acreditar!",
                                                                                                                                                  "Hoje no treino eu me saí muito bem!", 
                                                                                                                                                  "Até o treinador Roberto disse que",
                                                                                                                                                  "eu estava parecendo com o papai", 
                                                                                                                                                  "em campo!!!", datFontes, 2, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);    
                            } else if (informacaoMariana.posicao_conversa == 2) {
                                efeito_balao_exclamacao(buffer, informacaoPersonagem.x, informacaoPersonagem.y, &animacao_balao, &animacao_balao_delay); 
                                interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoMariana.face [0],"Ligeirinho Jr. é? Hmm...",
                                                                                                                                                  "Legal filho, parabéns, mas você", 
                                                                                                                                                  "está todo enxarcado de água!",
                                                                                                                                                  "Vá tomar um banho quente se não", 
                                                                                                                                                  "vai acabar ficando resfriado.", datFontes, 3, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);    
                            } else if (informacaoMariana.posicao_conversa == 3) {
                                efeito_balao_exclamacao(buffer, informacaoPersonagem.x, informacaoPersonagem.y, &animacao_balao, &animacao_balao_delay); 
                                interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoPersonagem.face [0],"Ok mamãe, vo la tomar um",
                                                                                                                                                  "banho quente e já vou direto pra cama...", 
                                                                                                                                                  "o treino foi bem puxado, estou bem cansado,",
                                                                                                                                                  "mas ao mesmo tempo estou muito feliz!", 
                                                                                                                                                  "", datFontes, 4, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);    
                            } else if (informacaoMariana.posicao_conversa == 4) {
                                efeito_balao_exclamacao(buffer, informacaoPersonagem.x, informacaoPersonagem.y, &animacao_balao, &animacao_balao_delay); 
                                interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoPersonagem.face [0],"Ok mamãe, vo la tomar um",
                                                                                                                                                  "banho quente e já vou direto pra cama...", 
                                                                                                                                                  "o treino foi bem puxado, estou bem cansado,",
                                                                                                                                                  "mas ao mesmo tempo estou muito feliz!", 
                                                                                                                                                  "", datFontes, 0, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);    
                                mapa_atual = 9;
                                musica = 1;
                                informacaoMariana.posicao_conversa = 0;
                            }      
                        } else if (progresso == 2) {
                            if (informacaoMariana.posicao_conversa == 0)   {                                                                                                                                                                                                                              // 3º = coordenada da posicao Final da locomoção.
                                animacao_balao = 0;
                                interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoPersonagem.face [1],"",                                                                                                                           // 4º = Tempo de Espera
                                                                                                                                                  "",                                                                                                                           // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);
                            } else if (informacaoMariana.posicao_conversa == 1) {
                                efeito_balao_exclamacao(buffer, informacaoPersonagem.x, informacaoPersonagem.y, &animacao_balao, &animacao_balao_delay); 
                                interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoPersonagem.face [1],"Mãe! Eu tive um pesadelo horrível!",
                                                                                                                                                  "", 
                                                                                                                                                  "",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 2, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);    
                            } else if (informacaoMariana.posicao_conversa == 2) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoMariana.face [0],"Nossa meu filho, você está pálido!",
                                                                                                                                                  "Que pesadelo foi esse???", 
                                                                                                                                                  "",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 3, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);    
                            } else if (informacaoMariana.posicao_conversa == 3) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoPersonagem.face [1],"Foi com meu pai e um homem estranho...",
                                                                                                                                                  "Eu não me lembro bem dos detalhes, mas parecia", 
                                                                                                                                                  "ser muiro real!",
                                                                                                                                                  "Ele estava preso em uma espécie de cativeiro...", 
                                                                                                                                                  "E o homem ficava maltratando ele...", datFontes, 4, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);    
                            } else if (informacaoMariana.posicao_conversa == 4) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoMariana.face [0],"Nossa... realmente não é um bom sonho.",
                                                                                                                                                  "Mas agora eu quero que você se acalme.", 
                                                                                                                                                  "Já passou...",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 5, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);    
                            } else if (informacaoMariana.posicao_conversa == 5) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoPersonagem.face [0],"Sim.. mas foi muito real mãe...",
                                                                                                                                                  "Agora eu tenho ainda mais certeza de", 
                                                                                                                                                  "que meu pai está vivo...",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 6, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);    
                            } else if (informacaoMariana.posicao_conversa == 6) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoMariana.face [0],"...",
                                                                                                                                                  "", 
                                                                                                                                                  "",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 7, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);    
                            } else if (informacaoMariana.posicao_conversa == 7) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoMariana.face [0],"Ta bom.. agora vamos parar de",
                                                                                                                                                  "falar sobre isso, ok? Que tal a gente brincar", 
                                                                                                                                                  "de jogo da memória pra distrair um pouco?",
                                                                                                                                                  "Assim eu já aproveito e vejo como sua", 
                                                                                                                                                  "memória está! O que acha?", datFontes, 8, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);    
                            } else if (informacaoMariana.posicao_conversa == 8) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoPersonagem.face [0],"Hmm... Pode ser...",
                                                                                                                                                  "Você sempre me disse que um bom jogador", 
                                                                                                                                                  "de futebol, acima de tudo, tem que ter um",
                                                                                                                                                  "bom raciocíneo para fazer as jogadas...", 
                                                                                                                                                  "Então vamos la!", datFontes, 9, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);    
                            } else if (informacaoMariana.posicao_conversa == 9) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoPersonagem.face [0],"Hmm... Pode ser...",
                                                                                                                                                  "Você sempre me disse que um bom jogador", 
                                                                                                                                                  "de futebol, acima de tudo, tem que ter um",
                                                                                                                                                  "bom raciocíneo para fazer as jogadas...", 
                                                                                                                                                   "Então vamos la!", datFontes, 10, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);    
                                musica = 1;
                                mapa_atual = 11;
                                informacaoMariana.posicao_conversa = 0;
                            }
                        } else if (progresso == 3) { 
                            if (informacaoMariana.posicao_conversa == 0)   {                                                                                                                                                                                                                              // 3º = coordenada da posicao Final da locomoção.
                                animacao_balao = 0;
                                interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoMariana.face [1],"",                                                                                                                           // 4º = Tempo de Espera
                                                                                                                                                  "",                                                                                                                           // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);
                            } else if (informacaoMariana.posicao_conversa == 1) {
                                efeito_balao_exclamacao(buffer, informacaoPersonagem.x, informacaoPersonagem.y, &animacao_balao, &animacao_balao_delay); 
                                interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoMariana.face [1],"João, agora que a gente terminou",
                                                                                                                                                  "de brincar, eu vou ter que arrumar algumas", 
                                                                                                                                                  "coisas aqui em casa filho.",
                                                                                                                                                  "Se você quiser, pode sair um pouco.", 
                                                                                                                                                  "Hoje é domingo, vai la fora se divertir, ", datFontes, 2, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);    
                            } else if (informacaoMariana.posicao_conversa == 2) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoMariana.face [0],"quem sabe você não descobre alguma coisa",
                                                                                                                                                  "legal heim?", 
                                                                                                                                                  "",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 3, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);    
                            } else if (informacaoMariana.posicao_conversa == 3) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoPersonagem.face [0],"Certo mamãe, vou la.",
                                                                                                                                                  "Já pensou se eu descubro algo", 
                                                                                                                                                  "sobre o papai???",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 4, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);    
                            } else if (informacaoMariana.posicao_conversa == 4) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoMariana.face [0],"...",
                                                                                                                                                  "", 
                                                                                                                                                  "",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 5, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);    
                            } else if (informacaoMariana.posicao_conversa == 5) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoMariana.face [1],"Ok, mas não vai se meter em confusão",
                                                                                                                                                  "heim!", 
                                                                                                                                                  "",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 6, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);    
                            } else if (informacaoMariana.posicao_conversa == 6) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoPersonagem.face [0],"Ta bom mamãe!!!",
                                                                                                                                                  "", 
                                                                                                                                                  "",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 0, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);    
                            } 
                        }         
                    }
                               
             
                    if (opcao == 0) {
                        if (key[KEY_ESC]) {                              //Abre Menu                                                                                                                                                                                                                                                                                                                                           
                            opcao = 1;
                            play_sample (audio_efeito [3], 500, 128, 1000, 0);
                        }
                    }
                    
                    
                    if (opcao != 0) {
                        opcao = pausa_menu (buffer, opcao, &animacao_bola, &animacao_bola_delay);        
                    }
                    
                    // Prepara Para Ir No Mapa 1 //
                    if (mapa_atual == 1) {
                        play_sample (audio_efeito [4], 500, 128, 1000, 0);
                        musica = 1;
                              
                        // Localização Inicial do Jogador Mapa Vila
                        informacaoPersonagem.x    =  160;
                        informacaoPersonagem.y    =  165;
                        informacaoPersonagem.lado = 0;
                        
                    } else if (mapa_atual == 7) {
                        play_sample (audio_efeito [4], 500, 128, 1000, 0);
                        musica = 1;
                                                    
                        // Localização Inicial do Jogador Mapa Vila
                        informacaoPersonagem.x    =  160;
                        informacaoPersonagem.y    =  165;
                        informacaoPersonagem.lado = 0;
                    }
                
                    if (informacaoPersonagem.vigor <= 0){
                        mapa_atual = 3;
                        musica = 3;
                    }
                
                    if ((((informacaoBola.delayanimacao <= 0) &&  (opcao == 0) && (informacaoMariana.posicao_conversa == 0) && (informacaoCachorro.posicao_conversa == 0)))) {
                         movimentarJogador (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.lado, &informacaoPersonagem.animacao, &informacaoPersonagem.terreno, &animacao_personagem_delay);
                    }
                    
                    // Desenha na Tela //
                    draw_sprite(screen, buffer, 0, 0);
                    clear (buffer);
                                        
                }  //   -----------------------------------------------------      FIM PROGRESSO 1    ------------------------------------------------------------------- //
                // Destruindo Imagens //
                for (cont_destruir_x = 0; cont_destruir_x != 4; cont_destruir_x++) {
                    for (cont_destruir_y = 0; cont_destruir_y != 4; cont_destruir_y++) {
                        destroy_bitmap (mariana[cont_destruir_x][cont_destruir_y]);
                        destroy_bitmap (cachorro[cont_destruir_x][cont_destruir_y]);
                    }
                }
                
                destroy_bitmap (informacaoMariana.face [0]);
                destroy_bitmap (informacaoMariana.face [1]);                                 
            } //FIM MAPA 2
//  ================================================================================================================================================================================================================= //                      
//  =============================================================================     GINÁSIO       ======================================================================================================================= //
            if (mapa_atual == 4) {
                // Load dos sprites que serão usados neste mapa //             
                // Geovana //
                informacaoGeovana.face[0] = load_bitmap("Imagens/Personagens/Geovana/Faces/face_geovana_0.tga",NULL);
                
                // Treinador Roberto //
                roberto [0][0] = load_bitmap("Imagens/Personagens/Roberto/frente91.bmp",NULL);
                roberto [0][1] = load_bitmap("Imagens/Personagens/Roberto/frente92.bmp",NULL);
                roberto [0][2] = load_bitmap("Imagens/Personagens/Roberto/frente93.bmp",NULL);
                roberto [0][3] = load_bitmap("Imagens/Personagens/Roberto/frente94.bmp",NULL);
    
                roberto [1][0] = load_bitmap("Imagens/Personagens/Roberto/direita91.bmp",NULL);
                roberto [1][1] = load_bitmap("Imagens/Personagens/Roberto/direita92.bmp",NULL);
                roberto [1][2] = load_bitmap("Imagens/Personagens/Roberto/direita93.bmp",NULL);
                roberto [1][3] = load_bitmap("Imagens/Personagens/Roberto/direita94.bmp",NULL);
        
                roberto [2][0] = load_bitmap("Imagens/Personagens/Roberto/costas91.bmp",NULL);
                roberto [2][1] = load_bitmap("Imagens/Personagens/Roberto/costas92.bmp",NULL);
                roberto [2][2] = load_bitmap("Imagens/Personagens/Roberto/costas93.bmp",NULL);
                roberto [2][3] = load_bitmap("Imagens/Personagens/Roberto/costas94.bmp",NULL);
    
                roberto [3][0] = load_bitmap("Imagens/Personagens/Roberto/esquerda91.bmp",NULL);
                roberto [3][1] = load_bitmap("Imagens/Personagens/Roberto/esquerda92.bmp",NULL);
                roberto [3][2] = load_bitmap("Imagens/Personagens/Roberto/esquerda93.bmp",NULL);
                roberto [3][3] = load_bitmap("Imagens/Personagens/Roberto/esquerda94.bmp",NULL);
                informacaoRoberto.face[0] = load_bitmap("Imagens/Personagens/Roberto/Faces/roberto_face_1.tga",NULL);
                
                // NPC 2 //
                npc2 [0][0] = load_bitmap("Imagens/Personagens/Jogadores1/frente101.bmp",NULL);
                npc2 [0][1] = load_bitmap("Imagens/Personagens/Jogadores1/frente102.bmp",NULL);
                npc2 [0][2] = load_bitmap("Imagens/Personagens/Jogadores1/frente103.bmp",NULL);
                npc2 [0][3] = load_bitmap("Imagens/Personagens/Jogadores1/frente104.bmp",NULL);
    
                npc2 [1][0] = load_bitmap("Imagens/Personagens/Jogadores1/direita101.bmp",NULL);
                npc2 [1][1] = load_bitmap("Imagens/Personagens/Jogadores1/direita102.bmp",NULL);
                npc2 [1][2] = load_bitmap("Imagens/Personagens/Jogadores1/direita103.bmp",NULL);
                npc2 [1][3] = load_bitmap("Imagens/Personagens/Jogadores1/direita104.bmp",NULL);
        
                npc2 [2][0] = load_bitmap("Imagens/Personagens/Jogadores1/costas101.bmp",NULL);
                npc2 [2][1] = load_bitmap("Imagens/Personagens/Jogadores1/costas102.bmp",NULL);
                npc2 [2][2] = load_bitmap("Imagens/Personagens/Jogadores1/costas103.bmp",NULL);
                npc2 [2][3] = load_bitmap("Imagens/Personagens/Jogadores1/costas104.bmp",NULL);
    
                npc2 [3][0] = load_bitmap("Imagens/Personagens/Jogadores1/esquerda101.bmp",NULL);
                npc2 [3][1] = load_bitmap("Imagens/Personagens/Jogadores1/esquerda102.bmp",NULL);
                npc2 [3][2] = load_bitmap("Imagens/Personagens/Jogadores1/esquerda103.bmp",NULL);
                npc2 [3][3] = load_bitmap("Imagens/Personagens/Jogadores1/esquerda104.bmp",NULL);
                informacaoNpc2.face [0] = load_bitmap("Imagens/Personagens/Jogadores1/Faces/face_jogador1_0.tga",NULL);                                                           
                
                // NPC 3 //
                npc3 [0][0] = load_bitmap("Imagens/Personagens/Jogadores2/frente111.bmp",NULL);
                npc3 [0][1] = load_bitmap("Imagens/Personagens/Jogadores2/frente112.bmp",NULL);
                npc3 [0][2] = load_bitmap("Imagens/Personagens/Jogadores2/frente113.bmp",NULL);
                npc3 [0][3] = load_bitmap("Imagens/Personagens/Jogadores2/frente114.bmp",NULL);
    
                npc3 [1][0] = load_bitmap("Imagens/Personagens/Jogadores2/direita111.bmp",NULL);
                npc3 [1][1] = load_bitmap("Imagens/Personagens/Jogadores2/direita112.bmp",NULL);
                npc3 [1][2] = load_bitmap("Imagens/Personagens/Jogadores2/direita113.bmp",NULL);
                npc3 [1][3] = load_bitmap("Imagens/Personagens/Jogadores2/direita114.bmp",NULL);
        
                npc3 [2][0] = load_bitmap("Imagens/Personagens/Jogadores2/costas111.bmp",NULL);
                npc3 [2][1] = load_bitmap("Imagens/Personagens/Jogadores2/costas112.bmp",NULL);
                npc3 [2][2] = load_bitmap("Imagens/Personagens/Jogadores2/costas113.bmp",NULL);
                npc3 [2][3] = load_bitmap("Imagens/Personagens/Jogadores2/costas114.bmp",NULL);
    
                npc3 [3][0] = load_bitmap("Imagens/Personagens/Jogadores2/esquerda111.bmp",NULL);
                npc3 [3][1] = load_bitmap("Imagens/Personagens/Jogadores2/esquerda112.bmp",NULL);
                npc3 [3][2] = load_bitmap("Imagens/Personagens/Jogadores2/esquerda113.bmp",NULL);
                npc3 [3][3] = load_bitmap("Imagens/Personagens/Jogadores2/esquerda114.bmp",NULL);
                informacaoNpc3.face [0] = load_bitmap("Imagens/Personagens/Jogadores2/Faces/face_jogador2_0.tga",NULL);                                                           
                
                // Vespa //
                vespa [0][0] = load_bitmap("Imagens/Personagens/Vespa/frente61.bmp",NULL);
                vespa [0][1] = load_bitmap("Imagens/Personagens/Vespa/frente62.bmp",NULL);
                vespa [0][2] = load_bitmap("Imagens/Personagens/Vespa/frente63.bmp",NULL);
                vespa [0][3] = load_bitmap("Imagens/Personagens/Vespa/frente64.bmp",NULL);
    
                vespa [1][0] = load_bitmap("Imagens/Personagens/Vespa/direita61.bmp",NULL);
                vespa [1][1] = load_bitmap("Imagens/Personagens/Vespa/direita62.bmp",NULL);
                vespa [1][2] = load_bitmap("Imagens/Personagens/Vespa/direita63.bmp",NULL);
                vespa [1][3] = load_bitmap("Imagens/Personagens/Vespa/direita64.bmp",NULL);
        
                vespa [2][0] = load_bitmap("Imagens/Personagens/Vespa/costas61.bmp",NULL);
                vespa [2][1] = load_bitmap("Imagens/Personagens/Vespa/costas62.bmp",NULL);
                vespa [2][2] = load_bitmap("Imagens/Personagens/Vespa/costas63.bmp",NULL);
                vespa [2][3] = load_bitmap("Imagens/Personagens/Vespa/costas64.bmp",NULL);
    
                vespa [3][0] = load_bitmap("Imagens/Personagens/Vespa/esquerda61.bmp",NULL);
                vespa [3][1] = load_bitmap("Imagens/Personagens/Vespa/esquerda62.bmp",NULL);
                vespa [3][2] = load_bitmap("Imagens/Personagens/Vespa/esquerda63.bmp",NULL);
                vespa [3][3] = load_bitmap("Imagens/Personagens/Vespa/esquerda64.bmp",NULL);

                if (cena_animada == 1) {
                    // Load nos Sprites que serão usadas apenas nas cenas animadas //
                    // Alexandre //
                    alexandre [0][0] = load_bitmap("Imagens/Personagens/Alexandre/frente81.bmp",NULL);
                    alexandre [0][1] = load_bitmap("Imagens/Personagens/Alexandre/frente82.bmp",NULL);
                    alexandre [0][2] = load_bitmap("Imagens/Personagens/Alexandre/frente83.bmp",NULL);
                    alexandre [0][3] = load_bitmap("Imagens/Personagens/Alexandre/frente84.bmp",NULL);
    
                    alexandre [1][0] = load_bitmap("Imagens/Personagens/Alexandre/direita81.bmp",NULL);
                    alexandre [1][1] = load_bitmap("Imagens/Personagens/Alexandre/direita82.bmp",NULL);
                    alexandre [1][2] = load_bitmap("Imagens/Personagens/Alexandre/direita83.bmp",NULL);
                    alexandre [1][3] = load_bitmap("Imagens/Personagens/Alexandre/direita84.bmp",NULL);
        
                    alexandre [2][0] = load_bitmap("Imagens/Personagens/Alexandre/costas81.bmp",NULL);
                    alexandre [2][1] = load_bitmap("Imagens/Personagens/Alexandre/costas82.bmp",NULL);
                    alexandre [2][2] = load_bitmap("Imagens/Personagens/Alexandre/costas83.bmp",NULL);
                    alexandre [2][3] = load_bitmap("Imagens/Personagens/Alexandre/costas84.bmp",NULL);
    
                    alexandre [3][0] = load_bitmap("Imagens/Personagens/Alexandre/esquerda81.bmp",NULL);
                    alexandre [3][1] = load_bitmap("Imagens/Personagens/Alexandre/esquerda82.bmp",NULL);
                    alexandre [3][2] = load_bitmap("Imagens/Personagens/Alexandre/esquerda83.bmp",NULL);
                    alexandre [3][3] = load_bitmap("Imagens/Personagens/Alexandre/esquerda84.bmp",NULL);
                    informacaoAlexandre.face [0] = load_bitmap("Imagens/Personagens/Alexandre/Faces/face_alexandre_2.tga",NULL); 
                                  
                     if (cena_animada_informacoes_iniciais == 1){    
                         informacaoPersonagem.x             =  380;
                         informacaoPersonagem.y             =  570;
                         informacaoPersonagem.lado          =  2;
                         informacaoPersonagem.delayanimacao =  0;
                         
                         informacaoAlexandre.x              =  550; 
                         informacaoAlexandre.y              =  460;
                         informacaoAlexandre.lado           =  1;
                         informacaoAlexandre.delayanimacao  =  0;
                         informacaoAlexandre.terreno        =  TERRENO_ARENOSO;
                         
                         informacaoRoberto.x                =  650;
                         informacaoRoberto.y                =  460;
                         informacaoRoberto.lado             =  3;
                         
                         informacaoNpc2.x                   = 200;
                         informacaoNpc2.y                   = 460;
                         informacaoNpc2.lado                = 1;
                         
                         informacaoNpc3.x                   = 250;
                         informacaoNpc3.y                   = 460;
                         informacaoNpc3.lado                = 3;
                         
                         informacaoVespa1.x                 = 200;
                         informacaoVespa1.y                 = 200;
                         informacaoVespa1.lado              = 1;
                         
                         informacaoVespa2.x                 = 500;
                         informacaoVespa2.y                 = 350;
                         informacaoVespa2.lado              = 2;

                         
                         fadeout (8);      
                         clear (buffer);
                         cenario = load_jpg("Imagens/EstilosCenarios/cenario_ginasio.jpg",NULL);
                        
                         draw_sprite(buffer, cenario, 0,  0);  
                         draw_sprite(buffer, alexandre [informacaoAlexandre.lado][informacaoAlexandre.animacao], informacaoAlexandre.x, informacaoAlexandre.y);
                         draw_sprite(buffer, roberto [informacaoRoberto.lado][informacaoRoberto.animacao], informacaoRoberto.x, informacaoRoberto.y);
                         draw_sprite(buffer, vespa [informacaoVespa1.lado][informacaoVespa1.animacao], informacaoVespa1.x, informacaoVespa1.y);
                         draw_sprite(buffer, vespa [informacaoVespa2.lado][informacaoVespa2.animacao], informacaoVespa2.x, informacaoVespa2.y);
                         draw_sprite(buffer, personagem [informacaoPersonagem.lado][informacaoPersonagem.animacao], informacaoPersonagem.x, informacaoPersonagem.y);
                         draw_sprite(buffer, npc2 [informacaoNpc2.lado][informacaoNpc2.animacao], informacaoNpc2.x, informacaoNpc2.y);
                         draw_sprite(buffer, npc3 [informacaoNpc3.lado][informacaoNpc3.animacao], informacaoNpc3.x, informacaoNpc3.y);
                   
                         efeito_torcedora(buffer, 240, 50, &animacao_torcedora [0], &animacao_torcedora_delay [0]);
                         efeito_geovana(buffer, 374, 80, &animacao_torcedora [1], &animacao_torcedora_delay [1]);
                         efeito_jogadores_direita_ginasio (buffer, 720, 120, &jogadores_direita_ginasio, &jogadores_direita_ginasio_delay);
                         efeito_jogadores_esquerda_ginasio (buffer, 45, 120, &jogadores_esquerda_ginasio, &jogadores_esquerda_ginasio_delay);
                         efeito_pilar_de_fogo_azul (buffer, 50, 60, &animacao_fogo [0], &animacao_fogo_delay [0]);
                         efeito_pilar_de_fogo_amarelo (buffer, 50, 455, &animacao_fogo [1], &animacao_fogo_delay [1]);
                         efeito_pilar_de_fogo_amarelo (buffer, 725, 60, &animacao_fogo [2], &animacao_fogo_delay [2]);
                         efeito_pilar_de_fogo_azul (buffer, 725, 455, &animacao_fogo [3], &animacao_fogo_delay [3]);
                         
                         // Efeitos de Fadein utilizando as primitivas desenhadas no buffer anteriormente //
                         fadein (buffer, 8);
                         cena_animada_informacoes_iniciais = 2;
                         audio_fundo = load_midi("Audios/Fundo/musica_inimigo.mid");            // Load na musica do mapa 1.
                         play_midi(audio_fundo, 1);                                             // Fadeout do cenário anterior, quanto menor o valor mais rápido é 
                    }
                    // Efeitos do Cenário //                 
                    draw_sprite(buffer, cenario, 0,  0);  
                    efeito_torcedora(buffer, 240, 50, &animacao_torcedora [0], &animacao_torcedora_delay [0]);
                    efeito_geovana(buffer, 374, 80, &animacao_torcedora [1], &animacao_torcedora_delay [1]);
                    efeito_jogadores_direita_ginasio (buffer, 720, 120, &jogadores_direita_ginasio, &jogadores_direita_ginasio_delay);
                    efeito_jogadores_esquerda_ginasio (buffer, 45, 120, &jogadores_esquerda_ginasio, &jogadores_esquerda_ginasio_delay);
                    efeito_pilar_de_fogo_azul (buffer, 50, 60, &animacao_fogo [0], &animacao_fogo_delay [0]);
                    efeito_pilar_de_fogo_amarelo (buffer, 50, 455, &animacao_fogo [1], &animacao_fogo_delay [1]);
                    efeito_pilar_de_fogo_amarelo (buffer, 725, 60, &animacao_fogo [2], &animacao_fogo_delay [2]);
                    efeito_pilar_de_fogo_azul (buffer, 725, 455, &animacao_fogo [3], &animacao_fogo_delay [3]);
                    draw_sprite(buffer, alexandre [informacaoAlexandre.lado][informacaoAlexandre.animacao], informacaoAlexandre.x, informacaoAlexandre.y);
                    draw_sprite(buffer, roberto [informacaoRoberto.lado][informacaoRoberto.animacao], informacaoRoberto.x, informacaoRoberto.y); 
                    draw_sprite(buffer, vespa [informacaoVespa1.lado][informacaoVespa1.animacao], informacaoVespa1.x, informacaoVespa1.y);
                    draw_sprite(buffer, vespa [informacaoVespa2.lado][informacaoVespa2.animacao], informacaoVespa2.x, informacaoVespa2.y);
                    draw_sprite(buffer, personagem [informacaoPersonagem.lado][informacaoPersonagem.animacao], informacaoPersonagem.x, informacaoPersonagem.y);
                    draw_sprite(buffer, npc2 [informacaoNpc2.lado][informacaoNpc2.animacao], informacaoNpc2.x, informacaoNpc2.y);
                    draw_sprite(buffer, npc3 [informacaoNpc3.lado][informacaoNpc3.animacao], informacaoNpc3.x, informacaoNpc3.y);
                    movimentarSpriteAutomaticamente(&informacaoVespa1.x, &informacaoVespa1.y, &informacaoVespa1.lado, &informacaoVespa1.animacao, &informacaoVespa1.delayanimacao, informacaoVespa1.terreno, 2, 450, 550, 0, &animacao_npc_delay, informacaoVespa1.velocidade_animacao);    // Parametros Numéricos//                                                                                                                                                                                                           // 7º Parametro responsável pelo sentido "1" para Vertical ou "2" para Horizontal    
                    movimentarSpriteAutomaticamente(&informacaoVespa2.x, &informacaoVespa2.y, &informacaoVespa2.lado, &informacaoVespa2.animacao, &informacaoVespa2.delayanimacao, informacaoVespa2.terreno, 2, 200, 300, 0, &animacao_npc_delay, informacaoVespa2.velocidade_animacao);    // Parametros Numéricos//                                                                                                                                                                                                           // 7º Parametro responsável pelo sentido "1" para Vertical ou "2" para Horizontal    
                    
                    
                    if (animacao_local == 0) {
                        movimentarSpriteAutomaticamente(&informacaoAlexandre.x, &informacaoAlexandre.y, &informacaoAlexandre.lado, &informacaoAlexandre.animacao, &informacaoAlexandre.delayanimacao, informacaoAlexandre.terreno, 2, 450, 550, 0, &animacao_personagem_delay, informacaoNpc1.velocidade_animacao);    // Parametros Numéricos//                                                                                                                                                                                                           // 7º Parametro responsável pelo sentido "1" para Vertical ou "2" para Horizontal
                        movimentarSpriteAutomaticamente(&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.lado, &informacaoPersonagem.animacao, &informacaoPersonagem.delayanimacao, informacaoNpc1.terreno, 1, 500, 570, 0, &animacao_personagem_delay, informacaoNpc1.velocidade_animacao);    // Parametros Numéricos//                                                                                                                                                                                                           // 7º Parametro responsável pelo sentido "1" para Vertical ou "2" para Horizontal
                        if (informacaoPersonagem.y <= 500) {
                            animacao_local = 1;
                            informacaoAlexandre.lado = 1;
                            informacaoAlexandre.animacao = 0;
                        }
                    }
                    
                    if (animacao_local == 1) {
                        informacaoPersonagem.animacao = 0;
                        if (informacaoAlexandre.posicao_conversa == 0)   {                                                                                                                                                                                                                              // 3º = coordenada da posicao Final da locomoção.
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoNpc1.lado, fala_personagem [1], buffer, informacaoPersonagem.face [1],"",                                                                                                      // 4º = Tempo de Espera
                                                                                                                                                  "",                                                                                                                               // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoAlexandre.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                        } else if (informacaoAlexandre.posicao_conversa == 1) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoNpc1.lado, fala_personagem [1], buffer, informacaoAlexandre.face [0],"Quer saber? Eu não preciso de ninguém",
                                                                                                                                                  "falando o que eu devo ou não fazer. Prefiro treinar", 
                                                                                                                                                  "sozinho, do que treinar com um bando de perdedores",
                                                                                                                                                  "igual a vocês! Um dia ainda irão me venerar", 
                                                                                                                                                  "mais do que veneravam aquele tal de Ligeirinho.", datFontes, 2, &informacaoAlexandre.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);    
                        } else if (informacaoAlexandre.posicao_conversa == 2) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoNpc1.lado, fala_personagem [1], buffer, informacaoAlexandre.face [0],"Quer saber? Eu não preciso de ninguém",
                                                                                                                                                  "falando o que eu devo ou não fazer. Prefiro treinar", 
                                                                                                                                                  "sozinho, do que treinar com um bando de perdedores",
                                                                                                                                                  "igual a vocês! Um dia ainda irão me venerar", 
                                                                                                                                                  "mais do que veneravam aquele tal de Ligeirinho.", datFontes, 3, &informacaoAlexandre.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);    
                            animacao_local = 2;
                            informacaoAlexandre.posicao_conversa = 0;
                            animacao_balao = 0;
                        }
                    }
                    
                    if (animacao_local == 2) {
                        informacaoPersonagem.lado = 1;
                        movimentarSpriteAutomaticamente(&informacaoAlexandre.x, &informacaoAlexandre.y, &informacaoAlexandre.lado, &informacaoAlexandre.animacao, &informacaoAlexandre.delayanimacao, informacaoAlexandre.terreno, 2, 380, informacaoAlexandre.x, 0, &animacao_personagem_delay, informacaoNpc1.velocidade_animacao);    // Parametros Numéricos//                                                                                                                                                                                                           // 7º Parametro responsável pelo sentido "1" para Vertical ou "2" para Horizontal
                        
                        if (informacaoAlexandre.x <= 420){
                            efeito_balao_reticencias(buffer, informacaoPersonagem.x, informacaoPersonagem.y, &animacao_balao, &animacao_balao_delay);
                            informacaoNpc3.lado = 1;
                        }
                        
                        if (informacaoAlexandre.x <= 400) {
                            informacaoPersonagem.lado = 2;
                        }
                                                  
                        if (informacaoAlexandre.x <= 380) {
    
                            animacao_local = 3;
                            informacaoAlexandre.lado = 0;
                            informacaoAlexandre.animacao = 0;
                        }
                     } 
                     
                     if (animacao_local == 3) {
                            if (informacaoAlexandre.posicao_conversa == 0)   {                                                                                                                                                                                                                              // 3º = coordenada da posicao Final da locomoção.
                                interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoNpc1.lado, fala_personagem [1], buffer, informacaoPersonagem.face [1],"",                                                                                                      // 4º = Tempo de Espera
                                                                                                                                                  "",                                                                                                                               // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoAlexandre.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                            } else if (informacaoAlexandre.posicao_conversa == 1) {
                                interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoNpc1.lado, fala_personagem [1], buffer, informacaoAlexandre.face [0],"Nossa quanto mais eu rezo, mais assombração",
                                                                                                                                                  "aparece! Olha só se não é o Babaca Junior...", 
                                                                                                                                                  "veio para o primeiro treino bebê?",
                                                                                                                                                  "Aposto que vocês irão formar um belo time,", 
                                                                                                                                                  "afinal, é um pior que o outro não é? Hahaha!", datFontes, 2, &informacaoAlexandre.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);    
                            } else if (informacaoAlexandre.posicao_conversa == 2) {
                                interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoNpc1.lado, fala_personagem [1], buffer, informacaoPersonagem.face [1],"Alexandre, eu realmente sinto pena",
                                                                                                                                                  "de você... Mas acho melhor a gente parar de", 
                                                                                                                                                  "ficar discutindo e deixar pra resolver",
                                                                                                                                                  "nossas diferenças na hora do jogo. Agora", 
                                                                                                                                                  "se você me der licença, vou ir para o treino.", datFontes, 3, &informacaoAlexandre.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);    

                            } else if (informacaoAlexandre.posicao_conversa == 3) {
                                interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoNpc1.lado, fala_personagem [1], buffer, informacaoAlexandre.face [0],"Errr, que seja... No campo",
                                                                                                                                                  "você não terá a menor chance mesmo...", 
                                                                                                                                                  "Aproveita para aparecer durantes esses",
                                                                                                                                                  "treininhos, porque na hora do jogo pra valer,", 
                                                                                                                                                  "você não vai ser ninguém perto de mim em campo.", datFontes, 4, &informacaoAlexandre.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);    

                            } else if (informacaoAlexandre.posicao_conversa == 4) {
                                interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoNpc1.lado, fala_personagem [1], buffer, informacaoAlexandre.face [0],"Errr, que seja... No campo",
                                                                                                                                                  "você não terá a menor chance mesmo...", 
                                                                                                                                                  "Aproveita para aparecer durantes esses",
                                                                                                                                                  "treininhos, porque na hora do jogo pra valer,", 
                                                                                                                                                  "você não vai ser ninguém perto de mim em campo.", datFontes, 5, &informacaoAlexandre.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);    
                            animacao_local = 4;
                            informacaoAlexandre.posicao_conversa = 0;                                                                                                                      
                            }
                       }
                       
                       if (animacao_local == 4) {
                           movimentarSpriteAutomaticamente(&informacaoAlexandre.x, &informacaoAlexandre.y, &informacaoAlexandre.lado, &informacaoAlexandre.animacao, &informacaoAlexandre.delayanimacao, informacaoAlexandre.terreno, 1, 460, 550, 0, &animacao_personagem_delay, informacaoNpc1.velocidade_animacao);    // Parametros Numéricos//                                                                                                                                                                                                           // 7º Parametro responsável pelo sentido "1" para Vertical ou "2" para Horizontal
                           movimentarSpriteAutomaticamente(&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.lado, &informacaoPersonagem.animacao, &informacaoPersonagem.delayanimacao, informacaoNpc1.terreno, 2, 380, 410, 0, &animacao_personagem_delay, informacaoNpc1.velocidade_animacao);    // Parametros Numéricos//                                                                                                                                                                                                           // 7º Parametro responsável pelo sentido "1" para Vertical ou "2" para Horizontal
                           if (informacaoPersonagem.x >= 410) {
                               animacao_local = 5;
                               animacao_balao = 0;
                           }
                       }
                       
                       if (animacao_local == 5) {
                           movimentarSpriteAutomaticamente(&informacaoAlexandre.x, &informacaoAlexandre.y, &informacaoAlexandre.lado, &informacaoAlexandre.animacao, &informacaoAlexandre.delayanimacao, informacaoAlexandre.terreno, 1, informacaoAlexandre.y, 620, 0, &animacao_personagem_delay, informacaoNpc1.velocidade_animacao);    // Parametros Numéricos//                                                                                                                                                                                                           // 7º Parametro responsável pelo sentido "1" para Vertical ou "2" para Horizontal
                           movimentarSpriteAutomaticamente(&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.lado, &informacaoPersonagem.animacao, &informacaoPersonagem.delayanimacao, informacaoNpc1.terreno, 1, 460, informacaoPersonagem.y, 0, &animacao_personagem_delay, informacaoNpc1.velocidade_animacao);    // Parametros Numéricos//                                                                                                                                                                                                           // 7º Parametro responsável pelo sentido "1" para Vertical ou "2" para Horizontal
                           efeito_balao_gota (buffer, informacaoPersonagem.x, informacaoPersonagem.y, &animacao_balao, &animacao_balao_delay);
                           if (informacaoAlexandre.y >= 620) {
                               animacao_local = 6;
                               informacaoPersonagem.lado = 1;
                               informacaoPersonagem.terreno = TERRENO_NORMAL;
                               cena_animada = 2;
                               informacaoNpc3.lado = 3;
                           }
                       }
                    destroy_bitmap (informacaoAlexandre.face [0]);  
                    for (cont_destruir_x = 0; cont_destruir_x != 4; cont_destruir_x++) {
                        for (cont_destruir_y = 0; cont_destruir_y != 4; cont_destruir_y++) {
                            destroy_bitmap (alexandre[cont_destruir_x][cont_destruir_y]);
                        }
                    }
                } else if (cena_animada == 2)  {  // FIM CENA ANIMADA 1 //                    
                    if (musica == 1) {                     
                         fadeout (8);      
                         clear (buffer);
                         cenario = load_jpg("Imagens/EstilosCenarios/cenario_ginasio.jpg",NULL);
                         
                         informacaoNpc2.x                   = 200;
                         informacaoNpc2.y                   = 460;
                         informacaoNpc2.lado                = 1;
                         
                         informacaoNpc3.x                   = 250;
                         informacaoNpc3.y                   = 460;
                         informacaoNpc3.lado                = 3;
                         
                         informacaoNpc1.fala                = 0;
                         
                         draw_sprite(buffer, cenario, 0,  0);  
                         draw_sprite(buffer, personagem [informacaoPersonagem.lado][informacaoPersonagem.animacao], informacaoPersonagem.x, informacaoPersonagem.y);
                         draw_sprite(buffer, roberto [informacaoRoberto.lado][informacaoRoberto.animacao], informacaoRoberto.x, informacaoRoberto.y);
                         draw_sprite(buffer, npc2 [informacaoNpc2.lado][informacaoNpc2.animacao], informacaoNpc2.x, informacaoNpc2.y);
                         draw_sprite(buffer, npc3 [informacaoNpc3.lado][informacaoNpc3.animacao], informacaoNpc3.x, informacaoNpc3.y);
                         draw_sprite(buffer, vespa [informacaoVespa1.lado][informacaoVespa1.animacao], informacaoVespa1.x, informacaoVespa1.y);
                         draw_sprite(buffer, vespa [informacaoVespa2.lado][informacaoVespa2.animacao], informacaoVespa2.x, informacaoVespa2.y);
                    
                         efeito_torcedora(buffer, 240, 50, &animacao_torcedora [0], &animacao_torcedora_delay [0]);
                         efeito_geovana(buffer, 374, 80, &animacao_torcedora [1], &animacao_torcedora_delay [1]);
                         efeito_jogadores_direita_ginasio (buffer, 720, 120, &jogadores_direita_ginasio, &jogadores_direita_ginasio_delay);
                         efeito_jogadores_esquerda_ginasio (buffer, 45, 120, &jogadores_esquerda_ginasio, &jogadores_esquerda_ginasio_delay);
                         efeito_pilar_de_fogo_azul (buffer, 50, 60, &animacao_fogo [0], &animacao_fogo_delay [0]);
                         efeito_pilar_de_fogo_amarelo (buffer, 50, 455, &animacao_fogo [1], &animacao_fogo_delay [1]);
                         efeito_pilar_de_fogo_amarelo (buffer, 725, 60, &animacao_fogo [2], &animacao_fogo_delay [2]);
                         efeito_pilar_de_fogo_azul (buffer, 725, 455, &animacao_fogo [3], &animacao_fogo_delay [3]);
                         
                         // Desenha Barra de Status //
                         efeito_barra_de_status_personagem (buffer, informacaoPersonagem.vigor, informacaoPersonagem.energia, &animacao_status, &animacao_status_delay, informacaoPersonagem.moedas, datFontes, informacaoPersonagem.experiencia_atual_porcentagem, informacaoPersonagem.nivel);                  
                         
                         // Desenhos as habilidades da barra de habilidades //
                         if (informacaoPersonagem.habilidade1 == 1) efeito_habilidade_1_ativa (buffer, 5 + 2, 120 + 2, &animacao_habilidade1, &animacao_habilidade1_delay);
                    
                         // Efeitos de Fadein utilizando as primitivas desenhadas no buffer anteriormente //
                         fadein (buffer, 8);
                         cena_animada_informacoes_iniciais = 2;
                         audio_fundo = load_midi("Audios/Fundo/musica_ginasio.mid");            // Load na musica do mapa 1.
                         play_midi(audio_fundo, 1);
                         musica = 2;
                         
                         informacaoRoberto.x                =  650;
                         informacaoRoberto.y                =  460;
                         
                         informacaoRoberto.colisao_para_conversar = 0;
                         informacaoNpc2.colisao_para_conversar    = 0;
                         informacaoNpc3.colisao_para_conversar    = 0;
                         
                         informacaoVespa1.vigor                   = 1;
                         informacaoVespa2.vigor                   = 1;
                         
                         informacaoVespa1.obter_experiencia       = 0;
                         informacaoVespa2.obter_experiencia       = 0;
                         
                         informacaoVespa1.loot                    = 1;
                         informacaoVespa2.loot                    = 1;
                    }
                    // Atualiza Nivel do Personagem Caso Evolua //
                    if (informacaoPersonagem.experiencia_atual >= informacaoPersonagem.experiencia_proximo_nivel) {
                        if (informacaoPersonagem.nivel != 99) {
                            informacaoPersonagem.nivel                     = informacaoPersonagem.nivel + 1;
                            informacaoPersonagem.experiencia_atual         = informacaoPersonagem.experiencia_atual - informacaoPersonagem.experiencia_proximo_nivel; 
                            informacaoPersonagem.experiencia_proximo_nivel = informacaoPersonagem.experiencia_proximo_nivel * informacaoPersonagem.nivel;
                            informacaoPersonagem.vigor                     = 6;
                            animacao_subiu_nivel                           = 0;
                        }    
                    }
                    
                    // Atualiza Porcentagem de Experiência do Personagem //
                    informacaoPersonagem.experiencia_atual_porcentagem = (informacaoPersonagem.experiencia_atual * 100) / informacaoPersonagem.experiencia_proximo_nivel;

                   // Atualiza Largura e Altura do Personagem Principal //
                    informacaoPersonagem.largura = informacaoPersonagem.x + SPRITE_LARGURA;
                    informacaoPersonagem.altura  = informacaoPersonagem.y + SPRITE_ALTURA;
                    
                    // Atualiza Largura e Altura do Roberto //
                    informacaoRoberto.largura = informacaoRoberto.x + SPRITE_NPC_LARGURA;
                    informacaoRoberto.altura  = informacaoRoberto.y + SPRITE_NPC_ALTURA;
                    
                    // Atualiza Largura e Altura do Npc2 //
                    informacaoNpc2.largura = informacaoNpc2.x + SPRITE_NPC_LARGURA;
                    informacaoNpc2.altura  = informacaoNpc2.y + SPRITE_NPC_ALTURA;
                    
                    // Atualiza Largura e Altura do Npc3 //
                    informacaoNpc3.largura = informacaoNpc3.x + SPRITE_NPC_LARGURA;
                    informacaoNpc3.altura  = informacaoNpc3.y + SPRITE_NPC_ALTURA;
                    
                    // Atualiza Largura e Altura da Vespa 1 //
                    informacaoVespa1.largura = informacaoVespa1.x + SPRITE_NPC_LARGURA;
                    informacaoVespa1.altura  = informacaoVespa1.y + SPRITE_NPC_ALTURA;
                    
                    // Atualiza Largura e Altura da Vespa 2 //
                    informacaoVespa2.largura = informacaoVespa2.x + SPRITE_NPC_LARGURA;
                    informacaoVespa2.altura  = informacaoVespa2.y + SPRITE_NPC_ALTURA;
                
                    // Atualiza Informação sobre Ataque do Personagem //
                    informacaoBola.x = informacaoPersonagem.x + 10;
                    informacaoBola.y = informacaoPersonagem.y + 25; 
                    
                    
                    // Testes de Colisões Mapa Vila//            
                    // Toda Parte Cima //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 0, 0, 800, 30, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                
                    // Toda Parte Esquerda //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 15, 0, 65, 600, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                
                    // Toda Parte Baixa Esquerda //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 25, 514, 345, 600, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);

                    // Toda Parte Baixo Direita //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 455, 514, 800, 600, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    
                    // Colisão Para Não Deixar Sair do Mapa //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 345, 600, 455, 600, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                 
                    // Parte Direita do Ginásio //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 735, 0, 800, 600, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    
                    // Com Gol da Esquerda //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 60, 230, 90, 330, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    
                    // Com Gol da Direita //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 710, 230, 800, 330, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    
                    // Com as mulheres Parte de Cima da Quadra //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 255, 0, 530, 60, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                
                    // Com a Geovana //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 390, 0, 395, 90, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    
                    // Para Sair do Ginásio //
                    if (progresso == 1) {
                        detectarColisaoEntrarSair(&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 345, 590, 455, 600, &mapa_atual, 7); //Ultimos dois parametros referem-se ao mapa atual e o mapa destino respectivamente.
                    }
                    
                    // Com Inimigos //
                    if (informacaoVespa1.vigor > 0) {
                        caso_colisao_nociva = detectarColisaoNociva(&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, informacaoPersonagem.lado, (informacaoVespa1.x + 12), (informacaoVespa1.y + 5), (informacaoVespa1.largura - 10), (informacaoVespa1.altura - 10), informacaoPersonagem.terreno, &informacaoPersonagem.animacao, &informacaoPersonagem.vigor); 
                    }
                    if (informacaoVespa2.vigor > 0) {
                        caso_colisao_nociva = detectarColisaoNociva(&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, informacaoPersonagem.lado, (informacaoVespa2.x + 12), (informacaoVespa2.y + 5), (informacaoVespa2.largura - 10), (informacaoVespa2.altura - 10), informacaoPersonagem.terreno, &informacaoPersonagem.animacao, &informacaoPersonagem.vigor); 
                    }
                    
                    // Colisao para Falar  com NPC //
                    informacaoRoberto.colisao_para_conversar = detectarColisaoSprite (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, (informacaoRoberto.x + 1) , (informacaoRoberto.y + 35), informacaoRoberto.largura + 5, informacaoRoberto.altura + 5, informacaoPersonagem.terreno, &informacaoRoberto.animacao);
                    informacaoNpc2.colisao_para_conversar    = detectarColisaoSprite (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, (informacaoNpc2.x + 1) , (informacaoNpc2.y + 35), informacaoNpc2.largura + 5, informacaoNpc2.altura + 5, informacaoPersonagem.terreno, &informacaoNpc2.animacao);
                    informacaoNpc3.colisao_para_conversar    = detectarColisaoSprite (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, (informacaoNpc3.x + 1) , (informacaoNpc3.y + 35), informacaoNpc3.largura + 5, informacaoNpc3.altura + 5, informacaoPersonagem.terreno, &informacaoNpc3.animacao);
                    
                    // Colisão de Falas com Animações dos Jogadores e da Torcida Feminina //
                    informacaoNpc1.colisao_para_conversar     = detectarColisaoSprite (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 50 , 160, 70, 420, informacaoPersonagem.terreno, &informacaoNpc1.animacao);
                    informacaoMariana.colisao_para_conversar  = detectarColisaoSprite (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 730, 160, 800, 420, informacaoPersonagem.terreno, &informacaoMariana.animacao);
                    informacaoGeovana.colisao_para_conversar  = detectarColisaoSprite (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 385, 0, 400, 95, informacaoPersonagem.terreno, &informacaoMariana.animacao); 
                    informacaoCachorro.colisao_para_conversar = detectarColisaoSprite (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 250, 0, 535 , 65, informacaoPersonagem.terreno, &informacaoMariana.animacao);
                    
                    // Colisão Com NPCs //
                    caso_colisao  = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, (informacaoRoberto.x + 6) , (informacaoRoberto.y + 40), informacaoRoberto.largura, informacaoRoberto.altura, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao  = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, (informacaoNpc2.x + 6) , (informacaoNpc2.y + 40), informacaoNpc2.largura, informacaoNpc2.altura, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao  = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, (informacaoNpc3.x + 6) , (informacaoNpc3.y + 40), informacaoNpc3.largura, informacaoNpc3.altura, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    
                    // Desenhos do Mapa //
                    draw_sprite(buffer, cenario, 0,  0);  
                    efeito_torcedora(buffer, 240, 50, &animacao_torcedora [0], &animacao_torcedora_delay [0]);
                    efeito_geovana(buffer, 374, 80, &animacao_torcedora [1], &animacao_torcedora_delay [1]);
                    efeito_jogadores_direita_ginasio (buffer, 720, 120, &jogadores_direita_ginasio, &jogadores_direita_ginasio_delay);
                    efeito_jogadores_esquerda_ginasio (buffer, 45, 120, &jogadores_esquerda_ginasio, &jogadores_esquerda_ginasio_delay);
                    efeito_pilar_de_fogo_azul (buffer, 50, 60, &animacao_fogo [0], &animacao_fogo_delay [0]);
                    efeito_pilar_de_fogo_amarelo (buffer, 50, 455, &animacao_fogo [1], &animacao_fogo_delay [1]);
                    efeito_pilar_de_fogo_amarelo (buffer, 725, 60, &animacao_fogo [2], &animacao_fogo_delay [2]);
                    efeito_pilar_de_fogo_azul (buffer, 725, 455, &animacao_fogo [3], &animacao_fogo_delay [3]);
                    
                    if (informacaoPersonagem.habilidade1 == 1){ // Ataque da Bola  desenhada Atras do Sprite //
                        if (informacaoPersonagem.lado == 2) {
                            if (informacaoBola.delayanimacao <= 0) {
                                efeito_ataque (buffer, &informacaoBola.x, &informacaoBola.y, &informacaoBola.delayanimacao, &informacaoPersonagem.energia, informacaoPersonagem.lado, &informacaoPersonagem.animacao, informacaoPersonagem.ataque1, &animacao_efeito_ataque, &animacao_efeito_ataque_2);
                                informacaoPersonagem.energia = informacaoPersonagem.energia + 1;
                            } else if (informacaoBola.delayanimacao > 0) {
                                efeito_ataque (buffer, &informacaoBola.x, &informacaoBola.y, &informacaoBola.delayanimacao, &informacaoPersonagem.energia, informacaoPersonagem.lado, &informacaoPersonagem.animacao, informacaoPersonagem.ataque1, &animacao_efeito_ataque, &animacao_efeito_ataque_2);
                            }
                            if (informacaoPersonagem.energia  > 3) {
                                informacaoPersonagem.energia = 3;
                            }
                        }
                    }
                    
                    // Animacao Caso Suba de Nível //
                    if (animacao_subiu_nivel <= 20) {
                        efeito_subiu_nivel (buffer, informacaoPersonagem.x, informacaoPersonagem.y, &animacao_subiu_nivel, &animacao_subiu_nivel_delay); 
                    }               
                    
                    // Desenha personagem entre o efeito de ataque com a bola  //
                    if (informacaoVespa1.vigor > 0) {
                        draw_sprite(buffer, vespa [informacaoVespa1.lado][informacaoVespa1.animacao], informacaoVespa1.x, informacaoVespa1.y);
                    }
                    
                    if (informacaoVespa2.vigor > 0) {
                        draw_sprite(buffer, vespa [informacaoVespa2.lado][informacaoVespa2.animacao], informacaoVespa2.x, informacaoVespa2.y);
                    }
                    
                    // Movimento Inimigos //
                    // Vespa 1 //
                    if (informacaoVespa1.vigor > 0) {
                         movimentarSpriteAutomaticamente(&informacaoVespa1.x, &informacaoVespa1.y, &informacaoVespa1.lado, &informacaoVespa1.animacao, &informacaoVespa1.delayanimacao, informacaoVespa1.terreno, 2, 120, 200, 0, &animacao_vespa_delay, informacaoVespa1.velocidade_animacao);
                    } else {
                        if (informacaoVespa1.obter_experiencia == 0) {
                            informacaoPersonagem.experiencia_atual = informacaoPersonagem.experiencia_atual + informacaoVespa1.experiencia_atual; 
                            informacaoVespa1.obter_experiencia = 1;
                        }
                        if (informacaoVespa1.loot == 1) {
                            informacaoVespa1.loot = detectarColisaoMoeda(buffer, informacaoPersonagem.x, informacaoPersonagem.y, informacaoPersonagem.altura, informacaoPersonagem.largura, (informacaoVespa1.x + 12), (informacaoVespa1.y + 5), (informacaoVespa1.largura - 10), (informacaoVespa1.altura - 10), &informacaoPersonagem.moedas, informacaoVespa1.moedas);  
                            efeito_moeda(buffer, informacaoVespa1.x + 10, informacaoVespa1.y + 10, &animacao_moeda, &animacao_moeda_delay);
                        
                        }      
                    }
                    
                    // Vespa 2 //
                    if (informacaoVespa2.vigor > 0) {
                         movimentarSpriteAutomaticamente(&informacaoVespa2.x, &informacaoVespa2.y, &informacaoVespa2.lado, &informacaoVespa2.animacao, &informacaoVespa2.delayanimacao, informacaoVespa2.terreno, 2, 450, 550, 0, &animacao_vespa_delay, informacaoVespa2.velocidade_animacao);
                    } else {
                        if (informacaoVespa2.obter_experiencia == 0) {
                            informacaoPersonagem.experiencia_atual = informacaoPersonagem.experiencia_atual + informacaoVespa2.experiencia_atual; 
                            informacaoVespa2.obter_experiencia = 1;
                        }
                        if (informacaoVespa2.loot == 1) {
                            informacaoVespa2.loot = detectarColisaoMoeda(buffer, informacaoPersonagem.x, informacaoPersonagem.y, informacaoPersonagem.altura, informacaoPersonagem.largura, (informacaoVespa2.x + 12), (informacaoVespa2.y + 5), (informacaoVespa2.largura - 10), (informacaoVespa2.altura - 10), &informacaoPersonagem.moedas, informacaoVespa2.moedas);  
                            efeito_moeda(buffer, informacaoVespa2.x + 10, informacaoVespa2.y + 10, &animacao_moeda, &animacao_moeda_delay);
                        
                        }      
                    }
                    
                    draw_sprite(buffer, personagem [informacaoPersonagem.lado][informacaoPersonagem.animacao], informacaoPersonagem.x, informacaoPersonagem.y);
                    draw_sprite(buffer, roberto [informacaoRoberto.lado][informacaoRoberto.animacao], informacaoRoberto.x, informacaoRoberto.y);
                    draw_sprite(buffer, npc2 [informacaoNpc2.lado][informacaoNpc2.animacao], informacaoNpc2.x, informacaoNpc2.y);
                    draw_sprite(buffer, npc3 [informacaoNpc3.lado][informacaoNpc3.animacao], informacaoNpc3.x, informacaoNpc3.y);
                    
                    
                    // Desenha Barra de Status //
                    efeito_barra_de_status_personagem (buffer, informacaoPersonagem.vigor, informacaoPersonagem.energia, &animacao_status, &animacao_status_delay, informacaoPersonagem.moedas, datFontes, informacaoPersonagem.experiencia_atual_porcentagem, informacaoPersonagem.nivel);                   
                    
                    // Desenhos as habilidades da barra de habilidades //
                    if (informacaoPersonagem.habilidade1 == 1) efeito_habilidade_1_ativa (buffer, 5 + 2, 120 + 2, &animacao_habilidade1, &animacao_habilidade1_delay);
                    
                    // Movimento do Personagem // 
                    // Observação importante: A função movimentar persongem, só deve ser chamada após o personagem ser desenhado na tela.
                    if (((((((((informacaoBola.delayanimacao <= 0) &&  (opcao == 0) && (informacaoNpc3.posicao_conversa == 0) && (informacaoNpc2.posicao_conversa == 0) && (informacaoNpc1.posicao_conversa == 0) && (informacaoMariana.posicao_conversa == 0) && (informacaoCachorro.posicao_conversa == 0) && (informacaoRoberto.posicao_conversa == 0) && (informacaoGeovana.posicao_conversa == 0))))))))) {
                         movimentarJogador (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.lado, &informacaoPersonagem.animacao, &informacaoPersonagem.terreno, &animacao_personagem_delay);
                    }
                    
                    
                    // Falas em Areas Estaticas //
                    // Jogadores da Esquerda //
                    if (progresso == 0) {
                        if (informacaoNpc1.colisao_para_conversar == 1) {
                            if (informacaoNpc1.fala == 0) {
                                if (informacaoNpc1.posicao_conversa == 0)   {                                                                                                                                                                                                                              // 3º = coordenada da posicao Final da locomoção.
                                    animacao_balao = 0;
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoNpc1.lado, fala_personagem [1], buffer, informacaoPersonagem.face [0],"",                                                                                                                           // 4º = Tempo de Espera
                                                                                                                                                  "",                                                                                                                           // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoNpc1.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoNpc1.fala);
                        
                                } else if (informacaoNpc1.posicao_conversa == 1) {
                                    efeito_balao_exclamacao(buffer, informacaoPersonagem.x, informacaoPersonagem.y, &animacao_balao, &animacao_balao_delay); 
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoNpc1.lado, fala_personagem [1], buffer, informacaoPersonagem.face [0],"O pessoal está bem animado para",
                                                                                                                                                  "o treino!", 
                                                                                                                                                  "Já estão aquecendo desde já!",
                                                                                                                                                  "Melhor eu não atrapalhar eles...", 
                                                                                                                                                  "", datFontes, 0, &informacaoNpc1.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoNpc1.fala);    
                                }
                            }
                        } else {
                            informacaoNpc1.posicao_conversa = 0;
                        }
                    } else {
                        if (informacaoNpc1.colisao_para_conversar == 1) {
                            if (informacaoNpc1.fala == 0) {
                                if (informacaoNpc1.posicao_conversa == 0)   {                                                                                                                                                                                                                              // 3º = coordenada da posicao Final da locomoção.
                                    animacao_balao = 0;
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoNpc1.lado, fala_personagem [1], buffer, informacaoPersonagem.face [0],"",                                                                                                                           // 4º = Tempo de Espera
                                                                                                                                                  "",                                                                                                                           // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoNpc1.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoNpc1.fala);
                        
                                } else if (informacaoNpc1.posicao_conversa == 1) {
                                    efeito_balao_exclamacao(buffer, informacaoPersonagem.x, informacaoPersonagem.y, &animacao_balao, &animacao_balao_delay); 
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoNpc1.lado, fala_personagem [1], buffer, informacaoPersonagem.face [0],"É, o pessoal continua animado",
                                                                                                                                                  "mesmoo depois do treino!", 
                                                                                                                                                  "Isso me deixa motivado a querer",
                                                                                                                                                  "treinar cada vez mais!", 
                                                                                                                                                  "", datFontes, 0, &informacaoNpc1.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoNpc1.fala);    
                                }
                            }
                        } else {
                            informacaoNpc1.posicao_conversa = 0;
                        }
                    }
                    
                    // Jogadores da Direita //
                    if (progresso == 0) {
                        if (informacaoMariana.colisao_para_conversar == 1) {
                            if (informacaoMariana.fala == 0) {
                                if (informacaoMariana.posicao_conversa == 0)   {                                                                                                                                                                                                                              // 3º = coordenada da posicao Final da locomoção.
                                    animacao_balao = 0;
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoPersonagem.face [1],"",                                                                                                                           // 4º = Tempo de Espera
                                                                                                                                                  "",                                                                                                                           // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);
                        
                                } else if (informacaoMariana.posicao_conversa == 1) {
                                    efeito_balao_reticencias(buffer, informacaoPersonagem.x, informacaoPersonagem.y, &animacao_balao, &animacao_balao_delay); 
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoPersonagem.face [1],"Também preciso dar um aquecida, caso",
                                                                                                                                                  "contrário vou acabar sendo esmagado no treino", 
                                                                                                                                                  "por esses caras!",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 0, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);    
                                } 
                            }
                        } else {
                            informacaoMariana.posicao_conversa = 0;
                        }
                    } else {
                        if (informacaoMariana.colisao_para_conversar == 1) {
                            if (informacaoMariana.fala == 0) {
                                if (informacaoMariana.posicao_conversa == 0)   {                                                                                                                                                                                                                              // 3º = coordenada da posicao Final da locomoção.
                                    animacao_balao = 0;
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoPersonagem.face [1],"",                                                                                                                           // 4º = Tempo de Espera
                                                                                                                                                  "",                                                                                                                           // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);
                        
                                } else if (informacaoMariana.posicao_conversa == 1) {
                                    efeito_balao_reticencias(buffer, informacaoPersonagem.x, informacaoPersonagem.y, &animacao_balao, &animacao_balao_delay); 
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoMariana.lado, fala_personagem [1], buffer, informacaoPersonagem.face [1],"Isso sim é animação!",
                                                                                                                                                  "Já é noite e as energias deles parecem", 
                                                                                                                                                  "não se esgotarem!",
                                                                                                                                                  "Preciso treinar mais para obter", 
                                                                                                                                                  "uma energia dessa!", datFontes, 0, &informacaoMariana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoMariana.fala);    
                                } 
                            }
                        } else {
                            informacaoMariana.posicao_conversa = 0;
                        }
                    }
                    
                    // Torcedoras Parte Superior //
                    if (informacaoCachorro.colisao_para_conversar == 1) {
                        if (informacaoCachorro.fala == 0) {
                            if (informacaoCachorro.posicao_conversa == 0)   {                                                                                                                                                                                                                              // 3º = coordenada da posicao Final da locomoção.
                                animacao_balao = 0;
                                interacaoNpc (informacaoPersonagem.lado, &informacaoCachorro.lado, fala_personagem [1], buffer, informacaoPersonagem.face [1],"",                                                                                                                           // 4º = Tempo de Espera
                                                                                                                                                  "",                                                                                                                           // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoCachorro.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoCachorro.fala);
                        
                            } else if (informacaoCachorro.posicao_conversa == 1) {
                                efeito_balao_exclamacao(buffer, informacaoPersonagem.x, informacaoPersonagem.y, &animacao_balao, &animacao_balao_delay);     
                                interacaoNpc (informacaoPersonagem.lado, &informacaoCachorro.lado, fala_personagem [1], buffer, informacaoPersonagem.face [1],"Nossa, elas são realmente muito organizadas!",
                                                                                                                                                  "Realizam os movimentos no mesmo instante", 
                                                                                                                                                  "e não perdem o rítmo!",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 0, &informacaoCachorro.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoCachorro.fala);    
                            } 
                        }
                    } else {
                        informacaoCachorro.posicao_conversa = 0;
                    } 
                    
                    
                    // Geovana //
                    if (progresso == 0) {
                        if (informacaoGeovana.colisao_para_conversar == 1) {
                            if (informacaoGeovana.fala == 0) {
                                if (informacaoGeovana.posicao_conversa == 0)   {                                                                                                                                                                                                                              // 3º = coordenada da posicao Final da locomoção.
                                    animacao_balao = 0;
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoGeovana.lado, fala_personagem [1], buffer, informacaoPersonagem.face [0],"",                                                                                                                           // 4º = Tempo de Espera
                                                                                                                                                  "",                                                                                                                           // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoGeovana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoGeovana.fala);
                    
                                } else if (informacaoGeovana.posicao_conversa == 1) {
                                    efeito_balao_coracao(buffer, 378,75, &animacao_balao, &animacao_balao_delay);     
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoGeovana.lado, fala_personagem [1], buffer, informacaoGeovana.face [0],"Oi Jõão!!! Tudo bem com você?",
                                                                                                                                                  "Boa sorte no treino de hoje! Estou torcendo", 
                                                                                                                                                  "muito para que você se saia bem nos exercícios",
                                                                                                                                                  "do treinador Roberto.", 
                                                                                                                                                  "", datFontes, 2, &informacaoGeovana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoGeovana.fala);    
                                } else if (informacaoGeovana.posicao_conversa == 2) {
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoGeovana.lado, fala_personagem [1], buffer, informacaoPersonagem.face [0],"Obrigado Geovana, você sempre torceu",
                                                                                                                                                  "muito por min. Espero que você também", 
                                                                                                                                                  "se saia bem como lider de torcida.",
                                                                                                                                                  "", 
                                                                                                                                                "", datFontes, 3, &informacaoGeovana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoGeovana.fala);    
                                } else if (informacaoGeovana.posicao_conversa == 3) {
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoGeovana.lado, fala_personagem [1], buffer, informacaoGeovana.face [0],"Obrigada João, você é mesmo",
                                                                                                                                                  "um amor!", 
                                                                                                                                                  "",
                                                                                                                                                  "", 
                                                                                                                                                "", datFontes, 0, &informacaoGeovana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoGeovana.fala);    
                                }
                            }
                        } else {
                            informacaoGeovana.posicao_conversa = 0;
                        }
                    } else {
                        if (informacaoGeovana.colisao_para_conversar == 1) {
                            if (informacaoGeovana.fala == 0) {
                                if (informacaoGeovana.posicao_conversa == 0)   {                                                                                                                                                                                                                              // 3º = coordenada da posicao Final da locomoção.
                                    animacao_balao = 0;
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoGeovana.lado, fala_personagem [1], buffer, informacaoPersonagem.face [0],"",                                                                                                                           // 4º = Tempo de Espera
                                                                                                                                                  "",                                                                                                                           // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoGeovana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoGeovana.fala);
                    
                                } else if (informacaoGeovana.posicao_conversa == 1) {
                                    efeito_balao_coracao(buffer, 378,75, &animacao_balao, &animacao_balao_delay);     
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoGeovana.lado, fala_personagem [1], buffer, informacaoGeovana.face [0],"Desde o momento em que vi você",
                                                                                                                                                  "entrar pelo portão do ginásio, sabia que", 
                                                                                                                                                  "o vencedor seria você!",
                                                                                                                                                  "Aiiii, você é o melhor mesmo João!!!", 
                                                                                                                                                  "", datFontes, 2, &informacaoGeovana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoGeovana.fala);    
                                } else if (informacaoGeovana.posicao_conversa == 2) {
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoGeovana.lado, fala_personagem [1], buffer, informacaoPersonagem.face [0],"Ahahaha que isso...não foi nada!",
                                                                                                                                                  "Aliás, se não fosse sua torcida por min,", 
                                                                                                                                                  "o resultado com certeza seria o oposto!",
                                                                                                                                                  "Obrigado Geovana!", 
                                                                                                                                                  "", datFontes, 3, &informacaoGeovana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoGeovana.fala);    
                                } else if (informacaoGeovana.posicao_conversa == 3) {
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoGeovana.lado, fala_personagem [1], buffer, informacaoGeovana.face [0],"Que isso João, não precisa",
                                                                                                                                                  "agradecer, eu sempre estarei torcendo", 
                                                                                                                                                  "por você!",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 0, &informacaoGeovana.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoGeovana.fala);    
                                }
                            }
                        } else {
                            informacaoGeovana.posicao_conversa = 0;
                        }
                    }
                    
                    // Movimento de Npcs //
                    if (informacaoRoberto.colisao_para_conversar == 0) {
                        movimentarSpriteAutomaticamente(&informacaoRoberto.x, &informacaoRoberto.y, &informacaoRoberto.lado, &informacaoRoberto.animacao, &informacaoRoberto.delayanimacao, informacaoRoberto.terreno, 2, 570, 650, 50, &animacao_npc_delay, informacaoRoberto.velocidade_animacao);    // Parametros Numéricos//                                                                                                                                                                                                           // 7º Parametro responsável pelo sentido "1" para Vertical ou "2" para Horizontal
                        informacaoRoberto.posicao_conversa = 0;
                    } else {
                        informacaoRoberto.animacao = 0;
                        if (progresso == 0) {
                            if (informacaoRoberto.fala == 0) {        
                                if (informacaoRoberto.posicao_conversa == 0)   {                                                                                                                                                                                                                              // 3º = coordenada da posicao Final da locomoção.
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoRoberto.lado, fala_personagem [1], buffer, informacaoRoberto.face [0],"",                                                                                                                           // 4º = Tempo de Espera
                                                                                                                                                  "",                                                                                                                           // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoRoberto.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoRoberto.fala);
                        
                                } else if (informacaoRoberto.posicao_conversa == 1) {
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoRoberto.lado, fala_personagem [1], buffer, informacaoRoberto.face [0],"Err, aquele menino consegue me irritar...",
                                                                                                                                                  "E você quase se atrasou João,", 
                                                                                                                                                  "mais um minuto e você iria perder",
                                                                                                                                                  "o treino logo no primeiro dia.", 
                                                                                                                                                  "", datFontes, 2, &informacaoRoberto.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoRoberto.fala);    
                                } else if (informacaoRoberto.posicao_conversa == 2) {
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoRoberto.lado, fala_personagem [1], buffer, informacaoPersonagem.face [1],"Desculpe treinador Roberto.",
                                                                                                                                                  "É que tive que ajudar um amigo", 
                                                                                                                                                  "quando estava vindo para o ginásio.",
                                                                                                                                                  "A propósito ele mandou um abraço", 
                                                                                                                                                  "para o senhor.", datFontes, 3, &informacaoRoberto.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoRoberto.fala);    
                                } else if (informacaoRoberto.posicao_conversa == 3) {
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoRoberto.lado, fala_personagem [1], buffer, informacaoRoberto.face [0],"Ok. Bom, comece dando uma corrida aqui",
                                                                                                                                                  "na quadra para você se aquecer. ", 
                                                                                                                                                  "Quando você estiver preparado, para",
                                                                                                                                                  "começar o treinamento de verdade,", 
                                                                                                                                                  "volte a falar comigo.", datFontes, 4, &informacaoRoberto.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoRoberto.fala);    
                                } else if (informacaoRoberto.posicao_conversa == 4) {
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoRoberto.lado, fala_personagem [1], buffer, informacaoRoberto.face [0],"Ok. Bom, comece dando uma corrida aqui",
                                                                                                                                                  "na quadra para você se aquecer. ", 
                                                                                                                                                  "Quando você estiver preparado, para",
                                                                                                                                                  "começar o treinamento de verdade,", 
                                                                                                                                                  "volte a falar comigo.", datFontes, 0, &informacaoRoberto.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 1, &informacaoRoberto.fala);    
                                    informacaoRoberto.fala = 1;
                                    informacaoRoberto.posicao_conversa = 0;
                                }
                            } else if (informacaoRoberto.fala == 1) {
                                if (informacaoRoberto.posicao_conversa == 0)   {                                                                                                                                                                                                                              // 3º = coordenada da posicao Final da locomoção.
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoRoberto.lado, fala_personagem [1], buffer, informacaoRoberto.face [0],"",                                                                                                                           // 4º = Tempo de Espera
                                                                                                                                                  "",                                                                                                                           // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoRoberto.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 1, &informacaoRoberto.fala);
                        
                                } else if (informacaoRoberto.posicao_conversa == 1) {
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoRoberto.lado, fala_personagem [1], buffer, informacaoRoberto.face [0],"Isso, agora você me parece já estar",
                                                                                                                                                  "preparado para começar o treinamento.", 
                                                                                                                                                  "Quando olho pra você, me lembro do" ,
                                                                                                                                                  "primeiro dia de treinamento do seu pai aqui...", 
                                                                                                                                                  "Não é todo dia que se vê um show daqueles!", datFontes, 2, &informacaoRoberto.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 1, &informacaoRoberto.fala);    
                                } else if (informacaoRoberto.posicao_conversa == 2) {
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoRoberto.lado, fala_personagem [1], buffer, informacaoRoberto.face [0],"Enfim! Vamos começar logo o treino.",
                                                                                                                                                  "Estou ancioso para ver se o filho", 
                                                                                                                                                  "do grande Ligeirinho herdou as",
                                                                                                                                                  "habilidades do pai.", 
                                                                                                                                                  "Preparado!? Então vamos la.", datFontes, 3, &informacaoRoberto.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 1, &informacaoRoberto.fala);    
                                } else if (informacaoRoberto.posicao_conversa == 3) {
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoRoberto.lado, fala_personagem [1], buffer, informacaoRoberto.face [0],"Enfim! Vamos começar logo o treino.",
                                                                                                                                                  "Estou ancioso para ver se o filho", 
                                                                                                                                                  "do grande Ligeirinho herdou as",
                                                                                                                                                  "habilidades do pai.", 
                                                                                                                                                  "Preparado!? Então vamos la.", datFontes, 0, &informacaoRoberto.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoRoberto.fala);    
                                    cena_animada = 3;
                                    informacaoRoberto.posicao_conversa = 0;
                                    informacaoRoberto.fala = 0;
                                }  
                            }      
                        } else {
                            if (informacaoRoberto.fala == 0) {        
                                if (informacaoRoberto.posicao_conversa == 0)   {                                                                                                                                                                                                                              // 3º = coordenada da posicao Final da locomoção.
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoRoberto.lado, fala_personagem [1], buffer, informacaoRoberto.face [0],"",                                                                                                                           // 4º = Tempo de Espera
                                                                                                                                                  "",                                                                                                                           // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoRoberto.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoRoberto.fala);
                        
                                } else if (informacaoRoberto.posicao_conversa == 1) {
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoRoberto.lado, fala_personagem [1], buffer, informacaoRoberto.face [0],"É... você concluiu treino de hoje!",
                                                                                                                                                  "Acabei até sentindo uma certa", 
                                                                                                                                                  "nostalgia... é como se Ligeirinho",
                                                                                                                                                  "estivesse treinando com a gente", 
                                                                                                                                                  "de novo...", datFontes, 2, &informacaoRoberto.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoRoberto.fala);    
                                } else if (informacaoRoberto.posicao_conversa == 2) {
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoRoberto.lado, fala_personagem [1], buffer, informacaoPersonagem.face [0],"O senhor acha mesmo?",
                                                                                                                                                  "Nossa, fico muito alegre de ouvir", 
                                                                                                                                                  "isso, o meu maior sonho é um dia",
                                                                                                                                                  "ser igual a meu pai! Apesar da", 
                                                                                                                                                  "minha mãe não gostar muito da ideia...", datFontes, 3, &informacaoRoberto.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoRoberto.fala);    
                                } else if (informacaoRoberto.posicao_conversa == 3) {
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoRoberto.lado, fala_personagem [1], buffer, informacaoRoberto.face [0],"Hahahaha! Mariana, protetora como sempre!",
                                                                                                                                                  "Ela não deve gostar muito disso porque", 
                                                                                                                                                  "tem medo que alguem queira fazer alguma",
                                                                                                                                                  "maldade com você... Mas lembre-se, as mães", 
                                                                                                                                                  "querem sempre o melhor para seus filhos!", datFontes, 4, &informacaoRoberto.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoRoberto.fala);    
                                } else if (informacaoRoberto.posicao_conversa == 4) {
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoRoberto.lado, fala_personagem [1], buffer, informacaoRoberto.face [0],"Agora vá para casa Ligeirinho! Ops, quer dizer",
                                                                                                                                                  "Agora vá para casa João, ja é noite e parece", 
                                                                                                                                                  "que vai cair uma chuva daquelas...",
                                                                                                                                                  "Melhor se apressar ou vai acabar", 
                                                                                                                                                  "se molhando!", datFontes, 5, &informacaoRoberto.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoRoberto.fala);    
                                } else if (informacaoRoberto.posicao_conversa == 5) {
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoRoberto.lado, fala_personagem [1], buffer, informacaoRoberto.face [0],"Agora vá para casa Ligeirinho! Ops, quer dizer",
                                                                                                                                                  "Agora vá para casa João, ja é noite e parece", 
                                                                                                                                                  "que vai cair uma chuva daquelas...",
                                                                                                                                                  "Melhor se apressar ou vai acabar", 
                                                                                                                                                  "se molhando!", datFontes, 0, &informacaoRoberto.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 1, &informacaoRoberto.fala);    
                                    informacaoRoberto.posicao_conversa = 0;
                                    informacaoRoberto.fala = 1;
                                }
                            } else if (informacaoRoberto.fala == 1) {
                                if (informacaoRoberto.posicao_conversa == 0)   {                                                                                                                                                                                                                              // 3º = coordenada da posicao Final da locomoção.
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoRoberto.lado, fala_personagem [1], buffer, informacaoRoberto.face [0],"",                                                                                                                           // 4º = Tempo de Espera
                                                                                                                                                  "",                                                                                                                           // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoRoberto.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 1, &informacaoRoberto.fala);
                        
                                } else if (informacaoRoberto.posicao_conversa == 1) {
                                    interacaoNpc (informacaoPersonagem.lado, &informacaoRoberto.lado, fala_personagem [1], buffer, informacaoRoberto.face [0],"Você está aqui ainda?",
                                                                                                                                                  "A chuva que está vindo parece ser muito", 
                                                                                                                                                  "forte, se você tomar ela, pode acabar" ,
                                                                                                                                                  "pegando um resfriado daqueles!", 
                                                                                                                                                  "Vá para casa antes que isso aconteça!", datFontes, 0, &informacaoRoberto.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 1, &informacaoRoberto.fala);    
                                } 
                            }
                        }
                    }
                    
                    // Fala com os Npc's imóveis //
                    // Npc2 do Mapa //
                    if (progresso == 0) {
                        if (informacaoNpc2.colisao_para_conversar == 1){
                            if (informacaoNpc2.posicao_conversa == 0)   {                                                                                                                                                                                                                              // 3º = coordenada da posicao Final da locomoção.
                                interacaoNpc (informacaoPersonagem.lado, &informacaoNpc2.lado, fala_personagem [1], buffer, informacaoNpc2.face [0],"",                                                                                                                           // 4º = Tempo de Espera
                                                                                                                                                  "",                                                                                                                           // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoNpc2.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoNpc2.fala);
                        
                            } else if (informacaoNpc2.posicao_conversa == 1) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoNpc2.lado, fala_personagem [1], buffer, informacaoNpc2.face [0],"Parece que o Alexandre não é",
                                                                                                                                                  "amigo de ninguém mesmo, mas de você", 
                                                                                                                                                  "ele parece ter um pouquinho mais",
                                                                                                                                                  "de raiva não é? Hahahaha... ", 
                                                                                                                                                  "", datFontes, 2, &informacaoNpc2.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoNpc2.fala);    
                            } else if (informacaoNpc2.posicao_conversa == 2) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoNpc2.lado, fala_personagem [1], buffer, informacaoNpc2.face [0],"Parece que o Alexandre não é",
                                                                                                                                                  "amigo de ninguém mesmo, mas de você", 
                                                                                                                                                  "ele parece ter um pouquinho mais",
                                                                                                                                                  "de raiva não é? Hahahaha... ", 
                                                                                                                                                  "", datFontes, 3, &informacaoNpc2.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoNpc2.fala);    
                                informacaoNpc2.posicao_conversa    = 0;
                                informacaoNpc2.lado = 1;  
                            } 
                        } else {
                            informacaoNpc2.posicao_conversa = 0;
                        }
                    } else {
                        if (informacaoNpc2.colisao_para_conversar == 1){
                            if (informacaoNpc2.posicao_conversa == 0)   {                                                                                                                                                                                                                              // 3º = coordenada da posicao Final da locomoção.
                                interacaoNpc (informacaoPersonagem.lado, &informacaoNpc2.lado, fala_personagem [1], buffer, informacaoNpc2.face [0],"",                                                                                                                           // 4º = Tempo de Espera
                                                                                                                                                  "",                                                                                                                           // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoNpc2.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoNpc2.fala);
                        
                            } else if (informacaoNpc2.posicao_conversa == 1) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoNpc2.lado, fala_personagem [1], buffer, informacaoNpc2.face [0],"O Alexandre também foi muito bem",
                                                                                                                                                  "no treino!", 
                                                                                                                                                  "Acho que daria uma boa competição",
                                                                                                                                                  "entre vocês dois, não é mesmo?", 
                                                                                                                                                  "Hahahahahaha.", datFontes, 2, &informacaoNpc2.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoNpc2.fala);    
                            } else if (informacaoNpc2.posicao_conversa == 2) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoNpc2.lado, fala_personagem [1], buffer, informacaoNpc2.face [0],"O Alexandre também foi muito bem",
                                                                                                                                                  "no treino!", 
                                                                                                                                                  "Acho que daria uma boa competição",
                                                                                                                                                  "entre vocês dois, não é mesmo?", 
                                                                                                                                                  "Hahahahahaha.", datFontes, 3, &informacaoNpc2.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoNpc2.fala);    
                                informacaoNpc2.posicao_conversa    = 0;
                                informacaoNpc2.lado = 1;  
                            } 
                        } else {
                            informacaoNpc2.posicao_conversa = 0;
                        }
                    }
                    
                    // Npc3 do Mapa //
                    if (progresso == 0) {
                        if (informacaoNpc3.colisao_para_conversar == 1){
                            if (informacaoNpc3.posicao_conversa == 0)   {                                                                                                                                                                                                                              // 3º = coordenada da posicao Final da locomoção.
                                interacaoNpc (informacaoPersonagem.lado, &informacaoNpc3.lado, fala_personagem [1], buffer, informacaoNpc3.face [0],"",                                                                                                                           // 4º = Tempo de Espera
                                                                                                                                                  "",                                                                                                                           // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoNpc3.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoNpc3.fala);
                        
                            } else if (informacaoNpc3.posicao_conversa == 1) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoNpc3.lado, fala_personagem [1], buffer, informacaoNpc3.face [0],"E ae já está aquecido para treino?",
                                                                                                                                                  "De uma corrida ae no campo para", 
                                                                                                                                                  "esquentar os músculos, assim seu",
                                                                                                                                                  "seu corpo não vai ficar tão dolorido", 
                                                                                                                                                  "quando acabar o treino.", datFontes, 2, &informacaoNpc3.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoNpc3.fala);    
                            } else if (informacaoNpc3.posicao_conversa == 2) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoNpc3.lado, fala_personagem [1], buffer, informacaoNpc3.face [0],"E ae já está aquecido para treino?",
                                                                                                                                                  "De uma corrida ae no campo para", 
                                                                                                                                                  "esquentar os músculos, assim seu",
                                                                                                                                                  "seu corpo não vai ficar tão dolorido", 
                                                                                                                                                  "quando acabar o treino.", datFontes, 0, &informacaoNpc3.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoNpc3.fala);    
                                informacaoNpc3.posicao_conversa    = 0;
                                informacaoNpc3.lado = 3; 
                            }
                        } else {
                            informacaoNpc3.posicao_conversa = 0;
                        }
                    } else {
                        if (informacaoNpc3.colisao_para_conversar == 1){
                            if (informacaoNpc3.posicao_conversa == 0)   {                                                                                                                                                                                                                              // 3º = coordenada da posicao Final da locomoção.
                                interacaoNpc (informacaoPersonagem.lado, &informacaoNpc3.lado, fala_personagem [1], buffer, informacaoNpc3.face [0],"",                                                                                                                           // 4º = Tempo de Espera
                                                                                                                                                  "",                                                                                                                           // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoNpc3.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoNpc3.fala);
                        
                            } else if (informacaoNpc3.posicao_conversa == 1) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoNpc3.lado, fala_personagem [1], buffer, informacaoNpc3.face [0],"Parabéns João! Seu treino foi",
                                                                                                                                                  "realmente impressionante!", 
                                                                                                                                                  "Parece que eu ainda vou ter que",
                                                                                                                                                  "treinar bastante meu corpo para", 
                                                                                                                                                  "ter uma velocidade igual a sua!", datFontes, 2, &informacaoNpc3.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoNpc3.fala);    
                            } else if (informacaoNpc3.posicao_conversa == 2) {
                                interacaoNpc (informacaoPersonagem.lado, &informacaoNpc3.lado, fala_personagem [1], buffer, informacaoNpc3.face [0],"Parabéns João! Seu treino foi",
                                                                                                                                                  "realmente impressionante!", 
                                                                                                                                                  "Parece que eu ainda vou ter que",
                                                                                                                                                  "treinar bastante meu corpo para", 
                                                                                                                                                  "ter uma velocidade igual a sua!", datFontes, 0, &informacaoNpc3.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay, 0, &informacaoNpc3.fala);    
                                informacaoNpc3.posicao_conversa    = 0;
                                informacaoNpc3.lado = 3; 
                            }
                        } else {
                            informacaoNpc3.posicao_conversa = 0;
                        }
                    }
                                                                                                                                 
                    // Ataque da Bola  desenhada na Frente do Sprite //
                    if (informacaoPersonagem.habilidade1 == 1) {
                        if (informacaoPersonagem.lado != 2) {
                            if (informacaoBola.delayanimacao <= 0) {
                                efeito_ataque (buffer, &informacaoBola.x, &informacaoBola.y, &informacaoBola.delayanimacao, &informacaoPersonagem.energia, informacaoPersonagem.lado, &informacaoPersonagem.animacao, informacaoPersonagem.ataque1, &animacao_efeito_ataque, &animacao_efeito_ataque_2);
                                informacaoPersonagem.energia = informacaoPersonagem.energia + 1;
                            } else if (informacaoBola.delayanimacao > 0) {
                                efeito_ataque (buffer, &informacaoBola.x, &informacaoBola.y, &informacaoBola.delayanimacao, &informacaoPersonagem.energia, informacaoPersonagem.lado, &informacaoPersonagem.animacao, informacaoPersonagem.ataque1, &animacao_efeito_ataque, &animacao_efeito_ataque_2);
                            }
                            if (informacaoPersonagem.energia  > 3) {
                                informacaoPersonagem.energia = 3;
                            }
                        }
                    } 
                    informacaoBola.delayanimacao = informacaoBola.delayanimacao - 1;  
                
                    // Atualiza Altura da Bola após Mudança das coordenadas X e Y //
                    informacaoBola.largura = informacaoBola.x + SPRITE_LARGURA;
                    informacaoBola.altura  = informacaoBola.y + SPRITE_ALTURA;
                    
                    // Colisão dos Ataques com os monstros // 
                    // Com Vespa 1 //
                    if (informacaoVespa1.vigor > 0) {
                        detectarColisaoAtaquePersonagem(buffer, &informacaoBola.x, &informacaoBola.y, &informacaoBola.altura, &informacaoBola.largura, informacaoBola.lado, (informacaoVespa1.x + 30), (informacaoVespa1.y + 40), informacaoVespa1.largura - 10, informacaoVespa1.altura + 10, informacaoBola.terreno, &informacaoBola.animacao, &informacaoVespa1.vigor); 
                    }
                    
                    // Com Vespa 2 //
                    if (informacaoVespa2. vigor > 0) {
                        detectarColisaoAtaquePersonagem(buffer, &informacaoBola.x, &informacaoBola.y, &informacaoBola.altura, &informacaoBola.largura, informacaoBola.lado, (informacaoVespa2.x + 30), (informacaoVespa2.y + 40), informacaoVespa2.largura - 10, informacaoVespa2.altura + 10, informacaoBola.terreno, &informacaoBola.animacao, &informacaoVespa2.vigor); 
                    }
                    
                    // Faz barulho de porta abrindo e arruma variáveis para mapa 7 //
                    if (mapa_atual == 7) {
                        play_sample (audio_efeito [4], 500, 128, 1000, 0);
                        
                        mapa_atual = 10;
                        musica = 1;            
                    }
                    
                    
                    // Caso Jogador Perca //
                    if (informacaoPersonagem.vigor <= 0){
                        clear (buffer);
                        draw_sprite(buffer, cenario, 0,  0);
                        if (informacaoVespa1.vigor > 0) {
                            draw_sprite(buffer, vespa [informacaoVespa1.lado][informacaoVespa1.animacao], informacaoVespa1.x, informacaoVespa1.y);
                        }
                        draw_sprite(buffer, roberto [informacaoRoberto.lado][informacaoRoberto.animacao], informacaoRoberto.x, informacaoRoberto.y);
                        draw_sprite(buffer, npc2 [informacaoNpc2.lado][informacaoNpc2.animacao], informacaoNpc2.x, informacaoNpc2.y);
                        draw_sprite(buffer, npc3 [informacaoNpc3.lado][informacaoNpc3.animacao], informacaoNpc3.x, informacaoNpc3.y);
                        draw_sprite(buffer, personagem_desmaiado, informacaoPersonagem.x , informacaoPersonagem.y);
                        efeito_torcedora(buffer, 240, 50, &animacao_torcedora [0], &animacao_torcedora_delay [0]);
                        efeito_geovana(buffer, 374, 80, &animacao_torcedora [1], &animacao_torcedora_delay [1]);
                        efeito_jogadores_direita_ginasio (buffer, 720, 120, &jogadores_direita_ginasio, &jogadores_direita_ginasio_delay);
                        efeito_jogadores_esquerda_ginasio (buffer, 45, 120, &jogadores_esquerda_ginasio, &jogadores_esquerda_ginasio_delay);
                        efeito_pilar_de_fogo_azul (buffer, 50, 60, &animacao_fogo [0], &animacao_fogo_delay [0]);
                        efeito_pilar_de_fogo_amarelo (buffer, 50, 455, &animacao_fogo [1], &animacao_fogo_delay [1]);
                        efeito_pilar_de_fogo_amarelo (buffer, 725, 60, &animacao_fogo [2], &animacao_fogo_delay [2]);
                        efeito_pilar_de_fogo_azul (buffer, 725, 455, &animacao_fogo [3], &animacao_fogo_delay [3]);
                        efeito_barra_de_status_personagem (buffer, informacaoPersonagem.vigor, informacaoPersonagem.energia, &animacao_status, &animacao_status_delay, informacaoPersonagem.moedas, datFontes, informacaoPersonagem.experiencia_atual_porcentagem, informacaoPersonagem.nivel); 
                        // Desenhos as habilidades da barra de habilidades //
                        if (informacaoPersonagem.habilidade1 == 1) efeito_habilidade_1_ativa (buffer, 5 + 2, 120 + 2, &animacao_habilidade1, &animacao_habilidade1_delay);
                    
                        mapa_atual = 3;
                        musica = 3;
                    }
 // --------------------------------------------------------------------------- MINI GAME TUTORIAL 0 ---------------------------------------------------------------------------------------------------------------
                 } else if (cena_animada == 3) { 
                    if (musica == 2) {  
                        fadeout (8);      
                        clear (buffer);
                        efeito_tutorial_parallax (buffer, &animacao_tutorial_parallax);
                        tutorial_minigame_ginasio_0 (buffer, posicao_tutorial);
                        fadein (buffer, 8);
                        musica = 1; 
                    }
                    efeito_tutorial_parallax (buffer, &animacao_tutorial_parallax);
                    tutorial_minigame_ginasio_0 (buffer, posicao_tutorial);
                    animacao_tecla_enter (buffer, 690, 410, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);  
                    set_keyboard_rate(0,0);
                    if (key[KEY_ENTER]) {
                        if (keypressed()) {
                            posicao_tutorial = posicao_tutorial + 1;
                        }
                        clear_keybuf();
                    }
                    if (posicao_tutorial >= 3) {
                        cena_animada = 4;
                        audio_fundo = load_midi("Audios/Fundo/musica_minigame_ginasio.mid");            // Load na musica do mapa 1.
                        play_midi(audio_fundo, 1);
                        posicao_tutorial = 0;
                    }     
 // --------------------------------------------------------------------------- MINI GAME CORRIDA  --------------------------------------------------------------------------------------------------------------- //
                 } else if (cena_animada == 4) {
                    if (musica == 1) {  
                        fadeout (3);      
                        clear (buffer);
                        
                        animacao_contagem_regressiva               = 0;
                        animacao_contagem_regressiva_delay         = 0;
                        
                        animacao_mini_game_corrida_resultado       = 0;
                        animacao_mini_game_corrida_resultado_delay = 0;
                        
                        mini_game_corrida_resultado                = 0;
                        mini_game_ponto_adversario                 = 0;
                        mini_game_ponto_jogador                    = 0;
                        
                        informacaoPersonagem.x                     = 720;
                        informacaoPersonagem.y                     = 390;
                        informacaoPersonagem.lado                  = 3;
                        informacaoNpc2.x                           = 720;
                        informacaoNpc2.y                           = 125;
                        informacaoNpc2.lado                        = 3;
                        
                        informacaoNpc3.x                           = 150;
                        informacaoNpc3.lado                        = 2;
                        informacaoRoberto.lado                     = 2;
                        informacaoRoberto.y                        = 430;
                        
                        // Velocidade do Adversário De Acordo Com O Nível do Minigame //
                        if (mini_game_corrida_nivel == 0) { 
                            informacaoNpc2.terreno = 6;
                        } else if (mini_game_corrida_nivel == 1) {
                            informacaoNpc2.terreno = 7;
                        } else if (mini_game_corrida_nivel == 2){
                            informacaoNpc2.terreno = 8;
                        } else {
                            informacaoNpc2.terreno = 2;
                        }             
                        
                        draw_sprite(buffer, cenario, 0,  0);
                        draw_sprite(buffer, personagem [informacaoPersonagem.lado][informacaoPersonagem.animacao], informacaoPersonagem.x, informacaoPersonagem.y);
                        draw_sprite(buffer, roberto [informacaoRoberto.lado][informacaoRoberto.animacao], informacaoRoberto.x, informacaoRoberto.y);
                        draw_sprite(buffer, npc2 [informacaoNpc2.lado][informacaoNpc2.animacao], informacaoNpc2.x, informacaoNpc2.y);
                        draw_sprite(buffer, npc3 [informacaoNpc3.lado][informacaoNpc3.animacao], informacaoNpc3.x, informacaoNpc3.y);
                        efeito_torcedora(buffer, 240, 50, &animacao_torcedora [0], &animacao_torcedora_delay [0]);
                        efeito_geovana(buffer, 374, 70, &animacao_torcedora [1], &animacao_torcedora_delay [1]);
                        efeito_jogadores_embaixo_ginasio (buffer, 223, 420, &jogadores_direita_ginasio, &jogadores_direita_ginasio_delay);
                        efeito_jogadores_encima_ginasio (buffer, 223, 93, &jogadores_esquerda_ginasio, &jogadores_esquerda_ginasio_delay);  
                        efeito_pilar_de_fogo_azul (buffer, 50, 60, &animacao_fogo [0], &animacao_fogo_delay [0]);
                        efeito_pilar_de_fogo_amarelo (buffer, 50, 455, &animacao_fogo [1], &animacao_fogo_delay [1]);
                        efeito_pilar_de_fogo_amarelo (buffer, 725, 60, &animacao_fogo [2], &animacao_fogo_delay [2]);
                        efeito_pilar_de_fogo_azul (buffer, 725, 455, &animacao_fogo [3], &animacao_fogo_delay [3]);
                        fadein (buffer, 2);
                        musica = 2; 
                    }
                    
                    // Atualiza Largura e Altura do Personagem Principal //
                    informacaoPersonagem.largura = informacaoPersonagem.x + SPRITE_LARGURA;
                    informacaoPersonagem.altura  = informacaoPersonagem.y + SPRITE_ALTURA;
                    
                    // Atualiza Largura e Altura do Roberto //
                    informacaoRoberto.largura = informacaoRoberto.x + SPRITE_NPC_LARGURA;
                    informacaoRoberto.altura  = informacaoRoberto.y + SPRITE_NPC_ALTURA;
                    
                    // Testes de Colisões Mapa Vila//            
                    // Toda Parte Alta do Personagem //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 0, 0, 800, 385, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                
                    // Toda Parte Baixa do Personagem //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 0, 445, 800, 600, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    
                    // Parte Direita do Ginásio //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 775, 0, 800, 600, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    
                    // Parte Esquerda do Ginásio //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 0, 0, 25, 600, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    
                    // Desenha Sprites na Tela //
                    draw_sprite(buffer, cenario, 0,  0);
                    draw_sprite(buffer, personagem [informacaoPersonagem.lado][informacaoPersonagem.animacao], informacaoPersonagem.x, informacaoPersonagem.y);
                    draw_sprite(buffer, roberto [informacaoRoberto.lado][informacaoRoberto.animacao], informacaoRoberto.x, informacaoRoberto.y);
                    draw_sprite(buffer, npc3 [informacaoNpc3.lado][informacaoNpc3.animacao], informacaoNpc3.x, informacaoNpc3.y);
                    efeito_torcedora(buffer, 240, 50, &animacao_torcedora [0], &animacao_torcedora_delay [0]);
                    efeito_geovana(buffer, 374, 70, &animacao_torcedora [1], &animacao_torcedora_delay [1]);
                    efeito_jogadores_embaixo_ginasio (buffer, 223, 420, &jogadores_direita_ginasio, &jogadores_direita_ginasio_delay); 
                    efeito_jogadores_encima_ginasio (buffer, 223, 93, &jogadores_esquerda_ginasio, &jogadores_esquerda_ginasio_delay);  
                    draw_sprite(buffer, npc2 [informacaoNpc2.lado][informacaoNpc2.animacao], informacaoNpc2.x, informacaoNpc2.y);
                    efeito_pilar_de_fogo_azul (buffer, 50, 60, &animacao_fogo [0], &animacao_fogo_delay [0]);
                    efeito_pilar_de_fogo_amarelo (buffer, 50, 455, &animacao_fogo [1], &animacao_fogo_delay [1]);
                    efeito_pilar_de_fogo_amarelo (buffer, 725, 60, &animacao_fogo [2], &animacao_fogo_delay [2]);
                    efeito_pilar_de_fogo_azul (buffer, 725, 455, &animacao_fogo [3], &animacao_fogo_delay [3]);
                    efeito_contagem_regressiva (buffer, 250, 70, &animacao_contagem_regressiva, &animacao_contagem_regressiva_delay); 
                    
                    // Movimento do Personagem // 
                    // Observação importante: A função movimentar persongem, só deve ser chamada após o personagem ser desenhado na tela.
                    if ((informacaoBola.delayanimacao <= 0) &&  (opcao == 0)) {
                        if (((mini_game_ponto_jogador < 3) && (mini_game_ponto_adversario < 3) && (animacao_contagem_regressiva > 2))) {
                            movimentarJogador (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.lado, &informacaoPersonagem.animacao, &informacaoPersonagem.terreno, &animacao_personagem_delay);
                        } else {
                            informacaoPersonagem.animacao = 0;
                        } 
                    }
                    
                    // Movimento do Adversário
                    if (((mini_game_ponto_jogador < 3) && (mini_game_ponto_adversario < 3) && (animacao_contagem_regressiva > 2))) {
                        if ((mini_game_corrida_nivel == 0) || (mini_game_corrida_nivel == 1)){
                            movimentarSpriteAutomaticamente(&informacaoNpc2.x, &informacaoNpc2.y, &informacaoNpc2.lado, &informacaoNpc2.animacao, &informacaoNpc2.delayanimacao, informacaoNpc2.terreno, 2, 50, 720, 0, &animacao_npc_delay, informacaoNpc2.velocidade_animacao);
                        } else {
                            movimentarSpriteAutomaticamente(&informacaoNpc2.x, &informacaoNpc2.y, &informacaoNpc2.lado, &informacaoNpc2.animacao, &informacaoNpc2.delayanimacao, informacaoNpc2.terreno, 2, 30, 745, 0, &animacao_npc_delay, informacaoNpc2.velocidade_animacao);  
                        }       
                    } else {
                        informacaoNpc2.animacao = 0;
                    }       
                    
                    if (informacaoPersonagem.x < 50) {
                        if (mini_game_lado_quadra_jogador == 1) {
                            mini_game_ponto_jogador = mini_game_ponto_jogador + 1;
                            mini_game_lado_quadra_jogador = 0;
                            play_sample (audio_efeito [6], 255, 128, 1000, 0);
                        }
                    } else if (informacaoPersonagem.x > 715) {
                        if (mini_game_lado_quadra_jogador == 0) {
                            mini_game_lado_quadra_jogador = 1;
                            if (mini_game_ponto_jogador != 0) {
                                mini_game_ponto_jogador = mini_game_ponto_jogador + 1;
                                play_sample (audio_efeito [6], 255, 128, 1000, 0);
                            }   
                        }
                    }
                    
                    if (informacaoNpc2.x < 50) {
                        if (mini_game_lado_quadra_adversario == 1) {
                            mini_game_ponto_adversario = mini_game_ponto_adversario + 1;
                            mini_game_lado_quadra_adversario = 0;
                        }
                    } else if (informacaoNpc2.x > 715) {
                        if (mini_game_lado_quadra_adversario == 0) {
                            mini_game_lado_quadra_adversario = 1;
                            if (mini_game_ponto_adversario != 0) {
                                mini_game_ponto_adversario = mini_game_ponto_adversario + 1;
                            }
                        }
                    }
                    
                    if (animacao_contagem_regressiva > 2) {
                        pontuacao_corrida (buffer, mini_game_ponto_jogador, mini_game_ponto_adversario); 
                        nivel_corrida (buffer, mini_game_corrida_nivel);
                    }
                    
                    if (mini_game_ponto_jogador == 3) {
                        mini_game_corrida_resultado = 1;    
                    }
                    
                    if (mini_game_ponto_adversario == 3) {
                        mini_game_corrida_resultado = 2;
                    }
                    
                    if ((mini_game_ponto_adversario == 3) || (mini_game_ponto_jogador == 3)) {
                        resultado_corrida (buffer, mini_game_corrida_resultado, &animacao_mini_game_corrida_resultado, &animacao_mini_game_corrida_resultado_delay);
                        if ((animacao_mini_game_corrida_resultado == 5) && (mini_game_corrida_resultado == 1)) {
                            musica = 1;
                            mini_game_corrida_nivel = mini_game_corrida_nivel + 1;
                   
                        } else if ((animacao_mini_game_corrida_resultado == 5) && (mini_game_corrida_resultado == 2)) {
                            musica = 1;
                            mini_game_corrida_nivel = mini_game_corrida_nivel + 1; 
                        }
                    }
                    
                    if (mini_game_corrida_nivel == 3) {
                        if (mini_game_corrida_resultado == 1) {
                            informacaoPersonagem.moedas = informacaoPersonagem.moedas + 50;
                            informacaoPersonagem.experiencia_atual = informacaoPersonagem.experiencia_atual + 20;
                        }
                        cena_animada = 5;
                        musica = 1;
                    }                                                        
                
  // ------------------------------------------------------------------------------- Tutorial Jogo do Penalti ---------------------------------------------------------------------------------------------- //
                } else if (cena_animada == 5) {
                    if (musica == 1) {  
                        fadeout (8);      
                        clear (buffer);
                        efeito_tutorial_parallax (buffer, &animacao_tutorial_parallax);
                        tutorial_minigame_ginasio_1 (buffer, posicao_tutorial);
                        fadein (buffer, 8);
                        musica = 2; 
                    }
                    efeito_tutorial_parallax (buffer, &animacao_tutorial_parallax);
                    tutorial_minigame_ginasio_1 (buffer, posicao_tutorial);
                    animacao_tecla_enter (buffer, 690, 410, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);  
                    set_keyboard_rate(0,0);
                    if (key[KEY_ENTER]) {
                        if (keypressed()) {
                            posicao_tutorial = posicao_tutorial + 1;
                        }
                        clear_keybuf();
                    }
                    if (posicao_tutorial > 3) {
                        mapa_atual = 8;
                        musica = 1;
                        posicao_tutorial = 0;
                    }  
                
  // --------------------------------------------------------------------------------- Tela Fim do Mini Game --------------------------------------------------------------------------------------------------- //               
                } else if (cena_animada == 6) {
                    if (musica == 1) {  
                        audio_fundo = load_midi("Audios/Fundo/musica_vitoria.mid");            // Load na musica do mapa 1.
                        play_midi(audio_fundo, 1);  
                        fadeout (8);      
                        clear (buffer);
                        efeito_vitoria_parallax (buffer, &animacao_tutorial_parallax);
                        tutorial_minigame_ginasio_fim (buffer, posicao_tutorial);
                        fadein (buffer, 8);
                        musica = 2; 
                    }
                    efeito_vitoria_parallax (buffer, &animacao_tutorial_parallax);
                    tutorial_minigame_ginasio_fim (buffer, posicao_tutorial);
                    animacao_tecla_enter (buffer, 690, 410, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);  
                    set_keyboard_rate(0,0);
                    if (key[KEY_ENTER]) {
                        if (keypressed()) {
                            posicao_tutorial = posicao_tutorial + 1;
                        }
                        clear_keybuf();
                    }
                    if (posicao_tutorial >= 1) {
                        cena_animada = 2;
                        musica = 1;
                        posicao_tutorial = 0;
                    }  
                }    
                
  // ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- //              
                // Abre Menu //              
                    if (opcao == 0) {
                        if (key[KEY_ESC]) {                                                                                                                                                                                                                                                                                                                                                                
                            opcao = 1;
                            play_sample (audio_efeito [3], 500, 128, 1000, 0);
                        }
                    }
                
                    if (opcao != 0) {
                        opcao = pausa_menu (buffer, opcao, &animacao_bola, &animacao_bola_delay);        
                    }              
                draw_sprite (screen, buffer, 0, 0);
                clear (buffer);
                
                destroy_bitmap (informacaoNpc2.face[0]);
                destroy_bitmap (informacaoNpc3.face[0]);
                destroy_bitmap (informacaoRoberto.face[0]);
                destroy_bitmap (informacaoGeovana.face[0]);
                for (cont_destruir_x = 0; cont_destruir_x != 4; cont_destruir_x++) {
                    for (cont_destruir_y = 0; cont_destruir_y != 4; cont_destruir_y++) {
                        destroy_bitmap (roberto[cont_destruir_x][cont_destruir_y]);
                        destroy_bitmap (npc2[cont_destruir_x][cont_destruir_y]);
                        destroy_bitmap (npc3[cont_destruir_x][cont_destruir_y]);
                        destroy_bitmap (vespa[cont_destruir_x][cont_destruir_y]);
                    }
                }
            } // FIM MAPA 4
//  ============================================================================================= TUTORIAL DE COMO USAR HABILIDADE 1 ======================================================================================= //            
            if (mapa_atual == 5) { 
                if (musica == 2) {  
                    fadeout (8);      
                    clear (buffer);
                    efeito_tutorial_parallax (buffer, &animacao_tutorial_parallax);
                    tutorial_habilidade1 (buffer, posicao_tutorial);
                    fadein (buffer, 8);
                    play_sample (audio_efeito [5], 255, 128, 1000, 0);
                    musica = 1; 
                }
                efeito_tutorial_parallax (buffer, &animacao_tutorial_parallax);
                tutorial_habilidade1 (buffer, posicao_tutorial);
                animacao_tecla_enter (buffer, 690, 410, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);  
                set_keyboard_rate(0,0);
                if (key[KEY_ENTER]) {
                    if (keypressed()) {
                        posicao_tutorial = posicao_tutorial + 1;
                    }
                    clear_keybuf();
                }
                if (posicao_tutorial >= 2) {
                    mapa_atual = 2;
                    posicao_tutorial = 0;
                } 
                draw_sprite (screen, buffer, 0, 0);
                clear (buffer);
            } 
//  ============================================================================================= MINI GAME JOGO MEMÓRIA ====================================================================================== //              
            if (mapa_atual == 6) {
                 if (musica == 1) { 
                     fadeout (8);      
                     clear (buffer);
                     cenario  = load_jpg("Imagens/MiniGames/JogoMemoria/Fundo/Fundo_Jogo_Memoria.jpg", NULL);
                     draw_sprite(buffer, cenario, 0,  0);
                     jogo_memoria (buffer, VetCartas, &informacaoJogoCarta1, &delay_ver_carta, &animacao_bola, &animacao_bola_delay, &posicao_x_efeito_carta_selecionada, &posicao_y_efeito_carta_selecionada, &animacao_carta_selecionada, &animacao_ponto_positivo, &animacao_ponto_negativo);
                     pontuacao_cartas (buffer, informacaoJogoCarta1.Ponto);
                     audio_fundo = load_midi("Audios/Fundo/musica_minigame_cartas.mid");           
                     play_midi(audio_fundo, 1);
                     fadein (buffer, 8);
                     musica = 2; 
                 }
                 draw_sprite(buffer, cenario, 0,  0);
                 jogo_memoria (buffer, VetCartas, &informacaoJogoCarta1, &delay_ver_carta, &animacao_bola, &animacao_bola_delay, &posicao_x_efeito_carta_selecionada, &posicao_y_efeito_carta_selecionada, &animacao_carta_selecionada, &animacao_ponto_positivo, &animacao_ponto_negativo);
                 pontuacao_cartas (buffer, informacaoJogoCarta1.Ponto); 
                 efeito_ponto_negativo (buffer, &animacao_ponto_negativo, &animacao_ponto_negativo_delay, 100, 150);
                 efeito_ponto_positivo (buffer, &animacao_ponto_positivo, &animacao_ponto_positivo_delay, 100, 150);
                 efeito_carta_selecionada (buffer, posicao_x_efeito_carta_selecionada, posicao_y_efeito_carta_selecionada, &animacao_carta_selecionada, &animacao_carta_selecionada_delay);
                 //Abre Menu 
                 if (opcao == 0) {
                     if (key[KEY_ESC]) {                                                                                                                                                                                                                                                                                                                                                                        
                         opcao = 1;
                         play_sample (audio_efeito [3], 500, 128, 1000, 0);
                     }
                 }
                 
                 if (informacaoJogoCarta1.testa_fim == 1) {
                     informacaoPersonagem.moedas = (informacaoPersonagem.moedas + (5 * informacaoJogoCarta1.Ponto));
                     mapa_atual = 12;
                     musica = 1; 
                 } 
                 
                 draw_sprite (screen, buffer, 0, 0);
                 clear (buffer);
            }// FIM MAPA 6
            
// =============================================================================================== FIM DO JOGO DA MEMÓRIA ================================================================================================== //
            if (mapa_atual == 12) {
                if (musica == 1) {
                    audio_fundo = load_midi("Audios/Fundo/musica_vitoria.mid");            // Load na musica do mapa 1.
                    play_midi(audio_fundo, 1);  
                    fadeout (8);      
                    clear (buffer);
                    efeito_vitoria_parallax (buffer, &animacao_tutorial_parallax);
                    jogo_memoria_fim(buffer);
                    fadein (buffer, 8);
                    musica = 2;   
                }
                efeito_vitoria_parallax (buffer, &animacao_tutorial_parallax);
                jogo_memoria_fim(buffer);
                animacao_tecla_enter (buffer, 690, 410, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);  
                if (key[KEY_ENTER]) {
                    if (keypressed()) {
                        mapa_atual = 2;
                        musica = 1;
                        audio_fundo = load_midi("Audios/Fundo/musica_vila3.mid");
                        play_midi(audio_fundo, 1);
                        progresso = 3;  
                    }
                    clear_keybuf();
                }
                
                draw_sprite(screen, buffer, 0, 0);
                clear (buffer);
            }
            
// =============================================================================================== FIM DO EPISÓDIO ================================================================================================== //
            if (mapa_atual == 13) {
                if (musica == 1) {
                    audio_fundo = load_midi("Audios/Fundo/musica_sonho.mid");            // Load na musica do mapa 1.
                    play_midi(audio_fundo, 1);  
                    fadeout (2);      
                    clear (buffer);
                    efeito_bola_parallax(buffer, &animacao_tutorial_parallax);
                    efeito_fim (buffer);
                    animacao_tecla_enter (buffer, 690, 440, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);  
                    fadein (buffer, 2);
                    musica = 2;   
                }
                efeito_bola_parallax(buffer, &animacao_tutorial_parallax);
                efeito_fim (buffer);
                animacao_tecla_enter (buffer, 690, 440, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);  
                if (key[KEY_ENTER]) {                                        
                    if (keypressed()) {                                                                                       
                    mapa_atual                         = 14;
                    /*progresso_global                 = 0;
                    progresso                          = 0;
                    animacao_local                     = 0;
                    cena_animada                       = 0;
                    cena_animada_informacoes_iniciais  = 0;
                    musica                             = 0;
                    caso_colisao                       = 0; // Através dessa variável recebo o retorno da fundação detectarColisao, que cria um quadradro imaginário para haver colisão.
                    caso_colisao_sprite                = 0; // Através dessa variável recebo o retorno da função detectarColisaoSprite, que cria um quadradro imaginário em que qunado há colisão o Npc simplesmente para de andar (como um sensor)
                    caso_colisao_nociva                = 0;
                    opcao                              = 0;
                    velocidade_tempo;
                    comparador_tempo;
                    velocidade_fps                     = 0;
                    posicao_tutorial                   = 0;   
                    teste_efeito_nuvem                 = 0;
                    altura_nuvem_1                     = 0;
                    srand(time(NULL));
                    altura_nuvem_2                     = 1 + (int)( 550.0 * rand() / ( RAND_MAX + 1.0 ) );
                    cont                               = 0;
                    interacao                          = 0;
                    efeito                             = 0;
                    efeito_sonoro                      = 0;
                    cont_destruir_x                    = 0;
                    cont_destruir_y                    = 0;
                        
                    mini_game_lado_quadra_jogador        = 0;
                    mini_game_ponto_jogador              = 0;
    
                    mini_game_lado_quadra_adversario     = 0;
                    mini_game_ponto_adversario           = 0;
    
                    mini_game_corrida_resultado          = 0;
                    mini_game_corrida_nivel              = 0;
    
                    mini_game_pergunta_resposta_opcao    = 0;
                    mini_game_pergunta_resposta_pergunta = 0;
                    mini_game_pergunta_resposta_ponto    = 0;
                    
                    entrar               = 1;
                    entrar_2             = 0;
                    entrar_3             = 0;
                    entrar_4             = 0;
                    entrar_5             = 0;
                    
                    introducao_posicao   = 0;
                    
                    audio_fundo = load_midi("Audios/Fundo/musica_abertura.mid");
                    
                    informacaoPersonagem.x                             =   0;
                    informacaoPersonagem.y                             =   0;
                    informacaoPersonagem.lado                          =   0;
                    informacaoPersonagem.animacao                      =   0;
                    informacaoPersonagem.terreno                       =   TERRENO_NORMAL;
                    informacaoPersonagem.largura                       =   informacaoPersonagem.x + SPRITE_LARGURA;
                    informacaoPersonagem.altura                        =   informacaoPersonagem.y + SPRITE_ALTURA;
                    informacaoPersonagem.vigor                         =   6;
                    informacaoPersonagem.energia                       =   3;
                    informacaoPersonagem.face [0]                      =   load_bitmap ("Imagens/Personagens/Principal/Faces/face_joao_0.tga", NULL);
                    informacaoPersonagem.face [1]                      =   load_bitmap ("Imagens/Personagens/Principal/Faces/face_joao_1.tga", NULL);
                    informacaoPersonagem.ataque1 [0]                   =   load_bitmap ("Imagens/Personagens/Principal/Ataque1/bola_0.bmp", NULL);
                    informacaoPersonagem.ataque1 [1]                   =   load_bitmap ("Imagens/Personagens/Principal/Ataque1/bola_1.bmp", NULL);
                    informacaoPersonagem.ataque1 [2]                   =   load_bitmap ("Imagens/Personagens/Principal/Ataque1/bola_2.bmp", NULL);
                    informacaoPersonagem.moedas                        =   10;
                    informacaoPersonagem.nivel                         =   1;
                    informacaoPersonagem.habilidade1                   =   0;
                    informacaoPersonagem.experiencia_atual             =   0;
                    informacaoPersonagem.experiencia_proximo_nivel     =   50 * informacaoPersonagem.nivel;
                    informacaoPersonagem.experiencia_atual_porcentagem =   (informacaoPersonagem.experiencia_atual * 100) / informacaoPersonagem.experiencia_proximo_nivel;
    
                    interacaoBau1.x                     = 0;
                    interacaoBau1.y                     = 0;
                    interacaoBau1.estado                = 0;
                    interacaoBau1.animacao              = 0;
                    interacaoBau1.animacao_delay        = 0;
                    interacaoBau1.animacao_brilho       = 0;
                    interacaoBau1.animacao_brilho_delay = 0;
                    interacaoBau1.recompensaHabilidade  = 1;
                    interacaoBau1.recompensaVigor       = 0;
                    
                    // Informações sobre o jogo de carta //
                    informacaoJogoCarta1.ComparaId[0] = 0;
                    informacaoJogoCarta1.ComparaId[1] = 0;
                    informacaoJogoCarta1.x            = 0;
                    informacaoJogoCarta1.y            = 0;
                    informacaoJogoCarta1.C1           = 0;
                    informacaoJogoCarta1.C2           = 0;
                    informacaoJogoCarta1.L1           = 0;
                    informacaoJogoCarta1.L2           = 0;
                    informacaoJogoCarta1.estadoClique = 0;
                    informacaoJogoCarta1.Ponto        = 0;
                    informacaoJogoCarta1.colisao      = 0;
                    informacaoJogoCarta1.contClique   = 0;
                    
                    // Zera Animaçoes //
                    animacao_personagem_delay                  = 0;
                    animacao_npc_delay                         = 0;
                    animacao_vespa_delay                       = 0;
    
                    animacao_menu_abrindo                      = 0;
                    animacao_menu_abrindo_audio                = 0;
    
                    animacao_pressione_enter                   = 0;
                    animacao_pressione_enter_delay             = 0;
    
                    animacao_bola                              = 0;
                    animacao_bola_delay                        = 0;
    
                    animacao_ceu_1_parallax_delay              = 0;
                    animacao_ceu_1_parallax                    = 0;
    
                    animacao_ceu_2_parallax_delay              = 0;
                    animacao_ceu_2_parallax                    = 0;
    
                    animacao_tutorial_parallax                 = 0;
                    animacao_parallax_quem_somos               = 0;
    
                    animacao_choro                             = 0;
                    animacao_choro_delay                       = 0;
    
                    animacao_status                            = 0;
                    animacao_status_delay                      = 0;
    
                    animacao_chuva_noite                       = 0;
                    animacao_chuva_noite_delay                 = 0;
    
                    animacao_efeito_ataque                     = 0;
                    animacao_efeito_ataque_2                   = 0;
    
                    animacao_relampago                         = 0;
                    animacao_relampago_delay                   = 0;  
    
                    animacao_fogo [4];
                    animacao_fogo_delay [4];
    
                    animacao_luz_poste                         = 0;
                    animacao_luz_poste_delay                   = 0;
    
                    animacao_balao                             = 0;
                    animacao_balao_delay                       = 0; 
    
                    animacao_subiu_nivel                       = 21;
                    animacao_subiu_nivel_delay                 = 0;
    
                    animacao_torcedora [2];         
                    animacao_torcedora_delay [2];
                    
                    animacao_torcedora [0]                         = 0;
                    animacao_torcedora [1]                         = 0; 
                    animacao_torcedora_delay [0]                   = 0;
                    animacao_torcedora_delay [1]                   = 5;
    
                    jogadores_direita_ginasio                  = 0;
                    jogadores_direita_ginasio_delay            = 0;
                    jogadores_esquerda_ginasio                 = 0;
                    jogadores_esquerda_ginasio_delay           = 0;
    
                    animacao_agua_1                            = 0;   
                    animacao_agua_1_delay                      = 0;
                    animacao_agua_2                            = 0;   
                    animacao_agua_2_delay                      = 0;
    
                    animacao_1_sombra_nuvem                    = 0;
                    animacao_1_sombra_nuvem_delay              = 0;
                    animacao_2_sombra_nuvem                    = 0;
                    animacao_2_sombra_nuvem_delay              = 0;
                    animacao_3_sombra_nuvem                    = 0;
                    animacao_3_sombra_nuvem_delay              = 0;
    
                    animacao_tecla_enter_pulsando              = 0;
                    animacao_tecla_enter_pulsando_delay        = 0;
    
                    animacao_tecla_esc_pulsando                = 0;
                    animacao_tecla_esc_pulsando_delay          = 0;
    
                    animacao_moeda                             = 0;
                    animacao_moeda_delay                       = 0;
    
                    animacao_ganha_habilidade                  = 0;
                    animacao_ganha_habilidade_delay            = 0;
    
                    animacao_habilidade1                       = 0;
                    animacao_habilidade1_delay                 = 0;
    
                    animacao_contagem_regressiva               = 0;
                    animacao_contagem_regressiva_delay         = 0;
    
                    animacao_mini_game_corrida_resultado       = 0;
                    animacao_mini_game_corrida_resultado_delay = 0;
    
                    delay_ver_carta                            = 0;
                    posicao_x_efeito_carta_selecionada         = 0;
                    posicao_y_efeito_carta_selecionada         = 0;
                    animacao_carta_selecionada                 = 9;
                    animacao_carta_selecionada_delay           = 0;
    
                    animacao_ponto_positivo                    = 11;
                    animacao_ponto_positivo_delay              = 0;
    
                    animacao_ponto_negativo                    = 11;
                    animacao_ponto_negativo_delay              = 0;
    
                    animacao_cursor_pergunta_resposta          = 0;
                    animacao_cursor_pergunta_resposta_delay    = 0;
    
                    animacao_acerto_esquerda                   = 16;
                    animacao_acerto_esquerda_delay             = 0;
    
                    animacao_acerto_direita                    = 16;
                    animacao_acerto_direita_delay              = 0;
    
                    animacao_erro_esquerda                     = 16;
                    animacao_erro_esquerda_delay               = 0;
    
                    animacao_erro_direita                      = 16;
                    animacao_erro_direita_delay                = 0;
    
                    animacao_texto_sonho                       = 11;
                    animacao_texto_sonho_delay                 = 0;
                    
                    for (cont_destruir_x = 0; cont_destruir_x <4; cont_destruir_x ++) {
                        for (cont_destruir_y = 0; cont_destruir_y < 4; cont_destruir_y ++) {
                            VetCartas [cont_destruir_x] [cont_destruir_y].estado = 0;
                        }
                    }
                    */
                    
                    clear (buffer);
                    fadeout (8);
                    }
                    clear_keybuf();
                }
                
                draw_sprite(screen, buffer, 0, 0);
                clear (buffer);
            }
// =============================================================================================== RANKING ================================================================================================== //
            if (mapa_atual == 14) {
                if (musica == 2) {
                    cenario  = load_jpg("Imagens/Ranking/fundo_ranking.jpg", NULL);
                    fadeout (8);      
                    clear (buffer);
                    draw_sprite(buffer, cenario, 0,  0);  
                    PontoNomeJogador.ponto = composicaoPonto(informacaoPersonagem.moedas, experiencia_total);   
                    fadein (buffer, 2);
                    musica = 1;   
                }
                draw_sprite(buffer, cenario, 0,  0);  
                efeito_numeros (buffer, &animacao_numeros_aleotorios, &animacao_numeros_aleotorios_delay, 495, 413);
                rotina_ler_teclado(PontoNomeJogador.nome, &indice_vetor);
                sprintf(nome, "%s", PontoNomeJogador.nome);
                textout_ex(buffer, (FONT *)datFontes[0].dat, nome, 280, 330, makecol(0,0,0),-1 );
                if (animacao_numeros_aleotorios > 9) {
                    sprintf(pontos, "%i", PontoNomeJogador.ponto);
                    textout_ex(buffer, (FONT *)datFontes[0].dat, pontos, 495, 408, makecol(0,0,0),-1 );
                }
                draw_sprite(screen, buffer, 0, 0);
                clear (buffer);
                if ((key[KEY_ENTER]) || (indice_vetor == 14)) {
                    salvar_ranking (buffer, PontoNomeJogador.ponto, PontoNomeJogador.nome);
                    
                    // Zera Variáveis e Volta Menu Inicial //
                    mapa_atual                         = 0;
                    progresso_global                   = 0;
                    progresso                          = 0;
                    animacao_local                     = 0;
                    cena_animada                       = 0;
                    cena_animada_informacoes_iniciais  = 0;
                    musica                             = 0;
                    caso_colisao                       = 0; // Através dessa variável recebo o retorno da fundação detectarColisao, que cria um quadradro imaginário para haver colisão.
                    caso_colisao_sprite                = 0; // Através dessa variável recebo o retorno da função detectarColisaoSprite, que cria um quadradro imaginário em que qunado há colisão o Npc simplesmente para de andar (como um sensor)
                    caso_colisao_nociva                = 0;
                    opcao                              = 0;
                    velocidade_tempo;
                    comparador_tempo;
                    velocidade_fps                     = 0;
                    posicao_tutorial                   = 0;   
                    teste_efeito_nuvem                 = 0;
                    altura_nuvem_1                     = 0;
                    srand(time(NULL));
                    altura_nuvem_2                     = 1 + (int)( 550.0 * rand() / ( RAND_MAX + 1.0 ) );
                    cont                               = 0;
                    interacao                          = 0;
                    efeito                             = 0;
                    efeito_sonoro                      = 0;
                    cont_destruir_x                    = 0;
                    cont_destruir_y                    = 0;
                        
                    mini_game_lado_quadra_jogador        = 0;
                    mini_game_ponto_jogador              = 0;
    
                    mini_game_lado_quadra_adversario     = 0;
                    mini_game_ponto_adversario           = 0;
    
                    mini_game_corrida_resultado          = 0;
                    mini_game_corrida_nivel              = 0;
    
                    mini_game_pergunta_resposta_opcao    = 0;
                    mini_game_pergunta_resposta_pergunta = 0;
                    mini_game_pergunta_resposta_ponto    = 0;
                    
                    entrar               = 1;
                    entrar_2             = 0;
                    entrar_3             = 0;
                    entrar_4             = 0;
                    entrar_5             = 0;
                    
                    introducao_posicao   = 0;
                    
                    audio_fundo = load_midi("Audios/Fundo/musica_abertura.mid");
                    
                    informacaoPersonagem.x                             =   0;
                    informacaoPersonagem.y                             =   0;
                    informacaoPersonagem.lado                          =   0;
                    informacaoPersonagem.animacao                      =   0;
                    informacaoPersonagem.terreno                       =   TERRENO_NORMAL;
                    informacaoPersonagem.largura                       =   informacaoPersonagem.x + SPRITE_LARGURA;
                    informacaoPersonagem.altura                        =   informacaoPersonagem.y + SPRITE_ALTURA;
                    informacaoPersonagem.vigor                         =   6;
                    informacaoPersonagem.energia                       =   3;
                    informacaoPersonagem.face [0]                      =   load_bitmap ("Imagens/Personagens/Principal/Faces/face_joao_0.tga", NULL);
                    informacaoPersonagem.face [1]                      =   load_bitmap ("Imagens/Personagens/Principal/Faces/face_joao_1.tga", NULL);
                    informacaoPersonagem.ataque1 [0]                   =   load_bitmap ("Imagens/Personagens/Principal/Ataque1/bola_0.bmp", NULL);
                    informacaoPersonagem.ataque1 [1]                   =   load_bitmap ("Imagens/Personagens/Principal/Ataque1/bola_1.bmp", NULL);
                    informacaoPersonagem.ataque1 [2]                   =   load_bitmap ("Imagens/Personagens/Principal/Ataque1/bola_2.bmp", NULL);
                    informacaoPersonagem.moedas                        =   10;
                    informacaoPersonagem.nivel                         =   1;
                    informacaoPersonagem.habilidade1                   =   0;
                    informacaoPersonagem.experiencia_atual             =   0;
                    informacaoPersonagem.experiencia_proximo_nivel     =   50 * informacaoPersonagem.nivel;
                    informacaoPersonagem.experiencia_atual_porcentagem =   (informacaoPersonagem.experiencia_atual * 100) / informacaoPersonagem.experiencia_proximo_nivel;
    
                    interacaoBau1.x                     = 0;
                    interacaoBau1.y                     = 0;
                    interacaoBau1.estado                = 0;
                    interacaoBau1.animacao              = 0;
                    interacaoBau1.animacao_delay        = 0;
                    interacaoBau1.animacao_brilho       = 0;
                    interacaoBau1.animacao_brilho_delay = 0;
                    interacaoBau1.recompensaHabilidade  = 1;
                    interacaoBau1.recompensaVigor       = 0;
                    
                    // Informações sobre o jogo de carta //
                    informacaoJogoCarta1.ComparaId[0] = 0;
                    informacaoJogoCarta1.ComparaId[1] = 0;
                    informacaoJogoCarta1.x            = 0;
                    informacaoJogoCarta1.y            = 0;
                    informacaoJogoCarta1.C1           = 0;
                    informacaoJogoCarta1.C2           = 0;
                    informacaoJogoCarta1.L1           = 0;
                    informacaoJogoCarta1.L2           = 0;
                    informacaoJogoCarta1.estadoClique = 0;
                    informacaoJogoCarta1.Ponto        = 0;
                    informacaoJogoCarta1.colisao      = 0;
                    informacaoJogoCarta1.contClique   = 0;
                    
                    // Zera Animaçoes //
                    animacao_personagem_delay                  = 0;
                    animacao_npc_delay                         = 0;
                    animacao_vespa_delay                       = 0;
    
                    animacao_menu_abrindo                      = 0;
                    animacao_menu_abrindo_audio                = 0;
    
                    animacao_pressione_enter                   = 0;
                    animacao_pressione_enter_delay             = 0;
    
                    animacao_bola                              = 0;
                    animacao_bola_delay                        = 0;
    
                    animacao_ceu_1_parallax_delay              = 0;
                    animacao_ceu_1_parallax                    = 0;
    
                    animacao_ceu_2_parallax_delay              = 0;
                    animacao_ceu_2_parallax                    = 0;
    
                    animacao_tutorial_parallax                 = 0;
                    animacao_parallax_quem_somos               = 0;
    
                    animacao_choro                             = 0;
                    animacao_choro_delay                       = 0;
    
                    animacao_status                            = 0;
                    animacao_status_delay                      = 0;
    
                    animacao_chuva_noite                       = 0;
                    animacao_chuva_noite_delay                 = 0;
    
                    animacao_efeito_ataque                     = 0;
                    animacao_efeito_ataque_2                   = 0;
    
                    animacao_relampago                         = 0;
                    animacao_relampago_delay                   = 0;  
    
                    animacao_fogo [4];
                    animacao_fogo_delay [4];
    
                    animacao_luz_poste                         = 0;
                    animacao_luz_poste_delay                   = 0;
    
                    animacao_balao                             = 0;
                    animacao_balao_delay                       = 0; 
    
                    animacao_subiu_nivel                       = 21;
                    animacao_subiu_nivel_delay                 = 0;
    
                    animacao_torcedora [2];         
                    animacao_torcedora_delay [2];
                    
                    animacao_torcedora [0]                         = 0;
                    animacao_torcedora [1]                         = 0; 
                    animacao_torcedora_delay [0]                   = 0;
                    animacao_torcedora_delay [1]                   = 5;
    
                    jogadores_direita_ginasio                  = 0;
                    jogadores_direita_ginasio_delay            = 0;
                    jogadores_esquerda_ginasio                 = 0;
                    jogadores_esquerda_ginasio_delay           = 0;
    
                    animacao_agua_1                            = 0;   
                    animacao_agua_1_delay                      = 0;
                    animacao_agua_2                            = 0;   
                    animacao_agua_2_delay                      = 0;
    
                    animacao_1_sombra_nuvem                    = 0;
                    animacao_1_sombra_nuvem_delay              = 0;
                    animacao_2_sombra_nuvem                    = 0;
                    animacao_2_sombra_nuvem_delay              = 0;
                    animacao_3_sombra_nuvem                    = 0;
                    animacao_3_sombra_nuvem_delay              = 0;
    
                    animacao_tecla_enter_pulsando              = 0;
                    animacao_tecla_enter_pulsando_delay        = 0;
    
                    animacao_tecla_esc_pulsando                = 0;
                    animacao_tecla_esc_pulsando_delay          = 0;
    
                    animacao_moeda                             = 0;
                    animacao_moeda_delay                       = 0;
    
                    animacao_ganha_habilidade                  = 0;
                    animacao_ganha_habilidade_delay            = 0;
    
                    animacao_habilidade1                       = 0;
                    animacao_habilidade1_delay                 = 0;
    
                    animacao_contagem_regressiva               = 0;
                    animacao_contagem_regressiva_delay         = 0;
    
                    animacao_mini_game_corrida_resultado       = 0;
                    animacao_mini_game_corrida_resultado_delay = 0;
    
                    delay_ver_carta                            = 0;
                    posicao_x_efeito_carta_selecionada         = 0;
                    posicao_y_efeito_carta_selecionada         = 0;
                    animacao_carta_selecionada                 = 9;
                    animacao_carta_selecionada_delay           = 0;
    
                    animacao_ponto_positivo                    = 11;
                    animacao_ponto_positivo_delay              = 0;
    
                    animacao_ponto_negativo                    = 11;
                    animacao_ponto_negativo_delay              = 0;
    
                    animacao_cursor_pergunta_resposta          = 0;
                    animacao_cursor_pergunta_resposta_delay    = 0;
    
                    animacao_acerto_esquerda                   = 16;
                    animacao_acerto_esquerda_delay             = 0;
    
                    animacao_acerto_direita                    = 16;
                    animacao_acerto_direita_delay              = 0;
    
                    animacao_erro_esquerda                     = 16;
                    animacao_erro_esquerda_delay               = 0;
    
                    animacao_erro_direita                      = 16;
                    animacao_erro_direita_delay                = 0;
    
                    animacao_texto_sonho                       = 11;
                    animacao_texto_sonho_delay                 = 0;
                    
                    indice_vetor                               = 0;
                    
                    for (cont_destruir_x = 0; cont_destruir_x <4; cont_destruir_x ++) {
                        for (cont_destruir_y = 0; cont_destruir_y < 4; cont_destruir_y ++) {
                            VetCartas [cont_destruir_x] [cont_destruir_y].estado = 0;
                        }
                    }
                    
                    PontoNomeJogador.ponto = 0;
                    strcpy (PontoNomeJogador.nome,"");
                    
                    fadeout (2);    
                }       
            }
//  ============================================================================================ MINI GAME PERGUNTA E RESPOSTA =================================================================================================== //
            if (mapa_atual == 8) {
                if (musica == 1) {
                    fadeout (8);      
                    clear (buffer);
                    cenario  = load_jpg("Imagens/MiniGames/PerguntaResposta/Fundo/Fundo_Pergunta_Resposta.jpg", NULL);
                    draw_sprite(buffer, cenario, 0,  0);
                    jogo_pergunta_resposta (buffer, &mini_game_pergunta_resposta_opcao, &mini_game_pergunta_resposta_pergunta, &mini_game_pergunta_resposta_ponto, &animacao_acerto_esquerda, &animacao_acerto_esquerda_delay, &animacao_acerto_direita, &animacao_acerto_direita_delay, &animacao_erro_esquerda, &animacao_erro_esquerda_delay, &animacao_erro_direita, &animacao_erro_direita_delay,  &animacao_cursor_pergunta_resposta, &animacao_cursor_pergunta_resposta_delay, &animacao_ponto_positivo, &animacao_ponto_positivo_delay, &animacao_ponto_negativo, &animacao_ponto_negativo_delay);
                    jogo_pergunta_resposta_pontuacao (buffer, mini_game_pergunta_resposta_ponto);
                    fadein (buffer, 8);
                    musica = 2;             
                }
                draw_sprite(buffer, cenario, 0,  0);
                               
                jogo_pergunta_resposta_pontuacao (buffer, mini_game_pergunta_resposta_ponto);
                jogo_pergunta_resposta (buffer, &mini_game_pergunta_resposta_opcao, &mini_game_pergunta_resposta_pergunta, &mini_game_pergunta_resposta_ponto, &animacao_acerto_esquerda, &animacao_acerto_esquerda_delay, &animacao_acerto_direita, &animacao_acerto_direita_delay, &animacao_erro_esquerda, &animacao_erro_esquerda_delay, &animacao_erro_direita, &animacao_erro_direita_delay,  &animacao_cursor_pergunta_resposta, &animacao_cursor_pergunta_resposta_delay, &animacao_ponto_positivo, &animacao_ponto_positivo_delay, &animacao_ponto_negativo, &animacao_ponto_negativo_delay);
                
                // Avança Pergunta //
               if ((((animacao_acerto_esquerda == 15) || (animacao_acerto_direita == 15) || (animacao_erro_esquerda == 15) || (animacao_erro_direita == 15)))) {
                   mini_game_pergunta_resposta_pergunta = mini_game_pergunta_resposta_pergunta + 1;
                   musica = 1;
               }

               if (mini_game_pergunta_resposta_pergunta > 4) {
                   mapa_atual = 4;
                   musica = 1;
                   cena_animada = 6;
                   progresso = 1;
                        
                   informacaoPersonagem.moedas = (informacaoPersonagem.moedas + (10 * mini_game_pergunta_resposta_ponto));
                        
                   informacaoPersonagem.x    = 420;
                   informacaoPersonagem.y    = 460;
                   informacaoPersonagem.lado = 0;
                        
                   informacaoRoberto.x       =  650;
                   informacaoRoberto.y       =  460;
                   informacaoRoberto.lado    =  3;
               }
                              
               //Abre Menu 
               if (opcao == 0) {
                   if (key[KEY_ESC]) {                                                                                                                                                                                                                                                                                                                                                                        
                       opcao = 1;
                       play_sample (audio_efeito [3], 500, 128, 1000, 0);
                   }
               }
                    
                    
               if (opcao != 0) {
                   opcao = pausa_menu (buffer, opcao, &animacao_bola, &animacao_bola_delay);        
               }
                
                draw_sprite (screen, buffer, 0, 0);  
                clear (buffer);
            }


//  ============================================================================================== VILA CHOVENDO MAPA 7 ========================================================================================================== //
            if (mapa_atual == 7) {
                // Load dos Sprites que serão usados neste mapa //
                // Vespa //
                vespa [0][0] = load_bitmap("Imagens/Personagens/Vespa/frente61.bmp",NULL);
                vespa [0][1] = load_bitmap("Imagens/Personagens/Vespa/frente62.bmp",NULL);
                vespa [0][2] = load_bitmap("Imagens/Personagens/Vespa/frente63.bmp",NULL);
                vespa [0][3] = load_bitmap("Imagens/Personagens/Vespa/frente64.bmp",NULL);
    
                vespa [1][0] = load_bitmap("Imagens/Personagens/Vespa/direita61.bmp",NULL);
                vespa [1][1] = load_bitmap("Imagens/Personagens/Vespa/direita62.bmp",NULL);
                vespa [1][2] = load_bitmap("Imagens/Personagens/Vespa/direita63.bmp",NULL);
                vespa [1][3] = load_bitmap("Imagens/Personagens/Vespa/direita64.bmp",NULL);
        
                vespa [2][0] = load_bitmap("Imagens/Personagens/Vespa/costas61.bmp",NULL);
                vespa [2][1] = load_bitmap("Imagens/Personagens/Vespa/costas62.bmp",NULL);
                vespa [2][2] = load_bitmap("Imagens/Personagens/Vespa/costas63.bmp",NULL);
                vespa [2][3] = load_bitmap("Imagens/Personagens/Vespa/costas64.bmp",NULL);
    
                vespa [3][0] = load_bitmap("Imagens/Personagens/Vespa/esquerda61.bmp",NULL);
                vespa [3][1] = load_bitmap("Imagens/Personagens/Vespa/esquerda62.bmp",NULL);
                vespa [3][2] = load_bitmap("Imagens/Personagens/Vespa/esquerda63.bmp",NULL);
                vespa [3][3] = load_bitmap("Imagens/Personagens/Vespa/esquerda64.bmp",NULL);
                    
                    
                // Portas //
                porta [0] = load_bitmap("Imagens/EstilosCenarios/Objetos/Portas/porta_0.bmp",NULL);
                porta [1] = load_bitmap("Imagens/EstilosCenarios/Objetos/Portas/porta_2.bmp",NULL);
                
                portao_ginasio [0] = load_bitmap("Imagens/EstilosCenarios/Objetos/Portas/portao_0.jpg",NULL);
                portao_ginasio [1] = load_bitmap("Imagens/EstilosCenarios/Objetos/Portas/portao_2.jpg",NULL);
                 
                    if (musica == 1) {                               
                        // Localização Inicial dos Inimigos Mapa Vila //
                        informacaoVespa1.x                 =  120;             
                        informacaoVespa1.y                 =  300;
                        informacaoVespa1.vigor             =  1;
                        informacaoVespa1.loot              =  1;
                        informacaoVespa1.obter_experiencia =  0;
                    
                        informacaoVespa2.x                 =  530;             
                        informacaoVespa2.y                 =  390;                   
                        informacaoVespa2.vigor             =  1;
                        informacaoVespa2.loot              =  1;
                        informacaoVespa2.obter_experiencia =  0;
                    
                        // Efeito de Fadeout e Limpa Tela, carregando a imagem referente ao mapa
                        fadeout (8);      
                        clear (buffer);
                        cenario = load_jpg("Imagens/EstilosCenarios/novo_cenario_principal_noite.jpg",NULL);
                                                           
                        // Desenho das Primitivas do Jogo //
                        draw_sprite(buffer, cenario, 0,  0);
                        draw_sprite (buffer, porta [0], 160, 131);
                        draw_sprite (buffer, portao_ginasio [0], 543, 191); 
                    
                        draw_sprite(buffer, personagem [informacaoPersonagem.lado][informacaoPersonagem.animacao], informacaoPersonagem.x, informacaoPersonagem.y);
                        if (informacaoVespa1.vigor > 0) {
                            draw_sprite (buffer, vespa [informacaoVespa1.lado][informacaoVespa1.animacao], informacaoVespa1.x, informacaoVespa1.y);
                        }
                    
                        if (informacaoVespa2.vigor > 0) {
                            draw_sprite (buffer, vespa [informacaoVespa2.lado][informacaoVespa2.animacao], informacaoVespa2.x, informacaoVespa2.y);
                        }
                        // Efeitos //
                        efeito_agua (buffer, 190, 440, &animacao_agua_1, &animacao_agua_1_delay, &animacao_agua_2, &animacao_agua_2_delay);
                        efeito_chuva_noite (buffer, 0, 0, &animacao_chuva_noite, &animacao_chuva_noite_delay);
                        efeito_fogo (buffer, 513, 210, &animacao_fogo [0], &animacao_fogo_delay [0]);
                        efeito_fogo (buffer, 610, 210, &animacao_fogo [1], &animacao_fogo_delay [1]);
                        efeito_luz_poste (buffer, 377, 425, &animacao_luz_poste, &animacao_luz_poste_delay); 
                        efeito_luz_poste (buffer, 90, 425, &animacao_luz_poste, &animacao_luz_poste_delay);
                        efeito_barra_de_status_personagem (buffer, informacaoPersonagem.vigor, informacaoPersonagem.energia, &animacao_status, &animacao_status_delay, informacaoPersonagem.moedas, datFontes, informacaoPersonagem.experiencia_atual_porcentagem, informacaoPersonagem.nivel);          
                        
                        // Desenhos as habilidades da barra de habilidades //
                        if (informacaoPersonagem.habilidade1 == 1) efeito_habilidade_1_ativa (buffer, 5 + 2, 120 + 2, &animacao_habilidade1, &animacao_habilidade1_delay);
                                        
                    
                        // Efeitos de Fadein utilizando as primitivas desenhadas no buffer anteriormente //
                        fadein (buffer, 8);                                                  
                        musica = 2;
                        play_sample (audio_efeito [7], 200, 128, 1000, 1);                         
                    } 
                    
                    
                    
                    // Atualiza Nivel do Personagem Caso Evolua //
                    if (informacaoPersonagem.experiencia_atual >= informacaoPersonagem.experiencia_proximo_nivel) {
                        if (informacaoPersonagem.nivel != 99) {
                            informacaoPersonagem.nivel                     = informacaoPersonagem.nivel + 1;
                            informacaoPersonagem.experiencia_atual         = informacaoPersonagem.experiencia_atual - informacaoPersonagem.experiencia_proximo_nivel; 
                            informacaoPersonagem.experiencia_proximo_nivel = informacaoPersonagem.experiencia_proximo_nivel * informacaoPersonagem.nivel;
                            informacaoPersonagem.vigor                     = 6;
                            animacao_subiu_nivel                           = 0;
                        }    
                    }
                    
                    // Atualiza Porcentagem de Experiência do Personagem //
                    informacaoPersonagem.experiencia_atual_porcentagem = (informacaoPersonagem.experiencia_atual * 100) / informacaoPersonagem.experiencia_proximo_nivel;

                    // Atualiza Largura e Altura do Personagem Principal //
                    informacaoPersonagem.largura = informacaoPersonagem.x + SPRITE_LARGURA;
                    informacaoPersonagem.altura  = informacaoPersonagem.y + SPRITE_ALTURA;
            
                    // Atualiza Largura e Altura dos Inimigos //
                    informacaoVespa1.largura = informacaoVespa1.x + SPRITE_NPC_LARGURA;
                    informacaoVespa1.altura  = informacaoVespa1.y + SPRITE_NPC_ALTURA;
                
                    informacaoVespa2.largura = informacaoVespa2.x + SPRITE_NPC_LARGURA;
                    informacaoVespa2.altura  = informacaoVespa2.y + SPRITE_NPC_ALTURA;
                
                    // Atualiza Informação sobre Ataque do Personagem //
                    informacaoBola.x = informacaoPersonagem.x + 10;
                    informacaoBola.y = informacaoPersonagem.y + 25;       
            
                    // Testes de Colisões Mapa Cidade//            
                    // Toda Parte Esquerda //
                    
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 15, 0, 25, 600, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                
                    // Toda Parte Baixa //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 65, 545, 800, 600, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    
                    // Com árvores Sáida da Direita //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 775, 325, 800, 410, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    
                    // Para Não Deixar Sair Pela Direita //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 800, 410, 800, 545, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                
                    // Parte Esquerda do Ginásio //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 325, 0, 505, 310, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                
                    // Parte Direita do Ginásio //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 650, 0, 800, 310, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                
                    // Restante do Ginásio
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 510, 0, 645, 220, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                
                    // Dois Pedestais com Fogo //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 510, 230, 535, 255, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 620, 230, 645, 255, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                
                    // Com Cerca e Plantas de Cima da Casa //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 30, 0, 150, 160, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 140, 0, 190, 130, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 200, 0, 220, 160, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                
                    // Restante das Plantas, Arvores e Madeiras da Direita //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 225, 0, 320, 30, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 295, 60, 320, 220, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 30, 230, 145, 215, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 240, 230, 290, 215, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                
                    // Chafariz e Mesas da Praça e Postes //
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 145, 525, 435, 545, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 170, 420, 410, 560, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 82, 445, 85, 480, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    caso_colisao = detectarColisao (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 40, 465, 110, 467, informacaoPersonagem.terreno, informacaoPersonagem.lado, &informacaoPersonagem.animacao);
                    
                    
                    // Com Inimigos //
                    if (informacaoVespa1.vigor > 0) {
                        caso_colisao_nociva = detectarColisaoNociva(&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, informacaoPersonagem.lado, (informacaoVespa1.x + 12), (informacaoVespa1.y + 5), (informacaoVespa1.largura - 10), (informacaoVespa1.altura - 10), informacaoPersonagem.terreno, &informacaoPersonagem.animacao, &informacaoPersonagem.vigor); 
                    }
                
                    if (informacaoVespa2.vigor > 0) {
                        caso_colisao_nociva = detectarColisaoNociva(&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, informacaoPersonagem.lado, (informacaoVespa2.x + 12), (informacaoVespa2.y + 5), (informacaoVespa2.largura - 10), (informacaoVespa2.altura - 10), informacaoPersonagem.terreno, &informacaoPersonagem.animacao, &informacaoPersonagem.vigor); 
                    }
                
                    // Para Mudar Cenário //
                    detectarColisaoEntrarSair(&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.altura, &informacaoPersonagem.largura, 140, 20, 190, 140, &mapa_atual, 2); //Ultimos dois parametros referem-se ao mapa atual e o mapa destino respectivamente.
 
                    // Desenhos em Variaveis //
                    // Desenha Cenário no Buffer //
                    draw_sprite(buffer, cenario, 0,  0);
                
                    // Abre Porta Casa//
                    if (mapa_atual == 2) {
                       clear (buffer);
                       draw_sprite(buffer, cenario, 0,  0);
                       draw_sprite (buffer, porta [1], 160, 131);
                       play_sample (audio_efeito [4], 500, 128, 1000, 0);
                       musica = 1;
                    } else {
                        draw_sprite (buffer, porta [0], 160, 131);
                    }
                    
                    // Abre Porta Ginásio //
                    if (mapa_atual == 4) {
                        clear (buffer);
                        draw_sprite(buffer, cenario, 0,  0);
                        draw_sprite (buffer, portao_ginasio [1], 543, 191);
                        draw_sprite (buffer, porta [0], 160, 131);
                        play_sample (audio_efeito [4], 500, 128, 1000, 0);
                        musica = 1;
                    } else {
                        draw_sprite (buffer, portao_ginasio [0], 543, 191);
                    }
                    
                
                    // Desenha Inimigos  e Itens Animados //
                    if (informacaoVespa1.vigor > 0) {
                        draw_sprite(buffer, vespa [informacaoVespa1.lado][informacaoVespa1.animacao], informacaoVespa1.x, informacaoVespa1.y);
                    }
                
                    if (informacaoVespa2.vigor > 0) {
                        draw_sprite(buffer, vespa [informacaoVespa2.lado][informacaoVespa2.animacao], informacaoVespa2.x, informacaoVespa2.y);
                    }
                
                    // Ataque da Bola  desenhada Atras do Sprite //
                    if (informacaoPersonagem.habilidade1 == 1) { 
                        if (informacaoPersonagem.lado == 2) {
                            if (informacaoBola.delayanimacao <= 0) {
                                efeito_ataque (buffer, &informacaoBola.x, &informacaoBola.y, &informacaoBola.delayanimacao, &informacaoPersonagem.energia, informacaoPersonagem.lado, &informacaoPersonagem.animacao, informacaoPersonagem.ataque1, &animacao_efeito_ataque, &animacao_efeito_ataque_2);
                                informacaoPersonagem.energia = informacaoPersonagem.energia + 1;
                            } else if (informacaoBola.delayanimacao > 0) {
                            efeito_ataque (buffer, &informacaoBola.x, &informacaoBola.y, &informacaoBola.delayanimacao, &informacaoPersonagem.energia, informacaoPersonagem.lado, &informacaoPersonagem.animacao, informacaoPersonagem.ataque1, &animacao_efeito_ataque, &animacao_efeito_ataque_2);
                            }
                            if (informacaoPersonagem.energia  > 3) {
                                informacaoPersonagem.energia = 3;
                            }
                         }
                    }               
              
                   // Movimento Inimigos //
                   // Vespa 1 //
                   if (informacaoVespa1.vigor > 0) {
                         movimentarSpriteAutomaticamente(&informacaoVespa1.x, &informacaoVespa1.y, &informacaoVespa1.lado, &informacaoVespa1.animacao, &informacaoVespa1.delayanimacao, informacaoVespa1.terreno, 2, 120, 200, 0, &animacao_vespa_delay, informacaoVespa1.velocidade_animacao);
                   } else {
                       if (informacaoVespa1.obter_experiencia == 0) {
                            informacaoPersonagem.experiencia_atual = informacaoPersonagem.experiencia_atual + informacaoVespa1.experiencia_atual; 
                            informacaoVespa1.obter_experiencia = 1;
                            experiencia_total = experiencia_total + informacaoVespa1.experiencia_atual;
                       }
                       if (informacaoVespa1.loot == 1) {
                            informacaoVespa1.loot = detectarColisaoMoeda(buffer, informacaoPersonagem.x, informacaoPersonagem.y, informacaoPersonagem.altura, informacaoPersonagem.largura, (informacaoVespa1.x + 12), (informacaoVespa1.y + 5), (informacaoVespa1.largura - 10), (informacaoVespa1.altura - 10), &informacaoPersonagem.moedas, informacaoVespa1.moedas);  
                            efeito_moeda(buffer, informacaoVespa1.x + 10, informacaoVespa1.y + 10, &animacao_moeda, &animacao_moeda_delay);
                        
                       }      
                   }
                
                   // Vespa 2 //
                   if (informacaoVespa2.vigor > 0) {
                       movimentarSpriteAutomaticamente(&informacaoVespa2.x, &informacaoVespa2.y, &informacaoVespa2.lado, &informacaoVespa2.animacao, &informacaoVespa2.delayanimacao, informacaoVespa2.terreno, 1, 390, 450, 0, &animacao_vespa_delay, informacaoVespa2.velocidade_animacao);
                   } else {
                       if (informacaoVespa2.obter_experiencia == 0) {
                           informacaoPersonagem.experiencia_atual = informacaoPersonagem.experiencia_atual + informacaoVespa2.experiencia_atual; 
                           informacaoVespa2.obter_experiencia = 1;
                           experiencia_total = experiencia_total + informacaoVespa1.experiencia_atual;
                       }
                       if (informacaoVespa2.loot == 1) {
                           informacaoVespa2.loot = detectarColisaoMoeda(buffer, informacaoPersonagem.x, informacaoPersonagem.y, informacaoPersonagem.altura, informacaoPersonagem.largura, (informacaoVespa2.x + 12), (informacaoVespa2.y + 5), (informacaoVespa2.largura - 10), (informacaoVespa2.altura - 10), &informacaoPersonagem.moedas, informacaoVespa2.moedas);  
                           efeito_moeda(buffer, informacaoVespa2.x + 10, informacaoVespa2.y + 10, &animacao_moeda, &animacao_moeda_delay);
                       }
                   }
                   
                   // Desenha personagem e NPC's testando se estão em cima ou embaixo um do outro // 
                   draw_sprite(buffer, personagem [informacaoPersonagem.lado][informacaoPersonagem.animacao], informacaoPersonagem.x, informacaoPersonagem.y);
 
                                                                                                                                                     
                    // Ataque da Bola  desenhada na Frente do Sprite //
                    if (informacaoPersonagem.habilidade1 == 1) {
                        if (informacaoPersonagem.lado != 2) {
                            if (informacaoBola.delayanimacao <= 0) {
                                efeito_ataque (buffer, &informacaoBola.x, &informacaoBola.y, &informacaoBola.delayanimacao, &informacaoPersonagem.energia, informacaoPersonagem.lado, &informacaoPersonagem.animacao, informacaoPersonagem.ataque1, &animacao_efeito_ataque, &animacao_efeito_ataque_2);
                                informacaoPersonagem.energia = informacaoPersonagem.energia + 1;
                            } else if (informacaoBola.delayanimacao > 0) {
                                efeito_ataque (buffer, &informacaoBola.x, &informacaoBola.y, &informacaoBola.delayanimacao, &informacaoPersonagem.energia, informacaoPersonagem.lado, &informacaoPersonagem.animacao, informacaoPersonagem.ataque1, &animacao_efeito_ataque, &animacao_efeito_ataque_2);
                            }
                            if (informacaoPersonagem.energia  > 3) {
                                informacaoPersonagem.energia = 3;
                            }
                        }
                    } 
                    informacaoBola.delayanimacao = informacaoBola.delayanimacao - 1;  
                    
                    // Atualiza Altura da Bola após Mudança das coordenadas X e Y //
                    informacaoBola.largura = informacaoBola.x + SPRITE_LARGURA;
                    informacaoBola.altura  = informacaoBola.y + SPRITE_ALTURA;
                
                
                    // Colisão dos Ataques com os monstros // 
                    if (informacaoVespa1.vigor > 0) {
                        detectarColisaoAtaquePersonagem(buffer, &informacaoBola.x, &informacaoBola.y, &informacaoBola.altura, &informacaoBola.largura, informacaoBola.lado, (informacaoVespa1.x + 30), (informacaoVespa1.y + 40), informacaoVespa1.largura - 10, informacaoVespa1.altura + 10, informacaoBola.terreno, &informacaoBola.animacao, &informacaoVespa1.vigor); 
                    }
                
                    if (informacaoVespa2.vigor > 0) {
                        detectarColisaoAtaquePersonagem(buffer, &informacaoBola.x, &informacaoBola.y, &informacaoBola.altura, &informacaoBola.largura, informacaoBola.lado, (informacaoVespa2.x + 30), (informacaoVespa2.y + 40), informacaoVespa2.largura - 10, informacaoVespa2.altura + 10, informacaoBola.terreno, &informacaoBola.animacao, &informacaoVespa2.vigor); 
                    }
                    
                    
                    // Testa Posição do Personagem Caso Mude de Cenário //
                    if (mapa_atual == 2){
                        informacaoPersonagem.x = 640;
                        informacaoPersonagem.y = 500;
                    }
 
                    if (mapa_atual == 4){
                        informacaoPersonagem.x = 380;
                        informacaoPersonagem.y = 520;
                    }
                    
                    // Desenha Animações //
                    efeito_agua (buffer, 190, 440, &animacao_agua_1, &animacao_agua_1_delay, &animacao_agua_2, &animacao_agua_2_delay);
                    efeito_chuva_noite (buffer, 0, 0, &animacao_chuva_noite, &animacao_chuva_noite_delay);
                    efeito_fogo (buffer, 513, 210, &animacao_fogo [0], &animacao_fogo_delay [0]);
                    efeito_fogo (buffer, 610, 210, &animacao_fogo [1], &animacao_fogo_delay [1]);
                    efeito_luz_poste (buffer, 377, 425, &animacao_luz_poste, &animacao_luz_poste_delay); 
                    efeito_luz_poste (buffer, 90, 425, &animacao_luz_poste, &animacao_luz_poste_delay);
                    efeito_relampago(buffer, &animacao_relampago, &animacao_relampago_delay);
                        
                    // Animacao Caso Suba de Nível //
                    if (animacao_subiu_nivel <= 20) {
                        efeito_subiu_nivel (buffer, informacaoPersonagem.x, informacaoPersonagem.y, &animacao_subiu_nivel, &animacao_subiu_nivel_delay); 
                    }
                    
                    // Desenha Barra de Status do Personagem// 
                    efeito_barra_de_status_personagem (buffer, informacaoPersonagem.vigor, informacaoPersonagem.energia, &animacao_status, &animacao_status_delay, informacaoPersonagem.moedas,  datFontes, informacaoPersonagem.experiencia_atual_porcentagem, informacaoPersonagem.nivel);
                    
                    // Desenhos as habilidades da barra de habilidades //
                    if (informacaoPersonagem.habilidade1 == 1) efeito_habilidade_1_ativa (buffer, 5 + 2, 120 + 2, &animacao_habilidade1, &animacao_habilidade1_delay);
                
                    // Movimento do Personagem // 
                    // Se não estiver em PAUSE, Ou sendo ATACADO, Ou ATACANDO // 
                    if ((informacaoBola.delayanimacao <= 0) &&  (opcao == 0)) {
                         movimentarJogador (&informacaoPersonagem.x, &informacaoPersonagem.y, &informacaoPersonagem.lado, &informacaoPersonagem.animacao, &informacaoPersonagem.terreno, &animacao_personagem_delay);
                    }
                
                    
                    if (opcao == 0) {
                        if (key[KEY_ESC]) {                              //Abre Menu                                                                                                                                                                                                                                                                                                                                           
                            opcao = 1;
                            play_sample (audio_efeito [3], 500, 128, 1000, 0);
                        }
                    }
                
                    if (opcao != 0) {
                        opcao = pausa_menu (buffer, opcao, &animacao_bola, &animacao_bola_delay);        
                    }
                    
                    if ((animacao_relampago == 4) && (animacao_relampago_delay == 0)) {
                        informacaoPersonagem.vigor = informacaoPersonagem.vigor - 1;
                    }
                    
                    if ((informacaoPersonagem.vigor <= 0)&& (animacao_relampago == 6)){
                        stop_sample (audio_efeito [7]);
                        clear (buffer);
                        draw_sprite(buffer, cenario, 0,  0);
                        draw_sprite (buffer, porta [0], 160, 131);
                        draw_sprite (buffer, portao_ginasio [0], 543, 191); 
                        if (informacaoVespa1.vigor > 0) {
                            draw_sprite(buffer, vespa [informacaoVespa1.lado][informacaoVespa1.animacao], informacaoVespa1.x, informacaoVespa1.y);
                        }
                        if (informacaoVespa2.vigor > 0) {
                            draw_sprite(buffer, vespa [informacaoVespa2.lado][informacaoVespa2.animacao], informacaoVespa2.x, informacaoVespa2.y);
                        }
                        draw_sprite(buffer, personagem_desmaiado, informacaoPersonagem.x , informacaoPersonagem.y);
                        efeito_agua (buffer, 190, 440, &animacao_agua_1, &animacao_agua_1_delay, &animacao_agua_2, &animacao_agua_2_delay);
                        efeito_chuva_noite (buffer, 0, 0, &animacao_chuva_noite, &animacao_chuva_noite_delay);
                        efeito_fogo (buffer, 513, 210, &animacao_fogo [0], &animacao_fogo_delay [0]);
                        efeito_fogo (buffer, 610, 210, &animacao_fogo [1], &animacao_fogo_delay [1]);
                        efeito_luz_poste (buffer, 377, 425, &animacao_luz_poste, &animacao_luz_poste_delay); 
                        efeito_luz_poste (buffer, 90, 425, &animacao_luz_poste, &animacao_luz_poste_delay);
                        efeito_relampago(buffer, &animacao_relampago, &animacao_relampago_delay);
                        
                        efeito_barra_de_status_personagem (buffer, informacaoPersonagem.vigor, informacaoPersonagem.energia, &animacao_status, &animacao_status_delay, informacaoPersonagem.moedas, datFontes, informacaoPersonagem.experiencia_atual_porcentagem, informacaoPersonagem.nivel); 
                        
                        // Desenhos as habilidades da barra de habilidades //
                        if (informacaoPersonagem.habilidade1 == 1) efeito_habilidade_1_ativa (buffer, 5 + 2, 120 + 2, &animacao_habilidade1, &animacao_habilidade1_delay);
                        
                        mapa_atual = 3;
                        musica = 3;
                    }
                    // Limpa Buffer //
                    draw_sprite(screen, buffer, 0, 0);
                    clear (buffer);
                // Destroi Imagens //
                for (cont_destruir_x = 0; cont_destruir_x != 4; cont_destruir_x++) {
                    for (cont_destruir_y = 0; cont_destruir_y != 4; cont_destruir_y++) {

                        destroy_bitmap (vespa [cont_destruir_x][cont_destruir_y]);
                    }
                }
                
                for (cont_destruir_x = 0; cont_destruir_x < 2; cont_destruir_x++) { 
                    destroy_bitmap (porta [cont_destruir_x]);
                    destroy_bitmap (portao_ginasio [cont_destruir_x]);    
                }                             
             } // FIM MAPA 7
             
             // =============================================================================================== TUTORIAL JOGO DA MEMÓRIA ================================================================================================ //
            if (mapa_atual == 11) {
                if (musica == 1) {
                    fadeout (8);     
                    clear (buffer);
                    efeito_tutorial_parallax (buffer, &animacao_tutorial_parallax);
                    tutorial_minigame_memoria (buffer, posicao_tutorial); 
                    fadein (buffer, 3);                                                      
                    musica = 2;     
                }
                efeito_tutorial_parallax (buffer, &animacao_tutorial_parallax);
                tutorial_minigame_memoria (buffer, posicao_tutorial);
                animacao_tecla_enter (buffer, 690, 410, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);  
                if (key[KEY_ENTER]) {
                    if (keypressed()) {
                       posicao_tutorial++;  
                    }
                    clear_keybuf();
                }
                
                if (posicao_tutorial > 4) {
                    mapa_atual = 6;
                    musica = 1;
                    posicao_tutorial = 0;
                } 
                
                draw_sprite(screen, buffer, 0, 0);
                clear (buffer);
            }
// ========================================================================================================================================================================================================================= //             
            if (mapa_atual == 10) {
                if (musica == 1) {
                    fadeout (8);     
                    clear (buffer);
                    play_sample (audio_efeito [7], 200, 128, 1000, 1);    
                    efeito_tutorial_parallax (buffer, &animacao_tutorial_parallax);
                    tutorial_chuva (buffer);
                    fadein (buffer, 3);   
                    stop_midi ();                                                      
                    musica = 2;     
                }
                efeito_tutorial_parallax (buffer, &animacao_tutorial_parallax);
                tutorial_chuva (buffer);
                animacao_tecla_enter (buffer, 690, 410, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);  
                if (key[KEY_ENTER]) {
                    if (keypressed()) {
                        mapa_atual = 7;
                        musica = 1;
                                                
                        // Localização Inicial do Jogador Mapa Vila
                        informacaoPersonagem.x    =  560;
                        informacaoPersonagem.y    =  225;
                        informacaoPersonagem.lado =  0;
                    }
                    clear_keybuf();
                }
                
                draw_sprite(screen, buffer, 0, 0);
                clear (buffer);
            }


// ================================================================================================ ANIMACAO DO SONHO ====================================================================================================== //
            if (mapa_atual == 9){
                // Carrega Sprites Ligeirinho //
                ligeirinho [0][0] = load_bitmap("Imagens/Personagens/Ligeirinho/frente_0.tga",NULL);
                ligeirinho [0][1] = load_bitmap("Imagens/Personagens/Ligeirinho/frente_1.tga",NULL);
                ligeirinho [0][2] = load_bitmap("Imagens/Personagens/Ligeirinho/frente_2.tga",NULL);
                ligeirinho [0][3] = load_bitmap("Imagens/Personagens/Ligeirinho/frente_3.tga",NULL);
    
                ligeirinho [1][0] = load_bitmap("Imagens/Personagens/Ligeirinho/direita_0.tga",NULL);
                ligeirinho [1][1] = load_bitmap("Imagens/Personagens/Ligeirinho/direita_1.tga",NULL);
                ligeirinho [1][2] = load_bitmap("Imagens/Personagens/Ligeirinho/direita_2.tga",NULL);
                ligeirinho [1][3] = load_bitmap("Imagens/Personagens/Ligeirinho/direita_3.tga",NULL);
        
                ligeirinho [2][0] = load_bitmap("Imagens/Personagens/Ligeirinho/costas_0.tga",NULL);
                ligeirinho [2][1] = load_bitmap("Imagens/Personagens/Ligeirinho/costas_1.tga",NULL);
                ligeirinho [2][2] = load_bitmap("Imagens/Personagens/Ligeirinho/costas_2.tga",NULL);
                ligeirinho [2][3] = load_bitmap("Imagens/Personagens/Ligeirinho/costas_3.tga",NULL);
    
                ligeirinho [3][0] = load_bitmap("Imagens/Personagens/Ligeirinho/esquerda_0.tga",NULL);
                ligeirinho [3][1] = load_bitmap("Imagens/Personagens/Ligeirinho/esquerda_1.tga",NULL);
                ligeirinho [3][2] = load_bitmap("Imagens/Personagens/Ligeirinho/esquerda_2.tga",NULL);
                ligeirinho [3][3] = load_bitmap("Imagens/Personagens/Ligeirinho/esquerda_3.tga",NULL);
                
                informacaoLigeirinho.face [0] = load_bitmap("Imagens/Personagens/Ligeirinho/Faces/face_ligeirinho_0.tga",NULL);
                
                // Carrega Sprites Inimigo //
                inimigo [0][0] = load_bitmap("Imagens/Personagens/Inimigo/frente_0.tga",NULL);
                inimigo [0][1] = load_bitmap("Imagens/Personagens/Inimigo/frente_1.tga",NULL);
                inimigo [0][2] = load_bitmap("Imagens/Personagens/Inimigo/frente_2.tga",NULL);
                inimigo [0][3] = load_bitmap("Imagens/Personagens/Inimigo/frente_3.tga",NULL);
    
                inimigo [1][0] = load_bitmap("Imagens/Personagens/Inimigo/direita_0.tga",NULL);
                inimigo [1][1] = load_bitmap("Imagens/Personagens/Inimigo/direita_1.tga",NULL);
                inimigo [1][2] = load_bitmap("Imagens/Personagens/Inimigo/direita_2.tga",NULL);
                inimigo [1][3] = load_bitmap("Imagens/Personagens/Inimigo/direita_3.tga",NULL);
        
                inimigo [2][0] = load_bitmap("Imagens/Personagens/Inimigo/costas_0.tga",NULL);
                inimigo [2][1] = load_bitmap("Imagens/Personagens/Inimigo/costas_1.tga",NULL);
                inimigo [2][2] = load_bitmap("Imagens/Personagens/Inimigo/costas_2.tga",NULL);
                inimigo [2][3] = load_bitmap("Imagens/Personagens/Inimigo/costas_3.tga",NULL);
    
                inimigo [3][0] = load_bitmap("Imagens/Personagens/Inimigo/esquerda_0.tga",NULL);
                inimigo [3][1] = load_bitmap("Imagens/Personagens/Inimigo/esquerda_1.tga",NULL);
                inimigo [3][2] = load_bitmap("Imagens/Personagens/Inimigo/esquerda_2.tga",NULL);
                inimigo [3][3] = load_bitmap("Imagens/Personagens/Inimigo/esquerda_3.tga",NULL);
                
                informacaoInimigo.face [0] = load_bitmap("Imagens/Personagens/Inimigo/Faces/face_inimigo_0.tga",NULL);
                informacaoInimigo.face [1] = load_bitmap("Imagens/Personagens/Inimigo/Faces/face_inimigo_1.tga",NULL);
                
                if (musica == 1) {
                    audio_fundo = load_midi("Audios/Fundo/musica_sonho.mid"); 
                    fadeout (2);
                    stop_sample (audio_efeito [7]); 
                    play_midi(audio_fundo, 1);      
                    
                    clear (buffer);
                    
                    efeito_estrelas_parallax (buffer, &animacao_tutorial_parallax);
                    efeito_texto_sonho (buffer, &animacao_texto_sonho, &animacao_texto_sonho_delay, 0, 0);
                    
                    fadein (buffer, 3);                                                         
                    musica = 2;
                    cena_animada = 0;                    
                }
                //Plano de Fundo Do Sonho //
                efeito_estrelas_parallax (buffer, &animacao_tutorial_parallax);
                
                // Primeira Parte do Sonho //
                if (cena_animada == 0) { 
                    efeito_texto_sonho (buffer, &animacao_texto_sonho, &animacao_texto_sonho_delay, 0, 0);
                    if (animacao_texto_sonho != 10) {
                        animacao_tecla_enter (buffer, 705, 480, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);  
                    } else {
                        cena_animada = 1;
                    }
                
                // Segunda Parte do Sonho //
                } else if (cena_animada == 1) {
                
                    if (musica == 2) {
                        // Localização Inicial dos Sprites //
                        informacaoLigeirinho.x        = 470;
                        informacaoLigeirinho.y        = 170;
                        informacaoLigeirinho.lado     = 3;
                        informacaoLigeirinho.animacao = 0;
                    
                        // Informação Iniciais do Mapa //
                        fadeout (5);
                        clear (buffer);
                        audio_fundo = load_midi("Audios/Fundo/musica_suspense.mid");
                        play_midi(audio_fundo, 1);   
                        efeito_estrelas_parallax (buffer, &animacao_tutorial_parallax);
                        cenario = load_bitmap("Imagens/EstilosCenarios/cenario_cativeiro.tga",NULL);
                        
                        set_alpha_blender();
                        draw_trans_sprite (buffer, cenario, 0, 0);
                        draw_trans_sprite(buffer, ligeirinho [informacaoLigeirinho.lado][informacaoLigeirinho.animacao], informacaoLigeirinho.x, informacaoLigeirinho.y);
                        
                        fadein (buffer, 3);
                        musica = 3;
                        cont = 0;                               
                    }
                    set_alpha_blender();
                    draw_trans_sprite (buffer, cenario, 0, 0);
                    draw_trans_sprite(buffer, ligeirinho [informacaoLigeirinho.lado][informacaoLigeirinho.animacao], informacaoLigeirinho.x, informacaoLigeirinho.y);
               
                    movimentarSpriteAutomaticamente(&informacaoLigeirinho.x, &informacaoLigeirinho.y, &informacaoLigeirinho.lado, &informacaoLigeirinho.animacao, &informacaoLigeirinho.delayanimacao, informacaoLigeirinho.terreno, 2, 410, 470, 0, &animacao_personagem_delay, informacaoLigeirinho.velocidade_animacao);   
                    
                    if (informacaoLigeirinho.x == 410) {
                        cont++;
                    }
                    
                    if (cont >=1) {
                        if (informacaoLigeirinho.posicao_conversa == 0)   {                                                                                                                                                                                                                              // 3º = coordenada da posicao Final da locomoção.
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoPersonagem.lado, fala_personagem [1], buffer, informacaoLigeirinho.face [0],"",                                                                                                      // 4º = Tempo de Espera
                                                                                                                                                  "",                                                                                                                               // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoLigeirinho.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                        } else if (informacaoLigeirinho.posicao_conversa == 1) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoPersonagem.lado, fala_personagem [1], buffer, informacaoLigeirinho.face [0],"Meu Deus, já não tenho vigor para continuar...",
                                                                                                                                                  "Eu devia ter escutado ela naquele dia...", 
                                                                                                                                                  "Se eu tivesse feito a escolha certa, minha",
                                                                                                                                                  "história poderia ter sido outra...", 
                                                                                                                                                  "Realmente... parece não haver nada que eu possa", datFontes, 2, &informacaoLigeirinho.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);    
                        } else if (informacaoLigeirinho.posicao_conversa == 2) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoPersonagem.lado, fala_personagem [1], buffer, informacaoLigeirinho.face [0],"fazer para sair deste buraco...",
                                                                                                                                                  "Estou fadado a viver nesse cativeiro...", 
                                                                                                                                                  "Tudo isso por culpa dessas pessoas",
                                                                                                                                                  "gananciosas que só pensam em dinheiro e não", 
                                                                                                                                                  "se importam com os sentimentos das pessoas...", datFontes, 3, &informacaoLigeirinho.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);    
                        } else if (informacaoLigeirinho.posicao_conversa == 3) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoPersonagem.lado, fala_personagem [1], buffer, informacaoLigeirinho.face [0],"fazer para sair deste buraco...",
                                                                                                                                                  "Estou fadado a viver nesse cativeiro...", 
                                                                                                                                                  "Tudo isso por culpa dessas pessoas",
                                                                                                                                                  "gananciosas que só pensam em dinheiro e não", 
                                                                                                                                                  "se importam com os sentimentos das pessoas...", datFontes, 0, &informacaoLigeirinho.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);    
                            
                            informacaoLigeirinho.posicao_conversa = 0;
                            cena_animada = 2;
                        }
                    }
                    
                // Terceira Cena Animada
                } else if (cena_animada == 2) {
                    if (musica == 3) {
                        informacaoInimigo.x        = 280;
                        informacaoInimigo.y        = 170;
                        informacaoInimigo.lado     = 1;
                        informacaoInimigo.animacao = 0;
                        musica = 2;
                    }
                    set_alpha_blender();
                    draw_trans_sprite (buffer, cenario, 0, 0);
                    draw_trans_sprite(buffer, ligeirinho [informacaoLigeirinho.lado][informacaoLigeirinho.animacao], informacaoLigeirinho.x, informacaoLigeirinho.y);
                    draw_trans_sprite(buffer, inimigo [informacaoInimigo.lado][informacaoInimigo.animacao], informacaoInimigo.x, informacaoInimigo.y);
    
                    movimentarSpriteAutomaticamente(&informacaoLigeirinho.x, &informacaoLigeirinho.y, &informacaoLigeirinho.lado, &informacaoLigeirinho.animacao, &informacaoLigeirinho.delayanimacao, informacaoLigeirinho.terreno, 2, 410, 470, 0, &animacao_personagem_delay, informacaoLigeirinho.velocidade_animacao);   
                    movimentarSpriteAutomaticamente(&informacaoInimigo.x, &informacaoInimigo.y, &informacaoInimigo.lado, &informacaoInimigo.animacao, &informacaoInimigo.delayanimacao, informacaoInimigo.terreno, 1, 170, 330, 0, &animacao_npc_delay, informacaoInimigo.velocidade_animacao);   
                    
                    if (informacaoInimigo.y == 330) {
                        cena_animada = 3;
                    }
                
                // Quarta Cena Animada
                } else if (cena_animada == 3) {
                    if (musica == 2) {
                        animacao_balao = 0;
                        musica = 3;
                    }
                    set_alpha_blender();
                    draw_trans_sprite (buffer, cenario, 0, 0);
                    draw_trans_sprite(buffer, ligeirinho [informacaoLigeirinho.lado][informacaoLigeirinho.animacao], informacaoLigeirinho.x, informacaoLigeirinho.y);
                    draw_trans_sprite(buffer, inimigo [informacaoInimigo.lado][informacaoInimigo.animacao], informacaoInimigo.x, informacaoInimigo.y);
                    
                    efeito_balao_nervoso(buffer, informacaoLigeirinho.x, informacaoLigeirinho.y, &animacao_balao, &animacao_balao_delay);
                    
                    movimentarSpriteAutomaticamente(&informacaoLigeirinho.x, &informacaoLigeirinho.y, &informacaoLigeirinho.lado, &informacaoLigeirinho.animacao, &informacaoLigeirinho.delayanimacao, informacaoLigeirinho.terreno, 2, 410, 470, 0, &animacao_personagem_delay, informacaoLigeirinho.velocidade_animacao);   
                    movimentarSpriteAutomaticamente(&informacaoInimigo.x, &informacaoInimigo.y, &informacaoInimigo.lado, &informacaoInimigo.animacao, &informacaoInimigo.delayanimacao, informacaoInimigo.terreno, 2, 280, informacaoLigeirinho.x, 0, &animacao_npc_delay, informacaoInimigo.velocidade_animacao);   
                    
                    if (informacaoInimigo.x == 410) {
                        cena_animada = 4;
                    }
                
                // Quinta Cena Animada //
                } else if (cena_animada == 4){ 
                    if (musica == 3) {
                        animacao_balao = 0;
                        informacaoInimigo.lado        = 2;
                        informacaoInimigo.animacao    = 2;
                        informacaoLigeirinho.lado     = 0;
                        informacaoLigeirinho.animacao = 0;;
                        musica = 2;
                    }
                    
                    set_alpha_blender();
                    draw_trans_sprite (buffer, cenario, 0, 0);
                    draw_trans_sprite(buffer, ligeirinho [informacaoLigeirinho.lado][informacaoLigeirinho.animacao], informacaoLigeirinho.x, informacaoLigeirinho.y);
                    draw_trans_sprite(buffer, inimigo [informacaoInimigo.lado][informacaoInimigo.animacao], informacaoInimigo.x, informacaoInimigo.y);
                    
                    efeito_balao_exclamacao(buffer, informacaoLigeirinho.x, informacaoLigeirinho.y, &animacao_balao, &animacao_balao_delay);
                    
                    if (informacaoLigeirinho.posicao_conversa == 0)   {                                                                                                                                                                                                                              // 3º = coordenada da posicao Final da locomoção.
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoPersonagem.lado, fala_personagem [1], buffer, informacaoInimigo.face [0],"",                                                                                                      // 4º = Tempo de Espera
                                                                                                                                                  "",                                                                                                                               // Ultimo parametro diz respeito a velocidade de animação, quanto menor, mais rápido.
                                                                                                                                                  "",                                                                                                                     
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 1, &informacaoLigeirinho.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);
                    } else if (informacaoLigeirinho.posicao_conversa == 1) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoPersonagem.lado, fala_personagem [1], buffer, informacaoInimigo.face [0],"Boa noite José, como você está meu amigo?",
                                                                                                                                                  "Ahh quer saber... não precisa nem responder...", 
                                                                                                                                                  "Da pra ver daqui que você está",
                                                                                                                                                  "esbanjando de saúde e felicidade não é?", 
                                                                                                                                                  "Também não é pra menos, com todo esse luxo...", datFontes, 2, &informacaoLigeirinho.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);    
                    } else if (informacaoLigeirinho.posicao_conversa == 2) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoPersonagem.lado, fala_personagem [1], buffer, informacaoLigeirinho.face [0],"Maldito! O que você ta fazendo aqui?",
                                                                                                                                                  "Já não basta ter me aprisionado nesse fim", 
                                                                                                                                                  "de mundo e ainda vem tirar sarro da minha cara!? ",
                                                                                                                                                  "Você...", 
                                                                                                                                                  "", datFontes, 3, &informacaoLigeirinho.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);    
                    } else if (informacaoLigeirinho.posicao_conversa == 3) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoPersonagem.lado, fala_personagem [1], buffer, informacaoInimigo.face [0],"Ei ei ei, calminha ae...",
                                                                                                                                                  "Eu venho todo educado conversar com você", 
                                                                                                                                                  "e é assim que você me trata? Ora essa...",
                                                                                                                                                  "Parece que você não aprendeu qual seu lugar", 
                                                                                                                                                  "ainda não é? Pois...", datFontes, 5, &informacaoLigeirinho.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);              
                    } else if (informacaoLigeirinho.posicao_conversa == 4) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoPersonagem.lado, fala_personagem [1], buffer, informacaoInimigo.face [0],"Ei ei ei, calminha ae...",
                                                                                                                                                  "Eu venho todo educado conversar com você", 
                                                                                                                                                  "e é assim que você me trata? Ora essa...",
                                                                                                                                                  "Parece que você não aprendeu qual seu lugar", 
                                                                                                                                                  "ainda não é? Pois...", datFontes, 4, &informacaoLigeirinho.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);    
                            
                            
                    } else if (informacaoLigeirinho.posicao_conversa == 5) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoPersonagem.lado, fala_personagem [1], buffer, informacaoInimigo.face [1],"Que tal se eu começar a dar bom",
                                                                                                                                                  "dia para sua família miserável também, hum?", 
                                                                                                                                                  "Acho que aquele garotinho iria adorar",
                                                                                                                                                  "bater uma bolinha comigo não é?", 
                                                                                                                                                  "", datFontes, 6, &informacaoLigeirinho.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);    
                            
                    } else if (informacaoLigeirinho.posicao_conversa == 6) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoPersonagem.lado, fala_personagem [1], buffer, informacaoLigeirinho.face [0],"Covarde! Não ouse chegar perto",
                                                                                                                                                  "deles! Se não eu vou...", 
                                                                                                                                                  "",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 7, &informacaoLigeirinho.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);    
                            
                    } else if (informacaoLigeirinho.posicao_conversa == 7) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoPersonagem.lado, fala_personagem [1], buffer, informacaoInimigo.face [1],"Se não você vai o que!?",
                                                                                                                                                  "Hahahahahahah! Você mal consegue parar em pé!", 
                                                                                                                                                  "Não está em condições de tentar alguma coisa...",
                                                                                                                                                  "Parece que a lenda chamada Ligeirinho realmente", 
                                                                                                                                                  "acabou, olhe pra você, é um perdedor...", datFontes, 8, &informacaoLigeirinho.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);    
                            
                    } else if (informacaoLigeirinho.posicao_conversa == 8) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoPersonagem.lado, fala_personagem [1], buffer, informacaoLigeirinho.face [0],"Você já acabou com a minha vida!",
                                                                                                                                                  "Não faça nada contra minha família, eu imploro!", 
                                                                                                                                                  "Que mal eles podem oferecer a você!?",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 9, &informacaoLigeirinho.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);    
                            
                    } else if (informacaoLigeirinho.posicao_conversa == 9) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoPersonagem.lado, fala_personagem [1], buffer, informacaoInimigo.face [0],"Humm, tavez agora não ofereçam...",
                                                                                                                                                  "mas o fato é que aquele muleque herdou um pouco", 
                                                                                                                                                  "de suas antigas habilidades... e você sabe...",
                                                                                                                                                  "sou um homem precavido quanto à esses assuntos...", 
                                                                                                                                                  "", datFontes, 10, &informacaoLigeirinho.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);    
                            
                    } else if (informacaoLigeirinho.posicao_conversa == 10) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoPersonagem.lado, fala_personagem [1], buffer, informacaoLigeirinho.face [0],"Nao! Não faça nada ao João!",
                                                                                                                                                  "Ele ainda é apenas um criança, e como qualquer", 
                                                                                                                                                  "outra crinça de sua idade, gosta de futebol.",
                                                                                                                                                  "Isso não significa que ele vai se tornar", 
                                                                                                                                                  "um grande jogador!", datFontes, 11, &informacaoLigeirinho.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);    
                            
                    } else if (informacaoLigeirinho.posicao_conversa == 11) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoPersonagem.lado, fala_personagem [1], buffer, informacaoInimigo.face [0],"Hmm, é verdade... Por hora",
                                                                                                                                                  "vou acreditar nesta sua teoria... Mas isso já", 
                                                                                                                                                  "não importa mais... O meu plano para acabar",
                                                                                                                                                  "com todos os esportes já está em ação...", 
                                                                                                                                                  "Agora é questão de tempo...", datFontes, 12, &informacaoLigeirinho.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);    
                            
                    } else if (informacaoLigeirinho.posicao_conversa == 12) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoPersonagem.lado, fala_personagem [1], buffer, informacaoLigeirinho.face [0],"Mas qual o motivo dessa sua obsessão",
                                                                                                                                                  "por acabar com todos os esportes do mundo?!", 
                                                                                                                                                  "Eu não consigo entender...",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 13, &informacaoLigeirinho.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);    
                            
                    } else if (informacaoLigeirinho.posicao_conversa == 13) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoPersonagem.lado, fala_personagem [1], buffer, informacaoInimigo.face [0],"Os esportes destruíram tudo que",
                                                                                                                                                  "era importante para min! Principalmente o", 
                                                                                                                                                  "futebol... Mas isso é da sua conta! ",
                                                                                                                                                  "Hoje iria darca você um belo prato", 
                                                                                                                                                  "de comida, mas perdi a vontade. Até mais...", datFontes, 14, &informacaoLigeirinho.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);    
     
                    } else if (informacaoLigeirinho.posicao_conversa == 14) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoPersonagem.lado, fala_personagem [1], buffer, informacaoLigeirinho.face [0],"Espera, não vá, minha barriga está doendo...",
                                                                                                                                                  "", 
                                                                                                                                                  "",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 15, &informacaoLigeirinho.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);    
    
                    }  else if (informacaoLigeirinho.posicao_conversa == 15) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoPersonagem.lado, fala_personagem [1], buffer, informacaoInimigo.face [1],"É mesmo!!!???",
                                                                                                                                                  "", 
                                                                                                                                                  "",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 16, &informacaoLigeirinho.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);    
  
                    } else if (informacaoLigeirinho.posicao_conversa == 16) {
                            interacaoIniciadaAutomaticamenteNpc (informacaoPersonagem.lado, &informacaoPersonagem.lado, fala_personagem [1], buffer, informacaoInimigo.face [1],"É mesmo!!!???",
                                                                                                                                                  "", 
                                                                                                                                                  "",
                                                                                                                                                  "", 
                                                                                                                                                  "", datFontes, 17, &informacaoLigeirinho.posicao_conversa, &animacao_tecla_enter_pulsando, &animacao_tecla_enter_pulsando_delay);    
                            informacaoLigeirinho.posicao_conversa = 0;
                            cena_animada = 5;      
                    }
                 
                 // Sexta Cena Animada //
                 } else if (cena_animada == 5){ 
                    if (musica == 2) {
                        animacao_balao = 0;
                        musica = 3;
                    }
                    
                    set_alpha_blender();
                    draw_trans_sprite (buffer, cenario, 0, 0);
                    draw_trans_sprite(buffer, ligeirinho [informacaoLigeirinho.lado][informacaoLigeirinho.animacao], informacaoLigeirinho.x, informacaoLigeirinho.y);
                    draw_trans_sprite(buffer, inimigo [informacaoInimigo.lado][informacaoInimigo.animacao], informacaoInimigo.x, informacaoInimigo.y);
                    
                    efeito_balao_reticencias(buffer, informacaoLigeirinho.x, informacaoLigeirinho.y, &animacao_balao, &animacao_balao_delay);
                    
                    movimentarSpriteAutomaticamente(&informacaoInimigo.x, &informacaoInimigo.y, &informacaoInimigo.lado, &informacaoInimigo.animacao, &informacaoInimigo.delayanimacao, informacaoInimigo.terreno, 2, 280, 410, 0, &animacao_npc_delay, informacaoInimigo.velocidade_animacao);   
                    
                    if (informacaoInimigo.x == 280) {
                        cena_animada = 6;    
                    }
                 } else if (cena_animada == 6) {
                    
                    set_alpha_blender();
                    draw_trans_sprite (buffer, cenario, 0, 0);
                    draw_trans_sprite(buffer, ligeirinho [informacaoLigeirinho.lado][informacaoLigeirinho.animacao], informacaoLigeirinho.x, informacaoLigeirinho.y);
                    draw_trans_sprite(buffer, inimigo [informacaoInimigo.lado][informacaoInimigo.animacao], informacaoInimigo.x, informacaoInimigo.y);
                    
                    movimentarSpriteAutomaticamente(&informacaoInimigo.x, &informacaoInimigo.y, &informacaoInimigo.lado, &informacaoInimigo.animacao, &informacaoInimigo.delayanimacao, informacaoInimigo.terreno, 1, 170, 330, 0, &animacao_npc_delay, informacaoInimigo.velocidade_animacao);   
                    
                    if (informacaoInimigo.y == 170) {
                        progresso = 2;
                        mapa_atual = 2;
                        musica = 1;
                        informacaoPersonagem.x                =  125;
                        informacaoPersonagem.y                =  320;
                        informacaoPersonagem.lado             =  1;
                        informacaoMariana.x                   =  250;
                        informacaoMariana.y                   =  200;
                        informacaoPersonagem.posicao_conversa = 0;   
                        audio_fundo = load_midi("Audios/Fundo/musica_vila.mid");            // Load na musica do mapa 1.
                        play_midi(audio_fundo, 1);  
                    } 
                 }
                 
                draw_sprite(screen, buffer, 0, 0);
                clear (buffer);
                
                for (cont_destruir_x = 0; cont_destruir_x < 4; cont_destruir_x++) {
                    for (cont_destruir_y = 0; cont_destruir_y < 4; cont_destruir_y++) {
                        destroy_bitmap (ligeirinho [cont_destruir_x][cont_destruir_y]);
                    }
                }
                destroy_bitmap (informacaoLigeirinho.face [0]);
                destroy_bitmap (informacaoInimigo.face [0]);
                destroy_bitmap (informacaoInimigo.face [1]);
            }
                
// ================================================================================================ TELA QUANDO PERDE O JOGO =============================================================================================== //            
            if (mapa_atual == 3) {
                if (musica == 3) {  
                    audio_fundo = load_midi("Audios/Fundo/musica_fim_de_jogo.mid");
                    play_midi(audio_fundo, 1); 
                    fadeout (2);      
                    clear (buffer);
                    cenario = load_jpg("Imagens/FimDeJogo/fim_de_jogo.jpg",NULL);
                    draw_sprite(buffer, cenario, 0,  0);
                    fadein (buffer, 1);                                                         
                    musica = 1;
                    opcao = 1;   
                }
                draw_sprite(buffer, cenario, 0,  0);
                opcao = efeito_bola_opcao_fim_de_jogo (buffer, opcao, &animacao_bola, &animacao_bola_delay);
                efeito_choro(buffer, 330, 230, &animacao_choro, &animacao_choro_delay);
                if (opcao == 0) {
                    cenario =  load_jpg("Imagens/FimDeJogo/fim_de_jogo_continuar.jpg",NULL); 
                    draw_sprite(buffer, cenario, 0,  0);
                    mapa_atual = 1;
                    draw_sprite(screen, buffer, 0, 0);
                    rest (2000);
                    musica = 1;
                    informacaoPersonagem.vigor = 6;
                    informacaoPersonagem.energia = 3;
                    
                    mapa_atual                         = 0;
                    progresso_global                   = 0;
                    progresso                          = 0;
                    animacao_local                     = 0;
                    cena_animada                       = 0;
                    cena_animada_informacoes_iniciais  = 0;
                    musica                             = 0;
                    caso_colisao                       = 0; // Através dessa variável recebo o retorno da fundação detectarColisao, que cria um quadradro imaginário para haver colisão.
                    caso_colisao_sprite                = 0; // Através dessa variável recebo o retorno da função detectarColisaoSprite, que cria um quadradro imaginário em que qunado há colisão o Npc simplesmente para de andar (como um sensor)
                    caso_colisao_nociva                = 0;
                    opcao                              = 0;
                    velocidade_tempo;
                    comparador_tempo;
                    velocidade_fps                     = 0;
                    posicao_tutorial                   = 0;   
                    teste_efeito_nuvem                 = 0;
                    altura_nuvem_1                     = 0;
                    srand(time(NULL));
                    altura_nuvem_2                     = 1 + (int)( 550.0 * rand() / ( RAND_MAX + 1.0 ) );
                    cont                               = 0;
                    interacao                          = 0;
                    efeito                             = 0;
                    efeito_sonoro                      = 0;
                    cont_destruir_x                    = 0;
                    cont_destruir_y                    = 0;
                        
                    mini_game_lado_quadra_jogador        = 0;
                    mini_game_ponto_jogador              = 0;
    
                    mini_game_lado_quadra_adversario     = 0;
                    mini_game_ponto_adversario           = 0;
    
                    mini_game_corrida_resultado          = 0;
                    mini_game_corrida_nivel              = 0;
    
                    mini_game_pergunta_resposta_opcao    = 0;
                    mini_game_pergunta_resposta_pergunta = 0;
                    mini_game_pergunta_resposta_ponto    = 0;
                    
                    entrar               = 1;
                    entrar_2             = 0;
                    entrar_3             = 0;
                    entrar_4             = 0;
                    entrar_5             = 0;
                    
                    introducao_posicao   = 0;
                    
                    audio_fundo = load_midi("Audios/Fundo/musica_abertura.mid");
                    
                    informacaoPersonagem.x                             =   0;
                    informacaoPersonagem.y                             =   0;
                    informacaoPersonagem.lado                          =   0;
                    informacaoPersonagem.animacao                      =   0;
                    informacaoPersonagem.terreno                       =   TERRENO_NORMAL;
                    informacaoPersonagem.largura                       =   informacaoPersonagem.x + SPRITE_LARGURA;
                    informacaoPersonagem.altura                        =   informacaoPersonagem.y + SPRITE_ALTURA;
                    informacaoPersonagem.vigor                         =   6;
                    informacaoPersonagem.energia                       =   3;
                    informacaoPersonagem.face [0]                      =   load_bitmap ("Imagens/Personagens/Principal/Faces/face_joao_0.tga", NULL);
                    informacaoPersonagem.face [1]                      =   load_bitmap ("Imagens/Personagens/Principal/Faces/face_joao_1.tga", NULL);
                    informacaoPersonagem.ataque1 [0]                   =   load_bitmap ("Imagens/Personagens/Principal/Ataque1/bola_0.bmp", NULL);
                    informacaoPersonagem.ataque1 [1]                   =   load_bitmap ("Imagens/Personagens/Principal/Ataque1/bola_1.bmp", NULL);
                    informacaoPersonagem.ataque1 [2]                   =   load_bitmap ("Imagens/Personagens/Principal/Ataque1/bola_2.bmp", NULL);
                    informacaoPersonagem.moedas                        =   10;
                    informacaoPersonagem.nivel                         =   1;
                    informacaoPersonagem.habilidade1                   =   0;
                    informacaoPersonagem.experiencia_atual             =   0;
                    informacaoPersonagem.experiencia_proximo_nivel     =   50 * informacaoPersonagem.nivel;
                    informacaoPersonagem.experiencia_atual_porcentagem =   (informacaoPersonagem.experiencia_atual * 100) / informacaoPersonagem.experiencia_proximo_nivel;
    
                    interacaoBau1.x                     = 0;
                    interacaoBau1.y                     = 0;
                    interacaoBau1.estado                = 0;
                    interacaoBau1.animacao              = 0;
                    interacaoBau1.animacao_delay        = 0;
                    interacaoBau1.animacao_brilho       = 0;
                    interacaoBau1.animacao_brilho_delay = 0;
                    interacaoBau1.recompensaHabilidade  = 1;
                    interacaoBau1.recompensaVigor       = 0;
                    
                    // Informações sobre o jogo de carta //
                    informacaoJogoCarta1.ComparaId[0] = 0;
                    informacaoJogoCarta1.ComparaId[1] = 0;
                    informacaoJogoCarta1.x            = 0;
                    informacaoJogoCarta1.y            = 0;
                    informacaoJogoCarta1.C1           = 0;
                    informacaoJogoCarta1.C2           = 0;
                    informacaoJogoCarta1.L1           = 0;
                    informacaoJogoCarta1.L2           = 0;
                    informacaoJogoCarta1.estadoClique = 0;
                    informacaoJogoCarta1.Ponto        = 0;
                    informacaoJogoCarta1.colisao      = 0;
                    informacaoJogoCarta1.contClique   = 0;
                    
                    // Zera Animaçoes //
                    animacao_personagem_delay                  = 0;
                    animacao_npc_delay                         = 0;
                    animacao_vespa_delay                       = 0;
    
                    animacao_menu_abrindo                      = 0;
                    animacao_menu_abrindo_audio                = 0;
    
                    animacao_pressione_enter                   = 0;
                    animacao_pressione_enter_delay             = 0;
    
                    animacao_bola                              = 0;
                    animacao_bola_delay                        = 0;
    
                    animacao_ceu_1_parallax_delay              = 0;
                    animacao_ceu_1_parallax                    = 0;
    
                    animacao_ceu_2_parallax_delay              = 0;
                    animacao_ceu_2_parallax                    = 0;
    
                    animacao_tutorial_parallax                 = 0;
                    animacao_parallax_quem_somos               = 0;
    
                    animacao_choro                             = 0;
                    animacao_choro_delay                       = 0;
    
                    animacao_status                            = 0;
                    animacao_status_delay                      = 0;
    
                    animacao_chuva_noite                       = 0;
                    animacao_chuva_noite_delay                 = 0;
    
                    animacao_efeito_ataque                     = 0;
                    animacao_efeito_ataque_2                   = 0;
    
                    animacao_relampago                         = 0;
                    animacao_relampago_delay                   = 0;  
    
                    animacao_fogo [4];
                    animacao_fogo_delay [4];
    
                    animacao_luz_poste                         = 0;
                    animacao_luz_poste_delay                   = 0;
    
                    animacao_balao                             = 0;
                    animacao_balao_delay                       = 0; 
    
                    animacao_subiu_nivel                       = 21;
                    animacao_subiu_nivel_delay                 = 0;
    
                    animacao_torcedora [2];         
                    animacao_torcedora_delay [2];
                    
                    animacao_torcedora [0]                         = 0;
                    animacao_torcedora [1]                         = 0; 
                    animacao_torcedora_delay [0]                   = 0;
                    animacao_torcedora_delay [1]                   = 5;
    
                    jogadores_direita_ginasio                  = 0;
                    jogadores_direita_ginasio_delay            = 0;
                    jogadores_esquerda_ginasio                 = 0;
                    jogadores_esquerda_ginasio_delay           = 0;
    
                    animacao_agua_1                            = 0;   
                    animacao_agua_1_delay                      = 0;
                    animacao_agua_2                            = 0;   
                    animacao_agua_2_delay                      = 0;
    
                    animacao_1_sombra_nuvem                    = 0;
                    animacao_1_sombra_nuvem_delay              = 0;
                    animacao_2_sombra_nuvem                    = 0;
                    animacao_2_sombra_nuvem_delay              = 0;
                    animacao_3_sombra_nuvem                    = 0;
                    animacao_3_sombra_nuvem_delay              = 0;
    
                    animacao_tecla_enter_pulsando              = 0;
                    animacao_tecla_enter_pulsando_delay        = 0;
    
                    animacao_tecla_esc_pulsando                = 0;
                    animacao_tecla_esc_pulsando_delay          = 0;
    
                    animacao_moeda                             = 0;
                    animacao_moeda_delay                       = 0;
    
                    animacao_ganha_habilidade                  = 0;
                    animacao_ganha_habilidade_delay            = 0;
    
                    animacao_habilidade1                       = 0;
                    animacao_habilidade1_delay                 = 0;
    
                    animacao_contagem_regressiva               = 0;
                    animacao_contagem_regressiva_delay         = 0;
    
                    animacao_mini_game_corrida_resultado       = 0;
                    animacao_mini_game_corrida_resultado_delay = 0;
    
                    delay_ver_carta                            = 0;
                    posicao_x_efeito_carta_selecionada         = 0;
                    posicao_y_efeito_carta_selecionada         = 0;
                    animacao_carta_selecionada                 = 9;
                    animacao_carta_selecionada_delay           = 0;
    
                    animacao_ponto_positivo                    = 11;
                    animacao_ponto_positivo_delay              = 0;
    
                    animacao_ponto_negativo                    = 11;
                    animacao_ponto_negativo_delay              = 0;
    
                    animacao_cursor_pergunta_resposta          = 0;
                    animacao_cursor_pergunta_resposta_delay    = 0;
    
                    animacao_acerto_esquerda                   = 16;
                    animacao_acerto_esquerda_delay             = 0;
    
                    animacao_acerto_direita                    = 16;
                    animacao_acerto_direita_delay              = 0;
    
                    animacao_erro_esquerda                     = 16;
                    animacao_erro_esquerda_delay               = 0;
    
                    animacao_erro_direita                      = 16;
                    animacao_erro_direita_delay                = 0;
    
                    animacao_texto_sonho                       = 11;
                    animacao_texto_sonho_delay                 = 0;
                    
                    for (cont_destruir_x = 0; cont_destruir_x <4; cont_destruir_x ++) {
                        for (cont_destruir_y = 0; cont_destruir_y < 4; cont_destruir_y ++) {
                            VetCartas [cont_destruir_x] [cont_destruir_y].estado = 0;
                        }
                    }
                    
                    clear (buffer);
                    fadeout (8);
                } 
                draw_sprite(screen, buffer, 0, 0);  
                clear (buffer);              
            } 
//  ================================================   
        }  // FIM CONTROLADOR FPS       
    }  // FIM LOOP PRINCIPAL  
     
    stop_sample (audio_efeito [7]);
    destroy_midi (audio_fundo);                       // Para música de fundo   
    play_sample (audio_efeito [0], 255, 128, 1000, 0);    // Toca o efeito de dormir
                                                          // 1º Parametro é o endereço do arquivo de audio.
                                                          // 2º Parametro é o volume do audio
                                                          // 3º Parametro é o lado que o som vai tocar das caixas de som variado de 0 a 255, sendo 128 o balanço entre as duas caixas.
                                                          // 4º Parametro é a velocidade da música, sendo o valor 1000 a velocidade normal, podendo ficar mais rápido > que 1000 ou mais lento < 1000
                                                          // 5º Parametro pode ser 1 ou 0 , sendo 1 para repetir infinitamente e 0 apenas 1 vez.

    fadeout (1);
    rest (3000); // Para a música terminar de tocar    	

    deinit();
	return 0;
}
END_OF_MAIN ()
/*  -----------------------------------------------------------------------------------------------------------------------------------------------  */
/*  -----------------------------------------------        FINAL DO PROGRAMA        ---------------------------------------------------------------  */
/*  -----------------------------------------------------------------------------------------------------------------------------------------------  */




void init() {
	int depth, res, sound;
	allegro_init();
	depth = desktop_color_depth();
	
    // Testa Vídeo //
    if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, TELA_LARGURA, TELA_ALTURA, 0, 0);          // GFX_AUTODETECT_WINDOWED = Janela 
    if (res != 0) {                                                                // GFX_AUTODETECT_FULLSCREEN = Tela Inteira
		printf("Erro ao inicializar dispositivos de video.");                      // GFX_DIRECTX = Deixa o jogo mais rápido usando directx (fullscreen)
		exit(1);                                                                   // GFX_DIRECTX_WIN =Deixa o jogo mais rapido usando directx (modo janela) 
	}                                                                              // A utilização do GFX faz com que seu jogo só funcione em S.O windows.
    
    // Instala outros dispositivos //
	install_timer();
	install_keyboard();
	install_mouse();
    install_sound( DIGI_AUTODETECT, MIDI_AUTODETECT, 0 );
    sound = install_sound( DIGI_AUTODETECT, MIDI_AUTODETECT, 0 );
    
    // Testa Áudio //
    if (sound != 0) {
        allegro_exit();
        printf("Erro ao inicializar dispositivos de audio");
        exit(1);    
    } 	
    // Para o Jogo não Travar quando fica em Segundo Plano //
	set_display_switch_mode(SWITCH_BACKGROUND); 
	
	//
	set_uformat (U_ASCII);
    /* add other initializations here */
}


void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}
/*  -----------------------------------------------------------------------------------------------------------------------------------------------  */
/*  ------------------------------------------------       Funções Usadas em Main    -- -----------------------------------------------------------  */
/*  -----------------------------------------------------------------------------------------------------------------------------------------------  */

// Movimentar Sprites usando Teclado //
void movimentarJogador (int *x, int *y, int *lado, int *animacao, int *terreno, int *animacao_delay) {   
    
    *animacao_delay = *animacao_delay + 1;
    
    if ((key [KEY_LSHIFT]) && (key[KEY_DOWN])) {
        *terreno = VELOCIDADE_AUMENTADA;
        *lado = 0;
        *y += *terreno;
        if (*animacao_delay > 1) {
            if (*animacao < 4){
              *animacao = 4;
            }
            *animacao += 1;
            *animacao_delay = 0;
            if (*animacao > 7){
              *animacao = 4;
            }
        }
    } else if ((key [KEY_LSHIFT]) && (key[KEY_RIGHT])) {
        *terreno = VELOCIDADE_AUMENTADA;
        *lado = 1;
        *x += *terreno;
        if (*animacao_delay > 1) {
            if (*animacao < 4){
              *animacao = 4;
            }
            *animacao += 1;
            *animacao_delay = 0;
            if (*animacao > 7){
              *animacao = 4;
            }
        }
    } else if ((key [KEY_LSHIFT]) && (key[KEY_UP])) {
        *terreno = VELOCIDADE_AUMENTADA;
        *lado = 2;
        *y -= *terreno;
        if (*animacao_delay > 1) {
            if (*animacao < 4){
              *animacao = 4;
            }
            *animacao += 1;
            *animacao_delay = 0;
            if (*animacao > 7){
              *animacao = 4;
            }
        }
    } else if ((key [KEY_LSHIFT]) && (key[KEY_LEFT])) {
        *terreno = VELOCIDADE_AUMENTADA;
        *lado = 3;
        *x -= *terreno;
        if (*animacao_delay > 1) {
            if (*animacao < 4){
              *animacao = 4;
            }
            *animacao += 1;
            *animacao_delay = 0;
            if (*animacao > 7){
              *animacao = 4;
            }
        }
    } else {
        if (key[KEY_DOWN]) {
            *terreno = TERRENO_NORMAL;
            *lado = 0;
            *y += *terreno;
            if (*animacao_delay > 1) {
                *animacao += 1;
                *animacao_delay = 0;
                if (*animacao > 3){
                  *animacao = 0;
                }
           }
        } else if (key[KEY_RIGHT]) {
            *terreno = TERRENO_NORMAL;
            *lado = 1;
            *x += *terreno;
            if (*animacao_delay > 1) {
                *animacao += 1;
                *animacao_delay = 0;
                if (*animacao > 3){
                  *animacao = 0;
                }
            }
        } else if (key[KEY_UP]) {
            *terreno = TERRENO_NORMAL;
            *lado = 2;
            *y -= *terreno;
            if (*animacao_delay > 1) {
                *animacao += 1;
                *animacao_delay = 0;
                if (*animacao > 3){
                    *animacao = 0;
                }
            }
        } else if (key[KEY_LEFT]) {
            *terreno = TERRENO_NORMAL;
            *lado = 3;
            *x -= *terreno;
            if (*animacao_delay > 1) {
                *animacao += 1;
                *animacao_delay = 0;
                if (*animacao > 3){
                  *animacao = 0;
                }
            }
        } else {
        *animacao = 0;
        }
    }
}

//  Detecção de Colisão Com Cenário  //
int detectarColisao (int *x1, int *y1, int *altura1, int *largura1,
                       int x2, int y2, int altura2, int largura2, int terreno, int lado, int *animacao) {
                           
    int colisao = 0;
    
    if (*x1 > altura2) {
    } else if (*y1 > largura2) {
    } else if (*largura1 < x2) {
    } else if (*altura1 < y2) {
    } else { 
        colisao = 1;
        if (lado == 0) {
            *y1 -= terreno;
        } else if (lado == 1) {
            *x1 -= terreno;
        } else if (lado == 2) {
            *y1 += terreno;
        } else {
            *x1 += terreno;
        }         
    }
    if (colisao == 1) {
        *animacao = 0;
    }
    return (colisao);
}

//  Detecção de Colisão Entre Sprites  //
int detectarColisaoSprite (int *x1, int *y1, int *altura1, int *largura1,
                       int x2, int y2, int altura2, int largura2, int terreno, int *animacao) {
                           
    int colisao = 0;
    
    if (*x1 > altura2) {
    } else if (*y1 > largura2) {
    } else if (*largura1 < x2) {
    } else if (*altura1 < y2) {
    } else { 
        colisao = 1;
    }
    if (colisao == 1) {
        *animacao = 0;       
    }
    return (colisao);
}

// Intereção com Npc //
void interacaoNpc (int ladoPersonagem, int *ladoNpc, BITMAP *fala_sprite, BITMAP *buffer_atual, BITMAP *face_sprite, char texto_fala_lin_1 [50], char texto_fala_lin_2 [50], char texto_fala_lin_3 [50], char texto_fala_lin_4 [50], char texto_fala_lin_5 [50], DATAFILE *fonte, int continuidade_conversa, int *atual_conversa, int *animacao_tecla, int *animacao_tecla_delay, int mudar_fala, int *personagem_fala){
        
    BITMAP *borda_fala_local = load_bitmap("Imagens/ObjetosDeInterface/Bordas/borda_fala_bitmap.bmp",NULL);
    BITMAP *fundo_fala_local = load_jpg("Imagens/ObjetosDeInterface/Fundos/fundo_fala.jpg",NULL);
    BITMAP *fundo_nome_local = load_jpg("Imagens/ObjetosDeInterface/Fundos/fundo_nome.jpg",NULL);
    BITMAP *double_buffer;
    BITMAP *animacao_enter [2];
    
    animacao_enter [0] = load_bitmap("Imagens/ObjetosDeInterface/Teclas/animacao_enter_0.bmp",NULL);
    animacao_enter [1] = load_bitmap("Imagens/ObjetosDeInterface/Teclas/animacao_enter_1.bmp",NULL);  
    
    double_buffer = buffer_atual;
    
    char *cLinhas[] = { texto_fala_lin_1, texto_fala_lin_2, texto_fala_lin_3, texto_fala_lin_4, texto_fala_lin_5, NULL};
    int i = 0;
    
    
    if ((*atual_conversa == 0) &&  (key [KEY_Z])) {     
        if (ladoPersonagem == 0) {
            *ladoNpc = 2;
        } else if (ladoPersonagem == 1) {
            *ladoNpc = 3;
        } else if (ladoPersonagem == 2) {
            *ladoNpc = 0;
        } else {
            *ladoNpc = 1;
        }
        *atual_conversa = 1;
    }else if (*atual_conversa > 0)  {
        set_trans_blender(0,0,0,150);
        draw_trans_sprite(double_buffer, fundo_fala_local, 0, 410);
        draw_trans_sprite(double_buffer, fundo_nome_local, 0, 350);
        set_alpha_blender();
        draw_trans_sprite (double_buffer, face_sprite, 11, 369);
        draw_sprite(double_buffer, borda_fala_local, 0, 350);
        for (i = 0;i<5;i++) {   // de 0 a 3 faça
            textout_justify_ex(double_buffer, (FONT *)fonte[0].dat, cLinhas[i], 190, 740, (i*text_height((FONT *)fonte[0].dat) + 435), 80, makecol(255, 255, 255),-1);
        }
        
        animacao_tecla_enter (double_buffer, 733, 508, animacao_tecla, animacao_tecla_delay);    
        set_keyboard_rate(0,0);
        if (key[KEY_ENTER]) {
            if (keypressed()) {
                *atual_conversa = continuidade_conversa;
                *personagem_fala = mudar_fala;
            }
            clear_keybuf();     
        } 
        
    }
    destroy_bitmap (animacao_enter [0]);
    destroy_bitmap (animacao_enter [1]);
    destroy_bitmap (borda_fala_local);
    destroy_bitmap (fundo_fala_local);
    destroy_bitmap (fundo_nome_local);
}


// Intereção com Npc Iniciada Automaticamente //
void interacaoIniciadaAutomaticamenteNpc (int ladoPersonagem, int *ladoNpc, BITMAP *fala_sprite, BITMAP *buffer_atual, BITMAP *face_sprite, char texto_fala_lin_1 [50], char texto_fala_lin_2 [50], char texto_fala_lin_3 [50], char texto_fala_lin_4 [50], char texto_fala_lin_5 [50], DATAFILE *fonte, int continuidade_conversa, int *atual_conversa, int *animacao_tecla, int *animacao_tecla_delay){
        
    BITMAP *borda_fala_local = load_bitmap("Imagens/ObjetosDeInterface/Bordas/borda_fala_bitmap.bmp",NULL);
    BITMAP *fundo_fala_local = load_jpg("Imagens/ObjetosDeInterface/Fundos/fundo_fala.jpg",NULL);
    BITMAP *fundo_nome_local = load_jpg("Imagens/ObjetosDeInterface/Fundos/fundo_nome.jpg",NULL);
    BITMAP *double_buffer;
    BITMAP *animacao_enter [2];
    
    animacao_enter [0] = load_bitmap("Imagens/ObjetosDeInterface/Teclas/animacao_enter_0.bmp",NULL);
    animacao_enter [1] = load_bitmap("Imagens/ObjetosDeInterface/Teclas/animacao_enter_1.bmp",NULL);  
    
    double_buffer = buffer_atual;
    
    char *cLinhas[] = { texto_fala_lin_1, texto_fala_lin_2, texto_fala_lin_3, texto_fala_lin_4, texto_fala_lin_5, NULL};
    int i = 0;
    
    
    if (*atual_conversa == 0) {        
        if (ladoPersonagem == 0) {
            *ladoNpc = 2;
        } else if (ladoPersonagem == 1) {
            *ladoNpc = 3;
        } else if (ladoPersonagem == 2) {
            *ladoNpc = 0;
        } else {
            *ladoNpc = 1;
        }
        *atual_conversa = 1;
    }else if ((*atual_conversa > 0)) {
        set_trans_blender(0,0,0,150);
        draw_trans_sprite(double_buffer, fundo_fala_local, 0, 410);
        draw_trans_sprite(double_buffer, fundo_nome_local, 0, 350);
        set_alpha_blender();
        draw_trans_sprite (double_buffer, face_sprite, 11, 369);
        draw_sprite(double_buffer, borda_fala_local, 0, 350);
        for (i = 0;i<5;i++) {   // de 0 a 3 faça
            textout_justify_ex(double_buffer, (FONT *)fonte[0].dat, cLinhas[i], 190, 740, (i*text_height((FONT *)fonte[0].dat) + 435), 80, makecol(255, 255, 255),-1);
        }
        
        animacao_tecla_enter (double_buffer, 733, 508, animacao_tecla, animacao_tecla_delay);    
        set_keyboard_rate(0,0);
        if (key[KEY_ENTER]) {
            if (keypressed()) {
                *atual_conversa = continuidade_conversa;
            }
            clear_keybuf();     
        }  
    }
    destroy_bitmap (animacao_enter [0]);
    destroy_bitmap (animacao_enter [1]);
    destroy_bitmap (borda_fala_local);
    destroy_bitmap (fundo_fala_local);
    destroy_bitmap (fundo_nome_local);
}




//  Detecção de Colisão Entrar e Sair  //
void detectarColisaoEntrarSair(int *x1, int *y1, int *altura1, int *largura1,
                       int x2, int y2, int altura2, int largura2,int *mapa_atual, int mapa_destino) {                           
    
    
    if (*x1 > altura2) {
    } else if (*y1 > largura2) {
    } else if (*largura1 < x2) {
    } else if (*altura1 < y2) {
    } else { 
    *mapa_atual = mapa_destino;
    }
}

//  Detecção de Colisão para Interação
void detectarColisaoInteracaoObjetoCima(int *x1, int *y1, int *altura1, int *largura1,
                       int x2, int y2, int altura2, int largura2,int lado_personagem, int *acao) {                           
    
    if (*x1 > altura2) {
    } else if (*y1 > largura2) {
    } else if (*largura1 < x2) {
    } else if (*altura1 < y2) {
    } else {
        if (lado_personagem == 2) { 
            if (key[KEY_Z]) {
                *acao = 1;
            }
        }
    }
}


// Detecção de Colisão Nociva //
int detectarColisaoNociva(int *x1, int *y1, int *altura1, int *largura1, int lado,
                       int x2, int y2, int altura2, int largura2, int terreno, int *animacao, int *vigor) {
                           
    BITMAP *efeito_pancada;
    SAMPLE *audio_efeito;
    
    efeito_pancada = load_bitmap ("Imagens/Animacoes/Pancada/pancada1.tga", NULL);
    audio_efeito   = load_sample("Audios/Efeito/efeito_ouch.wav");  
    
    int colisao = 0;
    
    if (*x1 > altura2) {
    } else if (*y1 > largura2) {
    } else if (*largura1 < x2) {
    } else if (*altura1 < y2) {
    } else { 
        colisao = 1;
    }
    if (colisao == 1) {        
        if (lado == 0) {
            *y1 -= (terreno + 15);
        } else if (lado == 1) {
            *x1 -= (terreno + 15);
        } else if (lado == 2) {
            *y1 += (terreno + 15);
        } else {
            *x1 += (terreno + 15);
        }
        play_sample (audio_efeito, 500, 128, 1000, 0);
        
        set_alpha_blender();
        draw_trans_sprite (screen, efeito_pancada,*x1 - 50, *y1 - 30);
        
        *vigor = *vigor - 1;
        if (*vigor < 0) {
            *vigor = 0;
        }
        *animacao = 0;          
    }
    destroy_bitmap (efeito_pancada);
    return (colisao);
}


// Detecção de Colisão do Ataque do Personagem //
int detectarColisaoAtaquePersonagem (BITMAP *buffer_atual, int *x1, int *y1, int *altura1, int *largura1, int lado,
                       int x2, int y2, int altura2, int largura2, int terreno, int *animacao, int *vigor) {
                           
    BITMAP *efeito_pancada;
    SAMPLE *audio_efeito;
    
    efeito_pancada = load_bitmap ("Imagens/Animacoes/Pancada/pancada2.tga", NULL);
    audio_efeito   = load_sample("Audios/Efeito/efeito_puch.wav");  
    
    int colisao = 0;
    
    if (*x1 > altura2) {
    } else if (*y1 > largura2) {
    } else if (*largura1 < x2) {
    } else if (*altura1 < y2) {
    } else { 
        colisao = 1;
    }
    if (colisao == 1) {        
        if (lado == 0) {
        } else if (lado == 1) {
        } else if (lado == 2) {
        } else {
        }
        play_sample (audio_efeito, 255, 128, 1000, 0);
        
        set_alpha_blender();
        draw_trans_sprite (buffer_atual, efeito_pancada, x2 - 75, y2 - 85);
        
        *vigor = *vigor - 1;
        if (*vigor < 0) {
            *vigor = 0;
        }
        *animacao = 0;          
    }
    destroy_bitmap (efeito_pancada);
    return (colisao);
}


//  Detecção de Terreno Arenoso  //     
int detectarTerrenoArenoso(int *x1, int *y1, int *altura1, int *largura1,
                       int x2, int y2, int altura2, int largura2, int *terreno, int lado) {
                           
    int colisao = 0;
    
    if (*x1 > altura2) {
    } else if (*y1 > largura2) {
    } else if (*largura1 < x2) {
    } else if (*altura1 < y2) {
    } else { 
        colisao = 1;
        *terreno = TERRENO_ARENOSO;
    }
    return (colisao); 
} 

//  Efeito Fadeout  //
void fadeout (int velocidade){
    
    BITMAP *bmp_buff;
    BITMAP *buffer;
    
    int a = 256;
    
        if ((buffer = create_bitmap(TELA_LARGURA, TELA_ALTURA))) {
            if ((bmp_buff = create_bitmap(TELA_LARGURA, TELA_ALTURA))) {
                blit(screen, buffer, 0,0, 0,0, TELA_LARGURA, TELA_ALTURA);
                for (a = 255 - velocidade; a > 0; a -= velocidade) {
                    clear(bmp_buff);
                    set_trans_blender(0,0,0,a);
                    draw_trans_sprite(bmp_buff, buffer, 0, 0);
                    vsync();
                    blit(bmp_buff, screen, 0,0, 0,0, TELA_LARGURA, TELA_ALTURA);
                }
                destroy_bitmap(bmp_buff);
            }
            destroy_bitmap(buffer);
        }
        rectfill(screen, 0,0, TELA_LARGURA, TELA_ALTURA, makecol(0,0,0));
        a = 0;                
}


//  Efeito Fadein  //
void fadein(BITMAP *buffer, int velocidade){                             //buffer é a imagem que vai ser desenhada no screen.
   BITMAP *bmp_buff;
 
    if ((bmp_buff = create_bitmap(TELA_LARGURA, TELA_ALTURA)))
    {
        int a;
        if (velocidade <= 0) velocidade = 16; 
        for (a = 0; a < 256; a+= velocidade)
        {
            clear(bmp_buff);
            set_trans_blender(0,0,0,a);
            draw_trans_sprite(bmp_buff, buffer, 0, 0);
            vsync();
            blit(bmp_buff, screen, 0,0, 0,0, TELA_LARGURA, TELA_ALTURA);
        }
        destroy_bitmap(bmp_buff);
    }
    blit(buffer, screen, 0,0, 0,0, TELA_LARGURA, TELA_ALTURA);   
}

// Efeito Nuvens //
int efeito_nuvens (BITMAP *buffer, int teste_efeito,  int velocidade_nuvem, int altura_nuvem, int tempo_espera, int *animacao_1, int *animacao_1_delay, int *animacao_2, int *animacao_2_delay, int *animacao_3, int *animacao_3_delay) {
    int posicao_x_nuvem;
    
    BITMAP *nuvem_efeito;
    
    nuvem_efeito = load_bitmap("Imagens/EstilosCenarios/Objetos/Nuvem/nuvem_1.bmp",NULL); 
    
    
    *animacao_1 = *animacao_1 + 1;                                                                             
    if (*animacao_1 > tempo_espera) {
        *animacao_2_delay = *animacao_2_delay + 1;
        if (*animacao_2_delay > 1) {
            *animacao_2 = *animacao_2 + 1;
            *animacao_2_delay = 0;
        }
        
        posicao_x_nuvem = (800 + tempo_espera * 20) - *animacao_2;
        
        if (teste_efeito == 1) {
            if (posicao_x_nuvem  < -154) {
                *animacao_1 = 0;
                *animacao_2 = 0;
                *animacao_3 = 0;
            } else {
                teste_efeito = 0;
            }
        } 
        
        *animacao_3_delay = *animacao_3_delay + 1;
        if (*animacao_3_delay > 7) {
            *animacao_3 = *animacao_3 + 1;
            *animacao_3_delay = 0;
        }
        
        set_trans_blender (0,0,0, 50);
        draw_trans_sprite (buffer, nuvem_efeito, posicao_x_nuvem, altura_nuvem + *animacao_3);
    
        if (posicao_x_nuvem  < -154) {
            teste_efeito = 1;
        } else {
            teste_efeito = 0;
        }
    }
    destroy_bitmap (nuvem_efeito);      
    return teste_efeito;
}

// Efeito Bola Opcao //
int efeito_bola_opcao_menu_principal (BITMAP *buffer_atual, int opcao_escolhida, int *animacao, int *delay_animacao) {
    
    BITMAP *cursor_efeito [4];
    
    SAMPLE *audio_efeito_menu;
    audio_efeito_menu = load_sample("Audios/Efeito/efeito_escolha.wav"); 
    
    *delay_animacao =  *delay_animacao + 1;
        
    if (*delay_animacao > 0) {
         *animacao = *animacao + 1;
         *delay_animacao = 0;
    }
    
    int cont;
    
    cursor_efeito [0]  = load_bitmap ("Imagens/ObjetosDeInterface/Cursores/cursor_opcao_efeito_0.tga",NULL);
    cursor_efeito [1]  = load_bitmap ("Imagens/ObjetosDeInterface/Cursores/cursor_opcao_efeito_1.tga",NULL);
    cursor_efeito [2]  = load_bitmap ("Imagens/ObjetosDeInterface/Cursores/cursor_opcao_efeito_2.tga",NULL);
    cursor_efeito [3]  = load_bitmap ("Imagens/ObjetosDeInterface/Cursores/cursor_opcao_efeito_3.tga",NULL);

        set_keyboard_rate(0,0);
        if (key [KEY_DOWN]) {
            if (keypressed()) {
                if (((opcao_escolhida == 1) || (opcao_escolhida == 2) || (opcao_escolhida == 0))) {
                    play_sample (audio_efeito_menu, 500, 128, 1000, 0);
                }
                opcao_escolhida ++;
                if (opcao_escolhida > 3) {
                    opcao_escolhida = 3;
                }
            }
            clear_keybuf();
        } else if (key [KEY_UP]) {
            if (keypressed()) {
                if (((opcao_escolhida == 1) || (opcao_escolhida == 2) || (opcao_escolhida == 3))) {
                    play_sample (audio_efeito_menu, 500, 128, 1000, 0);
                }
                opcao_escolhida = opcao_escolhida - 1;
                if (opcao_escolhida < 0) {
                    opcao_escolhida = 0;
                }  
            }
            clear_keybuf();
        }

    if (*animacao > 3) {
       *animacao = 0;
    }
    
    set_alpha_blender();
    if (opcao_escolhida == 0) {                 
        draw_trans_sprite(buffer_atual, cursor_efeito [*animacao], 296,350);
        draw_trans_sprite(buffer_atual, cursor_efeito [*animacao], 466,350);
    } else if (opcao_escolhida == 1) {
        draw_trans_sprite(buffer_atual, cursor_efeito [*animacao], 293,408);
        draw_trans_sprite(buffer_atual, cursor_efeito [*animacao], 468,408);
    } else if (opcao_escolhida == 2) {
        draw_trans_sprite(buffer_atual, cursor_efeito [*animacao], 286,466);
        draw_trans_sprite(buffer_atual, cursor_efeito [*animacao], 476,466);
    } else {
        draw_trans_sprite(buffer_atual, cursor_efeito [*animacao], 306,524);
        draw_trans_sprite(buffer_atual, cursor_efeito [*animacao], 456,524);
    }
    
    for (cont = 0; cont < 4; cont ++) {
        destroy_bitmap (cursor_efeito [cont]);
    } 
    return (opcao_escolhida);
}

// Efeito Ceu Parallax //     
void efeito_ceu_parallax (BITMAP *buffer_atual, int *animacao_ceu_1_parallax, int *animacao_ceu_1_parallax_delay, int *animacao_ceu_2_parallax, int *animacao_ceu_2_parallax_delay ) {
     BITMAP *ceu_1_parallax_1;
     BITMAP *ceu_2_parallax_2;
     
     *animacao_ceu_1_parallax_delay  =  *animacao_ceu_1_parallax_delay + 1;
     *animacao_ceu_2_parallax_delay  =  *animacao_ceu_2_parallax_delay + 1;
     
         *animacao_ceu_1_parallax = *animacao_ceu_1_parallax - 1;
         *animacao_ceu_1_parallax_delay = 0;

     if (*animacao_ceu_2_parallax_delay > 1) {
         *animacao_ceu_2_parallax = *animacao_ceu_2_parallax - 1;
         *animacao_ceu_2_parallax_delay = 0;
     }
     
     
     ceu_1_parallax_1 = load_bitmap ("Imagens/Parallax/Parallax_Nuvens.bmp",NULL);
     ceu_2_parallax_2 = load_bitmap ("Imagens/Parallax/Parallax_Nuvens_2.bmp",NULL);
     
     
     set_trans_blender (0,0,0, 100);
     
     draw_trans_sprite(buffer_atual, ceu_1_parallax_1, 0 + *animacao_ceu_1_parallax , 0);
     draw_trans_sprite(buffer_atual, ceu_1_parallax_1, 800 + *animacao_ceu_1_parallax , 0);
     
     draw_trans_sprite(buffer_atual, ceu_2_parallax_2, 0 + *animacao_ceu_2_parallax, 0);
     draw_trans_sprite(buffer_atual, ceu_2_parallax_2, 800 + *animacao_ceu_2_parallax, 0);
     
     if (*animacao_ceu_1_parallax < -799) {
         *animacao_ceu_1_parallax = 0;             
     }
     
     if (*animacao_ceu_2_parallax < -799) {
         *animacao_ceu_2_parallax = 0;             
     }
     
     destroy_bitmap (ceu_1_parallax_1);
     destroy_bitmap (ceu_2_parallax_2);     
}    

// Efeito Pausa e Menu //
int pausa_menu (BITMAP *buffer_atual, int opcao_menu_pausa, int *animacao, int *delay_animacao) {
    
    BITMAP *double_buffer;
    BITMAP *borda_menu;
    BITMAP *fundo_menu;
    BITMAP *tela_escura;

    tela_escura = create_bitmap(TELA_LARGURA, TELA_ALTURA);
    
    clear(tela_escura);
    double_buffer = buffer_atual;
    
    borda_menu = load_bitmap ("Imagens/ObjetosDeInterface/Bordas/borda_menu.tga", NULL);
    fundo_menu = load_jpg ("Imagens/ObjetosDeInterface/Fundos/fundo_menu.jpg", NULL);

    set_trans_blender(0,0,0,100);
    
    draw_trans_sprite(double_buffer, tela_escura, 0, 0);
    draw_trans_sprite(double_buffer, fundo_menu, 220, 150);
    
    set_alpha_blender();
    draw_trans_sprite (double_buffer, borda_menu, 220, 150);
    draw_sprite (buffer_atual, double_buffer, 0, 0); 
   
    opcao_menu_pausa = efeito_bola_opcao_menu_pequeno(double_buffer, opcao_menu_pausa, animacao, delay_animacao);
    
    destroy_bitmap (borda_menu);
    destroy_bitmap (fundo_menu);
    destroy_bitmap (tela_escura);
       
    return (opcao_menu_pausa);
}

// Efeito Bola Opcao Menu Pequeno //
int efeito_bola_opcao_menu_pequeno (BITMAP *buffer_atual, int opcao_escolhida, int *animacao, int *delay_animacao) {
    
    BITMAP *cursor_efeito [4];    
    SAMPLE *audio_efeito_menu [3];
    
    int cont = 0; 
    
    *delay_animacao =  *delay_animacao + 1;
        
    if (*delay_animacao > 0) {
         *animacao = *animacao + 1;
         *delay_animacao = 0;
    }

    audio_efeito_menu [0] = load_sample("Audios/Efeito/efeito_escolha.wav");
    audio_efeito_menu [1] = load_sample("Audios/Efeito/efeito_voltar.wav"); 
    audio_efeito_menu [2] = load_sample("Audios/Efeito/efeito_apito.wav"); 
   
    
    cursor_efeito [0]  = load_bitmap ("Imagens/ObjetosDeInterface/Cursores/cursor_opcao_efeito_0.tga",NULL);
    cursor_efeito [1]  = load_bitmap ("Imagens/ObjetosDeInterface/Cursores/cursor_opcao_efeito_1.tga",NULL);
    cursor_efeito [2]  = load_bitmap ("Imagens/ObjetosDeInterface/Cursores/cursor_opcao_efeito_2.tga",NULL);
    cursor_efeito [3]  = load_bitmap ("Imagens/ObjetosDeInterface/Cursores/cursor_opcao_efeito_3.tga",NULL);      
        
        set_keyboard_rate (0,0);
        if (key [KEY_DOWN]) {
            if (keypressed()) { 
                if (opcao_escolhida == 1) {
                    play_sample (audio_efeito_menu [0], 500, 128, 1000, 0);
                }
                opcao_escolhida = 2;
            }
            clear_keybuf();
        } else if (key [KEY_UP]) {
            if (keypressed()) {
                if (opcao_escolhida == 2) {
                    play_sample (audio_efeito_menu [0], 500, 128, 1000, 0);
                }
                opcao_escolhida = 1;
            }
            clear_keybuf();
        }
    
    
    if (*animacao > 3) {
        *animacao = 0;
    }
    
    set_alpha_blender();
    if (opcao_escolhida == 2) {                 
        draw_trans_sprite(buffer_atual, cursor_efeito [*animacao], 315,375);
        draw_trans_sprite(buffer_atual, cursor_efeito [*animacao], 453,375);
    } else {
        draw_trans_sprite(buffer_atual, cursor_efeito [*animacao], 244,277);
        draw_trans_sprite(buffer_atual, cursor_efeito [*animacao], 523,277);
    }
    
    if ((opcao_escolhida == 1) && (key[KEY_ENTER])) {
        play_sample (audio_efeito_menu [1], 500, 128, 1000, 0);
        opcao_escolhida = 0;                    
    } else if ((opcao_escolhida == 2) && (key[KEY_ENTER])) {
        play_sample (audio_efeito_menu [2], 500, 128, 1000, 0);
        opcao_escolhida = -1;    
    }

    for (cont = 0; cont != 3; cont ++) {
        destroy_bitmap (cursor_efeito [cont]);
    } 
    return (opcao_escolhida);
}

// Efeito Céu Parallax //
void efeito_nuvens_parallax (BITMAP *buffer_atual, int *animacao) {
     BITMAP *nuvens_parallax; 
     BITMAP *double_buffer;
     
     double_buffer = buffer_atual;
     *animacao = *animacao - 2;
     nuvens_parallax = load_bitmap ("Imagens/Parallax/Parallax_Ceu.jpg",NULL);   
     
     
     draw_sprite(double_buffer, nuvens_parallax, 0 + *animacao, 0);
     draw_sprite(double_buffer, nuvens_parallax, 800 + *animacao, 0);

     draw_sprite(buffer_atual, double_buffer,0, 0);
     
     if (*animacao < -799) {
         *animacao = 0;             
     }  
     destroy_bitmap (nuvens_parallax);
}

// Efeito Parallax Tutorial //
void efeito_tutorial_parallax (BITMAP *buffer_atual, int *animacao) {
     BITMAP *fundo_parallax; 
     BITMAP *double_buffer;
     
     double_buffer = buffer_atual;
     *animacao = *animacao - 2;
     fundo_parallax = load_bitmap ("Imagens/Parallax/Parallax_Tutorial.jpg",NULL);   
     
     
     draw_sprite(double_buffer, fundo_parallax, 0 + *animacao, 0);
     draw_sprite(double_buffer, fundo_parallax, 800 + *animacao, 0);

     draw_sprite(buffer_atual, double_buffer,0, 0);
     
     if (*animacao < -799) {
         *animacao = 0;             
     }  
     destroy_bitmap (fundo_parallax);
}

// Efeito Parallax Vitória //
void efeito_vitoria_parallax (BITMAP *buffer_atual, int *animacao) {
     BITMAP *fundo_parallax; 
     BITMAP *double_buffer;
     
     double_buffer = buffer_atual;
     *animacao = *animacao - 2;
     fundo_parallax = load_bitmap ("Imagens/Parallax/Parallax_Vitoria.jpg",NULL);   
     
     
     draw_sprite(double_buffer, fundo_parallax, 0 + *animacao, 0);
     draw_sprite(double_buffer, fundo_parallax, 800 + *animacao, 0);

     draw_sprite(buffer_atual, double_buffer,0, 0);
     
     if (*animacao < -799) {
         *animacao = 0;             
     }  
     destroy_bitmap (fundo_parallax);
}

// Efeito Parallax Fim //
void efeito_bola_parallax (BITMAP *buffer_atual, int *animacao) {
     BITMAP *fundo_parallax; 
     BITMAP *double_buffer;
     
     double_buffer = buffer_atual;
     *animacao = *animacao - 2;
     fundo_parallax = load_bitmap ("Imagens/Parallax/Parallax_Bolas.jpg",NULL);   
     
     
     draw_sprite(double_buffer, fundo_parallax, 0 + *animacao, 0);
     draw_sprite(double_buffer, fundo_parallax, 800 + *animacao, 0);

     draw_sprite(buffer_atual, double_buffer,0, 0);
     
     if (*animacao < -799) {
         *animacao = 0;             
     }  
     destroy_bitmap (fundo_parallax);
}

// Efeito Parallax Vitória //
void efeito_estrelas_parallax (BITMAP *buffer_atual, int *animacao) {
     BITMAP *fundo_parallax; 
     BITMAP *double_buffer;
     
     double_buffer = buffer_atual;
     *animacao = *animacao - 1;
     fundo_parallax = load_bitmap ("Imagens/Parallax/Parallax_Estrelas.jpg",NULL);   
     
     
     draw_sprite(double_buffer, fundo_parallax, 0, 0 + *animacao);
     draw_sprite(double_buffer, fundo_parallax, 0, 600 + *animacao);

     draw_sprite(buffer_atual, double_buffer,0, 0);
     
     if (*animacao < -599) {
         *animacao = 0;             
     }  
     destroy_bitmap (fundo_parallax);
}

// Efeito Parallax Vitória //
void efeito_faixa_ranking_parallax (BITMAP *buffer_atual, int *animacao) {
     BITMAP *faixa_parallax; 
     BITMAP *double_buffer;
     
     double_buffer = buffer_atual;
     *animacao = *animacao - 2;
     faixa_parallax = load_bitmap ("Imagens/Parallax/Parallax_Faixa_Ranking.tga",NULL);   
     
     set_alpha_blender();
     draw_trans_sprite(double_buffer, faixa_parallax, 0 + *animacao, 0);
     draw_trans_sprite(double_buffer, faixa_parallax, 800 + *animacao, 0);
     
     draw_trans_sprite(double_buffer, faixa_parallax, 0 + *animacao, 549);
     draw_trans_sprite(double_buffer, faixa_parallax, 800 + *animacao, 549);

     draw_sprite(buffer_atual, double_buffer,0, 0);
     
     if (*animacao < -800) {
         *animacao = 0;             
     }  
     destroy_bitmap (faixa_parallax);
}

// Tutorial_Mini_Game_Ginasio_0 //
void tutorial_minigame_ginasio_0 (BITMAP *buffer_atual, int posicao_tutorial) {
     BITMAP *minigame [3]; 
     
     minigame [0] = load_bitmap ("Imagens/ObjetosDeInterface/Tutoriais/Mini_Game_Corrida/tutorial_minigame_corrida_0.tga", NULL);
     minigame [1] = load_bitmap ("Imagens/ObjetosDeInterface/Tutoriais/Mini_Game_Corrida/tutorial_minigame_corrida_1.tga", NULL);
     minigame [2] = load_bitmap ("Imagens/ObjetosDeInterface/Tutoriais/Mini_Game_Corrida/tutorial_minigame_corrida_2.tga", NULL);
     
     if (posicao_tutorial < 3) {
         set_alpha_blender();
         draw_trans_sprite(buffer_atual, minigame[posicao_tutorial], 0, 0);
     }
     
     destroy_bitmap (minigame [0]);
     destroy_bitmap (minigame [1]);
     destroy_bitmap (minigame [2]);
}

// Tutorial_Mini_Game_Ginasio_0 //
void tutorial_minigame_ginasio_1 (BITMAP *buffer_atual, int posicao_tutorial) {
     BITMAP *minigame [4]; 
     
     minigame [0] = load_bitmap ("Imagens/ObjetosDeInterface/Tutoriais/Mini_Game_Pergunta_Resposta/tutorial_minigame_pergunta_resposta_0.tga", NULL);
     minigame [1] = load_bitmap ("Imagens/ObjetosDeInterface/Tutoriais/Mini_Game_Pergunta_Resposta/tutorial_minigame_pergunta_resposta_1.tga", NULL);
     minigame [2] = load_bitmap ("Imagens/ObjetosDeInterface/Tutoriais/Mini_Game_Pergunta_Resposta/tutorial_minigame_pergunta_resposta_2.tga", NULL);
     minigame [3] = load_bitmap ("Imagens/ObjetosDeInterface/Tutoriais/Mini_Game_Pergunta_Resposta/tutorial_minigame_pergunta_resposta_3.tga", NULL);
     
     if (posicao_tutorial < 4) {
         set_alpha_blender();
         draw_trans_sprite(buffer_atual, minigame[posicao_tutorial], 0, 0);
     }
     
     destroy_bitmap (minigame [0]);
     destroy_bitmap (minigame [1]);
     destroy_bitmap (minigame [2]);
     destroy_bitmap (minigame [3]);
}

// Efeito Fim //
void efeito_fim (BITMAP *buffer_atual) {
     BITMAP *fim; 
     
     fim = load_bitmap ("Imagens/FimDeJogo/fim.tga", NULL);
   
     set_alpha_blender();
     draw_trans_sprite(buffer_atual, fim, 50, 239.5);

     destroy_bitmap (fim);
}
             

// Tutorial Mini Game Ginasio Fim //
void tutorial_minigame_ginasio_fim (BITMAP *buffer_atual, int posicao_tutorial) {
     BITMAP *minigame [2]; 
     
     minigame [0] = load_bitmap ("Imagens/ObjetosDeInterface/Tutoriais/Mini_Game_Ginasio_Fim/fim_treinamento_ginasio.tga", NULL);
     minigame [1] = load_bitmap ("Imagens/ObjetosDeInterface/Tutoriais/Mini_Game_Ginasio_Fim/fim_treinamento_ginasio.tga", NULL);
   
     if (posicao_tutorial < 1) {
         set_alpha_blender();
         draw_trans_sprite(buffer_atual, minigame[posicao_tutorial], 0, 0);
     }
     
     destroy_bitmap (minigame [0]);
     destroy_bitmap (minigame [1]);
}

// Tutorial Cuidado com a Chuva //
void tutorial_chuva (BITMAP *buffer_atual) {
     BITMAP *chuva; 
     
     chuva = load_bitmap ("Imagens/ObjetosDeInterface/Tutoriais/tutorial_cuidado_chuva.tga", NULL);
   
     set_alpha_blender();
     draw_trans_sprite(buffer_atual, chuva, 0, 0);
     
     destroy_bitmap (chuva);
}    

// Texto Ganhou Habilidade1 //
void tutorial_habilidade1 (BITMAP *buffer_atual, int posicao_tutorial) {
     BITMAP *tutorial_habilidade [2]; 
     
     tutorial_habilidade [0] = load_bitmap ("Imagens/ObjetosDeInterface/Tutoriais/tutorial_habilidade_chute_bico_0.tga", NULL);
     tutorial_habilidade [1] = load_bitmap ("Imagens/ObjetosDeInterface/Tutoriais/tutorial_habilidade_chute_bico_1.tga", NULL);
     
     if (posicao_tutorial < 2) {
         set_alpha_blender();
         draw_trans_sprite(buffer_atual, tutorial_habilidade[posicao_tutorial], 0, 0);
     }
     
     destroy_bitmap (tutorial_habilidade [0]);
     destroy_bitmap (tutorial_habilidade [1]);
}

// Animacao Tecla Esc //
void animacao_tecla_esc (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *animacao_delay) {
    BITMAP *tecla_esc [2];
    
    tecla_esc [0] = load_bitmap ("Imagens/ObjetosDeInterface/Teclas/animacao_esc_0.bmp", NULL);
    tecla_esc [1] = load_bitmap ("Imagens/ObjetosDeInterface/Teclas/animacao_esc_1.bmp", NULL);
    
    *animacao_delay = *animacao_delay + 1;
    if (*animacao_delay > 8) {
        *animacao = *animacao + 1;             
        *animacao_delay = 0;
    }
    
    if (*animacao  > 1) {
        *animacao  = 0;
    }
    
    draw_sprite(buffer_atual, tecla_esc [*animacao], posicao_x, posicao_y);
    
    destroy_bitmap (tecla_esc [0]);
    destroy_bitmap (tecla_esc [1]);        
}


// Animacao Tecla Enter //
void animacao_tecla_enter (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *animacao_delay) {
    BITMAP *tecla_enter [2];
    
    tecla_enter [0] = load_bitmap ("Imagens/ObjetosDeInterface/Teclas/animacao_enter_0.bmp", NULL);
    tecla_enter [1] = load_bitmap ("Imagens/ObjetosDeInterface/Teclas/animacao_enter_1.bmp", NULL);

    *animacao_delay = *animacao_delay + 1;
    if (*animacao_delay > 8) {
        *animacao = *animacao + 1;             
        *animacao_delay = 0;
    }
    
    if (*animacao  > 1) {
        *animacao  = 0;
    }
    
    draw_sprite(buffer_atual, tecla_enter [*animacao], posicao_x, posicao_y);
    
    destroy_bitmap (tecla_enter [0]);
    destroy_bitmap (tecla_enter [1]);        
}


// Animacao Agua Com Chafariz //
void efeito_agua (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao_1, int *delay_animacao_1, int *animacao_2, int *delay_animacao_2) {
    
    int i;
    BITMAP *poste;
    BITMAP *animacao_agua [3];
    BITMAP *animacao_chafariz [3];
    
    *delay_animacao_1 = *delay_animacao_1 + 1;
    *delay_animacao_2 = *delay_animacao_2 + 1;
    
    if (*delay_animacao_1 > 5) {
        *animacao_1 = *animacao_1 + 1;
        *delay_animacao_1 = 0;
    }
    
    if (*delay_animacao_2 > 2) {
        *animacao_2 = *animacao_2 + 1;
        *delay_animacao_2 = 0;
    }
    
    
    animacao_agua  [0] = load_jpg ("Imagens/EstilosCenarios/Objetos/Aguas/agua_0.jpg", NULL);
    animacao_agua  [1] = load_jpg ("Imagens/EstilosCenarios/Objetos/Aguas/agua_1.jpg", NULL);
    animacao_agua  [2] = load_jpg ("Imagens/EstilosCenarios/Objetos/Aguas/agua_2.jpg", NULL);
    
    animacao_chafariz  [0] = load_bitmap ("Imagens/EstilosCenarios/Objetos/Chafariz/chafariz_0.tga", NULL);
    animacao_chafariz  [1] = load_bitmap ("Imagens/EstilosCenarios/Objetos/Chafariz/chafariz_1.tga", NULL);
    animacao_chafariz  [2] = load_bitmap ("Imagens/EstilosCenarios/Objetos/Chafariz/chafariz_2.tga", NULL);
    
    poste = load_bitmap ("Imagens/EstilosCenarios/Objetos/Poste/poste.bmp", NULL);
    
    
    if (*animacao_1 > 2) {
        *animacao_1 = 0;
    }
    
    if (*animacao_2 > 2) {
        *animacao_2 = 0;
    }
    
    set_alpha_blender();
    draw_sprite(buffer_atual, animacao_agua [*animacao_1], posicao_x, posicao_y);
    draw_trans_sprite(buffer_atual, animacao_chafariz [*animacao_2], posicao_x + 70, posicao_y + 20);
    draw_trans_sprite(buffer_atual, animacao_chafariz [*animacao_2], posicao_x + 110, posicao_y + 20);
    draw_sprite(buffer_atual, poste, posicao_x - 63, posicao_y + 22);
    draw_sprite(buffer_atual, poste, posicao_x + 225, posicao_y + 22);
    
    for (i = 0; i < 3; i++) {
        destroy_bitmap (animacao_agua [i]);
        destroy_bitmap (animacao_chafariz [i]);
    }   
    destroy_bitmap (poste);
}    


// Movimentar Sprite Automaticamente //   
void movimentarSpriteAutomaticamente(int *x, int *y, int *lado, int *animacao, int *delayanimacao, int terreno, int sentido, int posicao_inicial, int posicao_final, int tempo_espera, int *delayanimacao_2, int velocidade_animacao) {   
    *delayanimacao = *delayanimacao - 1;
    *delayanimacao_2 = *delayanimacao_2 + 1;
    if (sentido == 2) { 
        if (*delayanimacao  <= 0) {
            if ((*lado == 1) || (*lado == 0) || (*lado == 2)) {
                *lado = 1;
                if (*x < posicao_final) {
                    *x = *x + terreno;
                    if (*delayanimacao_2 > velocidade_animacao) {
                        *delayanimacao_2 = 0;
                        *animacao = *animacao + 1;                      
                    }  
                } else {
                    *lado = 3;
                    *delayanimacao = tempo_espera;
                    *animacao = 0;              
                }
            }
        }
        if (*delayanimacao  <= 0) {
            if ((*lado == 3) || (*lado == 0) || (*lado ==2)) {
                *lado = 3;
                if (*x > posicao_inicial) {
                    *x = *x - terreno;
                    if (*delayanimacao_2 > velocidade_animacao) {
                        *delayanimacao_2 = 0;
                        *animacao = *animacao + 1;                      
                    }   
                } else {
                    *lado = 1;
                    *delayanimacao = tempo_espera;
                    *animacao = 0;   
                }            
            }
        }
    }
    
    if (sentido == 1) {
        if (*delayanimacao  <= 0) {
            if ((*lado == 0)  || (*lado == 1) || (*lado == 3)){
                *lado = 0;
                if (*y < posicao_final) {
                    *y = *y + terreno;
                    if (*delayanimacao_2 > velocidade_animacao) {
                        *delayanimacao_2 = 0;
                        *animacao = *animacao + 1;                      
                    }  
                } else {
                    *lado = 2;
                    *delayanimacao = tempo_espera;
                    *animacao = 0;           
                }
            }
        }
        if (*delayanimacao  <= 0) {
            if ((*lado == 2)  || (*lado == 1) || (*lado == 3)) {
                *lado = 2;
                if (*y > posicao_inicial) {
                    *y = *y - terreno;
                    if (*delayanimacao_2 > velocidade_animacao) {
                        *delayanimacao_2 = 0;
                        *animacao = *animacao + 1;                      
                    }   
                } else {
                    *lado = 0;
                    *delayanimacao = tempo_espera;
                    *animacao = 0;    
                }            
            }
        }
    }
    
    
    if (*animacao > 3) {
        *animacao = 0;
    }
}


// Animacação Fogo //
void efeito_fogo(BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao) {
    BITMAP *fogo [4];
    *delay_animacao = *delay_animacao + 1;
    
    if (*delay_animacao > 1) {
         *animacao = *animacao + 1;
         *delay_animacao = 0;
    }
    
    fogo  [0] = load_bitmap ("Imagens/EstilosCenarios/Objetos/Bola_Brilhante/efeito_bola_brilhante_0.tga", NULL);
    fogo  [1] = load_bitmap ("Imagens/EstilosCenarios/Objetos/Bola_Brilhante/efeito_bola_brilhante_1.tga", NULL);
    fogo  [2] = load_bitmap ("Imagens/EstilosCenarios/Objetos/Bola_Brilhante/efeito_bola_brilhante_2.tga", NULL);
    fogo  [3] = load_bitmap ("Imagens/EstilosCenarios/Objetos/Bola_Brilhante/efeito_bola_brilhante_1.tga", NULL); 
     
    if (*animacao > 3) {
        *animacao = 0;
    }
    
    set_alpha_blender();
    draw_trans_sprite(buffer_atual, fogo [*animacao], posicao_x - 7, posicao_y - 10);
    
    destroy_bitmap (fogo [0]);
    destroy_bitmap (fogo [1]);
    destroy_bitmap (fogo [2]);
    destroy_bitmap (fogo [3]);
}


//  Animacao Barra de Status //
void efeito_barra_de_status_personagem (BITMAP *buffer_atual, int vigor_personagem, int energia_personagem, int *animacao, int *delay_animacao, int moedas, DATAFILE *fonte, int porcentagem_experiencia, int nivel) {
    int i;
    int posicao_experiencia = 55;
    
    BITMAP *barra_de_status;
    BITMAP *barra_de_experiencia;
    BITMAP *barra_de_habilidades;
    BITMAP *barra_de_moedas;
    
    BITMAP *animacao_experiencia;
    BITMAP *animacao_vigor [3];
    BITMAP *animacao_energia [3];
    
    char txt_moedas [5];
    char txt_nivel  [3];
    
    *delay_animacao = *delay_animacao + 1;
    if (*delay_animacao > 1) {
        *animacao = *animacao + 1;
        *delay_animacao = 0;
    }
    
    barra_de_status       = load_bitmap ("Imagens/InformacoesJogador/Barra_Status/barra_status.tga", NULL);
    barra_de_experiencia  = load_bitmap ("Imagens/InformacoesJogador/Barra_Experiencia/barra_de_experiencia.bmp", NULL);
    barra_de_habilidades  = load_bitmap ("Imagens/InformacoesJogador/Barra_Habilidades/barra_de_habilidades.tga", NULL);
    barra_de_moedas       = load_bitmap ("Imagens/InformacoesJogador/Barra_Moedas/barra_de_moedas.tga", NULL);
    
    animacao_experiencia  = load_bitmap ("Imagens/InformacoesJogador/Barra_Experiencia/experiencia_0.jpg", NULL);
     
    animacao_vigor  [0] = load_jpg ("Imagens/InformacoesJogador/Barra_Vigor/vigor_0.jpg", NULL);
    animacao_vigor  [1] = load_jpg ("Imagens/InformacoesJogador/Barra_Vigor/vigor_1.jpg", NULL);
    animacao_vigor  [2] = load_jpg ("Imagens/InformacoesJogador/Barra_Vigor/vigor_2.jpg", NULL);
    
    animacao_energia  [0] = load_jpg ("Imagens/InformacoesJogador/Barra_Energia/energia_0.jpg", NULL);
    animacao_energia  [1] = load_jpg ("Imagens/InformacoesJogador/Barra_Energia/energia_1.jpg", NULL);
    animacao_energia  [2] = load_jpg ("Imagens/InformacoesJogador/Barra_Energia/energia_2.jpg", NULL);
    
    set_alpha_blender();
    draw_trans_sprite(buffer_atual, barra_de_habilidades, 5, 120);
    draw_trans_sprite(buffer_atual, barra_de_moedas, 680, 3);
    
    if (*animacao > 2) {
        *animacao = 0;
    }
    
    if (vigor_personagem == 6) {
        draw_sprite(buffer_atual, animacao_vigor [*animacao], 18, 8);
        draw_sprite(buffer_atual, animacao_vigor [*animacao], 57, 8);    
        draw_sprite(buffer_atual, animacao_vigor [*animacao], 96, 8);
        draw_sprite(buffer_atual, animacao_vigor [*animacao], 135, 8);
        draw_sprite(buffer_atual, animacao_vigor [*animacao], 174, 8);
        draw_sprite(buffer_atual, animacao_vigor [*animacao], 213, 8);              
    } else if (vigor_personagem == 5) {
        draw_sprite(buffer_atual, animacao_vigor [*animacao], 18, 8);
        draw_sprite(buffer_atual, animacao_vigor [*animacao], 57, 8);    
        draw_sprite(buffer_atual, animacao_vigor [*animacao], 96, 8);
        draw_sprite(buffer_atual, animacao_vigor [*animacao], 135, 8);
        draw_sprite(buffer_atual, animacao_vigor [*animacao], 174, 8);     
    } else if (vigor_personagem == 4) {
        draw_sprite(buffer_atual, animacao_vigor [*animacao], 18, 8);
        draw_sprite(buffer_atual, animacao_vigor [*animacao], 57, 8);    
        draw_sprite(buffer_atual, animacao_vigor [*animacao], 96, 8);
        draw_sprite(buffer_atual, animacao_vigor [*animacao], 135, 8);
    } else if (vigor_personagem == 3) {
        draw_sprite(buffer_atual, animacao_vigor [*animacao], 18, 8);
        draw_sprite(buffer_atual, animacao_vigor [*animacao], 57, 8);    
        draw_sprite(buffer_atual, animacao_vigor [*animacao], 96, 8);
    } else if (vigor_personagem == 2) {
        draw_sprite(buffer_atual, animacao_vigor [*animacao], 18, 8);
        draw_sprite(buffer_atual, animacao_vigor [*animacao], 57, 8);    
    } else if (vigor_personagem == 1) {
        draw_sprite(buffer_atual, animacao_vigor [*animacao], 18, 8);
    }
    
    if (energia_personagem == 3) {
        draw_sprite(buffer_atual, animacao_energia [*animacao], 19, 43);
        draw_sprite(buffer_atual, animacao_energia [*animacao], 82, 43);    
        draw_sprite(buffer_atual, animacao_energia [*animacao], 145,43);        
    } else if (energia_personagem == 2) {
        draw_sprite(buffer_atual, animacao_energia [*animacao], 19, 43);
        draw_sprite(buffer_atual, animacao_energia [*animacao], 82, 43);       
    } else if (energia_personagem == 1) {
        draw_sprite(buffer_atual, animacao_energia [*animacao], 19, 43);
    } 
    
    sprintf(txt_moedas, "%d", moedas);
    textout_ex(buffer_atual, (FONT *)fonte[0].dat, txt_moedas, 737, 20, makecol(7,126,1),-1 );
    
    set_alpha_blender();
    draw_trans_sprite(buffer_atual, barra_de_status, 5, 5);
    
    sprintf(txt_nivel, "%d", nivel);
    textout_ex(buffer_atual, (FONT *)fonte[0].dat, txt_nivel, 70, 67, makecol(0,0,0),-1 );
    
    if (nivel != 99) {
        for (i=0; i < porcentagem_experiencia; i++) {
            draw_sprite(buffer_atual, animacao_experiencia, posicao_experiencia, 578);
            posicao_experiencia = posicao_experiencia + 7;
        }
        draw_sprite(buffer_atual, barra_de_experiencia, 37, 576);
    }
    
    destroy_bitmap (barra_de_experiencia);
    destroy_bitmap (barra_de_status);
    destroy_bitmap (barra_de_habilidades);
    destroy_bitmap (barra_de_moedas);
    destroy_bitmap (animacao_vigor  [0]);
    destroy_bitmap (animacao_vigor  [1]);
    destroy_bitmap (animacao_vigor  [2]);
    destroy_bitmap (animacao_energia  [0]);
    destroy_bitmap (animacao_energia  [1]);
    destroy_bitmap (animacao_energia  [2]);
    destroy_bitmap (animacao_experiencia);
}


// Animação Choro //
void efeito_choro(BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao) {
    BITMAP *choro [3];
    *delay_animacao = *delay_animacao + 1;
    
    if (*delay_animacao > 2) {
        *animacao = *animacao + 1;
        *delay_animacao = 0;
    }
    
    choro [0] = load_bitmap ("Imagens/FimDeJogo/choro_0.bmp", NULL);
    choro [1] = load_bitmap ("Imagens/FimDeJogo/choro_1.bmp", NULL);
    choro [2] = load_bitmap ("Imagens/FimDeJogo/choro_2.bmp", NULL); 
    
    if (*animacao > 2) {
        *animacao = 0;
    }
    set_trans_blender(0,0,0,60);
    
    draw_trans_sprite (buffer_atual, choro [*animacao], posicao_x, posicao_y);
    
    destroy_bitmap (choro [0]);
    destroy_bitmap (choro [1]);
    destroy_bitmap (choro [2]);
}


// Efeito Bola Opcao Fim de Jogo //
int efeito_bola_opcao_fim_de_jogo (BITMAP *buffer_atual, int opcao_escolhida, int *animacao, int *delay_animacao) {
    
    BITMAP *cursor_efeito [4];    
    SAMPLE *audio_efeito_menu [2];
    
    int cont = 0; 
    *delay_animacao = *delay_animacao + 1;
    
    if (*delay_animacao > 0) {
        *animacao = *animacao + 1;
        *delay_animacao = 0;
    }
    
    audio_efeito_menu [0] = load_sample("Audios/Efeito/efeito_escolha.wav");
    audio_efeito_menu [1] = load_sample("Audios/Efeito/efeito_apito.wav"); 
   
    
    cursor_efeito [0]  = load_bitmap ("Imagens/ObjetosDeInterface/Cursores/cursor_opcao_efeito_0.tga",NULL);
    cursor_efeito [1]  = load_bitmap ("Imagens/ObjetosDeInterface/Cursores/cursor_opcao_efeito_1.tga",NULL);
    cursor_efeito [2]  = load_bitmap ("Imagens/ObjetosDeInterface/Cursores/cursor_opcao_efeito_2.tga",NULL);
    cursor_efeito [3]  = load_bitmap ("Imagens/ObjetosDeInterface/Cursores/cursor_opcao_efeito_3.tga",NULL);

    if (key [KEY_RIGHT]) { 
        if (opcao_escolhida == 1) {
            play_sample (audio_efeito_menu [0], 500, 128, 1000, 0);
        }
    opcao_escolhida = 2;
    } else if (key [KEY_LEFT]) {
        if (opcao_escolhida == 2) {
            play_sample (audio_efeito_menu [0], 500, 128, 1000, 0);
        }
    opcao_escolhida = 1;
    }

     
    if (*animacao > 3) {
        *animacao = 0;
    }
    
    set_alpha_blender();
    if (opcao_escolhida == 2) {                 
        draw_trans_sprite(buffer_atual, cursor_efeito [*animacao], 445,490);
        draw_trans_sprite(buffer_atual, cursor_efeito [*animacao], 610,490);
    } else {
        draw_trans_sprite(buffer_atual, cursor_efeito [*animacao], 147,490);
        draw_trans_sprite(buffer_atual, cursor_efeito [*animacao], 287,490);
    }
    
    if ((opcao_escolhida == 1) && (key[KEY_ENTER])) {
        play_sample (audio_efeito_menu [1], 500, 128, 1000, 0);
        opcao_escolhida = 0;                    
    } else if ((opcao_escolhida == 2) && (key[KEY_ENTER])) {
        play_sample (audio_efeito_menu [1], 500, 128, 1000, 0);
        opcao_escolhida = -1;    
    }

    for (cont = 0; cont < 4; cont ++) {
        destroy_bitmap (cursor_efeito [cont]);
    } 
    return (opcao_escolhida);
}

// Efeito Ataque Bola //
void efeito_ataque (BITMAP *buffer_atual, int *posicao_bola_x, int *posicao_bola_y, int *delayanimacao, int *energia, int lado_personagem, int *animacao_personagem, BITMAP *bola [3], int *animacao, int *animacao_2) {
    *animacao   = *animacao + 1;
    *animacao_2 = *animacao_2 + 5;
    SAMPLE *audio_efeito;
    
    audio_efeito = load_sample("Audios/Efeito/efeito_chutar_bola.wav");
    
    if (*animacao > 2) {
        *animacao = 0;
    }
    
    if (*animacao_2 > 50) {
        *animacao_2 = 0;
    }
    
    if (*delayanimacao <= 0) { 
        if (*energia >= 2) {
            if (key [KEY_SPACE]) {
                *delayanimacao = 10;
                *energia = *energia - 3;
                *animacao_2 = 0;
                play_sample (audio_efeito, 500, 128, 1000, 0);
                *animacao_personagem = 1;      
            }
        }
    } else {     
       if (lado_personagem == 0) {
           *posicao_bola_y = *posicao_bola_y + *animacao_2;
           draw_sprite (buffer_atual, bola [*animacao], *posicao_bola_x, *posicao_bola_y + 10);
       } else if (lado_personagem == 1) {
           *posicao_bola_x = *posicao_bola_x + *animacao_2;
           draw_sprite (buffer_atual, bola [*animacao], *posicao_bola_x + 14, *posicao_bola_y + 8);
       } else if (lado_personagem == 2) {
           *posicao_bola_y = *posicao_bola_y - *animacao_2;
           draw_sprite (buffer_atual, bola [*animacao], *posicao_bola_x, *posicao_bola_y - 22);
       } else if (lado_personagem == 3) {
           *posicao_bola_x = *posicao_bola_x - *animacao_2;
           draw_sprite (buffer_atual, bola [*animacao], *posicao_bola_x - 13, *posicao_bola_y + 8);
       }              
    } 
}


// Efeito Moeda //
void efeito_moeda(BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao) {
    BITMAP *moeda [4];
    int i;
    
    *delay_animacao = *delay_animacao + 1;
    
    if (*delay_animacao > 2) {
        *animacao = *animacao + 1;
        *delay_animacao = 0;
    }
    
    if (*animacao > 3) {
        *animacao = 0;
    }
    
    moeda [0]  = load_bitmap ("Imagens/EstilosCenarios/Objetos/Moeda/moeda_0.bmp",NULL);
    moeda [1]  = load_bitmap ("Imagens/EstilosCenarios/Objetos/Moeda/moeda_1.bmp",NULL);
    moeda [2]  = load_bitmap ("Imagens/EstilosCenarios/Objetos/Moeda/moeda_2.bmp",NULL);
    moeda [3]  = load_bitmap ("Imagens/EstilosCenarios/Objetos/Moeda/moeda_3.bmp",NULL);
    
    draw_sprite(buffer_atual, moeda [*animacao], posicao_x, posicao_y);
    
    
    for (i=0; i < 4; i ++) {
        destroy_bitmap (moeda[i]);
    }        
}


// Detecção de Colisão com Moedas  //
int detectarColisaoMoeda(BITMAP *buffer_atual, int x1, int y1, int altura1, int largura1,
                       int x2, int y2, int altura2, int largura2, int *moeda_personagem, int moeda_adquirida) {
    int colisao = 1;
    
    if (x1 > altura2) {
    } else if (y1 > largura2) {
    } else if (largura1 < x2) {
    } else if (altura1 < y2) {
    } else { 
        colisao = 0;
    }
    if (colisao == 0) {
        BITMAP *pega_moeda_efeito;
        SAMPLE *audio_pega_moeda;
    
        pega_moeda_efeito  = load_bitmap ("Imagens/Animacoes/estrelas.bmp", NULL);
        audio_pega_moeda   = load_sample("Audios/Efeito/efeito_moeda.wav");          
        
        play_sample (audio_pega_moeda, 500, 128, 1000, 0);
        draw_sprite (buffer_atual, pega_moeda_efeito, x1, y1);
        *moeda_personagem = *moeda_personagem + moeda_adquirida;
        if (*moeda_personagem > 9999) {
            *moeda_personagem = 9999;
        }
        destroy_bitmap (pega_moeda_efeito);          
    }
    return (colisao);
}


// Animacação Torcedora //
void efeito_torcedora(BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao) {
    BITMAP *torcedora [4];
    *delay_animacao = *delay_animacao + 1;
    
    if (*delay_animacao > 14) {
         *animacao = *animacao + 1;
         *delay_animacao = 0;
    }
    
    torcedora [0] = load_bitmap ("Imagens/Personagens/Torcedora/torcedoras_0.bmp", NULL);
    torcedora [1] = load_bitmap ("Imagens/Personagens/Torcedora/torcedoras_1.bmp", NULL);
    torcedora [2] = load_bitmap ("Imagens/Personagens/Torcedora/torcedoras_2.bmp", NULL);
    torcedora [3] = load_bitmap ("Imagens/Personagens/Torcedora/torcedoras_1.bmp", NULL);
     
    if (*animacao > 3) {
        *animacao = 0;
    }
    
    draw_sprite(buffer_atual, torcedora [*animacao], posicao_x, posicao_y);
    
    destroy_bitmap (torcedora [0]);
    destroy_bitmap (torcedora [1]);
    destroy_bitmap (torcedora [2]);
    destroy_bitmap (torcedora [3]);
}


// Animacação Geovana Torcendo//
void efeito_geovana (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao) {
    BITMAP *geovana [4];
    *delay_animacao = *delay_animacao + 1;
    
    if (*delay_animacao > 14) {
         *animacao = *animacao + 1;
         *delay_animacao = 0;
    }
    
    geovana [0] = load_bitmap ("Imagens/Personagens/Geovana/Torcendo/geovana_0.bmp", NULL);
    geovana [1] = load_bitmap ("Imagens/Personagens/Geovana/Torcendo/geovana_1.bmp", NULL);
    geovana [2] = load_bitmap ("Imagens/Personagens/Geovana/Torcendo/geovana_2.bmp", NULL);
    geovana [3] = load_bitmap ("Imagens/Personagens/Geovana/Torcendo/geovana_1.bmp", NULL);
     
    if (*animacao > 3) {
        *animacao = 0;
    }
    
    draw_sprite(buffer_atual, geovana [*animacao], posicao_x, posicao_y);
    
    destroy_bitmap (geovana [0]);
    destroy_bitmap (geovana [1]);
    destroy_bitmap (geovana [2]);
    destroy_bitmap (geovana [3]);
}


// Animacação Jogadores da Direita//
void efeito_jogadores_direita_ginasio (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao) {
    BITMAP *jogadores [4];
    *delay_animacao = *delay_animacao + 1;
    
    if (*delay_animacao > 14) {
         *animacao = *animacao + 1;
         *delay_animacao = 0;
    }
    
    jogadores [0] = load_bitmap ("Imagens/Personagens/Jogadores2/jogadores_direita_0.bmp", NULL);
    jogadores [1] = load_bitmap ("Imagens/Personagens/Jogadores2/jogadores_direita_1.bmp", NULL);
    jogadores [2] = load_bitmap ("Imagens/Personagens/Jogadores2/jogadores_direita_2.bmp", NULL);
    jogadores [3] = load_bitmap ("Imagens/Personagens/Jogadores2/jogadores_direita_1.bmp", NULL);
     
    if (*animacao > 3) {
        *animacao = 0;
    }
    
    draw_sprite(buffer_atual, jogadores [*animacao], posicao_x, posicao_y);
    
    destroy_bitmap (jogadores [0]);
    destroy_bitmap (jogadores [1]);
    destroy_bitmap (jogadores [2]);
    destroy_bitmap (jogadores [3]);
}


// Animacação Jogadores da Esquerda//
void efeito_jogadores_esquerda_ginasio (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao) {
    BITMAP *jogadores [4];
    *delay_animacao = *delay_animacao + 1;
    
    if (*delay_animacao > 14) {
         *animacao = *animacao + 1;
         *delay_animacao = 0;
    }
    
    jogadores [0] = load_bitmap ("Imagens/Personagens/Jogadores1/jogadores_esquerda_0.bmp", NULL);
    jogadores [1] = load_bitmap ("Imagens/Personagens/Jogadores1/jogadores_esquerda_1.bmp", NULL);
    jogadores [2] = load_bitmap ("Imagens/Personagens/Jogadores1/jogadores_esquerda_2.bmp", NULL);
    jogadores [3] = load_bitmap ("Imagens/Personagens/Jogadores1/jogadores_esquerda_1.bmp", NULL);
     
    if (*animacao > 3) {
        *animacao = 0;
    }
    
    draw_sprite(buffer_atual, jogadores [*animacao], posicao_x, posicao_y);
    
    destroy_bitmap (jogadores [0]);
    destroy_bitmap (jogadores [1]);
    destroy_bitmap (jogadores [2]);
    destroy_bitmap (jogadores [3]);
}

// Animação Jogadores Embaixo //
void efeito_jogadores_embaixo_ginasio (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao) {
    BITMAP *jogadores [2];
    *delay_animacao = *delay_animacao + 1;
    
    if (*delay_animacao > 5) {
         *animacao = *animacao + 1;
         *delay_animacao = 0;
    }
    
    jogadores [0] = load_bitmap ("Imagens/Personagens/Jogadores1/jogadores_embaixo_0.bmp", NULL);
    jogadores [1] = load_bitmap ("Imagens/Personagens/Jogadores1/jogadores_embaixo_1.bmp", NULL);
    
    if (*animacao > 1) {
        *animacao = 0;
    }
    
    draw_sprite(buffer_atual, jogadores [*animacao], posicao_x, posicao_y);
    
    destroy_bitmap (jogadores [0]);
    destroy_bitmap (jogadores [1]);
}

// Animação Jogadores Encima//
void efeito_jogadores_encima_ginasio (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao) {
    BITMAP *jogadores [2];
    *delay_animacao = *delay_animacao + 1;
    
    if (*delay_animacao > 5) {
         *animacao = *animacao + 1;
         *delay_animacao = 0;
    }
    
    jogadores [0] = load_bitmap ("Imagens/Personagens/Jogadores1/jogadores_encima_0.bmp", NULL);
    jogadores [1] = load_bitmap ("Imagens/Personagens/Jogadores1/jogadores_encima_1.bmp", NULL);
    
    if (*animacao > 1) {
        *animacao = 0;
    }
    
    draw_sprite(buffer_atual, jogadores [*animacao], posicao_x, posicao_y);
    
    destroy_bitmap (jogadores [0]);
    destroy_bitmap (jogadores [1]);
}


// Animacação Pilar de Fogo Azul //
void efeito_pilar_de_fogo_azul(BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao) {
    BITMAP *pilar_de_fogo [4];
    
    *delay_animacao = *delay_animacao + 1;
    
    if (*delay_animacao > 3) {
         *animacao = *animacao + 1;
         *delay_animacao = 0;
    }
    
    pilar_de_fogo [0] = load_bitmap ("Imagens/EstilosCenarios/Objetos/Pilar_De_Fogo_Azul/pilar_de_fogo_azul_0.tga", NULL);
    pilar_de_fogo [1] = load_bitmap ("Imagens/EstilosCenarios/Objetos/Pilar_De_Fogo_Azul/pilar_de_fogo_azul_1.tga", NULL);
    pilar_de_fogo [2] = load_bitmap ("Imagens/EstilosCenarios/Objetos/Pilar_De_Fogo_Azul/pilar_de_fogo_azul_2.tga", NULL);
    pilar_de_fogo [3] = load_bitmap ("Imagens/EstilosCenarios/Objetos/Pilar_De_Fogo_Azul/pilar_de_fogo_azul_1.tga", NULL);
    
    if (*animacao > 3) {
        *animacao = 0;
    }
    
    set_alpha_blender();
    draw_trans_sprite(buffer_atual, pilar_de_fogo [*animacao], posicao_x, posicao_y);
    
    destroy_bitmap (pilar_de_fogo [0]);
    destroy_bitmap (pilar_de_fogo [1]);
    destroy_bitmap (pilar_de_fogo [2]);
    destroy_bitmap (pilar_de_fogo [3]);
}


// Animacação Pilar de Fogo Amarelo //
void efeito_pilar_de_fogo_amarelo(BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao) {
    BITMAP *pilar_de_fogo [4];
    
    *delay_animacao = *delay_animacao + 1;
    
    if (*delay_animacao > 3) {
         *animacao = *animacao + 1;
         *delay_animacao = 0;
    }
    
    pilar_de_fogo [0] = load_bitmap ("Imagens/EstilosCenarios/Objetos/Pilar_De_Fogo_Amarelo/pilar_de_fogo_amarelo_0.tga", NULL);
    pilar_de_fogo [1] = load_bitmap ("Imagens/EstilosCenarios/Objetos/Pilar_De_Fogo_Amarelo/pilar_de_fogo_amarelo_1.tga", NULL);
    pilar_de_fogo [2] = load_bitmap ("Imagens/EstilosCenarios/Objetos/Pilar_De_Fogo_Amarelo/pilar_de_fogo_amarelo_2.tga", NULL);
    pilar_de_fogo [3] = load_bitmap ("Imagens/EstilosCenarios/Objetos/Pilar_De_Fogo_Amarelo/pilar_de_fogo_amarelo_1.tga", NULL);
    
    if (*animacao > 3) {
        *animacao = 0;
    }
    
    set_alpha_blender();
    draw_trans_sprite(buffer_atual, pilar_de_fogo [*animacao], posicao_x, posicao_y);
    
    destroy_bitmap (pilar_de_fogo [0]);
    destroy_bitmap (pilar_de_fogo [1]);
    destroy_bitmap (pilar_de_fogo [2]);
    destroy_bitmap (pilar_de_fogo [3]);
}


// Animacação Balão Reticencias //
void efeito_balao_reticencias (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao) {
    if (*animacao <= 7) {
        int i;
        BITMAP *balao [8];
    
        *delay_animacao = *delay_animacao + 1;
    
        if (*delay_animacao > 1) {
           *animacao = *animacao + 1;
           *delay_animacao = 0;
        }
    
        balao [0] = load_bitmap ("Imagens/Animacoes/Reticencias/reticencias_0.tga", NULL);
        balao [1] = load_bitmap ("Imagens/Animacoes/Reticencias/reticencias_1.tga", NULL);
        balao [2] = load_bitmap ("Imagens/Animacoes/Reticencias/reticencias_2.tga", NULL);
        balao [3] = load_bitmap ("Imagens/Animacoes/Reticencias/reticencias_3.tga", NULL);
        balao [4] = load_bitmap ("Imagens/Animacoes/Reticencias/reticencias_4.tga", NULL);
        balao [5] = load_bitmap ("Imagens/Animacoes/Reticencias/reticencias_5.tga", NULL);
        balao [6] = load_bitmap ("Imagens/Animacoes/Reticencias/reticencias_6.tga", NULL);
        balao [7] = load_bitmap ("Imagens/Animacoes/Reticencias/reticencias_7.tga", NULL);
    
        if (*animacao <= 7) {
            set_alpha_blender();
            draw_trans_sprite(buffer_atual, balao [*animacao], posicao_x, posicao_y - 20);
        }
    
        for (i=0; i < 8; i++){
            destroy_bitmap (balao [i]);
        }
    }
}


// Animacação Balão Exclamação //
void efeito_balao_exclamacao(BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao) {
    if (*animacao <= 7) {
        int i;
        BITMAP *balao [8];
    
        *delay_animacao = *delay_animacao + 1;
    
        if (*delay_animacao > 1) {
            *animacao = *animacao + 1;
            *delay_animacao = 0;
        }
    
        balao [0] = load_bitmap ("Imagens/Animacoes/Exclamacao/exclamacao_0.tga", NULL);
        balao [1] = load_bitmap ("Imagens/Animacoes/Exclamacao/exclamacao_1.tga", NULL);
        balao [2] = load_bitmap ("Imagens/Animacoes/Exclamacao/exclamacao_2.tga", NULL);
        balao [3] = load_bitmap ("Imagens/Animacoes/Exclamacao/exclamacao_3.tga", NULL);
        balao [4] = load_bitmap ("Imagens/Animacoes/Exclamacao/exclamacao_4.tga", NULL);
        balao [5] = load_bitmap ("Imagens/Animacoes/Exclamacao/exclamacao_5.tga", NULL);
        balao [6] = load_bitmap ("Imagens/Animacoes/Exclamacao/exclamacao_6.tga", NULL);
        balao [7] = load_bitmap ("Imagens/Animacoes/Exclamacao/exclamacao_7.tga", NULL);
    
        if (*animacao <= 7) {
            set_alpha_blender();
            draw_trans_sprite(buffer_atual, balao [*animacao], posicao_x, posicao_y - 20);
        }
    
        for (i=0; i < 8; i++){
            destroy_bitmap (balao [i]);
        }
    }
}

// Animacação Balão Gota D'agua //
void efeito_balao_gota (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao) {         
    if (*animacao <= 7) { 
        int i;
        BITMAP *balao [8];
    
        *delay_animacao = *delay_animacao + 1;
    
        if (*delay_animacao > 1) {
            *animacao = *animacao + 1;
            *delay_animacao = 0;
        }
    
        balao [0] = load_bitmap ("Imagens/Animacoes/Gota/gota_0.tga", NULL);
        balao [1] = load_bitmap ("Imagens/Animacoes/Gota/gota_1.tga", NULL);
        balao [2] = load_bitmap ("Imagens/Animacoes/Gota/gota_2.tga", NULL);
        balao [3] = load_bitmap ("Imagens/Animacoes/Gota/gota_3.tga", NULL);
        balao [4] = load_bitmap ("Imagens/Animacoes/Gota/gota_4.tga", NULL);
        balao [5] = load_bitmap ("Imagens/Animacoes/Gota/gota_5.tga", NULL);
        balao [6] = load_bitmap ("Imagens/Animacoes/Gota/gota_6.tga", NULL);
        balao [7] = load_bitmap ("Imagens/Animacoes/Gota/gota_7.tga", NULL);
        
        if (*animacao <= 7) { 
            set_alpha_blender();
            draw_trans_sprite(buffer_atual, balao [*animacao], posicao_x, posicao_y - 20);
        }
        for (i=0; i < 8; i++){
            destroy_bitmap (balao [i]);
        }
    }
}

// Animacação Balão Nervoso //
void efeito_balao_nervoso (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao) {
    if (*animacao <= 7) {
        int i;
        BITMAP *balao [8];
    
        *delay_animacao = *delay_animacao + 1;
    
        if (*delay_animacao > 1) {
            *animacao = *animacao + 1;
            *delay_animacao = 0;
        }
    
        balao [0] = load_bitmap ("Imagens/Animacoes/Nervoso/nervoso_0.tga", NULL);
        balao [1] = load_bitmap ("Imagens/Animacoes/Nervoso/nervoso_1.tga", NULL);
        balao [2] = load_bitmap ("Imagens/Animacoes/Nervoso/nervoso_2.tga", NULL);
        balao [3] = load_bitmap ("Imagens/Animacoes/Nervoso/nervoso_3.tga", NULL);
        balao [4] = load_bitmap ("Imagens/Animacoes/Nervoso/nervoso_4.tga", NULL);
        balao [5] = load_bitmap ("Imagens/Animacoes/Nervoso/nervoso_5.tga", NULL);
        balao [6] = load_bitmap ("Imagens/Animacoes/Nervoso/nervoso_6.tga", NULL);
        balao [7] = load_bitmap ("Imagens/Animacoes/Nervoso/nervoso_7.tga", NULL);
    
        if (*animacao <= 7) {
            set_alpha_blender();
            draw_trans_sprite(buffer_atual, balao [*animacao], posicao_x, posicao_y - 20);
        }
    
        for (i=0; i < 8; i++){
            destroy_bitmap (balao [i]);
        }
    }
}


// Animacação Balão Coração //
void efeito_balao_coracao (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao) { 
    if (*animacao <= 7) {    
        int i;
        BITMAP *balao [8];
    
        *delay_animacao = *delay_animacao + 1;
    
        if (*delay_animacao > 1) {
            *animacao = *animacao + 1;
            *delay_animacao = 0;
        }
    
        balao [0] = load_bitmap ("Imagens/Animacoes/Coracao/coracao_0.tga", NULL);
        balao [1] = load_bitmap ("Imagens/Animacoes/Coracao/coracao_1.tga", NULL);
        balao [2] = load_bitmap ("Imagens/Animacoes/Coracao/coracao_2.tga", NULL);
        balao [3] = load_bitmap ("Imagens/Animacoes/Coracao/coracao_3.tga", NULL);
        balao [4] = load_bitmap ("Imagens/Animacoes/Coracao/coracao_4.tga", NULL);
        balao [5] = load_bitmap ("Imagens/Animacoes/Coracao/coracao_5.tga", NULL);
        balao [6] = load_bitmap ("Imagens/Animacoes/Coracao/coracao_6.tga", NULL);
        balao [7] = load_bitmap ("Imagens/Animacoes/Coracao/coracao_7.tga", NULL);
        
        if (*animacao <= 7) { 
            set_alpha_blender();
            draw_trans_sprite(buffer_atual, balao [*animacao], posicao_x, posicao_y - 20);
        }
        for (i=0; i < 8; i++){
            destroy_bitmap (balao [i]);
        }
    } 
}


// Animacação Subir Nível //
void efeito_subiu_nivel (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao) {
    if (*animacao <= 20) {
        int i;
    
        BITMAP *subiu_nivel [21];
        SAMPLE *audio_efeito_subiu_nivel;
        *delay_animacao = *delay_animacao + 1;
    
        subiu_nivel [0] = load_bitmap ("Imagens/Animacoes/Subiu_Nivel/subiu_nivel_0.tga", NULL);
        subiu_nivel [1] = load_bitmap ("Imagens/Animacoes/Subiu_Nivel/subiu_nivel_1.tga", NULL);
        subiu_nivel [2] = load_bitmap ("Imagens/Animacoes/Subiu_Nivel/subiu_nivel_2.tga", NULL);
        subiu_nivel [3] = load_bitmap ("Imagens/Animacoes/Subiu_Nivel/subiu_nivel_3.tga", NULL);
        subiu_nivel [4] = load_bitmap ("Imagens/Animacoes/Subiu_Nivel/subiu_nivel_4.tga", NULL);
        subiu_nivel [5] = load_bitmap ("Imagens/Animacoes/Subiu_Nivel/subiu_nivel_5.tga", NULL);
        subiu_nivel [6] = load_bitmap ("Imagens/Animacoes/Subiu_Nivel/subiu_nivel_6.tga", NULL);
        subiu_nivel [7] = load_bitmap ("Imagens/Animacoes/Subiu_Nivel/subiu_nivel_7.tga", NULL);
        subiu_nivel [8] = load_bitmap ("Imagens/Animacoes/Subiu_Nivel/subiu_nivel_8.tga", NULL);
        subiu_nivel [9] = load_bitmap ("Imagens/Animacoes/Subiu_Nivel/subiu_nivel_9.tga", NULL);
        subiu_nivel [10] = load_bitmap ("Imagens/Animacoes/Subiu_Nivel/subiu_nivel_10.tga", NULL);
        subiu_nivel [11] = load_bitmap ("Imagens/Animacoes/Subiu_Nivel/subiu_nivel_11.tga", NULL);
        subiu_nivel [12] = load_bitmap ("Imagens/Animacoes/Subiu_Nivel/subiu_nivel_12.tga", NULL);
        subiu_nivel [13] = load_bitmap ("Imagens/Animacoes/Subiu_Nivel/subiu_nivel_13.tga", NULL);
        subiu_nivel [14] = load_bitmap ("Imagens/Animacoes/Subiu_Nivel/subiu_nivel_14.tga", NULL);
        subiu_nivel [15] = load_bitmap ("Imagens/Animacoes/Subiu_Nivel/subiu_nivel_15.tga", NULL);
        subiu_nivel [16] = load_bitmap ("Imagens/Animacoes/Subiu_Nivel/subiu_nivel_16.tga", NULL);
        subiu_nivel [17] = load_bitmap ("Imagens/Animacoes/Subiu_Nivel/subiu_nivel_17.tga", NULL);
        subiu_nivel [18] = load_bitmap ("Imagens/Animacoes/Subiu_Nivel/subiu_nivel_18.tga", NULL);
        subiu_nivel [19] = load_bitmap ("Imagens/Animacoes/Subiu_Nivel/subiu_nivel_19.tga", NULL);
        subiu_nivel [20] = load_bitmap ("Imagens/Animacoes/Subiu_Nivel/subiu_nivel_20.tga", NULL);
    
        audio_efeito_subiu_nivel = load_sample ("Audios/Efeito/efeito_subiu_nivel.wav");
    

        set_alpha_blender();
        draw_trans_sprite(buffer_atual, subiu_nivel [*animacao], posicao_x - 70, posicao_y - 90);
    
        if (*delay_animacao > 0) {
            *animacao = *animacao + 1;
            *delay_animacao = 0;
        }
    
    
        if (*animacao == 1) {
            play_sample (audio_efeito_subiu_nivel , 500, 128, 1000, 0);
        }    
    
        for (i=0; i < 21; i++){
            destroy_bitmap (subiu_nivel [i]);
        }
    }
}

// Efeito Brilho na Tela //
void efeito_relampago(BITMAP *buffer_atual, int *animacao, int *delay_animacao) {
    *delay_animacao = *delay_animacao + 1;
    
    if (*delay_animacao > 1) {
        *animacao = *animacao + 1;
        *delay_animacao = 0;
    }    
    
    if (*animacao > 40) {
        *animacao = 0;
    }
    
    if (*animacao < 5) {
        int i;
        
        SAMPLE *efeito_relampago;
        SAMPLE *efeito_grito;
        
        BITMAP *relampago [5];
        
        efeito_relampago = load_sample("Audios/Efeito/efeito_raio.wav"); 
        efeito_grito     = load_sample("Audios/Efeito/efeito_ouch.wav");
        
        if ((*animacao == 2) && (*delay_animacao == 0)) {
            play_sample (efeito_relampago , 200, 128, 1000, 0);
        } else if ((*animacao == 4) && (*delay_animacao == 0)) {
            play_sample (efeito_grito , 255, 128, 1000, 0);
        } 
        
        relampago [0] = load_bitmap ("Imagens/Animacoes/Brilho_Tela/brilho_tela_0.tga", NULL);
        relampago [1] = load_bitmap ("Imagens/Animacoes/Brilho_Tela/brilho_tela_1.tga", NULL);
        relampago [2] = load_bitmap ("Imagens/Animacoes/Brilho_Tela/brilho_tela_2.tga", NULL);
        relampago [3] = load_bitmap ("Imagens/Animacoes/Brilho_Tela/brilho_tela_3.tga", NULL);
        relampago [4] = load_bitmap ("Imagens/Animacoes/Brilho_Tela/brilho_tela_4.tga", NULL);
        
        set_alpha_blender();
        draw_trans_sprite(buffer_atual, relampago [*animacao], 0, 0);
        
        for (i=0; i < 5; i++){
            destroy_bitmap (relampago [i]);
        }
    }
}



// Efeito Baú //
void efeito_bau (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao, int *animacao_brilho, int *delay_animacao_brilho, int acao_abrir) {
    int i;
    
    BITMAP *bau [4];

    SAMPLE *efeito_abrir_bau;

    
    if (acao_abrir == 0) {
        BITMAP *brilho_azul [4];
        BITMAP *bau;
        
        bau = load_bitmap ("Imagens/EstilosCenarios/Objetos/Bau/bau_0.tga", NULL);
        
        brilho_azul [0] = load_bitmap ("Imagens/Animacoes/Brilho_Terreo/efeito_brilho_bau_0.tga", NULL);
        brilho_azul [1] = load_bitmap ("Imagens/Animacoes/Brilho_Terreo/efeito_brilho_bau_1.tga", NULL);
        brilho_azul [2] = load_bitmap ("Imagens/Animacoes/Brilho_Terreo/efeito_brilho_bau_2.tga", NULL);
        brilho_azul [3] = load_bitmap ("Imagens/Animacoes/Brilho_Terreo/efeito_brilho_bau_3.tga", NULL);    
   
        set_alpha_blender();
        *delay_animacao_brilho = *delay_animacao_brilho + 1;
        if (*delay_animacao_brilho > 2) {
            *animacao_brilho = *animacao_brilho + 1;
            *delay_animacao_brilho = 0;
        }
        if (*animacao_brilho > 3) {
            *animacao_brilho = 0;
        }
        draw_trans_sprite(buffer_atual, brilho_azul [*animacao_brilho], posicao_x - 4, posicao_y - 3);
        draw_trans_sprite(buffer_atual, bau, posicao_x, posicao_y);
        
        for (i=0; i < 4; i++){
            destroy_bitmap (brilho_azul [i]);
        }
        destroy_bitmap (bau);
    } else {       
        if (*animacao < 3) {  
            BITMAP *bau [4];
        
            bau [0] = load_bitmap ("Imagens/EstilosCenarios/Objetos/Bau/bau_0.tga", NULL);
            bau [1] = load_bitmap ("Imagens/EstilosCenarios/Objetos/Bau/bau_1.tga", NULL);
            bau [2] = load_bitmap ("Imagens/EstilosCenarios/Objetos/Bau/bau_2.tga", NULL);
            bau [3] = load_bitmap ("Imagens/EstilosCenarios/Objetos/Bau/bau_3.tga", NULL);   
                          
            *delay_animacao = *delay_animacao + 1;
            set_alpha_blender();
            draw_trans_sprite(buffer_atual, bau [*animacao], posicao_x, posicao_y);
            if (*delay_animacao > 0) {
                *animacao = *animacao + 1;
                *delay_animacao = 0;
            }
            efeito_abrir_bau = load_sample ("Audios/Efeito/efeito_abreporta.wav");
            if (*animacao == 1) {
                play_sample (efeito_abrir_bau , 500, 128, 1000, 0);
            }  

            *animacao_brilho       = -1;
            *delay_animacao_brilho = 0;
            
            for (i=0; i < 4; i++){
                destroy_bitmap (bau [i]);
            }
            
        } else {
            BITMAP *bau;
            
            bau = load_bitmap ("Imagens/EstilosCenarios/Objetos/Bau/bau_3.tga", NULL);   
            
            *delay_animacao_brilho = *delay_animacao_brilho + 1;
            if (*delay_animacao_brilho > 0) {
                *animacao_brilho = *animacao_brilho + 1;
                *delay_animacao_brilho = 0;
            }
            
            set_alpha_blender();
            draw_trans_sprite(buffer_atual, bau, posicao_x, posicao_y);
            
            if (*animacao_brilho < 7) {
                BITMAP *bau_brilho_abrir [7];
                
                bau_brilho_abrir [0] = load_bitmap ("Imagens/EstilosCenarios/Objetos/Bau/efeito_bau_0.tga", NULL);
                bau_brilho_abrir [1] = load_bitmap ("Imagens/EstilosCenarios/Objetos/Bau/efeito_bau_1.tga", NULL);
                bau_brilho_abrir [2] = load_bitmap ("Imagens/EstilosCenarios/Objetos/Bau/efeito_bau_2.tga", NULL);
                bau_brilho_abrir [3] = load_bitmap ("Imagens/EstilosCenarios/Objetos/Bau/efeito_bau_3.tga", NULL);
                bau_brilho_abrir [4] = load_bitmap ("Imagens/EstilosCenarios/Objetos/Bau/efeito_bau_4.tga", NULL);
                bau_brilho_abrir [5] = load_bitmap ("Imagens/EstilosCenarios/Objetos/Bau/efeito_bau_5.tga", NULL);
                bau_brilho_abrir [6] = load_bitmap ("Imagens/EstilosCenarios/Objetos/Bau/efeito_bau_6.tga", NULL);
                
                set_alpha_blender();
                draw_trans_sprite(buffer_atual, bau_brilho_abrir [*animacao_brilho], posicao_x - 35, posicao_y - 35);
                
                for (i=0; i < 7; i++){
                    destroy_bitmap (bau_brilho_abrir [i]);
                }
                destroy_bitmap (bau);
            
            }
        }
    }
}


// Efeito Ganhar Habilidade //
void efeito_ganhar_habilidade (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao) {
    if (*animacao <= 13) {
        int i;
    
        BITMAP *ganhar_habilidade[14];
        SAMPLE *audio_habilidade;
    
        audio_habilidade = load_sample ("Audios/Efeito/efeito_ganha_habilidade.wav");
    
        *delay_animacao = *delay_animacao + 1;
    
        
        ganhar_habilidade [0] = load_bitmap ("Imagens/Animacoes/Ganhou_Habilidade/efeito_ganha_habilidade_0.tga", NULL);
        ganhar_habilidade [1] = load_bitmap ("Imagens/Animacoes/Ganhou_Habilidade/efeito_ganha_habilidade_1.tga", NULL);
        ganhar_habilidade [2] = load_bitmap ("Imagens/Animacoes/Ganhou_Habilidade/efeito_ganha_habilidade_2.tga", NULL);
        ganhar_habilidade [3] = load_bitmap ("Imagens/Animacoes/Ganhou_Habilidade/efeito_ganha_habilidade_3.tga", NULL);
        ganhar_habilidade [4] = load_bitmap ("Imagens/Animacoes/Ganhou_Habilidade/efeito_ganha_habilidade_4.tga", NULL);
        ganhar_habilidade [5] = load_bitmap ("Imagens/Animacoes/Ganhou_Habilidade/efeito_ganha_habilidade_5.tga", NULL);
        ganhar_habilidade [6] = load_bitmap ("Imagens/Animacoes/Ganhou_Habilidade/efeito_ganha_habilidade_6.tga", NULL);
        ganhar_habilidade [7] = load_bitmap ("Imagens/Animacoes/Ganhou_Habilidade/efeito_ganha_habilidade_7.tga", NULL);
        ganhar_habilidade [8] = load_bitmap ("Imagens/Animacoes/Ganhou_Habilidade/efeito_ganha_habilidade_8.tga", NULL);
        ganhar_habilidade [9] = load_bitmap ("Imagens/Animacoes/Ganhou_Habilidade/efeito_ganha_habilidade_9.tga", NULL);
        ganhar_habilidade [10] = load_bitmap ("Imagens/Animacoes/Ganhou_Habilidade/efeito_ganha_habilidade_10.tga", NULL);
        ganhar_habilidade [11] = load_bitmap ("Imagens/Animacoes/Ganhou_Habilidade/efeito_ganha_habilidade_11.tga", NULL);
        ganhar_habilidade [12] = load_bitmap ("Imagens/Animacoes/Ganhou_Habilidade/efeito_ganha_habilidade_12.tga", NULL);
        ganhar_habilidade [13] = load_bitmap ("Imagens/Animacoes/Ganhou_Habilidade/efeito_ganha_habilidade_13.tga", NULL);
    
        set_alpha_blender();
        draw_trans_sprite(buffer_atual, ganhar_habilidade [*animacao], posicao_x, posicao_y);
    
        if (*delay_animacao > 0) {
            *animacao = *animacao + 1;
            *delay_animacao = 0;
        }

        if (*animacao == 1) {
            play_sample (audio_habilidade , 200, 128, 1000, 0);
        }    
        for (i=0; i < 14; i++){
            destroy_bitmap (ganhar_habilidade [i]);
        }
    }
}                

// Efeito Habilidade 1 Ativa //
void efeito_habilidade_1_ativa (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao){
    if (*animacao <= 5) {
        int i;
        
        BITMAP *habilidade_1[6];
        *delay_animacao = *delay_animacao + 1;
    
        habilidade_1 [0] = load_bitmap ("Imagens/InformacoesJogador/Habilidade1/habilidade1_0.tga", NULL);
        habilidade_1 [1] = load_bitmap ("Imagens/InformacoesJogador/Habilidade1/habilidade1_1.tga", NULL);
        habilidade_1 [2] = load_bitmap ("Imagens/InformacoesJogador/Habilidade1/habilidade1_2.tga", NULL);
        habilidade_1 [3] = load_bitmap ("Imagens/InformacoesJogador/Habilidade1/habilidade1_3.tga", NULL);
        habilidade_1 [4] = load_bitmap ("Imagens/InformacoesJogador/Habilidade1/habilidade1_4.tga", NULL);
        habilidade_1 [5] = load_bitmap ("Imagens/InformacoesJogador/Habilidade1/habilidade1_5.tga", NULL);
    
        set_alpha_blender();
        draw_trans_sprite(buffer_atual, habilidade_1 [*animacao], posicao_x, posicao_y);
        
        if (*delay_animacao > 0) {
            *animacao = *animacao + 1;
            *delay_animacao = 0;
        }
        
        for (i=0; i < 6; i++){
            destroy_bitmap (habilidade_1 [i]);
        }
    } else {
        BITMAP *habilidade_1;
        if (*animacao != 6) *animacao = 6;
        habilidade_1 = load_bitmap ("Imagens/InformacoesJogador/Habilidade1/habilidade1_5.tga", NULL);
        
        set_alpha_blender();
        draw_trans_sprite(buffer_atual, habilidade_1, posicao_x, posicao_y);
        
        destroy_bitmap (habilidade_1);
    } 
}


// Efeito Contagem Regressiva //
void efeito_contagem_regressiva (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao) {
    if (*animacao <= 2) {
        int i;
    
        BITMAP *contagem_regressiva[3];
    
        *delay_animacao = *delay_animacao + 1;
        
        contagem_regressiva [0] = load_bitmap ("Imagens/Animacoes/Contagem_Regressiva/efeito_contagem_regressiva_0.tga", NULL);
        contagem_regressiva [1] = load_bitmap ("Imagens/Animacoes/Contagem_Regressiva/efeito_contagem_regressiva_1.tga", NULL);
        contagem_regressiva [2] = load_bitmap ("Imagens/Animacoes/Contagem_Regressiva/efeito_contagem_regressiva_2.tga", NULL);
        
        set_alpha_blender();
        draw_trans_sprite(buffer_atual, contagem_regressiva [*animacao], posicao_x, posicao_y);
    
        if (*delay_animacao > 14) {        //Porque o FPS está 15, logo acima de 14 será exato 1 Segundo
            *animacao = *animacao + 1;
            *delay_animacao = 0;
        }
   
        for (i=0; i < 3; i++){
            destroy_bitmap (contagem_regressiva [i]);
        }
    }
}

// Efeito Pressione Enter //
void efeito_pressione_enter (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao) {
    BITMAP *pressione_enter [2];
    
    *delay_animacao = *delay_animacao + 1;
    
    if (*delay_animacao > 0) {
         *animacao = *animacao + 1;
         *delay_animacao = 0;
    }
    
    pressione_enter [0] = load_bitmap ("Imagens/TelaInicial/Pressione_Enter/pressione_enter_0.tga", NULL);
    pressione_enter [1] = load_bitmap ("Imagens/TelaInicial/Pressione_Enter/pressione_enter_1.tga", NULL);

    if (*animacao > 1) {
        *animacao = 0;
    }
    
    set_alpha_blender();
    draw_trans_sprite(buffer_atual, pressione_enter [*animacao], posicao_x, posicao_y);
    
    destroy_bitmap (pressione_enter [0]);
    destroy_bitmap (pressione_enter [1]);
}

// Efeito Luz Poste a Noite //
void efeito_luz_poste (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao) {
    int i;
    
    BITMAP *luz_projetada [4];
    
    *delay_animacao = *delay_animacao + 1;
    
    if (*delay_animacao > 3) {
         *animacao = *animacao + 1;
         *delay_animacao = 0;
    }
    
    luz_projetada [0] = load_bitmap ("Imagens/Animacoes/Brilho_Lampada/efeito_luz_projetada_0.tga", NULL);
    luz_projetada [1] = load_bitmap ("Imagens/Animacoes/Brilho_Lampada/efeito_luz_projetada_1.tga", NULL);
    luz_projetada [2] = load_bitmap ("Imagens/Animacoes/Brilho_Lampada/efeito_luz_projetada_2.tga", NULL);
    luz_projetada [3] = load_bitmap ("Imagens/Animacoes/Brilho_Lampada/efeito_luz_projetada_3.tga", NULL);

    if (*animacao > 3) {
        *animacao = 0;
    }
    
    set_alpha_blender();
    draw_trans_sprite(buffer_atual, luz_projetada [*animacao], posicao_x - 345, posicao_y - 260);
    
    for (i=0; i<4; i++) {
        destroy_bitmap (luz_projetada [i]);    
    }
}

// Efeito Luz Poste a Noite //
void efeito_chuva_noite (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao) {
    BITMAP *chuva_noite [3];
    
    *delay_animacao = *delay_animacao + 1;
    
    if (*delay_animacao > 1) {
         *animacao = *animacao + 1;
         *delay_animacao = 0;
    }
    
    chuva_noite [0] = load_bitmap ("Imagens/Animacoes/Chuva/efeito_chuva_noite_0.tga", NULL);
    chuva_noite [1] = load_bitmap ("Imagens/Animacoes/Chuva/efeito_chuva_noite_1.tga", NULL);
    chuva_noite [2] = load_bitmap ("Imagens/Animacoes/Chuva/efeito_chuva_noite_2.tga", NULL);

    if (*animacao > 2) {
        *animacao = 0;
    }
    
    set_alpha_blender();
    draw_trans_sprite(buffer_atual, chuva_noite [*animacao], posicao_x, posicao_y);
    
    destroy_bitmap (chuva_noite [0]);
    destroy_bitmap (chuva_noite [1]);
    destroy_bitmap (chuva_noite [2]);
}

// Efeito Sombra Ginásio //
void efeito_sombra_ginasio (BITMAP *buffer_atual, int posicao_x, int posicao_y) {
    BITMAP *sombra_ginasio;
    
    sombra_ginasio = load_bitmap ("Imagens/EstilosCenarios/Objetos/Sombra_Ginásio/sombra_ginásio.tga", NULL);

    set_alpha_blender();
    draw_trans_sprite(buffer_atual, sombra_ginasio, posicao_x, posicao_y);
    
    destroy_bitmap (sombra_ginasio);
}

// Efeito Titulo do Jogo //
void titulo_jogo (BITMAP *buffer_atual, int posicao_x, int posicao_y) {
    BITMAP *titulo;
    BITMAP *mato_bola;
    
    titulo    = load_bitmap ("Imagens/TelaInicial/Titulo/Titulo_Jogo.tga", NULL);
    mato_bola = load_bitmap ("Imagens/TelaInicial/Titulo/Mato_Bola.tga", NULL);

    set_alpha_blender();
    draw_trans_sprite(buffer_atual, titulo, posicao_x, posicao_y);
    draw_trans_sprite(buffer_atual, mato_bola, 0, 380);
    
    destroy_bitmap (mato_bola);
    destroy_bitmap (titulo);
}         

// Menu Inicial Abrindo //
void menu_inicial_abrindo (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *efeito_sonoro) {  
    int i;
    
    if (*animacao < 16) {
        BITMAP *menu [16];
        
        menu [0] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_0.tga", NULL);  
        menu [1] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_1.tga", NULL);
        menu [2] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_2.tga", NULL);
        menu [3] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_3.tga", NULL);
        menu [4] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_4.tga", NULL);
        menu [5] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_5.tga", NULL);
        menu [6] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_6.tga", NULL);
        menu [7] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_7.tga", NULL);
        menu [8] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_8.tga", NULL);
        menu [9] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_9.tga", NULL);
        menu [10] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_10.tga", NULL);
        menu [11] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_11.tga", NULL);
        menu [12] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_12.tga", NULL);
        menu [13] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_13.tga", NULL);
        menu [14] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_14.tga", NULL);
        menu [15] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_15.tga", NULL);
        
        set_alpha_blender();
        draw_trans_sprite(buffer_atual, menu [*animacao], posicao_x,  posicao_y);     
        
        *animacao = *animacao + 1;
    
        if (*animacao == 6) {
            if (*efeito_sonoro == 0) {
                SAMPLE *audio;
                
                audio = load_sample("Audios/Efeito/efeito_voltar.wav");
                
                play_sample (audio, 255, 128, 1000, 0);
                *efeito_sonoro = 1;
            }
        }
        *efeito_sonoro = 0;
        
        for (i=0; i<16; i++){
            destroy_bitmap (menu [i]);
        }
    } else {
        BITMAP *menu;
        menu = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_15.tga", NULL);
        
        set_alpha_blender();
        draw_trans_sprite(buffer_atual, menu, posicao_x,  posicao_y);  
        
        destroy_bitmap (menu);
    }
}

// Menu Inicial Fechando //
void menu_inicial_fechando (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *efeito_sonoro) {  
    int i;
    
    if (*animacao >=  0) {
        BITMAP *menu [16];
        
        menu [0] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_0.tga", NULL);  
        menu [1] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_1.tga", NULL);
        menu [2] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_2.tga", NULL);
        menu [3] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_3.tga", NULL);
        menu [4] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_4.tga", NULL);
        menu [5] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_5.tga", NULL);
        menu [6] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_6.tga", NULL);
        menu [7] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_7.tga", NULL);
        menu [8] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_8.tga", NULL);
        menu [9] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_9.tga", NULL);
        menu [10] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_10.tga", NULL);
        menu [11] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_11.tga", NULL);
        menu [12] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_12.tga", NULL);
        menu [13] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_13.tga", NULL);
        menu [14] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_14.tga", NULL);
        menu [15] = load_bitmap ("Imagens/TelaInicial/Menu_Inicial/Menu_Inicial_15.tga", NULL);
        
        *animacao = *animacao - 1;
        
        set_alpha_blender();
        draw_trans_sprite(buffer_atual, menu [*animacao], posicao_x,  posicao_y);     

        if (*animacao == 6) {
            if (*efeito_sonoro == 0) {
                SAMPLE *audio;
                
                audio = load_sample("Audios/Efeito/efeito_voltar.wav");
                
                play_sample (audio, 255, 128, 1000, 0);
                *efeito_sonoro = 1;
            }
        }
        *efeito_sonoro = 0;
        for (i=0; i<16; i++){
            destroy_bitmap (menu [i]);
        }
    }   
}

// Pontuação do Mini Game Corrida //
void pontuacao_corrida (BITMAP *buffer_atual, int pontuacao_jogador, int pontuacao_adversario) {  
    int i;
    
    BITMAP *ponto_jogador [4];
    BITMAP *ponto_adversario [4];
    
    ponto_jogador [0]    = load_bitmap ("Imagens/MiniGames/CorridaGinasio/Pontuacao/pontuacao_jogador_0.tga", NULL);  
    ponto_jogador [1]    = load_bitmap ("Imagens/MiniGames/CorridaGinasio/Pontuacao/pontuacao_jogador_1.tga", NULL); 
    ponto_jogador [2]    = load_bitmap ("Imagens/MiniGames/CorridaGinasio/Pontuacao/pontuacao_jogador_2.tga", NULL);
    ponto_jogador [3]    = load_bitmap ("Imagens/MiniGames/CorridaGinasio/Pontuacao/pontuacao_jogador_3.tga", NULL);
    
    ponto_adversario [0] = load_bitmap ("Imagens/MiniGames/CorridaGinasio/Pontuacao/pontuacao_adversario_0.tga", NULL);
    ponto_adversario [1] = load_bitmap ("Imagens/MiniGames/CorridaGinasio/Pontuacao/pontuacao_adversario_1.tga", NULL);  
    ponto_adversario [2] = load_bitmap ("Imagens/MiniGames/CorridaGinasio/Pontuacao/pontuacao_adversario_2.tga", NULL);
    ponto_adversario [3] = load_bitmap ("Imagens/MiniGames/CorridaGinasio/Pontuacao/pontuacao_adversario_3.tga", NULL); 
    
    set_alpha_blender();
    draw_trans_sprite(buffer_atual, ponto_jogador [pontuacao_jogador], 50,  10);
    draw_trans_sprite(buffer_atual, ponto_adversario [pontuacao_adversario], 650,  10); 
    
    for (i=0; i<4; i++) {
        destroy_bitmap (ponto_jogador [i]);
        destroy_bitmap (ponto_adversario [i]);
    }      
}


// Resultado Corrida //
void resultado_corrida (BITMAP *buffer_atual, int resultado_corrida, int *animacao, int *delay_animacao) {  
    if (resultado_corrida == 1) {
        if (*animacao < 5) {
            int i;
            BITMAP *mensagem_vitoria [5];
        
            mensagem_vitoria [0] = load_bitmap ("Imagens/MiniGames/CorridaGinasio/Resultado/Vitoria/mensagem_vitoria_4.tga", NULL);
            mensagem_vitoria [1] = load_bitmap ("Imagens/MiniGames/CorridaGinasio/Resultado/Vitoria/mensagem_vitoria_3.tga", NULL);
            mensagem_vitoria [2] = load_bitmap ("Imagens/MiniGames/CorridaGinasio/Resultado/Vitoria/mensagem_vitoria_2.tga", NULL);
            mensagem_vitoria [3] = load_bitmap ("Imagens/MiniGames/CorridaGinasio/Resultado/Vitoria/mensagem_vitoria_1.tga", NULL);
            mensagem_vitoria [4] = load_bitmap ("Imagens/MiniGames/CorridaGinasio/Resultado/Vitoria/mensagem_vitoria_0.tga", NULL);
        
            set_alpha_blender();
            draw_trans_sprite(buffer_atual, mensagem_vitoria [*animacao], 58,  260);     
        
            *delay_animacao = *delay_animacao + 1;
    
            if (*delay_animacao > 0) {
                *animacao = *animacao + 1;
                *delay_animacao = 0;
            }
            
            for (i=0; i<5; i++){
                destroy_bitmap (mensagem_vitoria [i]);
            }
        } else {
            BITMAP *mensagem_vitoria;
            mensagem_vitoria = load_bitmap ("Imagens/MiniGames/CorridaGinasio/Resultado/Vitoria/mensagem_vitoria_0.tga", NULL);   
        
            set_alpha_blender();
            draw_trans_sprite(buffer_atual, mensagem_vitoria, 58,  260);     
        
            destroy_bitmap (mensagem_vitoria);
        }       
    } else if (resultado_corrida == 2){
        if (*animacao < 5) {
            int i;
            BITMAP *mensagem_derrota [5];
        
            mensagem_derrota [0] = load_bitmap ("Imagens/MiniGames/CorridaGinasio/Resultado/Derrota/mensagem_derrota_4.tga", NULL);
            mensagem_derrota [1] = load_bitmap ("Imagens/MiniGames/CorridaGinasio/Resultado/Derrota/mensagem_derrota_3.tga", NULL);
            mensagem_derrota [2] = load_bitmap ("Imagens/MiniGames/CorridaGinasio/Resultado/Derrota/mensagem_derrota_2.tga", NULL);
            mensagem_derrota [3] = load_bitmap ("Imagens/MiniGames/CorridaGinasio/Resultado/Derrota/mensagem_derrota_1.tga", NULL);
            mensagem_derrota [4] = load_bitmap ("Imagens/MiniGames/CorridaGinasio/Resultado/Derrota/mensagem_derrota_0.tga", NULL);
        
            set_alpha_blender();
            draw_trans_sprite(buffer_atual, mensagem_derrota [*animacao], 58,  260);     
        
            *delay_animacao = *delay_animacao + 1;
    
            if (*delay_animacao > 0) {
                *animacao = *animacao + 1;
                *delay_animacao = 0;
            }
    
        
            for (i=0; i<5; i++){
                destroy_bitmap (mensagem_derrota [i]);
            }
            
        } else {
            BITMAP *mensagem_derrota;
            mensagem_derrota = load_bitmap ("Imagens/MiniGames/CorridaGinasio/Resultado/Derrota/mensagem_derrota_0.tga", NULL);
        
            set_alpha_blender();
            draw_trans_sprite(buffer_atual, mensagem_derrota, 58,  260);     
            
            destroy_bitmap (mensagem_derrota);
        }
    }   
}


// Mostrar Nivel do Mini Game //
void nivel_corrida (BITMAP *buffer_atual, int nivel){
    if (nivel == 0){
        BITMAP *nivel_tela;
         
        nivel_tela = load_bitmap ("Imagens/MiniGames/CorridaGinasio/Pontuacao/mini_game_nivel_1.tga", NULL);
        
        set_alpha_blender();
        draw_trans_sprite(buffer_atual, nivel_tela, 300,  460);
    
        destroy_bitmap (nivel_tela);
    } else if (nivel == 1) {
        BITMAP *nivel_tela; 
        
        nivel_tela = load_bitmap ("Imagens/MiniGames/CorridaGinasio/Pontuacao/mini_game_nivel_2.tga", NULL);
        
        set_alpha_blender();
        draw_trans_sprite(buffer_atual, nivel_tela, 300,  460);
    
        destroy_bitmap (nivel_tela);
    } else {
        BITMAP *nivel_tela; 
        nivel_tela = load_bitmap ("Imagens/MiniGames/CorridaGinasio/Pontuacao/mini_game_nivel_3.tga", NULL);
        
        set_alpha_blender();
        draw_trans_sprite(buffer_atual, nivel_tela, 300,  460);
    
        destroy_bitmap (nivel_tela);
    } 
}

// Tela Quem Somos //
void quem_somos (BITMAP *buffer_atual) {
    BITMAP *tela_quem_somos [2];
        
        tela_quem_somos [0] = load_bitmap ("Imagens/TelaInicial/quem_somos_parallax_fundo_1.tga", NULL);
        tela_quem_somos [1] = load_bitmap ("Imagens/TelaInicial/Tela_Inicial_Quem_Somos_Novo.tga", NULL);
        
        set_alpha_blender();
        draw_trans_sprite(buffer_atual, tela_quem_somos [0], 0,  0);
        draw_trans_sprite(buffer_atual, tela_quem_somos [1], -50,  150);
        
    destroy_bitmap (tela_quem_somos [0]);
    destroy_bitmap (tela_quem_somos [1]);
}

// Tela Ranking Nomes //
void ranking_nomes (BITMAP *buffer_atual) {
    BITMAP *ranking;
        
    ranking = load_jpg ("Imagens/Ranking/fundo_ranking_nomes.jpg", NULL);
    draw_sprite(buffer_atual, ranking, 0,  0);
  
    destroy_bitmap (ranking);
}

// Jogo de Memória //
void jogo_memoria (BITMAP *buffer_atual, TCartas informacaoCarta, informacaoJogoCarta *dadosJogoCarta, int *delay_ver_cartas, int *animacao, int *delay_animacao, int *posicao_x_efeito_carta_selecionada, int *posicao_y_efeito_carta_selecionada, int *efeito_carta_selecionada, int *efeito_ponto_positivo, int *efeito_ponto_negativo) {
    int x;
    int y;
    int cont = 0;
    
    BITMAP *Buffer;
    BITMAP *Cartas;
    BITMAP *Cursor_Mouse [7];
    
    SAMPLE *carta_certa;
    SAMPLE *carta_errada;
    SAMPLE *seleciona_carta;
    
    carta_certa     = load_sample ("Audios/Efeito/efeito_uhuu.wav");
    carta_errada    = load_sample ("Audios/Efeito/efeito_vaia.wav");
    seleciona_carta = load_sample ("Audios/Efeito/efeito_escolher_carta_certa.wav");
    
    informacaoCarta [0][0].CartasSel = load_jpg("Imagens/MiniGames/JogoMemoria/Cartas/carta1.jpg",NULL);
    informacaoCarta [0][1].CartasSel = load_jpg("Imagens/MiniGames/JogoMemoria/Cartas/carta5.jpg",NULL);
    informacaoCarta [0][2].CartasSel = load_jpg("Imagens/MiniGames/JogoMemoria/Cartas/carta3.jpg",NULL);
    informacaoCarta [0][3].CartasSel = load_jpg("Imagens/MiniGames/JogoMemoria/Cartas/carta2.jpg",NULL);
    informacaoCarta [1][0].CartasSel = load_jpg("Imagens/MiniGames/JogoMemoria/Cartas/carta4.jpg",NULL);
    informacaoCarta [1][1].CartasSel = load_jpg("Imagens/MiniGames/JogoMemoria/Cartas/carta4.jpg",NULL);
    informacaoCarta [1][2].CartasSel = load_jpg("Imagens/MiniGames/JogoMemoria/Cartas/carta1.jpg",NULL);
    informacaoCarta [1][3].CartasSel = load_jpg("Imagens/MiniGames/JogoMemoria/Cartas/carta5.jpg",NULL);
    informacaoCarta [2][0].CartasSel = load_jpg("Imagens/MiniGames/JogoMemoria/Cartas/carta2.jpg",NULL);
    informacaoCarta [2][1].CartasSel = load_jpg("Imagens/MiniGames/JogoMemoria/Cartas/carta6.jpg",NULL);
    informacaoCarta [2][2].CartasSel = load_jpg("Imagens/MiniGames/JogoMemoria/Cartas/carta8.jpg",NULL);
    informacaoCarta [2][3].CartasSel = load_jpg("Imagens/MiniGames/JogoMemoria/Cartas/carta7.jpg",NULL);
    informacaoCarta [3][0].CartasSel = load_jpg("Imagens/MiniGames/JogoMemoria/Cartas/carta3.jpg",NULL);
    informacaoCarta [3][1].CartasSel = load_jpg("Imagens/MiniGames/JogoMemoria/Cartas/carta7.jpg",NULL);
    informacaoCarta [3][2].CartasSel = load_jpg("Imagens/MiniGames/JogoMemoria/Cartas/carta8.jpg",NULL);
    informacaoCarta [3][3].CartasSel = load_jpg("Imagens/MiniGames/JogoMemoria/Cartas/carta6.jpg",NULL);
    
    Cursor_Mouse [0] = load_bitmap("Imagens/MiniGames/JogoMemoria/Cursor/mouse_cursor_0.tga",NULL);
    Cursor_Mouse [1] = load_bitmap("Imagens/MiniGames/JogoMemoria/Cursor/mouse_cursor_1.tga",NULL);
    Cursor_Mouse [2] = load_bitmap("Imagens/MiniGames/JogoMemoria/Cursor/mouse_cursor_2.tga",NULL);
    Cursor_Mouse [3] = load_bitmap("Imagens/MiniGames/JogoMemoria/Cursor/mouse_cursor_3.tga",NULL);
    Cursor_Mouse [4] = load_bitmap("Imagens/MiniGames/JogoMemoria/Cursor/mouse_cursor_4.tga",NULL);
    Cursor_Mouse [5] = load_bitmap("Imagens/MiniGames/JogoMemoria/Cursor/mouse_cursor_5.tga",NULL);
    Cursor_Mouse [6] = load_bitmap("Imagens/MiniGames/JogoMemoria/Cursor/mouse_cursor_6.tga",NULL);
    
    *delay_animacao = *delay_animacao + 1;
    
    if (*delay_animacao > 0) {
        *animacao = *animacao + 1;
        *delay_animacao = 0;
    }
    
    if (*animacao > 6) {
        *animacao = 0;
    }
    
    Cartas       = load_jpg("Imagens/MiniGames/JogoMemoria/Cartas/CartaVirada.jpg",NULL);
    
    dadosJogoCarta->x = 370;
    dadosJogoCarta->y = 80;
    
    set_mouse_range (0, 0, TELA_LARGURA, TELA_ALTURA); //Limites de movimento do mouse na tela
    
    for(x = 0; x < 4; x++) {
        for(y = 0; y < 4; y++) {
            if(informacaoCarta[x][y].estado == 0) {
                draw_sprite(buffer_atual, Cartas, dadosJogoCarta->x, dadosJogoCarta->y);
                cont++;
            }
               
            informacaoCarta[x][y].posicaoX = dadosJogoCarta->x;
            informacaoCarta[x][y].posicaoY = dadosJogoCarta->y;

            if(informacaoCarta[x][y].estado == 1) {
                draw_sprite(buffer_atual, informacaoCarta[x][y].CartasSel, informacaoCarta[x][y].posicaoX, informacaoCarta[x][y].posicaoY );
            }

            dadosJogoCarta->x = dadosJogoCarta->x + 85;
        }
        dadosJogoCarta->x = 370;
        dadosJogoCarta->y = dadosJogoCarta->y + 115;
    }
    
    if (cont == 0) {
        dadosJogoCarta->testa_fim = 1;
    }
    dadosJogoCarta->x = 370;
    dadosJogoCarta->y = 80;

    if (!mouse_b & 1) {
        dadosJogoCarta->estadoClique = 0;//contClique++; //conta a quantidade de cliques
    }

    if(mouse_b & 1) {
        if(dadosJogoCarta->estadoClique == 0) {
            dadosJogoCarta->estadoClique = 1;     
            for(x = 0; x < 4; x++) {
                for(y = 0; y < 4; y++) {
                    dadosJogoCarta->colisao = detectarColisaoCartas (mouse_x, mouse_y, mouse_y + 5, mouse_x + 5, dadosJogoCarta->x, dadosJogoCarta->y, dadosJogoCarta->x + 70,  dadosJogoCarta->y + 103); //realiza a colisao nas cartas
                    if (dadosJogoCarta->colisao == 1) { // Se estiver occorendo Colisão do mouse a carta na tela //
                        if (informacaoCarta[x][y].estado == 0) {
                            dadosJogoCarta->contClique = dadosJogoCarta->contClique + 1;
                            *posicao_x_efeito_carta_selecionada = dadosJogoCarta->x;
                            *posicao_y_efeito_carta_selecionada = dadosJogoCarta->y;
                            *efeito_carta_selecionada = 0;
                        }
                        if ((dadosJogoCarta->contClique == 1) && (informacaoCarta[x][y].estado == 0)) {
                            draw_sprite(buffer_atual, informacaoCarta [x][y].CartasSel, informacaoCarta[x][y].posicaoX, informacaoCarta[x][y].posicaoY);
                            dadosJogoCarta->ComparaId[0] = informacaoCarta[x][y].id;
                            informacaoCarta[x][y].estado = 1;
                            dadosJogoCarta->C1 = x;
                            dadosJogoCarta->L1 = y;
                            play_sample (seleciona_carta, 255, 128, 1000, 0);
                        } else if((dadosJogoCarta->contClique == 2) && (informacaoCarta[x][y].estado == 0)){
                            draw_sprite(buffer_atual, informacaoCarta [x][y].CartasSel, informacaoCarta[x][y].posicaoX, informacaoCarta[x][y].posicaoY);
                            informacaoCarta[x][y].estado = 1;
                            dadosJogoCarta->ComparaId[1] = informacaoCarta[x][y].id;
                            dadosJogoCarta->C2 = x;
                            dadosJogoCarta->L2 = y;
                            play_sample (seleciona_carta, 255, 128, 1000, 0);
                            if(dadosJogoCarta->ComparaId[0] == dadosJogoCarta->ComparaId[1]) {
                                *efeito_ponto_positivo = 0;
                                play_sample (carta_certa, 255, 128, 1000, 0);
                                dadosJogoCarta->Ponto = dadosJogoCarta->Ponto + 1;
                                dadosJogoCarta->contClique   = 0;
                                dadosJogoCarta->ComparaId[0] = 0;
                                dadosJogoCarta->ComparaId[1] = 0;
                            } else  {
                                *efeito_ponto_negativo = 0;
                                play_sample (carta_errada, 255, 128, 1000, 0);
                                dadosJogoCarta->Ponto = dadosJogoCarta->Ponto - 1;
                                if (dadosJogoCarta->Ponto < 0) {
                                    dadosJogoCarta->Ponto = 0;
                                }
                                *delay_ver_cartas = *delay_ver_cartas + 1;
                                if (*delay_ver_cartas > 14) {
                                    informacaoCarta[dadosJogoCarta->C1][dadosJogoCarta->L1].estado = 0;
                                    informacaoCarta[dadosJogoCarta->C2][dadosJogoCarta->L2].estado = 0;
                                    dadosJogoCarta->contClique   = 0;
                                    dadosJogoCarta->ComparaId[0] = 0;
                                    dadosJogoCarta->ComparaId[1] = 0;
                                    *delay_ver_cartas = 0;
                                }
                            }
                        } else if ((dadosJogoCarta->contClique > 2) && (informacaoCarta[x][y].estado == 0)) {
                            informacaoCarta[dadosJogoCarta->C1][dadosJogoCarta->L1].estado = 0;
                            informacaoCarta[dadosJogoCarta->C2][dadosJogoCarta->L2].estado = 0;
                            dadosJogoCarta->C1 = 0;
                            dadosJogoCarta->L1 = 0;
                            dadosJogoCarta->C2 = 0;
                            dadosJogoCarta->L2 = 0;
                            dadosJogoCarta->contClique = 0;
                        }
                    }
                    dadosJogoCarta->x = dadosJogoCarta->x + 85;
                }
                dadosJogoCarta->x = 370;
                dadosJogoCarta->y = dadosJogoCarta->y + 115;
            }
        }
    }
    
    set_alpha_blender();
    draw_trans_sprite(buffer_atual, Cursor_Mouse [*animacao], mouse_x - 22.5,  mouse_y - 22.5);
    
    for (x=0; x<4; x++) {
        for (y=0; y<4; y++) {
            destroy_bitmap (informacaoCarta [x][y].CartasSel);
        }
    }
    
    for (x=0; x<7;x++){
        destroy_bitmap (Cursor_Mouse [x]);
    }
    destroy_bitmap (Cartas);
}

// Animacação Carta Selecionada //
void efeito_carta_selecionada (BITMAP *buffer_atual, int posicao_x, int posicao_y, int *animacao, int *delay_animacao) {
    if (*animacao <= 7) {
        int i;
    
        BITMAP *carta_selecionada [8];
        *delay_animacao = *delay_animacao + 1;
    
        carta_selecionada [0] = load_bitmap ("Imagens/MiniGames/JogoMemoria/Cartas/Efeito_Carta_Selecionada/Efeito_Carta_Selecionada_0.tga", NULL);
        carta_selecionada [1] = load_bitmap ("Imagens/MiniGames/JogoMemoria/Cartas/Efeito_Carta_Selecionada/Efeito_Carta_Selecionada_1.tga", NULL);
        carta_selecionada [2] = load_bitmap ("Imagens/MiniGames/JogoMemoria/Cartas/Efeito_Carta_Selecionada/Efeito_Carta_Selecionada_2.tga", NULL);
        carta_selecionada [3] = load_bitmap ("Imagens/MiniGames/JogoMemoria/Cartas/Efeito_Carta_Selecionada/Efeito_Carta_Selecionada_3.tga", NULL);
        carta_selecionada [4] = load_bitmap ("Imagens/MiniGames/JogoMemoria/Cartas/Efeito_Carta_Selecionada/Efeito_Carta_Selecionada_4.tga", NULL);
        carta_selecionada [5] = load_bitmap ("Imagens/MiniGames/JogoMemoria/Cartas/Efeito_Carta_Selecionada/Efeito_Carta_Selecionada_5.tga", NULL);
        carta_selecionada [6] = load_bitmap ("Imagens/MiniGames/JogoMemoria/Cartas/Efeito_Carta_Selecionada/Efeito_Carta_Selecionada_6.tga", NULL);
        carta_selecionada [7] = load_bitmap ("Imagens/MiniGames/JogoMemoria/Cartas/Efeito_Carta_Selecionada/Efeito_Carta_Selecionada_7.tga", NULL);

        set_alpha_blender();
        draw_trans_sprite(buffer_atual, carta_selecionada [*animacao], posicao_x - 25, posicao_y - 25);
    
        if (*delay_animacao > 0) {
            *animacao = *animacao + 1;
            *delay_animacao = 0;
        }
    
        for (i=0; i < 8; i++){
            destroy_bitmap (carta_selecionada [i]);
        }
    }
}

// Tela Pontuação Minigame Cartas //
void pontuacao_cartas (BITMAP *buffer_atual, int pontuacao) {
    BITMAP *pontos;
    if (pontuacao == 0) {      
        pontos = load_bitmap ("Imagens/Minigames/JogoMemoria/Pontuacao/pontuacao_0.tga", NULL);   
    } else if (pontuacao == 1) {
        pontos = load_bitmap ("Imagens/Minigames/JogoMemoria/Pontuacao/pontuacao_1.tga", NULL);  
    } else if (pontuacao == 2) {
        pontos = load_bitmap ("Imagens/Minigames/JogoMemoria/Pontuacao/pontuacao_2.tga", NULL); 
    } else if (pontuacao == 3) {
        pontos = load_bitmap ("Imagens/Minigames/JogoMemoria/Pontuacao/pontuacao_3.tga", NULL);
    } else if (pontuacao == 4) {        
        pontos = load_bitmap ("Imagens/Minigames/JogoMemoria/Pontuacao/pontuacao_4.tga", NULL); 
    } else if (pontuacao == 5) {       
        pontos = load_bitmap ("Imagens/Minigames/JogoMemoria/Pontuacao/pontuacao_5.tga", NULL);   
    } else if (pontuacao == 6) { 
        pontos = load_bitmap ("Imagens/Minigames/JogoMemoria/Pontuacao/pontuacao_6.tga", NULL);        
    } else if (pontuacao == 7) {    
        pontos = load_bitmap ("Imagens/Minigames/JogoMemoria/Pontuacao/pontuacao_7.tga", NULL);
        
    } else if (pontuacao == 8) {
        pontos = load_bitmap ("Imagens/Minigames/JogoMemoria/Pontuacao/pontuacao_8.tga", NULL);
    }
    
    set_alpha_blender();
    draw_trans_sprite(buffer_atual, pontos, 180,  280);
    
    destroy_bitmap (pontos);
}

// Animacação Ponto Positivo //
void efeito_ponto_positivo (BITMAP *buffer_atual, int *animacao, int *delay_animacao, int posicao_x, int posicao_y) {
    if (*animacao <= 10) {
        int i;
    
        BITMAP *ponto_positivo [11];
        *delay_animacao = *delay_animacao + 1;
    
        ponto_positivo [0]  = load_bitmap ("Imagens/MiniGames/JogoMemoria/Pontuacao/Ponto_Positivo/ponto_positivo_0.tga",  NULL);
        ponto_positivo [1]  = load_bitmap ("Imagens/MiniGames/JogoMemoria/Pontuacao/Ponto_Positivo/ponto_positivo_1.tga",  NULL);
        ponto_positivo [2]  = load_bitmap ("Imagens/MiniGames/JogoMemoria/Pontuacao/Ponto_Positivo/ponto_positivo_2.tga",  NULL);
        ponto_positivo [3]  = load_bitmap ("Imagens/MiniGames/JogoMemoria/Pontuacao/Ponto_Positivo/ponto_positivo_3.tga",  NULL);
        ponto_positivo [4]  = load_bitmap ("Imagens/MiniGames/JogoMemoria/Pontuacao/Ponto_Positivo/ponto_positivo_4.tga",  NULL);
        ponto_positivo [5]  = load_bitmap ("Imagens/MiniGames/JogoMemoria/Pontuacao/Ponto_Positivo/ponto_positivo_5.tga",  NULL);
        ponto_positivo [6]  = load_bitmap ("Imagens/MiniGames/JogoMemoria/Pontuacao/Ponto_Positivo/ponto_positivo_6.tga",  NULL);
        ponto_positivo [7]  = load_bitmap ("Imagens/MiniGames/JogoMemoria/Pontuacao/Ponto_Positivo/ponto_positivo_7.tga",  NULL);
        ponto_positivo [8]  = load_bitmap ("Imagens/MiniGames/JogoMemoria/Pontuacao/Ponto_Positivo/ponto_positivo_8.tga",  NULL);
        ponto_positivo [9]  = load_bitmap ("Imagens/MiniGames/JogoMemoria/Pontuacao/Ponto_Positivo/ponto_positivo_9.tga",  NULL);
        ponto_positivo [10] = load_bitmap ("Imagens/MiniGames/JogoMemoria/Pontuacao/Ponto_Positivo/ponto_positivo_10.tga", NULL);
        
        set_alpha_blender();
        draw_trans_sprite(buffer_atual, ponto_positivo [*animacao], posicao_x, posicao_y);
    
        if (*delay_animacao > 0) {
            *animacao = *animacao + 1;
            *delay_animacao = 0;
        }
    
        for (i=0; i < 11; i++){
            destroy_bitmap (ponto_positivo [i]);
        }
    }
}

// Animacação Ponto Negativo //
void efeito_ponto_negativo (BITMAP *buffer_atual, int *animacao, int *delay_animacao, int posicao_x, int posicao_y) {
    if (*animacao <= 10) {
        int i;
    
        BITMAP *ponto_negativo [11];
        *delay_animacao = *delay_animacao + 1;
    
        ponto_negativo [0]  = load_bitmap ("Imagens/MiniGames/JogoMemoria/Pontuacao/Ponto_Negativo/ponto_negativo_0.tga",  NULL);
        ponto_negativo [1]  = load_bitmap ("Imagens/MiniGames/JogoMemoria/Pontuacao/Ponto_Negativo/ponto_negativo_1.tga",  NULL);
        ponto_negativo [2]  = load_bitmap ("Imagens/MiniGames/JogoMemoria/Pontuacao/Ponto_Negativo/ponto_negativo_2.tga",  NULL);
        ponto_negativo [3]  = load_bitmap ("Imagens/MiniGames/JogoMemoria/Pontuacao/Ponto_Negativo/ponto_negativo_3.tga",  NULL);
        ponto_negativo [4]  = load_bitmap ("Imagens/MiniGames/JogoMemoria/Pontuacao/Ponto_Negativo/ponto_negativo_4.tga",  NULL);
        ponto_negativo [5]  = load_bitmap ("Imagens/MiniGames/JogoMemoria/Pontuacao/Ponto_Negativo/ponto_negativo_5.tga",  NULL);
        ponto_negativo [6]  = load_bitmap ("Imagens/MiniGames/JogoMemoria/Pontuacao/Ponto_Negativo/ponto_negativo_6.tga",  NULL);
        ponto_negativo [7]  = load_bitmap ("Imagens/MiniGames/JogoMemoria/Pontuacao/Ponto_Negativo/ponto_negativo_7.tga",  NULL);
        ponto_negativo [8]  = load_bitmap ("Imagens/MiniGames/JogoMemoria/Pontuacao/Ponto_Negativo/ponto_negativo_8.tga",  NULL);
        ponto_negativo [9]  = load_bitmap ("Imagens/MiniGames/JogoMemoria/Pontuacao/Ponto_Negativo/ponto_negativo_9.tga",  NULL);
        ponto_negativo [10] = load_bitmap ("Imagens/MiniGames/JogoMemoria/Pontuacao/Ponto_Negativo/ponto_negativo_10.tga", NULL);
        
        set_alpha_blender();
        draw_trans_sprite(buffer_atual, ponto_negativo [*animacao], posicao_x, posicao_y);
    
        if (*delay_animacao > 0) {
            *animacao = *animacao + 1;
            *delay_animacao = 0;
        }
    
        for (i=0; i < 11; i++){
            destroy_bitmap (ponto_negativo [i]);
        }
    }
}

//  Detecção de Colisão Com Cartas /
int detectarColisaoCartas (int x1, int y1, int altura1, int largura1,int x2, int y2, int altura2, int largura2)
{
    int colisao = 0;

    if (x1 > altura2) {
    } else if (y1 > largura2) {
    } else if (largura1 < x2) {
    } else if (altura1 < y2) {
    } else {
        colisao = 1;
    }
    return (colisao);
}

// Mini Game Pergunta e Resposta //
void jogo_pergunta_resposta (BITMAP *buffer_atual, int *opcao_escolhida, int *pergunta, int *ponto, int *animacao_acerto_esquerda, int *animacao_acerto_esquerda_delay, int *animacao_acerto_direita, int *animacao_acerto_direita_delay, int *animacao_erro_esquerda, int *animacao_erro_esquerda_delay, int *animacao_erro_direita, int *animacao_erro_direita_delay,  int *animacao_cursor, int *delay_animacao_cursor, int *animacao_ponto_positivo, int *animacao_ponto_positivo_delay, int *animacao_ponto_negativo, int *animacao_ponto_negativo_delay){    

    SAMPLE *audio_efeito_menu;
    audio_efeito_menu = load_sample ("Audios/Efeito/efeito_avancar.wav");
    
    // Controla Local do Cursor //
    set_keyboard_rate(0,0);
        if (key [KEY_DOWN]) {
            if (keypressed()) {
                if (*opcao_escolhida != 3) {
                    play_sample (audio_efeito_menu, 500, 128, 1000, 0);
                }
                *opcao_escolhida = *opcao_escolhida + 1;
                if (*opcao_escolhida > 3) {
                    *opcao_escolhida = 3;
                }
            }
            clear_keybuf();
        } else if (key [KEY_UP]) {
            if (keypressed()) {
                if (*opcao_escolhida != 0) {
                    play_sample (audio_efeito_menu, 500, 128, 1000, 0);
                }
                *opcao_escolhida = *opcao_escolhida - 1;
                if (*opcao_escolhida < 0) {
                    *opcao_escolhida = 0;
                }  
            }
            clear_keybuf();
        }
    
    
    // Testa Primeira Questão //
    if ((((key[KEY_ENTER]) && (*pergunta == 0) && (*opcao_escolhida == 2) && (*animacao_acerto_esquerda > 14)))){
        *animacao_acerto_esquerda = 0;
        *animacao_ponto_positivo  = 0;
        *ponto = *ponto + 1;
    } else {
        if ((((key[KEY_ENTER]) && (*opcao_escolhida == 0) && (*pergunta == 0) && (*animacao_erro_esquerda > 15)))) {
            if (*animacao_erro_esquerda > 14) {
                *animacao_erro_esquerda = 0;
                *animacao_ponto_negativo  = 0;
                *ponto = *ponto - 1;        
            }
        } else if ((((key[KEY_ENTER]) && (*pergunta == 0) && (*animacao_erro_esquerda > 15))) && ((*opcao_escolhida == 1) || (*opcao_escolhida == 3))) {
            if (*animacao_erro_direita > 14) {
                *animacao_erro_direita = 0;
                *animacao_ponto_negativo  = 0;
                *ponto = *ponto - 1;
            }
        }
    }
    
    // Testa Segunda Questão //
    if ((((key[KEY_ENTER]) && (*pergunta == 1) && (*opcao_escolhida == 3) && (*animacao_acerto_direita > 14)))){
        *animacao_acerto_direita = 0;
        *animacao_ponto_positivo = 0;
        *ponto = *ponto + 1;
    } else {
        if ((((key[KEY_ENTER]) && (*opcao_escolhida == 1) && (*pergunta == 1) && (*animacao_erro_esquerda > 15)))){
            if (*animacao_erro_direita > 14) {
                *animacao_erro_direita = 0;
                *animacao_ponto_negativo  = 0;
                *ponto = *ponto - 1;
            }
        } else if ((((key[KEY_ENTER]) && (*pergunta == 1) && (*animacao_erro_esquerda > 15))) && ((*opcao_escolhida == 0) || (*opcao_escolhida == 2)))  {
            if (*animacao_erro_esquerda > 14) {
                *animacao_erro_esquerda = 0;
                *animacao_ponto_negativo  = 0;
                *ponto = *ponto - 1;
            }
        }
    }
    
    // Testa Terceira Questão //
    if ((((key[KEY_ENTER]) && (*pergunta == 2) && (*opcao_escolhida == 3) && (*animacao_acerto_direita > 14)))){
        *animacao_acerto_direita = 0;
        *animacao_ponto_positivo  = 0;
        *ponto = *ponto + 1;
    } else {
        if ((((key[KEY_ENTER]) && (*opcao_escolhida == 1) && (*pergunta == 2) && (*animacao_erro_esquerda > 15)))){
            if (*animacao_erro_direita > 14) {
                *animacao_erro_direita   = 0;
                *animacao_ponto_negativo  = 0;
                *ponto = *ponto - 1;
            }
        } else if ((((key[KEY_ENTER]) && (*pergunta == 2) && (*animacao_erro_esquerda > 15))) && ((*opcao_escolhida == 0) || (*opcao_escolhida == 2)))  {
            if (*animacao_erro_esquerda > 14) {
                *animacao_erro_esquerda = 0;
                *animacao_ponto_negativo = 0;
                *ponto = *ponto - 1;
            }
        }
    }
    
    // Testa Quarta Questão //
    if ((((key[KEY_ENTER]) && (*pergunta == 3) && (*opcao_escolhida == 2) && (*animacao_acerto_esquerda > 14)))){
        *animacao_acerto_esquerda = 0;
        *animacao_ponto_positivo  = 0;
        *ponto = *ponto + 1;
    } else {
        if ((((key[KEY_ENTER]) && (*opcao_escolhida == 0) && (*pergunta == 3) && (*animacao_erro_esquerda > 15)))){
            if (*animacao_erro_esquerda > 14) {
                *animacao_erro_esquerda = 0;
                *animacao_ponto_negativo = 0;
                *ponto = *ponto - 1;
            }
        } else if ((((key[KEY_ENTER]) && (*pergunta == 3) && (*animacao_erro_esquerda > 15))) && ((*opcao_escolhida == 1) || (*opcao_escolhida == 3)))  {
            if (*animacao_erro_direita > 14) {
                *animacao_erro_direita = 0;
                *animacao_ponto_negativo  = 0;
                *ponto = *ponto - 1;
            }
        }
    }
    
    // Testa Quinta Questão //
    if ((((key[KEY_ENTER]) && (*pergunta == 4) && (*opcao_escolhida == 0) && (*animacao_acerto_esquerda > 14)))){
        *animacao_acerto_esquerda = 0;
        *animacao_ponto_positivo  = 0;
        *ponto = *ponto + 1;
    } else {
        if ((((key[KEY_ENTER]) && (*opcao_escolhida == 2) && (*pergunta == 4) && (*animacao_erro_esquerda > 15)))){
            if (*animacao_erro_esquerda > 14) {
                *animacao_erro_esquerda = 0;
                *animacao_ponto_negativo = 0;
                *ponto = *ponto - 1;
            }
        } else if ((((key[KEY_ENTER]) && (*pergunta == 4) && (*animacao_erro_esquerda > 15))) && ((*opcao_escolhida == 1) || (*opcao_escolhida == 3)))  {
            if (*animacao_erro_direita > 14) {
                *animacao_erro_direita = 0;
                *animacao_ponto_negativo = 0;
                *ponto = *ponto - 1;
            }
        }
    }
    
    
    // Realiza Animacoes //
    efeito_erro_esquerda   (buffer_atual, animacao_erro_esquerda, animacao_erro_esquerda_delay);
    efeito_acerto_esquerda (buffer_atual, animacao_acerto_esquerda, animacao_acerto_esquerda_delay);
    efeito_erro_direita    (buffer_atual, animacao_erro_direita, animacao_erro_direita_delay);
    efeito_acerto_direita  (buffer_atual, animacao_acerto_direita, animacao_acerto_direita_delay);
    efeito_ponto_positivo  (buffer_atual, animacao_ponto_positivo, animacao_ponto_positivo_delay, -50, -75);
    efeito_ponto_negativo  (buffer_atual, animacao_ponto_negativo, animacao_ponto_negativo_delay, -50, -75);
    
    // Testa se está ocorrendo alguma animação // Se estiver ocorrendo animacação ele não desenha a pergunta e nem o cursor na tela //
    if ((((*animacao_acerto_esquerda > 15) && (*animacao_acerto_direita > 15) && (*animacao_erro_esquerda > 15) && (*animacao_erro_direita > 15)))){
        
        int i;
        
        BITMAP *imagem_pergunta;
        BITMAP *cursor[4];
        BITMAP *bola;
        
        bola = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Bola/bola_parada.tga",  NULL); 
            
    
        // Carrega Cursores //
        cursor[0] = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Cursor/cursor_0.tga",  NULL);
        cursor[1] = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Cursor/cursor_1.tga",  NULL);
        cursor[2] = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Cursor/cursor_2.tga",  NULL);
        cursor[3] = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Cursor/cursor_3.tga",  NULL); 
    
        // Carrega Perguntas //
        if (*pergunta == 0) {
            imagem_pergunta = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Perguntas/pergunta_0.tga",  NULL);
        } else if (*pergunta == 1) {
            imagem_pergunta = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Perguntas/pergunta_1.tga",  NULL);
        } else if (*pergunta == 2) {
            imagem_pergunta = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Perguntas/pergunta_2.tga",  NULL);
        } else if (*pergunta == 3) {
            imagem_pergunta = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Perguntas/pergunta_3.tga",  NULL);
        } else if (*pergunta == 4) {
            imagem_pergunta = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Perguntas/pergunta_4.tga",  NULL);
        }
    
        
        *delay_animacao_cursor = *delay_animacao_cursor + 1;
    
        if (*delay_animacao_cursor > 0) {
            *animacao_cursor = *animacao_cursor + 1;
            *delay_animacao_cursor = 0;
        }
    
        if (*animacao_cursor > 3) {
            *animacao_cursor = 0;
        }
        
        set_alpha_blender();
        if (*opcao_escolhida == 0) {                 
            draw_trans_sprite(buffer_atual, cursor [*animacao_cursor], 170, 30);
        } else if (*opcao_escolhida == 1) {
            draw_trans_sprite(buffer_atual, cursor [*animacao_cursor], 527, 30);
        } else if (*opcao_escolhida == 2) {
            draw_trans_sprite(buffer_atual, cursor [*animacao_cursor], 170, 135);
        } else {
           draw_trans_sprite(buffer_atual, cursor [*animacao_cursor], 527, 135);
        }
        
        draw_trans_sprite(buffer_atual, bola, 0, 0);
        draw_trans_sprite(buffer_atual, imagem_pergunta, 48.5, 30);

        destroy_bitmap (bola);
        destroy_bitmap (imagem_pergunta);   
        for (i=0; i<4; i++) {
            destroy_bitmap (cursor [i]);
        }  
    }
    if (*ponto < 0) *ponto = 0;          
}


// Animacação Chuta Esquerda Defendido //
void efeito_erro_esquerda (BITMAP *buffer_atual, int *animacao, int *delay_animacao) {
    if (*animacao < 15) {
        int i;
                
        SAMPLE *efeito_chute;
        SAMPLE *efeito_erro;
        
        BITMAP *chute [15];
        
        *delay_animacao = *delay_animacao + 1;
                
        efeito_chute = load_sample ("Audios/Efeito/efeito_chutar_bola.wav");
        efeito_erro  = load_sample ("Audios/Efeito/efeito_vaia.wav");
        
        chute [0]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Esquerda/erro_esquerda_0.tga",  NULL);
        chute [1]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Esquerda/erro_esquerda_1.tga",  NULL);
        chute [2]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Esquerda/erro_esquerda_2.tga",  NULL);
        chute [3]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Esquerda/erro_esquerda_3.tga",  NULL);
        chute [4]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Esquerda/erro_esquerda_4.tga",  NULL);
        chute [5]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Esquerda/erro_esquerda_5.tga",  NULL);
        chute [6]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Esquerda/erro_esquerda_6.tga",  NULL);
        chute [7]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Esquerda/erro_esquerda_7.tga",  NULL);
        chute [8]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Esquerda/erro_esquerda_8.tga",  NULL);
        chute [9]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Esquerda/erro_esquerda_9.tga",  NULL);
        chute [10] = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Esquerda/erro_esquerda_10.tga", NULL);
        chute [11] = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Esquerda/erro_esquerda_11.tga", NULL);
        chute [12] = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Esquerda/erro_esquerda_12.tga", NULL);
        chute [13] = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Esquerda/erro_esquerda_13.tga", NULL);
        chute [14] = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Esquerda/erro_esquerda_14.tga", NULL);
        
        set_alpha_blender();
        draw_trans_sprite(buffer_atual, chute [*animacao], 0, 0);
        
        if (*animacao == 0) {
            play_sample (efeito_chute, 255, 128, 1000, 0);
        } else if (*animacao == 5) {
            play_sample (efeito_erro, 255, 128, 1000, 0);
        }
        
        if (*delay_animacao > 0) {
            *animacao = *animacao + 1;
            *delay_animacao = 0;
        }
    
        for (i=0; i < 15; i++){
            destroy_bitmap (chute [i]);
        }
    } else if (*animacao == 15) {
        *animacao = 16;
    }
}

// Animacação Chuta Direita Defendido //
void efeito_erro_direita (BITMAP *buffer_atual, int *animacao, int *delay_animacao) {
    if (*animacao < 15) {
        int i;
        
        SAMPLE *efeito_chute;
        SAMPLE *efeito_erro;
        
        BITMAP *chute [15];
        
        *delay_animacao = *delay_animacao + 1;
                
        efeito_chute = load_sample ("Audios/Efeito/efeito_chutar_bola.wav");
        efeito_erro  = load_sample ("Audios/Efeito/efeito_vaia.wav");
        
        chute [0]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Direita/erro_direita_0.tga",  NULL);
        chute [1]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Direita/erro_direita_1.tga",  NULL);
        chute [2]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Direita/erro_direita_2.tga",  NULL);
        chute [3]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Direita/erro_direita_3.tga",  NULL);
        chute [4]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Direita/erro_direita_4.tga",  NULL);
        chute [5]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Direita/erro_direita_5.tga",  NULL);
        chute [6]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Direita/erro_direita_6.tga",  NULL);
        chute [7]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Direita/erro_direita_7.tga",  NULL);
        chute [8]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Direita/erro_direita_8.tga",  NULL);
        chute [9]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Direita/erro_direita_9.tga",  NULL);
        chute [10] = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Direita/erro_direita_10.tga", NULL);
        chute [11] = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Direita/erro_direita_11.tga", NULL);
        chute [12] = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Direita/erro_direita_12.tga", NULL);
        chute [13] = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Direita/erro_direita_13.tga", NULL);
        chute [14] = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Erro/Direita/erro_direita_14.tga", NULL);
        
        set_alpha_blender();
        draw_trans_sprite(buffer_atual, chute [*animacao], 0, 0);
        
        if (*animacao == 0) {
            play_sample (efeito_chute, 255, 128, 1000, 0);
        } else if (*animacao == 5) {
            play_sample (efeito_erro, 255, 128, 1000, 0);
        }
        
        if (*delay_animacao > 0) {
            *animacao = *animacao + 1;
            *delay_animacao = 0;
        }
        
        for (i=0; i < 15; i++){
            destroy_bitmap (chute [i]);
        }
    } else if (*animacao == 15) {
        *animacao = 16;
    }
}

// Animacação Chuta Esquerda Não Defendido //
void efeito_acerto_esquerda (BITMAP *buffer_atual, int *animacao, int *delay_animacao) {
    if (*animacao < 15) {
        int i;
                
        SAMPLE *efeito_chute;
        SAMPLE *efeito_acerto;
        
        BITMAP *chute [15];
        
        *delay_animacao = *delay_animacao + 1;
                
        efeito_chute  = load_sample ("Audios/Efeito/efeito_chutar_bola.wav");
        efeito_acerto = load_sample ("Audios/Efeito/efeito_uhuu.wav");
        
        chute [0]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Esquerda/acerto_esquerda_0.tga",   NULL);
        chute [1]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Esquerda/acerto_esquerda_1.tga",   NULL);
        chute [2]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Esquerda/acerto_esquerda_2.tga",   NULL);
        chute [3]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Esquerda/acerto_esquerda_3.tga",   NULL);
        chute [4]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Esquerda/acerto_esquerda_4.tga",   NULL);
        chute [5]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Esquerda/acerto_esquerda_5.tga",   NULL);
        chute [6]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Esquerda/acerto_esquerda_6.tga",   NULL);
        chute [7]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Esquerda/acerto_esquerda_7.tga",   NULL);
        chute [8]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Esquerda/acerto_esquerda_8.tga",   NULL);
        chute [9]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Esquerda/acerto_esquerda_9.tga",   NULL);
        chute [10]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Esquerda/acerto_esquerda_10.tga", NULL);
        chute [11]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Esquerda/acerto_esquerda_11.tga", NULL);
        chute [12]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Esquerda/acerto_esquerda_12.tga", NULL);
        chute [13]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Esquerda/acerto_esquerda_13.tga", NULL);
        chute [14]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Esquerda/acerto_esquerda_14.tga", NULL);
        
        set_alpha_blender();
        draw_trans_sprite(buffer_atual, chute [*animacao], 0, 0);
        
        if (*animacao == 0) {
            play_sample (efeito_chute, 255, 128, 1000, 0);
        } else if (*animacao == 3) {
            play_sample (efeito_acerto, 255, 128, 1000, 0);
        }
        
        if (*delay_animacao > 0) {
            *animacao = *animacao + 1;
            *delay_animacao = 0;
        }
    
        for (i=0; i < 15; i++){
            destroy_bitmap (chute [i]);
        }
    } else if (*animacao == 15) {
        *animacao = 16;
    }
}

// Animacação Chuta Esquerda Não Defendido //
void efeito_acerto_direita (BITMAP *buffer_atual, int *animacao, int *delay_animacao) {
    if (*animacao < 15) {
        int i;
                
        SAMPLE *efeito_chute;
        SAMPLE *efeito_acerto;
        
        BITMAP *chute [15];
        
        *delay_animacao = *delay_animacao + 1;
                
        efeito_chute  = load_sample ("Audios/Efeito/efeito_chutar_bola.wav");
        efeito_acerto = load_sample ("Audios/Efeito/efeito_uhuu.wav");
        
        chute [0]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Direita/acerto_direita_0.tga",   NULL);
        chute [1]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Direita/acerto_direita_1.tga",   NULL);
        chute [2]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Direita/acerto_direita_2.tga",   NULL);
        chute [3]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Direita/acerto_direita_3.tga",   NULL);
        chute [4]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Direita/acerto_direita_4.tga",   NULL);
        chute [5]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Direita/acerto_direita_5.tga",   NULL);
        chute [6]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Direita/acerto_direita_6.tga",   NULL);
        chute [7]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Direita/acerto_direita_7.tga",   NULL);
        chute [8]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Direita/acerto_direita_8.tga",   NULL);
        chute [9]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Direita/acerto_direita_9.tga",   NULL);
        chute [10]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Direita/acerto_direita_10.tga", NULL);
        chute [11]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Direita/acerto_direita_11.tga", NULL);
        chute [12]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Direita/acerto_direita_12.tga", NULL);
        chute [13]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Direita/acerto_direita_13.tga", NULL);
        chute [14]  = load_bitmap ("Imagens/MiniGames/PerguntaResposta/Chutes/Acerto/Direita/acerto_direita_14.tga", NULL);
              
        set_alpha_blender();
        draw_trans_sprite(buffer_atual, chute [*animacao], 0, 0);
        
        if (*animacao == 0) {
            play_sample (efeito_chute, 255, 128, 1000, 0);
        } else if (*animacao == 3) {
            play_sample (efeito_acerto, 255, 128, 1000, 0);
        }
        
        if (*delay_animacao > 0) {
            *animacao = *animacao + 1;
            *delay_animacao = 0;
        }
    
        for (i=0; i < 15; i++){
            destroy_bitmap (chute [i]);
        }
    } else if (*animacao == 15) {
        *animacao = 16;
    }
}


// Pontuacao Jogo Pergunta e Resposta //
void jogo_pergunta_resposta_pontuacao(BITMAP *buffer_atual, int pontuacao) {
    BITMAP *pontos;
    BITMAP *quadro;
    
    quadro = load_bitmap ("Imagens/Minigames/PerguntaResposta/Pontuacao/quadro_pontuacao.tga", NULL);
    
    set_alpha_blender();
    draw_trans_sprite(buffer_atual, quadro, 10,  30);
    
    if (pontuacao == 0) {
    
        pontos = load_bitmap ("Imagens/Minigames/PerguntaResposta/Pontuacao/pontuacao_0.tga", NULL);
        
    } else if (pontuacao == 1) {

        pontos = load_bitmap ("Imagens/Minigames/PerguntaResposta/Pontuacao/pontuacao_1.tga", NULL);
        
    } else if (pontuacao == 2) {

        pontos = load_bitmap ("Imagens/Minigames/PerguntaResposta/Pontuacao/pontuacao_2.tga", NULL);
        
    } else if (pontuacao == 3) {
    
        pontos = load_bitmap ("Imagens/Minigames/PerguntaResposta/Pontuacao/pontuacao_3.tga", NULL);
        
    } else if (pontuacao == 4) {
        
        pontos = load_bitmap ("Imagens/Minigames/PerguntaResposta/Pontuacao/pontuacao_4.tga", NULL);
        
    } else if (pontuacao == 5) {
        
        pontos = load_bitmap ("Imagens/Minigames/PerguntaResposta/Pontuacao/pontuacao_5.tga", NULL);
    } 
    
    draw_trans_sprite(buffer_atual, pontos, 37,  80); 
    destroy_bitmap (pontos);
}

// Animacação Texto Sonho //
void efeito_texto_sonho (BITMAP *buffer_atual, int *animacao, int *delay_animacao, int posicao_x, int posicao_y) {
    if (*animacao <= 9) {
        int i;
    
        BITMAP *texto_sonho [10];
        *delay_animacao = *delay_animacao + 1;
    
        texto_sonho [0]  = load_bitmap ("Imagens/Sonho/texto_sonho_0.tga",  NULL);
        texto_sonho [1]  = load_bitmap ("Imagens/Sonho/texto_sonho_1.tga",  NULL);
        texto_sonho [2]  = load_bitmap ("Imagens/Sonho/texto_sonho_2.tga",  NULL);
        texto_sonho [3]  = load_bitmap ("Imagens/Sonho/texto_sonho_3.tga",  NULL);
        texto_sonho [4]  = load_bitmap ("Imagens/Sonho/texto_sonho_4.tga",  NULL);
        texto_sonho [5]  = load_bitmap ("Imagens/Sonho/texto_sonho_5.tga",  NULL);
        texto_sonho [6]  = load_bitmap ("Imagens/Sonho/texto_sonho_6.tga",  NULL);
        texto_sonho [7]  = load_bitmap ("Imagens/Sonho/texto_sonho_7.tga",  NULL);
        texto_sonho [8]  = load_bitmap ("Imagens/Sonho/texto_sonho_8.tga",  NULL);
        texto_sonho [9]  = load_bitmap ("Imagens/Sonho/texto_sonho_9.tga",  NULL);

        set_alpha_blender();
        draw_trans_sprite(buffer_atual, texto_sonho [*animacao], posicao_x, posicao_y);
    
        if (*delay_animacao > 0) {
            *animacao = *animacao + 1;
            *delay_animacao = 0;
        }
    
        for (i=0; i < 10; i++){
            destroy_bitmap (texto_sonho [i]);
        }
    } else if (*animacao == 11){
        BITMAP *texto_sonho;
        
        texto_sonho = load_bitmap ("Imagens/Sonho/texto_sonho_0.tga",  NULL);
        
        set_alpha_blender();
        draw_trans_sprite(buffer_atual, texto_sonho, posicao_x, posicao_y);
        
        if (key [KEY_ENTER]) {
            if (keypressed()) {
                *animacao = 0;
            }  
            clear_keybuf();
        }
        destroy_bitmap (texto_sonho);
    } 
}


// Tutorial_Mini_Game_Memória //
void tutorial_minigame_memoria (BITMAP *buffer_atual, int posicao_tutorial) {
     BITMAP *minigame [5]; 
     
     minigame [0] = load_bitmap ("Imagens/ObjetosDeInterface/Tutoriais/Mini_Game_Jogo_Memoria/tutorial_minigame_memoria_0.tga", NULL);
     minigame [1] = load_bitmap ("Imagens/ObjetosDeInterface/Tutoriais/Mini_Game_Jogo_Memoria/tutorial_minigame_memoria_1.tga", NULL);
     minigame [2] = load_bitmap ("Imagens/ObjetosDeInterface/Tutoriais/Mini_Game_Jogo_Memoria/tutorial_minigame_memoria_2.tga", NULL);
     minigame [3] = load_bitmap ("Imagens/ObjetosDeInterface/Tutoriais/Mini_Game_Jogo_Memoria/tutorial_minigame_memoria_3.tga", NULL);
     minigame [4] = load_bitmap ("Imagens/ObjetosDeInterface/Tutoriais/Mini_Game_Jogo_Memoria/tutorial_minigame_memoria_4.tga", NULL);
     
     if (posicao_tutorial < 5) {
         set_alpha_blender();
         draw_trans_sprite(buffer_atual, minigame[posicao_tutorial], 0, 0);
     }
     
     destroy_bitmap (minigame [0]);
     destroy_bitmap (minigame [1]);
     destroy_bitmap (minigame [2]);
     destroy_bitmap (minigame [3]);
     destroy_bitmap (minigame [4]);
}

// Final do Jogo de Memória //
void jogo_memoria_fim (BITMAP *buffer_atual) {
     BITMAP *fim; 
     
     fim = load_bitmap ("Imagens/ObjetosDeInterface/Tutoriais/Mini_Game_Jogo_Memoria/tutorial_minigame_memoria_fim.tga", NULL);
   
     set_alpha_blender();
     draw_trans_sprite(buffer_atual, fim, 0, 0);
     
     destroy_bitmap (fim);
}     

//FUNÇÃO PARA INSERIR NOMES
void rotina_ler_teclado(char nome [], int *indice_vetor) {
  if(key[KEY_A]){
    strcat(nome,"A");
    *indice_vetor = *indice_vetor + 1;
    rest (200);
  } else if(key[KEY_B]){
    strcat(nome,"B");
    *indice_vetor = *indice_vetor + 1;
    rest (200);
  } else if(key[KEY_C]){
    strcat(nome,"C");
    *indice_vetor = *indice_vetor + 1;
    rest (200);
  } else if(key[KEY_D]){
    strcat(nome,"D");
    *indice_vetor = *indice_vetor + 1;
    rest (200);
  } else if(key[KEY_E]){
    strcat(nome,"E");
    *indice_vetor = *indice_vetor + 1;
    rest (200);
  } else if(key[KEY_F]){
    strcat(nome,"F");
    *indice_vetor = *indice_vetor + 1;
    rest (200);
  } else if(key[KEY_G]){
    strcat(nome,"G");
    *indice_vetor = *indice_vetor + 1;
    rest (200);
  } else if(key[KEY_H]){
    strcat(nome,"H");
    rest (200);
    *indice_vetor = *indice_vetor + 1;
  } else if(key[KEY_I]){
    strcat(nome,"I");
    *indice_vetor = *indice_vetor + 1;
    rest (200);
  } else if(key[KEY_J]){
    strcat(nome,"J");
    *indice_vetor = *indice_vetor + 1;
    rest (200);
  } else if(key[KEY_K]){
    strcat(nome,"K");
    *indice_vetor = *indice_vetor + 1;
    rest (200);
  } else if(key[KEY_L]){
    strcat(nome,"L");
    *indice_vetor = *indice_vetor + 1;
    rest (200);
  } else if(key[KEY_M]){
    strcat(nome,"M");
    *indice_vetor = *indice_vetor + 1;
    rest (200);
  } else if(key[KEY_N]){
    strcat(nome,"N");
    *indice_vetor = *indice_vetor + 1;
    rest (200);
  } else if(key[KEY_O]){
    strcat(nome,"O");
    *indice_vetor = *indice_vetor + 1;
    rest (200);
  } else if(key[KEY_P]){
    strcat(nome,"P");
    *indice_vetor = *indice_vetor + 1;
    rest (200);
  } else if(key[KEY_Q]){
    strcat(nome,"Q");
    rest (200);
  } else if(key[KEY_R]){
    strcat(nome,"R");
    *indice_vetor = *indice_vetor + 1;
    rest (200);
  } else if(key[KEY_S]){
    strcat(nome,"S");
    *indice_vetor = *indice_vetor + 1;
    rest (200); 
  } else if(key[KEY_T]){
    strcat(nome,"T");
    *indice_vetor = *indice_vetor + 1;
    rest (200);
  } else if(key[KEY_U]){
    strcat(nome,"U");
    *indice_vetor = *indice_vetor + 1;
    rest (200);
  } else if(key[KEY_V]){
    strcat(nome,"V");
    *indice_vetor = *indice_vetor + 1;
    rest (200);
  } else if(key[KEY_X]){
    strcat(nome,"X");
    *indice_vetor = *indice_vetor + 1;
    rest (200);
  } else if(key[KEY_Z]){
    strcat(nome,"Z");
    *indice_vetor = *indice_vetor + 1;
    rest (200);
  } else if(key[KEY_SPACE]){
    strcat(nome," ");
    *indice_vetor = *indice_vetor + 1;
    rest (200);
  }

}

// Função Composição de Ponto //
float composicaoPonto(int moeda, int experiencia_total)
{
    float ponto;

    ponto = (experiencia_total / 50) + (moeda * 5);

    return(ponto);
}

// Procedimento de Ordenar Vetor //
void ordenaVetor(Treg_ranking vet[5])
{
    int i, j, k;
    Treg_ranking aux;

    k = 4;
    i = 0;
    j = 0;

    for (i = 0; i <= 5; i++)
    {
        for(j=0; j<k;j++)
        {
            if(vet[j].ponto < vet[j+1].ponto)
            {
                aux = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = aux;
            }
        }
        k = k - 1;
    }
}

// Construção de Ranking //
void salvar_ranking (BITMAP *buffer_atual, int ponto, char nome [15]) {
    Treg_ranking jogadorRanking;
    Tarq_ranking arquivo, aux;
    Treg_ranking vet[5];
    int num;
    int i;
    
    SAMPLE *som_erro;
    BITMAP *mensagem_erro;
    
    som_erro = load_sample ("Audios/Efeito/efeito_negado.wav");
    
    arquivo = fopen ("Ranking/ranking.dat", "ab");
    
    strcpy (jogadorRanking.nome, nome);
    jogadorRanking.ponto = ponto;
    
    if (arquivo == NULL) {
        play_sample (som_erro, 255, 128, 1000, 0);
        //set_alpha_blender();
        //draw_trans_sprite(buffer_atual, mensagem_erro, 0, 0);
        while (!key[KEY_ENTER]);    
    } else {
        num = contagem();
        if(num < 5)
        {
            fwrite (&jogadorRanking, sizeof (Treg_ranking), 1, arquivo);
        }
        else 
        {
            rewind(arquivo);
            i = 0;
            fread (&jogadorRanking, sizeof (Treg_ranking), 1, arquivo);
            vet[i] = jogadorRanking;
            i++;
            while (!feof(arquivo) && (i<5)) 
            {
                fread (&jogadorRanking, sizeof (Treg_ranking), 1, arquivo);
                vet[i] = jogadorRanking;
                i++;    
            }
            ordenaVetor(vet);
            aux = fopen("Ranking/aux.dat", "w+b");
            rewind (arquivo);
            fread (&jogadorRanking, sizeof (Treg_ranking), 1, arquivo);
            while(!feof (arquivo))
            {
                 if (vet[4].ponto >= ponto)
                 {
                     fwrite(&jogadorRanking,sizeof(Treg_ranking), 1, aux);
                 }
                 fread (&jogadorRanking, sizeof (Treg_ranking), 1, arquivo);
            }
            jogadorRanking.ponto = ponto;
            strcpy (jogadorRanking.nome, nome);
            
            fwrite(&jogadorRanking,sizeof(Treg_ranking), 1, aux);
            
            fclose(arquivo);
            fclose(aux);
            system("del Ranking/ranking.dat");
            system("ren Ranking/aux.dat Ranking/ranking.dat");  
            }
        }    
}

// Animacação Numeros Aleotorios //
void efeito_numeros (BITMAP *buffer_atual, int *animacao, int *delay_animacao, int posicao_x, int posicao_y) {
    if (*animacao < 10) {
        int i;
                
        //SAMPLE *efeito_numeros_mudando;
        
        BITMAP *numero [10];
        
        *animacao = *animacao + 1;
                
        //efeito_numeros_mudando  = load_sample ("Audios/Efeito/efeito_chutar_bola.wav");
        
        if (*animacao > 9) {
            *animacao = 0;
            *delay_animacao = *delay_animacao + 1;
        }
        
        numero [0]  = load_bitmap ("Imagens/Animacoes/Numeros/numeros_0.tga", NULL);
        numero [1]  = load_bitmap ("Imagens/Animacoes/Numeros/numeros_1.tga", NULL);
        numero [2]  = load_bitmap ("Imagens/Animacoes/Numeros/numeros_2.tga", NULL);
        numero [3]  = load_bitmap ("Imagens/Animacoes/Numeros/numeros_3.tga", NULL);
        numero [4]  = load_bitmap ("Imagens/Animacoes/Numeros/numeros_4.tga", NULL);
        numero [5]  = load_bitmap ("Imagens/Animacoes/Numeros/numeros_5.tga", NULL);
        numero [6]  = load_bitmap ("Imagens/Animacoes/Numeros/numeros_6.tga", NULL);
        numero [7]  = load_bitmap ("Imagens/Animacoes/Numeros/numeros_7.tga", NULL);
        numero [8]  = load_bitmap ("Imagens/Animacoes/Numeros/numeros_8.tga", NULL);
        numero [9]  = load_bitmap ("Imagens/Animacoes/Numeros/numeros_9.tga", NULL);
              
        set_alpha_blender();
        draw_trans_sprite(buffer_atual, numero [*animacao], posicao_x, posicao_y);
        
        
        if (*delay_animacao > 3) {
            *animacao = 10;
        }
    
        for (i=0; i < 10; i++){
            destroy_bitmap (numero [i]);
        }
    }
}

// Contagem de Registros //
int contagem ()
{
     Tarq_ranking arq_ranking;
     Treg_ranking reg_ranking;
     int tamanho_arquivo;
     int tamanho_registro;
     int num;
     
     num = 1;
     
     arq_ranking = fopen ("Ranking/ranking.dat","rb");
     
     if (arq_ranking != NULL) {     
         fseek(arq_ranking, 0, SEEK_END);
         tamanho_arquivo  = ftell (arq_ranking);
         tamanho_registro = sizeof (Treg_ranking); 
         num = tamanho_arquivo/ tamanho_registro;
         fclose(arq_ranking);
     }
     return(num);
}

// Mostra Pontuação Na Tela de Ranking //
void mostrar_pontuacao_ranking (BITMAP *buffer_atual, DATAFILE *fonte) {
    Treg_ranking ranking;
    Treg_ranking vet[5];
    Tarq_ranking arquivo;
    char nome[15];
    char ponto[15];
    long pos;
    int i;
    
    for (i=0; i<5; i++) {
        strcpy (vet[i].nome, "");
        vet[i].ponto = 0;
    }
    i=0;
    
    arquivo = fopen ("Ranking/ranking.dat", "rb");
    fread (&ranking, sizeof (Treg_ranking), 1, arquivo);
    
    while (!feof(arquivo)) {
        vet[i] = ranking;
        i = i + 1;
        fread (&ranking, sizeof (Treg_ranking), 1, arquivo);
    } 
    
    ordenaVetor(vet);
    
    for (i=0; i<5; i++) {
        sprintf(nome, "%s", vet[i].nome);
        sprintf(ponto, "%i", vet[i].ponto);
        if (i<2) {
            textout_ex(buffer_atual, (FONT *)fonte[0].dat, nome, 205, 123 + 94 * i, makecol(0,0,0),-1 );
            textout_ex(buffer_atual, (FONT *)fonte[0].dat, ponto, 690, 125 + 95 * i, makecol(0,0,0),-1 );
        } else {
            textout_ex(buffer_atual, (FONT *)fonte[0].dat, nome, 205, 126 + 95 * i, makecol(0,0,0),-1 );
            textout_ex(buffer_atual, (FONT *)fonte[0].dat, ponto, 690, 127 + 96 * i, makecol(0,0,0),-1 );
        }
    }
    fclose (arquivo);
} 
