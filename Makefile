NAME = pipex

CC= gcc

CFLAGS = -Wall -Werror -Wextra -g

FSRCS = main.c \

FBONUS = 



OFILES = $(FSRCS:.c=.o)

OFBONUS = $(FBONUS:.c=.o)

ARRC=ar -rc

all : $(NAME)

$(NAME) : $(OFILES)
		$(ARRC) $(NAME) $(OFILES)

bonus : $(OFBONUS)
		$(ARRC) $(NAME) $(OFBONUS)
		
clean :
	rm -f $(OFILES) $(OFBONUS)

fclean : clean
	rm -f $(NAME)
	
re : fclean $(NAME)

.PHONY: all clean fclean re bonus