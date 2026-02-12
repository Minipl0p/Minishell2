
#include <stdio.h>

/* ========================================================================== */
/* COULEURS DEBUG                               */
/* ========================================================================== */
#define C_RESET  "\033[0m"
#define C_RED    "\033[31m"
#define C_GREEN  "\033[32m"
#define C_YELLOW "\033[33m"
#define C_BLUE   "\033[34m"
#define C_MAG    "\033[35m"
#define C_CYAN   "\033[36m"

/* ========================================================================== */
/* HELPERS D'AFFICHAGE                           */
/* ========================================================================== */

// Affiche les redirections d'un noeud
static void print_redirs_debug(t_redir *r)
{
    while (r)
    {
        printf(C_YELLOW " [");
        if (r->type == R_IN) printf("< ");
        else if (r->type == R_OUT) printf("> ");
        else if (r->type == R_APPEND) printf(">> ");
        else if (r->type == R_HEREDOC) printf("<< ");
        
        printf("%s]" C_RESET, r->target ? r->target : "NULL");
        r = r->next;
    }
}

// Affiche les arguments d'une commande
static void print_argv_debug(char **argv)
{
    int i = 0;
    if (!argv) return;
    while (argv[i])
    {
        printf(" \"%s\"", argv[i]);
        i++;
    }
}

// Convertit l'enum type en string lisible
static char *get_type_str(t_ast_type type)
{
    switch (type)
    {
        case AST_PIPE:    return (C_MAG "PIPE" C_RESET);
        case AST_AND:     return (C_RED "AND (&&)" C_RESET);
        case AST_OR:      return (C_RED "OR (||)" C_RESET);
        case AST_COMMAND: return (C_GREEN "CMD" C_RESET);
        case AST_SUBTREE: return (C_CYAN "SUBTREE (Parens)" C_RESET);
        default:          return ("UNKNOWN");
    }
}

/* ========================================================================== */
/* FONCTION RECURSIVE                               */
/* ========================================================================== */
static void recursive_print_ast(t_btree *node, int level, char *prefix)
{
    if (!node)
        return;

    t_ast_node *ast = (t_ast_node *)node->content;

    // 1. Affichage de l'indentation
    for (int i = 0; i < level; i++)
        printf("    ");
    
    // 2. Affichage du préfixe (ROOT, ├──, └──)
    printf("%s ", prefix);

    // 3. Affichage du contenu
    if (ast)
    {
        printf("%s", get_type_str(ast->type));
        
        if (ast->type == AST_COMMAND)
        {
            print_argv_debug(ast->argv);
            print_redirs_debug(ast->redirs);
        }
        else if (ast->type == AST_SUBTREE)
        {
            // On affiche les redirs appliquées à TOUTE la parenthèse
            // Ex: (ls) > file
            print_redirs_debug(ast->redirs);
        }
        printf("\n");
    }

    // 4. Récursion
    if (node->left) 
    {
        // Si c'est un subtree, le contenu est "en dessous"
        // On garde le même niveau ou on augmente un peu pour l'effet visuel
        char *sub_pref = (ast && ast->type == AST_SUBTREE) ? "  (IN) " : "├──";
        recursive_print_ast(node->left, level + 1, sub_pref);
    }
    if (node->right) 
    {
        recursive_print_ast(node->right, level + 1, "└──");
    }
}
/* ========================================================================== */
/* FONCTION PRINCIPALE                              */
/* ========================================================================== */

void print_ast(t_btree *root)
{
    printf("\n" C_BLUE "=== AST VISUALIZER ===" C_RESET "\n");
    if (!root)
        printf("Empty Tree\n");
    else
        recursive_print_ast(root, 0, "ROOT");
    printf(C_BLUE "======================" C_RESET "\n\n");
}

