#pragma once

#include "fsm.h"

#define HANDLER_USPC_FSM_STEP(NAME_STEP)				static int NAME_STEP ( const fsm_step< user_string_parsing_class >* previous_step, user_string_parsing_class* obj )

class user_string_parsing_class {
public:
	user_string_parsing_class();
	void start_parsing ( char* string );

	HANDLER_USPC_FSM_STEP( fsm_step_func_team_search );
	HANDLER_USPC_FSM_STEP( fsm_step_func_team_search_fail );
	HANDLER_USPC_FSM_STEP( fsm_step_func_set_param );
	HANDLER_USPC_FSM_STEP( fsm_step_func_read_param );
	HANDLER_USPC_FSM_STEP( fsm_step_func_set_param_done );
	HANDLER_USPC_FSM_STEP( fsm_step_func_set_param_fail );
private:
	/// Указатель на текущий символ строки.
	char*										p = nullptr;

	/// Данные, которые мы будем считывать и записывать.
	int											data = 0;

	/// Конечный автомат.
	fsm_class< user_string_parsing_class >		fsm;
};
