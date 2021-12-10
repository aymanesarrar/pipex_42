/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysarrar <aysarrar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 09:58:26 by aysarrar          #+#    #+#             */
/*   Updated: 2021/12/10 12:24:00 by aysarrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*get_path(char *envp[])
{
	char	*path;
	int		index;

	if (!envp || !*envp)
		return (NULL);
	index = 0;
	while (envp[index])
	{
		if (ft_strnstr(envp[index], "PATH", ft_strlen(envp[index])) != NULL)
			path = ft_strdup(envp[index]);
		index++;
	}
	return (path);
}

void	handle_errors(char *str)
{
	if (errno != 0)
		perror(str);
	else
		ft_putstr_fd(str, 1);
	exit(EXIT_FAILURE);
}
void	launch_processes(t_pipex *pipe_list, char **argv, char *envp[])
{
		pipe_list->pipe_r = pipe(pipe_list->fd);
		if (pipe_list->pipe_r < 0)
			handle_errors("pipe");
		pipe_list->childpid = fork();
		if (pipe_list->childpid == 0)
			child_process(pipe_list, envp, argv[2]);
		else
			second_child_process(pipe_list, envp, argv[3]);
}
int	main(int argc, char **argv, char *envp[])
{
	t_pipex	*pipe_list;
	int		status;
	
	if (argc != 5)
		handle_errors("invalid arguments");
	pipe_list = malloc(sizeof(t_pipex *));
	if (!pipe_list)
		handle_errors("malloc failed\n");
	pipe_list->infile = open(argv[1], O_RDONLY);
	pipe_list->outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (pipe_list->infile < 0 || pipe_list->outfile < 0)
		handle_errors("fd");
	pipe_list->childpid = fork();
	if (pipe_list->childpid < 0)
		handle_errors("fork");
	if (pipe_list->childpid == 0)
		launch_processes(pipe_list, argv, envp);
	else
		wait(&status);
	free(pipe_list);
	//return (0);
}
