# TP2: Web Crawler #  
**Autor: Daniel Alejandro Lovera López**  
**Número padrón: 103442**  
**[https://github.com/DanieLovera/tp2](https://github.com/DanieLovera/tp2)**  

---
### Introducción ###  
El presente trabajo consiste en la elaboración de un Web Crawler, este es un programa que escanea un sitio web y como sus páginas se entrelazan entre si. La implementación que se realizó para el Web Crawler fue una simplificación, la busqueda sobre las páginas web fueron simuladas utilizando archivos en disco que contienen la url que se quiere explorar y, un offset y size para mapear la ubicación de su página web en un archivo html que contiene finalmente todas las páginas que serán exploradas. Con el objetivo de trabajar los conceptos aprendidos sobre hilos, la implementación además fue multithreading, para ello se trabajo con el caso base de un Worker (entidad encargada de simular el fetch de una pagina web) y posteriormente se extendió para que el programa principal haga uso de varios de estos Workers y trabajen concurrentemente.  
  
Entre las clases principales utilizadas para lograr implementar el Web Crawler multithreading se encuentran:

- **Thread**: Wrappea la clase thread de C++, con esto cualquier clase que necesite trabajar con hilos simplemente puede heradar de esta e implementar el método abstracto *```run()```*, y luego utilizar los métodos ```start()``` y ```join()``` para lanzar el hilo y sincronizarlo respectivamente.
- **Worker**: Realiza la búsqueda de la url en el IndexMonitor para verificar la validez de la url y el fetch de las urls relacionadas en el archivo html.
- **BlockingQueue**: Contenedor utilizado para guardar las urls que deben ser exploradas por el Worker, tiene un comportamiento productor debido al método ```push()``` y consumidor por el método ```pop()``` es decir, mientras el contenedor no sea cerrado tiene la capacidad de dormir todos los hilos que accedan a un pop mientras la cola este vacía y despertarlos cuando un nuevo dato fuese producido. 
- **Url**: Es una abstracción de una url.
- **IndexMonitor**: Contenedor usado para mantener las urls que son válidas para explorar.
- **IfsMonitor**: Abstracción que permite leer un archivo de entrada para proporcionarle datos al programa.  

---
### Desarrollo ##  
