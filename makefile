# ============================================================================#
#                                   Makefile                                  #
# ============================================================================#

# --- Couleurs ---------------------------------------------------------------
RED     := \033[0;31m
GREEN   := \033[0;32m
YELLOW  := \033[0;33m
BLUE    := \033[0;34m
NC      := \033[0m

# --- Configuration ----------------------------------------------------------
NAME    := minishell
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -g -IIncludes
LFLAGS  := -Llibft -lft -lreadline

# --- Dossiers ---------------------------------------------------------------
SRCDIR  := src
OBJDIR  := obj
LIBFT   := libft

# --- Sous-dossiers sources --------------------------------------------------
SUBDIRS := ast dict expand exec lex readline banner

# --- Sources (sans nom de dossier !) ----------------------------------------
SRC_MAIN := main.c

SRC_AST  := ast_tools.c destroy.c pars_and.c pars_or.c pars_cmd.c \
            pars_pipe.c pars_redir.c pars_subtree.c print_ast.c

SRC_DICT := convert_dict.c init_d_env.c

SRC_BANNER := banner.c banner_utils.c

SRC_EXP  :=

SRC_EXEC :=

SRC_LEX  := lex.c token.c word_utils.c

SRC_RL   := readline.c

SRCS := $(SRC_MAIN) $(SRC_AST) $(SRC_DICT) $(SRC_EXP) $(SRC_BANNER) $(SRC_EXEC) $(SRC_LEX) $(SRC_RL)

# --- PATH -------------------------------------
VPATH := $(SRCDIR) $(addprefix $(SRCDIR)/, $(SUBDIRS))

# --- OBJECTS -----------------------------------------------------------------
OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)

# --- COMMANDS --------------------------------------------------------------
RM      := rm -rf
MKDIR   := mkdir -p

# --- PHONY ------------------------------------------------------------------
.PHONY: all clean fclean re lib

# --- RULES -----------------------------------------------------------------
all: lib $(NAME)

$(NAME): $(OBJS)
	@printf "$(BLUE)🔗 Linking $@...$(NC)\n"
	@$(CC) $(OBJS) $(LFLAGS) -o $@
	@printf "$(GREEN)✅ Built $@$(NC)\n"

$(OBJDIR)/%.o: %.c
	@$(MKDIR) $(OBJDIR)
	@printf "$(YELLOW)🔨 Compiling $< -> $@$(NC)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

lib:
	@printf "$(BLUE)📦 Building libft...$(NC)\n"
	@test -d $(LIBFT) || git clone git@github.com:Minipl0p/libft_perso.git $(LIBFT) --depth=1
	@$(MAKE) --no-print-directory -C $(LIBFT)
	@printf "$(GREEN)📦 libft ready$(NC)\n"

clean:
	@printf "$(RED)🧹 Cleaning objects...$(NC)\n"
	@$(RM) $(OBJDIR)
	@if [ -d "$(LIBFT)" ]; then \
		printf "$(RED)🧹 Cleaning libft...$(NC)\n"; \
		$(MAKE) --no-print-directory -C $(LIBFT) clean; \
	fi

fclean: clean
	@printf "$(RED)🧹 Removing binary and libft...$(NC)\n"
	@$(RM) $(NAME) $(LIBFT)

re: fclean all
