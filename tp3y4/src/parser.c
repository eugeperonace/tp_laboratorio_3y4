#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include <string.h>

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	char auxId[4096];
	char auxNombre[4096];
	char auxHorasTrabajadas[4096];
	char auxSueldo[4096];
	Employee* pEmployee;

	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",auxId,auxNombre,auxHorasTrabajadas,auxSueldo) == 4) //Leo el contenido del archivo y lo guardo en variables aux.
			{
				pEmployee = employee_newParametrosTxt(auxId,auxNombre,auxHorasTrabajadas,auxSueldo);         //Creo un empleado con los datos que leí.
				if (pEmployee != NULL)
				{
					if(ll_add(pArrayListEmployee,pEmployee)==0)                                              //Agrego a mi Linkedlist el puntero del empleado que creé .
					{
						retorno = 0;
					}
				}
			}
		}while(!feof(pFile));                                                                               //Mientras feof() devuelva 0 significa que hay contenido por leer.
	}
	return retorno;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	char auxId[4096];
	char auxNombre[4096];
	char auxHorasTrabajadas[4096];
	char auxSueldo[4096];
	Employee auxEmployee;
	Employee* pEmployee;

	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		do
		{
			if(fread(&auxEmployee,sizeof(Employee),1,pFile)==1)                                               //Leo el contenido del archivo y lo guardo en una variable variable de tipo Employee para poder acceder a sus campos.
			{
				strcpy(auxNombre,auxEmployee.nombre);                                                         //Copio los datos leídos en variables auxiliares.
				sprintf(auxId,"%d",auxEmployee.id);
				sprintf(auxSueldo,"%d",auxEmployee.sueldo);
				sprintf(auxHorasTrabajadas,"%d",auxEmployee.horasTrabajadas);

				pEmployee = employee_newParametrosTxt(auxId,auxNombre,auxHorasTrabajadas,auxSueldo);         //Creo un empleado con los datos que leí.
				if (pEmployee != NULL)
				{
					if(ll_add(pArrayListEmployee,pEmployee)==0)                                              //Agrego a mi Linkedlist el puntero del empleado que creé .
					{
						retorno = 0;
					}
				}
			}
		}while(!feof(pFile));                                                                               //Mientras feof() devuelva 0 significa que hay contenido por leer.
	}
	return retorno;
}
