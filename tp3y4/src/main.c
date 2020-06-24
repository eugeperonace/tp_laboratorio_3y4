#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "utn.h"

/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/



int main()
{
	setbuf(stdout,NULL);
    int option = 0;
    LinkedList* listaEmpleados = ll_newLinkedList();
    LinkedList* listaClonada;
    LinkedList* listaFiltrada;
    LinkedList* subLista;
    int from;
    int to;
    int contadorEmp;
    int indice;
    int auxId;
    int auxContains;
    int isEmpty;
    int index;
    char nombre[NOMBRE_LEN];
    Employee* pEmp;
    int mayorSueldo;
    int menorSueldo;


    do{
    	utn_getNumero(&option,
    			"\nElija una opción:\n"
    			"1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).\n"
    			"2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).\n"
    			"3. Alta de empleado.\n"
    			"4. Modificar datos de empleado.\n"
    			"5. Baja de empleado.\n"
    			"6. Listar empleados.\n"
    			"7. Ordenar empleados.\n"
    			"8. Guardar los datos de los empleados en el archivo data.csv (modo texto).\n"
    			"9. Guardar los datos de los empleados en el archivo data.csv (modo binario).\n"
    			"10. Averguar en qué posición de la lista se encuentra X empleado.\n"
    			"11. Determinar si la lista de empleados está vacía o no.\n"
    			"12. Eliminar empleado de la lista y de memoria.\n"
    			"13. Crear una sublista de empleados.\n"
    			"14. Determinar si los elementos de la sublista se encuentran contenidos en la lista de empleados.\n"
    			"15. Clonar lista de empleados.\n"
    			"16. Filtar empleados que tienen un sueldo superior a $50.000,00.\n"
    			"17. Cantidad de empleados con sueldo superior a $50.000,00.\n"
    			"18. Cantidad de empleados que trabajan menos de 100 horas.\n"
    			"19. Calcular el sueldo más alto.\n"
    			"20. Calcular el sueldo más bajo.\n"
    			"21. Salir.\n","Error\n",1,20,2);

        switch(option)
        {
            case 1:
            	controller_loadFromText("data.csv",listaEmpleados);
                break;
            case 2:
            	controller_loadFromBinary("dataBin.csv",listaEmpleados);
               break;
            case 3:
            	controller_addEmployee(listaEmpleados);
                break;
            case 4:
            	controller_editEmployee(listaEmpleados);
                break;
            case 5:
            	controller_removeEmployee(listaEmpleados);
                break;
            case 6:
            	controller_ListEmployee(listaEmpleados);
                break;
            case 7:
            	controller_sortEmployee(listaEmpleados);
                break;
            case 8:
            	controller_saveAsText("data.csv",listaEmpleados);
            	break;
            case 9:
            	controller_saveAsBinary("dataBin.csv",listaEmpleados);
                break;
            case 10:
            	controller_ListEmployee(listaEmpleados);
            	if( !utn_getNumero(&auxId,"\nIngrese el ID del empleado para saber en qué posición de la lista se encuentra: \n","ID inválido.\n",0,ll_len(listaEmpleados),2))
            	{
            	   indice = buscarIndicePorId(listaEmpleados,auxId);
            	   if (ll_get(listaEmpleados,indice) != NULL)
            	   {
            		   pEmp = (Employee*) ll_get(listaEmpleados,indice);
            		   index = ll_indexOf(listaEmpleados,pEmp);
            		   employee_getNombre(pEmp,nombre);
            		   printf("El empleado %s se encuentras en la posición [%d] de la lista.\n",nombre,index);
            	   }
            	}
                break;

            case 11:
            	isEmpty = ll_isEmpty(listaEmpleados);
            	if(isEmpty)
            	{
            		printf("La lista de empleados se encuentra vacía.\n");
            	}
            	else if(isEmpty == 0)
            	{
            		printf("La lista de empleados NO está vacía.\n");
            	}
            	else
            	{
            		printf("[ERROR] El puntero a la lista es NULL.");
            	}
                break;

            case 12:
            	controller_ListEmployee(listaEmpleados);
            	if( !utn_getNumero(&auxId,"\nIngrese el ID del empleado a eliminar: \n","ID inválido.\n",0,ll_len(listaEmpleados),2))
            	{
            		indice = buscarIndicePorId(listaEmpleados,auxId);
            		pEmp = (Employee*) ll_pop(listaEmpleados,indice);
            		if(pEmp != NULL)
            		{
            			employee_delete(pEmp);
            			printf("El empleado fue eliminado de la lista y de memoria correctamente.\n");
            		}
            	}
                break;

            case 13:
            	if( !utn_getNumero(&from,"¿Desde qué índice desea que comience la sublist?","Index inválido.\n",0,ll_len(listaEmpleados),2) &&
                    !utn_getNumero(&to,"¿Hasta qué índice desea que abarque la sublist?","Index inválido.\n",0,ll_len(listaEmpleados),2))
            	{
            		if( ll_subList(listaEmpleados,from,to) != NULL)
            		{
            			subLista = ll_subList(listaEmpleados,from,to);
            			printf("\n---SUBLISTA DE EMPLEADOS DESDE INDEX %d hasta el INDEX %d---\n",from,to);
            			ll_map(subLista,employee_imprimirEmp);
            		}
            	}
            	break;

            case 14:
            	auxContains = ll_containsAll(listaEmpleados,subLista);
            	if(auxContains == 1)
            	{
            		printf("Los elemento de la sub lista se encuentran contenidos en la lista de empleados.\n");
            	}
            	else if(auxContains == 0)
            	{
            		printf("Los elemento de la sub lista NO se encuentran contenidos en la lista de empleados.\n");
            	}
            	else
            	{
            		printf("[ERROR] Alguno de los punteros a las listas es NULL.\n");
            	}
                break;

            case 15:
            	listaClonada = ll_clone(listaEmpleados);
            	if(listaClonada != NULL)
            	{
            		printf("La lista ha sido clonada exitosamente.\n\n");
            		ll_map(listaClonada,employee_imprimirEmp);
            	}
                break;

            case 16:
            	listaFiltrada = ll_filter(listaEmpleados,calcularEmpleadosSueldoMayorA50000);
            	if(listaFiltrada != NULL)
            	{
            		printf("---LISTA DE EMPLEADOS CON SUELDO SUPERIOR A $50.000,00---\n\n");
            		ll_map(listaFiltrada,employee_imprimirEmp);
            	}
                 break;

            case 17:
            	contadorEmp = ll_count(listaEmpleados,calcularEmpleadosSueldoMayorA50000);
            	printf("La lista cuenta con %d empleados quienes tienen sueldo igual o superior a $50.000,00.\n", contadorEmp);
            	break;
            case 18:
            	contadorEmp = ll_count(listaEmpleados,calcularEmpleadosHorasMenorA100);
            	printf("La lista cuenta con %d empleados quienes trabajan menos de 100 horas.\n", contadorEmp);
            	break;
            case 19:
            	if ( ll_reduce(listaEmpleados,compararSueldoPorMayor) > 0)
            	{
            		mayorSueldo = ll_reduce(listaEmpleados,compararSueldoPorMayor);
            		printf("El sueldo más alto es de: [$%d].\n", mayorSueldo);
            	}
                break;
            case 20:
                if ( ll_reduce(listaEmpleados,compararSueldoPorMenor) > 0)
              	{
              		menorSueldo = ll_reduce(listaEmpleados,compararSueldoPorMenor);
               		printf("El sueldo más bajo es de: [$%d].\n", menorSueldo);
              	}
                break;
        }
    }while(option != 21);
    return 0;
}

