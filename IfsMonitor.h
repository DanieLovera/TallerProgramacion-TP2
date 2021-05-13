#ifndef _IFS_MONITOR_H_
#define _IFS_MONITOR_H_

#include <fstream>
#include <string>
#include <mutex>

/*
 * Clase RAII para proteger la lectura del recurso ifstream.
 */
class IfsMonitor {
	private:
		std::ifstream ifs;
		std::mutex m;

		IfsMonitor(const IfsMonitor &other) = delete;
		IfsMonitor& operator=(const IfsMonitor &other) = delete;

		/*
		 * @brief Cierra el recurso file si se encuentra abierto.
		 */
		void closeIfOpen();

	public:
		/*
		 * @brief Constructor de la clase.
		 * @param fileName: Nombre del archivo que se quiere tomar.
		 */
		IfsMonitor(const std::string &fileName);

		/*
		 * @brief Constructor por movimiento de la clase.
		 * @param other: Objeto del cual se moveran los recursos.
		 */
		IfsMonitor(IfsMonitor &&other);

		/*
		 * @brief Destructor de la clase.
		 */
		~IfsMonitor();
		
		/*
		 * @brief Asignacion por moviento
		 * @param other: Objeto del cual se moveran los recursos.
		 * @returns Devuelve una referencia a si mismo.
		 */
		IfsMonitor& operator=(IfsMonitor &&other);

		/**
		 * @brief Lee una palabra del archivo file y la almacena en buffer,
		 * omite caracteres de espacio.
		 * @param buffer: Buffer para contener la palabra leida.
		 * @returns Devuelve True si llego al final del archivo y False
		 * en caso contrario. 
		 */
		bool readWord(std::string &buffer);

		bool readLine(std::string &buffer);

		void readBlockFromTo(char *buffer, std::size_t from, std::size_t to);
};

#endif // _IFS_MONITOR_H_
