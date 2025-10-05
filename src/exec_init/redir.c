/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menny <menny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:26:25 by gvigano           #+#    #+#             */
/*   Updated: 2025/02/24 15:44:31 by menny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	child_process_hd(t_token *data, t_token *head)
{
	char	*line;
	char	*limiter;
	int		fd;

	fd = get_tmpfd(data);
	if (!fd)
		return (0);
	limiter = ft_strjoin(data->rd->name, "\n");
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strcmp(line, limiter))
			write(fd, line, ft_strlen(line));
		else
			break ;
		free (line);
		line = get_next_line(STDIN_FILENO);
	}
	if (line)
		free (line);
	close (fd);
	free (limiter);
	get_next_line(-42);
	free_token (head);
	return (1);
}
/*				PIU' RECENTE			*/
// int	here_doc(t_token *data, int **tmp_fd, int **tmp_pids, t_token *head)
// {
// 	int		pid_r;
// 	int		fd[2];

// 	if (pipe(fd) < 0)
// 	{
// 		perror("Pipe error");
// 		return (0);
// 	}
// 	pid_r = fork();
// 	g_kill_pid = pid_r;
// 	check_pid(data, pid_r);
// 	if (pid_r == 0)
// 	{
// 		free(*(tmp_fd));
// 		free(*(tmp_pids));
// 		free_environment(data->env, 1);
// 		if (!child_process_hd(data, head))
// 			exit(EXIT_FAILURE);
// 		exit(EXIT_SUCCESS);
// 	}
// 	else
// 		parent_process_hd(data, pid_r);
// 	return (1);
// }

int	here_doc(t_token *data, t_token *head)
{
	int		pid_r;
	int		fd[2];

	if (pipe(fd) < 0)
	{
		perror("Pipe error");
		return (0);
	}
	pid_r = fork();
	g_kill_pid = pid_r;
	check_pid(data, pid_r);
	if (pid_r == 0)
	{
		free(*(head->fvar->fd));
		free_process_memory(NULL, head->env, head->fvar);
		if (!child_process_hd(data, head))
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else
		parent_process_hd(data, pid_r);
	return (1);
}

// int	here_doc(t_token *data, int ***free_var)
// {
// 	int		pid_r;
// 	int		fd[2];
// 	int		i;

// 	if (pipe(fd) < 0)
// 	{
// 		perror("Pipe error");
// 		return (0);
// 	}
// 	pid_r = fork();
// 	g_kill_pid = pid_r;
// 	check_pid(data, pid_r);
// 	if (pid_r == 0)
// 	{
// 		i = 0;
// 		while (*(free_var[i]))
// 			free(*(free_var[i]));
// 		free(*(free_var));
// 		free_environment(data->env, 1);
// 		if (!child_process_hd(data))
// 			return (0);
// 		exit(EXIT_SUCCESS);
// 	}
// 	else
// 		parent_process_hd(data, pid_r);
// 	return (1);
// }

static int	handle_input_redir(t_redir *rd, int *fd, int i)
{
	if (rd && rd->type == T_RED_IN)
	{
		close (fd[0]);
		fd[0] = open(rd->name, O_RDONLY);
		if (fd[0] < 0)
			return (-1);
	}
	else if (rd && rd->type == T_DELIM && fd[2] == i)
	{
		fd[0] = open("heredoc_tmp.txt", O_RDONLY);
		if (fd[0] < 0)
		{
			perror("Error heredoc_tmp");
			return (-1);
		}
	}
	else if (rd && rd->type == T_DELIM)
		return (-1);
	return (fd[0]);
}

static int	handle_output_redir(t_redir *rd, int tmpout)
{
	if (rd && rd->type == T_RED_OUT)
	{
		close (tmpout);
		tmpout = open(rd->name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (tmpout < 0)
		{
			perror("Error opening output file");
			return (-1);
		}
	}
	else if (rd && rd->type == T_RED_APPEN)
	{
		close (tmpout);
		tmpout = open(rd->name, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (tmpout < 0)
		{
			perror("Error opening output file");
			return (-1);
		}
	}
	return (tmpout);
}

// static int	handle_input_redir(t_token *data, t_redir *rd, int *fd, int i)
// {
// 	if (rd && rd->type == T_RED_IN)
// 	{
// 		fd[0] = open(rd->name, O_RDONLY);
// 		if (fd[0] < 0)
// 		{
// 			free_token(data);
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	else if (rd && rd->type == T_DELIM && fd[2] == i)
// 	{
// 		fd[0] = open("heredoc_tmp.txt", O_RDONLY);
// 		if (fd[0] < 0)
// 		{
// 			free_token(data);
// 			perror("Error heredoc_tmp");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	else if (rd && rd->type == T_DELIM)
// 	{
// 		free_token(data);
// 		exit(EXIT_FAILURE);
// 	}
// 	return (fd[0]);
// }

// static int	handle_output_redir(t_token *data, t_redir *rd, int tmpout)
// {
// 	if (rd && rd->type == T_RED_OUT)
// 	{
// 		tmpout = open(rd->name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 		if (tmpout < 0)
// 		{
// 			free_token(data);
// 			perror("Error opening output file");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	else if (rd && rd->type == T_RED_APPEN)
// 	{
// 		tmpout = open(rd->name, O_WRONLY | O_CREAT | O_APPEND, 0777);
// 		if (tmpout < 0)
// 		{
// 			free_token(data);
// 			perror("Error opening output file");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	return (tmpout);
// }

int	*handle_redir(t_token *data, int *fd, int j, t_token *head)
{
	t_redir	*current;
	size_t	i;

	i = 0;
	current = data->rd;
	while (i < data->nredir)
	{
		fd[0] = handle_input_redir(current, fd, j);
		fd[1] = handle_output_redir(current, fd[1]);
		if (fd[0] == -1 || fd[1] == -1)
		{
			free(*(head->fvar->fd));
			free_process_memory(head, head->env, head->fvar);
			exit(EXIT_FAILURE);
		}
		if (data->env->exit_stat == SIGKILL)
		{
			free(*(head->fvar->fd));
			free_process_memory(head, head->env, head->fvar);
			exit(data->env->exit_stat);
		}
		current = current->next;
		i++;
	}
	return (fd);
}
