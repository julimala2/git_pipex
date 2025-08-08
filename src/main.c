/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:06:34 by jmalaval          #+#    #+#             */
/*   Updated: 2025/08/08 16:22:49 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	*pipex;
	int		ret;

	ret = 0;
	if (argc != 5)
		exit_with_message("Incorrect number of arguments", 1);
	if (access(argv[1], F_OK) < 0)
		perror(argv[1]);
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		exit_with_message("Pipex malloc", 1);
	init_struct(pipex);
	init_pipex(pipex, argv, env);
	if (pipe(pipex->pipefd) == -1)
		exit_with_message_and_free("Pipe", pipex, 1);
	if (pipex->infile == -2)
	{
		init_outfile(pipex, argv);
		free_struct(pipex);
		return (0);
	}
	ret = ft_pipex(pipex, argv, env);
	free_struct(pipex);
	return (ret);
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
