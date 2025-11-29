/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 15:46:29 by ohaker            #+#    #+#             */
/*   Updated: 2025/11/29 15:47:51 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	printf_safe(t_philo *philo, char *msg)
{
	long	time_diff;

	time_diff = get_time_diff(philo->rules->start_time);
	pthread_mutex_lock(&philo->rules->print_lock);
	if (get_stop_sim(philo->rules) == 0)
		printf("%ld %d %s\n", time_diff, philo->id, msg);
	pthread_mutex_unlock(&philo->rules->print_lock);
}

void	set_stop_sim(t_rules *rules)
{
	pthread_mutex_lock(&rules->simulation_lock);
	rules->stop_simulation = 1;
	pthread_mutex_unlock(&rules->simulation_lock);
}

int	get_stop_sim(t_rules *rules)
{
	int	value;

	pthread_mutex_lock(&rules->simulation_lock);
	value = rules->stop_simulation;
	pthread_mutex_unlock(&rules->simulation_lock);
	return (value);
}

int	philo_full(t_philo *philo)
{
	int	full;

	pthread_mutex_lock(&philo->philo_lock);
	if (philo->meals_eaten >= philo->rules->must_eat_count
		&& philo->rules->must_eat_count > 0)
		full = 1;
	else
		full = 0;
	pthread_mutex_unlock(&philo->philo_lock);
	return (full);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}
