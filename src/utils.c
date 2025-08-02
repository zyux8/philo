/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:28:20 by ohaker            #+#    #+#             */
/*   Updated: 2025/07/30 19:03:54 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void error_msg(char *err_str)
{
	printf("Error: %s", err_str);
	exit (1);
}

int ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	x;
	int	res;

	x = 0;
	res = 0;
	while (ft_isdigit(str[x]))
	{
		res = (res * 10) + (str[x] - '0');
		x++;
	}
	return (res);
}

long get_time_diff(struct timeval start)
{
	struct timeval	now;
	long			time_diff;

	gettimeofday(&now, NULL);
	time_diff = (now.tv_sec - start.tv_sec) * 1000;
	time_diff += (now.tv_usec - start.tv_usec) / 1000;
	return (time_diff);
}

void	ft_usleep(long sleep, t_philo *philo)
{
	long	start;
	long	current;

	start = get_time_diff(philo->rules->start_time);
	while (1)
	{
		pthread_mutex_lock(&philo->rules->simulation_lock);
		if (philo->rules->stop_simulation)
		{
			pthread_mutex_unlock(&philo->rules->simulation_lock);
			break;
		}
		pthread_mutex_unlock(&philo->rules->simulation_lock);

		current = get_time_diff(philo->rules->start_time);
		if (current - start >= sleep)
			break;
		usleep(sleep / 100);
	}
}

void printf_safe(t_philo *philo, char *msg)
{
	long	time_diff;
	
	time_diff = get_time_diff(philo->rules->start_time);
	pthread_mutex_lock(&philo->rules->print_lock);
	if (check_alive(philo->rules))
		printf("%ld %d %s\n", time_diff, philo->id, msg);
	pthread_mutex_unlock(&philo->rules->print_lock);
}

void set_stop_sim(t_rules *rules)
{
	pthread_mutex_lock(&rules->simulation_lock);
	rules->stop_simulation = 1;
	pthread_mutex_unlock(&rules->simulation_lock);
}
