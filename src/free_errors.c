/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:11:29 by jmalaval          #+#    #+#             */
/*   Updated: 2025/07/10 18:24:51 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	exit_with_message(char *str)
{
	ft_putendl_fd("Error\n", 2);
	ft_putendl_fd(str, 2);
	exit(1);
}

void	free_tab(char **tab)
{
	int i; 
	
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
void	exit_with_message_and_free(char *str, t_pipex *pipex)
{
	ft_putendl_fd("Error\n", 2);
	ft_putendl_fd(str, 2);
	free_struct(pipex);
	exit(1);
}

void	free_struct(t_pipex *pipex)
{
	if (pipex)
	{
		if (pipex->directories)
			free_tab(pipex->directories);
		if (pipex->path)
			free(pipex->path);
		if (pipex->pathname_cmd1)
			free(pipex->pathname_cmd1);
		if (pipex->pathname_cmd2)
			free(pipex->pathname_cmd2);
		if (pipex->cmd1)
			free_tab(pipex->cmd1);
		if (pipex->cmd2)
			free_tab(pipex->cmd2);
	}
}
