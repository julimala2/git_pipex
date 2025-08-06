/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:06:34 by jmalaval          #+#    #+#             */
/*   Updated: 2025/08/06 14:18:46 by juliette-ma      ###   ########.fr       */
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
	if (pipex->infile == -2 || access(argv[1], F_OK) < 0)
	{
		init_outfile(pipex, argv);
		free_struct(pipex);
		return (0);
	}
	ret = ft_pipex(pipex, argv, env);
	free_struct(pipex);
	return (ret);
}
