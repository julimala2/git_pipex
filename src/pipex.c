/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:06:05 by jmalaval          #+#    #+#             */
/*   Updated: 2025/07/11 18:53:54 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void    ft_pipex(t_pipex *pipex, char **env)
{
    pid_t	pid1;
	pid_t	pid2;
    
    pid1 = fork();
	if (pid1 < 0)
	{
		free_struct(pipex);
		perror("pid1");
	}
	if (pid1 == 0)
		cmd1_process(pipex, env);
    pid2 = fork();
	if (pid2 < 0)
	{
		free_struct(pipex);
		perror("pid2");
	}
	if (pid2 == 0)
		cmd2_process(pipex, env);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    close(pipex->pipefd[0]);
    close(pipex->pipefd[1]);
}

void    cmd1_process(t_pipex *pipex, char **env)
{
    dup2(pipex->infile, 0);
    dup2(pipex->pipefd[1], 1);
    close(pipex->pipefd[0]);
    execve(pipex->pathname_cmd1, pipex->cmd1, env);
}

void    cmd2_process(t_pipex *pipex, char **env)
{
    dup2(pipex->pipefd[0], 0);
    dup2(pipex->outfile, 1);
    close(pipex->pipefd[1]);
    execve(pipex->pathname_cmd2, pipex->cmd2, env);
}
