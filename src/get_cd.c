#include "../include/minishell.h"

void go_home(t_info *info)
{
    char *path;
    path = get_env_value("HOME", info->envp, 4);
    if (chdir(path))
        printf("%s%s\n", info->tokens[0],
         ": HOME not set");
    update_pwd(info);
}

void go_back(t_info *info)
{
    chdir("..");
    update_pwd(info);
}

void go_last(t_info *info)
{
    char *path;
    path = get_env_value("OLDPWD", info->envp, 6);
    chdir(path);
    update_pwd(info);
}

void go_path(t_info *info)
{
    if(chdir(info->tokens[1]))
        printf("%s%s%s\n", info->tokens[0],
         ": no such file or directory: ", info->tokens[1]);
    update_pwd(info);
}

void update_pwd(t_info *info)
{
    char *pwd;
    char *oldpwd;

    oldpwd = get_env_value("PWD", info->envp, 3);
    pwd = getcwd(NULL, 0);
    info->envp = set_env("OLDPWD", oldpwd, info->envp, 6);
    info->envp = set_env("PWD", pwd, info->envp, 3);
}

void get_cd(t_info *info)
{
  if (!ft_strcmp(info->tokens[0], "cd") && info->counter == 1)
    go_home(info);
  else if(!ft_strcmp(info->tokens[1], "..") && info->counter == 2)
    go_back(info);
  else if(!ft_strcmp(info->tokens[1], "-") && info->counter == 2)
    go_last(info);
  else
    go_path(info);
}