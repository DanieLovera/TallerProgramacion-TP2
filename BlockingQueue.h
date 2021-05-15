#ifndef _BLOCKING_QUEUE_H_
#define _BLOCKING_QUEUE_H_

#include "Url.h"
#include <queue>
#include <mutex>
#include <condition_variable>

class ClosedQueueException : public std::exception { };

class BlockingQueue {
	private:
		std::queue<Url> urls;
		std::mutex mutex;
		std::condition_variable cv;
		bool isClose;

		BlockingQueue(const BlockingQueue &other) = delete;
		BlockingQueue& operator=(const BlockingQueue &other) = delete;
		BlockingQueue(BlockingQueue &&other) = delete;
		BlockingQueue& operator=(BlockingQueue &&other) = delete;
		bool isWaitCondition() const;

	public:
		/*
		 * @brief Constructor de la clase.
		 */
		BlockingQueue();

		/*
		 * @brief Destructor de la clase.
		 */
		~BlockingQueue();

		/*
		 * @brief Coloca una url en el fin de la cola de urls.
		 * @param url: Url que sera cargada en la pila, la url
		 * sera movida de su variable original. Cualquier uso
		 * posterior al llamado de esta función sera indeterminado.
		 */
		void push(Url &&url);

		/*
		 * @brief Saca una url de el principio de la cola, mientras
		 * la cola no este cerrada la cola tendra un comportamiento
		 * de consumidor y esperara a que ocurra un push que la vuelva
		 * a producir un dato.
		 * @returns Devuelve la url en el principio de la cola.
		 */
		Url pop();

		/*
		 * @brief Cierra la cola para indicar que el pop ya no tendra
		 * un comportamiento de consumidor y en caso de que la cola 
		 * este vacia el thread no se quede esperando.
		 */
		void close();
};

#endif // _BLOCKING_QUEUE_H_
