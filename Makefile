NAME = webser

GG = c++

Header1 =  Webserv.hpp

VERSION = -std=c++98  -Wall -Wextra -Werror 


SRC =	main.cpp									\
		parsing/server.cpp							\
		Run_serv/run_server.cpp						\

OBJECTS = $(SRC:.cpp=.opp)

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(GG) $(VERSION) $(OBJECTS) -o $(NAME) 

%.opp : %.cpp $(Header1) $(Header2)
	@$(GG) $(VERSION)  -o $@ -c $<

clean:
	@rm -rf $(OBJECTS)
fclean: clean
	@rm -rf $(NAME)

re: fclean all
