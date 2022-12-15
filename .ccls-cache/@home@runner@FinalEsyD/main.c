#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
void merge_sort_paginated(int *arr, int n, int page_size) {
    // Divide the array into subarrays of size "page_size"
    int num_subarrays = n / page_size;
    int **subarrays = malloc(num_subarrays * sizeof(int *));
    for (int i = 0; i < num_subarrays; i++) {
        subarrays[i] = arr + i * page_size;
    }

    // Sort each subarray using merge sort
    for (int i = 0; i < num_subarrays; i++) {
        merge_sort(subarrays[i], page_size);
    }

    // Merge the sorted subarrays back together to form a single, sorted array
    int *temp = malloc(n * sizeof(int));
    merge(arr, temp, subarrays, num_subarrays, page_size);
    free(temp);
    free(subarrays);
}
*/

struct generos {
  int id_gen;
  char gen[50];
} est;

struct artistas {
  int id_art;
  char art[50];
} est_art;

struct canciones {
  int id_cancion;
  char can[60];
  int duracion;
  int reproducciones;
  int puntuacion;
  int r_gen;
  int r_art;
} est_can;

struct elementosDeLaLista {
  struct canciones cancion;
  struct artistas artista;
  struct generos genero;
  struct elementosDeLaLista *sig;
};

struct colaReproduccion {
  struct canciones cancion;
  struct artistas artista;
  struct colaReproduccion *sig;
  struct colaReproduccion *ant;
};

int elementoACola(struct colaReproduccion **cola, struct canciones cancion);
int vaciarLista(struct elementosDeLaLista **lista);

void impresion(struct elementosDeLaLista *inicio) {
  struct elementosDeLaLista *temp;
  temp = inicio;
  while (temp) {
    printf("#%d\n", temp->cancion.id_cancion);
    printf("< %s >\n", temp->cancion.can);
    printf("- %s -\n", temp->artista.art);
    printf("\n");
    temp = temp->sig;
  }
}

/*
void buscarcoincidencia(struct elementosDeLaLista *inicio)
FILE *fp= fopen"Registro.txt","r";
if (fp == NULL) {
fprint (stderr, "ERROR AL ABRIR ARCHIVO\n");
return 1;
}

char line[256];
while (fgets(line,sizeof(line),fp)){
char *match = strstr(line, "EJEMPLO");

if (match){
printf("%s",line);
}
}
fcloset(fp);
returt 0;
*/
int insertarLista(struct elementosDeLaLista **lista, struct canciones cancion) {
  struct elementosDeLaLista *temp, *ultimo;
  if ((*lista) == NULL) {
    temp = (struct elementosDeLaLista *)calloc(
        1, sizeof(struct elementosDeLaLista));
    temp->cancion = cancion;
    *lista = temp;
    return 1;
  } else {
    ultimo = (*lista);
    while (ultimo->sig != NULL) {
      ultimo = ultimo->sig;
    }
    temp = (struct elementosDeLaLista *)calloc(
        1, sizeof(struct elementosDeLaLista));
    temp->cancion = cancion;
    ultimo->sig = temp;
    return 1;
  }
}

int insertarArtistas(struct elementosDeLaLista *inicio) {
  if (!inicio) {
    return 0;
  }
  inicio->cancion.r_art;

  FILE *ptr;
  ptr = fopen("Registroart.txt", "ab+");
  if (ptr == NULL) {
    return 0;
  }

  while (!feof(ptr)) {
    fread(&est_art, sizeof(est_art), 1, ptr);

    if (inicio->cancion.r_art == est_art.id_art) {
      inicio->artista = est_art;
    }
  }
  if (inicio->sig != NULL) {
    insertarArtistas(inicio->sig);
  }
}
// lista ligada o cola?^^^^
int limpiarCola(struct colaReproduccion **cola) {
  struct colaReproduccion *ultimo, *temp;
  if ((*cola) == NULL) {
    return 0;
  } else {
    ultimo = (*cola);
    while (ultimo->sig != NULL) {
      temp = ultimo;
      ultimo = ultimo->sig;
      free(temp);
    }
    free(ultimo);
    (*cola) = NULL;
  }
  return 1;
}

int agregarListaACola(struct colaReproduccion *cola,
                      struct elementosDeLaLista *lista, bool reproducir) {
  if (reproducir) {
    // Aqui se tiene que limpiar la cola
    limpiarCola(&cola->sig);
  }
  // Agregar a la estructura cola todo lo que hay en lista
  struct colaReproduccion *temp;
  if (cola->sig == NULL) {
    temp =
        (struct colaReproduccion *)calloc(1, sizeof(struct colaReproduccion));
    cola->sig = temp;
    temp->cancion = lista->cancion;
    temp->artista = lista->artista;
    temp->ant = cola;
    if (lista->sig != NULL) {
      agregarListaACola(cola->sig, lista->sig, reproducir);
    }
    return 1;
  } else {
    agregarListaACola(cola->sig, lista, reproducir);
  }
}
////////////////////////////////////////////////////////////////////////////////////////////
int agregarCancionACola(struct colaReproduccion **cola,
                        struct elementosDeLaLista *lista, bool reproducir,
                        int ID_Cancion) {
  struct elementosDeLaLista *tempElemLista;
  struct colaReproduccion *tempCola, *temp2;
  int test;
  if (reproducir) {
    // Aqui se tiene que limpiar la cola
    limpiarCola(&(*cola)->sig);
  }
  // Agregar a la estructura cola todo lo que hay en lista
  struct colaReproduccion *temp;
  tempElemLista = lista;
  while (tempElemLista) {
    if (tempElemLista->cancion.id_cancion == ID_Cancion) {
      temp =
          (struct colaReproduccion *)calloc(1, sizeof(struct colaReproduccion));
      if (*cola == NULL) {
        temp->cancion = tempElemLista->cancion;
        temp->artista = tempElemLista->artista;
        *cola = temp;
        return 0;
      } else {
        temp2 = (*cola);
        while (temp2->sig != NULL) {
          temp2 = temp2->sig;
        }
      }
      temp2->sig = temp;
      //(*cola) -> sig = temp;
      temp->cancion = tempElemLista->cancion;
      temp->artista = tempElemLista->artista;
      temp->ant = temp2;
      return 1;
    } else {
      tempElemLista = tempElemLista->sig;
    }
  }
}

void estadoDeCola(struct colaReproduccion *inicioCola) {
  struct colaReproduccion *temp;
  temp = inicioCola;
  while (temp) {
    printf("< %s >\n", temp->cancion.can);
    printf("- %s -\n", temp->artista.art);
    printf("\n");
    temp = temp->sig;
  }
  int x;
  scanf("%i", &x);
}
void agregarAReproductor(struct colaReproduccion **reproductor,
                         struct colaReproduccion *inicioCola) {
  *reproductor = inicioCola;
}
void mostrarReproductor(struct colaReproduccion *reproductor) {

  printf("< %s >\n", reproductor->cancion.can);
  printf("- %s -\n", reproductor->artista.art);
  printf("\n");
}
// Funcion auxiliar que deja completamente vacia y elimina todos los elementos
// de una lista
int vaciarLista(struct elementosDeLaLista **lista) {
  struct elementosDeLaLista *ultimo, *temp;
  if ((*lista) == NULL) {
    return 0;
  } else {
    ultimo = (*lista);
    while (ultimo->sig != NULL) {
      temp = ultimo;
      ultimo = ultimo->sig;
      free(temp);
    }
    free(ultimo);
    (*lista) = NULL;
  }
  return 1;
}

//////////////////////////////////////////////////////////////////////////////////
int main() {
  struct elementosDeLaLista *lista;
  struct canciones *cancion;
  struct elementosDeLaLista *listaTemporal = NULL;
  struct colaReproduccion *cola;
  struct colaReproduccion *reproductor = NULL;
  int opcionReproductorint;
  bool modoRepetir = false;

  // listaTemporal  = (struct elementosDeLaLista *) calloc(1,
  // sizeof(*listaTemporal));

  FILE *ptr;
  FILE *ptr2;
  FILE *ptr3;

  lista = (struct elementosDeLaLista *)calloc(1, sizeof(*lista));
  cancion = (struct canciones *)calloc(1, sizeof(*cancion));
  cola = (struct colaReproduccion *)calloc(1, sizeof(*cola));

  // strcpy(cancion->can, "Test");
  // insertarLista(lista, *cancion);
  // impresion(lista);
  int opcionSwitch, opcionGeneros;
  char opcionGeneros2, opcionCanciones, opcionReproductor;

  // poner do while para menu para quitar mains
  while (opcionSwitch != 4) {
    opcionSwitch = 0;
    system("clear");
    printf("Bienvenido a SpotiUV\n");
    printf("---------------------\n");
    printf("1.  Explorar Generos\n");
    printf("2.  Explorar Canciones\n");
    printf("3.  Reproductor\n");
    printf("4.  Salir\n");
    printf("5.  Cola de reproduccion\n");
    printf("6.  Buscar canciones a partir de una frase\n\n");
    printf("Selecciona una opcion: ");
    fflush(stdin);
    fflush(stdout);
    scanf("%i", &opcionSwitch);
    switch (opcionSwitch) {
    case 1: {
      system("clear");
      // printf("\nVER DATOS\n");
      ptr = fopen("Registrogen.txt", "ab+");
      if (ptr == NULL) {
        printf("Error al abrir el archivo\n");
        main();
        break;
      }

      printf("\n ID	     |GENERO\n");
      printf("----------------------\n");
      while (fread(&est, sizeof(est), 1, ptr))

      {
        printf(" %d.       | %s\n", est.id_gen, est.gen);
      }
      fclose(ptr);
      int opmengen;
      printf("\n------------------------------");
      printf("\n1.Seleccionar un genero.");
      printf("\n2.Regresar al menu principal.");
      printf("\n------------------------------");
      printf("\n\nIntroduzca una opcion (1-2): ");
      scanf("%d", &opmengen);

      switch (opmengen) {
      case 1: {
        ptr = fopen("Registrogen.txt", "rb+");
        if (ptr == NULL)
          return 0;
        int opgen;
        printf("\nSeleccione un genero: ");
        scanf("%d", &opgen);

        while (!feof(ptr)) {
          fread(&est, sizeof(est), 1, ptr);
          if (est.id_gen == opgen) {
            // MOSTRAR CANCIONES CON ARTISTA
            ptr2 = fopen("Registrocan.txt", "ab+");
            if (ptr2 == NULL) {
              printf("Error al abrir el archivo\n");
              main();
              break;
            }
            // listaTemporal  = (struct elementosDeLaLista *)
            // calloc(1,sizeof(*listaTemporal));
            vaciarLista(&listaTemporal);
            while (!feof(ptr2)) {
              fread(&est_can, sizeof(est_can), 1, ptr2);
              if (opgen == est_can.r_gen) {
                // printf("\n<%s>",est_can.can);
                insertarLista(&listaTemporal, est_can);
                insertarArtistas(listaTemporal);
              }
            }
            break;
          }
        }
        if (opgen != est.id_gen) {

          printf("Genero no encontrado.\n");
        }
        ////////////////
        char opc;
        while (opc != 'p') {
          system("clear");
          printf("\n----------%s----------\n\n", est.gen);
          impresion(listaTemporal);
          printf("\n--------------------------------------");
          printf("\np.  Regresar al menu principal.");
          printf("\nq.  Agregar a la cola de reproducción.");
          printf("\nr.  Reproducir toda esta lista.");
          printf("\ns.  Escoger una canción para enviarla a la cola.");
          printf("\nt.  Escoger una canción para reproducirla.");
          printf("\n--------------------------------------");
          printf("\nSeleccione una opción: ");
          scanf("%s", &opc);

          switch (opc) {
          case 'q':
            agregarListaACola(cola, listaTemporal, false);
            estadoDeCola(cola->sig);
            // vaciarLista(&listaTemporal);
            if (!reproductor) {
              agregarAReproductor(&reproductor, cola->sig);
            }
            break;
          case 'r':
            // vaciarLista(&listaTemporal);
            agregarListaACola(cola, listaTemporal, true);
            estadoDeCola(cola->sig);
            agregarAReproductor(&reproductor, cola->sig);

            break;
          case 's':
            printf("\nSeleccione una canción para enviarla a la cola: ");
            scanf("%d", &opcionReproductorint);
            agregarCancionACola(&cola, listaTemporal, false,
                                opcionReproductorint);
            if (!reproductor) {
              agregarAReproductor(&reproductor, cola->sig);
            }
            break;
          case 't':
            printf("\nSeleccione una canción para reproducirla: ");
            scanf("%d", &opcionReproductorint);
            agregarCancionACola(&cola, listaTemporal, true,
                                opcionReproductorint);
            agregarAReproductor(&reproductor, cola->sig);
            break;
          default:
            break;
          }
        }
        break;
      }
      }
      break;
    } //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    case 2: {
      printf("Lista de canciones\n");
      printf("1.<Nombre cancion>\n");
      printf("  <Nombre artista>\n");
      printf("2.<cancion>\n");
      printf("  <Nombre artista>\n");
      printf("Opciones:\n");
      printf("p: Regresar al menu principal\n");
      printf("a: 10 Canciones anteriores\n");
      printf("d: 10 Canciones siguientes \n");
      printf("q: Agregar a la cola una cancion de la lista\n");
      printf("r: Reproducir una cancion\n");
      printf("Selecciona una opcion: ");
      getchar();
      scanf("%c", &opcionCanciones);

      switch (opcionCanciones) {
      case 'p':
        break;
      case 'a':
        printf("10 Canciones anteriores...");
        break;
      case 'd':
        printf("10 Canciones siguientes...");
        break;
      case 'q':
        printf("Agregar a la cola una cancion de la lista...");
        break;
      case 'r':
        printf("Reproducir una cancion...");
        break;

      default:
        break;
      }
      break;
    } //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    case 3:
      opcionReproductor = '_';
      if (reproductor) {
        system("clear");
        while (opcionReproductor != 'p') {
          printf("Reproductor\n");
          printf("Actualmente sonando:\n");
          // printf("address of reproductor sig: %p\n", reproductor);
          // printf("address of reproductor: %p\n", &reproductor);
          // printf("address of cola siguiente: %p\n", cola->sig);
          mostrarReproductor(reproductor);
          printf("<   ||   >\n");
          printf("Opciones:\n");
          printf("p: Regresar al menu principal\n");
          printf("a: Cancion anterior\n");
          printf("d: Siguiente cancion\n");
          printf("e: Repetir cancion\n");
          if (modoRepetir == true) {
            printf("r: Desactivar Repeticion\n");
          } else {
            printf("r: Activar Repeticion\n");
          }
          printf("s: Pausar/Continuar sonando\n");
          printf("Selecciona una opcion: ");
          fflush(stdin);
          fflush(stdout);
          scanf("%c", &opcionReproductor);
          system("clear");
          switch (opcionReproductor) {
          case 'a':
            if (modoRepetir == true) {

            } else if (reproductor->ant != NULL && reproductor->ant != cola) {
              reproductor = reproductor->ant;
            }
            break;
          case 'd':
            if (modoRepetir == true) {

            } else if (reproductor->sig != NULL) {
              reproductor = reproductor->sig;
            }

            break;
          case 'e':
            printf("Repetir cancion...");
            break;
          case 'r':
            printf("Activar/desactivar Repeticion...");
            if (modoRepetir) {
              printf("Repetir cancion desactivado...");
              modoRepetir = false;
            } else {
              printf("Repetir cancion activado...");
              modoRepetir = true;
            }

            break;
          case 's':
            printf("Pausando/Continuando...");
            break;
          default:
            break;
          }
        }
      } else {
        printf("No hay canciones en el reproductor ni en cola...");
        getchar();
      }
      break;
    case 4:
      printf("Saliendo...");
      return 0;
      break;
    // case 5 sirve para probar, no borrar porfavor
    case 5:
      printf("Cola de reproduccion: \n");
      estadoDeCola(cola->sig);
      break;
    case 6:
      break;
    case 7:

    default:
      break;
    }
  }
  return 0;
}