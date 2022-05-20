/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkailany <lkailany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 18:08:47 by lkailany          #+#    #+#             */
/*   Updated: 2022/04/18 12:44:45 by lkailany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_alldata(char **possiblepaths, char **cmdargs, char *cmd)
{
	int	i;

	i = 0;
	free(cmd);
	free(possiblepaths);
	while (cmdargs[i])
	{
		free(cmdargs[i]);
		i++;
	}
	free(cmdargs);
}

static	char	*getpathfrom_env(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4) != 0)
		i++;
	return (envp[i] + 5);
}

void	checkcmd(char *argv, char **envp)
{
	char	*path_envp;
	char	**possiblepaths;
	char	**cmdargs;
	char	*cmd;
	int		i;

	i = 0;
	path_envp = getpathfrom_env(envp);
	possiblepaths = ft_split(path_envp, ':');
	cmdargs = ft_split(argv, ' ');
	cmd = ft_strjoin("/", cmdargs[0]);
	while (possiblepaths[i] != 0)
	{
		possiblepaths[i] = ft_strjoin(possiblepaths[i], cmd);
		execve(possiblepaths[i], cmdargs, envp);
		free(possiblepaths[i]);
		i++;
	}
	free_alldata(possiblepaths, cmdargs, cmd);
}
