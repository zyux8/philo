/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:24:51 by ohaker            #+#    #+#             */
/*   Updated: 2025/07/26 20:17:34 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int check_input(int argc, char **argv)
{
	int x;
	int y;

	if (argc < 5 || argc > 6)
	error_msg("Invalid number of arguments.\n");
	x = 1;
	while (argv[x])
	{
		y = 0;
		while (argv[x][y])
		{
			if (!ft_isdigit(argv[x][y]))
				error_msg("Invalid input.\n");
			y++;
		}
		x++;
	}
	return (0);
}

int check_alive(t_rules *rules)
{
	int x;

	x = 0;
	pthread_mutex_lock(&rules->alive_lock);
	while (x < rules->philo_count)
	{
		if (!rules->philos[x].alive)
		{
			printf_safe(&rules->philos[x], "died\n");
			rules->stop_simulation = 1;
			pthread_mutex_unlock(&rules->alive_lock);
			return (0);
		}
		x++;
	}
	pthread_mutex_unlock(&rules->alive_lock);
	return (1);
}

int all_eaten(t_rules *rules)
{
	int x;

	x = 0;
	while (x < rules->philo_count)
	{
		pthread_mutex_lock(&rules->meal_lock);
		if (rules->philos[x].meals_eaten < rules->must_eat_count)
		{
			pthread_mutex_unlock(&rules->meal_lock);
			return (0);
		}
		pthread_mutex_unlock(&rules->meal_lock);
		x++;
	}
	return (1);
}

int check_end(t_rules *rules)
{
	int x;
	long time_diff;

	while (!rules->stop_simulation)
	{
		x = 0;
		while (x < rules->philo_count)
		{
			pthread_mutex_lock(&rules->meal_lock);
			time_diff = get_time_diff(rules->philos[x].last_meal);
			pthread_mutex_unlock(&rules->meal_lock);
			if (time_diff > rules->time_to_eat)
			{
				printf_safe(&rules->philos[x], "died\n");
				rules->stop_simulation = 1;
				return (0);
			}
			x++;
		}
		if (rules->must_eat_count > 0 && all_eaten(rules))
		{
			rules->stop_simulation = 1;
			return (0);
		}
		usleep(1000);
	}
	return (0);
}
