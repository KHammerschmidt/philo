/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:04:15 by khammers          #+#    #+#             */
/*   Updated: 2022/03/16 15:05:23 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

/* **************************************************************** */
/*							INCLUDES								*/
/* **************************************************************** */

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>	//necessary??
# include <pthread.h>
# include <sys/time.h>

# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>

# define GRABBING_FORKS	1
# define RETURNING_FORKS	2
# define SEM_FORKS	"/sem_forks"
# define SEM_PRINT	"/sem_print"
# define SEM_REAPER "/sem_reaper"

/* **************************************************************** */
/*							STRUCTS									*/
/* **************************************************************** */

typedef struct s_philo
{
	int				id;
	pid_t			pid;
	int				num_meals;
	int				stuffed;
	long			last_meal_ts;
	pthread_t		reaper;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				exit_status;
	long			starttime;
	int				num_philos;
	int				num_philos_created;
	int				ttd;
	int				tte;
	int				tts;
	int				mte;
	int				fed_philos;
	sem_t			*sem_forks;
	sem_t			*sem_print;
	sem_t			*sem_reaper;
	struct s_philo	*philo;
}	t_data;

/* **************************************************************** */
/*							PROTOYPES								*/
/* **************************************************************** */

int		main(int argc, char *argv[]);

/* Initialisation & input handling */
int		parsing(t_data *data, int argc, char *argv[]);
int		init(t_data *data);

/* Process handling */
int		philo_lifecycle(t_philo *philo);
int		philo_simulation_main(t_data *data);
void	ft_free_and_exit(t_data *data, int status);
void	ft_print_log(int id, int status, t_data *data);
int		ft_eating_ceremony(int id, t_data *data);
void	ft_think(int id, t_data *data);
void	ft_sleep(int id, t_data *data);
int		ft_create_reaper_thread(t_philo *philo);

/* Time related functions */
long	ft_get_time(void);
void	ft_usleep(useconds_t ms);

/* Utils */
int		ft_isdigit(int c);
int		ft_isnum(char *str);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);

#endif