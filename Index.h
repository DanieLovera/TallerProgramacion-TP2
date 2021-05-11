#ifndef _INDEX_H_
#define _INDEX_H_

#include "FileReader.h"
#include "Url.h"
#include <map>
#include <vector>

/*
 * Clase que contiene el archivo index en memoria.
 */
class Index {
	private:
		std::map<Url, std::vector<std::size_t>> index;

		Index(const Index &other) = delete;
		Index& operator=(const Index &other) = delete;

		/*
		 * @brief Carga el map utilizando un fileReader.
		 * @param fileReader: Debe estar inicializado correctamente con un
		 * archivo que use el formato URL PAGE_OFFSET PAGE_SIZE.
		 */
		void loadMap(FileReader &fileReader);

	public:
		/*
		 * @brief Constructor de la clase.
		 */
		Index();

		/*
		 * @brief Constructor por movimiento de la clase.
		 * @param other: Objeto del cual se moveran los recursos.
		 */
		Index(Index &&other);

		/*
		 * @brief Destructor de la clase.
		 */

		~Index();

		/*
		 * @brief Asignacion por moviento
		 * @param other: Objeto del cual se moveran los recursos.
		 * @returns Devuelve una referencia a si mismo.
		 */
		Index& operator=(Index &&other);

		/*
		 * @brief Carga el index utilizando el nombre de un archivo valido.
		 * @param fileName: Debe ser un nombre de archivo valido y cumplir
		 * con el formato URL PAGE_OFFSET PAGE_SIZE.
		 */
		void load(const std::string &fileName);
};

#endif // _INDEX_H_
