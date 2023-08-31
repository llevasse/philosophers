/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 09:54:38 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/31 22:32:36 by llevasse         ###   ########.fr       */
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
	int	id;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eaten_times;
	struct s_philo *left_buddy;
	struct s_philo *right_buddy;
}	t_philo;

typedef struct s_table {
	pthread_t	*threads;
	t_philo		**philo;
}	t_table;

int					is_args_valid(int argc, char **argv);
int					is_only_digit(char	*s);

void				free_table(t_table *table);
t_table				*init_table(char **argv);
void				set_table_null(t_table *table);
t_philo				 **init_philo(int max_id);
void				set_philo(char **argv, t_table *table, int buddy_id);
void				print_philo(t_table *table, int id);

int					ft_isspace(char c);
int					ft_atoi(const char *str);

#endif
