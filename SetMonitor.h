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
		SetMonitor& operator=(const SetMonitor &other) = delete;
	
	public:
		/*
		 * @brief Constructor de la clase.
		 */
		SetMonitor();

		/*
		 * @brief Constructor por movimiento de la clase.
		 * @param other: Objeto del cual se moveran los recursos.
		 */
		SetMonitor(SetMonitor &&other);

		/*
		 * @brief Destructor de la clase.
		 */
		~SetMonitor();

		/*
		 * @brief Asignacion por moviento
		 * @param other: Objeto del cual se moveran los recursos.
		 * @returns Devuelve una referencia a si mismo.
		 */
		SetMonitor& operator=(SetMonitor &&other);

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
