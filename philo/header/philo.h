#ifndef PHILO_H
# define PHILO_H

/* **************************************************************** */
/*							INCLUDES								*/
/* **************************************************************** */

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

#define GRABBING_FORKS	1
#define RETURNING_FORKS	2

/* **************************************************************** */
/*							STRUCTS									*/
/* **************************************************************** */

typedef struct		s_philo
{
	pthread_t		thread_id;
	int				id;
	int				num_meals;
	long			last_meal_ts;
	pthread_mutex_t	fork;
	pthread_mutex_t	check_lock;
	struct s_data	*data;
} 	t_philo;


typedef struct 		s_data
{
	long			starttime;
	int				num_philos;
	int				num_philos_created;
	int				ttd;
	int				tte;
	int				tts;
	int				mte;
	int				fed_philos;
	int				death_lock;
	int				fed_lock;
	pthread_mutex_t	assembly_lock;
	pthread_mutex_t	print_status;
	pthread_mutex_t	reaper_lock;
	pthread_mutex_t	meal_lock;
	struct s_philo	*philo;
	pthread_t		reaper;
	pthread_t		stuffed;
} 	t_data;

/* **************************************************************** */
/*							PROTOYPES								*/
/* **************************************************************** */

int		main(int argc, char *argv[]);

/* Initialisation & input handling */
int		parsing(t_data *data, int argc, char *argv[]);
int		ft_init(t_data *data);
void	init_philo_struct(t_data *data);

/* Thread handling, e.g. thread creation and joining. */
int		ft_create_philo_threads(t_data *data);
void	ft_print_log(int id, int status, t_data *data);
int		ft_eating_ceremony(int id, t_data *data);
void	ft_think(int id, t_data *data);
void	ft_sleep(int id, t_data *data);
int		ft_create_reaper_thread(t_data *data);
int		ft_create_stuffed_thread(t_data *data);
int		ft_join_threads(t_data *data);

/* Time related functions */
long	ft_get_time(void);
void	ft_usleep(useconds_t ms);

/* Utils */
int		ft_isdigit(int c);
int		ft_isnum(char *str);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);

#endif