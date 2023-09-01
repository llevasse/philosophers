/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 09:54:38 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/01 12:40:57 by llevasse         ###   ########.fr       */
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

# include "mess.h"

typedef struct s_philo {
	struct timeval	current_time;
	int				is_alive;
	int				id;
	int				time_to_die;
	int				time_to_eat;
	struct timeval	time_since_eating;
	int				time_to_sleep;
	struct timeval	time_since_sleeping;
	int				eaten_times;
	int				succes;
	pthread_mutex_t	fork;
	struct s_philo	*left_buddy;
	struct s_philo	*right_buddy;
	struct s_table	*table;
}	t_philo;

typedef struct s_table {
	struct timeval	init_time;
	int				nb_philo;
	int				nb_rounds;	//one round is ended when each philo eated at least once.
	pthread_t	*threads;
	t_philo		**philo;
}	t_table;

int					is_args_valid(int argc, char **argv);
int					is_only_digit(char	*s);

void				create_threads(t_table *table);
void				free_table(t_table *table);
t_table				*init_table(char **argv);
void				set_table_null(t_table *table);
t_philo				 **init_philo(int max_id);
void				set_philo(char **argv, t_table *table, int buddy_id);
void				print_philo(t_philo *philo);

void				*alive_routine(void	*args);

int					ft_isspace(char c);
int					ft_atoi(const char *str);

size_t				ft_strlen(const char *s);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

#endif
