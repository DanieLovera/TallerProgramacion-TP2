#ifndef _IFS_MONITOR_H_
#define _IFS_MONITOR_H_

#include <fstream>
#include <string>
#include <mutex>

class IfsMonitor {
	private:
		std::ifstream ifs;
		std::mutex mutex;

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
		explicit IfsMonitor(const std::string &fileName);

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
		 * @brief Asignacion por moviento.
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

		/**
		 * @brief Lee un bloque del archivo controlado por el ifs.
		 * @param buffer: Tendra el bloque leído del ifs, deberá ser
		 * lo suficientemente grande como para guardar (to - from) bytes.
		 * @param from: Inicio del punto en donde se comenzara a leer el
		 * archivo.
		 * @param to: Marca el ultimo caracter que sera leido del ifs.
		 */
		void readBlockFromTo(char *buffer, 
							 const std::size_t from, 
							 const std::size_t to);
};

#endif // _IFS_MONITOR_H_
