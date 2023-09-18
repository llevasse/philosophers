/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:45:10 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/18 21:21:08 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "philosophers.h"

typedef struct s_philo {
	struct timeval	curr_time;
	long long		init_time;
	int				id;
	int				alive;
	int				time_to_die;
	int				time_to_eat;
	long long		time_since_eat;
	int				time_to_sleep;
	int				eaten_times;
	pthread_mutex_t	fork;
	pthread_mutex_t	save;
	struct s_philo	*left_buddy;
	struct s_philo	*right_buddy;
	struct s_table	*table;
}	t_philo;

typedef struct s_table {
	struct timeval	curr_time;
	long long		init_time;
	int				alive;
	int				nb_philo;
	int				nb_rounds;
	pthread_t		death;
	pthread_t		*threads;
	pthread_mutex_t	write;
	t_philo			**philo;
}	t_table;

#endif
