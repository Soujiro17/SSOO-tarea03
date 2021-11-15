#include <random>
#include <iostream>    // for cout
#include <fstream>
#include <queue>       // for queue
#include <vector>      // for vector
#include <array>
#include <future>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <csignal>
#include <unistd.h>

void signal_handler( int signal_num ) { 
	
    switch (signal_num){
    case  SIGINT:
        std::cout << "Detención no permitida" << std::endl;
        break;
    case SIGUSR1:
        exit(EXIT_SUCCESS);
        break;
    case SIGUSR2:
        exit(EXIT_SUCCESS);
        break;
    default:
        break;
    }
} 

int main(){

    long int c = 0, a = 0, b = 1;
    int child = fork();

	std::signal(SIGUSR1, signal_handler);
    std::signal(SIGUSR2, signal_handler);
	std::signal(SIGINT, signal_handler); 

    for(int i = 0; i < 50; i++) {

        if(child < 0){ // ERROR
            std::cerr << "Error al crear el hijo.";
            exit(EXIT_FAILURE);
        }else if (child == 0){ // HIJO
            if (i % 2 != 0)
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "Valor Impar: " << i << " - PID = " << getpid() << "\n";
            }
        }else{ // PADRE
            c = a + b;
            a = b;
            b = c;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "Valor Fibonacci: " << c  << " - PPIDE = " << getpid() << std::endl;
        }
    }

    exit(EXIT_SUCCESS);
}