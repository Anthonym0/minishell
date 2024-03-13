# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aherve <aherve@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/05 12:04:59 by aherve            #+#    #+#              #
#    Updated: 2024/03/11 17:50:35 by aherve           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
DEF_COLOR = \033[0;39m
BOLD_WHITE = \033[1;39m
BOLD_GREEN = \033[1;92m
BOLD_CYAN = \033[1;96m

# Program Name
NAME = minishell

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline

# Sources
SRC_PATH = srcs/

# Objects
OBJ_PATH = objs/

# Minishell
MINISHELL_SRC_PATH = srcs/minishell/
MINISHELL_SRC = minishell.c copy_env.c minishell_utils.c return_status.c ft_signals.c
MINISHELL_SRCS = $(addprefix $(MINISHELL_SRC_PATH), $(MINISHELL_SRC))
MINISHELL_OBJ_PATH = objs/minishell/
MINISHELL_OBJ = $(MINISHELL_SRC:.c=.o)
MINISHELL_OBJS = $(addprefix $(MINISHELL_OBJ_PATH), $(MINISHELL_OBJ))

# Prompt
PROMPT_SRC_PATH = srcs/prompt/
PROMPT_SRC = prompt_utils.c prompt.c
PROMPT_SRCS = $(addprefix $(PROMPT_SRC_PATH), $(PROMPT_SRC))
PROMPT_OBJ_PATH = objs/prompt/
PROMPT_OBJ = $(PROMPT_SRC:.c=.o)
PROMPT_OBJS = $(addprefix $(PROMPT_OBJ_PATH), $(PROMPT_OBJ))

# Parsing
PARSING_SRC_PATH = srcs/parsing/
PARSING_SRC = args.c check_pipes.c check_redirection_utils.c check_redirection.c cmd_utils.c cmds.c env_var_expansion_utils.c env_var_expansion.c fill_commands.c fill_commands_utils.c here_doc.c here_doc_utils.c parsing.c token_utils.c token.c trim_quotes.c
PARSING_SRCS = $(addprefix $(PARSING_SRC_PATH), $(PARSING_SRC))
PARSING_OBJ_PATH = objs/parsing/
PARSING_OBJ = $(PARSING_SRC:.c=.o)
PARSING_OBJS = $(addprefix $(PARSING_OBJ_PATH), $(PARSING_OBJ))

# Executer
EXECUTER_SRC_PATH = srcs/executer/
EXECUTER_SRC = execute_utils.c execute.c fds.c path_utils.c path.c redirections.c redirections_utils.c launcher.c builtin.c
EXECUTER_SRCS = $(addprefix $(EXECUTER_SRC_PATH), $(EXECUTER_SRC))
EXECUTER_OBJ_PATH = objs/executer/
EXECUTER_OBJ = $(EXECUTER_SRC:.c=.o)
EXECUTER_OBJS = $(addprefix $(EXECUTER_OBJ_PATH), $(EXECUTER_OBJ))

# Builtins
BUILTINS_SRC_PATH = srcs/builtins/
BUILTINS_SRC = cd.c echo.c pwd.c env.c export.c export_utils.c unset.c exit.c
BUILTINS_SRCS = $(addprefix $(BUILTINS_SRC_PATH), $(BUILTINS_SRC))
BUILTINS_OBJ_PATH = objs/builtins/
BUILTINS_OBJ = $(BUILTINS_SRC:.c=.o)
BUILTINS_OBJS = $(addprefix $(BUILTINS_OBJ_PATH), $(BUILTINS_OBJ))

# Utils
UTILS_SRC_PATH = srcs/utils/
UTILS_SRC = int_array.c double_tab.c ft_string.c ft_string_write.c access.c
UTILS_SRCS = $(addprefix $(UTILS_SRC_PATH), $(UTILS_SRC))
UTILS_OBJ_PATH = objs/utils/
UTILS_OBJ = $(UTILS_SRC:.c=.o)
UTILS_OBJS = $(addprefix $(UTILS_OBJ_PATH), $(UTILS_OBJ))

all: $(NAME)

# Linking and building of Minishell program
$(NAME): $(PROMPT_OBJS) $(MINISHELL_OBJS) $(PARSING_OBJS) $(EXECUTER_OBJS) $(BUILTINS_OBJS) $(UTILS_OBJS)
	@echo "[$(BOLD_GREEN)OK$(DEF_COLOR)] Linking objects"
	@$(CC) $(CFLAGS) -o $(NAME) $(MINISHELL_OBJS) $(PROMPT_OBJS) $(PARSING_OBJS) $(EXECUTER_OBJS) $(BUILTINS_OBJS) $(UTILS_OBJS) $(LDFLAGS)
	@echo "[$(BOLD_GREEN)OK$(DEF_COLOR)] Building $(BOLD_CYAN)$(NAME)$(DEF_COLOR)"

# Root objects' directory creation
$(OBJ_PATH):
	@mkdir $(OBJ_PATH)
	@echo "[$(BOLD_GREEN)OK$(DEF_COLOR)] Root objects' directory created"

# Minishell objects compilation
$(MINISHELL_OBJ_PATH)%.o: $(MINISHELL_SRC_PATH)%.c | $(MINISHELL_OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "[$(BOLD_GREEN)OK$(DEF_COLOR)] $(BOLD_WHITE)MINISHELL$(DEF_COLOR): Compiling $< --> $@"

# Minishell objects' directory creation
$(MINISHELL_OBJ_PATH): | $(OBJ_PATH)
	@mkdir $(MINISHELL_OBJ_PATH)
	@echo "[$(BOLD_GREEN)OK$(DEF_COLOR)] $(BOLD_WHITE)MINISHELL$(DEF_COLOR): Objects directory created"

# Prompt objects compilation
$(PROMPT_OBJ_PATH)%.o: $(PROMPT_SRC_PATH)%.c | $(PROMPT_OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "[$(BOLD_GREEN)OK$(DEF_COLOR)] $(BOLD_WHITE)PROMPT$(DEF_COLOR): $< --> $@"

# Prompt objects' directory creation
$(PROMPT_OBJ_PATH): | $(OBJ_PATH)
	@mkdir $(PROMPT_OBJ_PATH)
	@echo "[$(BOLD_GREEN)OK$(DEF_COLOR)] $(BOLD_WHITE)PROMPT$(DEF_COLOR): Objects directory created"

# Parsing objects compilation
$(PARSING_OBJ_PATH)%.o: $(PARSING_SRC_PATH)%.c | $(PARSING_OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "[$(BOLD_GREEN)OK$(DEF_COLOR)] $(BOLD_WHITE)PARSING$(DEF_COLOR): $< --> $@"

# Parsing objects' directory creation
$(PARSING_OBJ_PATH): | $(OBJ_PATH)
	@mkdir $(PARSING_OBJ_PATH)
	@echo "[$(BOLD_GREEN)OK$(DEF_COLOR)] $(BOLD_WHITE)PARSING$(DEF_COLOR): Objects directory created"

# Executer objects compilation
$(EXECUTER_OBJ_PATH)%.o: $(EXECUTER_SRC_PATH)%.c | $(EXECUTER_OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "[$(BOLD_GREEN)OK$(DEF_COLOR)] $(BOLD_WHITE)EXECUTER$(DEF_COLOR): $< --> $@"

# Executer objects' directory creation
$(EXECUTER_OBJ_PATH): | $(OBJ_PATH)
	@mkdir $(EXECUTER_OBJ_PATH)
	@echo "[$(BOLD_GREEN)OK$(DEF_COLOR)] $(BOLD_WHITE)EXECUTER$(DEF_COLOR): Objects directory created"

# Builtins objects compilation
$(BUILTINS_OBJ_PATH)%.o: $(BUILTINS_SRC_PATH)%.c | $(BUILTINS_OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "[$(BOLD_GREEN)OK$(DEF_COLOR)] $(BOLD_WHITE)BUILTINS$(DEF_COLOR): $< --> $@"

# Builtins objects' directory creation
$(BUILTINS_OBJ_PATH): | $(BUILTINS_PATH)
	@mkdir $(BUILTINS_OBJ_PATH)
	@echo "[$(BOLD_GREEN)OK$(DEF_COLOR)] $(BOLD_WHITE)BUILTINS$(DEF_COLOR): Objects directory created"

# Utils objects compilation
$(UTILS_OBJ_PATH)%.o: $(UTILS_SRC_PATH)%.c | $(UTILS_OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "[$(BOLD_GREEN)OK$(DEF_COLOR)] $(BOLD_WHITE)UTILS$(DEF_COLOR): $< --> $@"

# Utils objects' directory creation
$(UTILS_OBJ_PATH): | $(UTILS_PATH)
	@mkdir $(UTILS_OBJ_PATH)
	@echo "[$(BOLD_GREEN)OK$(DEF_COLOR)] $(BOLD_WHITE)UTILS$(DEF_COLOR): Objects directory created"

clean:
	@rm -rf $(OBJ_PATH)
	@echo "[$(BOLD_GREEN)OK$(DEF_COLOR)] Removing object files and directories"

fclean: clean
	@rm -rf $(NAME)
	@echo "[$(BOLD_GREEN)OK$(DEF_COLOR)] Removing $(BOLD_CYAN)$(NAME)$(DEF_COLOR)"

re: fclean $(NAME)

.PHONY: all clean fclean re