#include <iostream>
#include <vector>
#include <random>
using namespace std;

class Process {
public:
	int pid;								//each process has a process id or pid and a vector that stores all of the tickets assigned to this process
	vector<int> tickets;

	Process(int id) {						//this initializes the process with the number associated with it
		pid = id;
	}
};

class Scheduler {
private:
	vector<Process> processes;						//the scheduler holds a vector of the processes declared
	int winningTicket;								//it also has a winning ticket variable to cross check algorithms worked correctly in the printTickets function
	int ticketsPerProcess;

public:

	Scheduler(int t) {								//This is the constructor to initialize the ticketsPerProcess and declare the winning ticket as non existent yet (-1)
		ticketsPerProcess = t;
		winningTicket = -1;
	}

	void allocateTickets() {															//once all the processes have been added this function is called to randomly distribute tickets based on ticketsPerProcess
		srand(time(0));																		//set the rand function to a random set of integers
		vector<int> availableTickets;													
		for (int i = 0; i < processes.size() * ticketsPerProcess; i++) {					//This loop will create an in order vector of ticket numbers of processes * ticketsPerProcess
			availableTickets.push_back(i);
		}

		for (int j = 0; j < processes.size(); j++) {										//Loop through the processes
			for (int k = 0; k < ticketsPerProcess; k++) {										//Loop through the tickets in each process
				int currTicket = rand() % availableTickets.size();									//Select a random ticket from the vector of available tickets
				processes.at(j).tickets.push_back(availableTickets.at(currTicket));					//Add the ticket to the Process
				availableTickets.erase(availableTickets.begin() + currTicket);						//Erase the ticket from the vector of available tickets
			}
		}
	}

	Process selectProcess(){
		winningTicket = rand() % (processes.size() * ticketsPerProcess);				//Randomly select the winning ticket based on number of processes * tickets per process
		for (int i = 0; i < processes.size(); i++) {									//Loop through the processes
			Process currProcess = processes.at(i);										
			vector<int>::iterator ticketPlace = find(currProcess.tickets.begin(), currProcess.tickets.end(), winningTicket);	//try to find the winning tickets in the vector of tickets for the current process
			if (ticketPlace != currProcess.tickets.end()) {									//if the winning ticket was found (ie the find function didn't return the end of the ticket list) return the current process
				return currProcess;
			}
		}
	}

	void addProcess(Process p1) {														//add a new process to the vector of processes
		processes.push_back(p1);
	}

	void printTickets() {																//this print function is purely for checking the ticket assignment and selection of the winning process are working as expected 
		for (int i = 0; i < processes.size(); i++) {										//loop through the processes
			cout << "Process " << processes.at(i).pid << " has tickets: ";						//display the current process
			int j = 0;
			while (j < ticketsPerProcess-1) {													//loop through the tickets in each process
				cout << processes.at(i).tickets.at(j) << ", ";										//display each ticket followed by a comma
				j++;
			}
			cout << processes.at(i).tickets.at(j) << endl;										//display the last ticket in each process
		}
		cout << "Winning Ticket is: " << winningTicket << endl;								//lastly display the winning ticket number for checking purposes
	}
};

int main() {
	int ticketsPerProcess = 6;
	Scheduler s1(ticketsPerProcess);													// This creates a scheduler with a known value of how many tickets per process it should distribute

	Process p1(1);																		//lines 78-82 all declare seperate processes
	Process p2(2);
	Process p3(3);
	Process p4(4);
	Process p5(5);

	s1.addProcess(p1);																	//lines 84-88 add all of the processes into the scheduler
	s1.addProcess(p2);
	s1.addProcess(p3);
	s1.addProcess(p4);
	s1.addProcess(p5);

	s1.allocateTickets();																//AFTER ALL processes have been added to the scheduler assign the tickets to each process

	Process selectedProcess = s1.selectProcess();										//select the winning process

	//s1.printTickets();																//uncomment this line to see the allocation of the tickets as well as the selection of the winning ticket to return the correct process

	cout << "Process " << selectedProcess.pid << " won the lottery!" << endl;			//Print out the winning processes id
}