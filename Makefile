RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

NAME = minishell
CC = cc
#CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
CFLAGS = -Wall -Wextra -Werror -g3
LDLIBS = -lreadline -lncurses

OS := $(shell uname)

ifeq ($(OS), Darwin)  # macOS
    target:
        READLINE = -lreadline -L ./readline -I ./readline -lcurses
else ifeq ($(OS), Linux)  # Linux
    target:
        READLINE = -L /usr/lib/x86_64-linux-gnu -lreadline -lncurses
else
    target:
		READLINE = -lreadline -L ./readline -I ./readline -lcurses
		READLINE = -L /usr/lib/x86_64-linux-gnu -lreadline -lncurses
        #@echo "Unsupported operating system: $(OS)"
        #@exit 1
endif


.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@ 

SRC = minishell \
		helpers/env \
		helpers/prompt \
		helpers/is_utils \
		helpers/ft_strlenn \
		parsing/parse \
		parsing/checker/check_oper \
		parsing/checker/check_chars \
		parsing/checker/check_pipe \
		parsing/checker/check_unsupport \
		parsing/add_space \
		parsing/split_args \
		parsing/token_input \
		parsing/parse_token \
		parsing/delete_quoate \
		parsing/expand/expand \
		parsing/expand/expand2 \
		parsing/split_by_pipe \
		parsing/count_cmds \
		builtins/unset \
		builtins/exit \
		builtins/pwd \
		builtins/echo \
		builtins/cd \
		builtins/export \
		builtins/env \
		execution/piping \
		execution/exec_cmd \
		execution/exec_builtins \
		execution/open_outfile \
		execution/open_infile \
		execution/dup_after_piping \
		execution/dup_before_piping \
		execution/multi_pipes_exec \
		execution/single_cmd_exec \
		execution/execute_line \
		execution/open_input_output \
		execution/init_shell_data \
		execution/heredoc_0x0 \
		execution/heredoc_0x1 \
		err_manage/args_error \
		err_manage/cmd_not_found \
		err_manage/check_fails \
		gnl/gnl \
		env/convert_env \
		env/get_env_value \

OBJ = $(SRC:=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@printf "$(YELLOW)Compiling minishell... %-10.10s$(RESET)\r" $@
	@make -s -C libft/
	@mv libft/libft.a .
	@$(CC) $(CFLAGS) $(READLINE) $(OBJ) -o $(NAME) $(READLINE) $(LDLIBS) libft.a
	@printf "$(GREEN)😎 minishell is ready           $(RESET)\n"

clean:
	@make -s clean -C libft/
	@rm -f $(OBJ)
	@rm -rf ./gnl/gnl.o
	@set -e; \
	i=0; \
	while [ $$i -le 10 ]; do \
		printf "$(YELLOW)Deleting objects...\r" $$((i * 10)); \
		sleep 0.35; \
		i=$$((i + 10)); \
	done
	@echo "$(GREEN)✅ Cleaning complete. $(RESET)"

fclean: clean
	@make -s fclean -C libft/
	@rm -f libft.a
	@rm -f $(NAME)
	@set -e; \
	i=0; \
	while [ $$i -le 10 ]; do \
		printf "$(YELLOW)Deleting executable... \r" $$((i * 10)); \
		sleep 0.35; \
		i=$$((i + 10)); \
	done
	@echo "$(GREEN)✅ Deletion complete. $(RESET)"

re: fclean all

