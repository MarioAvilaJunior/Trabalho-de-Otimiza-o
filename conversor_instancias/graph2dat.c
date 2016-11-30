#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

    if (argc != 3) {
        printf("Parametros invalidos. Modo de uso:\n");
        printf("%s arquivo_de_origem.graph arquivo_de_destino.dat\n\n", argv[0]);
        return -1;    
    } else {

        FILE *arquivo, *data;
        char linha[256], *pch;
        printf("Abrindo arquivo de origem...\n");
        arquivo = fopen(argv[1], "r");
        printf("Abrindo arquivo de destino...\n");
        data = fopen (argv[2], "w");
        int inteiro;
        int vertice, max_vertices;
        //int vizinhos[200], i = 1, k, igual = 0;

        if (!arquivo)
        {
            printf ("Erro na abertura do arquivo \"%s\".\n",argv[1]);
            return -2;
        }
        else
        {
            printf("Convertendo arquivo...\n");
            fgets(linha, sizeof(linha), arquivo);
            pch = strtok(linha, " ");
            fprintf (data, "#numero de vertices\nparam n := %s;\n\n", pch);
            max_vertices = atoi(pch);
            pch = strtok(NULL, " ");
            printf ("Numero de vertices no arquivo: %d\n", max_vertices);
            printf ("Numero de arestas no arquivo: %s\n", pch);
            fprintf (data, "#numero de arestas\nparam m := %s;\n", pch);
            //printf("#numero de arestas\nparam m := %s;\n", pch);

            fprintf(data, "#arestas do grafo\n");
            //printf("#arestas do grafo\n");
            fprintf(data, "param : A : arestas_inclusas :=\n");
            //printf("param : A : I :=\n");
            printf("Lendo vizinhos dos vertices...\n");
            for(vertice = 1; vertice <= max_vertices; vertice++)
            {
                //printf("%d ", vertice);
                fgets(linha, sizeof(linha), arquivo);
                pch = strtok(linha, " ");
                //inteiro = atoi(pch); //Primeiro vizinho do vertice
                //fprintf (data, "  %d %d 1\n", vertice, inteiro);
                //printf("antes do while\n");
                while (pch != NULL)
                {
                    //printf("(%d %s)\n", vertice, pch);
                    inteiro = atoi(pch);
                    if (inteiro != 0)
                        fprintf (data, "  %d %d 1\n", vertice, inteiro);
                    pch = strtok(NULL, " ");
                }
            }
            //printf("\nFim do arquivo.\n\n");
        }

        fprintf (data, ";\n\nend;\n");
        fclose(arquivo);
        fclose(data);

        printf("\n=== Conversao concluida. ===\n\n");
    }

    return 0;
}

