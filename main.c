#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "PE.h" //pilha est�tica
//#include "PD.h" //pilha din�mica
#include "FE.h" //fila est�tica
//#include "FD.h" //fila din�mica

#include "main.h"

URL url_atual;

/////////////////////////////////// DOWNLOAD ////////////////////////////////////////////////////

// Processa o download que est� ativo e inicia um novo se a fila n�o estiver vazia
void processar_downloads(Fila *fila_downloads, DownloadON *download_on) {
    Download temp;

    //se tem algum download ativo, v� quando tempo falta (Tfalta)
    if (download_on->on) {
        download_on->Tfalta--;

        if (download_on->Tfalta == 0) {
            printf("download %s concluido\n", download_on->url);
            download_on->on = 0;
            download_on->url[0] = '\0';
        }
    }

    //se n�o tem nenhum download acontecendo mas tem itens na fila
    if (!download_on->on && !f_vazia(fila_downloads)) {
        if (pop_f(fila_downloads, &temp)) {
            download_on->on = 1;
            strcpy(download_on->url, temp.url);
            download_on->Tfalta = temp.Tfalta;
            printf("iniciando download %s. Termino em %d comandos\n", download_on->url, download_on->Tfalta);
        }
    }
}

///////////////////////////////////////// HIST�RICO ///////////////////////////////////////////

void remove_historico(Pilha *historico) {
    if (p_cheia(historico)) {
        // remove o elemento da base e move todos os outros elementos uma posi��o para baixo.
        for (int i = 0; i < historico->topo; i++) {
            strcpy(historico->info[i], historico->info[i + 1]);
        }
        historico->topo--; // Reduz o topo
    }
}

////////////////////////////////////// URL /////////////////////////////////////////////////

// Adiciona uma URL ao hist�rico levando em considera��o a capacidade
void visita_pagina(Pilha *historico, URL nova_url) {
    // se hist�rico estiver cheio remove o primeiro a entrar
    if (p_cheia(historico))
        remove_historico(historico);

    push_p(historico, nova_url);
    strcpy(url_atual, nova_url);

    printf("visualizando %s\n", url_atual);
}

//////////////////////////////////////// VOLTAR /////////////////////////////////////////////////

void voltar(Pilha *historico){
    URL url_temp;

    if(p_tam(historico) > 0 && pop_p(historico, url_temp)){
        URL ant;
    }

    if(p_tam(historico) > 0 && pop_p(historico, ant)){
        push_p(historico, ant); //coloca de volta no topo
        strcpy(url_atual, ant);
        printf("visualizando %s\n", url_atual);
    }
    else{
            strcpy(url_atual, "pagina em branco");
        printf("visualizando pagina em branco \n");
    }

}

////////////////////////////////////////////// MAIN //////////////////////////////////////////////////

int main() {
    Pilha historico; //pilha de p�ginas visitadas
    Fila fila_downloads; //fila dos downloads pendentes
    DownloadON download_on = {"", 0, 0}; //inicializando tudo em nulo ou em zero

    cria_fila(&fila_downloads);
    cria_pilha(&historico);
    strcpy(url_atual, "pagina em branco"); //a p�gina inicial � definida em branco, j� que nenhuma foi acessada ainda

    char linha_comando[500]; //salva a linha inteira que foi inserida
    char comando[100]; //salva s� o comando
    char Durl[MAX_URL]; //salva o url inserido, ou o segundo comando
    int tempo; //salva o n�mero que � o tempo de download

    //stdin � para ler os dados
    //fgets serve pra ler tudo at� o \n
    while (fgets(linha_comando, sizeof(linha_comando), stdin) != NULL) {
        // Remove o '\n' final
        //strcspn serve pra delimitar a frase at� o \n
        linha_comando[strcspn(linha_comando, "\n")] = 0;

        // Limpa vari�veis antes de usar pra n�o ter bug com o que tinha nelas antes
        comando[0] = Durl[0] = '\0';
        tempo = 0;

        int args = sscanf(linha_comando, "%s %s %d", comando, Durl, &tempo);
        //comando, url e tempo

        switch (comando[0]) {

            case 'v': //VISITAR OU VOLTAR
                if (strcmp(comando, "visitar") == 0 && args >= 2) {
                    visita_pagina(&historico, Durl);
                }
                else if (strcmp(comando, "voltar") == 0) {
                    voltar(&historico);
                }
                break;


            case 'd': //DOWNLOAD
                if (strcmp(comando, "download") == 0 && args == 3) {
                    Download novo;
                    strcpy(novo.url, Durl);
                    novo.Tfalta = tempo;

                    if (f_cheia(&fila_downloads)) {
                        printf("fila cheia; arquivo nao inserido na fila\n");
                    } else {
                        push_f(&fila_downloads, novo);
                        printf("inserido %s na fila\n", novo.url);
                    }
                }
                break;

            case 'F':
                printf("arquivos na fila de download: %d\n",
                       f_tam(&fila_downloads) + (download_on.on ? 1 : 0));
                printf("paginas no historico: %d\n", p_tam(&historico));
                free_p(&historico);
                free_f(&fila_downloads);
                return 0;

            default: //ignora comandos desconhecidos
                break;
        }

        processar_downloads(&fila_downloads, &download_on); //processar downloads ap�s cada comando executado
    }

    free_p(&historico);
    free_f(&fila_downloads);
    return 0;
}
