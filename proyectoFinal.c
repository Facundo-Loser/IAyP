//Proyecto Final
//Integrantes: Loser Facundo Darío y Oviedo Francisco Genaro Nicolás 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  long int ddmmyyyy;
  int tmax;
  int tmin;
  int HUM;
  int PNM;
  int DV;
  int FF;
  int PP;
  int borrado;
} Tregdiario;

typedef struct{        //registro de arreglo de 366 elem de Tregdiario
    Tregdiario a[366];
    int cant;
}TData;

typedef struct nodo{  //doblete de Tregdiario
    Tregdiario info;
    struct nodo *next;
}TNodo;


//***MÓDULOS SECUNDARIOS***
int Bisiesto(int yyyy); 
int BuscarRecursiva(TData x, int cant, int fecha);
void AgregarLista(TNodo **p, Tregdiario a); 
void BubbleSort1(TData *regDs);
void BubbleSort2(TData *regDs);  
int Vacia(TData x); 
void MostrarLista(TNodo *p); 
void InsertionSort(TData *regDs); 
void MostrarXUltimos(TData regDiarios, int MaxDias); 
void MostrarXPrimeros(TData x, int MaxDias); 
void ArchAArreg(FILE *x, TData *regDs);

//***MÓDULOS PRINCIPALES*** 
void Alta(char nomExt[40], int yyyy);
void Suprimir(char nomExt[40], int yyyy);
void Modificar(char nomExt[40], int yyyy);
void Mostrar(char nomExt[40]);
void Busqueda(char nomExt[40], int yyyy);
void ListarMaxTemp(char nomExt[40]);
void ListarMaxPrec(char nomExt[40]);
void ListarVelocViento(char nomExt[40]);
void CopiaDeSeguridad(char nomExt[40]);

FILE *f;                 //Nombre interno utilizado para la apertura del archivo con el cuál trabajar
char nombreArchivo[40];  //Almacena el nombre del archivo a trabajar
int yyyyArchivo;         //Almacena el año con el cual trabaja el archivo
int opc;                 //Almacena la opción ingresada del menú
int aperturaExitosa;     //Almacena 1 si se pudo abrir un archivo existente y 0 si no se logro abrir
Tregdiario datosDia1;    //Almacena los datos de la primera fecha ingresada en un archivo

int main(){
    do{
        printf("1-Crear un nuevo archivo\n");
        printf("2-Trabajar con un archivo existente\n");
        printf("3-Salir\n");
        printf("Ingrese la opción: ");
        scanf("%d", &opc);
        printf("\n");

        if(opc == 1){
            printf("Ingrese el nombre del nuevo archivo (sin el .dat): ");
            scanf("%s", nombreArchivo);     //.dat será concatenado al nombre insertado
            strcat(nombreArchivo,".dat");
            printf("Archivo a crear: %s \n", nombreArchivo);
            printf("\n");
            printf("¿Con qué año desea utilizar este archivo?: ");
            scanf("%d", &yyyyArchivo);
            printf("\n");

            f = fopen(nombreArchivo, "wb+"); //Se crea el nuevo archivo
            fclose(f);
            printf("Archivo creado con éxito!\n");
            aperturaExitosa = 1;
        }else{
            if(opc == 2){
                aperturaExitosa = 0;
                printf("Ingrese el nombre del archivo existente (sin el .dat): ");
                scanf("%s", nombreArchivo);     //.dat será concatenado al nombre ingresado
                strcat(nombreArchivo,".dat");
                printf("Archivo a utilizar: %s \n", nombreArchivo);
                printf("\n");

                f = fopen(nombreArchivo, "rb"); 

                if(f == NULL){                                            //Si el archivo no existe
                    printf("No existe un archivo con ese nombre!\n\n");
                    fclose(f);
                }else{                                                    //Si el archivo existe
                        printf("Apertura exitosa!\n");
                        if(fread(&datosDia1, sizeof(datosDia1), 1, f) > 0){   //Si tiene registros cargados
                            yyyyArchivo = (datosDia1.ddmmyyyy % 10000);
                            printf("El archivo trabaja con datos del año: %d\n\n", yyyyArchivo);
                        }else{                                                 //Si no tiene registros cargados
                            printf("¿Con qué año desea utilizar este archivo?: ");
                            scanf("%d", &yyyyArchivo);
                            printf("\n");
                        }
                        aperturaExitosa = 1;
                        fclose(f); 
                    }    
                }else{
                    if(opc == 3){
                        printf("Fin del programa!\n");
                    }
                }
            }
    }while(aperturaExitosa != 1 && opc != 3);

    if(opc != 3){
        do{
        printf("*********************************************************************\n");    
        printf("1-Alta de un Registro\n");
        printf("2-Suprimir un registro\n");
        printf("3-Modificar un registro\n");
        printf("4-Mostrar todos los registros\n");
        printf("5-Buscar un registro\n");
        printf("6-Listar el día/días de máxima temperatura\n");
        printf("7-Listar el día/días de máxima precipitación en lo que va del año\n");
        printf("8-Listar las fechas de mayor a menor velocidad de viento\n");
        printf("9-Realizar una copia de seguridad del archivo del año en curso\n");
        printf("10-Salir\n");
        printf("Ingrese la opción: ");
        scanf("%d", &opc);
        printf("\n");
        printf("*********************************************************************\n");    

        if(opc == 1){
            Alta(nombreArchivo, yyyyArchivo);
        }else{
           if(opc == 2){
             Suprimir(nombreArchivo, yyyyArchivo);
           }else{
            if(opc == 3){
                Modificar(nombreArchivo, yyyyArchivo);
            }else{
                if(opc == 4){
                    Mostrar(nombreArchivo);
                }else{
                    if(opc == 5){
                        Busqueda(nombreArchivo, yyyyArchivo);
                    }else{
                        if(opc == 6){
                            ListarMaxTemp(nombreArchivo);
                        }else{
                            if(opc== 7){
                                ListarMaxPrec(nombreArchivo);
                            }else{
                                if(opc == 8){
                                    ListarVelocViento(nombreArchivo);
                                }else{
                                    if(opc == 9){
                                        CopiaDeSeguridad(nombreArchivo);                                          
                                    }else{
                                        if(opc == 10){
                                            printf("Fin del programa!\n");
                                        }else{
                                            if(opc < 1 || opc > 10){
                                                printf("Opción ingresada no válida!\n");
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
           }
        }
    }while(opc != 10);
    }

    return 0;
}

//***MÓDULOS SECUNDARIOS***

//Función Bisiesto: devuelve 1 cuando el año es bisiesto y 0 cuando no lo es.

int Bisiesto(int yyyy){
    if(yyyy % 4 == 0 && yyyy % 100 != 0){
        return 1;
    }else{
        if(yyyy % 100 == 0 && yyyy % 400 == 0){
            return 1;
        }else{
            return 0;
        }
    }
}

//Función BuscarRecursiva: Función recursiva que devuelve la posición de un registro en el archivo, 
//siempre y cuando coincida la fecha y el campo .borrado sea igual a 0;
//en caso contrario, devuelve un -1.

int BuscarRecursiva(TData x, int cant, int fecha){
    if(cant == -1){
        return -1;
    }else{
        if(cant >= 0){
            if(x.a[cant].ddmmyyyy == fecha && x.a[cant].borrado == 0){
                return cant;
            }else{
                return BuscarRecursiva(x, cant - 1, fecha);
            }
        }
    }
    return -1; //Para evitar un warning (no llega nunca a este punto)
}

//Acción AgregarLista: se encarga de agregar al final de una LSE un nuevo elemento. 
//Los nodos contendrán la fecha y la temp. máx. del mismo día.

void AgregarLista(TNodo **p, Tregdiario a){ 
    TNodo *aux, *aux2;

    aux = *p;
    if(aux == NULL){                            //Inserción a la cabeza
        aux2 = (TNodo *) malloc(sizeof(TNodo));
        aux2->info.ddmmyyyy = a.ddmmyyyy;
        aux2->info.tmax = a.tmax;
        aux2->next = aux;
        *p = aux2;
    }else{                                      
        if(aux != NULL){                        //Inserción a la cola
            while(aux->next != NULL){
                aux = aux->next;
            }
            aux2 = (TNodo *) malloc(sizeof(TNodo));
            aux2->info.ddmmyyyy = a.ddmmyyyy;
            aux2->info.tmax = a.tmax;
            aux2->next = aux->next;
            aux->next = aux2;
        }
    }
}

//Acción BubbleSort1: aplica BubbleSort para ordenar de mayor a menor los registros de un arreglo 
//según la velocidad del viento.

void BubbleSort1(TData *regDs){                                         
    int i;  //Variable para indicar los índices del arreglo
    int j;  //Variable para indicar los índices del arreglo
    Tregdiario auxReg; //Variable que será usada para guardar el registro con menor FF, para luego ser intercambiado con su sucesor.
     
    i = (*regDs).cant - 1;

    while(i >= 0){
        j = 0;
        while(j < i){
            if((*regDs).a[j].FF < (*regDs).a[j+1].FF){

                auxReg.ddmmyyyy = (*regDs).a[j].ddmmyyyy;
                auxReg.FF = (*regDs).a[j].FF;

                (*regDs).a[j].ddmmyyyy = (*regDs).a[j + 1].ddmmyyyy;
                (*regDs).a[j].FF = (*regDs).a[j + 1].FF;

                (*regDs).a[j + 1].ddmmyyyy = auxReg.ddmmyyyy;
                (*regDs).a[j + 1].FF = auxReg.FF;
            }
            j = j + 1;
        }
        i = i - 1;
    }
}

//Acción BubbleSort2: aplica BubbleSort para ordenar de mayor a menor los registros de un arreglo 
//según la temperatura máxima.

void BubbleSort2(TData *regDs){                                        
    int i;  //Variable para indicar los índices del arreglo
    int j;  //Variable para indicar los índices del arreglo
    Tregdiario auxReg; //Variable que será usada para guardar el registro con menor FF, para luego ser intercambiado con su sucesor.
     
    i = (*regDs).cant - 1;

    while(i > 0){

        j = 0;

        while(j < i){
            if((*regDs).a[j].tmax < (*regDs).a[j+1].tmax){

                auxReg.ddmmyyyy = (*regDs).a[j].ddmmyyyy;
                auxReg.tmax = (*regDs).a[j].tmax;

                (*regDs).a[j].ddmmyyyy = (*regDs).a[j + 1].ddmmyyyy;
                (*regDs).a[j].tmax = (*regDs).a[j + 1].tmax;          

                (*regDs).a[j + 1].ddmmyyyy = auxReg.ddmmyyyy;
                (*regDs).a[j + 1].tmax = auxReg.tmax;
            }
            j = j + 1;
        }
        i = i - 1;
    }
}

//Función Vacia: devuelve 1 cuando el arreglo pasado está vacío y 0 cuando no lo está.

int Vacia(TData x){
    if(x.cant == 0){
        return 1;
    }else{
        return 0;
    }
}

//Acción MostrarLista: se encarga de mostrar los fechas de los registros de una LSE.
//Esquema: R2 marca final.

void MostrarLista(TNodo *p){ 
  TNodo *aux;

  aux = p;
  if(aux == NULL){
    printf("Lista vacía!\n");
  }else{
    if(aux != NULL){
        while(aux != NULL){
            printf("%ld\n", aux->info.ddmmyyyy); //muestra solo fecha
            aux = aux->next;
        }
    }
  }
}

//Acción InsertionSort: aplica InsertionSort para ordenar de menor a mayor los registros de un arreglo 
//según la precipitación pluvial acumulada.

void InsertionSort(TData *regDs){              
    Tregdiario auxArre;
    int i, j;

    i = 1;
    while(i < (*regDs).cant){
        j = i;
        auxArre.ddmmyyyy = (*regDs).a[i].ddmmyyyy;
        auxArre.PP = (*regDs).a[i].PP;
        j--;
        while(j >= 0 && (*regDs).a[j].PP > auxArre.PP){
            (*regDs).a[j + 1].ddmmyyyy = (*regDs).a[j].ddmmyyyy;
            (*regDs).a[j + 1].PP = (*regDs).a[j].PP;
            j--;
        }
        (*regDs).a[j + 1].ddmmyyyy = auxArre.ddmmyyyy;
        (*regDs).a[j + 1].PP = auxArre.PP;
        i++;
    }
}

//Acción MostrarXUltimos: se encargará de mostrar los últimos 10 días (o menos, en el 
//caso de TDATA con 1<=.cant<=9) donde se dieron las mayores precips.

void MostrarXUltimos(TData regDiarios, int MaxDias){  
    int i; //Variable necesaria para recorrer el arreglo y mostrar su contenido

    i = regDiarios.cant - 1;

    while(i >= 0 && i >= (regDiarios.cant - MaxDias)){
        printf("Fecha: %ld\n", regDiarios.a[i].ddmmyyyy);
        printf("Precipitación pluvial acumulada: %d\n", regDiarios.a[i].PP);
        i = i - 1;
    }
}

//Acción MostrarXPrimeros: se encargará de mostrar los 10 últimos elementos del arreglo (o menos, en el caso de TDATA con 1<=.cant<=9), 
//donde se dieron las mayores velocidades del viento.
//Esquema: R2 marca final.

void MostrarXPrimeros(TData x, int MaxDias){ 
    int i;

    i = 0;
    if(i == x.cant){
        printf("Arreglo vacío\n");
    }else{
        if(i < x.cant){
            while(i < x.cant && i < MaxDias){         //muestra solo los 10 primeros
                printf("Fecha: %ld\n", x.a[i].ddmmyyyy); //muestra solo fechas
                printf("Velocidad del viento: %d\n", x.a[i].FF);
                i++;
            }
        }
    }
}

//Acción ArchAArreg: acción necesaria para pasar los registros activos del archivo a un arreglo.
//Esquema: R1 de marca inicial.

void ArchAArreg(FILE *x, TData *regDs){
    Tregdiario a; //Auxiliar necesario para guardar los registros que se irán leyendo
    int i;        //Auxiliar para indicar los índices a completar

    (*regDs).cant = 0;
    i = 0;

    while (fread(&a, sizeof(a), 1, f) > 0){
        if(a.borrado == 0){

            (*regDs).a[i].ddmmyyyy = a.ddmmyyyy;
            (*regDs).a[i].tmax = a.tmax;
            (*regDs).a[i].tmin = a.tmin;
            (*regDs).a[i].DV = a.DV;
            (*regDs).a[i].FF = a.FF;
            (*regDs).a[i].HUM = a.HUM;
            (*regDs).a[i].PNM = a.PNM;
            (*regDs).a[i].PP = a.PP;
            (*regDs).a[i].borrado = 0;
            (*regDs).cant = (*regDs).cant + 1;
            i = i + 1;

        }
    }
}

//***MÓDULOS PRINCIPALES***  

//Acción Alta: permite ingresar todos los nuevos registros de Tregdiario 
//que quiera el usuario y los escribe en el archivo. 
//Los datos ingresados respetan todos los rangos de los campos que forman a Tregdiario.

void Alta(char nomExt[40], int yyyy){
    FILE *f;
    Tregdiario a;
    int dia, mes, fecha;
    int valido;
    int seguir;

    f = fopen(nomExt, "ab+");

    do{
        valido = 0;
        do{                                       //Ingreso de la fecha
            printf("Ingrese el día: ");
            scanf("%d", &dia);
            printf("\n");
            printf("ingrese el mes: ");
            scanf("%d", &mes);
            printf("\n");
            
            if(mes == 2){
                if(Bisiesto(yyyy) == 1){
                    if(dia >= 1 && dia <= 29){
                        valido = 1;
                    }
                }else{
                    if(dia >= 1 && dia <= 28){
                        valido = 1;
                    }
                }
            }else{
                if(mes == 4 || mes == 6 || mes == 9 || mes == 11){
                    if(dia >= 1 && dia <= 30){
                        valido = 1;
                    }
                }else{
                    if(mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12){
                        if(dia >= 1 && dia <= 31){
                            valido = 1;
                        }
                    }
                }
            }

            fecha = (dia * 1000000) + (mes * 10000) + yyyy;
            fseek(f, 0, SEEK_SET);

            do{}while(fread(&a, sizeof(a), 1, f) > 0 && (a.ddmmyyyy != fecha || a.borrado != 0)); //Se busca si ya existe un registro 
                                                                                                  //con la fecha ingresada
            if(a.ddmmyyyy == fecha && a.borrado == 0){
                printf("Ya existe un registro con esa fecha!\n");
                fseek(f, 0, SEEK_END);
                valido = 0;
            }

        }while(valido != 1);

        a.ddmmyyyy = fecha;

        do{                                                       //Ingreso de la temp máxima
            printf("Ingrese la temperatura máxima del día: ");
            scanf("%d", &a.tmax);
            printf("\n");
        }while(a.tmax < -50 || a.tmax > 60);

        do{                                                       //Ingreso de la temp mínima
            printf("Ingrese la temperatura mínima del día: ");
            scanf("%d", &a.tmin);
            printf("\n");
        }while(a.tmin < -50 || a.tmin > 60);

        do{                                                       //Ingreso de la humedad promedio
            printf("Ingrese la humedad promedio: "); 
            scanf("%d", &a.HUM);
            printf("\n");
        }while(a.HUM < 0 || a.HUM > 100);

        do{                                                       //Ingreso de la presión atmosférica
            printf("Ingrese la presión atmosférica: ");
            scanf("%d", &a.PNM);
            printf("\n");
        }while(a.PNM < 900 || a.PNM > 3500);

        do{                                                       //Ingreso de la dirección del viento
            printf("Ingrese la dirección del viento: ");
            scanf("%d", &a.DV);
            printf("\n");
        }while(a.DV < 0 || a.DV > 360);

        do{                                                        //Ingreso de la velocidad del viento
            printf("Ingrese la velocidad del viento: ");
            scanf("%d", &a.FF);
            printf("\n");
        }while(a.FF < 0 || a.FF > 400);

        do{                                                        //Ingreso de la preicpitación pluvial acumulada
            printf("Ingrese la precipitación pluvial acumulada: ");
            scanf("%d", &a.PP);
            printf("\n");
        }while(a.PP < 0 || a.PP > 1000);

        a.borrado = 0;

        fwrite(&a, sizeof(a), 1, f);
        printf("Registro cargado con exito!\n\n");

        do{
            printf("Desea cargar otro registro?:\n");
            printf("1-Aceptar\n");
            printf("2-Cancelar\n");
            printf("Ingrese la opción: ");
            scanf("%d", &seguir);
            printf("\n");
        }while(seguir != 1 && seguir != 2);

    }while(seguir != 2);

    fclose(f);
}

//Acción Suprimir: elimina todos los registros de Tregdiario que desee el usuario buscándolos por la
//fecha y borrándolos lógicamente siempre y cuando su campo .borrado sea igual a 0.
//Esquema: R2 de marca incial.

void Suprimir(char nomExt[40], int yyyy){
    Tregdiario a;
    Tregdiario b;
    FILE *f;
    int seguir;
    int dia, mes;
    long int fecha;

    f = fopen(nomExt, "rb+");
    fseek(f, 0, SEEK_END);

    if(ftell(f) == 0){
        printf("El archivo está vacío!\n");
    }else{
        do{
            fseek(f, 0 , SEEK_SET);
            printf("Ingrese la fecha del registro a borrar:\n");
            printf("Ingrese el día: ");
            scanf("%d", &dia);
            printf("\n");
            printf("Ingrese el mes: ");
            scanf("%d", &mes);
            printf("\n");
            fecha = (dia * 1000000) + (mes * 10000) + yyyy;

            do{}while(fread(&a, sizeof(a), 1, f) > 0 && (a.ddmmyyyy != fecha || a.borrado != 0));

            if(a.ddmmyyyy == fecha && a.borrado == 0){
                printf("Encontrado!\n");
                a.borrado = 1;
                if(fread(&b, sizeof(b), 1, f) == 0){
                    fseek(f, -sizeof(Tregdiario), SEEK_END);              
                }else{                  
                    fseek(f, -2 * sizeof(Tregdiario), SEEK_CUR);
                }
                fwrite(&a, sizeof(a), 1, f);
                printf("\nRegistro borrado!\n");
            }else{
                printf("\nNo existe un registro con esa fecha!\n");
            }

            do{
                printf("Desea suprimir otro registro?:\n");
                printf("1-Aceptar\n");
                printf("2-Cancelar\n");
                printf("Ingrese la opción: ");
                scanf("%d", &seguir);
                printf("\n");
            }while(seguir != 1 && seguir != 2);

        }while(seguir != 2);
    }
    fclose(f);
}

////Acción Modificar: permite modificar por completo (excepto el campo .borrado y la fecha) todos los registros del archivo que desee el usuario, 
//en caso de que se encuentre un registro con la fecha ingresada.
//Esquema: Búsqueda de marca inicial.

void Modificar(char nomExt[40], int yyyy){
    Tregdiario a;
    Tregdiario b;
    FILE *f;
    int seguir;
    int dia, mes;
    int fecha;

    f = fopen(nomExt, "rb+");
    fseek(f, 0, SEEK_END);

    if(ftell(f) == 0){
        printf("El archivo está vacío!\n");
    }else{
        do{
            fseek(f, 0 , SEEK_SET);
            printf("Ingrese la fecha del registro que desea modificar:\n");
            printf("Ingrese el día: ");
            scanf("%d", &dia);
            printf("\n");
            printf("Ingrese el mes: ");
            scanf("%d", &mes);
            printf("\n");
            fecha = (dia * 1000000) + (mes * 10000) + yyyy;

            do{}while(fread(&a, sizeof(a), 1, f) > 0 && (a.ddmmyyyy != fecha || a.borrado != 0)); 

            if(a.ddmmyyyy == fecha && a.borrado == 0){
                printf("Modificación de datos:\n");

                do{                                                       //Ingreso de la temp máxima
                  printf("Ingrese la temperatura máxima del día: ");
                  scanf("%d", &a.tmax);
                  printf("\n");
                }while(a.tmax < -50 || a.tmax > 60);

               do{                                                       //Ingreso de la temp mínima
                  printf("Ingrese la temperatura mínima del día: ");
                  scanf("%d", &a.tmin);
                  printf("\n");
                }while(a.tmin < -50 || a.tmin > 60);

               do{                                                       //Ingreso de la humedad promedio
                  printf("Ingrese la humedad promedio: "); 
                  scanf("%d", &a.HUM);
                  printf("\n");
                }while(a.HUM < 0 || a.HUM > 100);

                do{                                                       //Ingreso de la presión atmosférica
                  printf("Ingrese la presión atmosférica: ");
                  scanf("%d", &a.PNM);
                  printf("\n");
                }while(a.PNM < 900 || a.PNM > 3500);

                do{                                                       //Ingreso de la dirección del viento
                  printf("Ingrese la dirección del viento: ");
                  scanf("%d", &a.DV);
                  printf("\n");
                }while(a.DV < 0 || a.DV > 360);

                do{                                                        //Ingreso de la velocidad del viento
                  printf("Ingrese la velocidad del viento: ");
                  scanf("%d", &a.FF);
                  printf("\n");
                }while(a.FF < 0 || a.FF > 400);

                do{                                                        //Ingreso de la preicpitación pluvial acumulada
                  printf("Ingrese la precipitación pluvial acumulada: ");
                  scanf("%d", &a.PP);
                  printf("\n");
                }while(a.PP < 0 || a.PP > 1000);


                if(fread(&b, sizeof(b), 1, f) == 0){
                    fseek(f, -sizeof(Tregdiario) , SEEK_END);
                }else{                  
                    fseek(f, -2 * sizeof(Tregdiario), SEEK_CUR);
                }
                fwrite(&a, sizeof(a), 1, f);
                printf("\nRegistro modificado!\n");
            }else{
                printf("\nNo existe un registro con esa fecha!\n");
            }

            do{
                printf("Desea modificar otro registro?:\n");
                printf("1-Aceptar\n");
                printf("2-Cancelar\n");
                printf("Ingrese la opción: ");
                scanf("%d", &seguir);
                printf("\n");
            }while(seguir != 1 && seguir != 2);

        }while(seguir != 2);
    }
    fclose(f);
}

//Acción Busqueda: realiza la búsqueda por fecha de todos los registros que desee el usuario 
//y si existen muestra todos sus campos.

void Busqueda(char nomExt[40], int yyyy){
  FILE *f;
  TData regdiarios;
  int pos;
  int dia, mes;
  long int fecha;
  int seguir;
  
  f = fopen(nomExt, "rb+");
  
  fseek(f, 0, SEEK_END);
  
  if(ftell(f) == 0){
    printf("El archivo está vacío!\n");
  }else{
    fseek(f, 0, SEEK_SET);
    ArchAArreg(f, &regdiarios);
    
    do{
      printf("Ingrese la fecha que desea buscar:\n");
      printf("Ingrese el día: ");
      scanf("%d", &dia);
      printf("\n");
      printf("Ingrese el mes: ");
      scanf("%d", &mes);
      printf("\n");
      fecha = (dia * 1000000) + (mes * 10000) + yyyy;
  
      pos = BuscarRecursiva(regdiarios, regdiarios.cant, fecha);
    
      if(pos != -1){
          printf("Datos del registro buscado:\n");
          printf("*********************************\n");
          printf("Fecha: %ld\n", regdiarios.a[pos].ddmmyyyy);
          printf("Temp max: %d\n", regdiarios.a[pos].tmax);
          printf("Temp min: %d\n", regdiarios.a[pos].tmin);
          printf("Humedad promedio: %d\n", regdiarios.a[pos].HUM);
          printf("Presión atmosférica: %d\n", regdiarios.a[pos].PNM);
          printf("Precipitaciones: %d\n", regdiarios.a[pos].PP);
          printf("Dirección del viento: %d\n", regdiarios.a[pos].DV);
          printf("Veloc del viento: %d\n", regdiarios.a[pos].FF);
          printf("*********************************\n");
      }else{
        printf("No existe un registro con la fecha ingresada!\n");
      }
      
      do{
        printf("Desea buscar otro registro?:\n");
        printf("1-Aceptar\n");
        printf("2-Cancelar\n");
        printf("Ingrese la opción: ");
        scanf("%d", &seguir);
        printf("\n");
      }while(seguir != 1 && seguir != 2);
      
    }while(seguir != 2);
  
  }
  fclose(f);
}

//Acción Mostrar: se encarga de mostrar todos los registros activos del archivo.
//Esquema: R2 de marca inicial.

void Mostrar(char nomExt[40]){  
    FILE* f;
    Tregdiario a;
    int cont; //Contador de registros activos mostrados.
    
    f = fopen(nomExt, "rb+");
    fseek(f, 0, SEEK_END);

    if(ftell(f) == 0){
        printf("El archivo está vacío! \n");
    }else{

        fseek(f, 0 , SEEK_SET);
        cont = 0;

        while(fread(&a, sizeof(a), 1, f) > 0){
            if(a.borrado == 0){
                printf("*********************************\n");
                printf("\n");
                printf("Fecha: %ld \n", a.ddmmyyyy);
                printf("Temp. máx.: %d \n", a.tmax);
                printf("Temp. min.: %d \n", a.tmin);
                printf("Humedad promedio: %d \n", a.HUM);
                printf("Presión atmosférica: %d \n", a.PNM);
                printf("Direcc. del viento: %d \n", a.DV);
                printf("Veloc. del viento: %d \n", a.FF);
                printf("Precip. pluvial acum.: %d \n", a.PP);
                printf("\n");
                cont = cont + 1;
            }
        }

        if(cont == 0){
            printf("Arch. sin registros activos \n");
        }
    }
    fclose(f);
}

//Acción ListarMaxTemp: se encarga de mostrar la máx. temp. que se dio entre los registros activos
//y las fechas donde se dio esa máx.temp.
//Esquema: Utiliza (B), luego (R2) y al  final (R1). Los tres de marca final.

void ListarMaxTemp(char nomExt[40]){
    FILE* f;
    TNodo *p;
    int i;
    TData x;
    Tregdiario a;
    int tempMax;

    f = fopen(nomExt, "rb+");
    fseek(f, 0, SEEK_END);

    if(ftell(f) == 0){
        printf("El archivo está vacío \n");
    }else{
            fseek(f, 0 , SEEK_SET);
            ArchAArreg(f, &x);

            if(Vacia(x) == 0){
                BubbleSort2(&x);

                i = 0;
                p = NULL;
                a.ddmmyyyy = x.a[i].ddmmyyyy;
                a.tmax = x.a[i].tmax;
                AgregarLista(&p, a);
                i++;

                while(i < x.cant && x.a[i].tmax == p->info.tmax){
                    a.ddmmyyyy = x.a[i].ddmmyyyy;
                    a.tmax = x.a[i].tmax;
                    AgregarLista(&p, a);
                    i++;
                }
                tempMax = a.tmax;
                printf("La temp. máxima registrada fue: %d\n", tempMax); 
                printf("Fechas en las que se dio:\n");
                MostrarLista(p);
            }else{
                printf("El archivo está vacío!\n");
            }
    }
    fclose(f);
}

//Acción ListarMaxPrec: se encarga de mostrar los 10 registros donde se dieron las mayores precipitaciones.
//Esquema: R2 de marca final.

void ListarMaxPrec(char nomExt[40]){
    TData regDiarios;
    FILE* f;

    f = fopen(nomExt, "rb+");
    fseek(f, 0 , SEEK_END);
   
    if(ftell(f) == 0){
        printf("El archivo está vacío");
    }else{
        fseek(f, 0, SEEK_SET);    
        ArchAArreg(f, &regDiarios);
        if(Vacia(regDiarios) == 0){
            InsertionSort(&regDiarios);
            MostrarXUltimos(regDiarios, 10);
        }else{
           printf("No hay registros activos\n");
        }
    }
    fclose(f);
}

//Acción ListarVelocViento: se encarga de mostrar los 10 registros 
//donde se dieron las mayores velocidades del viento.
//Esquema: R2 de marca final.

void ListarVelocViento(char nomExt[40]){
    FILE *f;
    TData regdiarios;

    f = fopen(nomExt, "r");
    fseek(f, 0, SEEK_END);

    if(ftell(f) == 0){
        printf("El archivo está vacío!\n");
    }else{
        fseek(f, 0, SEEK_SET);
        ArchAArreg(f, &regdiarios);

        if(Vacia(regdiarios) != 1){
            BubbleSort1(&regdiarios);
            MostrarXPrimeros(regdiarios, 10);
        }else{
            printf("No hay registros activos!\n");
        }
    }
    fclose(f);

}

//Acción CopiaDeSeguridad: realiza una copia de seguridad pasando solo los registros activos en el nuevo archivo. 
//La copia siempre se realiza sobre el archivo backup.dat

void CopiaDeSeguridad(char nomExt[40]){
    FILE *f;
    FILE *g;
    Tregdiario a;

    f = fopen(nomExt, "rb+");
    fseek(f, 0, SEEK_END);

    if(ftell(f) == 0){
        printf("El archivo está vacío!\n");
    }else{
        fseek(f, 0 , SEEK_SET);
        g = fopen("backup.dat", "wb+");

        while(fread(&a, sizeof(a), 1, f) > 0){
            if(a.borrado == 0){
                fwrite(&a, sizeof(a), 1, g);
            }
        }

        fseek(g, 0, SEEK_END);

        if(ftell(g) == 0){
            printf("Arch. original sin elementos activos!\n");
        }else{
            printf("Copia realizada con éxito en el archivo 'backup.dat'!\n");
        }
    }
    
    fclose(g);
    fclose(f);
}