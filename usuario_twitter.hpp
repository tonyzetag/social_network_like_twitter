/****************************************************************************
* Clase UsuarioTwitter
*
* Esta clase implementa toda la operativa relativa a un usuario de la red
* social 'Twitter', permitiendo la gestión de la lista de tweets,
* usuarios seguidos (following) y usuarios seguidores (followers).
*
* Autor: Jose Antonio Zúñiga García
* Fecha: Fri Mar 10 12:14:11 2017
****************************************************************************/

#ifndef __USUARIO__TWITTER__
#define __USUARIO__TWITTER__
#include <string>
#include <array>
#include <fstream>

namespace {
	const unsigned MAX_USUARIOS = 100; // Máximo número de seguidores o siguiendo
	const unsigned MAX_TWEETS = 10000; // Máximo número de tweets del usuario
}


namespace bblProgII {
	//---------------------------------------------------------------------------
	// TIPOS PÚBLICOS
	//
	// Lista de usuarios
	typedef std::array <std::string, MAX_USUARIOS> ListaUsuarios;
	struct Usuarios {
		unsigned num_usuarios;
		ListaUsuarios listado;
	};
	//---------------------------------------------------------------------------
	// Lista de tweets
	struct FechaHora {
		unsigned anyo, mes, dia, hora, minuto, segundo;
	};
	struct Tweet {
		std::string tweet;
		FechaHora fecha_hora;
	};
	typedef std::array <Tweet, MAX_TWEETS> ListaTweets;
	struct Tweets {
		unsigned num_tweets;
		ListaTweets listado;
	};
	//---------------------------------------------------------------------------
	// Resulstado de las operaciones:
	//  - OK: la operación se ha realizado con éxito
	//  - LISTA_LLENA: la operación no ha sido posible: lista llena
	//  - YA_EXISTE: la operación no ha sido posible: el elemento ya existe
	//  - NO_EXISTE: el elemento no existe
	//  - FIC_ERROR: error en el fichero
	typedef unsigned Resultado;
	const Resultado OK = 0,
		LISTA_LLENA = 1,
		YA_EXISTE = 2,
		NO_EXISTE = 3,
		FIC_ERROR = 4;

	/* O, alternativamente,
	enum Resultado {
	OK,
	LISTA_LLENA,
	YA_EXISTE,
	NO_EXISTE,
	FIC_ERROR
	};
	*/


	class UsuarioTwitter {
	public:
		// Constructor por defecto
		// Inicializar todos los datos vacíos.
		UsuarioTwitter() : id_usuario(""), tweets(), siguiendo(), seguidores() {
			tweets.num_tweets = 0;
			siguiendo.num_usuarios = 0;
			seguidores.num_usuarios = 0;
		}

		// Constructor extendido.
		// Inicializa el idenfificador de usuario con el 'id' que se pasa
		// como parámetro. Las listas de usuarios y tweets están
		// vacías.
		UsuarioTwitter(const std::string &id) {
			id_usuario = id;
			tweets.num_tweets = 0;
			siguiendo.num_usuarios = 0;
			seguidores.num_usuarios = 0;
		}

		// Constructor de copia
		UsuarioTwitter(const UsuarioTwitter &otro_usuario) {
			id_usuario = otro_usuario.id_usuario;
			tweets.num_tweets = otro_usuario.tweets.num_tweets;
			siguiendo.num_usuarios = otro_usuario.siguiendo.num_usuarios;
			seguidores.num_usuarios = otro_usuario.seguidores.num_usuarios;
		}

		// Operador de asignación (¡¡¡OPCIONAL!!!)
		UsuarioTwitter & operator=(const UsuarioTwitter &otro_usuario) {
			
			if (this != &otro_usuario) {
				
				id_usuario = otro_usuario.id_usuario;

				tweets.num_tweets = otro_usuario.tweets.num_tweets;
				for (unsigned i = 0; i < tweets.num_tweets; i++) {
					tweets.listado[i] = otro_usuario.tweets.listado[i];
				}

				siguiendo.num_usuarios = otro_usuario.siguiendo.num_usuarios;
				for (unsigned i = 0; i < siguiendo.num_usuarios; i++) {
					siguiendo.listado[i] = otro_usuario.siguiendo.listado[i];
				}

				seguidores.num_usuarios = otro_usuario.seguidores.num_usuarios;
				for (unsigned i = 0; i < seguidores.num_usuarios; i++) {
					seguidores.listado[i] = otro_usuario.seguidores.listado[i];
				}
			}
		}

		// Destructor de la clase
		~UsuarioTwitter() {};

		//------------------------------------------------------------------
		// MÉTODOS DE CONSULTA

		// Devuelve el idenficador del usuario
		std::string obtener_id() const {
			return id_usuario;
		}

		// Devuelve la lista de seguidores
		void obtener_seguidores(Usuarios &lista_seg) const {
			lista_seg = seguidores;
		}

		// Devuelve la lista de usuarios a los que se sigue
		void obtener_siguiendo(Usuarios &lista_sig) const {
			lista_sig = siguiendo;
		}

		// Devuelve la lista de tweets del usuario
		void obtener_tweets(Tweets &lista_tweets) const {
			lista_tweets = tweets;
		}

		// Indica si un determinado usuario es seguidor de este usuario
		bool me_sigue(const std::string &otro_usuario) const {
			bool mismo_usuario;
			// Primero busco la posición donde debería estar
			unsigned pos = buscar_usuario(seguidores, otro_usuario);
			// Si es el mismo usuario devuelve true, si no, false
			if (seguidores.listado[pos] == otro_usuario) {
				mismo_usuario = true;
			}
			else {
				mismo_usuario = false;
			}
			return mismo_usuario;
		}

		// Indica si este usuario está siguiendo a otro
		bool estoy_siguiendo(const std::string &otro_usuario) const {
			bool mismo_usuario;
			// Primero busco la posición donde debería estar
			unsigned pos = buscar_usuario(siguiendo, otro_usuario);
			// Si es el mismo usuario devuelve true, si no, false
			if (siguiendo.listado[pos] == otro_usuario) {
				mismo_usuario = true;
			}
			else {
				mismo_usuario = false;
			}
			return mismo_usuario;
		}

		// Devuelve el número de seguidores
		unsigned num_seguidores() const {
			return seguidores.num_usuarios;
		}

		// Devuelve el número de usuarios a los que se sigue
		unsigned num_siguiendo() const {
			return siguiendo.num_usuarios;
		}

		// Devuelve el número de tweets del usuario
		unsigned num_tweets() const {
			return tweets.num_tweets;
		}

		// Imprime por pantalla la lista de seguidores
		// Si num_imprime == 0, imprime todos los seguidores. Si no,
		// se imprime el número de seguidores que se indica.
		// PRECONDICIÓN: num_imprime <= num_seguidores
		void imprimir_seguidores(unsigned num_imprime) const {
			// PRECONDICIÓN: num_imprime <= num_seguidores
			bool ok = (num_imprime <= seguidores.num_usuarios) ? true : false;
			// Si num_imprime == 0, imprime todos los seguidores
			if (ok && (num_imprime == 0)) {
				for (unsigned i = 0; i < seguidores.num_usuarios; i++) {
					std::cout << i << ": " << seguidores.listado[i] << std::endl;
				}
			}
			// Si num_imprime != 0, imprime "num_imprime" seguidores
			else if (ok && (num_imprime != 0)) {
				for (unsigned i = 0; i < num_imprime; i++) {
					std::cout << i << ": " << seguidores.listado[i] << std::endl;
				}
			}
			// Si no cumple la condición deuvelve error por pantalla
			else {
				std::cerr << "Error: El número de seguidores es menor que " << num_imprime << std::endl;
			}
		}

		// Imprime por pantalla la lista de usuarios a los que sigue
		// Si num_imprime == 0, imprime todos los usuarios a los que sigue.
		// Si no, imprime el número de usuarios que se indica.
		// PRECONDICIÓN: num_imprime <= num_siguiendo
		void imprimir_siguiendo(unsigned num_imprime) const {
			// PRECONDICIÓN: num_imprime <= num_siguiendo
			bool ok = (num_imprime <= siguiendo.num_usuarios) ? true : false;
			// Si num_imprime == 0, imprime todos los seguidos
			if (ok && (num_imprime == 0)) {
				for (unsigned i = 0; i < siguiendo.num_usuarios; i++) {
					std::cout << i << ": " << siguiendo.listado[i] << std::endl;
				}
			}
			// Si num_imprime != 0, imprime "num_imprime" seguidores
			else if (ok && (num_imprime != 0)) {
				for (unsigned i = 0; i < num_imprime; i++) {
					std::cout << i << ": " << siguiendo.listado[i] << std::endl;
				}
			}
			// Si no cumple la condición deuvelve error por pantalla
			else {
				std::cerr << "Error: El número de usuarios seguidos es menor que " << num_imprime << std::endl;
			}
		}

		// Imprime por pantalla la lista de tweets
		// Si num_imprime == 0, imprime todos los tweets del usuario.
		// Si no, imprime el número de tweets que se indica.
		// PRECONDICIÓN: num_imprime <= num_tweets
		void imprimir_tweets(unsigned num_imprime) const {
			// PRECONDICIÓN: num_imprime <= num_tweets
			bool ok = (num_imprime <= tweets.num_tweets) ? true : false;
			// Si num_imprime == 0, imprime todos los tweets del usuario.
			if (ok && (num_imprime == 0)) {
				for (unsigned i = 0; i < tweets.num_tweets; i++) {
					std::cout <<
						tweets.listado[i].fecha_hora.dia << " " <<
						tweets.listado[i].fecha_hora.mes << " " <<
						tweets.listado[i].fecha_hora.anyo << " " <<
						tweets.listado[i].fecha_hora.hora << " " <<
						tweets.listado[i].fecha_hora.minuto << " " <<
						tweets.listado[i].fecha_hora.segundo << " " <<
						tweets.listado[i].tweet << std::endl;
				}
			}
			// Si no, imprime el número de tweets que se indica.
			else if (ok && (num_imprime > 0)) {
				for (unsigned i = (tweets.num_tweets) - num_imprime; i < tweets.num_tweets; i++) {
					std::cout <<
						tweets.listado[i].fecha_hora.dia << " " <<
						tweets.listado[i].fecha_hora.mes << " " <<
						tweets.listado[i].fecha_hora.anyo << " " <<
						tweets.listado[i].fecha_hora.hora << " " <<
						tweets.listado[i].fecha_hora.minuto << " " <<
						tweets.listado[i].fecha_hora.segundo << " " <<
						tweets.listado[i].tweet << std::endl;
				}
			}
			// Si no cumple la condición deuvelve error por pantalla
			else {
				std::cerr << "Error: El número de tweets es menor que " << num_imprime << std::endl;
			}

		}

		// Guarda en fichero la lista de seguidores
		void guardar_seguidores(const std::string &nom_fic, Resultado &res) const {
			// Variables
			std::ofstream fichero;
			// Abrimos
			fichero.open(nom_fic.c_str());
			// Comprobación
			if (!fichero.fail()) {
				unsigned n = 0;
				while (!fichero.fail() && n < seguidores.num_usuarios)
				{
					fichero << seguidores.listado[n] << std::endl;
					n++;
				}
			}
			res = (!fichero.fail()) ? OK : FIC_ERROR;
			// Cerrar
			fichero.close();
		}

		// Guarda en fichero la lista de usuarios a los que sigue
		void guardar_seguiendo(const std::string &nom_fic, Resultado &res) const {
			// Variables
			std::ofstream fichero;
			// Abrimos
			fichero.open(nom_fic.c_str());
			// Comprobación
			if (!fichero.fail()) {
				unsigned n = 0;
				while (!fichero.fail() && n < siguiendo.num_usuarios)
				{
					fichero << siguiendo.listado[n] << std::endl;
					n++;
				}
			} 
			res = (!fichero.fail()) ? OK : FIC_ERROR;
			// Cerrar
			fichero.close();
		}

		// Guarda en fichero los tweets del usuario
		void guardar_tweets(const std::string &nom_fic, Resultado &res) const {
			// Variables
			std::ofstream fichero;
			// Abrimos
			fichero.open(nom_fic.c_str());
			// Comprobación
			if (!fichero.fail()) {
				unsigned n = 0;
				while (!fichero.fail() && n < tweets.num_tweets)
				{
					fichero <<
						tweets.listado[n].fecha_hora.dia << " " <<
						tweets.listado[n].fecha_hora.mes << " " <<
						tweets.listado[n].fecha_hora.anyo << " " <<
						tweets.listado[n].fecha_hora.hora << " " <<
						tweets.listado[n].fecha_hora.minuto << " " <<
						tweets.listado[n].fecha_hora.segundo << " " <<
						tweets.listado[n].tweet << std::endl;
					n++;
				}
			}
			res = (!fichero.fail()) ? OK : FIC_ERROR;
			// Cerrar
			fichero.close();
		}

		// Guarda en fichero las listas de usuarios  y tweets
		void guardar_todo(const std::string &nom_fic_seguidores,
			const std::string &nom_fic_siguiendo,
			const std::string &nom_fic_tweets,
			Resultado &res_seguidores,
			Resultado &res_siguiendo,
			Resultado &res_tweets) const
		{
			// Usamos las funciones de guardado de cada uno
			guardar_seguidores(nom_fic_seguidores, res_seguidores);
			guardar_seguiendo(nom_fic_siguiendo, res_siguiendo);
			guardar_tweets(nom_fic_tweets, res_tweets);
		}

		//------------------------------------------------------------------
		// MÉTODOS DE ACTUALIZACIÓN

		// Modifica el identificador del usuario
		void establecer_id(const std::string &nuevo_id) {
			id_usuario = nuevo_id;
		}

		// Inserta un seguidor en la lista de seguidores.
		// Si el nuevo seguidor no existe, se inserta de manera ordenada
		// (orden lexicográfico creciente) y se devuelve 'OK' a través de
		// 'res'. Si ya existe el seguidor, no se inserta y se devuelve
		// 'YA_EXISTE' a través de 'res'. Si no, si la lista de seguidores está
		// llena, se devuelve 'LISTA_LLENA' a través de 'res'.
		void nuevo_seguidor(const std::string &nuevo, Resultado &res) {
			// Posición en la que debería de estar "nuevo"
			unsigned pos = buscar_usuario(seguidores, nuevo);
			// Comprobación de que no existe
			bool existe = (seguidores.listado[pos] == nuevo) ? true : false;
			// Comprobación de lista llena
			bool llena = (seguidores.num_usuarios == MAX_USUARIOS) ? true : false;
			// Asignación de valor a res
			if (existe) {
				res = YA_EXISTE;
			}
			else if (llena) {
				res = LISTA_LLENA;
			}
			else {
				insertar_usuario_pos(seguidores, pos, nuevo);
				res = OK;
			}
		}

		// Inserta un usuario en la lista de usuarios a los que sigue.
		// Si el nuevo usuario no existe, se inserta de manera ordenada
		// (orden lexicográfico creciente) y se devuelve 'OK' a través de
		// 'res'. Si ya existe el usuario, no se inserta y se devuelve
		// 'YA_EXISTE' a través de 'res'. Si no, si la lista de seguidores está
		// llena, se devuelve 'LISTA_LLENA' a través de 'res'.
		void nuevo_siguiendo(const std::string &nuevo, Resultado &res) {
			// Posición en la que debería de estar "nuevo"
			unsigned pos = buscar_usuario(siguiendo, nuevo);
			// Comprobación de que no existe
			bool existe = (siguiendo.listado[pos] == nuevo) ? true : false;
			// Comprobación de lista llena
			bool llena = (siguiendo.num_usuarios == MAX_USUARIOS) ? true : false;
			// Asignación de valor a res
			if (existe) {
				res = YA_EXISTE;
			}
			else if (llena) {
				res = LISTA_LLENA;
			}
			else {
				insertar_usuario_pos(siguiendo, pos, nuevo);
				res = OK;
			}
		}

		// Inserta un nuevo tweet al final de la lista de tweets. Si la lista de
		// tweets está llena, se devuelve 'LISTA_LLENA' a través de 'res'. Si no,
		// se devuelve 'OK'. La longitud máxima del tweet es 140 caracteres, por
		// lo que si el texto del tweet tiene más de 140 caracteres, los
		// caracteres sobrantes por el final se eliminarán.
		void nuevo_tweet(const Tweet &nuevo, Resultado &res) {
			// Constante, máxima longitud de tweet
			const unsigned MAX_LONG_TWEET = 140;
			// Comprobación de lista llena
			bool llena = (tweets.num_tweets == MAX_TWEETS) ? true : false;
			// Asignación de valor a res
			res = (llena) ? LISTA_LLENA : OK;
			// Si todo va bien, inserta nuevo tweet (140 caracteres)
			if (res == OK) {
				Tweet formateado = nuevo;
				tweets.num_tweets++;
				if (formateado.tweet.length() > MAX_LONG_TWEET) {
					formateado.tweet.resize(MAX_LONG_TWEET);
				}
				tweets.listado[tweets.num_tweets - 1] = formateado;
			}
		}

		// Elimina a un usuario de la lista de seguidores
		// Si el usuario existe, se elimina y se devuelve 'OK' a través de
		// 'res'. Si no existe el usuario, se devuelve 'NO_EXISTE' a través
		// de 'res'.
		void eliminar_seguidor(const std::string &usuario, Resultado &res) {
			unsigned pos;
			// Posicion donde debería de estar el usuario
			pos = buscar_usuario(seguidores, usuario);
			res = (seguidores.listado[pos] == usuario) ? OK : NO_EXISTE;
			// Si el usuario existe eliminarlo y reordenar
			if (res == OK) {
				for (unsigned i = pos; i < seguidores.num_usuarios - 1; i++) {
					seguidores.listado[i] = seguidores.listado[i + 1];
				}
				seguidores.num_usuarios--;
			}
		}

		// Elimina a un usuario de la lista de usuarios a los que sigue
		// Si el usuario existe, se elimina y se devuelve 'OK' a través de
		// 'res'. Si no existe el usuario, se devuelve 'NO_EXISTE' a través
		// de 'res'.
		void eliminar_siguiendo(const std::string &usuario, Resultado &res) {
			unsigned pos;
			// Posicion donde debería de estar el usuario
			pos = buscar_usuario(siguiendo, usuario);
			res = (siguiendo.listado[pos] == usuario) ? OK : NO_EXISTE;
			// Si el usuario existe eliminarlo y reordenar
			if (res == OK) {
				for (unsigned i = pos; i < siguiendo.num_usuarios - 1; i++) {
					siguiendo.listado[i] = siguiendo.listado[i + 1];
				}
				siguiendo.num_usuarios--;
			}
		}

		// Carga desde fichero la lista de seguidores,
		// eliminando los seguidores actuales. Si el fichero se ha leído
		// correctamente y los usuarios caben en la lista, se devuelve
		// 'OK' a través de 'res'. En caso contrario, se devuelve
		// 'FIC_ERROR' o 'LISTA_LLENA', respectivamente (aunque se insertan
		// solo los usuarios que caben en la lista).
		void cargar_seguidores(const std::string &nom_fic, Resultado &res) {
			// Variables
			std::ifstream fichero;
			// Abrir fichero
			fichero.open(nom_fic.c_str());
			// Si no falla, leer los usuarios
			if (!fichero.fail()) {
				unsigned n = 0;
				while (!fichero.fail() && n < MAX_USUARIOS) {
					getline(fichero, seguidores.listado[n]);
					seguidores.num_usuarios = n;
					n++;
				}
			}
			// Si el fichero ha llegado al fina, todo correcto
			res = (fichero.eof()) ? OK : FIC_ERROR;
			// Cerramos
			fichero.close();
		}

		// Carga desde fichero la lista de usuarios a los que se sigue,
		// eliminando los usuarios seguidos actuales. Si el fichero se ha leído
		// correctamente y los usuarios caben en la lista, se devuelve
		// 'OK' a través de 'res'. En caso contrario, se devuelve
		// 'FIC_ERROR' o 'LISTA_LLENA', respectivamente (aunque se insertan
		// solo los usuarios que caben en la lista).
		void cargar_seguiendo(const std::string &nom_fic, Resultado &res) {
			// Variables
			std::ifstream fichero;
			// Abrir fichero
			fichero.open(nom_fic.c_str());
			// Si no falla, leer los usuarios
			if (!fichero.fail()) {
				unsigned n = 0;
				while (!fichero.fail() && n < MAX_USUARIOS) {
					getline(fichero, siguiendo.listado[n]);
					siguiendo.num_usuarios = n;
					n++;
				}
			}
			// Si el fichero ha llegado al fina, todo correcto
			res = (fichero.eof()) ? OK : FIC_ERROR;
			// Cerramos
			fichero.close();
		}

		// Carga desde fichero la lista de tweets del usuario,
		// eliminando los tweets actuales. Si el fichero se ha leído
		// correctamente y los tweets caben en la lista, se devuelve
		// 'OK' a través de 'res'. En caso contrario, se devuelve
		// 'FIC_ERROR' o 'LISTA_LLENA', respectivamente (aunque se insertan
		// solo los tweets que caben en la lista).
		void cargar_tweets(const std::string &nom_fic, Resultado &res) {
			// Variables
			std::ifstream fichero;
			// Abrir fichero
			fichero.open(nom_fic.c_str());
			// Si no falla, leer los usuarios
			if (!fichero.fail()) {
				unsigned n = 0;
				while (!fichero.fail() && n < MAX_USUARIOS) {
					fichero >> std::ws;
					fichero >>
						tweets.listado[n].fecha_hora.dia >>
						tweets.listado[n].fecha_hora.mes >>
						tweets.listado[n].fecha_hora.anyo >>
						tweets.listado[n].fecha_hora.hora >>
						tweets.listado[n].fecha_hora.minuto >>
						tweets.listado[n].fecha_hora.segundo;
					getline(fichero, tweets.listado[n].tweet);
					tweets.num_tweets = n;
					n++;
				}
			}
			// Si el fichero ha llegado al fina, todo correcto
			res = (fichero.eof()) ? OK : FIC_ERROR;
			// Cerramos
			fichero.close();
		}

		// Carga desde fichero las listas de usuarios y tweets. Si cada fichero se ha leído
		// correctamente y los usuarios/tweets caben en la lista correspondiente, se devuelve
		// 'OK' a través del parámetro 'res_*' correspondiente. En caso contrario, se devuelve
		// 'FIC_ERROR' o 'LISTA_LLENA', respectivamente (aunque se insertan
		// solo los usuarios/tweets que caben en la lista correspondiente).
		void cargar_todo(const std::string &nom_fic_seguidores,
			const std::string &nom_fic_siguiendo,
			const std::string &nom_fic_tweets,
			Resultado & res_seguidores,
			Resultado & res_siguiendo,
			Resultado & res_tweets)
		{
			cargar_seguidores(nom_fic_seguidores, res_seguidores);
			cargar_seguiendo(nom_fic_siguiendo, res_siguiendo);
			cargar_tweets(nom_fic_tweets, res_tweets);
		}

	private:
		//------------------------------------------------------------------
		// ATRIBUTOS: A DEFINIR POR EL ALUMNO
		//
		// Identificador del usuario
		// ... id_usuario;
		std::string id_usuario;
		// Lista de tweets
		// ... tweets;
		Tweets tweets;
		// Lista de usuarios a los que se estoy siguiendo
		// ... siguiendo;
		Usuarios siguiendo;
		// Lista de usuarios que me siguen
		// ... seguidores;
		Usuarios seguidores;
		//------------------------------------------------------------------

		//------------------------------------------------------------------
		// MÉTODOS PRIVADOS:
		//
		// Busca a un usuario en la lista ordenada de usuarios. Si lo
		// encuentra, devuelve la posición de la lista donde está. Si no,
		// devuelve la posición donde debería estar según el orden de la
		// lista.
		unsigned buscar_usuario(const Usuarios &usuarios, const std::string &user) const {
			// Variables
			unsigned pos = 0;
			unsigned numcaracter = 0;
			bool fin = false;
			// Bucle hasta encontrar la posición
			while (fin == false && pos <= usuarios.num_usuarios) {
				// Si estamos en la ultima posición finaliza bucle
				if (pos == usuarios.num_usuarios) {
					fin = true;
				}
				// Si la 'numcaracter' letra del usuario es menor, sigue iterando
				if ((fin == false) && (usuarios.listado[pos][numcaracter] < user[numcaracter])) {
					pos++;
					numcaracter = 0;
				}
				// Si la 'numcaracter' letra del usuario es mayor, posición encontrada
				else if ((fin == false) && (usuarios.listado[pos][numcaracter] > user[numcaracter])) {
					fin = true;
				}
				else if ((fin == false) && (usuarios.listado[pos][numcaracter] == user[numcaracter])) {
					if ((numcaracter < usuarios.listado[pos].length() - 1) && (numcaracter < user.length() - 1)) {
						numcaracter++;
					} 
					else if ((numcaracter == usuarios.listado[pos].length() - 1) || (numcaracter == user.length() - 1)){
						fin = true;
					}
				}
			}
			return pos;
		}

		// Inserta un usuario en la lista en la posición indicada
		// PRECONDICIÓN: el usuario cabe en la lista
		// PRECONDICIÓN: la posición es correcta
		void insertar_usuario_pos(Usuarios &usuarios, unsigned pos, const std::string &usuario) {
			// PRECONDICIÓN: el usuario cabe en la lista
			bool cabe = (usuarios.num_usuarios < MAX_USUARIOS) ? true : false;
			// PRECONDICIÓN: la posición es correcta
			bool posicion_correcta = (pos == buscar_usuario(usuarios, usuario)) ? true : false;
			// Si cumple, inserta un usuario en la lista en la posición indicada
			if (cabe && posicion_correcta) {
				// Añade 1 a la lista
				usuarios.num_usuarios++;
				// Bucle de reordenación desde el ultimo hasta llegar a pos
				for (unsigned i = usuarios.num_usuarios; i > pos; i--) {
					usuarios.listado[i] = usuarios.listado[i - 1];
				}
				// Y para finalizar, añadimos en la posición el usuario
				usuarios.listado[pos] = usuario;
			}
		}

		// Elimina un usuario de una posisición
		// PRECONDICIÓN: la posición es correcta
		void eliminar_usuario_pos(Usuarios &usuarios, unsigned pos) {
			// PRECONDICIÓN: la posición es correcta
			bool posicion_correcta = (pos >= 0 && pos < usuarios.num_usuarios) ? true : false;
			// Si todo va bien, eliminar usuario
			if (posicion_correcta) {
				// Elimino el usuario pisandolo con el siguiente
				for (unsigned i = pos; i < usuarios.num_usuarios - 1; i++) {
					usuarios.listado[i] = usuarios.listado[i + 1];
				}
				// Quito 1 de la cuenta de la lista
				usuarios.num_usuarios--;
			}
		}
	};
}
#endif