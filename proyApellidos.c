#include <stdio.h>
#include <string.h>

#define NMax 1000 //Límite para los apellidos
#define LongMaxCad 30 //Longitud máxima para las cadenas

typedef struct{
  char a[NMax][LongMaxCad];  //Arreglo para almacenar hasta 1000 apellidos
  int cant;          //Lleva la cuenta de la cantidad de apellidos cargados
}TData;

int Vacia(TData x);  //Devuelve true si el arreglo esta vacío o false si no lo esta
int Llena(TData x);  //Devuelve true si el arreglo esta lleno o false si no lo esta
void Insertar(TData *x, char apellido[LongMaxCad]); //Inserta un apellido en el arreglo
void Suprimir(TData *x, char apellido[LongMaxCad]); //Dado un apellido, lo borra del arreglo
void MostrarApellidos(TData x); //Muestra todos los apellidos del arreglo
int Buscar(TData x, char apellido[LongMaxCad]); //Retorna el indice del apellido buscado
int Repetido(char apellido1[LongMaxCad], char apellido2[LongMaxCad]); //Retorna 1 si dos apellidos son iguales o 0 si no lo son

char apellido[LongMaxCad]; //Almacena el apellido ingresado
char apellidoMod[LongMaxCad]; //Almacena el apellido que se desea modificar
TData lista; //Arreglo para gestionar la nómina de empleados
int num; //Almacena el número ingresado
int i; //indice para controlar ciclos
int repetido; //almacena 1 si un apellido esta repetido o 0 si no lo esta

int main(){
  //Inicio:
  lista.cant = 0; //Inicializo la cantidad de la lista
  do{
    printf("\n1-Alta de empleado\n");
    printf("2-Baja de empleado\n");
    printf("3-Modificar datos de empleado\n");
    printf("4-Listar\n");
    printf("5-Buscar a un empleado\n");
    printf("6-Salir\n");
    printf("\nIngrese el número: ");
    scanf("%d", &num);
    printf("\n");

    if(num == 1){
      if(Llena(lista) == 1){
        printf("La lista ya está llena\n");
      }else{
        printf("Ingrese el nuevo apellido: ");
        scanf("%s", apellido);
        printf("\n");
        i = 0;
        repetido = 0;
        while(i < lista.cant && repetido == 0){
          if(Repetido(lista.a[i], apellido) == 1){
            repetido = 1;
          }else{
            repetido = 0;
          }
          i++;
        }
        if(repetido == 1){
          printf("El apellido ya existe en la lista\n");
        }else{
          Insertar(&lista, apellido);
        }
      }
    
    }else{
      
      if(num == 2){
        if(Vacia(lista) == 1){
          printf("La lista esta vacía\n");
        }else{
          printf("Ingrese el apellido del empleado que desea borrar: ");
          scanf("%s", apellido);
          printf("\n");
          i = 0;
          repetido = 0;
          while(i < lista.cant && repetido == 0){
            if(Repetido(lista.a[i], apellido) == 1){
              repetido = 1;
            }else{
              repetido = 0;
            }
            i++;
          }
          if(repetido == 1){
            Suprimir(&lista, apellido);
          }else{
            printf("El apellido que desea borrar no existe en la lista\n");
          }
        }
      
      }else{
        
        if(num == 3){
          if(Vacia(lista) == 1){
            printf("La lista esta vacía\n");
          }else{
            printf("Ingrese el apellido que desea modificar: ");
            scanf("%s", apellidoMod);
            printf("\n");
            i = 0;
            repetido = 0;
            while(i < lista.cant && repetido == 0){
              if(Repetido(lista.a[i], apellidoMod) == 1){
                repetido = 1;
              }else{
                repetido = 0;
              }
              i++;
            }
            if(repetido == 1){
              printf("ingrese la modificación del apellido: ");
              scanf("%s", apellido);
              printf("\n");
              strcpy(lista.a[Buscar(lista, apellidoMod)], apellido);
            }else{
              printf("El apellido que desea modificar no existe\n");
            }
          }
        
        }else{
          
          if(num == 4){
            MostrarApellidos(lista);
          }else{
            if(num == 5){
              if(Vacia(lista) == 1){
                printf("La lista esta vacía\n");
              }else{
                printf("Ingrese el apellido que desea buscar: ");
                scanf("%s", apellido);
                printf("\n");
                i = 0;
                repetido = 0;
                while(i < lista.cant && repetido == 0){
                  if(Repetido(lista.a[i], apellido) == 1){
                    repetido = 1;
                  }else{
                    repetido = 0;
                  }
                  i++;
                }
                if(repetido == 1){
                  printf("El apellido existe\n");
                }else{
                  printf("Apellido inexistente\n");
                }
              }
            
            }else{
              
              if(num == 6){
                printf("Fin del programa!\n\n");
              }else{
                if(num < 1 || num > 6){
                  printf("Número ingresado no válido!\n\n");
                }
              }
            }
          }
        }
      }
    }
  }while(num != 6);
  //Fin
  return 0;
}

int Vacia(TData x){
  //Inicio:
  if(x.cant == 0){
    return 1;
  }else{
    return 0;
  }
  //Ffunción
}

int Llena(TData x){
  //Inicio:
  if(x.cant == 1000){
    return 1;
  }else{
    return 0;
  }
  //Ffunción
}

void Insertar(TData *x, char apellido[LongMaxCad]){
  //Inicio:
  strcpy((*x).a[(*x).cant], apellido);
  (*x).cant = (*x).cant + 1;
  //Facción
}


void Suprimir(TData *x, char apellido[LongMaxCad]){
  //Léxico local:
  int i;
  int j;
  //Inicio:
  i = 0;
  while(!(strcmp((*x).a[i], apellido) == 0)){ //Busca el indice del apellido a borrar
    i++;
  }
  for(j = i; j < ((*x).cant) - 1; j++){       //Realiza desplazamiento hacía la izquierda
    strcpy((*x).a[j], (*x).a[j + 1]);
  }
  (*x).cant = (*x).cant - 1;
  //Facción
}

void MostrarApellidos(TData x){
  //Léxico local:
  int i;
  //Inicio:
   for(i = 0; i < x.cant; i++){
     printf("%s\n", x.a[i]);
   }
  //Facción
}

int Buscar(TData x, char apellido[LongMaxCad]){
  //Léxico local:
  int i;
  //Inicio:
  i = 0;
  while(!(strcmp(x.a[i], apellido) == 0)){
    i++;
  }
  return i;
  //Ffunción
}

int RepetidoDos(TData x, char apellido[LongMaxCad]){
  //Léxico local:
  int i;
  int repetido; //Variable de tipo lógico 1 = True / 0 = False
  //Inicio:
  i = 0;
  repetido = 0;
  while(i < x.cant && repetido == 0){
    if(strcmp(x.a[i], apellido) == 0){  //Compara si dos cadenas son iguales
      repetido = 1;
    }
    i++;
  }
  if(repetido == 1){
    return 1;
  }else{
    return 0;
  }
  //Ffunción
}

int Repetido(char apellido1[LongMaxCad], char apellido2[LongMaxCad]){
  //Inicio:
  if(strcmp(apellido1, apellido2) == 0){
    return 1;
  }else{
    return 0;
  }
  //Ffunción
}