NAME 			= css_gen
#------------------------------------------------------------------------------#
#                  COLORS                                                      # 
#------------------------------------------------------------------------------#
RED			= \033[1;31m
GRE			= \033[1;32m
YEL			= \033[1;33m
BLU			= \033[1;34m
MAG			= \033[1;35m
CYA			= \033[1;36m
NO_COL 			= \033[0m

#------------------------------------------------------------------------------#
#                  COMMANDS                                                    # 
#------------------------------------------------------------------------------#
CC        		= clang++
ECHO      		= printf
RM        		= rm -rf
MAKE      		= make -s --no-print-directory -i

CFLAGS    		= -Wall -Werror -Wextra -std=c++98 -pedantic -g
CMACROS	  		= 
CHEADERS  		= -I . -I ./$(DIR_HDRS)
LDFLAGS   		= -L . -L ./$(DIR_HDRS)
ALL_FLAGS 		= $(CHEADERS) $(CFLAGS) $(CMACROS)

#------------------------------------------------------------------------------#
#                  FILES                                                       # 
#------------------------------------------------------------------------------#

DIR_SRCS 		= srcs/
DIR_HDRS 		= includes/
SRCS    		= $(addprefix $(DIR_SRCS), $(addsuffix .cpp, \
			  	AStatFile \
			  	HTMLFile \
			  	main \
			  ))
HDRS			= $(addprefix $(DIR_HDRS), $(addsuffix .hpp, \
			  	AStatFile \
			  	HTMLFile \
			  ))
OBJS			+= $(SRCS:.cpp=.o)

HTML 			= index.html
CSS 			= style.css

#------------------------------------------------------------------------------#
#                  RULES                                                       #
#------------------------------------------------------------------------------#
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(HDRS)
	@$(ECHO) "$(GRE)"
	@$(ECHO) "linking object... %-29.29s\r" $^
	@$(ECHO) "producing exec... %-29.29s\r" $@
	@$(CC) $(ALL_FLAGS) $(LDFLAGS) $(OBJS) -o $@
	@$(ECHO) "\t\t\t\t\t\t\tdone.\r"
	@$(ECHO) "\n"
	@$(ECHO) "$(NO_COL)"

%.o: %.cpp
	@$(ECHO) "$(GRE)"
	@$(ECHO) "producing object... %-29.29s\r" $@
	@$(CC) $(ALL_FLAGS) -c $< -o $@
	@$(ECHO) "$(NO_COL)"

clean:
	@$(ECHO) "$(RED)"
	@$(ECHO) "deleting .o... %-29.29s\r" $(OBJS)
	@$(RM) $(OBJS)
	@$(ECHO) "$(NO_COL)"

clean_test_files: clean
	@$(ECHO) "$(RED)"
	@$(ECHO) "deleting .o... %-29.29s %-29.29s\r" $(HTML) $(CSS)
	@$(RM) $(HTML) $(CSS)
	@$(ECHO) "$(NO_COL)"

fclean: clean_test_files
	@$(ECHO) "$(RED)"
	@$(ECHO) "deleting exec... %-39.39s\r" $(NAME)
	@$(ECHO) "\n"
	@$(RM) $(NAME) $(NAME).dSYM
	@$(ECHO) "$(NO_COL)"

re: fclean all

test: re
	./html_squeletor_generator.sh $(HTML) "Test_Me"
	./$(NAME) $(HTML) $(CSS)
	make clean
