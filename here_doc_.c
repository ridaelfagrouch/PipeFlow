/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:35:47 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/02/21 11:36:08 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_file_access(t_data *data, char **av)
{
	if (ft_strcmp(av[1], "here_doc") != 0)
	{
		if (access(av[1], F_OK) != 0 || access(av[1], R_OK) != 0)
		{
			write(data->dap_out, "error ocurred with opening the filein!\n", 39);
			exit(1);
		}
		if (access(av[1], R_OK | F_OK) == 0)
			data->pro.file1 = open(av[1], O_RDONLY, 00500);
	}
	if (access(av[data->ac - 1], F_OK) != 0)
	{
		data->pro.file2 = open(av[data->ac - 1], O_CREAT | O_RDWR, 00774);
		if (data->pro.file2 < 0)
		{
			write(data->dap_out, "error! opening the fileout\n", 27);
			exit(1);
		}
	}
	else
		data->pro.file2 = open(av[data->ac - 1], O_RDWR | O_TRUNC, 00774);
}

//****************************************************

void	dup_file(t_data *data, char **av)
{
	if (ft_strcmp(av[1], "here_doc") != 0)
	{
		data->pro.dup_check2 = dup2(data->pro.file1, STDIN_FILENO);
		if (data->pro.dup_check2 == -1)
		{
			write(data->dap_out, "error dup2\n", 11);
			exit(1);
		}
	}
	data->pro.dup_check3 = dup2(data->pro.file2, STDOUT_FILENO);
	if (data->pro.dup_check3 == -1)
	{
		write(data->dap_out, "error dup2\n", 11);
		exit(1);
	}
}

//****************************************************

void	check_dap_creat(t_data *data, char **av, char **env)
{
	char	**str;

	check_file_access(data, av);
	dup_file(data, av);
	while (data->j < data->ac - 2)
	{
		creat_pipe(av[data->j], env, data);
		data->j++;
	}
	data->pro.path = get_path(env, av[data->ac - 2], data);
	str = ft_split(av[data->ac - 2], ' ');
	execve(data->pro.path, str, env);
}

//****************************************************

void	here_doc_(t_data *data, char **av)
{
	char	*ptr;

	while (1)
	{
		write(0, "heredoc> ", 9);
		ptr = ft_strtrim(get_next_line(0), "\n");
		if (ft_strcmp(ptr, av[2]) == 0)
		{
			free(ptr);
			break ;
		}
		write(data->fd[1], ptr, ft_strlen(ptr));
		free(ptr);
	}
}

//****************************************************

void	here_doc_pipe(t_data *data, char **av)
{
	if (pipe(data->fd) == -1)
	{
		write(data->dap_out, "error ocurred with opening the pipe\n", 36);
		exit(1);
	}
	data->pid = fork();
	if (data->pid == 0)
	{
		close(data->fd[0]);
		dup2(data->fd[1], STDOUT_FILENO);
		here_doc_(data, av);
	}
	else
	{
		wait(NULL);
		dup2(data->fd[0], STDIN_FILENO);
		close(data->fd[1]);
	}
}
