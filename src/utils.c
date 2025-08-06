/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:06:05 by jmalaval          #+#    #+#             */
/*   Updated: 2025/08/06 14:51:22 by juliette-ma      ###   ########.fr       */
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

char	*get_env_value(char *value, char **env)
{
	size_t	len_value;
	size_t	i;

	len_value = ft_strlen(value);
	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], value, len_value) == 0)
			return (ft_strdup(env[i] + len_value));
		i++;
	}
	return (NULL);
}

void	get_pathname(char **cmd, t_pipex *pipex, int j)
{
	int		i;
	char	*temp;
	char	*path;

	path = NULL;
	i = 0;
	temp = ft_strjoin("/", cmd[0]);
	while (pipex->directories[i])
	{
		path = ft_strjoin(pipex->directories[i], temp);
		if (access(path, X_OK) == 0)
		{
			if (j == 1)
				pipex->pathname_cmd1 = path;
			else if (j == 2)
				pipex->pathname_cmd2 = path;
			break ;
		}
		free(path);
		i++;
	}
	free(temp);
}

void	init_pipex(t_pipex *pipex, char **av, char **env)
{
	if (access(av[1], F_OK) == 0 && access(av[1], R_OK) < 0)
	{
			pipex->infile = -2;
			perror(av[1]);
	}
	else if (access(av[1], F_OK) == 0)
	{
		pipex->infile = open(av[1], O_RDONLY);
		if (pipex->infile == -1)
			perror(av[1]);
	}
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
			pipex->outfile = open(av[4], O_WRONLY | O_TRUNC | O_CREAT);
			if (pipex->outfile < 0)
				perror(av[4]);
			else
				pipex->outfile_error = 0;
		}
	}
}
