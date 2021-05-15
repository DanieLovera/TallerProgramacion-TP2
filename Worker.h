#ifndef _WORKER_H_
#define _WORKER_H_

#include "Thread.h"
class Url;
class IndexMonitor;
class IfsMonitor;
class BlockingQueue;
class SetMonitor;
#include <string>

class Worker : public Thread {
	private:
		IndexMonitor &indexStructure;
		IfsMonitor &ifsMonitor;
		BlockingQueue &blockingQueue;
		SetMonitor &result;
		const std::string &domainFilter;

		Worker(const Worker &other) = delete;
		Worker& operator=(const Worker &other) = delete;
		Worker& operator=(Worker &&other) = delete;

		/*
		 * @brief Carga en la blocking queue los resultados obtenidos
		 * al explorar una url.
		 * @param urlsResult: Contiene el resultado que cargara a la
		 * cola en formato de string con las nuevas urls separadas
		 * por un espacio.
		 */
		void pushUrls(const std::string &urlsResult);

	public:
		/*
		 * @brief Constructor de la clase.
		 * @brief indexStructure: indice que debe contener indicaciones
		 * para localizar las paginas de cada url.
		 * @brief ifsMonitor: permite acceder a la lectura del archivo
		 * <pages> en memoria. Debe estar correctamente inicializado
		 * para leer este archivo.
		 * @brief setMonitor: coleccion comun en donde se guardaran
		 * los resultados del worker.
		 * @brief domainFilter: nombre de dominio filtro para encontrar
		 * urls especificas en el archivo <pages>.
		 */
		Worker(IndexMonitor &indexStructure, 
			   IfsMonitor &ifsMonitor, 
			   BlockingQueue &blockingQueue, 
			   SetMonitor &result, 
			   const std::string &domainFilter);

		/*
		 * @brief Constructor por movimiento de la clase.
		 * @param other: Objeto del cual se moveran los recursos.
		 */
		Worker(Worker &&other);

		/*
		 * @brief Destructor de la clase.
		 */
		~Worker();

		/*
		 * @brief Operacion que se ejecutara concurrentemente en el thread.
		 */	
		void run() override;
};

#endif //_WORKER_H_
