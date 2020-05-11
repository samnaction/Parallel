// mpihello.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <mpi.h>
const int MAX_STRING = 100;
int main()
{
	char       greeting[MAX_STRING];  /* String storing message */
	int        comm_sz;               /* Number of processes    */
	int        my_rank;               /* My process rank        */

	/* Start up MPI */
	MPI_Init(NULL, NULL);

	/* Get the number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	/* Get my rank among all the processes */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if (my_rank != 0) {
		/* Create message */
		sprintf(greeting, "Greetings from process %d of %d!",
			my_rank, comm_sz);
		/* Send message to process 0 */
		MPI_Send(greeting, strlen(greeting) + 1, MPI_CHAR, 0, 0,
			MPI_COMM_WORLD);
	}
	else {
		/* Print my message */
		printf("Greetings from process %d of %d!\n", my_rank, comm_sz);
		for (int q = 1; q < comm_sz; q++) {
			/* Receive message from process q */
			MPI_Recv(greeting, MAX_STRING, MPI_CHAR, q,
				0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			MPI_Recv(greeting, MAX_STRING, MPI_CHAR, MPI_ANY_SOURCE,
				0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			/* Print message from process q */
			printf("%s\n", greeting);
		}
	}

	/* Shut down MPI */
	MPI_Finalize();

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
