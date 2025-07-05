/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrashid <amrashid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:08:09 by amrashid          #+#    #+#             */
/*   Updated: 2025/07/05 14:22:06 by amrashid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	init_timer(void)
{
	struct timeval	start;
	long			sec;
	long			usec;
	long			time;
	
	gettimeofday(&start, NULL);
	sec = start.tv_sec;
	usec = start.tv_usec;
	time = (sec * 1000) + (usec / 1000);
	return (time);
}

long    current_time(long start_time)
{
    struct timeval	current;
    long			sec;
    long			usec;
    long			time;

    gettimeofday(&current, NULL);
    sec = current.tv_sec;
    usec = current.tv_usec;
    time = (sec * 1000) + (usec / 1000);
    time -= start_time;
    return (time);
}