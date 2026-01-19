# ============================================================================ #
#                                   LIBFT                                      #
# ============================================================================ #

# --- Colors ------------------------------------------------------------------
RED     := \033[0;31m
GREEN   := \033[0;32m
BLUE    := \033[0;34m
NC      := \033[0m

# --- Config ------------------------------------------------------------------
NAME    := libft.a
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -g
AR      := ar rcs
RM      := rm -rf
MKDIR   := mkdir -p

# --- Paths -------------------------------------------------------------------
SRCDIR  := src
OBJDIR  := obj
INCDIR  := include

# ============================================================================ #
#                                   SOURCES                                    #
# ============================================================================ #

# --- Char --------------------------------------------------------------------
SRCS_CHAR := \
	src/char/ft_isalnum.c \
	src/char/ft_isalpha.c \
	src/char/ft_isascii.c \
	src/char/ft_isdigit.c \
	src/char/ft_isprint.c \
	src/char/ft_isspace.c \
	src/char/ft_tolower.c \
	src/char/ft_toupper.c

# --- Memory ------------------------------------------------------------------
SRCS_MEMORY := \
	src/memory/ft_bzero.c \
	src/memory/ft_calloc.c \
	src/memory/ft_memchr.c \
	src/memory/ft_memcmp.c \
	src/memory/ft_memcpy.c \
	src/memory/ft_memmove.c \
	src/memory/ft_memset.c

# --- String ------------------------------------------------------------------
SRCS_STRING := \
	src/string/ft_strlen.c \
	src/string/ft_strdup.c \
	src/string/ft_strndup.c \
	src/string/ft_strchr.c \
	src/string/ft_strrchr.c \
	src/string/ft_strncmp.c \
	src/string/ft_strcmp.c \
	src/string/ft_strcpy.c \
	src/string/ft_strcat.c \
	src/string/ft_strlcpy.c \
	src/string/ft_strlcat.c \
	src/string/ft_strjoin.c \
	src/string/ft_strtrim.c \
	src/string/ft_substr.c \
	src/string/ft_strnstr.c \
	src/string/ft_striteri.c \
	src/string/ft_strmapi.c \
	src/string/ft_split.c \
	src/string/ft_strjoin_wish.c

# --- Convert -----------------------------------------------------------------
SRCS_CONVERT := \
	src/convert/ft_atoi.c \
	src/convert/ft_atol.c \
	src/convert/ft_atof.c \
	src/convert/ft_itoa.c

# --- IO ----------------------------------------------------------------------
SRCS_IO := \
	src/io/ft_putchar_fd.c \
	src/io/ft_putstr_fd.c \
	src/io/ft_putendl_fd.c \
	src/io/ft_putnbr_fd.c \
	src/io/ft_puterror.c

# --- Printf ------------------------------------------------------------------
SRCS_PRINTF := \
	src/printf/ft_printf.c \
	src/printf/vd_printf.c \
	src/printf/ft_putchar_printf.c \
	src/printf/ft_putstr_printf.c \
	src/printf/ft_putnbr_printf.c \
	src/printf/ft_putnbr_base_printf.c

# --- List --------------------------------------------------------------------
SRCS_LIST := \
	src/list/ft_lstnew.c \
	src/list/ft_lstadd_front.c \
	src/list/ft_lstadd_back.c \
	src/list/ft_lstlast.c \
	src/list/ft_lstsize.c \
	src/list/ft_lstdelone.c \
	src/list/ft_lstclear.c \
	src/list/ft_lstiter.c \
	src/list/ft_lstmap.c

# --- Utils -------------------------------------------------------------------
SRCS_UTILS := \
	src/utils/ft_countwordsep.c \
	src/utils/ft_free_arr.c

# --- GNL ---------------------------------------------------------------------
SRCS_GNL := \
	src/gnl/get_next_line.c \
	src/gnl/get_next_line_utils.c

# --- LISTDB ---------------------------------------------------------------------
SRCS_LISTDB := \
	src/listdb/ft_dbadd_back.c \
	src/listdb/ft_dbadd_front.c \
	src/listdb/ft_dbremove.c \
	src/listdb/ft_dbnew.c \
	src/listdb/ft_dbclear.c \
	src/listdb/ft_dbdelone.c \
	src/listdb/ft_dbsize.c \
	src/listdb/ft_dbfirst.c \
	src/listdb/ft_dbinsert_add.c \
	src/listdb/ft_dbinsert_idx.c \
	src/listdb/ft_dbiter.c \
	src/listdb/ft_dblast.c \
	src/listdb/ft_dbmap.c

# --- BTREE ---------------------------------------------------------------------
SRCS_BTREE := \
	src/btree/btree_infix.c \
	src/btree/btree_insert.c \
	src/btree/btree_clear.c \
	src/btree/btree_new.c \
	src/btree/btree_postfix.c \
	src/btree/btree_prefix.c \
	src/btree/btree_search.c

# --- DICT ---------------------------------------------------------------------
SRCS_DICT := \
	src/dict/dict_clear.c \
	src/dict/dict_create.c \
	src/dict/dict_destroy.c \
	src/dict/dict_get.c \
	src/dict/dict_hash.c \
	src/dict/dict_iter.c \
	src/dict/dict_remove.c \
	src/dict/dict_set.c

# --- All sources -------------------------------------------------------------
SRCS := \
	$(SRCS_CHAR) \
	$(SRCS_MEMORY) \
	$(SRCS_STRING) \
	$(SRCS_CONVERT) \
	$(SRCS_IO) \
	$(SRCS_PRINTF) \
	$(SRCS_LIST) \
	$(SRCS_UTILS) \
	$(SRCS_LISTDB) \
	$(SRCS_BTREE) \
	$(SRCS_DICT) \
	$(SRCS_GNL)

# --- Objects -----------------------------------------------------------------
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# ============================================================================ #
#                                   RULES                                      #
# ============================================================================ #

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@printf "$(BLUE)📦 Archiving $(NAME)...$(NC)\n"
	@$(AR) $(NAME) $(OBJS)
	@printf "$(GREEN)✅ $(NAME) ready$(NC)\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(MKDIR) $(dir $@)
	@$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	@printf "$(RED)🧹 Cleaning objects...$(NC)\n"
	@$(RM) $(OBJDIR)

fclean: clean
	@printf "$(RED)🗑️ Removing $(NAME)...$(NC)\n"
	@$(RM) $(NAME)

re: fclean all
