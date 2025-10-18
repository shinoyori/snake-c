# Jogo da Cobrinha em C (Console)

Um remake do clássico jogo da cobrinha (Snake Game) desenvolvido em linguagem C para rodar no console (Windows). Esta versão utiliza a estrutura de dados de **Fila (Queue)** para gerenciar o corpo da cobra e inclui um recurso de obstáculo dinâmico: a bomba. Este projeto foi desenvolvido para a disciplina de Algoritmos e Estruturas de Dados 1 da UFSCar.

## Funcionalidades

  * **Implementação Clássica:** Movimento da cobra usando teclas `W`, `A`, `S`, `D`.
  * **Estrutura de Dados:** O corpo da cobra é implementado como uma **Fila (Queue)** com alocação dinâmica (`malloc`).
  * **Pontuação Dinâmica:** A pontuação é baseada no comprimento atual da cobra (`length`).
  * **Velocidade Crescente:** A velocidade do jogo aumenta à medida que a cobra cresce, tornando o jogo progressivamente mais desafiador.
  * **Colisão e Fim de Jogo:** O jogo termina se a cobra colidir com as paredes (`#`) ou com seu próprio corpo.
  * **Recursos Adicionais:**
      * **Comida (`*`):** Aumenta o comprimento e a pontuação em 1.
      * **Bomba (`X`):** Reduz o comprimento da cobra em 2 segmentos. Se o comprimento for menor ou igual a 2, o jogador perde uma vida (Game Over).
      * **Vidas:** A cobra começa com 1 vida (`lives = 1`) e pode perdê-la ao colidir com uma bomba se estiver muito curta.


## Controles

| Tecla | Ação |
| :---: | :--- |
| **W** | Mover para Cima |
| **S** | Mover para Baixo |
| **A** | Mover para a Esquerda |
| **D** | Mover para a Direita |

## Como Compilar e Executar

1.  **Clone o repositório:**

    ```bash
    git clone [LINK_DO_SEU_REPOSITÓRIO]
    cd [pasta-do-jogo]
    ```

2.  **Compile o código** usando o GCC (ou MinGW):

    > Certifique-se de que o compilador está acessível no seu terminal.

    ```bash
    gcc main.c snake.c -o snake_game.exe
    ```

3.  **Execute o jogo:**

    ```bash
    ./snake_game.exe
    ```

