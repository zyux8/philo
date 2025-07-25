/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:51:15 by ohaker            #+#    #+#             */
/*   Updated: 2025/07/23 03:15:04 by ohaker           ###   ########.fr       */
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

int init_input(int argc, char **argv, t_philo *philo)
{
	int x;
	int y;

	x = 0;
	y = 0;
	philo->rules->philo_count = ft_atoi(argv[1]);
	philo->rules->time_to_die = ft_atoi(argv[2]);
	philo->rules->time_to_eat = ft_atoi(argv[3]);
	philo->rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->rules->must_eat_count = ft_atoi(argv[5]);
	else if (argc == 5)
		philo->rules->must_eat_count = -1;
	philo->rules->forks = malloc(sizeof(pthread_mutex_t)
		* philo->rules->philo_count); //fix this ho
	if (!philo->rules->forks)
		error_msg("Memory allocation for forks failed.\n");
	while (x < ft_atoi(argv[1]))
		pthread_mutex_init(&philo->rules->forks[x++], NULL);
	pthread_mutex_init(&philo->rules->print_lock, NULL);
	pthread_mutex_init(&philo->rules->simulation_lock, NULL);
	return (0);
}

int init_philo(t_rules *rules)
{
	int x;

	x = 0;
	rules->philos = malloc(sizeof(t_philo) * rules->philo_count);
	if (!rules->philos)
		error_msg("Memory allocation of philos failes.\n");
	while (x < rules->philo_count)
	{
		rules->philos[x].rules = rules;
		rules->philos[x].id = x;
		rules->philos[x].meals_eaten = 0;
		rules->philos[x].last_meal = 0;
		rules->philos[x].left_fork = &rules->forks[x];
		rules->philos[x].right_fork = &rules->forks[(x + 1) % rules->philo_count];
		x++;
	}
	gettimeofday(&rules->start_time, NULL);
	return (0);
}

void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	if (philo->id % 2 == 0)
		usleep(100);
	while(//all philos alive)
	{
		philo_think(&philo);
		if (philo_fork(&philo))
		{
			philo_eat(&philo);
			philo_sleep(&philo);
		}
	}
}

int thread_create(t_rules *rules)
{
	int x;

	x = 0;
	if (rules->philo_count == 1)
		pthread_create(rules->philos[x].thread_id, NULL, one_philo, NULL);
	while (x < rules->philo_count)
	{
		pthread_create(rules->philos[x].thread_id, NULL, philo_routine, NULL);
	}
}

int main(int argc, char **argv)
{
	t_philo philo;

	philo.rules = malloc(sizeof(t_rules));
	if (!philo.rules)
		error_msg("Memory allocation failed.\n");
	check_input(argc, argv);
	init_input(argc, argv, &philo);
	init_philos(&philo.rules);
	printf("philos: %d\ndie: %d\neat: %d\nsleep: %d\ncount: %d\n", philo.rules->philo_count, philo.rules->time_to_die, philo.rules->time_to_eat, philo.rules->time_to_sleep, philo.rules->must_eat_count);
	return (0);
}
