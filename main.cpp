#include <stdio.h>
#include <pthread.h>

#include "simulation.h"
#include "UART.h"
#include "asservissement.h"

#include <iostream>

Simulation* m_Simulation = 0;

void* start_simulation_thread(void*) {
    m_Simulation->start();
    exit(0);
}


bool setRobotPositionFromAsservissement() {
    bouge_robot_sdl(
        get_x_actuel()/PLATEAU_SCALE,
        (PLATEAU_LARG - get_y_actuel())/PLATEAU_SCALE,
        (double)get_theta_actuel()/-1000);
    return true;
}

int main() {
    m_Simulation = new Simulation();
    m_Simulation->init();

    pthread_t uiThread;
    pthread_create(&uiThread, NULL, &start_simulation_thread, NULL);

    init_UART_thread();

    std::cout << "This is the working thread !" << std::endl;

    m_Simulation->plateau->addPointPassageCarto(0,00,0);
    //Glib::signal_timeout().connect( sigc::ptr_fun(&setRobotPositionFromAsservissement), 20);

    pause();

    return 0;
}




void bouge_robot_sdl(int x, int y, double alpha){
    m_Simulation->plateau->setRobotPosition(x, y, alpha);
}
void dessine_obstacle_rond(int cx, int cy, int r){
    m_Simulation->plateau->addObstacleRond(cx, cy, r);
}
void dessine_obstacle_ligne(int x1, int y1, int x2, int y2){
    m_Simulation->plateau->addObstacleLine(x1, y1, x2, y2);
}
void dessine_point_passage_carto(int x, int y, int type) {
    m_Simulation->plateau->addPointPassageCarto(x, y, type);
}
