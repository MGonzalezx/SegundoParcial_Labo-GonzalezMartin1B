#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "LinkedList.h"
#include "Libro.h"
#include "Editorial.h"
#include "parser.h"
#include "Biblioteca.h"

/** \brief Parsea  los datos de los libros desde el archivo (modo texto).
 *
 * \param pFile FILE* Archivo  abierto en modo lectura.
 * \param pArrayListLibro LinkedList* Lista linkeada donde se ubican los datos.
 * \return int Devuelve 0 si se realizo o 1 en caso de puntero NULL.
 *
 */
int parser_LibroFromText(FILE* pFile , LinkedList* pArrayListLibro)
{

	eLibro* pLibro = NULL;
	eLibro* pAuxLibro = NULL;
	int cantidadDeDatosLeidos;
	char id[15];
	char titulo[128];
	char autor[128];
	char precio[15];
	char idEditorial[15];
	int retorno = 1;
	FILE* archivoUltimoId;
	int lastId;
	int mayor;

	if(pArrayListLibro != NULL)
	{
		while(!feof(pFile))
		{
			cantidadDeDatosLeidos = fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^\n]\n", id, titulo, autor, precio, idEditorial);
			if(cantidadDeDatosLeidos == 5 && isdigit(id[0]) != 0)
			{
				pLibro = eLibro_newParametros(id, titulo, autor, precio, idEditorial);
				if(pLibro != NULL)
				{
					ll_add(pArrayListLibro, pLibro);
				}
			}

		}

		archivoUltimoId = fopen("ultimo_id.txt","r");
		if(archivoUltimoId == NULL)
		{
			for(int i = 0; i <ll_len(pArrayListLibro); i++ )
			{
				pAuxLibro = ll_get(pArrayListLibro, i);
				//printf("%d\n", pAuxEmployee->id);
				eLibro_getId(pAuxLibro,&lastId);
				if( i == 0 || mayor < lastId)
				{

					mayor = lastId;
					//printf("%d\n", mayor);
				}
			}
			archivoUltimoId = fopen("ultimo_id.txt","w");
			if(archivoUltimoId != NULL)
			{
				fprintf(archivoUltimoId, "%d",mayor);


			}
		}
		fclose(archivoUltimoId);

		retorno = 0;
	}
	return retorno;
}


/** \brief Parsea los datos de las editoriales desde el archivo (modo texto).
 *
 * \param pFile FILE* Archivo  abierto en modo lectura.
 * \param pArrayListEditorial LinkedList* Lista linkeada donde se ubican los datos.
 * \return int Devuelve 0 si se realizo o 1 en caso de puntero NULL.
 *
 */
int parser_EditorialFromText(FILE* pFile , LinkedList* pArrayListEditorial)
{

	eEditorial* pEditorial = NULL;
	eEditorial* pAuxEditorial = NULL;
	int cantidadDeDatosLeidos;
	char id[15];
	char nombre[128];
	int retorno = 1;
	FILE* archivoUltimoIdEditorial;
	int lastId;
	int mayor;

	if(pArrayListEditorial != NULL)
	{
		while(!feof(pFile))
		{
			cantidadDeDatosLeidos = fscanf(pFile,"%[^,],%[^\n]\n", id, nombre);
			if(cantidadDeDatosLeidos == 2 && isdigit(id[0]) != 0)
			{
				pEditorial = eEditorial_newParametros(id, nombre);
				if(pEditorial != NULL)
				{
					ll_add(pArrayListEditorial, pEditorial);
				}
			}

		}

		archivoUltimoIdEditorial = fopen("ultimo_id_editorial.txt","r");
		if(archivoUltimoIdEditorial == NULL)
		{
			for(int i = 0; i <ll_len(pArrayListEditorial); i++ )
			{
				pAuxEditorial = ll_get(pArrayListEditorial, i);
				//printf("%d\n", pAuxEmployee->id);
				eEditorial_getId(pAuxEditorial,&lastId);
				if( i == 0 || mayor < lastId)
				{

					mayor = lastId;
					//printf("%d\n", mayor);
				}
			}
			archivoUltimoIdEditorial = fopen("ultimo_id_editorial.txt","w");
			if(archivoUltimoIdEditorial != NULL)
			{
				fprintf(archivoUltimoIdEditorial, "%d",mayor);


			}
		}
		fclose(archivoUltimoIdEditorial);

		retorno = 0;
	}
	return retorno;
}



/** \brief Parsea los datos de los libros para el archivo  (modo texto).
 *
 * \param pFile FILE* Archivo  abierto en modo escritura.
 * \param pArrayListLibro LinkedList* Lista linkeada donde se ubican los datos.
 * \return int Devuelve 0 si se realizo o 1 en caso de puntero NULL.
 *
 */
int parser_TextFromLibro(FILE* pFile , LinkedList* pArrayListLibro)
{

	eLibro* pLibro = NULL;
	int indice;
	int retorno = 1;

	if(pArrayListLibro != NULL)
	{
		fprintf(pFile, "%s,%s,%s,%s\n", "Id", "Titulo", "Autor", "Precio");
		for(indice = 0; indice < ll_len(pArrayListLibro); indice++)
		{
			pLibro = (eLibro *)ll_get(pArrayListLibro, indice);
			fprintf(pFile, "%d,%s,%s,%.1f\n", pLibro->id, pLibro->titulo, pLibro->autor, pLibro->precio);
		}
		retorno = 0;
	}
	return retorno;
}
