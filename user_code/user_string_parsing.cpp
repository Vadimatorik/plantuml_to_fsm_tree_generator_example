#include "user_string_parsing.h"
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <errno.h>

using namespace std;

/// Имя вершины формируется как:
/// имя классе + имя старового метода + _fsm_step
/// user_string_parsing_class_ + team_search + _fsm_step
extern	const fsm_step< user_string_parsing_class > \
		user_string_parsing_class_team_search_fsm_step;

user_string_parsing_class::user_string_parsing_class() {
	/// Производим связывание машины состояния с начальным шагом и объектом.
	this->fsm.relinking( &user_string_parsing_class_team_search_fsm_step, this );
}

void user_string_parsing_class::start_parsing ( char* string ) {
	/// Сохраняем указатель на сообщение, которое будем проверять.
	this->p = string;

	/// Запускаем анализ сообщения.
	this->fsm.start();
}

#define FSM_F_USPC	\
	const fsm_step< user_string_parsing_class >* \
	previous_step, user_string_parsing_class* obj

int user_string_parsing_class::fsm_step_func_team_search ( FSM_F_USPC ) {
	( void )previous_step;
	if ( strncmp( obj->p, "set", sizeof( "set" ) - 1 ) == 0 ) {
		obj->p += sizeof( "set" );
		return 1;
	}
	if ( strcmp( obj->p, "read" ) == 0 ) {
		return 2;
	}
	return 0;
}

int user_string_parsing_class::fsm_step_func_team_search_fail ( FSM_F_USPC ) {
	( void )previous_step;
	( void )obj;
	cout << "Command search fail! Available commands: set, read." << endl << endl;
	return 0;
}

int user_string_parsing_class::fsm_step_func_set_param ( FSM_F_USPC ) {
	( void )previous_step;
	int r;
	r = sscanf( obj->p, "%d", &obj->data );
	return ( r == 1 ) ? 0 : 1;
}

int user_string_parsing_class::fsm_step_func_read_param ( FSM_F_USPC ) {
	( void )previous_step;
	cout << "Data = " << obj->data << endl;
	return 0;
}

int user_string_parsing_class::fsm_step_func_set_param_done ( FSM_F_USPC ) {
	( void )previous_step;
	( void )obj;
	cout << "The parameter done set!" << endl << endl;
	return 0;
}

int user_string_parsing_class::fsm_step_func_set_param_fail ( FSM_F_USPC ) {
	( void )previous_step;
	( void )obj;
	cout << "The parameter must be int!" << endl << endl;
	return 0;
}
