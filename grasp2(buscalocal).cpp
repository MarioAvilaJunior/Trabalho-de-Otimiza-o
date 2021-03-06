#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <ctime>

#define GRUPO_A 0
#define GRUPO_B 1


int numero_vertices;
int numero_arestas;
std::vector< std::vector<int> > vertices;
//std::vector<int> solucao(numero_vertices, -1); //Cria um vetor com |V| elementos, cada um com valor -1.
double alpha;

int leitor_entrada (void);
void construir_solucao_inicial (std::vector<int>& solucao);
void exibe_arestas_corte (const std::vector<int>& solucao, int inteiro);
void busca_local (std::vector<int>& solucao, const std::vector< std::vector<int> >& vertices);


int main (int argc, char **argv) {

    if (argc != 2) {
        std::cout<< "Usage: " << argv[0] << " valor_do_alfa";
    } else {
        alpha = atof(argv[1]);

        std::cout << "alfa escolhido: " << alpha << "\n";
        numero_vertices = leitor_entrada();
        std::vector<int> solucao(numero_vertices, -1); //Cria um vetor com |V| elementos, cada um com valor -1.
        construir_solucao_inicial(solucao);
        exibe_arestas_corte(solucao, 0);
        busca_local (solucao, vertices);
        exibe_arestas_corte (solucao, 1);
    }

    return 0;
}

int leitor_entrada (void) {
    std::string linha;
    char * linha_char;
    char * pch;
    int inteiro;

    getline (std::cin,linha);
    linha_char = new char [linha.length()+1];
    std::strcpy (linha_char, linha.c_str());
    pch = strtok (linha_char, " ");
    std::cout << "Numero de vertices: " << pch << "\n";
    numero_vertices = atoi (pch); //Numero de vertices no grafo
    pch = strtok(NULL, " ");
    std::cout << "Numero de arestas: " << pch << "\n";
    numero_arestas = atoi (pch); //Numero de arestas no grafo
    for (int i = 0; i < numero_vertices; i++) //Para cada vertice v
    {
        std::vector<int>temp;
        getline (std::cin,linha);
        linha_char = new char [linha.length()+1];
        std::strcpy (linha_char, linha.c_str());
        pch = strtok (linha_char, " ");
        //std::cout << inteiro << " ";
        //Sleep(200);
        while (pch != NULL) //Indique os vizinhos do vertice v.
        {
            inteiro = atoi (pch);
            if (inteiro != 0)
            {
                temp.push_back(inteiro -1);
                //std::cout << inteiro << " ";
                //Sleep(200);
            }
            pch = strtok(NULL, " ");
        }
        vertices.push_back(temp);
        temp.clear();
    }
    std::cout << "Leitura concluida.\n";
    return numero_vertices;
}


void construir_solucao_inicial (std::vector<int>& solucao) {
    int vertice_aleatorio_um;
    int vertice_aleatorio_dois;
    int grupo_selecionado;
    int outro_grupo;
    int menor_diferenca;
    int diferenca;
    int aleatorio;


    //std::vector<int> solucao(numero_vertices, -1); //Cria um vetor com |V| elementos, cada um com valor -1.
    std::vector<int> candidatos; //Lista de candidatos.
    std::vector<int> diferencas(numero_vertices);
    srand(time(NULL));
    do {
        vertice_aleatorio_um = rand() % numero_vertices; //Gera um numero aleatorio entre 0 e |V|-1
        vertice_aleatorio_dois = rand() % numero_vertices; //Gera um numero aleatorio entre 0 e |V|-1
    } while (vertice_aleatorio_um == vertice_aleatorio_dois);   //vertices u e v devem ser distintos.

    std::cout << "primeiro vertice em A: \n" << vertice_aleatorio_um << "\n";
    std::cout << "primeiro vertice em B: \n" << vertice_aleatorio_dois << "\n";



    solucao[vertice_aleatorio_um] = GRUPO_A;

    solucao[vertice_aleatorio_dois] = GRUPO_B;
    grupo_selecionado = GRUPO_B;

    for (int v = 0; v < numero_vertices - 2; v++) {
        grupo_selecionado = 1 - grupo_selecionado;
        outro_grupo = 1 - grupo_selecionado;
        menor_diferenca = numero_arestas;
        diferenca = 0;
        for (int i = 0; i < numero_vertices; i++) { //Para todo vertice
            if (solucao[i] == -1) { //Se o vertice ainda nao foi selecionado.
                for (unsigned int j = 0; j < vertices[i].size(); j++) { //Para todo vizinho do vertice...
                    if (solucao[vertices[i][j]] == grupo_selecionado) {
                        diferenca--;
                    } else if (solucao[vertices[i][j]] == outro_grupo) {
                        diferenca++;
                    }
                }
                diferencas[i] = diferenca;
                if (diferenca < menor_diferenca) {
                    menor_diferenca = diferenca;
                }
            }
        }

        for (int i = 0; i < numero_vertices; i++) {
            //Forma RCL
            if (solucao[i] == -1 && (diferencas[i] <= menor_diferenca + (abs(menor_diferenca) * alpha)))
                candidatos.push_back(i);
        }

        srand(time(NULL));
        aleatorio = rand() % candidatos.size(); //Pegar um aleatorio entre a lista de candidatos.
        solucao[candidatos[aleatorio]] = grupo_selecionado;

        candidatos.clear();

        /*if (v > 0 && v % 10 == 0) {
            std::cout << v << " ";
        }*/
    }
}
void exibe_arestas_corte(const std::vector<int>& solucao, int inteiro){
    int arestas_de_corte = 0;

    for (unsigned int i = 0; i < solucao.size(); i++) {
        if (solucao[i] == 0) {
            for (unsigned int j = 0; j < vertices[i].size(); j++) {
                if (solucao[vertices[i][j]] == 1) {
                    arestas_de_corte++;
                }
            }
        }
    }


    std::cout <<"\n\nGrupo A:\n";
    for (int i = 0; i < numero_vertices; i++ ) {
        if (solucao[i] == GRUPO_A) {
            std::cout << " " << i+1;
        }
    }
    std::cout <<"\nGrupo B:\n";
    for (int i = 0; i < numero_vertices; i++ ) {
        if (solucao[i] == GRUPO_B) {
            std::cout << " " << i+1;
        }
    }
    if (inteiro == 0)
    std::cout << "\n\nSolucao inicial (SI):\nArestas de corte: " << arestas_de_corte << "\n";
    else
    std::cout << "\n\nSolucao final (SF):\nArestas de corte: " << arestas_de_corte << "\n";

}

void busca_local (std::vector<int>& solucao, const std::vector< std::vector<int> >& vertices)
{
 unsigned int grupo_selecionado = GRUPO_A;


 for (unsigned int i = 0; i < solucao.size(); i++)
 {
      int arestas_no_subgrafo = 0;
      int arestas_no_subgrafo_complementar = 0;
     if (grupo_selecionado == 1 && solucao[i] == GRUPO_B)
     {
         for (unsigned int j = 0; j < vertices[i].size(); j++)
         {
             if (solucao[vertices[i][j]] == GRUPO_B)
                arestas_no_subgrafo++;
             else
                arestas_no_subgrafo_complementar++;
         }
         if (arestas_no_subgrafo - arestas_no_subgrafo_complementar < 0)
         {
             solucao[i] = GRUPO_A;
             grupo_selecionado = 1 - grupo_selecionado;
         }
     }
     else if (grupo_selecionado == 0 && solucao[i] == GRUPO_A)
     {
         for (unsigned int j = 0; j < vertices[i].size(); j++)
         {
             if (solucao[vertices[i][j]] == GRUPO_A)
                arestas_no_subgrafo++;
             else
                arestas_no_subgrafo_complementar++;
         }
         if (arestas_no_subgrafo - arestas_no_subgrafo_complementar < 0)
         {
             solucao[i] = GRUPO_B;
             grupo_selecionado = 1 - grupo_selecionado;
         }
     }
 }
}
