#include <stdio.h>


typedef struct processo{ //cria uma estrutura com os dados de id, tempo e tempo executado com o nome processo
    int id;
    int tempo;
    int tempoExecutado;
    int turnaround;
    int tempoEspera;
} Processo;

int Finalizados(Processo*, int); //prototipo da função finalizados

int main(){
    int quantum; //armazena o quantum
    int quant; // armazena a quantidade de processos que serão cadastrados

    printf("Digite o valor do Quantum (1-5): ");
    scanf("%d", &quantum); // le o valor de quantum pelo usuario

    //verifica se ele esta entre 1 e 5
    if(quantum < 1){
        printf("Valor menor que minimo\nQuantum = 1");
        quantum = 1;
    } else if(quantum > 5){
        printf("Valor maior que o maximo\nQuantum = 5");
        quantum = 5;
    }


    printf("Quantos processos serao cadastrados: ");
    scanf("%d", &quant); //le o valor de processos que serão cadastrados

    //verifica se o valor de processos é maior que zero
    if(quant <= 0){
        printf("Valor menor que minimo\nTotal Processos = 1");
        quant = 1;
    }

    Processo proccess[quant]; //cria um vetor vazio com espaço dado pelo usuario

    //looping para criar processos
    for(int i=0; i < quant ; i++){
        proccess[i].id = i+1; //coloca o id
        proccess[i].tempoExecutado = 0; //zera o tempo executado
        proccess[i].turnaround = 0; //zera o turnaround
        proccess[i].tempoEspera = 0; //zera o tempo de espera
        printf("Digite o tempo(ms) do processo %d: ", proccess[i].id);
        scanf("%d", &proccess[i].tempo); //pega o tempo do processo pelo usuario

        //verifica se ele é menor q 1
        if(proccess[i].tempo < 1){
            printf("Valor menor que minimo\nTempo do processo = 1ms");
            proccess[i].tempo = 1; //iguala a 1
        }
    }

    // imprime todos os processos
    printf("\nPROCESSOS CADASTRADOS ---------------------------------------\n");
    for(int i=0; i < quant; i++){
        printf("ID: %d\nTempo:%d", proccess[i].id, proccess[i].tempo);
        printf("\n\n");
    }

    int cronometro=0; //zera o cronometro dos processos

    for(int i=0; i < quant; i++){
        if(proccess[i].tempo == proccess[i].tempoExecutado){ //se o tempo do processo for igual ao tempo executado
            if(i == quant-1 && Finalizados(proccess, quant) != quant){ //se for o ultimo item da fila porem não estão todos itens da fila finalizados
                i = 0; //volte para o inicio da fila
            }
            else //se não, só pular para o proximo item
                continue; //pula para o proximo. i+1
                
        }

        printf("O processo %d entrou no processador (%dms de %dms).\n", proccess[i].id, proccess[i].tempoExecutado, proccess[i].tempo);
        
        if(Finalizados(proccess, quant) != quant-1){ //se o processo atual NÃO ser o ultimo a ser finalizado
            cronometro += quantum;
            proccess[i].tempoExecutado += quantum;
        }
        else{ //se o processo atual for o ultimo a ser finalizado
            while(proccess[i].tempoExecutado < proccess[i].tempo){
                cronometro += quantum;
                proccess[i].tempoExecutado += quantum;
            }
        }

        if(proccess[i].tempoExecutado >= proccess[i].tempo){
            cronometro -= proccess[i].tempoExecutado - proccess[i].tempo;
            proccess[i].tempoExecutado = proccess[i].tempo;
            proccess[i].turnaround = cronometro;
            proccess[i].tempoEspera = proccess[i].turnaround - proccess[i].tempo;
            printf("O processo %d foi finalizado (%dms).\n", proccess[i].id, proccess[i].tempo);
        }

        printf("O processo %d saiu do processador (%dms de %dms).\n", proccess[i].id, proccess[i].tempoExecutado, proccess[i].tempo);

        
        if(i == quant - 1 && Finalizados(proccess, quant) != quant){// se for o ultimo item da fila e tem processos não finalizados
            i = -1; //volta para o inicio da fila
        }
    }

    printf("Todos os processos foram finalizados.\n");

    float tmr=0, tme=0;

    printf("\nPROCESSOS CADASTRADOS ---------------------------------------\n");
    for(int i=0; i < quant; i++){
        tmr += proccess[i].turnaround;
        tme += proccess[i].tempoEspera;
        printf("ID: %d\nTempo: %dms\nTurnaround: %dms\nTEP: %dms", proccess[i].id, proccess[i].tempo, proccess[i].turnaround, proccess[i].tempoEspera);
        printf("\n\n");
    }

    printf("Tempo Medio de Espera: %.2f\nTempo Medio de Retorno: %.2f", tme/quant, tmr/quant);

    return 0;
}

int Finalizados(Processo *pro, int lenght){
    int finalizados=0; //variavel para armazenar os finalizados
    for(int i=0; i< lenght; i++){ //looping para percorrer por todos os processos 
        if(pro[i].tempo == pro[i].tempoExecutado) //se o item estiver finalizado
            finalizados++; //adicione mais um em finalizados
    }

    return finalizados; //retorna o valor de finalizados
}