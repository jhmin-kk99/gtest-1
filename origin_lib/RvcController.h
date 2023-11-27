//
// Created by user on 2023-11-24.
//

#ifndef SOFTWAREENGINEERING_RVCCONTROLLER_H
#define SOFTWAREENGINEERING_RVCCONTROLLER_H

#ifdef __cplusplus
extern "C"{


#endif
#include <stdio.h>
enum MoterCommand { MOVE_FORWARD, MOVE_BACKWARD, TURN_LEFT, TURN_RIGHT, MOVE_FORWARD_DISABLE, MOVE_BACKWARD_DISABLE };
enum CleanerCommand { POWER_ON, POWER_OFF, POWER_UP };
enum Enable_Or_Disable { ENABLE, DISABLE };

struct Moter_Status {
    int MoveForward;
    int MoveBackward;
    int Turn;
};
struct Cleaner_Status {
    int Power;
};
int Front_Sensor_Interface(FILE* file, int line);
int Left_Sensor_Interface(FILE* file);
int Right_Sensor_Interface(FILE* file);
int Dust_Sensor_Interface(FILE* file, int line);

void Move_Forward(int Enable_Or_Disable, struct Moter_Status *moterStatus);
void Move_Backward(int Enable_Or_Disable, struct Moter_Status *moterStatus);
void Turn_Left(struct Moter_Status *moterStatus);
void Turn_Right(struct Moter_Status *moterStatus);

void Power_On(struct Cleaner_Status *cleanerStatus);
void Power_Off(struct Cleaner_Status *cleanerStatus);
void Power_Up(struct Cleaner_Status *cleanerStatus);

void Moter_Interface(int command, struct Moter_Status *moterStatus);
void Cleaner_Interface(int command, struct Cleaner_Status *cleanerStatus);

int Determine_Obstacle_Location(FILE* file,int line);
int Determine_Dust_Existence(FILE* file, int line);
int Moter_Control(int Obstacle_Location, int Dust_Existence, struct Moter_Status *moterStatus);
int Cleaner_Control(int Obstacle_Location, int Dust_Existence, struct Cleaner_Status *cleanStatus);
void run(const char* Obstacle_file, const char* Dust_file,struct Moter_Status *moterStatus, struct Cleaner_Status *cleanerStatus, int Obstacle_line, int Dust_line);

#ifdef __cplusplus
}

#endif
#endif //SOFTWAREENGINEERING_RVCCONTROLLER_H
