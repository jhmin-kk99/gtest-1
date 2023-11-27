//
// Created by user on 2023-11-24.
//
#include "RvcController.h"

int Prev_Moter_Command;
int Front_Obstacle, Left_Obstacle, Right_Obstacle;
int Obstacle_Location;
int Dust_Existence;
int Moter_Command, Clean_Command;

int Front_Sensor_Interface(FILE* file, int line){
    int i, ret;
    for(i = 1; i < line; i++){
        while(fgetc(file) != '\n');
    }
    if (fscanf(file, "%d", &ret) != 1) {
        return -1;
    }
    return ret;
};
int Left_Sensor_Interface(FILE* file){
    int ret;
    if (fscanf(file, "%d", &ret) != 1) {
        return -1;
    }
    return ret;
};
int Right_Sensor_Interface(FILE* file){
    int ret;
    if (fscanf(file, "%d", &ret) != 1) {
        return -1;
    }
    return ret;
};
int Dust_Sensor_Interface(FILE* file, int line){
    int i, ret;
    for(i = 1; i < line; i++){
        while(fgetc(file) != '\n');
    }
    if (fscanf(file, "%d", &ret) != 1) {
        return -1;
    }
    return ret;};

void Move_Forward(int Enable_Or_Disable){};
void Move_Backward(int Enable_Or_Disable){};
void Turn_Left(){};
void Turn_Right(){};

void Power_On(){};
void Power_Off(){};
void Power_Up(){};

void Moter_Interface(int command){};
void Clean_Interface(int command){};

int Determine_Obstacle_Location(int line){
    FILE* file;
    int i;
    fopen("/Users/chilledpi/Documents/dev/C:C++/SoftwareEngineering/Google_tests/obstacle.txt", "r");
    if (file == NULL) {
        // 오류 처리, 예를 들어 오류 메시지 출력 및 반환
        perror("파일 열기 오류");
        return -1;
    }
    for(i = 1; i < line; i++){
        while(fgetc(file) != '\n');
    }
    Front_Obstacle = Front_Sensor_Interface(file, line);
    Left_Obstacle = Left_Sensor_Interface(file);
    Right_Obstacle = Right_Sensor_Interface(file);
    fclose(file);
    if(Prev_Moter_Command == MOVE_BACKWARD){
        if (!Left_Obstacle) return TURN_LEFT; // TURNLEFT
        if (Left_Obstacle && !Right_Obstacle) return TURN_RIGHT; //TURNRIGHT
        if(Left_Obstacle && Right_Obstacle) return MOVE_BACKWARD; // MOVEBACKWARD 유지
    } else {
        if (!Front_Obstacle) return MOVE_FORWARD; // MOVEFORWARD 유지
        if (Front_Obstacle && !Left_Obstacle) return TURN_LEFT; // TURNLEFT
        if (Front_Obstacle && Left_Obstacle && !Right_Obstacle) return TURN_RIGHT; // TURNRIGHT
        if(Front_Obstacle && Left_Obstacle && Right_Obstacle) return MOVE_BACKWARD;  // MOVEBACKWARD
    }
}
int Determine_Dust_Existence(int line) {
    FILE* file = fopen("/Users/chilledpi/Documents/dev/C:C++/SoftwareEngineering/Google_tests/dust.txt", "r");
    if (file == NULL) {
        // 오류 처리, 예를 들어 오류 메시지 출력 및 반환
        perror("파일 열기 오류");
        return -1;
    }
    return Dust_Sensor_Interface(file, line); }

int Moter_Control(){
    if(Dust_Existence) {
        Move_Forward(DISABLE);
        return MOVE_FORWARD;
    }
    switch (Obstacle_Location)
    { case MOVE_FORWARD:
            Move_Forward(ENABLE);
            return MOVE_FORWARD;

        case MOVE_BACKWARD:
            Move_Forward(DISABLE);
            Move_Backward(ENABLE);
            return MOVE_BACKWARD;

        case TURN_LEFT:
            if (Prev_Moter_Command == MOVE_FORWARD)
                Move_Forward(DISABLE);
            else if (Prev_Moter_Command == MOVE_BACKWARD)
                Move_Backward(DISABLE);
            Turn_Left();
            return TURN_LEFT;

        case TURN_RIGHT:
            if (Prev_Moter_Command == MOVE_FORWARD)
                Move_Forward(DISABLE);
            else if (Prev_Moter_Command == MOVE_BACKWARD)
                Move_Backward(DISABLE);
            Turn_Right();
            return TURN_RIGHT;
    }
}

int Clean_Control(int Obstacle_Location, int Dust_Existence){
    switch (Obstacle_Location)
    {
        case MOVE_FORWARD:
            Power_On();
            if (Dust_Existence){
                Power_Up();
                return POWER_UP;
            }
            return POWER_ON;

        case MOVE_BACKWARD:
        case TURN_LEFT:
        case TURN_RIGHT:
            Power_Off();
            return POWER_OFF;
    }
}

void run(){
    Move_Forward(ENABLE);
    Power_On();
    Prev_Moter_Command = MOVE_FORWARD;
    while (1) {
        Obstacle_Location = Determine_Obstacle_Location(1);
        Dust_Existence = Determine_Dust_Existence(1);
        Moter_Command = Moter_Control();
        Moter_Interface(Moter_Command);
        Clean_Command = Clean_Control(Obstacle_Location, Dust_Existence);
        Clean_Interface(Clean_Command);
        Prev_Moter_Command = Moter_Command;
    }
}