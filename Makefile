NAME = pipex

CC= cc

CFLAGS = -Wall -Werror -Wextra -g

FSRCS = main.c \
		utils.c \
		utils2.c \
		fork_and_exec.c \
		get_path.c \
		open_file.c \

OFILES = $(FSRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OFILES)
	$(CC) $(CFLAGS) -o $(NAME) $(OFILES)

clean :
	rm -f $(OFILES) 

fclean : clean
	rm -f $(NAME)
	
re : fclean $(NAME)

.PHONY: all clean fclean re
