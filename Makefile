NAME = minishell
CC = cc
CFLAGS =  -Wall -Wextra -Werror -Ilibft

OS := $(shell uname)

READLINE_PREFIX := $(shell brew --prefix readline 2>/dev/null)

ifeq ($(OS), Darwin)
	ifeq ($(READLINE_PREFIX),)
		READLINE_PREFIX = /opt/homebrew/opt/readline
	endif
endif

ifneq ($(READLINE_PREFIX),)
	CFLAGS += -I$(READLINE_PREFIX)/include
	READLINEFLAGS = -L$(READLINE_PREFIX)/lib -lreadline
else
	READLINEFLAGS = -lreadline
endif

INCLUDES = -Iincludes

OBJDIR = .obj
GITLIBFT = https://github.com/BahaBerkPancar/Libft-42.git
LIBFT = libft/libft.a

SRCS = parse/parse.c minishell.c ext/new_node.c ext/ft_lstprint.c ext/find_char.c execute/exec_utils.c\
	ext/last_node.c ext/type.c ext/checks.c ext/ft_strcmp.c built_ins/pwd.c  execute/execute_helper.c\
	parse/doubleqoute.c parse/singlequote.c ext/free.c parse/count.c execute/execute.c env/set_path.c \
	env/env.c ext/delete_node.c built_ins/export.c built_ins/unset.c ext/exit.c ext/heredoc.c \
	built_ins/builtin.c built_ins/echo.c execute/execute_requirements.c ext/count_args.c signals.c built_ins/cd.c built_ins/export_utils.c env/handle_variable.c

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

# Colors
COLOR_RESET = \033[0m
COLOR_RED = \033[0;31m
COLOR_GREEN = \033[0;32m
COLOR_YELLOW = \033[0;33m
COLOR_BLACK = \033[0;30m
COLOR_BOLD_RED = \033[1;31m

all: check_dir $(NAME)

check_dir:
	@if [ ! -d "libft" ]; then \
		clear; \
		echo "$(COLOR_RED)You need to clone libft! ❌"; \
		echo "$(COLOR_YELLOW) Running 'make clone'"; \
		$(MAKE) clone;\
	fi

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C libft

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINEFLAGS) -o $(NAME)
	@echo "$(COLOR_BLACK)@ DONE $(NAME) ✅$(COLOR_RESET)"

clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) clean -C libft > /dev/null 2>&1
	@echo "$(COLOR_RED)@ Cleaned All Objects$(COLOR_RESET)"

clone:
	@echo "$(COLOR_GREEN)@ Cloning libft...$(COLOR_RESET)"
	@git clone $(GITLIBFT) libft
	@$(MAKE) -C libft > /dev/null 2>&1
	@$(MAKE) bonus -C libft > /dev/null 2>&1
	@echo "$(COLOR_GREEN)@ Cloned libft ✅$(COLOR_RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(COLOR_RED)@ Cleaned $(NAME)$(COLOR_RESET)"

re: fclean all

full-clean: fclean
	@rm -rf libft
	@echo "$(COLOR_BOLD_RED)🌀 You Have Cleared Everything$(COLOR_RESET)"

run: all
	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell

rule: 
	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp  ./minishell


.PHONY: all clean fclean re clone run full-clean ru
