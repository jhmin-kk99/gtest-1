//
// Created by user on 2023-11-24.
//

#ifndef SOFTWAREENGINEERING_RVCCONTROLLER_H
#define SOFTWAREENGINEERING_RVCCONTROLLER_H

#ifdef __cplusplus
extern "C"{


#endif
#include <stdio.h>
enum Moter_Command { MOVE_FORWARD, MOVE_BACKWARD, TURN_LEFT, TURN_RIGHT };
enum Cleaner_Command { POWER_ON, POWER_OFF, POWER_UP };
enum Enable_Or_Disable { ENABLE, DISABLE };

//extern int Prev_Moter_Command;
//extern int Front_Obstacle, Left_Obstacle, Right_Obstacle;
//extern int Obstacle_Location;
//extern int Dust_Existence;
//extern int Moter_Command, Clean_Command;

int Front_Sensor_Interface(FILE* file, int line);
int Left_Sensor_Interface(FILE* file);
int Right_Sensor_Interface(FILE* file);
int Dust_Sensor_Interface(FILE* file, int line);

void Move_Forward(int Enable_Or_Disable);
void Move_Backward(int Enable_Or_Disable);
void Turn_Left();
void Turn_Right();

void Power_On();
void Power_Off();
void Power_Up();

void Moter_Interface(int command);
void Clean_Interface(int command);

int Determine_Obstacle_Location(int line);
int Determine_Dust_Existence();
int Moter_Control();
int Clean_Control(int Obstacle_Location, int Dust_Existence);
void run();


//extern int Prev_Moter_Command;
//extern int Front_Obstacle, Left_Obstacle, Right_Obstacle;
//extern int Obstacle_Location;
//extern int Dust_Existence;
//extern int Moter_Command, Clean_Command;
#ifdef __cplusplus
}

#endif
#endif //SOFTWAREENGINEERING_RVCCONTROLLER_H
