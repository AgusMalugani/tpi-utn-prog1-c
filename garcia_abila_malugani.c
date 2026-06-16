/*
TRABAJO PRACTICO DE PROGRAMACION
INTEGRANTES DEL GRUPO: Garcia Arami, Abila Pablo, Malugani Agustin

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void cargaDeAlumnos(char dni[][15], char nombre[][30], char apellido[][30], int edad[], char codTaller[][10], int medioPago[], float montoAbonar[30], int *cantAlumnos);
float totalAPagarPorCurso(char codTaller[10], int edad, int medioPago);
int buscadorDeAlumnoPorDni(char dni[][15], int cantAlumnos);
void eleccionTaller(char codTaller[][10], int cantAlumnos, int indice);
void estadoTalleres(char codTaller[][10], float montoAbonar[], int cantAlumnos);
void estadisticaGestion(int cantAlumnos, char codTaller[][10], int edad[]);
void intercambiarAlumnosLocal(int indiceA, int indiceB, char dniLocal[][15], char nombreLocal[][30], char apellidoLocal[][30], int edadLocal[], char codTallerLocal[][10]);
void mostrarListaGeneral(char dniLocal[][15], char nombreLocal[][30], char apellidoLocal[][30], int edadLocal[], char codTallerLocal[][10], int cantAlumnos);
void mostrarListaPorDisciplina(char dniLocal[][15], char nombreLocal[][30], char apellidoLocal[][30], int edadLocal[], char codTallerLocal[][10], int cantAlumnos);
void listaGeneralAlumnos(char dni[][15], char nombre[][30], char apellido[][30], int edad[], char codTaller[][10], int cantAlumnos);
void listaPorDisciplina(char dni[][15], char nombre[][30], char apellido[][30], int edad[], char codTaller[][10], int cantAlumnos);

int validarDni(char dni[15]);  
int validacionString(char string[30]);
int validacionEdad(int edad); 
int validacionMetodoPago(int metodoPago);  

void main()
{
    char dni[30][15];
    char nombre[30][30];
    char apellido[30][30];
    int edad[30];
    char codTaller[30][10];
    int medioPago[30];
    float montoAbonar[30];
    int opcion;
    int cantAlumnos = 0;
    int bandera = 0;

    do
    {
        printf("===========================\n");
        printf("MENU DE INSCRIPCION\n");
        printf("===========================\n");
        printf("1- CARGAR ALUMNOS\n");
        printf("2- LISTA GENERAL DE ALUMNOS\n");
        printf("3- LISTA POR DISCIPLINA\n");
        printf("4- ESTADO DE TALLER\n");
        printf("5- BUSCADOR DE ALUMNOS\n");
        printf("6- ESTADISTICA DE GESTION\n");
        printf("7- CERRAR SISTEMA\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        printf("\n");

        switch (opcion)
        {
        case 1:
        {
            cargaDeAlumnos(dni, nombre, apellido, edad, codTaller, medioPago, montoAbonar, &cantAlumnos);
            break;
        }
        case 2:
        {
            if (cantAlumnos == 0)
            {
                printf("No hay alumnos cargados.\n");
            }
            else
            {
                listaGeneralAlumnos(dni, nombre, apellido, edad, codTaller, cantAlumnos);
            }
            break;
        }

        case 3:
        {
            if (cantAlumnos == 0)
            {
                printf("No hay alumnos cargados.\n");
            }
            else
            {
                listaPorDisciplina(dni, nombre, apellido, edad, codTaller, cantAlumnos);
            }
            break;
        }

        case 4:
        {
            if (cantAlumnos == 0)
            {
                printf("No hay alumnos cargados.\n");
            }
            else
            {
                estadoTalleres(codTaller, montoAbonar, cantAlumnos);
            };
            break;
        };

        case 5:
        {
            if (cantAlumnos == 0)
            {
                printf("No hay alumnos cargados.\n");
            }
            else
            {
                int i;
                i = buscadorDeAlumnoPorDni(dni, cantAlumnos); // CON EL I ( SERIA LA POSICION DE LOS ARREGLOS ) BUSCO LOS OTROS DATOS
                if (i == -1)
                {
                    printf("No existe usuario con ese dni \n");
                }
                else
                {
                    printf("Datos del usuario: \n");
                    printf("Nombre: %s \n", nombre[i]);
                    printf("Apellido: %s \n", apellido[i]);
                    printf("Dni: %s \n", dni[i]);
                    printf("Edad: %d \n", edad[i]);
                    printf("Taller: %s \n", codTaller[i]);
                    printf("Importe a abonar: %.2f \n", montoAbonar[i]);
                }
            }

            break;
        }
        case 6:
        {
            if (cantAlumnos == 0)
            {
                printf("No hay alumnos cargados.\n");
            }
            else
            {
                estadisticaGestion(cantAlumnos, codTaller, edad);
            }
            break;
        }

        case 7:
        {
            int resp;
            int salida = 0;
            do
            {
                printf("Desea salir del programa? \n");
                printf("1- Si\n");
                printf("2- No\n");
                scanf("%d", &resp);

                if (resp == 1 || resp == 2)
                {
                    salida = 1;
                }
                else
                {
                    printf("Opcion invalida.\n");
                };

            } while (salida == 0);

            if (resp == 1)
            {
                printf("Saliendo del sistema.\n");
                bandera = 1;
            }
            else if (resp == 2)
            {
                printf("Volviendo al menu.\n");
            };
            break;
        }
        default:
        {
            printf("Opcion invalida. \n");
            break;
        }
        }

    } while (bandera == 0);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//                  VALIDACIONES
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
la funcion validarDni recibe por parametro el dni a validar,
va a validar que tenga 7-8 digitos y si eso se cumple validara si empieza con 5 o 6  o si no, si esta entre 10.000.000 - 60.000.000

se utiliza la funcion strlen para obtener la cantidad de digitos del dni
se utiliza atoi para pasar el dni de string a numero para corroborar de manera mas facil si esta entre 10 y 60 millones

si no se cumple nada de esto, retorna un 0. En caso que sea un dni valido, retorna un 1 ( se usa la variable bandera para esto)
*/
int validarDni(char dni[15])
{
  
    int bandera = 0;
    int lenghtDni = strlen(dni);


    if (lenghtDni < 7 || lenghtDni > 8)
    {
        printf("El dni debe contener entre 7 u 8 digitos \n");
        // 1.000.000 - 10.000.000
    }
    else
    {

        int numDni = atoi(dni); //convierte la cadena a un entero
        char primerNum = dni[0];
        if ((primerNum == '5' || primerNum == '6') || (lenghtDni == 8 && (numDni >= 10000000 && numDni <= 60000000)))
        {
            bandera = 1;
        }
        else
        {
            printf("El Dni debe comenzar con 5 o 6  o debe estar entre el rango 10.000.000 - 60.000.000 \n");
        };
    }

    return bandera;
}


/*
validacionString, si el string tiene menos de 3 caracteres o tiene mas de 30, entonces lanza un error 
*/
int validacionString(char string[30])
{

    int bandera = 0;
    int lenghtString = strlen(string);

    if (lenghtString > 2 && lenghtString < 30)
    {
        bandera = 1;
    }
    else
    {
        printf("Debe ingresar almenos 2 caracteres y menos de 30 caracteres \n");
    };

    return bandera;
};


/*validacionEdad, si la edad es menor q 0 o mayor que 99, entonces lanza error*/
int validacionEdad(int edad)
{
    int bandera = 0;
    if (edad < 100 && edad > 0)
    {
        bandera = 1;
    }
    else
    {
        printf("La edad debe estar entre 1-99 \n");
    }
    return bandera;
};

/* validacionMetodoPago, si no es 1 o 2, lanza error*/
int validacionMetodoPago(int metodoPago)
{
    int bandera = 0;

    if (metodoPago == 1 || metodoPago == 2)
    {
        bandera = 1;
    }
    else
    {
        printf("Opcion ingresada incorrecta. Debe ser 1 o 2 \n");
    };

    return bandera;
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//                  FUNCIONES
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
    La funcion cargaDeAlumnos se encargha de toda la logica para la carga de alumnos, recibe por parametro
    los arreglos: dni, nombre, apellido, edad, codTaller, medioPago, montoAbonar  y la variable por puntero *cantAlumnos

    en dicha funcion primero pedimos la cant de alumnos que vamos aingresar y luego creamos un bucle for que empiece de 0 hasta ese numero de alumnos
    en la funcion vamos a utilizar los arreglos paralelos para guardar los datos, en todos los arreglos en la posicion i vamos a tener los datos de ese alumno

    por ejemplo el primer alumno que cargue tendra la posicion en todos los arreglos que seria la posicion 0, Asique para acceder a los datos de ese alumno
    tendria que buscar la posicion 0 de todos los arreglos, nombre,apellido,dni, etc

*/

void cargaDeAlumnos(char dni[][15], char nombre[][30], char apellido[][30], int edad[], char codTaller[][10], int medioPago[], float montoAbonar[], int *cantAlumnos)
{
    printf("INGRESE LA CANTIDAD DE ALUMNOS QUE INGRESARA \n");
    scanf("%d", cantAlumnos); // lo cargo por puntero

    // al pasar los arreglos no hace falta pasarlo por puntero, ya se pasan por puntero de manera implicita
    for (int i = 0; i < *cantAlumnos; i++)
    {
        printf("CARGA DEL ALUMNO %d \n", i);

        do
        {
            printf("Ingrese el DNI\n");
            scanf("%s", dni[i]);
        } while (validarDni(dni[i]) == 0);

        do
        {

            printf("Ingrese el NOMBRE\n");
            scanf("%s", nombre[i]);

        } while (validacionString(nombre[i]) == 0);

        do
        {
            printf("Ingrese el APELLIDO\n");
            scanf("%s", apellido[i]);
        } while (validacionString(apellido[i]) == 0);

        do
        {
            printf("Ingrese la EDAD\n");
            scanf(" %d", &edad[i]);
        } while (validacionEdad(edad[i]) == 0);

        eleccionTaller(codTaller, *cantAlumnos, i);

        do
        {
            printf("Ingrese el medio de pago:\n");
            printf("1- Efectivo \n");
            printf("2- Tarjeta de credito \n");
            scanf("%d", &medioPago[i]);
        } while (validacionMetodoPago(medioPago[i])== 0);

        montoAbonar[i] = totalAPagarPorCurso(codTaller[i], edad[i], medioPago[i]);
    };
};

/*
    la funcion eleccionTaller recibe por parametro el arreglo de codTaller, la cantAlumnos ingresados y el indice en el cual se encuentra la funcion padre ( cargaDeAlumnos )
    en la funcion creamos 2 variables, char codigo que guardara el codigo que ingrese el usuario
    int bandera que se inicializa en -1, esta variable la usaremos como variable para salir del bucle dowhile, justamente como dice su nombre, como bandera
    el bucle dowhile se ejecutara mientras que bandera sea == -1

    dentro del bucle dowhile creamos una variable contadora que la iniciamos en 0
    pedimos que ingrese el codigo el usuario y hacemos un bucle for para recorrer este arreglo de codTaller por la cant de alumnos ingresados

    dentro del for vamos a hacer un condicional diciendo que si el codTaller[i] ==  codigo le vamos a aumentar en 1 al contador, esto nos sirve para saber
    la cantidad de personas que tienen ese taller, ya que si el taller tiene 60 personas, no se podra elegir y tendremos que elegir otro taller

    saldremos del bucle una vez que elijamos un taller que tenga espacio.

    tras salir guardaremos en el arreglo de codTaller en el indice que se encuentra la funcion padre ( recordamos que pasamos indice por parametro )
    de esta manera le guardamos en la posicion correspondiente el curso al usuario, utilizando los punteros

*/

void eleccionTaller(char codTaller[][10], int cantAlumnos, int indice)
{
    char codigo[10];
    int bandera = 1;
    int coincidenciaTaller = 1;
    char talleres[][10] = {"PNT", "ESC", "THR", "FOT"}; //arreglo auxiliar
    do
    {
        int cont = 0;  // va a servir para ver cuantos inscriptos hay por taller

        printf("Codigo Disciplina Importe Mensual\n");
        printf("PNT Pintura $25.000\n");
        printf("ESC Escultura $14.000\n");
        printf("THR Teatro $19.000\n");
        printf("FOT Fotografia $23.000\n");

        printf("Ingrese el codigo de Taller\n");
        scanf("%3s", codigo);

        for (int i = 0; i < cantAlumnos; i++)
        {
            if (strcmp(codTaller[i], codigo) == 0) // veo cada pos del arreglo, para saber la cant de inscriptos ahi
            {
                cont++;
            };
        };

        for (int i = 0; i < strlen(codigo); i++)
        {
            codigo[i] = toupper(codigo[i]); // Convertimos a mayúscula cada letra
        }

        for (int i = 0; i < 4; i++)
        {
            if (strcmp(codigo, talleres[i]) == 0)  // ahora comparo con el array aux a ver si esta ese taller
            {
                coincidenciaTaller = 0;  //si esta, cambio variable a 0
            };
        }

        if (coincidenciaTaller == 1)  //si es 1, significa que no estaba en el array aux
        {
            printf("El codigo ingresado no coincide con los codigos disponibles\n");
        }

        if (cont > 59) // si el cont es 60 significa que esta lleno
        {
            printf("Debe seleccionar otro taller, ya que el taller con el codigo %s se encuentra lleno \n", codigo);
        }
        else
        {
            bandera = 0;  // si cambio la bandera significa que lo puedo asignar correctamente y salir del bucle
        }

    } while (bandera == 1 || coincidenciaTaller == 1); // ambas banderas deben cambiar a 0 para poder salir del dowhile

    strcpy(codTaller[indice], codigo);   // si salio, entonces en el arreglo, en el indice q envie por param, guardo el codigo da taller
};

/*
    la funcion buscadorDeAlumnoPorDni recibe el arreglo de dni y la cantAlumnos ingresados
    se crean 2 variables, 1 para el dni a buscar y otra variable llamada indice que se inicializa en -1 ( se inicializo en -1 porque si la dejo en 0
    y no encuentra el dni, entonces tomara el dni del primer usuario del arreglo.)
    y una variable cont inicializada en 0, para evitar el bucle infinito, donde nunca encuentre el dni

    se le pide al usuario que ingrese el dni y se hace un bucle while donde se ejecutara hasta que i sea = a cantAlumnos o que indice sea != a -1
    esto significa que si indice es != -1 se encontro el dni

    dentro del bucle, en cada iteracion, se suma cont ++.  parasalir del bucle, se tiene que encontrar el dni, o el cont debe ser 3


    al salir del bucle while, 
    se valida si se encontro el dni, o si fue x max intento y retorna la variable indice. esta variable tiene 2 opciones
    -  -1 si no encontro el dni buscado
    -  el indice del dni buscado

*/

int buscadorDeAlumnoPorDni(char dni[][15], int cantAlumnos)
{
    char dniBuscar[15];
    int indice = -1;
    int cont = 0;
    do
    {
        printf("Ingrese el dni del usuario a buscar: \n");
        scanf("%s", &dniBuscar);
        cont++;
    } while (validarDni(dniBuscar) == 0 && cont < 3);

    int i = 0;
    while (i < cantAlumnos && indice == -1)
    {
        if (strcmp(dni[i], dniBuscar) == 0)
        {
            indice = i;
        };

        i++;
    };

    if (cont == 3 && indice == -1)
    {
        printf("Error, maximos intentos \n");
    }

    return indice;
};

/*

    La funcion totalAPagarPorCurso, va a recibir por parametro,  el codigo de taller que se ingreso, la edad del usuario y el medio de pago elegido

    se le define una variable importe en 2000, xq tiene una condicion que dice que si es menor a 5 años no importa el taller, abonara solamente 2000.
    por eso creamos la condicion y digo que si es igual o mayor a 5 cambie el importe
    desp ve si le aumenta el importe por el medi ode pago y retorna el importe

*/
float totalAPagarPorCurso(char codTaller[10], int edad, int medioPago)
{
    float importe = 2000;

    if (edad >= 5)
    {

        if (strcmp(codTaller, "PNT") == 0)
        {
            importe = 25000;
        };
        if (strcmp(codTaller, "ESC") == 0)
        {
            importe = 14000;
        };
        if (strcmp(codTaller, "THR") == 0)
        {
            importe = 19000;
        };
        if (strcmp(codTaller, "FOT") == 0)
        {
            importe = 23000;
        };

        if (medioPago == 2)
        {
            importe = importe + (importe * 0.05);
        }
    };

    return importe;
};

/*
    la funcion estadoTalleres, recibe por parametro el arreglo de codTalleres, montoAbonar y la variable de cantAlumnos

    en la funcion, voy a crear 3 variables:
    - cantidadAlumnosCurso, suma y sumaTotalTalleres
    - un arreglo talleres que tendra 4 posiciones porque tenemos 4 cursos posibles

    tendremos 2 for anidados, donde el primero sera del arreglo talleres que recorrera cada taller y se iniciara la variable suma y cantidadAlumnosCurso en 0, y por cada taller hara
    uso del otro for, para recorrer los usuarios cargados ( el arreglo de codTaller) y aumentara por cada iteracion que coincida la variable suma y cantidadAlumnosCurso
    ademas tambien hara sumaTotalTalleres += suma, para despues mostrar el total recaudado por la academia.
    Tras salir de ese for que recorre la cant de alumnos, se ingresa a otro if, que corrobora si el talleres[i] == a PNT por ejemplo
    y muestra el codigo de taller, el nombre, la cantidad de alumnos del taller ( la variable cantidadAlumnosCurso) y
    el monto recaudado por el taller ( la variable suma ). Asi se realizaran los 4 if correspondiente, uno por cada codigo de talleres

    al salir de los 2 for, imprimiremos la variable sumaTotalTalleres y mostraremos cual fue el total recaudado de la academia.
*/
void estadoTalleres(char codTaller[][10], float montoAbonar[], int cantAlumnos)
{
    int cantidadAlumnosCurso;
    float suma;
    float sumaTotalTalleres = 0;
    char talleres[][10] = {"PNT", "ESC", "THR", "FOT"}; //array aux

    for (int i = 0; i < 4; i++) // seria c/taller del array aux
    {
        suma = 0;
        cantidadAlumnosCurso = 0;
        for (int j = 0; j < cantAlumnos; j++)
        {
            if (strcmp(codTaller[j], talleres[i]) == 0) //comparo el taller de los alumnos con el array aux
            {
                suma = suma + montoAbonar[j];
                cantidadAlumnosCurso++;
            }
        }// cuando salgo del for muestro los resultados que encontre,la cant alumnos y la suma del taller
        printf("######################\n");
        if (strcmp(talleres[i], "PNT") == 0)
        {
            printf("Codigo: PNT\n");
            printf("Nombre de taller: Pintura\n");
            printf("Cantidad alumnos: %d \n", cantidadAlumnosCurso);
            printf("Monto recaudado del taller: %.2f \n", suma);
            printf("######################\n");
            printf("\n");
        };
        if (strcmp(talleres[i], "ESC") == 0)
        {
            printf("Codigo: ESC\n");
            printf("Nombre de taller: Escultura\n");
            printf("Cantidad alumnos: %d \n", cantidadAlumnosCurso);
            printf("Monto recaudado del taller: %.2f \n", suma);
            printf("######################\n");
            printf("\n");
        };
        if (strcmp(talleres[i], "THR") == 0)
        {

            printf("Codigo: THR\n");
            printf("Nombre de taller: Teatro\n");
            printf("Cantidad alumnos: %d \n", cantidadAlumnosCurso);
            printf("Monto recaudado del taller: %.2f \n", suma);
            printf("######################\n");
            printf("\n");
        };
        if (strcmp(talleres[i], "FOT") == 0)
        {
            printf("Codigo: FOT\n");
            printf("Nombre de taller: Fotografia\n");
            printf("Cantidad alumnos: %d \n", cantidadAlumnosCurso);
            printf("Monto recaudado del taller: %.2f \n", suma);
            printf("######################\n");
            printf("\n");
        };

        sumaTotalTalleres = sumaTotalTalleres + suma;
    }

    printf("El importe total recaudado por la academia fue de: %.2f \n", sumaTotalTalleres);
}


/*
estadisticaGestion, recibe la cantidad de alumnos, el array de codtaller y el array de edades
se recorre el arreglo de talleres auxiliar de 0 a 3
y se inicializa apenas se entra, las variables porcentaje, cantidadAlumonosCurso, cantMenores5anoisCurso, porcMenoresCurso

Se crea otro for, para recorrer el array q se envia de talleres, codTaller  
y se evalua si el taller es igual al taller que estoy en i ( aux [i] = codtaller[j])
si entra al condicional, significa que son el mismo nombre de taller y le suma 1 a cantidadAlumnosCurso ( esta variable me sirve para ver cuantos alumons tiene c/curso)
ahora evaluo, si ese alumno tiene menos de 5 años, si es asi, sumo uno a la variable cantMenores5AniosCurso

al salir del for voy a ver si la variable cantAlumMayor ( que tendria que tener el num de alumnos max en los cursor) es menor que
cantidadAlumnosCurso, si es asi, cantAlumMayor, ahora vale lo que vale cantidadAlumnosCursos
 y la variable  actualizo la variable codCursoMayor( esta variable va a guardar el codigo del taller con mas alumnos) con el codigo del taller en la posicion i, talleres[i]

despues calculo el porcentaje de alumnos, el porcentaje de alumnos menores a 5 años, y muestro los datos de los cursos correspondientes

*/
void estadisticaGestion(int cantAlumnos, char codTaller[][10], int edad[])
{

    int cantidadAlumnosCurso;
    float porcentaje;
    int cantAlumMayor = 0;
    char codCursoMayor[10];
    int cantMenores5AniosCurso;
    float porcMenoresCurso;
    /*
    6. Estadísticas de Gestión: Mostrar:
     Porcentaje de alumnos inscriptos en cada taller respecto del total.
     Taller con mayor cantidad de inscriptos.
     Porcentaje de alumnos menores de 5 años por cada taller.
    */

    char talleres[][10] = {"PNT", "ESC", "THR", "FOT"};//array aux

    for (int i = 0; i < 4; i++)
    {
        porcentaje = 0;
        cantidadAlumnosCurso = 0;
        cantMenores5AniosCurso = 0;
        porcMenoresCurso = 0;
        for (int j = 0; j < cantAlumnos; j++)
        {
            if (strcmp(codTaller[j], talleres[i]) == 0)
            {
                cantidadAlumnosCurso++;
                if (edad[j] < 5)
                {
                    cantMenores5AniosCurso++;
                };
            };
        };

        printf("######################\n");

        if (cantAlumMayor < cantidadAlumnosCurso)
        {
            cantAlumMayor = cantidadAlumnosCurso;
            strcpy(codCursoMayor, talleres[i]);
        }

        if (cantAlumnos != 0)
        {
            porcentaje = (cantidadAlumnosCurso * 100.0) / cantAlumnos;
        }
        else
        {
            porcentaje = 0;
        };

        if (cantidadAlumnosCurso != 0)
        {
            porcMenoresCurso = (cantMenores5AniosCurso * 100.0) / cantidadAlumnosCurso;
        }
        else
        {
            porcMenoresCurso = 0;
        };

        if (strcmp(talleres[i], "PNT") == 0)
        {
            printf("Codigo: PNT\n");
            printf("Cantidad alumnos: %d \n", cantidadAlumnosCurso);
            printf("Porcentaje de alumnos inscriptos en cada taller respecto del total: %.2f  \n", porcentaje);
            printf("porcentaje de menores a 5 anios del curso  %.2f \n", porcMenoresCurso);
            printf("######################\n");
            printf("\n");
        };

        if (strcmp(talleres[i], "ESC") == 0)
        {
            printf("Codigo: ESC\n");
            printf("Cantidad alumnos: %d \n", cantidadAlumnosCurso);
            printf("Porcentaje de alumnos inscriptos en cada taller respecto del total: %.2f  \n", porcentaje);
            printf("porcentaje de menores a 5 anios del curso  %.2f \n", porcMenoresCurso);
            printf("######################\n");
            printf("\n");
        };
        if (strcmp(talleres[i], "THR") == 0)
        {
            printf("Codigo: THR\n");
            printf("Cantidad alumnos: %d \n", cantidadAlumnosCurso);
            printf("Porcentaje de alumnos inscriptos en cada taller respecto del total: %.2f  \n", porcentaje);
            printf("porcentaje de menores a 5 anios del curso  %.2f \n", porcMenoresCurso);
            printf("######################\n");
            printf("\n");
        };
        if (strcmp(talleres[i], "FOT") == 0)
        {
            printf("Codigo: FOT\n");
            printf("Cantidad alumnos: %d \n", cantidadAlumnosCurso);
            printf("Porcentaje de alumnos inscriptos en cada taller respecto del total: %.2f  \n", porcentaje);
            printf("porcentaje de menores a 5 anios del curso  %.2f \n", porcMenoresCurso);
            printf("######################\n");
            printf("\n");
        };
    }

    printf("El curso con mas alumnos es: %s, con una cantidad de %d, alumnos \n", codCursoMayor, cantAlumMayor);
};

/*
    La funcion intercambiarAlumnosLocal recibe dos indices y los arreglos locales de copia.
    Intercambia los datos completos de un alumno entre indiceA e indiceB para mantener
    sincronizados dni, nombre, apellido, edad y codTaller al ordenar.  y evitar que se pierda algun dato ya que usamos arreglos paralelos

*/
void intercambiarAlumnosLocal(int indiceA, int indiceB, char dniLocal[][15], char nombreLocal[][30], char apellidoLocal[][30], int edadLocal[], char codTallerLocal[][10])
{
    char auxDni[15];
    char auxNombre[30];
    char auxApellido[30];
    char auxCodTaller[10];
    int auxEdad;

    strcpy(auxDni, dniLocal[indiceA]);
    strcpy(auxNombre, nombreLocal[indiceA]);
    strcpy(auxApellido, apellidoLocal[indiceA]);
    strcpy(auxCodTaller, codTallerLocal[indiceA]);
    auxEdad = edadLocal[indiceA]; // GUARDO LOS DATOS EN UNAS VARIABLES AUXILIARES PARA DESPUES ASIGNARLAS A AL OTRO ARREGLO

    strcpy(dniLocal[indiceA], dniLocal[indiceB]);
    strcpy(nombreLocal[indiceA], nombreLocal[indiceB]);
    strcpy(apellidoLocal[indiceA], apellidoLocal[indiceB]);
    strcpy(codTallerLocal[indiceA], codTallerLocal[indiceB]);
    edadLocal[indiceA] = edadLocal[indiceB]; // ACA REEMPLAZO LO QUE TENIA EN A Y PONGO LO QUE TENGO EN B

    strcpy(dniLocal[indiceB], auxDni);
    strcpy(nombreLocal[indiceB], auxNombre);
    strcpy(apellidoLocal[indiceB], auxApellido);
    strcpy(codTallerLocal[indiceB], auxCodTaller);
    edadLocal[indiceB] = auxEdad; // ACA EN B PONGO LO QUE GUARDE EN AUX, QUE SERIA LO QUE TENIA EN A

    // DE ESTA MANERA NO PIERDO LOS DATOS Y NO SE ME DESORDENAN LOS ARREGLOS PARALELOS
}

/*
    La funcion mostrarListaGeneral recibe los arreglos locales ya ordenados y la cantidad de alumnos.
    Muestra apellido y nombre, dni, edad y el codigo del taller seleccionado.
*/
void mostrarListaGeneral(char dniLocal[][15], char nombreLocal[][30], char apellidoLocal[][30], int edadLocal[], char codTallerLocal[][10], int cantAlumnos)
{
    printf("========== LISTA GENERAL DE ALUMNOS ==========\n");

    for (int i = 0; i < cantAlumnos; i++)
    {
        printf("Apellido y Nombre: %s %s\n", apellidoLocal[i], nombreLocal[i]);
        printf("DNI: %s\n", dniLocal[i]);
        printf("Edad: %d\n", edadLocal[i]);
        printf("Taller seleccionado: %s\n", codTallerLocal[i]);
        printf("----------------------------------------------\n");
    }
}

/*
    La funcion mostrarListaPorDisciplina recibe los arreglos locales ya ordenados y la cantidad de alumnos.
    Muestra codigo de taller, apellido y nombre, dni y edad.
*/
void mostrarListaPorDisciplina(char dniLocal[][15], char nombreLocal[][30], char apellidoLocal[][30], int edadLocal[], char codTallerLocal[][10], int cantAlumnos)
{
    printf("========== LISTA POR DISCIPLINA ==========\n");

    for (int i = 0; i < cantAlumnos; i++)
    {
        printf("Codigo de Taller: %s\n", codTallerLocal[i]);
        printf("Apellido y Nombre: %s %s\n", apellidoLocal[i], nombreLocal[i]);
        printf("DNI: %s\n", dniLocal[i]);
        printf("Edad: %d\n", edadLocal[i]);
        printf("-----------------------------------------\n");
    }
}

/*
    La funcion listaGeneralAlumnos copia los datos de los arreglos originales a arreglos locales,
    los ordena por apellido y nombre con ordenamiento por seleccion , y llama a mostrarListaGeneral
    sin modificar los arreglos originales del main.
*/
void listaGeneralAlumnos(char dni[][15], char nombre[][30], char apellido[][30], int edad[], char codTaller[][10], int cantAlumnos)
{
    char dniLocal[30][15];
    char nombreLocal[30][30];
    char apellidoLocal[30][30];
    int edadLocal[30];
    char codTallerLocal[30][10];
    int menor;
    int comparacionApellido;

    for (int i = 0; i < cantAlumnos; i++)
    {
        strcpy(dniLocal[i], dni[i]);
        strcpy(nombreLocal[i], nombre[i]);
        strcpy(apellidoLocal[i], apellido[i]);
        edadLocal[i] = edad[i];
        strcpy(codTallerLocal[i], codTaller[i]);
    } // EN ESTE FOR, COPIE TODOS LOS ELEMENTOS DEL ARREGLO ORIGINAL, EN EL ARREGLO LOCAL

    for (int i = 0; i < cantAlumnos - 1; i++)
    {
        menor = i;

        for (int j = i + 1; j < cantAlumnos; j++)
        {
            comparacionApellido = strcmp(apellidoLocal[j], apellidoLocal[menor]);

            if (comparacionApellido < 0 ||
                (comparacionApellido == 0 && strcmp(nombreLocal[j], nombreLocal[menor]) < 0))
            {
                menor = j;
            }
        }

        if (menor != i)
        {
            intercambiarAlumnosLocal(i, menor, dniLocal, nombreLocal, apellidoLocal, edadLocal, codTallerLocal);
        }
    }

    mostrarListaGeneral(dniLocal, nombreLocal, apellidoLocal, edadLocal, codTallerLocal, cantAlumnos);
}

/*
    La funcion listaPorDisciplina copia los datos de los arreglos originales a arreglos locales,
    los ordena por codigo de taller, apellido y nombre con ordenamiento por seleccion,
    y llama a mostrarListaPorDisciplina sin modificar los arreglos originales del main.
*/
void listaPorDisciplina(char dni[][15], char nombre[][30], char apellido[][30], int edad[], char codTaller[][10], int cantAlumnos)
{
    char dniLocal[30][15];
    char nombreLocal[30][30];
    char apellidoLocal[30][30];
    int edadLocal[30];
    char codTallerLocal[30][10];
    int menor;
    int comparacionTaller;
    int comparacionApellido;

    for (int i = 0; i < cantAlumnos; i++)
    {
        strcpy(dniLocal[i], dni[i]);
        strcpy(nombreLocal[i], nombre[i]);
        strcpy(apellidoLocal[i], apellido[i]);
        edadLocal[i] = edad[i];
        strcpy(codTallerLocal[i], codTaller[i]);
    }

    for (int i = 0; i < cantAlumnos - 1; i++)
    {
        menor = i;

        for (int j = i + 1; j < cantAlumnos; j++)
        {
            comparacionTaller = strcmp(codTallerLocal[j], codTallerLocal[menor]);

            if (comparacionTaller < 0)
            {
                menor = j;
            }
            else if (comparacionTaller == 0)
            {
                comparacionApellido = strcmp(apellidoLocal[j], apellidoLocal[menor]);

                if (comparacionApellido < 0 ||
                    (comparacionApellido == 0 && strcmp(nombreLocal[j], nombreLocal[menor]) < 0))
                {
                    menor = j;
                }
            }
        }

        if (menor != i)
        {
            intercambiarAlumnosLocal(i, menor, dniLocal, nombreLocal, apellidoLocal, edadLocal, codTallerLocal);
        }
    }

    mostrarListaPorDisciplina(dniLocal, nombreLocal, apellidoLocal, edadLocal, codTallerLocal, cantAlumnos);
}






