/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:45:10 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/06 00:37:51 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "philosophers.h"

typedef struct s_philo {
	long long		current_time;
	long long		init_time;
	int				is_alive;
	int				id;
	int				time_to_die;
	int				time_to_eat;
	long long		time_since_eat;
	int				time_to_sleep;
	int				eaten_times;
	int				succes;
	pthread_mutex_t	fork;
	struct s_philo	*left_buddy;
	struct s_philo	*right_buddy;
	struct s_table	*table;
}	t_philo;

typedef struct s_table {
	long long		init_time;
	int				alive;
	int				nb_philo;
	int				nb_rounds;
	pthread_t		death;
	pthread_t		*threads;
	pthread_mutex_t	dead;
	pthread_mutex_t	write;
	t_philo			**philo;
	struct timeval	current_time;
}	t_table;

#endif
