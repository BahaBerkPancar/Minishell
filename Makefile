NAME = minishell
GCC = cc
CFLAGS = -Wall -Wextra -Werror -I/opt/homebrew/Cellar/readline/8.2.13/include -Ilibft

READLINEFLAGS = -L/opt/homebrew/Cellar/readline/8.2.13/lib -lreadline -lhistory
INCLUDES = -I./include

OBJDIR = .obj
GITLIBFT = git@github.com:BahaBerkPancar/Libft-42.git
LIBFT = libft/libft.a

SRCS = parse/parse.c parse/operations.c minishell.c ext/new_node.c ext/ft_lstprint.c ext/find_char.c ext/last_node.c ext/type.c ext/checks.c ext/ft_strcmp.c built_ins/pwd.c built_ins/tmp.c parse/doubleqoute.c parse/singlequote.c ext/free.c parse/temp.c execute.c env/set_path.c env/env.c ext/delete_node.c built_ins/export.c built_ins/unset.c ext/exit.c ext/heredoc.c
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

#################################################### COLORS ####################################################
COLOR_RESET         = \033[0m
COLOR_RED           = \033[0;31m
COLOR_GREEN         = \033[0;32m
COLOR_BLACK         = \033[0;30m
COLOR_BOLD_RED      = \033[1;31m
################################################################################################################

check_dir:
	@if [ ! -d "libft" ]; then \
		clear; \
		echo "$(COLOR_RED)You need to clone libft! ❌"; \
		echo "$(COLOR_YELLOW) Running 'make clone'"; \
		$(MAKE) clone;\
		$(MAKE) $(NAME);\
	else \
		$(MAKE) $(NAME); \
	fi

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	@$(GCC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: check_dir $(NAME)

$(NAME): $(OBJS)
	@$(GCC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINEFLAGS) -g -o $(NAME)
	@clear
	@echo "$(COLOR_BLACK)@ DONE $(NAME) ✅$(COLOR_RESET)"

clean:
	@rm -rf $(OBJDIR)
	@make clean -C libft > /dev/null 2>&1
	@echo "$(COLOR_RED)@ Cleaned All Objects$(COLOR_RESET)"
	@sleep 2
	@clear

clone:
	@echo "$(COLOR_GREEN)@ Cloning libft...$(COLOR_RESET)"
	@git clone $(GITLIBFT) libft
	@make -C libft > /dev/null 2>&1
	@make bonus -C libft > /dev/null 2>&1
	@echo "$(COLOR_GREEN)@ Cloned libft ✅$(COLOR_RESET)"
	@clear

fclean: clean
	@rm -rf $(NAME)
	@make clean -C libft > /dev/null 2>&1
	@echo "$(COLOR_RED)@ Cleaned $(NAME)$(COLOR_RESET)"
	@sleep 2
	@clear

re: fclean
	@$(MAKE) all
	@echo "$(COLOR_GREEN)@ Remaken$(COLOR_RESET)"
	@sleep 2
	@clear

clear: fclean
	@clear
	@rm -rf libft
	@echo "$(COLOR_BOLD_RED)🌀 You Have Cleared Everything$(COLOR_RESET)"
	@sleep 2
	@clear

run: all
	@./$(NAME) "files/infile" "ls -l" "grep p" "files/outfile"
	@sleep 3
	@clear

display: all
	@./$(NAME) "files/infile" "ls -l" "grep b" "files/outfile"

fsanitize: $(OBJS)
	@$(GCC) -fsanitize=address -g $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@./$(NAME) files/infile "ls -l" "grep b" files/outfile

.PHONY: all clean fclean re clear run display
