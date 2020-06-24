/*
 * Employee.c
 *
 *  Created on: May 9, 2020
 *      Author: Eugenia
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "Employee.h"

#define SUELDO_LEN 100
#define HORASTRAB_LEN 100
#define ID_LEN 100

static int isValidNombre(char* cadena,int longitud);
static int esNumerica(char* cadena, int limite);


/** \brief Crea un espacio de memoria para un empleado.
 * \param void() no recibe parámetros.
 * \return devuelve un puntero al empleado creado.
 *
 */
Employee* employee_new()
{
	Employee* auxiliarP = NULL;
	auxiliarP = (Employee*) malloc(sizeof(Employee));
	return auxiliarP;
}


/** \brief Crea un empleado con sus campos, recibiendo los datos como String.
 * \param idStr char*
 * \param nombreStr char*
 * \param horasTrabajadasStr char*
 * \param sueldoStr char*
 * \return devuelve un puntero al empleado creado.
 *
 */
Employee* employee_newParametrosTxt(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr)
{
	Employee* this = NULL;
	this = employee_new();
	if(this != NULL && idStr != NULL && nombreStr != NULL && horasTrabajadasStr != NULL && sueldoStr != NULL)
	{
		if(	employee_setIdTxt(this,idStr) == -1 ||
			employee_setNombre(this,nombreStr) == -1 ||
			employee_setHorasTrabajadasTxt(this, horasTrabajadasStr) == -1 ||
			employee_setSueldoTxt(this,sueldoStr) )
		{
			employee_delete(this);
			this = NULL;
		}
	}
	return this;
}


/** \brief Crea un empleado con sus campos.
 * \param id int
 * \param nombre char*
 * \param horasTrabajadas int
 * \param sueldo int
 * \return devuelve un puntero al empleado creado.
 *
 */
Employee* employee_newParametros(int id,char* nombre,int horasTrabajadas, int sueldo)
{
	Employee* this = NULL;
	this = employee_new();
	if(this != NULL && id >= 0 && nombre != NULL && horasTrabajadas >= 0 && sueldo >= 0)
	{
		if(	employee_setId(this,id) == -1 ||
			employee_setNombre(this,nombre) == -1 ||
			employee_setHorasTrabajadas(this, horasTrabajadas) == -1 ||
			employee_setSueldo(this,sueldo) )
		{
			employee_delete(this);
			this = NULL;
		}
	}
	return this;
}


/** \brief Elimina a un empleado de memoria.
 * \param this Employee* recibe como param. el puntero al empleado a eliminar.
 * \return void.
 *
 */
void employee_delete(Employee* this)
{
	if(this != NULL)
	{
		free(this);
	}
}


/** \brief Escribe el Id recibido, en el campo Id del empleado recibido por parámetro.
 * \param this Employee*
 * \param id int
 * \return int
 *
 */
int employee_setId(Employee* this,int id)
{
	int retorno = -1;
	if(this != NULL && id >= 0)
	{
		retorno = 0;
		this->id = id;
	}
	return retorno;
}


/** \brief Obtiene el id del empleado correspondiente a la dirección de memoria que le paso por parametros.
 * \param this Employee* puntero al empleado.
 * \param id int*
 * \return int
 *
 */
int employee_getId(Employee* this,int* id)
{
	int retorno = -1;
	if(this != NULL && id != NULL)
	{
		retorno = 0;
		*id = this->id;
	}
	return retorno;
}

/** \brief Escribe el Id recibido (como string), en el campo Id del empleado recibido por parámetro.
 * \param this Employee*
 * \param id char*
 * \return int
 *
 */
int employee_setIdTxt(Employee* this,char* id)
{
	int retorno = -1;
	if(this != NULL && id != NULL)
	{
		if(esNumerica(id,10))
		{
			retorno = 0;
			this->id = atoi(id);
		}
	}
	return retorno;
}


/** \brief Obtiene el id (como string) del empleado correspondiente a la dirección de memoria que le paso por parametros.
 * \param this Employee* puntero al empleado.
 * \param id char*
 * \return int
 *
 */
int employee_getIdTxt(Employee* this,char* id)
{
	int retorno = -1;
	if(this != NULL && id != NULL)
	{
		retorno = 0;
		sprintf(id,"%d",this->id);
	}
	return retorno;
}


/** \brief Escribe las horas trabajadas recibidas (como string), en el campo horasTrabajadas
 *   del empleado recibido por parámetro.
 * \param this Employee*
 * \param horasTrabajadas char*
 * \return int
 *
 */
int employee_setHorasTrabajadasTxt(Employee* this,char* horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && horasTrabajadas != NULL)
	{
		if(esNumerica(horasTrabajadas,10))
		{
			retorno = 0;
			this->horasTrabajadas = atoi(horasTrabajadas);
		}
	}
	return retorno;
}


/** \brief Obtiene las horas trabajadas (como string) del empleado correspondiente
 * a la dirección de memoria que le paso por parametros.
 * \param this Employee* puntero al empleado.
 * \param horasTrabajadas char*
 * \return int
 *
 */
int employee_getHorasTrabajadasTxt(Employee* this,char* horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && horasTrabajadas != NULL)
	{
		retorno = 0;
		sprintf(horasTrabajadas,"%d",this->horasTrabajadas);
	}
	return retorno;
}


/** \brief Escribe el sueldo recibido (como string), en el campo sueldo del empleado recibido por parámetro.
 * \param this Employee*
 * \param sueldo int
 * \return int
 *
 */
int employee_setSueldoTxt(Employee* this,char* sueldo)
{
	int retorno = -1;
	if(this != NULL && sueldo != NULL)
	{
		if(esNumerica(sueldo,10))
		{
			retorno = 0;
			this->sueldo = atoi(sueldo);
		}
	}
	return retorno;
}


/** \brief Obtiene el sueldo (como string) del empleado correspondiente
 * a la dirección de memoria que le paso por parametros.
 * \param this Employee* puntero al empleado.
 * \param sueldo char*
 * \return int
 *
 */
int employee_getSueldoTxt(Employee* this,char* sueldo)
{
	int retorno = -1;
	if(this != NULL && sueldo != NULL)
	{
		retorno = 0;
		sprintf(sueldo,"%d",this->sueldo);
	}
	return retorno;
}


/** \brief Escribe el nombre recibido, en el campo nombre del empleado recibido por parámetro.
 * \param this Employee*
 * \param nombre char*
 * \return int
 *
 */
int employee_setNombre(Employee* this,char* nombre)
{
	int retorno = -1;
		if(this != NULL && nombre != NULL)
		{
			if(isValidNombre(nombre,NOMBRE_LEN))
			{
				retorno = 0;
				strncpy(this->nombre,nombre,NOMBRE_LEN);
			}
		}
		return retorno;
}


/** \brief Obtiene el nombre del empleado correspondiente
 * a la dirección de memoria que le paso por parametros.
 * \param this Employee* puntero al empleado.
 * \param nombre char*
 * \return int
 *
 */
int employee_getNombre(Employee* this,char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL)
	{
		retorno = 0;
		strncpy(nombre,this->nombre,NOMBRE_LEN);
	}
	return retorno;
}


/** \brief Escribe las horas trabajadas recibidas, en el campo horasTrabajadas
 *   del empleado recibido por parámetro.
 * \param this Employee*
 * \param horasTrabajadas int
 * \return int
 *
 */
int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && horasTrabajadas >= 0)
	{
		retorno = 0;
		this->horasTrabajadas = horasTrabajadas;
	}
	return retorno;
}


/** \brief Obtiene las horas trabajadas del empleado correspondiente
 * a la dirección de memoria que le paso por parametros.
 * \param this Employee* puntero al empleado.
 * \param horasTrabajadas int*
 * \return int
 *
 */
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && horasTrabajadas != NULL)
	{
		retorno = 0;
		*horasTrabajadas = this->horasTrabajadas;
	}
	return retorno;
}


/** \brief Escribe el sueldo recibido, en el campo sueldo del empleado recibido por parámetro.
 * \param this Employee*
 * \param sueldo int
 * \return int
 *
 */
int employee_setSueldo(Employee* this,int sueldo)
{
	int retorno = -1;
	if(this != NULL && sueldo >= 0)
	{
		retorno = 0;
		this->sueldo = sueldo;
	}
	return retorno;
}


/** \brief Obtiene el sueldo del empleado correspondiente
 * a la dirección de memoria que le paso por parametros.
 * \param this Employee* puntero al empleado.
 * \param sueldo int*
 * \return int
 *
 */
int employee_getSueldo(Employee* this,int* sueldo)
{
	int retorno = -1;
	if(this != NULL && sueldo != NULL)
	{
		retorno = 0;
		*sueldo = this->sueldo;
	}
	return retorno;
}

/**
 * \brief Verifica si la cadena ingresada es un nombre valido
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 *
 */
static int isValidNombre(char* cadena,int longitud)
{
	int i=0;
	int retorno = 1;

	if(cadena != NULL && longitud > 0)
	{
		for(i=0 ; cadena[i] != '\0' && i < longitud; i++)
		{
			if((cadena[i] < 'A' || cadena[i] > 'Z' ) && (cadena[i] < 'a' || cadena[i] > 'z' ))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Verifica si la cadena ingresada es numerica
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 (verdadero) si la cadena es numerica, 0 (falso) si no lo es y -1 en caso de error
 *
 */
static int esNumerica(char* cadena, int limite)
{
	int retorno = -1; // ERROR
	int i;
	if(cadena != NULL && limite > 0)
	{
		retorno = 1; // VERDADERO
		for(i=0;i<limite && cadena[i] != '\0';i++)
		{
			if(i==0 && (cadena[i] == '+' || cadena[i] == '-'))
			{
				continue;
			}
			if(cadena[i] < '0'||cadena[i] > '9')
			{
				retorno = 0;
				break;
			}
			//CONTINUE
		}
		//BREAK
	}
	return retorno;
}

/**
 * \brief Ordena por nombre
 * \param emp1 void* puntero al empleado1 que se quiere ordenar
 * \param emp1 void* puntero al empleado2 que se quiere ordenar
 * \return Retorna 0 (si son iguales), 1 (si nombre1 es mayor que nombre2) y -1 (si nombre1 es menor que nombre2)
 *
 */
int employee_funcionOrdenarNombre(void* emp1, void* emp2)
{
	int retorno = 0;
	Employee* employee1;
	Employee* employee2;
	char nombre1[NOMBRE_LEN];
	char nombre2[NOMBRE_LEN];

	employee1 = (Employee*) emp1;  //Cargo la direccion de memoria del empleado en variables del tipo Employee*
	employee2 = (Employee*) emp2;

	if(emp1 != NULL && emp2 != NULL)
	{
		if ( !employee_getNombre(employee1,nombre1) &&
			 !employee_getNombre(employee2,nombre2))
		{
			if(strncmp(nombre1,nombre2,NOMBRE_LEN)>0)
			{
				retorno = 1;
			}
			else if(strncmp(nombre1,nombre2,NOMBRE_LEN)<0)
			{
				retorno = -1;
			}
		}
	}

	return retorno;
}


/** \brief Imprime el empleado pasado como parámetro.
 *
 * \param this void*
 * \return int
 *
 */
int employee_imprimirEmp(void* pElement)
{
	int retorno = -1;
	Employee* pEmployee = (Employee*) pElement;
	char auxNombre[NOMBRE_LEN];
	char auxId[ID_LEN];
	char auxSueldo[SUELDO_LEN];
	char auxHorasTrabajadas[HORASTRAB_LEN];

	if(pEmployee != NULL)
    {
    	retorno = 0;
    	employee_getNombre(pEmployee,auxNombre);
    	employee_getIdTxt(pEmployee,auxId);
    	employee_getSueldoTxt(pEmployee,auxSueldo);
    	employee_getHorasTrabajadasTxt(pEmployee,auxHorasTrabajadas);
    	printf("ID: %s - NOMBRE: %s - HORAS TRABAJADAS: %s - SUELDO: %s.\n",auxId,auxNombre,auxHorasTrabajadas,auxSueldo);
    }
	return retorno;
 }

/** \brief Calcula el empleado que tiene un sueldo mayor a $50.000.
 *
 * \param pElement void* puntero al elemento a ser evaluado.
 * \return int (-1) NULL (1) si tiene sueldo mayor a 50000 (0) si no tiene sueldo mayor a 50000
 *
 */
int calcularEmpleadosSueldoMayorA50000(void* pElement)
{
	int retorno = -1;
	Employee* pEmployee;
	pEmployee = (Employee*) pElement;
	int auxSueldo;

	if(pElement != NULL)
	{
		employee_getSueldo(pEmployee,&auxSueldo);
		if(auxSueldo >= 50000)
		{
			retorno = 1;
		}
		else
		{
			retorno = 0;
		}
	}
	return retorno;
}

/** \brief Calcula el empleado que trabaja menos de 100 hs.
 *
 * \param pElement void* puntero al elemento a ser evaluado.
 * \return int
 *
 */
int calcularEmpleadosHorasMenorA100(void* pElement)
{
	int retorno = -1;
	Employee* pEmployee;
	pEmployee = (Employee*) pElement;
	int auxHorasTrab;

	if(pElement != NULL)
	{
		employee_getHorasTrabajadas(pEmployee,&auxHorasTrab);
		if(auxHorasTrab < 100)
		{
			retorno = 1;
		}
		else
		{
			retorno = 0;
		}
	}
	return retorno;
}

/** \brief Compara el sueldo de un elemento con el sueldo mayor.
 *
 * \param pElement void* puntero al elemento a ser evaluado.
 * \return int retorna el sueldo mayor
 *
 */
int compararSueldoPorMayor(void* pElemento, int mayor, int index)
{
	Employee* pEmp = (Employee*) pElemento;
	if(pElemento != NULL && mayor >=0)
	{
		if(index==0)
		{
			mayor = pEmp->sueldo;
		}
		else if(pEmp->sueldo > mayor)
		{
			mayor = pEmp->sueldo;
		}
	}
	return mayor;
}

/** \brief Compara el sueldo de un elemento con el sueldo menor.
 *
 * \param pElement void* puntero al elemento a ser evaluado.
 * \return int retorna el sueldo menor
 *
 */
int compararSueldoPorMenor(void* pElemento, int menor, int index)
{
	Employee* pEmp = (Employee*) pElemento;
	if(pElemento != NULL && menor >=0)
	{
		if(index==0)
		{
			menor = pEmp->sueldo;
		}
		else if(pEmp->sueldo < menor)
		{
			menor = pEmp->sueldo;
		}
	}
	return menor;
}

