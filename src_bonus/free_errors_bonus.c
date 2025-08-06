/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:11:29 by jmalaval          #+#    #+#             */
/*   Updated: 2025/08/06 15:43:40 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	exit_with_message(char *str, int n)
{
	ft_putendl_fd("Error\n", 2);
	ft_putendl_fd(str, 2);
	exit(n);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	exit_with_message_and_free(char *str, t_pipex_b *pipex, int n)
{
	if (str)
		ft_putendl_fd(str, 2);
	free_struct(pipex);
	exit(n);
}

void	free_struct(t_pipex_b *pipex)
{
	if (pipex)
	{
		if (pipex->directories)
			free_tab(pipex->directories);
		if (pipex->path)
			free(pipex->path);
		if (pipex->pathname_cmd)
			free(pipex->pathname_cmd);
		if (pipex->cmd)
			free_tab(pipex->cmd);
		if (pipex->pid)
			free(pipex->pid);
		if (pipex->pipefd)
			free_pipe(pipex);
		free(pipex);
	}
}

void	free_pipe(t_pipex_b *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count)
	{
		free(pipex->pipefd[i]);
		i++;
	}
	free(pipex->pipefd);
}
