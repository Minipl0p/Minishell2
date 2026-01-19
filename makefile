# ============================================================================#
# 									Makefile								  #
# ============================================================================#

# --- Couleurs ANSI -----------------------------------------------------------
RED				:= \033[0;31m
GREEN			:= \033[0;32m
YELLOW			:= \033[0;33m
BLUE			:= \033[0;34m
NC				:= \033[0m # No Color

# --- Configuration -----------------------------------------------------------
NAME   			:= minishell
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror $(INCDIR)

# --- Chemins -----------------------------------------------------------------
SRCDIR			:= src
INCDIR			:= Includes
OBJDIR			:= obj

# --- Sources et objets -------------------------------------------------------
SRCS :=	src/main.c \
		src/pars.c \
		src/minilib.c \
		src/init.c \
		src/routine.c \
		src/monitoring.c \
		src/fork.c \

OBJS		:= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# --- Commandes utiles --------------------------------------------------------
RM			:= rm -rf
MKDIR		:= mkdir -p

# --- Phony targets -----------------------------------------------------------
.PHONY: all clean fclean re run help bonus

# --- Règles ------------------------------------------------------------------
all: $(NAME)
bonus: $(NAME_BONUS)

$(NAME): $(OBJS)
	@printf "$(BLUE)🔗 Linking $@...$(NC)\n"
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@printf "$(GREEN)✅ Built $@$(NC)\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(MKDIR) $(dir $@)
	@printf "$(YELLOW)🔨 Compiling $< -> $@$(NC)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "$(RED)🧹 Cleaning objects...$(NC)\n"
	@$(RM) $(OBJDIR) $(OBJDIR_BONUS)

fclean: clean
	@$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

run: re
	$(shell ./minishell)

help:
	@echo "$(BLUE)=== Makefile Help ===$(NC)"
	@echo "$(BLUE)NAME:$(NC) $(NAME)"
	@echo "$(BLUE)SRCS:$(NC) $(SRCS)"
	@echo "$(BLUE)OBJS:$(NC) $(OBJS)"
	@echo "$(BLUE)LIB:$(NC) $(LIB)"
