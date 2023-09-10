/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 09:54:38 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/10 12:45:33 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <pthread.h>

# include "struct.h"
# include "mess.h"

int					is_args_valid(int argc, char **argv);
int					is_only_digit(char	*s);

void				create_threads(t_table *table);
void				free_table(t_table *table);
t_table				*init_table(char **argv);
void				set_table_null(t_table *table);
t_philo				**init_philo(int max_id);
void				set_philo(char **argv, t_table *table, int buddy_id);
void				print_philo(t_philo *philo);

long long			timestamp(struct timeval tv);
void				wait_time(t_philo *buddy, long wait_time, long long time);

void				*death_routine(void	*args);
void				*alive_routine(void	*args);
int					check_death(t_philo *buddy, long long time);
int					choose_fork(t_philo *buddy, long long time);

int					ft_isspace(char c);
int					ft_atoi(const char *str);

size_t				ft_strlen(const char *s);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

#endif
