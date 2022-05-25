#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "usuario_twitter.hpp"

using namespace std;
using namespace bblProgII;

// Escribe el menú de opciones, lee la opción por teclado y la devuelve
char menu();

// Pulsar una tecla para continuar
void Seguir();

// Escribir resultado de operación por pantalla
void escribir_resultado(const Resultado res);


int main() {
	/*ALUMNO: declarar el objeto ada_lovelace, con identificador "ada_lovelace"*/ UsuarioTwitter usuario = UsuarioTwitter("ada_lovelace");
	string id_usuario;
	Tweet tweet;
	char opcion, seguir;
	unsigned num_tweets;
	unsigned num_usuarios;
	Resultado res_seg, res_sig, res_twt;
	time_t tSac; // instante actual
	tm tms;


	do {
		opcion = menu();
		switch (opcion) {
		case 'a': cout << "Usuario con id: @" << /*ALUMNO: obtener id de ada_lovelace ...*/ usuario.obtener_id() << endl;
			Seguir();
			break;
		case 'b': cout << "Introduzca el nombre del usuario a buscar: ";
			cin >> id_usuario; cin.ignore();
			if (/*ALUMNO: id_usuario sigue a ada_lovelace*/ usuario.me_sigue(id_usuario)) {
			cout << "El usuario @" << id_usuario << " me está siguiendo." << endl;
			}
			else {
				cout << "El usuario @" << id_usuario << " NO me está siguiendo." << endl;
			}
			Seguir();
			break;
		case 'c': cout << "Introduzca el nombre del usuario a buscar: ";
			cin >> id_usuario; cin.ignore();
			if (/*ALUMNO: ada_lovelace sigue a id_usuario*/usuario.estoy_siguiendo(id_usuario)) {
				cout << "Estoy siguiendo al usuario @" << id_usuario << endl;
			}
			else {
				cout << "NO estoy siguiendo al usuario @" << id_usuario << endl;
			}
			Seguir();
			break;
		case 'd': cout << "ESTADÍSTICAS DEL USUARIO:" << endl;
			cout << "Seguidores: " << /*ALUMNO: obtener seguidores de ada_lovelace*/ usuario.num_seguidores() << endl;
			cout << "Siguiendo: " << /*ALUMNO: obtener usuarios a los que sigue ada_lovelace*/ usuario.num_siguiendo() << endl;
			cout << "Tweets: " << /*ALUMNO: obtener cuántos tweets tiene ada_lovelace*/ usuario.num_tweets() << endl;
			Seguir();
			break;
		case 'e':
			cout << "Tiene actualmente " << /*ALUMNO: obtener cuántos seguidores tiene ada_lovelace*/ usuario.num_seguidores()  << " seguidores "
				<< " y está siguiendo a " << /*ALUMNO: obtener a cuántos sigue ada_lovelace*/ usuario.num_siguiendo()  << " usuarios " << endl;

			cout << "¿Número de usuarios a imprimir de ambas listas (0 -> todos): ";
			cin >> num_usuarios; cin.ignore();
			cout << "Su lista de seguidores: " << endl;
			/*ALUMNO: escribir por pantalla los seguidores de ada_lovelace*/ usuario.imprimir_seguidores(num_usuarios);
			cout << endl;
			cout << "Su lista de usuarios a los que sigue: " << endl;
			/*ALUMNO: escribir por pantalla la lista de usuarios a los que sigue ada_lovelace*/ usuario.imprimir_siguiendo(num_usuarios);
			cout << endl;
			Seguir();
			break;
		case 'f':
			cout << "Tiene actualmente " << /*ALUMNO: consultar cuántos tweets tiene ada_lovelace*/ usuario.num_tweets() << " tweets..." << endl;
			cout << "¿Número de tweets a imprimir (0 -> todos): ";
			cin >> num_tweets; cin.ignore();
			cout << "Estos son sus últimos tweets:" << endl;
			/*ALUMNO: escribir por pantalla los tweets de ada_lovelace*/ usuario.imprimir_tweets(num_tweets);
			Seguir();
			break;
		case 'g': cout << "Se guardarán todos los datos a fichero..." << endl;
			cout << "¡Atención! Los datos de los ficheros se sobreescribirán." << endl;
			do {
				cout << "¿Desea continuar (s/n)?: ";
				cin.get(seguir); cin.ignore();
			} while (tolower(seguir) != 's' && tolower(seguir) != 'n');
			if (seguir == 's') {
				id_usuario = /*ALUMNO: obtener el id de ada_lovelace*/
				/*ALUMNO...*/usuario.obtener_id();
				cout << "Guardando la lista de seguidores..." << endl;
				/*ALUMNO: guardar en ada_lovelace.seg los seguidores de ada_lovelace*/ usuario.guardar_seguidores(id_usuario + ".seg", res_seg);
				cout << "Guardando la lista de usuarios a los que sigo..." << endl;
				/*ALUMNO: guardar en ada_lovelace.sig los seguidores a los que sigue ada_lovelace*/ usuario.guardar_seguiendo(id_usuario + ".sig", res_sig);
				cout << "Guardando la lista de tweets..." << endl;
				/*ALUMNO: guardar en ada_lovelace.twt los tweets de ada_lovelace*/ usuario.guardar_tweets(id_usuario + ".twt", res_twt);
			}
			Seguir();
			break;
		case 'h': cout << "Introduzca el nuevo id del usuario: ";
			cin >> id_usuario; cin.ignore();
			/*ALUMNO: modificar el id de ada_lovelace*/ usuario.establecer_id(id_usuario);
			cout << "Nuevo id del usuario: " << /*ALUMNO: consultar el id de ada_lovelace*/usuario.obtener_id() << endl;
			Seguir();
			break;
		case 'i': cout << "Introduzca un tweet (máximo 140 caracteres): ";
			getline(cin, tweet.tweet);

			// PARA OBTENER LA HORA DEL ORDENADOR: --------
			tSac = time(NULL); // instante actual
			tms = *localtime(&tSac);
			tweet.fecha_hora.dia = unsigned(tms.tm_mday);
			tweet.fecha_hora.mes = unsigned(tms.tm_mon + 1);
			tweet.fecha_hora.anyo = unsigned(tms.tm_year + 1900);
			tweet.fecha_hora.hora = unsigned(tms.tm_hour);
			tweet.fecha_hora.minuto = unsigned(tms.tm_min);
			tweet.fecha_hora.segundo = unsigned(tms.tm_sec);
			//----------------------------------------------
			/*ALUMNO: insertar un nuevo tweet en la lista de tweets de ada_lovelace*/ usuario.nuevo_tweet(tweet, res_twt);
			escribir_resultado(res_twt);
			Seguir();
			break;
		case 'j': cout << "Introduzca el nombre del usuario seguidor: ";
			cin >> id_usuario; cin.ignore();
			/*ALUMNO: insertar un nuevo seguidor en la lista de seguidores de ada_lovelace*/ usuario.nuevo_seguidor(id_usuario, res_seg);
			escribir_resultado(res_seg);
			Seguir();
			break;
		case 'k': cout << "Introduzca el nombre del usuario a seguir: ";
			cin >> id_usuario;  cin.ignore();
			/*ALUMNO: insertar un nuevo usuario en la lista de usuarios a los que sigue ada_lovelace*/ usuario.nuevo_siguiendo(id_usuario, res_sig);
			escribir_resultado(res_sig);
			Seguir();
			break;
		case 'l': cout << "Introzca el nombre del usuario seguidor a eliminar: ";
			cin >> id_usuario;  cin.ignore();
			/*ALUMNO: eliminar id_usuario de la lista de seguidores de ada_lovelace*/ usuario.eliminar_seguidor(id_usuario, res_seg);
			escribir_resultado(res_seg);
			Seguir();
			break;
		case 'm': cout << "Introzca el nombre del usuario a eliminar de la lista de usuarios a los que sigo: ";
			cin >> id_usuario;  cin.ignore();
			/*ALUMNO: eliminar id_usuario de la lista de siguiendo de ada_lovelace*/ usuario.eliminar_siguiendo(id_usuario, res_sig);
			escribir_resultado(res_sig);
			Seguir();
			break;
		case 'n': cout << "Se cargarán todos los datos desde fichero..." << endl;
			cout << "¡Atención! Sus datos actuales se borrarán." << endl;
			do {
				cout << "¿Desea continuar (s/n)?: ";
				cin.get(seguir); cin.ignore();
			} while (tolower(seguir) != 's' && tolower(seguir) != 'n');
			if (seguir == 's') {
				id_usuario = /*ALUMNO: obtener id de ada_lovelace*/ usuario.obtener_id();
				/*ALUMNO: cargar todo (seguidores, siguiendo y tweets) de
				sus respectivos ficheros: ada_lovelace.seg, ada_lovelace.sig
				y ada_lovelace.twt*/ usuario.cargar_todo(id_usuario + ".seg", id_usuario + ".sig", id_usuario + ".twt", res_seg, res_sig, res_twt);
				cout << "Cargando la lista de seguidores..." << endl;
				escribir_resultado(res_seg);
				cout << "Cargando la lista de usuarios a los que sigo..." << endl;
				escribir_resultado(res_sig);
				cout << "Cargando la lista de tweets..." << endl;
				escribir_resultado(res_twt);
			}
			Seguir();
			break;
		}
	} while (opcion != 'x');
}

char menu() {
	char opcion;

	system("clear"); // Limpiamos la pantalla
	system("cls");

	do {
		cout << "MENÚ DE OPCIONES (elija una opción y pulse <enter>):" << endl << endl;
		cout << "a -> Obtener id del usuario" << endl;
		cout << "b -> Consultar si un usuario me sigue" << endl;
		cout << "c -> Consultar si estoy siguiendo a un usuario" << endl;
		cout << "d -> Imprimir mis estadísticas (seguidores, siguiendo, etc.)" << endl;
		cout << "e -> Imprimir mi lista de seguidores y usuarios a los que sigo" << endl;
		cout << "f -> Imprimir mi lista de tweets" << endl;
		cout << "g -> Guardar todos mis datos en fichero (seguidores, tweets, etc.)" << endl;
		cout << "h -> Modificar el id de mi usuario" << endl;
		cout << "i -> Insertar un nuevo tweet" << endl;
		cout << "j -> Insertar un nuevo seguidor en mi lista de seguidores" << endl;
		cout << "k -> Insertar un nuevo usuario en mi lista de usuarios a los que sigo" << endl;
		cout << "l -> Eliminar un usuario de mi lista de seguidores" << endl;
		cout << "m -> Eliminar un usuario de mi lista de usuarios a los que sigo" << endl;
		cout << "n -> Cargar todos los datos desde disco (se borran los actuales)" << endl;
		cout << "x -> SALIR DEL PROGRAMA" << endl;

		cin.get(opcion); cin.ignore(); opcion = char(tolower(int(opcion)));
	} while ((opcion < 'a' || opcion > 'n') && (opcion != 'x'));

	return opcion;
}

void Seguir() {
	string enter;

	cout << endl << "Pulse <enter> para continuar..." << endl;
	getline(cin, enter);
}


void escribir_resultado(const Resultado res) {
	switch (res) {
	case OK: cout << "Operación realizada correctamente." << std::endl;
		break;
	case LISTA_LLENA: cout << "Operación NO realizada: lista llena." << std::endl;
		break;
	case YA_EXISTE: cout << "Operación NO realizada: el elemento ya existe" << std::endl;
		break;
	case NO_EXISTE: cout << "Operación NO realizada: el elemento no existe" << std::endl;
		break;
	case FIC_ERROR: cout << "Error en la apertura de fichero" << std::endl;
	}
}