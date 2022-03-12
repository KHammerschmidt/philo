/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:04:26 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/12 22:19:53 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo_bonus.h"

/* Status change of a dead philo is printed and death_lock set to 1. */
static void	activate_reaper(t_philo *philo, int i)
{
	unsigned long timestamp;

	timestamp = 0;
	sem_wait(philo->data->sem_reaper);
	timestamp = ft_get_time() - philo->data->starttime;
	sem_wait(philo->data->sem_print);
	printf("%lu %d died\n", timestamp, i + 1);
	philo->data->death_lock++;
	sem_post(philo->data->sem_print);
	sem_post(philo->data->sem_reaper);
	// kill(-1, SIGKILL);	// kill(0, SIGINT);		// kill (-1, SIGINT/SIGKILL)???
	exit(1);
}

/* Checks in a loop if philosophers are already stuffed or if a philo exceeded
ttd with his last meal. */
void	*reaper_main(void *varg)
{
	t_philo	*philo;

	philo = (t_philo *)varg;
	while (1)
	{
		sem_wait(philo->data->sem_reaper);
		if ((ft_get_time() - philo->data->starttime) - philo->last_meal_ts
			> philo->data->ttd)
			{
				activate_reaper(philo, philo->id);
			}
		sem_post(philo->data->sem_reaper);
	}
	return (NULL);
}

/* Creates thread reaper and calles reaper_main(). */
int	ft_create_reaper_thread(t_philo *philo)
{
	if (pthread_create(&(philo->reaper), NULL, &reaper_main, philo) != 0)
	{
		printf("Error: thread creation\n");
		return (1);
	}
	return (0);
}
