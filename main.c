#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "PE.h" //pilha estática
//#include "PD.h" //pilha dinâmica
#include "FE.h" //fila estática
//#include "FD.h" //fila dinâmica

#include "main.h"

URL url_atual;

/////////////////////////////////// DOWNLOAD ////////////////////////////////////////////////////

// Processa o download que está ativo e inicia um novo se a fila não estiver vazia
void processar_downloads(Fila *fila_downloads, DownloadON *download_on) {
    Download temp;

    //se tem algum download ativo, vê quando tempo falta (Tfalta)
    if (download_on->on) {
        download_on->Tfalta--;

        if (download_on->Tfalta == 0) {
            printf("download %s concluido\n", download_on->url);
            download_on->on = 0;
            download_on->url[0] = '\0';
        }
    }

    //se não tem nenhum download acontecendo mas tem itens na fila
    if (!download_on->on && !f_vazia(fila_downloads)) {
        if (pop_f(fila_downloads, &temp)) {
            download_on->on = 1;
            strcpy(download_on->url, temp.url);
            download_on->Tfalta = temp.Tfalta;
            printf("iniciando download %s. Termino em %d comandos\n", download_on->url, download_on->Tfalta);
        }
    }
}

///////////////////////////////////////// HISTÓRICO ///////////////////////////////////////////

void remove_historico(Pilha *historico, URL nova_url) {
    if (p_cheia(historico)) {
        // remove o elemento da base e move todos os outros elementos uma posição para baixo.
        for (int i = 0; i < historico->topo; i++) {
            strcpy(historico->info[i], historico->info[i + 1]);
        }
        historico->topo--; // reduz o topo
    }
}

////////////////////////////////////// URL /////////////////////////////////////////////////

// Adiciona uma URL ao histórico levando em consideração a capacidade
void visita_pagina(Pilha *historico, URL nova_url) {
    // Se o historico estiver cheio (com 10 URLs), remova do historico a pagina visitada por primeiro;
    if (p_cheia(historico))
        remove_historico(historico);

    push_p(historico, nova_url); //adiciona o novo url
    strcpy(url_atual, nova_url); //copia o url para colocar na mensagem de visualização

    printf("visualizando %s\n", url_atual);
}

//////////////////////////////////////// VOLTAR /////////////////////////////////////////////////

void voltar(Pilha *historico){
    URL url_temp;
    //vai tentar removar a página atual
    if(pop_p(historico, url_temp))){
        if(p_tam(historico) > 0){ //se ainda tem coisa na pilha depois do pop
            URL ant; //armazena a página anterior
            pop_p(historico, ant); //tira o topo para consultar
            push_p(historico, ant); //coloca de volta depois de ver

            strcpy(url_atual, ant);
            printf("visualizando %s\n", url_atual);
        }
        else{ //se a pilha ficou vazia
            strcpy(url_atual, "pagina em branco"); //atribui a mensagem
            printf("visualizando %s\n", url_atual;)
        }
    }
    else{ //a pilha já estava vazia no começo
        printf("visualizando pagina em branco \n");
    }

}

////////////////////////////////////////////// MAIN //////////////////////////////////////////////////

int main() {
    Pilha historico; //pilha de páginas visitadas
    Fila fila_downloads; //fila dos downloads pendentes
    DownloadON download_on = {"", 0, 0}; //inicializando tudo em nulo ou em zero

    cria_fila(&fila_downloads);
    cria_pilha(&historico);
    strcpy(url_atual, "pagina em branco"); //a página inicial é definida em branco, já que nenhuma foi acessada ainda

    char linha_comando[500]; //salva a linha inteira que foi inserida
    char comando[100]; //salva só o comando
    char Durl[MAX_URL]; //salva o url inserido, ou o segundo comando
    int tempo; //salva o número que é o tempo de download

    //stdin é para ler os dados
    //fgets serve pra ler tudo até o \n
    while (fgets(linha_comando, sizeof(linha_comando), stdin) != NULL) {
        // remove o '\n' final
        //strcspn serve pra delimitar a frase até o \n
        linha_comando[strcspn(linha_comando, "\n")] = 0;

        // Limpa variáveis antes de usar pra não ter bug com o que tinha nelas antes
        comando[0] = Durl[0] = '\0';
        tempo = 0;

        //sscanf é para ler várias variáveis de uma vez
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
                    strcpy(novo.url, Durl); //copia o url digitado (Durl)
                    novo.Tfalta = tempo;

                    if (f_cheia(&fila_downloads)) { //se a fila de downloads estiver cheia
                        printf("fila cheia; arquivo nao inserido na fila\n");
                    } else {
                        if(push_f(&fila_downloads, novo))
                            printf("inserido %s na fila\n", novo.url);
                    }
                }
                break;

            case 'F':
                int total_downloads = f_tam(&fila_downloads);
                if(download_on.on)
                    total_downloads++;
                printf("arquivos na fila de download: %d\n", total_downloads);
                printf("paginas no historico: %d\n", p_tam(&historico));
                free_p(&historico);
                free_f(&fila_downloads);
                return 0;

            default: //ignora comandos desconhecidos
                break;
        }

        processar_downloads(&fila_downloads, &download_on); //processar downloads após cada comando executado
    }

    free_p(&historico);
    free_f(&fila_downloads);
    return 0;
}
