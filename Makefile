NAME = pipex

CC= gcc

CFLAGS = -Wall -Werror -Wextra -g

FSRCS = main.c \
		utils.c \
		utils2.c \


FBONUS = 



OFILES = $(FSRCS:.c=.o)

# OFBONUS = $(FBONUS:.c=.o)


all : $(NAME)

$(NAME) : $(OFILES)
	$(CC) $(CFLAGS) -o $(NAME) $(OFILES)

#bonus : $(OFBONUS)
#	$(NAME) $(OFBONUS)

# dans le clean penser a remettre le $(OFBONUS)
clean :
	rm -f $(OFILES) 

fclean : clean
	rm -f $(NAME)
	
re : fclean $(NAME)

.PHONY: all clean fclean re bonus