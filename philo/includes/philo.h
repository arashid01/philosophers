/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:22:01 by amal              #+#    #+#             */
/*   Updated: 2025/06/30 01:30:57 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>

typedef struct s_args {
	int	num_of_philo;
	int	num_of_forks;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_meals;
}	t_args;

// ****************** utils ******************
int		ft_isnum(char c);
int		ft_atoi(char *nbr);
int		ft_strlen(char *str);
int		correct_args(int argc, char **argv);
void	ft_putendl_fd(char *str, int fd);

#endif