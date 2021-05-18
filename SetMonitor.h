#ifndef _SET_MONITOR_H_
#define _SET_MONITOR_H_

class Url;
#include <set>
#include <mutex>

class SetMonitor {
	private:
		std::set<Url> result;
		std::mutex mutex;
		SetMonitor(const SetMonitor &other) = delete;
		SetMonitor(SetMonitor &&other) = delete;
		SetMonitor& operator=(const SetMonitor &other) = delete;
		SetMonitor& operator=(SetMonitor &&other) = delete;
	
	public:
		/*
		 * @brief Constructor de la clase.
		 */
		SetMonitor();

		/*
		 * @brief Destructor de la clase.
		 */
		~SetMonitor();

		/*
		 * @brief Inserta un dato en la coleccion.
		 * @param url: Contiene la url que sera insertada en la coleccion,
		 * la url sera movida de su variable original. Por lo cual cualquier
		 * uso posterior al llamado de la funcion sera indefinido.
		 */
		void insert(Url &&url);

		/*
		 * @brief Muestra los datos guardados en la coleccion.
		 */		
		void print();
};

#endif // _SET_MONITOR_H_
