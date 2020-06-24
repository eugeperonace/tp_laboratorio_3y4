#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
#define NOMBRE_LEN 128

typedef struct
{
    int id;
    char nombre[NOMBRE_LEN];
    int horasTrabajadas;
    int sueldo;
}Employee;

Employee* employee_new();
Employee* employee_newParametrosTxt(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* sueldoStr);
Employee* employee_newParametros(int id,char* nombreStr,int horasTrabajadas,int sueldo);
void employee_delete(Employee* this);

int employee_setId(Employee* this,int id);
int employee_getId(Employee* this,int* id);
int employee_setIdTxt(Employee* this,char* id);
int employee_getIdTxt(Employee* this,char* id);

int employee_setNombre(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);
int employee_setHorasTrabajadasTxt(Employee* this,char* horasTrabajadas);
int employee_getHorasTrabajadasTxt(Employee* this,char* horasTrabajadas);

int employee_setSueldo(Employee* this,int sueldo);
int employee_getSueldo(Employee* this,int* sueldo);
int employee_setSueldoTxt(Employee* this,char* sueldo);
int employee_getSueldoTxt(Employee* this,char* sueldo);

int employee_funcionOrdenarNombre(void* item1, void* item2);

int calcularEmpleadosSueldoMayorA50000(void* pElement);
int calcularEmpleadosHorasMenorA100(void* pElement);

int employee_imprimirEmp(void* pElement);
int compararSueldoPorMayor(void* pElemento, int mayor, int index);
int compararSueldoPorMenor(void* pElemento, int menor, int index);

#endif // employee_H_INCLUDED

