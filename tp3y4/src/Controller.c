#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "utn.h"
#include "Controller.h"

#define SUELDO_LEN 100
#define HORASTRAB_LEN 100
#define ID_LEN 100

static int buscarMaximoId(LinkedList* pArrayListEmployee, int* maximoId);

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	FILE* pFile;
	if(path != NULL && pArrayListEmployee != NULL)
	{
		pFile = fopen(path,"r");
		if( pFile != NULL &&
			parser_EmployeeFromText(pFile,pArrayListEmployee)==0)
		{
			retorno=0;
			printf("Archivo cargado exitosamente.\n");
			fclose(pFile);
		}
		else
		{
			printf("El archivo no logró cargarse.\n");
		}
	}
	return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	FILE* pFile;
	if(path != NULL && pArrayListEmployee != NULL)
	{
		pFile = fopen(path,"rb");
		if( pFile != NULL &&
			parser_EmployeeFromBinary(pFile,pArrayListEmployee)==0)
		{
			retorno=0;
			printf("Archivo cargado exitosamente.\n");
			fclose(pFile);
		}
		else
		{
			printf("El archivo no logró cargarse.\n");
		}
	}
	return retorno;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    char auxNombre[NOMBRE_LEN];
    int auxSueldo;
    int auxHorasTrabajadas;
    int auxId;
    Employee* pEmployee;

    if(pArrayListEmployee != NULL)
    {
    	if( !utn_getNombre(auxNombre,NOMBRE_LEN,"\nIngrese nombre?","\nNombre invalido.",2) &&           //Pido los datos.
    		!utn_getNumero(&auxSueldo,"Ingrese sueldo:\n","Sueldo inválido.\n",1,2000000,2) &&
			!utn_getNumero(&auxHorasTrabajadas,"Ingrese horas trabajadas:\n","Horas trabajadas inválidas.\n",1,2000,2))
		{
    		if(ll_len(pArrayListEmployee)==0)
    		{
    			auxId = 0;
    		}
    		else
    		{
    			buscarMaximoId(pArrayListEmployee,&auxId);                                     //Busco el Id mayor y lo incremento en 1.
    			auxId = auxId+1;
    		}
    		if( employee_newParametros(auxId,auxNombre,auxHorasTrabajadas,auxSueldo) != NULL)  //Creo un empleado con los datos que recibí.
    		{
    			pEmployee = employee_newParametros(auxId,auxNombre,auxHorasTrabajadas,auxSueldo);
    			ll_add(pArrayListEmployee,pEmployee);                                          //Agrego ese empleado a mi LinkedList.
    			retorno = 0;
    			printf("\nEmpleado con ID: %d dado de alta correctamente.\n", auxId);
    		}
		}
    }
    return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int auxId;
	int indiceEmp;
	char auxNombre[NOMBRE_LEN];
	int auxSueldo;
	int auxHorasTrabajadas;
	Employee* pEmployee;

	if(pArrayListEmployee != NULL)
	{
		controller_ListEmployee(pArrayListEmployee);
		utn_getNumero(&auxId,"\nIngrese el ID del empleado a modificar: \n","ID inválido.\n",0,ll_len(pArrayListEmployee),2);

		indiceEmp = buscarIndicePorId(pArrayListEmployee,auxId);  //Busco la posición en la que se encuentra ese ID
		pEmployee = ll_get(pArrayListEmployee,indiceEmp);         //Consigo el puntero al empleado a quien corresponde esa posición de mi LinkedList.
		if (pEmployee != NULL)
		{
			if( !utn_getNombre(auxNombre,NOMBRE_LEN,"\nIngrese nombre?","\nNombre invalido.",2) &&
				!utn_getNumero(&auxSueldo,"Ingrese sueldo:\n","Sueldo inválido.\n",1,2000000,2) &&
				!utn_getNumero(&auxHorasTrabajadas,"Ingrese horas trabajadas:\n","Horas trabajadas inválidas.\n",1,2000,2))
			{
				retorno = 0;
				employee_setNombre(pEmployee,auxNombre);
				employee_setSueldo(pEmployee,auxSueldo);
				employee_setHorasTrabajadas(pEmployee,auxHorasTrabajadas);
			}
			printf("\nEl empleado con ID: %d fue modificado correctamente.\n", auxId);
		}
	}
	return retorno;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int auxId;
    int indiceEmp;
    Employee* pEmployee;

    if(pArrayListEmployee != NULL)
    {
    	controller_ListEmployee(pArrayListEmployee);
    	utn_getNumero(&auxId,"\nIngrese el ID del empleado a eliminar: \n","ID inválido.\n",0,ll_len(pArrayListEmployee),2);

    	indiceEmp = buscarIndicePorId(pArrayListEmployee,auxId);    //Busco la posición en la que se encuentra ese ID
    	pEmployee = ll_get(pArrayListEmployee,indiceEmp);           //Consigo el puntero al empleado a quien corresponde esa posición de mi LinkedList.
    	if (pEmployee != NULL)
    	{
    		retorno = 0;
    		employee_delete(pEmployee);                             //Elimino al empleado de memoria.
    		ll_remove(pArrayListEmployee,indiceEmp);                //Elimino de mi LinkedList el indice que correspondía a ese empleado que ya no existe.
    	}
    	printf("El empleado con ID: %d fue eliminado correctamente.\n",auxId);
    }
    return retorno;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int i;
	Employee* pEmployee;
	char auxNombre[NOMBRE_LEN];
	char auxId[ID_LEN];
	char auxSueldo[SUELDO_LEN];
	char auxHorasTrabajadas[HORASTRAB_LEN];

    if(pArrayListEmployee != NULL)
    {
    	for(i=0;i<ll_len(pArrayListEmployee);i++)
    	{
    		pEmployee = ll_get(pArrayListEmployee,i);
    		if(pEmployee != NULL)
    		{
    			retorno = 0;
    			employee_getNombre(pEmployee,auxNombre);
    			employee_getIdTxt(pEmployee,auxId);
    			employee_getSueldoTxt(pEmployee,auxSueldo);
    			employee_getHorasTrabajadasTxt(pEmployee,auxHorasTrabajadas);
    			printf("ID: %s - NOMBRE: %s - HORAS TRABAJADAS: %s - SUELDO: %s.\n",auxId,auxNombre,auxHorasTrabajadas,auxSueldo);
    		}
    	}
    }
    return retorno;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int formaOrdenar;

	if(pArrayListEmployee != NULL)
	{
		utn_getNumero(&formaOrdenar,"¿Cómo desea ordenar la lista? [1/ASCENDENTE-0/DESCENDENTE]\n","Opción inválida.\n",0,1,2);
		if(ll_sort(pArrayListEmployee,employee_funcionOrdenarNombre,formaOrdenar)==0)
		{
			printf("La lista fue ordenada con éxito.\n");
			controller_ListEmployee(pArrayListEmployee);
			return 0;
		}
	}
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int i;
    FILE* pFile;
    Employee* pEmployee;
    int auxId;
    char auxNombre[NOMBRE_LEN];
	int auxSueldo;
	int auxHorasTrab;

    if(path != NULL && pArrayListEmployee != NULL)
    {
    	pFile = fopen(path,"w");
    	if(pFile != NULL)
    	{
    		retorno = 0;
    		for(i=0;i<ll_len(pArrayListEmployee);i++)
    		{
    			pEmployee = (Employee*) ll_get(pArrayListEmployee,i);
    			if(pEmployee != NULL)
    			{
    				if ( !employee_getId(pEmployee,&auxId) &&
    					 !employee_getNombre(pEmployee,auxNombre) &&
    					 !employee_getSueldo(pEmployee,&auxSueldo) &&
    					 !employee_getHorasTrabajadas(pEmployee,&auxHorasTrab))
						 {
    						fprintf(pFile,"%d,%s,%d,%d\n",auxId,auxNombre,auxHorasTrab,auxSueldo);
						 }
    			}
    		}
    		fclose(pFile);
    		printf("Archivo generado exitosamente.\n");
    	}
    	else
    	{
    		printf("No logró generarse el archivo.\n");
    	}

    }
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	FILE* pFile;
	int i;
	Employee* pEmployee;

	if(path != NULL && pArrayListEmployee != NULL)
	{
		pFile = fopen(path,"wb");
		if(pFile != NULL)
		{
			for(i=0;i<ll_len(pArrayListEmployee);i++)
			{
				pEmployee = ll_get(pArrayListEmployee,i);
				if(pEmployee != NULL)
				{
					if(fwrite(pEmployee,sizeof(Employee),1,pFile) == 1)
					{
						retorno = 0;
					}
				}
			}
			fclose(pFile);
		}
		printf("Archivo generado exitosamente.\n");
   	}
	return retorno;
}

/** \brief Busca el Id máximo correspondientes a los empleados.
 *
 * \param pArrayListEmployee LinkedList*
 * \param maximoId int*
 * \return int
 *
 */
static int buscarMaximoId(LinkedList* pArrayListEmployee, int* maximoId)
{
	int retorno = -1;
	int i;
	Employee* pEmployee;
	int auxId;
	int auxIdMaximo;
	int flag = 0;
	if(pArrayListEmployee != NULL && maximoId != NULL)
	{
		retorno = 0;
		for(i=0;i<ll_len(pArrayListEmployee);i++)
		{
			if(flag==0)
			{
				pEmployee = ll_get(pArrayListEmployee,i);
				employee_getId(pEmployee,&auxIdMaximo);
				flag = 1;
			}
			else
			{
				pEmployee = ll_get(pArrayListEmployee,i);
				employee_getId(pEmployee,&auxId);
				if(auxId >= auxIdMaximo)
				{
					auxIdMaximo = auxId;
				}
			}
		}
		*maximoId = auxIdMaximo;
	}
	return retorno;
}

/** \brief Busca la posición de mi LinkedList en la que se encuentra el empleado
 *   correspondiente al ID que le paso.
 * \param pArrayListEmployee LinkedList*
 * \param idModif int*
 * \return int
 *
 */
int buscarIndicePorId(LinkedList* pArrayListEmployee, int idModif)
{
	int retorno = -1;
	int i;
	int auxId;
	Employee* pEmployee;
	if(pArrayListEmployee !=NULL && idModif >= 0)
	{
		retorno = -2;
		for(i=0;i<ll_len(pArrayListEmployee);i++)
		{
			pEmployee = ll_get(pArrayListEmployee,i);  //Busco en mi LinkedList el puntero al empleado de la posición i.
			employee_getId(pEmployee,&auxId);          //Obtengo el ID del empleado de la posición i.

			if(auxId == idModif)                       //Si el ID que obtuve es igual al que quiero modificar, devuelvo el indice en donde se encuentra.
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}
