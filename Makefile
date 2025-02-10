NAME = pipex

CC= cc

CFLAGS = -Wall -Werror -Wextra -g

FSRCS = close_fd.c \
		fork_and_exec.c \
		free.c \
		ft_split.c \
		get_path.c \
		init_struct.c \
		main.c \
		open_file.c \
		utils.c \
		verify.c \

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
