#ifndef _DEAD_H_
#define _DEAD_H_

#include "UrlState.h"
#include <string>

class Dead : public UrlState {
	private:
		Dead(const Dead &other) = delete;
		Dead& operator=(const Dead &other) = delete;
		Dead& operator=(Dead &&Dead) = delete;

	public:
		/*
		 * @brief Constructor de la clase.
		 */
		Dead();

		/*
		 * @brief Constructor por movimiento de la clase.
		 * @param other: Objeto del cual se moveran los recursos.
		 */
		Dead(Dead &&other);

		/*
		 * @brief Destructor de la clase.
		 */
		~Dead();

		/*
		 * @brief Muestra por salida estandar los atributos de la clase.
		 */		
		void print() const override;

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
		void handleValidation(const IndexMonitor &indexStructure, 
							  std::size_t &offset, 
							  std::size_t &size, 
							  Url &context) override;

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
		void handleExploration(IfsMonitor &ifsMonitor, 
							   const std::string &domainFilter, 
							   std::size_t &offset, 
							   std::size_t &size, 
							   std::string &result, 
							   Url &context) override;
};

#endif // _DEAD_H_
