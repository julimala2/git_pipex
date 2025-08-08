/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:06:05 by jmalaval          #+#    #+#             */
/*   Updated: 2025/08/08 16:22:38 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	init_struct(t_pipex *pipex)
{
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->cmd1 = NULL;
	pipex->cmd2 = NULL;
	pipex->path = NULL;
	pipex->directories = NULL;
	pipex->outfile_error = 1;
	pipex->pathname_cmd1 = NULL;
	pipex->pathname_cmd2 = NULL;
}

void	init_pipex(t_pipex *pipex, char **av, char **env)
{
	init_infile(pipex, av);
	pipex->cmd1 = ft_split(av[2], ' ');
	if (!pipex->cmd1)
		exit_with_message_and_free("Split cmd1", pipex, 1);
	pipex->cmd2 = ft_split(av[3], ' ');
	if (!pipex->cmd2)
		exit_with_message_and_free("Split cmd2", pipex, 1);
	pipex->path = get_env_value("PATH=", env);
	if (pipex->path == NULL)
		exit_with_message_and_free("Unable to get PATH", pipex, 1);
	pipex->directories = ft_split(pipex->path, ':');
	if (!pipex->directories)
		exit_with_message_and_free("Split directories", pipex, 1);
	get_pathname(pipex->cmd1, pipex, 1);
	get_pathname(pipex->cmd2, pipex, 2);
}

void	init_infile(t_pipex *pipex, char **av)
{
	if (access(av[1], F_OK) == 0 && access(av[1], R_OK) < 0)
	{
		pipex->infile = -2;
		perror(av[1]);
	}
	if (access(av[1], F_OK) == 0)
	{
		pipex->infile = open(av[1], O_RDONLY);
		if (pipex->infile == -1)
			perror(av[1]);
	}
	else if (access(av[1], F_OK) < 0)
		pipex->infile = open("/dev/null", O_RDONLY);
}

void	init_outfile(t_pipex *pipex, char **av)
{
	if (access(av[4], F_OK) < 0)
	{
		pipex->outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->outfile < 0)
			perror(av[4]);
		else
			pipex->outfile_error = 0;
	}
	else
	{
		if (access(av[4], W_OK) < 0)
			perror(av[4]);
		else
		{
			pipex->outfile = open(av[4], O_WRONLY | O_TRUNC, 0644);
			if (pipex->outfile < 0)
				perror(av[4]);
			else
				pipex->outfile_error = 0;
		}
	}
}
