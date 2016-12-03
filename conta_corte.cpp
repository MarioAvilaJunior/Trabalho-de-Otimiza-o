unsigned int conta_corte(void) {

    std::vector<unsigned int> solucao;
    unsigned int arestas_de_corte = 0;

    for (int i = 0; i < A.size(); i++) {
        solucao[A[i]] = 0;
    }
    for (int i = 0; i < B.size(); i++) {
        solucao[B[i]] = 1;
    }

    for (int i = 0; i < solucao.size(); i++) {
        if (solucao[i] == 0) {
            for (int j = 0; j < vertices[i].size(); j++) {
                if (solucao[vertices[i][j]] == 1) {
                    arestas_de_corte++;
                }
            }
        }
    }

    return arestas_de_corte;
}
