#ifndef _URL_STATE_H_
#define _URL_STATE_H_

class Url;
class IndexMonitor;
class IfsMonitor;
#include <string>

class UrlState {
	private:
		UrlState(const UrlState &other) = delete;
		UrlState& operator=(const UrlState &other) = delete;
		UrlState& operator=(UrlState &&other) = delete;

	public:
		/*
		 * @brief Constructor de la clase.
		 */
		UrlState();

		/*
		 * @brief Constructor por movimiento de la clase.
		 * @param other: Objeto del cual se moveran los recursos.
		 */
		UrlState(UrlState &&other);

		/*
		 * @brief Destructor de la clase.
		 */
		virtual ~UrlState();

		/*
		 * @brief Muestra por salida estandar los atributos de la clase.
		 */		
		virtual void print() const = 0;

		/*
		 * @brief Controla si una url es valida o no.
		 * @param indexStructure: Contiene la informacion necesaria
		 * para gestionar si una url existe.
		 * @param offset: Contiene el offset de la pagina asociada
		 * a la url. El valor es modificado para retornar el resultado.
		 * @param size: Contiene el size de la pagina asociada a la
		 * url. El valor es modificado para el retornar el resultado.
		 * @param context: Contiene la url a la cual se esta refiriendo
		 * el estado. Puede modificar el valor de la url pasada.
		 */		
		virtual void handleValidation(const IndexMonitor &indexStructure, 
							  std::size_t &offset, 
							  std::size_t &size, 
							  Url &context) = 0;

		/*
		 * @brief Controla la exploracion de la pagina de una url.
		 * @param ifsMonitor: Contiene la informacion necesaria
		 * para leer un archivo <pages> que debe contener las paginas
		 * para el proceso de fetching.
		 * @param offset: Contiene el offset de la pagina asociada
		 * a la url. El valor es modificado para retornar el resultado.
		 * @param size: Contiene el size de la pagina asociada a la
		 * url. El valor es modificado para el retornar el resultado.
		 * @param result: Sera modificada para colocar el resultado del
		 * fetching de la pagina web. Devuelve una string que separa las
		 * urls encontradas con un espacio en blanco.
		 * @param context: Contiene la url a la cual se esta refiriendo
		 * el estado. Puede modificar el valor de la url pasada.
		 */	
		virtual void handleExploration(IfsMonitor &ifsMonitor, 
							   		   const std::string &domainFilter, 
							   		   std::size_t &offset, 
							   		   std::size_t &size, 
							   		   std::string &result, 
							   		   Url &context) = 0;
};

#endif // _URL_STATE_H_
