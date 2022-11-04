#define ledRed 12
#define ledYellow 8
#define ledGreen 6
#define ledBlue 4
#define button1 2
#define button2 40
#define buzzer 36
#define ldr 15

void setup() {
  // Definindo estados dos componentes
  Serial.begin(115200);
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);

}

// Vetor que guarda as portas do leds
int vetorLeds[4] = {ledRed, ledYellow, ledGreen, ledBlue};

// Vetor que guarda os valores máximos de cada intervalo da faixa de 0 a 15
int vetorValoresLdr[16] = {256, 512, 768, 1024, 1280, 1536, 1792, 2048, 2304, 2560, 2816, 3072, 3328, 3584, 4095};

// Contador de cliques do botão
int qtdCliques = 0;

// Quantidade máxima para se guardar os números binários armazenados pelo botão 
int vetorBinarios[500];

// Quantidade máxima para se guardar os números de zero a quinze armazenados pelo botão 
int vetorZeroAQuinze[500];

// Contador para auxiliar no manejo do vetor de binários
int qtdNoVetorBinarios = 0;

// Função responsável por converter os valores do ldr do momento para valores de zero a quinze
int conversorLdr(int valorLdr) {
// Se o valor atual do ldr for menor ou igual ao intervalo de números correspondente a posição "0" do vetor
// de valores então irá retornar 0
  if (valorLdr <= vetorValoresLdr[0]) {
    return 0;
  } else {
// Loop que compara o valor atual do ldr a partir do intervalo "1" do vetor de valores do ldr
    for (int i = 0; i < 15; i++) {
      if (valorLdr > vetorValoresLdr[i] && valorLdr <= vetorValoresLdr[i + 1]) {
        return i + 1;
      }
    }
  }
}

// Função responsável por converter número de base decimal para a base binária
// E também dar o número binário correspondente com a posição passada no argumento
// Posição que corresponde poder pegar algum número da contagem de quatro binários 
int conversorBinario(int numero, int posicao) {
// Variável que irá auxiliar na divisão por dois do número passado como argumento na função
  int armazenaValor = numero;
  int vetorResultado[4];
  for (int i = 3; i >= 0; i--) {
    vetorResultado[i] = armazenaValor%2;
    armazenaValor = armazenaValor/2;
  }
// Retorno de algum número da contagem binária de quatro digitos dependendo da posição passada como argumento
  return vetorResultado[posicao];
}

// Função que contém o objetivo de acender o led dependendo de qual porta de led foi passada como argumento
// O argumento "numero" corresponde se o led deve permanecer ligado ou desligado
void acendeLed(int led, int numero) {
  if (numero == 0) {
    digitalWrite(vetorLeds[led], LOW);
  } else {
    digitalWrite(vetorLeds[led], HIGH);
  }
}



void loop() {
  if (digitalRead(button1) == LOW) {

// Se o botão 1 for clicado ele irá armazenar mais um valor no contador de quantidade de cliques
     qtdCliques = qtdCliques + 1;
    for (int i = 0; i < 4; i++) {

// Armazena um valor a mais na variável "qtdNoVetorBinarios" para saber futuramente a quantidade de itens que terão no vetor de binários
      qtdNoVetorBinarios = qtdNoVetorBinarios + 1;
// Acende o led correspondente ao valor atual do ldr
      acendeLed(i, conversorBinario(conversorLdr(analogRead(ldr)), i));
// Guarda no "vetorBinarios" todos os valores da contagem binária de quatro digitos convertidos no momento
      vetorBinarios[qtdNoVetorBinarios - 1] = conversorBinario(conversorLdr(analogRead(ldr)), i);
    }

// Guarda no " vetorZeroAQuinze" o valor atual do ldr convertido para algum número entre 0 a 15
// com o objetivo de auxiliar na frequência do buzzer
    vetorZeroAQuinze[qtdCliques - 1] = conversorLdr(analogRead(ldr));
    tone(buzzer, vetorZeroAQuinze[qtdCliques - 1]*100, 200);
    while (digitalRead(button1) == LOW) {
    }
  }
  if (digitalRead(button2) == LOW) {

// Loop que passa por cada número do "vetorZeroAQuinze"
// a partir desse número da para saber que valores binários passar para o led e acendê-lo
    for (int i = 0; i < qtdCliques; i++) {
      for (int j = 0; j < 4; j++) {
        acendeLed(j, conversorBinario(vetorZeroAQuinze[i], j));
      }
      tone(buzzer, vetorZeroAQuinze[i]*100, 300);
      delay(600);
// Zera todos os valores do vetor de todas as posições preenchidas anteriormente
      vetorZeroAQuinze[i] = 0;
    }
    for (int i = 0; i < qtdNoVetorBinarios; i++) {
      vetorBinarios[i] = 0;
    }
// Zera a quantidade de cliques no botão e também zera o contador de itens do vetor de binários
    qtdCliques = 0;
    qtdNoVetorBinarios = 0;
    while (digitalRead(button2) == LOW) {
    }
  }
}
