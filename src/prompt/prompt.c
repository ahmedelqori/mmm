#include "../../includes/minishell.h"

char    *ft_search_in_env(char *key,t_env *env)
{
    while (env)
    {
        if (ft_strlen(key) == ft_strlen(env->key) &&
            ft_strncmp(key, env->key, ft_strlen(key) )== 0)
        {
            return (ft_strdup(env->value));        
        }
        env = env->next;
    }
    return (NULL);
}

char    *current_path(t_env *env)
{
    char    *home;
    char    *current_dir;
    char    *path;

    home = ft_search_in_env(HOME, env);
    if (home == NULL)
        return (NULL);
    current_dir = ft_search_in_env(PWD, env);
    if (current_dir == NULL)
        return (NULL);
    if (ft_strncmp(home,current_dir, ft_strlen(home)) == 0)
        path = ft_strjoin("~", current_dir + ft_strlen(home));
    else
        path = ft_strdup(current_dir);
    free(home);
    free(current_dir);
    return (path);
}

char    *ft_prompt(t_env *env)
{
    char    *current_dir;
    char    *prompt;

    current_dir = current_path(env);
    prompt = ft_strjoin(BOLDYELLOW MINISHELL_PROMPT RESET, current_dir); 
    free(current_dir);
    current_dir = prompt;
    prompt = ft_strjoin(current_dir, " ");
    free(current_dir);
    return (prompt);
}