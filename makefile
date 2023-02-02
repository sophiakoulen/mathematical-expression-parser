CC=gcc
CFLAGS= -Wall -Wextra

DEBUG=1
FSAN=1

ifdef DEBUG
	CFLAGS += -g3
endif

ifdef FSAN
	CFLAGS += -fsanitize=address
endif

FILE_NAMES = main \
evaluate \
lexer \
parse_float \
parser \
print \
print_tree \
tree_ops \
args \
cleanup

SRCS = $(addsuffix .c, $(addprefix srcs/, $(FILE_NAMES)))
OBJS = $(addsuffix .o, $(addprefix objs/, $(FILE_NAMES)))

SRCS_DIR = srcs/
OBJS_DIR = objs/

NAME = eval

all: $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p objs
	$(CC) $(CFLAGS) -c -o $@ -Iinclude $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lm -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

db: all
	lldb ./$(NAME)
