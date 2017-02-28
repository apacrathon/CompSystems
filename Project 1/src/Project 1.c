/*
 ============================================================================
 Name        : Project.c
 Author      : Raj Patel
 Version     :
 Copyright   : © 2017 Apacrathon, All Rights Reserved.
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

/*
 * Functions to read and write to a file.
 */
int32_t write_random_nums(int32_t n, FILE * f);
int32_t read_file(int32_t n, int32_t data[], FILE * f);

/*
 * Arithmetic functions for an array
 */

int32_t sum_of_array(int32_t n, int32_t data[]);
int32_t min_of_array(int32_t n, int32_t data[]);
int32_t max_of_array(int32_t n, int32_t data[]);

/*
 * Functions for each part
 */

int32_t PART_A(int32_t data_size, int32_t data[]);
int32_t PART_B(int32_t data_size, int32_t data[]);
int32_t PART_C(int32_t data_size, int32_t data[]);
int32_t PART_D(int32_t data_size, int32_t data[]);
int32_t PART_EC(int32_t data_size, int32_t data[]);

/*
 * Misc. functions.
 */
void print_array(int32_t data_size, int32_t data[]);

int main(void)
{
	srand(time(NULL));

	FILE * f_write = fopen("random.list", "w");
	FILE * f_read = fopen("random.list", "r");
	int32_t data_size = 100, data[data_size];

	//printf("\nWriting to file...\n");
	write_random_nums(data_size, f_write);
	//printf("Successfully wrote to file...\n");

	//printf("Reading from file...\n");
	read_file(data_size, data, f_read);
	//printf("Successfully read from file...\n");

	//PART_A(data_size, data);
	//PART_B(data_size, data);
	PART_C(data_size, data);
	return EXIT_SUCCESS;
}
int32_t PART_A(int32_t data_size, int32_t data[])
{
	pid_t pid = getpid();
	pid_t ppid = getppid();

	printf("Running Part A...\n\n");
	printf("Hi, I'm process %d, and my parent is %d.\n", pid, ppid);
	printf("The maximum value is: %d\n", max_of_array(data_size, data));
	printf("The minimum value is: %d\n", min_of_array(data_size, data));
	printf("The sum of the array is: %d\n", sum_of_array(data_size, data));
	return 0;
}

int32_t PART_B(int32_t data_size, int32_t data[])
{
	pid_t ppid = getppid(), pid = getpid();
	char buffer[30];
	int pipefd[2];
	if (pipe(pipefd) == -1) { printf("Error creating pipe."); return -1; }

	for (int i = 0; i < 5; i++) {
		pid_t pid = fork();

		if (pid > 0) {
			// parent
			printf("in parent with pid %d\n", getpid());

		} else if (pid == 0) {
			// child
			printf("in child with pid %d\n", getpid());
			exit(0);
		} else {
			printf("fork error\n");
			exit(1);
		}
	}
		for (int i = 0; i < 5; i++) {
			printf("I could be doing some work here\n");
			sleep(10);
			write(pipefd[1], "hello world\n", 12);
		}
}

int32_t PART_C(int32_t data_size, int32_t data[])
{
	int32_t min = data[0], max = data[0], sum = 0, num_processes, data_per_process;
	int32_t pipefd[2], pipefd2[2], data_buffer[data_size], stats_buffer[3] = { data[0], data[data_size - 1] ,0}, stats[3] = { min, max, sum };

	num_processes = data_size / 10;
	data_per_process = 10;

	if (pipe(pipefd) == -1) { printf("Error creating pipe."); return -1; }

	write(pipefd[1], data, data_size*sizeof(int));
	close(pipefd[1]);

	for (int i = 0; i < num_processes; i++)
	{
		pid_t pid = fork();
		sleep(2);
		if (pid > 0)
		{
			printf("in parent process (pid = %d)\n", getpid());
		}
		else if (pid == 0)
		{
			printf("in child process (pid = %d, ppid = %d)\n", getpid(), getppid());
			read(pipefd[0], data_buffer, data_per_process*sizeof(int));

			for (int j = 0; j < data_per_process; j++)
			{
				if (stats_buffer[0] > data_buffer[j]) { stats_buffer[0] = data_buffer[j]; }
				if (stats_buffer[1] < data_buffer[j]) { stats_buffer[1] = data_buffer[j]; }
				stats_buffer[2] += data_buffer[j];
			}

			print_array(3, stats_buffer);
			printf("\n");
			sleep(15);
			exit(0);
		}
		else { printf("fork error\n"); return -1; }
	}

	printf("min: %d, max: %d, sum: %d\n", stats[0], stats[1], stats[2]);
	printf("min2: %d, max2: %d, sum2: %d\n", min_of_array(data_size, data), max_of_array(data_size, data), sum_of_array(data_size, data));
}

int32_t write_random_nums(int32_t n, FILE * f)
{

	int32_t result = 0;

	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}

	for (int count = 0; count < n; count++)
	{
		fprintf(f, "%d\n", (rand() % 100));
	}

	result = fclose(f);

	return result;
}

int32_t read_file(int32_t n, int32_t data[], FILE * f)
{
	int32_t result = 0;

	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    return 1;
	}

	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &data[i]);
	}

	result = fclose(f);

	return result;
}

int32_t sum_of_array(int32_t n, int32_t data[])
{
	int sum = 0;

	for (int i = 0; i < n; i++)
	{
		sum += data[i];
	}

	return sum;
}

int32_t min_of_array(int32_t n, int32_t data[])
{
	int min = data[0];

	for (int i = 1; i < n; i++)
	{
		if (min > data[i]) { min = data[i]; }
	}

	return min;
}

int32_t max_of_array(int32_t n, int32_t data[])
{
	int min = data[0];

	for (int i = 1; i < n; i++)
	{
		if (min < data[i]) { min = data[i]; }
	}

	return min;
}

void print_array(int32_t n, int32_t data[])
{
	for (int32_t i = 0; i < n; i++)
	{
		printf("%d\n", data[i]);
	}
}
