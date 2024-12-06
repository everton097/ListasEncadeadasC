#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct para armazenar os personagens
typedef struct Personagem {
    char nome[50];
    int ano_nasc;
    struct Personagem *prox;
} Personagem;

// Struct para armazenar os animes
typedef struct Anime {
    char titulo[50];
    int ano;
    char autor[50];
    Personagem *personagens; // Lista encadeada de personagens associados ao anime
    struct Anime *prox;
} Anime;

// Funcao para criar um novo personagem
Personagem* criarPersonagem(char nome[], int ano_nasc) {
    Personagem *novoPersonagem = (Personagem*)malloc(sizeof(Personagem));
    strcpy(novoPersonagem->nome, nome);
    novoPersonagem->ano_nasc = ano_nasc;
    novoPersonagem->prox = NULL;
    return novoPersonagem;
}

// Funcao para adicionar um personagem na lista de personagens
void adicionarPersonagem(Personagem **listaPersonagens, char nome[], int ano_nasc) {
    Personagem *novo = criarPersonagem(nome, ano_nasc);
    novo->prox = *listaPersonagens;
    *listaPersonagens = novo;
}

// Funcao para criar um novo anime
Anime* criarAnime(char titulo[], int ano, char autor[]) {
    Anime *novoAnime = (Anime*)malloc(sizeof(Anime));
    strcpy(novoAnime->titulo, titulo);
    novoAnime->ano = ano;
    strcpy(novoAnime->autor, autor);
    novoAnime->personagens = NULL;
    novoAnime->prox = NULL;
    return novoAnime;
}

// Funcao para adicionar um anime na lista de animes
void adicionarAnime(Anime **listaAnimes, char titulo[], int ano, char autor[]) {
    Anime *novo = criarAnime(titulo, ano, autor);
    novo->prox = *listaAnimes;
    *listaAnimes = novo;
}

// Funcao para listar todos os animes com IDs
void listarAnimesComID(Anime *listaAnimes) {
    Anime *atual = listaAnimes;
    int id = 0;
    while (atual != NULL) {
        printf("%d - %s\n", id, atual->titulo);
        atual = atual->prox;
        id++;
    }
}

// Funcao para buscar um anime pelo ID
Anime* buscarAnimePorID(Anime *listaAnimes, int id) {
    Anime *atual = listaAnimes;
    int contador = 0;
    while (atual != NULL) {
        if (contador == id) {
            return atual;
        }
        atual = atual->prox;
        contador++;
    }
    return NULL; // Retorna NULL caso o ID nao exista
}

// Funcao para listar todos os animes
void listarAnimes(Anime *listaAnimes) {
    Anime *atual = listaAnimes;
    if (atual == NULL) {
        printf("Nao ha animes cadastrados.\n");
        return;
    }
    while (atual != NULL) {
        printf("Anime: %s\nAno: %d\nAutor: %s\n", atual->titulo, atual->ano, atual->autor);
        Personagem *p = atual->personagens;
        printf("Personagens:\n");
        while (p != NULL) {
            printf(" - Nome: %s, Ano de Nascimento: %d\n", p->nome, p->ano_nasc);
            p = p->prox;
        }
        atual = atual->prox;
        printf("\n");
    }
}

// Funcao corrigida para listar todos os personagens, agrupados por anime
void listarTodosPersonagens(Anime *listaAnimes) {
    Anime *atualAnime = listaAnimes;
    if (atualAnime == NULL) {
        printf("Nao ha animes cadastrados.\n");
        return;
    }
    while (atualAnime != NULL) {
        printf("Anime: %s\n", atualAnime->titulo);
        Personagem *atualPersonagem = atualAnime->personagens;
        if (atualPersonagem == NULL) {
            printf("  Nenhum personagem associado.\n");
        }
        while (atualPersonagem != NULL) {
            printf("  - Nome: %s, Ano de Nascimento: %d\n", atualPersonagem->nome, atualPersonagem->ano_nasc);
            atualPersonagem = atualPersonagem->prox;
        }
        atualAnime = atualAnime->prox;
    }
}

// Funcao para editar anime
void editarAnime(Anime *listaAnimes) {
    Anime *listaAtualAnime = listaAnimes;
    if (listaAtualAnime == NULL) {
        printf("Nao ha animes cadastrados.\n");
        return;
    }
    printf("Escolha o ID do anime a ser editado:\n");
    listarAnimesComID(listaAnimes);
    int id;
    scanf("%d", &id);

    Anime *anime = buscarAnimePorID(listaAnimes, id);
    if (anime == NULL) {
        printf("ID do anime invalido.\n");
        return;
    }

    printf("Digite o novo titulo (ou deixe vazio para manter): ");
    char novoTitulo[50];
    scanf(" %[^\n]", novoTitulo);
    if (strlen(novoTitulo) > 0) {
        strcpy(anime->titulo, novoTitulo);
    }

    printf("Digite o novo ano (ou 0 para manter): ");
    int novoAno;
    scanf("%d", &novoAno);
    if (novoAno > 0) {
        anime->ano = novoAno;
    }

    printf("Digite o novo autor (ou deixe vazio para manter): ");
    char novoAutor[50];
    scanf(" %[^\n]", novoAutor);
    if (strlen(novoAutor) > 0) {
        strcpy(anime->autor, novoAutor);
    }

    printf("Anime editado com sucesso!\n");
}

// Funcao para excluir um anime
void excluirAnime(Anime **listaAnimes) {
    printf("Escolha o ID do anime a ser excluido:\n");
    listarAnimesComID(*listaAnimes);
    int id;
    scanf("%d", &id);

    Anime *atual = *listaAnimes, *anterior = NULL;
    int contador = 0;

    while (atual != NULL && contador != id) {
        anterior = atual;
        atual = atual->prox;
        contador++;
    }

    if (atual == NULL) {
        printf("ID do anime invalido.\n");
        return;
    }

    if (anterior == NULL) {
        *listaAnimes = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    // Liberar a memoria dos personagens associados
    Personagem *p = atual->personagens;
    while (p != NULL) {
        Personagem *temp = p;
        p = p->prox;
        free(temp);
    }
    free(atual);

    printf("Anime excluido com sucesso!\n");
}

// Funcao para editar personagem
void editarPersonagem(Anime *listaAnimes) {
  Anime *atual = listaAnimes;
    if (atual == NULL) {
        printf("Nao ha animes cadastrados.\n");
        return;
    }
    printf("Escolha o ID do anime que possui o personagem:\n");
    listarAnimesComID(listaAnimes);
    int idAnime;
    scanf("%d", &idAnime);

    Anime *anime = buscarAnimePorID(listaAnimes, idAnime);
    if (anime == NULL) {
        printf("ID do anime invalido.\n");
        return;
    }

    printf("Personagens do anime '%s':\n", anime->titulo);
    Personagem *personagem = anime->personagens;
    int id = 0;

    while (personagem != NULL) {
        printf("%d - Nome: %s, Ano: %d\n", id, personagem->nome, personagem->ano_nasc);
        personagem = personagem->prox;
        id++;
    }

    printf("Escolha o ID do personagem a ser editado: ");
    int idPersonagem;
    scanf("%d", &idPersonagem);

    personagem = anime->personagens;
    id = 0;
    while (personagem != NULL && id != idPersonagem) {
        personagem = personagem->prox;
        id++;
    }

    if (personagem == NULL) {
        printf("ID do personagem invalido.\n");
        return;
    }

    printf("Digite o novo nome (ou deixe vazio para manter): ");
    char novoNome[50];
    scanf(" %[^\n]", novoNome);
    if (strlen(novoNome) > 0) {
        strcpy(personagem->nome, novoNome);
    }

    printf("Digite o novo ano de nascimento (ou 0 para manter): ");
    int novoAno;
    scanf("%d", &novoAno);
    if (novoAno > 0) {
        personagem->ano_nasc = novoAno;
    }

    printf("Personagem editado com sucesso!\n");
}

// Menu principal
int main() {
    Anime *listaAnimes = NULL;

    int opcao;
    do {
        printf("\nMenu Principal:\n");
        printf("1 - Inserir Anime\n");
        printf("2 - Inserir Personagem\n");
        printf("3 - Editar Anime\n");
        printf("4 - Excluir Anime\n");
        printf("5 - Editar Personagem\n");
        printf("6 - Listar Animes\n");
        printf("7 - Listar Personagens\n");
        printf("8 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        char titulo[50], nome[50], autor[50];
        int ano, ano_nasc;

        switch (opcao) {
            case 1:
                printf("Digite o titulo do anime: ");
                scanf(" %[^\n]", titulo);
                printf("Digite o ano do anime: ");
                scanf("%d", &ano);
                printf("Digite o autor do anime: ");
                scanf(" %[^\n]", autor);
                adicionarAnime(&listaAnimes, titulo, ano, autor);
                printf("Anime cadastrado com sucesso!\n");
                break;

            case 2:
                if (listaAnimes == NULL) {
                    printf("Nao ha animes cadastrados. Cadastre um anime primeiro.\n");
                    break;
                }
                printf("Escolha o ID do anime para associar o personagem:\n");
                listarAnimesComID(listaAnimes);
                int idAnime;
                scanf("%d", &idAnime);

                Anime *animeSelecionado = buscarAnimePorID(listaAnimes, idAnime);
                if (animeSelecionado == NULL) {
                    printf("ID do anime invalido.\n");
                    break;
                }

                printf("Digite o nome do personagem: ");
                scanf(" %[^\n]", nome);
                printf("Digite o ano de nascimento do personagem: ");
                scanf("%d", &ano_nasc);

                adicionarPersonagem(&animeSelecionado->personagens, nome, ano_nasc);
                printf("Personagem '%s' cadastrado e associado ao anime '%s' com sucesso!\n", nome, animeSelecionado->titulo);
                break;

            case 3:
                editarAnime(listaAnimes);
                break;

            case 4:
                excluirAnime(&listaAnimes);
                break;

            case 5:
                editarPersonagem(listaAnimes);
                break;

            case 6:
                listarAnimes(listaAnimes);
                break;

            case 7:
                listarTodosPersonagens(listaAnimes);
                break;

            case 8:
                printf("Encerrando o programa.\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 8);

    return 0;
}
