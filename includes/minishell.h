/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:01:50 by ael-qori          #+#    #+#             */
/*   Updated: 2024/02/22 14:21:08 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL
#define MINISHELL

#include "../libft/libft.h"
#include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
// ======================= MACRO ==================

#define MINISHELL_PROMPT "MiniShell $> "
#define HOME "HOME"
#define PWD "PWD"
#define OLDPWD "OLDPWD"

#define PIPE '|'
#define INPUT '<'
#define OUTPUT '>'

// ======================= COLORS ==================

#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define BOLDBLACK "\033[1m\033[30m"
#define BOLDRED "\033[1m\033[31m"
#define BOLDGREEN "\033[1m\033[32m"
#define BOLDYELLOW "\033[1m\033[33m"
#define BOLDBLUE "\033[1m\033[34m"
#define BOLDMAGENTA "\033[1m\033[35m"
#define BOLDCYAN "\033[1m\033[36m"
#define BOLDWHITE "\033[1m\033[37m"

// ==================== STRUCT ========================//

typedef struct s_env
{
    char    *key;
    char    *value;
    struct s_env *next;
}	t_env;

typedef struct s_tree
{
    char    *command;
    struct s_tree *left;
    struct s_tree *right;
} t_tree;

typedef struct s_list_pipe
{
    t_tree  *root;
    struct s_list_pipe *next;
}t_list_pipe;



// typedef struct s_shell
// {
//     char    *command;
//     char    *file;
//     char    *options;
//     int     pipe;
//     char    *redirecion;
//     char    *here_doc;
//     struct s_shell *next;
// } t_shell;


// typedef struct s_node
// {
//     t_tree *root;
//     struct s_node *next;
// }t_node;

// ================ PROTOTYPE =======================

// ***** env list *******

t_env   *ft_lst_new_env(char *key, char *value);
void    ft_lst_inert(t_env **env, t_env *node);
void    ft_lst_env_addback(t_env **env, t_env *node);
char    *ft_getkey_env(char *str);
char    *ft_getvalue_env(char *str);

// ***** ft_env *******
void    ft_print_env(t_env *env);
t_env *ft_env(char **env_list);

// ***** SIGNALST *****

void    ft_signals(void);

// ***** PROMPT *******

char    *ft_prompt(t_env *env);

// ***** PWD ********

// char	*ft_pwd(t_env *env);

// ****** CD ********

// void    ft_cd(t_env **env, char *path);

// ******** export ********
// void	ft_export(t_env **env, char *key, char *value);

// ********* unset ********


// ********** tree ********

// t_tree  *ft_new_tree(char *s);
// void	ft_tree_insert(t_tree **root, t_tree *node);
// t_tree  *create_tree(char **arr);

// ********** PARSING ********

char	*ft_add_space_to_pipe(char *s);
char	*ft_add_space_to_input(char *s);
char	*ft_add_space_to_output(char *s);
int	ft_is_redirections(char c);
char	*ft_parsing(char *input);

// // *********** TREE **********
// t_tree *create_tree(char **arr);
// void    print_tree(t_tree *root);

// // *********** LIST **********
// t_shell	*ft_new_shell(void);
// void	ft_shell_addback(t_shell **lst, t_shell *new);
// t_shell	*create_shell(char	**arr);
// void	print_shell(t_shell *shell);
// void	ft_handle_redirection_output(t_shell **shell,char	**arr,int *i);
// void	ft_handle_redirection_append(t_shell **shell,char	**arr,int *i);
// void	ft_handle_redirection_here_doc(t_shell **shell,char	**arr,int *i);



// t_node	*ft_new_node(t_tree *root);
// void	ft_node_addback(t_node **lst, t_node *new);
// t_node		*create(char	**arr);

void	ft_tree_insert(t_tree **root, t_tree *new);
t_tree	*ft_tree_new(char	*command);
void	ft_execute(t_list_pipe *lst , int *fd);
t_list_pipe	*ft_create_list(char	**arr);
void	ft_print_lstpipe(t_list_pipe	*lst);
void handle_multiple_pipe(t_list_pipe *lst);
#endif