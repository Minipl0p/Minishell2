# ============================================================================#
#                                   Makefile                                  #
# ============================================================================#

# --- Couleurs ---------------------------------------------------------------
ESC=\033
RESET=\033[0m
BOLD=$(ESC)[1m

PRIMARY = $(BOLD)$(ESC)[38;2;73;212;117m
INFO    = $(ESC)[38;2;52;170;94m
ACCENT  = $(ESC)[38;2;34;120;70m
WARN    = $(ESC)[38;2;120;140;125m
ERROR   = $(BOLD)$(ESC)[38;2;180;50;50m

# --- header -----------------------------------------------------------------
define HEADER
$(ESC)[38;2;120;235;155m ██▄  ▄██ ██ ███  ██ ██ ▄█████ ██  ██ ██████ ██     ██  
$(ESC)[38;2;73;212;117m ██ ▀▀ ██ ██ ██ ▀▄██ ██ ▀▀▀▄▄▄ ██████ ██▄▄   ██     ██  
$(ESC)[38;2;34;120;70m ██    ██ ██ ██   ██ ██ █████▀ ██  ██ ██▄▄▄▄ ██████ ██████
endef
export HEADER

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
SUBDIRS := heredocs signals ast dict expand exec exec/pipeline lex readline banner builtin expand/wildcards errors

# --- Sources (sans nom de dossier !) ----------------------------------------
SRC_MAIN := main.c

SRC_AST  := ast_tools.c destroy.c create_ast.c pars_cmd.c \
            pars_pipe.c pars_redir.c pars_subtree.c 

SRC_DICT := convert_dict.c init_d_env.c

SRC_BANNER := banner.c banner_utils.c

SRC_HERE := heredocs_fork.c heredocs.c heredocs_write.c

SRC_SIGN := signals.c

SRC_EXP  := expand.c expand_utils.c expand_argv.c expand_heredocs.c expand_interpretor.c expand_redir.c

SRC_WILD := expand_wildcards.c trunc.c trunc_middle.c trunc_utils.c quotes.c 

SRC_EXEC := exec.c exec_cmd.c

SRC_EXEC_P := pipeline_builder.c fd.c path.c pipeline.c pipeline_utils.c

SRC_ERROR := errors.c error_kaam.c

SRC_LEX  := lex.c token.c word_utils.c token_utils.c

SRC_RL   := readline.c

SRC_BUILT_IN := cd.c echo.c export_no_arg.c pwd.c unset.c env.c exit.c banner_builtin.c export_new.c

# -----------------------------------------------------------------------------

SRCS := $(SRC_MAIN) $(SRC_AST) $(SRC_SIGN) $(SRC_HERE) $(SRC_DICT) $(SRC_EXP) $(SRC_BANNER) $(SRC_EXEC) $(SRC_EXEC_P) $(SRC_LEX) $(SRC_RL) \
		$(SRC_BUILT_IN) $(SRC_WILD) $(SRC_ERROR)

# --- PATH -------------------------------------
VPATH := $(SRCDIR) $(addprefix $(SRCDIR)/, $(SUBDIRS))

# --- OBJECTS -----------------------------------------------------------------
OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)

# --- COMMANDS --------------------------------------------------------------
RM      := rm -rf
MKDIR   := mkdir -p

# --- PHONY ------------------------------------------------------------------
.PHONY: all clean fclean re lib header

# --- RULES -----------------------------------------------------------------
all: header lib $(NAME)

header:
	@printf "\n"
	@printf "$(BOLD)$$HEADER\n$(RESET)"
	@printf "\n"

$(NAME): $(OBJS)
	@printf "$(INFO)\nLinking $@...$(RESET)\n"
	@$(CC) $(OBJS) $(LFLAGS) -o $@
	@printf "$(PRIMARY)Built $@$(RESET)\n"

$(OBJDIR)/%.o: %.c
	@$(MKDIR) $(OBJDIR)
	@printf "\r$(ESC)[K$(ACCENT)Compiling $< -> $@$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

lib:
	@printf "$(INFO)Building libft...\n"
	@printf "$(WARN)"
	@test -d $(LIBFT) || git clone git@github.com:Minipl0p/libft_perso.git $(LIBFT) --depth=1
	@printf "$(RESET)"
	@$(MAKE) --no-print-directory -C $(LIBFT)
	@printf "$(SUCCESS)libft ready$(RESET)\n"

clean: header
	@printf "$(ERROR)Cleaning objects...$(RESET)\n"
	@$(RM) $(OBJDIR)
	@if [ -d "$(LIBFT)" ]; then \
		printf "$(ACCENT)Cleaning libft...$(RESET)\n"; \
		$(MAKE) --no-print-directory -C $(LIBFT) clean; \
	fi

fclean: header clean
	@printf "$(ERROR)Removing binary and libft...$(RESET)\n"
	@$(RM) $(NAME) $(LIBFT)

re: header fclean all
