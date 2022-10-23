#include <iostream>
#include <string>

using namespace std;

// Array para ser usado futuramente para saber o lado da maior distância
char *direcoes[4] = {(char*) "Direita",(char*) "Esquerda",(char*) "Frente",(char*) "Trás"};


// Funcao 1 
// Pega os parametros, e por meio desses, ajusta o valor
// O valor é retornado 
int funcaoAjusta (int medida, int minimo, int maximo) {
    int valor = medida - minimo;
    int delta = maximo - minimo;
    int resultado = valor/ delta;

    return resultado;
}

// Funcao 2
// Pede um valor para o usuário
// Retorna esse valor
int input (char direcao) {
    cout << "Digite o valor:" << direcao;
    int valorInput;
    cin >> valorInput;

    return valorInput;

}

// Funcao 4
// Compara cada valor e retorna a maior distância em conjunto com o lado
char* direcaoMaiorCaminho(int *vetor, int *maiorDirecao) {
    int maiorDistancia = vetor[0];
    int indice;

    for (int i =0; i <4; i++) {
        if (vetor[i] > maiorDistancia) {
            maiorDistancia = vetor[i];
            indice = i;
        }
    }

    *maiorDirecao = maiorDistancia;
    return direcoes[indice];
}

// Funcao 3
// Auxilia no armazenamento dos valores das direções 
int armazenaValorVetor(int medida, int *vetor, int lenMaximoVetor, int posicaoAtual) {
    if (posicaoAtual > lenMaximoVetor) {
        cout << "Posição inválida";
    } else {
        vetor[posicaoAtual] = medida; 
    }
    return posicaoAtual + 1;
}

//Funcao 5
//Pergunta ao usuário se ele deseja continuar
// Caso sim, a pergunta é feita denovo, senão acabou o mapeamento
int perguntaDirecaoUsuario() {
    char resposta;
    cout << "Deseja Continuar? (s/n)";
    cin >> resposta;

    if (resposta == 's') {
        return 1;
    } else {

        return 0;
    }
}

int dirige(int *v,int maxv){
	int maxVetor = maxv;
	int *vetorMov = v;
	int posicaoAtualVetor = 0;
	int dirigindo = 1;		
	while(dirigindo){
    // Etapa 6
    // Acontece um loop para o mapeamento 
        for (int i = 0;i < 4; i++) {
            int medida = input(*direcoes[i]);
            medida = funcaoAjusta(medida,0,830);
            posicaoAtualVetor = armazenaValorVetor(medida, vetorMov, maxVetor, posicaoAtualVetor);
        }
		dirigindo = perguntaDirecaoUsuario();		
	}
	return posicaoAtualVetor;
}

void percorre(int *v,int tamPercorrido){		
	int *vetorMov = v;
	int maiorDir = 0;
	
	for(int i = 0; i< tamPercorrido; i+=4){
		char *direcao = direcaoMaiorCaminho(&(vetorMov[i]),&maiorDir);
		printf("Movimentando para %s distancia = %i\n",direcao,maiorDir);
	}
}

int main(int argc, char** argv) {
	int maxVetor = 100;
	int vetorMov[maxVetor*4];
	int posicaoAtualVet = 0;
	
	posicaoAtualVet = dirige(vetorMov,maxVetor);
	percorre(vetorMov,posicaoAtualVet);
	
	return 0;
}