/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:17:21 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/15 18:38:37 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

/* Adapted usleep function. Thread sleeps exactly the indicated milliseconds
for a more precise usleep(). */
void	ft_usleep(useconds_t ms)
{
	long	time;

	time = ft_get_time();
	while (ft_get_time() < (time + ms))
		usleep(500);
}


/* Gets the current time in milliseconds. */
long	ft_get_time(void)
{
	long			current_time;
	int				err_msg;
	struct timeval	time;

	err_msg = 0;
	current_time = 0;
	err_msg = gettimeofday(&time, NULL);
	if (err_msg != 0)
	{
		printf("Error: current time could not be determined\n");
		return (-1);
	}
	current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (current_time);
}
