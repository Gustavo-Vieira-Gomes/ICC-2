# Palindromo - Atividade 1

## Problema

O objetivo da atividade é receber uma série de linhas, até EOF, e verificar se cada linha é ou não um palíndromo. As linhas de entrada podem conter uma palavra, uma frase, e caracteres alfanuméricos ou não-alfanuméricos.
Três soluções deviam ser criadas: Uma recursiva feita por nós, uma recursiva feita pela IA e uma iterativa feita por nós.

### Comparação entre versão Iterativa feita por nós x feita pela IA

#### Entrada de dados

Enquanto nós alocamos uma quantidade inicial de memória, definindo um tamanho limite para as strings, e fizemos a leitura da linha por completo, usando o fgets. Já a IA criou uma função auxiliar para ler uma linha, a qual leu char a char, alocando memória de forma dinâmica (Dobrando a memória alocada quando necessário.)
Além disso, a IA protegeu suas funções de uso externo utilizando static.

```c
// Nossa versão
char *palavra;
    palavra = (char *)malloc(1000 * sizeof(char));

    // Lê uma linha de qualquer tamanho (sem o '\n'). Retorna NULL no EOF sem dados.
    while (fgets(palavra, 999, stdin) != NULL) {...}
```

```c
// versão IA
static char *read_line(void) {
    int c;
    size_t cap = 128, len = 0;
    char *buf = malloc(cap);
    if (!buf) return NULL;

    while ((c = getchar()) != EOF) {
        if (c == '\r') continue;          /* ignora CR (Windows) */
        if (c == '\n') break;             /* fim da linha */
        if (len + 1 >= cap) {
            cap *= 2;
            char *tmp = realloc(buf, cap);
            if (!tmp) { free(buf); return NULL; }
            buf = tmp;
        }
        buf[len++] = (char)c;
    }

    if (c == EOF && len == 0) {           /* EOF sem dados */
        free(buf);
        return NULL;
    }

    buf[len] = '\0';
    return buf;
}
```

#### Limpeza das string e Análise

Na nossa versão, criamos funções auxiliares que realizam a limpeza e preparação da string para análise. Após limpa, comparamos o primeiro e o último caracter, caso sejam diferentes retorna falso, caso contrário, analisa o segundo e o penúlitimo, e assim por diante até que a posição que partiu do começo seja igual ou maior que a posição que saiu do final da string.
Já na versão da IA, ela não fez uma limpeza prévia da string, ela apenas desconsidera os caracteres não alfanuméricos na hora da análise e converte para minúsculo logo antes de comparar no início e fim da substring considerada.

```c
// Nossa versão
bool isPalindromo(char **palavra) {
    // Recebe um ponteiro para um ponteiro de char, e percorre-o comparando o primeiro
    // e o último caractere, se aproximando do centro de ambos os lados
    int start = 0;
    int end = strlen(*palavra) - 1;

    while (start < end) {
        if ((*palavra)[start] == (*palavra)[end]) {
            start++;
            end--;
        } else {
            return false;
        }
    }
    return true;
}

void removeNonAlphaNumeric(char **palavra) {
    // Recebe um ponteiro para um ponteiro de char, e percorre-o removendo caracteres não alfanuméricos
    int i = 0;
    int j = 0;
    while ((*palavra)[i] != '\0') {
        if (isalnum((*palavra)[i])) {
            (*palavra)[j++] = (*palavra)[i];
        }
        i++;
    }
    (*palavra)[j] = '\0';
}

void toUpper(char **palavra) {
    // Recebe um ponteiro para um ponteiro de char, e percorre-o
    // convertendo caracteres minúsculos para maiúsculos
    int i = 0;
    while ((*palavra)[i] != '\0') {
        if ((*palavra)[i] >= 'a' && (*palavra)[i] <= 'z') {
            (*palavra)[i] = (*palavra)[i] - 'a' + 'A';
        }
        i++;
    }
}
```

```c
//Versão IA
static int is_palindrome(const char *s) {
    size_t i = 0, j = strlen(s);
    if (j == 0) return 1;
    j--;

    while (i < j) {
        while (i < j && !isalnum((unsigned char)s[i])) i++;
        while (i < j && !isalnum((unsigned char)s[j])) j--;
        if (i >= j) break;

        unsigned char a = (unsigned char)s[i];
        unsigned char b = (unsigned char)s[j];
        a = (unsigned char)tolower(a);
        b = (unsigned char)tolower(b);

        if (a != b) return 0;
        i++; j--;
    }
    return 1;
}
```

### Qual versão é a mais eficiente e por quê?

#### Recursiva x Iterativa

A implementação iterativa é mais eficiente do que a recursiva pois a segunda exige a chamada de múltiplas funções simultaneamente na stack, ocupando
mais espaço de memória. Por outro lado, a implementação iterativa utiliza um único laço while, que não exige muito espaço na stack pois não cria variáveis ou funções novas a cada
repetição. Quanto ao tempo de execução, a iterativa sobressai novamente, uma vez que exige uma quantidade menor de chamadas de funções, operações relativamente lentas. Além disso
não existe difrença entre os códigos, já que utilizam as mesmas funções de retirada de caracteres alphanuméricos e de transformação em maiúsculos.

#### Iterativa x Iterativa IA

A IA sobressaiu no quesito eficiência devido a uma implementação extremamente enxuta de limpeza da string. Enquanto nós criamos duas funções que
percorrem a string para limpá-la (toUpper e removeNonAplhaNumeric) e mais uma que a percorre para verificar se é ou não palíndromo, a IA fez tudo isso em uma única função, percor-
rendo a string apenas uma vez. Isto reduz a complexidade do código de O(3n) para O(n) (não muito significativo pois ambos são lineares), impactando principalmente no tempo de execu-
ção do código. Há, em contrapartida, um desvantagem da IA no âmbito da eficiência devido ao uso da função realloc(), operação muito custosa em memória, porém que não a compromete
gravemente.

### Qual é o mais simples?

Analisando a simplicidade a partir da facilidade de compreensão e organização de código, acreditamos que o mais simples é a nossa versão iterativa, pois está mais modularizada e a lógica para verificar se é palíndromo ou não é concisa. Em sequência, acreditamos que a nossa versão recursiva e por último, menos simples e de maior dificuldade de compreensão, a versão da iterativa da IA.
Em contrapartida, analisando a quantidade de recursos criados, o código da IA foi mais simples por resolver a questão em menos funções, de forma mais direta ao ponto.

### O que a IA considerou que nós não consideramos

O código feito da IA leva em conta alguns detalhes que nós não lidamos:

- A IA lê char a char, alocando memória dinâmicamente evitando reservar uma quantia excessiva de memória, enquanto nós alocamos uma quantidade que pode estar em excesso.
- A IA "protegeu" as funções criadas por ela de uso externo ao arquivo declarando-as como static _funcao_.
