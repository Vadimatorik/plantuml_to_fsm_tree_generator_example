CPP			:= g++
CPP_FLAGS	:= -O0 -g3 -Werror -Wall -Wextra -std=c++1z
LDFLAGS		:= -O0 -g3 -Werror -Wall -Wextra

PU			= plantuml_to_fsm_tree_generator/build/plantuml_to_fsm_tree_generator

# Собираем все необходимые данные из папки user_code.
USER_CPP_FILE			:= $(shell find user_code/ -maxdepth 5 -type f -name "*.cpp" )
USER_DIR				:= $(shell find user_code/ -maxdepth 5 -type d -name "*" )
USER_PATH				:= $(addprefix -I, $(USER_DIR))
USER_OBJ_FILE			:= $(addprefix build/obj/, $(USER_CPP_FILE))
USER_OBJ_FILE			:= $(patsubst %.cpp, %.o, $(USER_OBJ_FILE))

PROJECT_PATH			+= $(USER_PATH)
PROJECT_OBJ_FILE		+= $(USER_OBJ_FILE)

FSM_PU_FILE				= $(shell find user_code/ -maxdepth 5 -type f -name "*.pu" )
FSM_CPP_FILE			+= $(patsubst %.pu, %.cpp, $(FSM_PU_FILE))
FSM_OBJ_FILE			+= $(patsubst %.pu, build/obj/%.o, $(FSM_PU_FILE))
PROJECT_OBJ_FILE		+= $(FSM_OBJ_FILE)

include module_fsm/makefile

%.cpp:	%.pu
	@echo [PU] $<
	@$(PU) $< $@ user_string_parsing_class user_string_parsing.h

build/obj/%.o:	%.cpp
	@echo [CPP] $<
	@mkdir -p $(dir $@)
	@$(CPP) $(CPP_FLAGS) 				\
	$(PROJECT_PATH)						\
	-c $< -o $@


all: $(PROJECT_OBJ_FILE)
	@$(CPP) $(PROJECT_OBJ_FILE) -o build/example
	@size --format=Berkeley build/example

clean:
	@rm -R build/
	@echo Clean all!

pfsm_build:	
	mkdir -p plantuml_to_fsm_tree_generator/build
	cd plantuml_to_fsm_tree_generator/build && qmake -qt=qt5 .. && make

pfsm_clean:

	cd plantuml_to_fsm_tree_generator/ && rm -R build

pfsm_rebuild:
	cd plantuml_to_fsm_tree_generator/ && rm -R build
	mkdir plantuml_to_fsm_tree_generator/build
	cd plantuml_to_fsm_tree_generator/build && qmake -qt=qt5 .. && make
