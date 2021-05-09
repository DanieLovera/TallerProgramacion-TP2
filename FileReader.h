#ifndef _FILE_READER_H_
#define _FILE_READER_H_

#include <fstream>
#include <string>

/*
 * Clase RAII para proteger la lectura del recurso file.
 */
class FileReader {
	private:
		std::ifstream file;
		FileReader(const FileReader &other) = delete;
		FileReader& operator=(const FileReader &other) = delete;

		/*
		 * @brief Cierra el recurso file si se encuentra abierto.
		 */
		void closeIfOpen();

	public:
		/*
		 * @brief Constructor de la clase.
		 * @param fileName: Nombre del archivo que se quiere tomar.
		 */
		FileReader(const std::string &fileName);

		/*
		 * @brief Constructor por movimiento de la clase.
		 * @param other: Objeto del cual se moveran los recursos.
		 */
		FileReader(FileReader &&other);

		/*
		 * @brief Destructor de la clase.
		 */
		~FileReader();
		
		/*
		 * @brief Asignacion por moviento
		 * @param other: Objeto del cual se moveran los recursos.
		 * @returns Devuelve una referencia a si mismo.
		 */
		FileReader& operator=(FileReader &&other);

		/**
		 * @brief Lee una palabra del archivo file y la almacena en buffer,
		 * omite caracteres de espacio.
		 * @param buffer: Buffer para contener la palabra leida.
		 * @returns Devuelve True si llego al final del archivo y False
		 * en caso contrario. 
		 */
		bool readWord(std::string &buffer);

		bool readLine(std::string &buffer);
};

#endif // _FILE_READER_H_
