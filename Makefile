NAME = webser

GG = c++

Header1 =  Webserv.hpp Request/HandleRequest.hpp Request/Getdata.hpp

VERSION = -std=c++98  -Wall -Wextra -Werror 

# -g -fsanitize=address,undefined,integer

SRC =	main.cpp	\
		parsing/server.cpp	\
		Run_serv/run_server.cpp	\
		Request/HandleRequest.cpp	\
		Request/Getdata.cpp	\
		Request/Response.cpp	\

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
