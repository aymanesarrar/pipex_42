/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysarrar <aysarrar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 09:58:26 by aysarrar          #+#    #+#             */
/*   Updated: 2021/12/09 13:32:53 by aysarrar         ###   ########.fr       */
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
int		get_path_and_execute(char **cmd, char *envp[])
{
	char	*new_path;
	int		index;
	char	**exec_path;
	char	*path;
	char	*full_cmd;

	index = 0;
	path = ft_substr(get_path(envp), 5, ft_strlen(get_path(envp)) - 5);
	exec_path = ft_split(path, ':');
	while (exec_path[index] != NULL)
	{
		new_path = ft_strjoin(exec_path[index], "/");
		full_cmd = ft_strjoin(new_path, cmd[0]);
		if (access(full_cmd, X_OK) == 0)
		{
			execve(full_cmd, cmd, envp);
			exit(EXIT_SUCCESS);
		}
		free(new_path);
		free(full_cmd);
		index++;
	}
	return (0);
}
void	child_process(pipex_t *pipe_list, char *envp[], char *cmd1)
{
	char	**parse_cmd1;
	int		exec_r;
	
	pipe_list->dup2_r = dup2(pipe_list->infile, 0);
	parse_cmd1 = ft_split(cmd1, ' ');
	if (pipe_list->dup2_r < 0)
		handle_errors("dup2");
	pipe_list->dup2_r = dup2(pipe_list->fd[1], 1);
	if (pipe_list->dup2_r < 0)
		handle_errors("dup2");
	close(pipe_list->outfile);
	close(pipe_list->fd[0]);
	exec_r = get_path_and_execute(parse_cmd1, envp);
	if (exec_r == 0)
		handle_errors("unknown command\n");
	exit(EXIT_SUCCESS);
}
void	parent_process(pipex_t *pipe_list, char *envp[], char *cmd2)
{
	char	**parse_cmd2;
	int		exec_r;
	
	wait(NULL);
	parse_cmd2 = ft_split(cmd2, ' ');
	pipe_list->dup2_r = dup2(pipe_list->outfile, 1);
	if (pipe_list->dup2_r < 0)
		handle_errors("dup2");
	pipe_list->dup2_r = dup2(pipe_list->fd[0], 0);
	if (pipe_list->dup2_r < 0)
		handle_errors("dup2");
	close(pipe_list->infile);
	close(pipe_list->fd[1]);
	exec_r = get_path_and_execute(parse_cmd2, envp);
	if (exec_r == 0)
		handle_errors("unknown command");
	exit(EXIT_SUCCESS);
}
int main(int argc, char **argv, char *envp[])
{
	pipex_t *pipe_list;
	
	if (argc != 5)
		handle_errors("invalid arguments");
	pipe_list = malloc(sizeof(pipex_t *));
	if (!pipe_list)
		exit(EXIT_FAILURE);
	pipe_list->infile = open(argv[1], O_RDONLY);
	pipe_list->outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0677);
	if (pipe_list->infile < 0 || pipe_list->outfile < 0)
		handle_errors("fd");
	pipe_list->pipe_r = pipe(pipe_list->fd);
	if (pipe_list->pipe_r < 0)
		handle_errors("pipe");
	pipe_list->childpid = fork();
	if (pipe_list->childpid < 0)
		handle_errors("fork");
	if (pipe_list->childpid == 0)
		child_process(pipe_list, envp, argv[2]);
	else
		parent_process(pipe_list, envp, argv[3]);
}