/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 17:30:35 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/02/10 20:36:42 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

char	*execv_fan(char **env, char *av);
void	child(int fd[2], char **av, char *env[]);
void	parent(int fd[2], char **av, char *env[]);
void	creat_pipe(int fd[2], int pid, char **av, char *env[]);

#endif