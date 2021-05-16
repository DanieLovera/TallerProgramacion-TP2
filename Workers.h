#ifndef _WORKERS_H_
#define _WORKERS_H_

class Worker;
class IndexMonitor;
class IfsMonitor;
class BlockingQueue;
class SetMonitor;
#include <vector>
#include <string>

class Workers {
	private:
		const std::size_t nworkers;
		std::vector<Worker*> workers;

		Workers(const Workers &other) = delete;
		Workers& operator=(const Workers &other) = delete;

		/*
		 * @brief Inicializa los workers.
		 * @param indexMonitor: indice que debe contener indicaciones
		 * para localizar las paginas de cada url.
		 * @param ifsMonitor: permite acceder a la lectura del archivo
		 * <pages> en memoria. Debe estar correctamente inicializado
		 * para leer este archivo.
		 * @param setMonitor: coleccion comun en donde se guardaran
		 * los resultados del worker.
		 * @param domainFilter: nombre de dominio filtro para encontrar
		 * urls especificas en el archivo <pages>.
		 */		
		void initWorkers(IndexMonitor &indexMonitor, 
				   		 IfsMonitor &ifsMonitor, 
				   		 BlockingQueue &blockingQueue, 
				   		 SetMonitor &result, 
				   		 const std::string &domainFilter);

		/*
		 * @brief Libera los recursos de cada workers.
		 */
		void uninitWorkers();

		/*
		 * @brief Lanza todos los threads a ejecutarse.
		 */
		void startAllWorkers();

	public:
		/*
		 * @brief Constructor de la clase.
		 * @param nworkers: Numero de workers que se utilizaran.
		 */
		explicit Workers(const std::size_t nworkers);

		/*
		 * @brief Constructor por movimiento de la clase.
		 * @param other: Objeto del cual se moveran los recursos.
		 */
		Workers(Workers &&other);

		/*
		 * @brief Destructor de la clase.
		 */
		~Workers();


		Workers& operator=(Workers &&other);

		/*
		 * @brief Inicializa y lanza los workers. Startear dos veces
		 * un join intermedio causara comportamiento indefinido.
		 * @param indexMonitor: indice que debe contener indicaciones
		 * para localizar las paginas de cada url.
		 * @param ifsMonitor: permite acceder a la lectura del archivo
		 * <pages> en memoria. Debe estar correctamente inicializado
		 * para leer este archivo.
		 * @param setMonitor: coleccion comun en donde se guardaran
		 * los resultados del worker.
		 * @param domainFilter: nombre de dominio filtro para encontrar
		 * urls especificas en el archivo <pages>.
		 */
		void start(IndexMonitor &indexMonitor, 
				   IfsMonitor &ifsMonitor, 
				   BlockingQueue &blockingQueue, 
				   SetMonitor &result, 
				   const std::string &domainFilter);

		/*
		 * @brief Sincroniza el trabajo de los workes con el hilo
		 * principal.
		 */
		void join();
};

#endif // _WORKER_H_
