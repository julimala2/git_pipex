/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:06:05 by jmalaval          #+#    #+#             */
/*   Updated: 2025/07/06 18:06:19 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void    cmd1_process(t_pipex *pipex, char **argv, char **env)
{
    dup2(pipex->infile, 0);
    dup2(pipex->pipefd[1], 1);
    close(pipex->pipefd[0]);
    execve(pathname, pipex->cmd1, env);
}

void    cmd2_process(t_pipex *pipex, char **argv, char **env)
{
    dup2(pipex->pipefd[0], 0);
    dup2(pipex->outfile, 1);
    close(pipex->pipefd[1]);
    execve(pathname, pipex->cmd2, env);
}

void    init_pipex(t_pipex *pipex, char **av)
{ 
    pipex->infile = open(av[1], O_RDONLY);
    if (pipex->infile == -1)
        perror("Opening infile");
    pipex->outfile = open(av[4], O_WRONLY | O_CREAT);
    if (pipex->outfile == -1)
        perror("Opening or creating outfile");
    pipex->cmd1 = av[2];
    pipex->cmd2 = av[3];
    // prevoir des exit et erreurs en cas de chaine nulle
}

char    *get_pathname(char **directories, char *cmd)
{
    // j'ai mes directories avec /usr/bin/ls
}