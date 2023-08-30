/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 09:54:38 by llevasse          #+#    #+#             */
/*   Updated: 2023/08/30 22:02:10 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# include "mess.h"

typedef struct s_philo {
	int	id;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eaten;
}	t_philo;


int					is_args_valid(int argc, char **argv);
int					is_only_digit(char	*s);

int					ft_isspace(char c);
unsigned long long	ft_atoi_ullong(const char *str);

#endif
