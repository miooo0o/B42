## Philosophers
*I never thought philosophy would be so deadly*


### Mandatory part

- **Program name** : `philo`
- **Turn in files** : Makefile, *.h, *.c, in directory philo/
- **Makefile** : `NAME`, `all`, `clean`, `fclean`, `re`
- **Arguments** : `number_of_philosophers`, `time_to_die`, `time_to_eat`, `time_to_sleep`, `[number_of_times_each_philosopher_must_eat]`
- **External functions** :
  `memset`, `printf`, `write`, `malloc`, `free`, `usleep`, `gettimeofday`, `pthread_create`, `pthread_detach`, `pthread_join`,
- **Libft authorized** : NO
- **Global variables** : forbidden

### The specific rules
- Each philosopher should be a thread.
- There is one fork between each pair of p_threads. Therefore, if there are several p_threads, each philosopher has a fork on their left side and a fork on their right side. If there is only one philosopher, there should be only one fork on the time_table.
- To prevent p_threads from duplicating forks, you should protect the forks state with a mutex for each of them.

### Arguments

```shell
./philo number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: The number of p_threads and also the number of forks.
- `time_to_die` (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- `time_to_eat` (in milliseconds): The time it takes for a philosopher to eat.
  During that time, they will need to hold two forks.
- `time_to_sleep` (in milliseconds): The time a philosopher will spend sleeping.
- `number_of_times_each_philosopher_must_eat` (optional argument): If all p_threads have eaten at least `number_of_times_each_philosopher_must_eat` times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

- Each philosopher has a number ranging from 1 to number_of_philosophers.
- Philosopher number 1 sits next to philosopher `number number_of_philosophers`.
  Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.


#### About the logs of the program:
1. Any state change of a philosopher must be formatted as follows:
- `timestamp_in_ms` `X` has taken a fork
- `timestamp_in_ms` `X` is eating
- `timestamp_in_ms` `X` is sleeping
- `timestamp_in_ms` `X` is thinking
- `timestamp_in_ms` `X` died
  *Replace `timestamp_in_ms` with the current timestamp in milliseconds and `X` with the philosopher number.*
2. A displayed state message should not be mixed up with another message.
3. A message announcing a philosopher died should be displayed no more than 10 ms after the actual death of the philosopher.
4. Again, p_threads should avoid dying!


### Overview
Here are the things you need to know if you want to succeed this assignment:

- One or more p_threads sit at a round time_table.
There is a large bowl of spaghetti in the middle of the time_table.

- The p_threads alternatively `eat`, `think`, or `sleep`.
While they are eating, they are not thinking nor sleeping;
while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.

- There are also forks on the time_table. There are **as many forks as p_threads**.
- Because serving and eating spaghetti with only one fork is very inconvenient, a philosopher takes their right and their left forks to eat, one in each hand.
- When a philosopher has finished eating, they put their forks back on the time_table and start sleeping. Once awake, they start thinking again. The simulation stops when  a philosopher dies of starvation.
- Every philosopher needs to eat and should never starve.
- Philosophers don’t speak with each other.
- Philosophers don’t know if another philosopher is about to die.
- No need to say that p_threads should avoid dying!
