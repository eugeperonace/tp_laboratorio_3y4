#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this = NULL;
    this = malloc(sizeof(LinkedList));
    if(this != NULL)
    {
    	this->size = 0;
    	this->pFirstNode = NULL;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
    	returnAux = this->size;
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	Node* auxNodo = NULL;
	int indice;
	if(this != NULL && nodeIndex >= 0 && nodeIndex < ll_len(this))
	{
       auxNodo = this->pFirstNode;
       indice = 0;
       do
       {
    	   if(indice == nodeIndex)
    	   {
    		   break;
    	   }
    	   else
    	   {
    		   auxNodo = auxNodo->pNextNode;
    		   indice++;
    	   }
       }while(auxNodo != NULL);             //condición de corte que el prox node sea NULL.
	}
	return auxNodo;
}
/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
	int returnAux = -1;
	Node* auxNode = NULL;
	Node* auxNode2 = NULL;

	if(this != NULL && nodeIndex >= 0 && nodeIndex <= ll_len(this))
	{
		auxNode = (Node*) malloc(sizeof(Node));
		auxNode2 = (Node*) malloc(sizeof(Node));

		if(auxNode != NULL && auxNode2 != NULL)
		{
			auxNode->pElement = pElement;
			this->size++;
			returnAux = 0;

			if(nodeIndex == 0 )
			{
				auxNode->pNextNode = this->pFirstNode;
				this->pFirstNode = auxNode;
			}
			else if(nodeIndex == ll_len(this))
			{
				auxNode2 = getNode(this,nodeIndex-1);
				auxNode2->pNextNode = auxNode;
				auxNode->pNextNode = NULL;
			}
			else
			{
				auxNode2 = getNode(this,nodeIndex);
				auxNode->pNextNode = auxNode2;
				auxNode2= getNode(this,nodeIndex-1);
				auxNode2->pNextNode = auxNode;
			}
		}
	}
	return returnAux;
}


/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this != NULL)
    {
    	if( !addNode(this,ll_len(this),pElement))
    	{
    		returnAux = 0;
    	}
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* pNode;

    if(this != NULL && index >= 0 && index < ll_len(this))
    {
    	pNode = getNode(this,index);
   		returnAux = pNode->pElement;
   	}
    return returnAux;
 }


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* pNode;

    if(this != NULL && index >= 0 && index < ll_len(this))
    {
    	pNode = getNode(this,index);
    	pNode->pElement = pElement;
    	returnAux = 0;
    }
    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* nodeRemove;
    Node* auxNode;

    if(this != NULL && index >= 0 && index < ll_len(this))
    {
    	nodeRemove = getNode(this,index);
    	auxNode = getNode(this,index-1);

    	if(index == 0)
    	{
    		this->pFirstNode = nodeRemove->pNextNode;
    	}
    	else
    	{
    		auxNode->pNextNode = nodeRemove->pNextNode;
    	}

    	free(nodeRemove);
    	this->size--;
    	returnAux = 0;
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int i;

    if(this != NULL)
    {
    	for(i=0;i<ll_len(this);i++)
    	{
    		ll_remove(this,i);
    		this->pFirstNode = NULL;
    		this->size = 0;
    		returnAux = 0;
    	}
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
    	ll_clear(this);
    	free(this);
    	returnAux = 0;
    }
    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int i;
    Node* pNode;

    if(this != NULL)
    {
    	for(i=0;i<ll_len(this);i++)
    	{
    		pNode = getNode(this,i);

    		if(pNode->pElement == pElement)
    		{
    			returnAux = i;
    		}
    	}
   	}
    return returnAux;
}


/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
    	if(ll_len(this) == 0)
    	{
    		returnAux = 1;
    	}
    	else
    	{
    		returnAux = 0;
    	}
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;

    if(this != NULL && index >=0 && index <= ll_len(this))
    {
    	addNode(this,index,pElement);
    	returnAux = 0;
    }
    return returnAux;
}

/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    void* pElement;

    if(this != NULL && index >= 0 && index < ll_len(this))
    {
    	pElement = ll_get(this,index);
    	returnAux = pElement;
    	ll_remove(this,index);
    }
    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int i;
    void* pElemento;

    if(this != NULL)
    {
    	returnAux = 0;
    	for(i=0;i<ll_len(this);i++)
    	{
    		pElemento = ll_get(this,i);
    		if(pElemento == pElement)
    		{
    			returnAux = 1;
    			break;
    		}
    	}
    }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int i;
    void* pElement;

    if(this != NULL && this2 != NULL)
    {
    	returnAux = 0;
    	for(i=0;i<ll_len(this2);i++)
    	{
    		pElement = ll_get(this,i);
    		if(ll_contains(this2,pElement) == 1)
    		{
    			returnAux = 1;
    		}
    		else
    		{
    			returnAux = 0;
    		}
    	}
    }
    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    int i;
    void* pElement;

    if(this != NULL && from >= 0 && from < to && to >= 0 && to <= ll_len(this) && from <= ll_len(this))
    {
    	cloneArray = ll_newLinkedList();

    	for(i=from;i<to;i++)
    	{
    		pElement = ll_get(this,i);
    		if( !ll_add(cloneArray,pElement))
    		{
    			continue;
    		}
    	}
    }
    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;

    if(this != NULL)
    {
    	cloneArray = ll_newLinkedList();

    	if(ll_subList(this,0,ll_len(this)) != NULL)
    	{
    		cloneArray = ll_subList(this,0,ll_len(this));
    	}
    }
    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux = -1;
    int flagSwap;
    int i;
    int len;
    void* pElement;
    void* pElement2;
    int funcCriterio;
    void* buffer;

    if(this != NULL && pFunc != NULL && (order == 0 || order == 1))
    {
    	returnAux = 0;
    	len = ll_len(this)-1;
    	do
    	{
    		flagSwap = 0;

    		for(i=0;i<len;i++)
    		{
    			pElement = ll_get(this,i);
    			pElement2 = ll_get(this,i+1);

    			funcCriterio = pFunc(pElement,pElement2);

    			if((funcCriterio == 1 && order == 1) || (funcCriterio == -1 && order == 0))
    			{
    				flagSwap = 1;
    				buffer = pElement;
    				ll_set(this,i,pElement2);
    				ll_set(this,i+1,buffer);
    			}
    		}
    		len--;
    	}while(flagSwap);
    }
    return returnAux;
}

/** \brief Aplica una condición a la lista (mediante una función criterio pasada como parámetro)
 *         y realiza algo con los elementos de la misma.
 * \param this LinkedList* Puntero a la lista
 * \param int* pFuncArgumento Función criterio que determina qué es lo que se quiere hacer con los elementos de la lista.
 * \return int Retorna  -1 si el puntero a la lista es NULL
 *                       o 0 salió todo ok.
 */
int ll_map(LinkedList* this, int(*pFuncArgumento)(void*))
{
	int retorno = -1;
	int i;
	void* pElement;

	if(this != NULL && pFuncArgumento != NULL)
	{
		for(i=0;i<ll_len(this);i++)
		{
			pElement = ll_get(this,i);
			if(pFuncArgumento(pElement)==0)
			{
				retorno = 0;
			}
		}
	}
	return retorno;
}


/** \brief Filtra los elementos de la lista de acuerdo a la función criterio recibida como parámetro.
 *
 * \param this LinkedList* Puntero a la lista
 * \param int* pFuncArgumento Función criterio que determina qué es lo que se quiere hacer con los elementos de la lista.
 * \return int Retorna  NULL si el puntero a la lista es NULL
 *                       o un puntero a la lista filtrada si salió todo ok.
 */
LinkedList* ll_filter(LinkedList* this, int(*pFuncArgumento)(void*))
{
	LinkedList* listaFiltrada = NULL;
	int i;
	void* pElement;

	if(this != NULL && pFuncArgumento != NULL)
	{
		listaFiltrada = ll_newLinkedList();
		if (listaFiltrada != NULL)
		{
			for(i=0;i<ll_len(this);i++)
			{
				pElement = ll_get(this,i);
				if(pFuncArgumento(pElement)==1)
				{
					ll_add(listaFiltrada,pElement);
				}
			}
		}
	}
	return listaFiltrada;
}


/** \brief Cuenta los elementos de la lista de acuerdo a la función criterio recibida como parámetro.
 *
 * \param this LinkedList* Puntero a la lista
 * \param int* pFuncArgumento Función criterio que determina qué particularidad tienen loe elementos que voy a contar.
 * \return int Retorna  -1 si el puntero a la lista es NULL
 *                       o la cantidad total acumulada si salió todo ok.
 */
int ll_count(LinkedList* this, int(*pFuncArgumento)(void*))
{
	int i;
	void* pElement;
	int acum = 0;
	int retorno = -1;

	if(this != NULL && pFuncArgumento != NULL)
	{
		for(i=0;i<ll_len(this);i++)
		{
			pElement = ll_get(this,i);
			if(pFuncArgumento(pElement)==1)
			{
				acum = acum + pFuncArgumento(pElement);
				retorno = acum;
			}
		}
	}
	return retorno;
}
/** \brief Reduce la lista a un unico valor.
 * \param this LinkedList* Puntero a la lista
 * \param int* pFuncArgumento Función criterio que determina por qué voy a comparar mis elementos.
 * \return int Retorna  NULL si el puntero a la lista es NULL
 *                       o el valor si salió todo ok.
 */
int ll_reduce(LinkedList* this, int(*pFuncArgumento)(void*,int,int))
{
	int i;
	void* pElement = NULL;
	int valor = 0;

	if(this != NULL && pFuncArgumento != NULL)
	{
		for(i=0;i<ll_len(this);i++)
		{
			pElement = ll_get(this,i);
			valor = pFuncArgumento(pElement,valor,i);
		}
	}
	return valor;
}
