#ifndef _URL_H_
#define _URL_H_

class UrlState;
class IndexMonitor;
class IfsMonitor;
#include <string>

class Url {
	private:
		std::string url;
		UrlState *state;
		Url(const Url &other) = delete;
		Url& operator=(const Url &other) = delete;

		/*
		 * @brief Libera la memoria utilizada por el state si es diferente
		 * de nullptr.
		 */
		void freeIfNotNullState();

		/*
		 * @brief Filtra la url usando el domainFilter. Solo dominios
		 * o subDominios que coincidan con este filtro.
		 */
		bool filter(const std::string &url, const std::string &domainFilter);

	public:
		/*
		 * @brief Constructor de la clase.
		 */
		Url();

		/*
		 * @brief Constructor de la clase.
		 * @param url: nombre del dominio para la url.
		 */
		explicit Url(const std::string &url);

		/*
		 * @brief Constructor por movimiento de la clase.
		 * @param other: Objeto del cual se moveran los recursos.
		 */
		Url(Url &&other);

		/*
		 * @brief Destructor de la clase.
		 */
		~Url();

		/*
		 * @brief Asignacion por moviento
		 * @param other: Objeto del cual se moveran los recursos.
		 * @returns Devuelve una referencia a si mismo.
		 */
		Url& operator=(Url &&other);

		/*
		 * @brief Operador menor.
		 * @param other: Objeto que se usa para comparar.
		 * @returns Devuelve true si other es mayor o false
		 * en caso contrario.
		 */
		bool operator<(const Url &other) const;

		/*
		 * @brief Valida la url para saber si esta muerta o no.
		 * @param offset: En caso de que la url sea valida devuelve
		 * su ubicacion en el archivo <pages> en caso contrario
		 * devuelve 0.
		 * @param size: En caso de que la url sea valida devuelve
		 * el tamanio de la pagina en caso contrario
		 * devuelve 0.
		 */
		void validate(const IndexMonitor &indexStructure, 
				   	  std::size_t &offset, 
				   	  std::size_t &size);

		/*
		 * @brief Explora en busqueda de links en su pagina.
		 * @param domainFilter: filtro que se utiliza para encontrar
		 * las urls adecuadas dentro del archivo <pages>.
		 * @param offset: Ubicacion de la pagina correspondiente
		 * a la url en el archivo <pages>.
		 * @param size: Tamanio de la pagina.
		 * @param result: string que guardara el resultado de la busqueda
		 * separando los links resultantes por espacios en blanco.
		 */
		void exploreLinks(IfsMonitor &ifsMonitor, 
					  	  const std::string &domainFilter, 
					  	  std::size_t &offset, 
					  	  std::size_t &size,
					  	  std::string &result);

		/*
		 * @brief Verifica si la url es un subdominio de domainFilter y
		 * si utiliza el protocolo http.
		 * @param url: url que se utiliza para la validacion-
		 * @param domainFilter: nombre del filtro que se utilizara en
		 * la validacion.
		 */
		bool isSubUrl(const std::string &url, const std::string &domainFilter);

		/*
		 * @brief Cambia el estado de la url.
		 * @param state: Contiene la direccion de memoria del nuevo estado,
		 * este debera ser creado en el heap. La clase url se encarga de
		 * gestionar correctamente la liberacion de esta memoria.
		 */
		void setState(UrlState *state);

		/*
		 * @brief Muestra en salida estandar los atributos de la url.
		 */
		void print() const;
};

#endif // _URL_H_
