/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katharinahammerschmidt <katharinahammer    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:33:07 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/07 23:11:08 by katharinaha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

/* Initialises variables in t_philo. */
void	init_philo_struct(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->num_philos)
	{
		data->philo[i].last_meal_ts = 0;
		data->philo[i].num_meals = 0;
		i++;
	}
}

/* Initialises the mutexes within t_philo, fork and a check_lock. */
int	init_mutex_philo_fork_check(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philo[i].id = i;
		if (pthread_mutex_init(&(data->philo[i].fork), NULL) != 0)
		{
			printf("Error: Mutex init fork\n");
			return (1);
		}
		if (pthread_mutex_init(&(data->philo[i].check_lock), NULL) != 0)
		{
			printf("Error: Mutex init fork\n");
			return (1);
		}
		i++;
	}
	return (0);
}

/* Initialises all mutexes of t_data: print status, reaper_lock, 
assembly_lock and meal_lock. */
static int	init_mutexes_data(t_data *data)
{
	if (pthread_mutex_init(&(data->print_status), NULL) != 0)
	{
		printf("Error: Mutex init\n");
		return (1);
	}
	if (pthread_mutex_init(&(data->reaper_lock), NULL) != 0)
	{
		printf("Error: Mutex init reaper lock\n");
		return (1);
	}
	if (pthread_mutex_init(&(data->assembly_lock), NULL) != 0)
	{
		printf("Error: Mutex init assembly lock\n");
		return (1);
	}
	if (data->mte != -1)
	{
		if (pthread_mutex_init(&(data->meal_lock), NULL) != 0)
		{
			printf("Error: Mutex init meal lock\n");
			return (1);
		}
	}
	return (0);
}

/* Calls the functions to initialise all mutexes within the structs. */
int	ft_init(t_data *data)
{
	if (init_mutex_philo_fork_check(data) != 0)
		return (1);
	if (init_mutexes_data(data) != 0)
		return (1);
	init_philo_struct(data);
	return (0);
}