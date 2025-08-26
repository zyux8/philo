/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:24:51 by ohaker            #+#    #+#             */
/*   Updated: 2025/08/26 19:06:49 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int check_input(int argc, char **argv)
{
	int x;
	int y;

	if (argc < 5 || argc > 6)
		error_msg("Invalid number of arguments.\n");
	if (ft_atoi(argv[1]) == 0)
		error_msg("Impossible number of philosophers.\n");
	if (argc == 6 && ft_atoi(argv[5]) == 0)
		error_msg("Impossible number of must-have meals.\n");
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
	long time_diff;
	
	x = 0;
	pthread_mutex_lock(&rules->alive_lock);
	while (x < rules->philo_count)
	{
		pthread_mutex_lock(&rules->meal_lock);
		time_diff = get_time_diff(rules->philos[x].last_meal);
		pthread_mutex_unlock(&rules->meal_lock);
		if (time_diff > rules->time_to_die)
		{
			printf_safe(&rules->philos[x], "di3d");
			set_stop_sim(rules);
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
	long time_diff;

	while (!get_stop_sim(rules))
	{
		check_alive(rules);
		if (rules->must_eat_count > 0 && all_eaten(rules) )
		{
			set_stop_sim(rules);
			return (0);
		}
		usleep(10000);
	}
	return (0);
}
