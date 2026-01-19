#include <stdio.h>
#include "../../Includes/ast.h"

/* ========================= */
/* ===== TOKENS UTILS ===== */
/* ========================= */

static t_token	*token_new(t_token_type type, char *value)
{
	t_token	*tok;

	tok = ft_calloc(1, sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	if (value)
		tok->value = ft_strdup(value);
	return (tok);
}

static void	token_add_back(t_token **lst, t_token *new)
{
	t_token	*cur;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	cur = *lst;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

static void	token_clear(t_token **lst)
{
	t_token	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->value);
		free(*lst);
		*lst = tmp;
	}
}

/* =============================== */
/* ===== BUILD TEST TOKENS ======= */
/* =============================== */
/*
** echo $USER | cat > $HOME/file
*/
static t_token	*build_test_tokens(void)
{
	t_token	*lst;

	lst = NULL;
	token_add_back(&lst, token_new(WORD, "echo"));
	token_add_back(&lst, token_new(WORD, "\'$USER et Patxi\'"));
	token_add_back(&lst, token_new(PIPE, "|"));
	token_add_back(&lst, token_new(WORD, "cat"));
	token_add_back(&lst, token_new(REDIR_OUT, ">"));
	token_add_back(&lst, token_new(WORD, "\'$HOME\'/coucou.txt"));
	token_add_back(&lst, token_new(EOF_TOK, NULL));
	return (lst);
}

/* ========================= */
/* ===== AST PRINTING ===== */
/* ========================= */

static void	print_redirs(t_redir *r)
{
	while (r)
	{
		printf("      redir -> type=%d target=\"%s\"\n",
			r->type, r->target);
		r = r->next;
	}
}

static void	print_command_node(t_ast_node *cmd)
{
	int	i;

	printf("    COMMAND\n");
	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		printf("      argv[%d] = \"%s\"\n", i, cmd->argv[i]);
		i++;
	}
	print_redirs(cmd->redirs);
}

static void	print_ast(t_btree *root, int depth)
{
	int	i;

	if (!root)
		return ;
	for (i = 0; i < depth; i++)
		printf("  ");
	if (((t_ast_node *)root->content)->type == AST_PIPE)
		printf("PIPE\n");
	else
		print_command_node(root->content);
	print_ast(root->left, depth + 1);
	print_ast(root->right, depth + 1);
}

/* =============================== */
/* ===== BUILD TEST ENV ========= */
/* =============================== */

static t_dict	*build_test_env(char **envp)
{
	t_dict	*d_env;

	d_env = init_d_env(envp);
	if (!d_env)
	{
		printf("ERROR: init_d_env failed\n");
		return (NULL);
	}
	return (d_env);
}

/* ========================= */
/* ========= MAIN ========= */
/* ========================= */

int	main(int ac, char **av, char **envp)
{
	t_token	*tokens;
	t_btree	*ast;
	t_dict	*d_env;

	(void)ac;
	(void)av;

	printf("=== BUILD TOKENS ===\n");
	tokens = build_test_tokens();
	if (!tokens)
		return (1);

	printf("=== CREATE AST ===\n");
	ast = create_ast(tokens);
	if (!ast)
	{
		token_clear(&tokens);
		return (1);
	}

	printf("\n=== AST BEFORE EXPAND ===\n");
	print_ast(ast, 0);

	printf("\n=== INIT ENV ===\n");
	d_env = build_test_env(envp);
	if (!d_env)
	{
		btree_clear(&ast, ast_node_free);
		token_clear(&tokens);
		return (1);
	}

	printf("\n=== EXPAND AST ===\n");
	if (expand_infix(ast, d_env) < 0)
		printf("ERROR during expand\n");

	printf("\n=== AST AFTER EXPAND ===\n");
	print_ast(ast, 0);

	printf("\n=== CLEANUP ===\n");
	dict_destroy(d_env, free);
	btree_clear(&ast, ast_node_free);
	token_clear(&tokens);

	return (0);
}
