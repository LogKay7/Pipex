/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkailany <lkailany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:20:48 by lkailany          #+#    #+#             */
/*   Updated: 2022/04/18 12:40:14 by lkailany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	parent_process(int fd, int tube[], char *cmd, char **envp)
{
	int	dupid;

	dupid = dup2(fd, STDOUT_FILENO);
	if (dupid == -1)
		errormsg("Error : dup2 function failed for fd2\n");
	dupid = dup2(tube[0], STDIN_FILENO);
	if (dupid == -1)
		errormsg("Error : dup2 function failed for fd2\n");
	close(tube[1]);
	close(fd);
	checkcmd(cmd, envp);
	errormsg("Error : second command not found\n");
}

void	child_process(int fd, int tube[], char *cmd, char **envp)
{
	int	dupid;

	dupid = dup2(fd, STDIN_FILENO);
	if (dupid == -1)
		errormsg("Error : dup2 function failed for fd1\n");
	dupid = dup2(tube[1], STDOUT_FILENO);
	if (dupid == -1)
		errormsg("Error : dup2 function failed for tube[1]\n");
	close(tube[0]);
	close(fd);
	checkcmd(cmd, envp);
	errormsg("Error : first command not found\n");
}

void	pipex(int fd1, int fd2, char **argv, char **envp)
{
	int		tube[2];
	int		pipeid;
	pid_t	parentid;

	pipeid = pipe(tube);
	if (pipeid == -1)
		errormsg("Error : pipe failed\n");
	parentid = fork();
	if (parentid == -1)
		errormsg("Error : fork failed");
	if (parentid == 0)
		child_process(fd1, tube, argv[2], envp);
	else
	{		
		parent_process(fd2, tube, argv[3], envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	infilefd;
	int	outfilefd;

	if (argc != 5)
		errormsg("Error : Invalid number of argument.\n");
	infilefd = open(argv[1], O_RDONLY);
	outfilefd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (infilefd == -1 || outfilefd == -1)
		errormsg("Error : File opening failed\n");
	pipex(infilefd, outfilefd, argv, envp);
	return (0);
}
