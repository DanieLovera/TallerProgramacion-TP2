#ifndef _INDEX_H_
#define _INDEX_H_

#include "Url.h"
class IfsMonitor;
#include <map>
#include <vector>
#include <string>
#include <mutex>

class IndexMonitor {
	private:
		std::map<Url, std::vector<std::size_t>> index;
		std::mutex mutex;

		IndexMonitor(const IndexMonitor &other) = delete;
		IndexMonitor(IndexMonitor &&other) = delete;
		IndexMonitor& operator=(const IndexMonitor &other) = delete;
		IndexMonitor& operator=(IndexMonitor &&other) = delete;

	public:
		/*
		 * @brief Constructor de la clase.
		 */
		IndexMonitor();

		/*
		 * @brief Destructor de la clase.
		 */
		~IndexMonitor();

		/*
		 * @brief Carga el index utilizando el nombre de un archivo valido.
		 * @param fileName: Debe ser un nombre de archivo valido y cumplir
		 * con el formato URL PAGE_OFFSET PAGE_SIZE.
		 */
		void load(const std::string &fileName);

		/*
		 * @brief Busca la existencia de la url en el indice.
		 * @param url: Recibe la url que debera ser buscada en el indice.
		 * @param offset: Devuelve la ubicacion del inicio de la pagina
		 * apuntada por la url. En caso de no existencia devuelve 0.
		 * @param size: Devuelve el tamanio de la pagina. En caso de no
		 * existencia devuelve 0.
		 */
		void lookUp(const Url &url, std::size_t &offset, std::size_t &size) const; 
};

#endif // _INDEX_H_
