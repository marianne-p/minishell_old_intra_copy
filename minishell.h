/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:14:31 by mpihur            #+#    #+#             */
/*   Updated: 2024/07/25 19:05:25 by mpihur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define PATH_MAX 1024

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>
# include <signal.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./Libft/libft.h"

extern volatile short	g_signals[2];

/*enum e_minish_err
{
	GEN_ERR = 1,
	SUCS = 0,
	MALL_ERR = -1,
	NO_FILE = -2,
	NO_PERM = -3,
	INV_ARGS = -4,
	NO_MEMORY = -5,
	NO_PATH = -6,
	DUP2_ERROR = -7,
	EXECVE_ERROR = 126,
	PIPE_ERROR = -9,
	FORK_ERROR = -10,
	NO_CMD = -11,
	REDIR_ERR = -12,
	VALID_ERR = 126,
};*/

enum e_minish_err
{
	GEN_ERR = 1,
	SUCS = 0,
	MALL_ERR = 13,
	NO_FILE = 2,
	NO_PERM = 3,
	INV_ARGS = 4,
	NO_MEMORY = 5,
	NO_PATH = 6,
	DUP2_ERROR = 7,
	EXECVE_ERROR = 126,
	PIPE_ERROR = 9,
	FORK_ERROR = 10,
	NO_CMD = 11,
	REDIR_ERR = 12,
	VALID_ERR = 126,
};

typedef enum e_nodes
{
	CMD_NODE,
	REDIR_NODE,
	PIPE_NODE
}	t_node_type;

typedef struct s_cmd
{
	char	**av;
	int		ac;
	char	*full_line;
	int		outfd;
	int		infd;
}	t_cmd;

typedef struct s_redir
{
	struct s_node	*child;
	char			*filename;
	char			*delim;
	int				mode;
}	t_redir;

typedef struct s_pipe
{
	struct s_node	*left;
	struct s_node	*right;
}	t_pipe;

typedef struct s_ev
{
	char		*key;
	char		*value;
	struct s_ev	*next;	
}	t_envv;

typedef struct s_node
{
	t_node_type		type;
	t_cmd			*cmd;
	t_redir			*redir;
	t_redir			*inred;
	t_redir			*outred;
	t_pipe			*pipe;
	struct s_node	*next;
}	t_node;

typedef struct s_minish
{
	int				status;
	char			**tokens;
	struct s_node	*node;
	struct s_ev		*env;
	char			**envv;
}	t_minish;

char	**ft_split_minish(char *str, int i, t_minish **msh_ptr);
void	busy_wait(void);
void	setup_signal_handlers(void);
int		token_exec(char **input, char **tokens, t_minish **msh, t_node *node);
void	remove_useless_quotes(char **input_ptr, char *input, int i);
t_envv	*split_envv(t_minish **msh_ptr, t_envv **env, char **envv, int i);
char	*expand(int i, char *cpy, t_minish *msh);
char	**ret_and_free(char *str, char **tokens);
int		verify_quotes(char *str, int i, int db_q, int sing_q);
void	copy_regtoken(char **tokens, char **str, t_envv *env, t_minish *msh);
void	copy_quote(char **tokens, char **str);
void	copy_quote_expand(char **tokens, char **str, t_minish **msh_ptr);
int		len(char *str, int count);
int		isvalidquote(char **str);
int		is_white_space(char c);
int		ft_is_all_num(char *str);
char	*ft_strncpy(char *dest, const char *src, size_t n);
void	sigint_handler(int sig);
char	*ft_strjoinc(char const *s1, char const *s2);
int		check_redir_cmd(t_node *node, bool cmd, bool redir);
int		check_validity(t_node *node, t_minish *msh);

/*FREE and ERRORS*/
int		ft_no_exit(t_minish **msh_ptr, int i, void *temp, char *str);
int		ft_cust_err_no_exit(t_minish **msh_ptr, void *temp, char *str);
void	ft_no_err_no_exit(t_minish **msh_ptr, int i, void *temp);
void	free_tokens(t_minish **msh_ptr, int i);
void	free_t_node(t_node **node_ptr, t_node *temp);
t_envv	*free_new(t_envv **new, char **str);
void	free_cmd_node(t_node **node_ptr, int i);

/*PARSER*/
t_node	*parser(char **tokens, t_minish **msh_ptr,
			t_node *root, t_node *current);
t_node	*link_nodes(t_node *current, t_node *new_node);
void	syntax_tree(t_node **node_ptr, t_node *start, t_minish **msh_ptr);
void	remove_arg_quotes(char ***av_ptr, int ac, char **av, int i);
char	*copy_inside_quote(char *res, char *str);
void	ft_addenvv(t_envv **env_ptr, char *sngl, t_envv *new);

/*EXECUTE*/
void	execute(t_minish **msh_ptr, t_node **node, t_node *unode);
int		handle_cmd_pipe(t_node *node, t_minish **msh_ptr);
void	child_process(t_node *node, int fd[2], t_minish *msh);
int		handle_cmd_redir(t_minish **msh_ptr, t_redir *inrd,
			t_redir *outrd, t_node **node);
int		single_cmd(t_node *node, t_minish **msh_ptr);
int		is_exp_env_uns(char *cmd);
int		single_cmd_in_parent(t_minish **msh_ptr, t_node *node);

/*REDIR_Data*/
void	set_redir(char ***tokens, t_node **current, t_node **root);
int		is_redirection(char *tokens);
t_node	*wrap_redir_in_node(t_redir *redir);
t_redir	*create_redir_node(char ***tokens);
void	remove_redir(t_node **node_ptr, t_node *red_node);
void	open_redir(t_node **start_ptr, t_node *node,
			t_node *cmd_node, t_minish **msh_ptr);
int		handle_input_heredoc(t_minish *msh, t_node *node, char *str);
char	*get_str(char *delim, char *buff, char *ret);

/*PIPE_Data*/
void	set_pipe(t_node **current, t_node **root);
int		is_pipe(char *tokens);
t_pipe	*create_pipe_node(void);
t_node	*wrap_pipe_in_node(t_pipe *pipe);
t_node	**clean_pipes(t_node **node, t_minish **msh_ptr, int pipe_count);

/*CMD_Data*/
char	**split_path(t_minish *msh);
char	*find_envv_value(t_envv *env, char *key);
void	set_cmd(char ***tokens, t_node **current,
			t_node **root, char **full_line);
t_cmd	*create_cmd_node(char ***tokens);
int		check_command(char **path, char *token, char **full_line);
int		is_valid_cmd(char *tokens, char **full_line, t_minish *msh);
int		is_builtin(char *token);
t_node	*wrap_cmd_in_node(t_cmd *cmd, char **full_line);

/*Built-ins*/
void	exec_builtin(t_node *node, t_minish **msh_ptr);
int		exec_exit(t_node *node, t_minish **msh_ptr);
void	ft_pwd(void);
int		ft_cd(char *path);
int		ft_echo(char **cmd);
void	ft_exit(char *str, t_minish **msh_ptr, int ret, void *temp);
int		ft_export(char **av, t_envv **head);
void	print_all_envv(t_envv *head);
void	free_envv(t_envv **node);
void	ft_addenvv(t_envv **env_ptr, char *sngl, t_envv *new);
int		ft_unset(char *key, t_envv **head);
void	ft_env(t_minish *minish);

#endif
