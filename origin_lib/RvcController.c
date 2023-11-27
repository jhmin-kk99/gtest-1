//
// Created by user on 2023-11-24.
//
#include "RvcController.h"

int Prev_Moter_Command;
int Front_Obstacle, Left_Obstacle, Right_Obstacle;
int Obstacle_Location;
int Dust_Existence;
int Moter_Command, Cleaner_Command;


//파일 절대경로
const char* obstacle_Location_file = "C:\\Users\\user\\CLionProjects\\gtest-1\\Google_tests\\obstacle.txt";
const char* dust_Location_file = "C:\\Users\\user\\CLionProjects\\gtest-1\\Google_tests\\dust.txt";


//o
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
//o
int Left_Sensor_Interface(FILE* file){
    int ret;
    if (fscanf(file, "%d", &ret) != 1) {
        return -1;
    }
    return ret;
};
//o
int Right_Sensor_Interface(FILE* file){
    int ret;
    if (fscanf(file, "%d", &ret) != 1) {
        return -1;
    }
    return ret;
};
//o
int Dust_Sensor_Interface(FILE* file, int line){
    int i, ret;
    for(i = 1; i < line; i++){
        while(fgetc(file) != '\n');
    }
    if (fscanf(file, "%d", &ret) != 1) {
        return -1;
    }
    return ret;
};

//o
int Determine_Obstacle_Location(FILE *file, int line){
    Front_Obstacle = Front_Sensor_Interface(file, line);
    Left_Obstacle = Left_Sensor_Interface(file);
    Right_Obstacle = Right_Sensor_Interface(file);

    if(Prev_Moter_Command == MOVE_BACKWARD){
        if (!Left_Obstacle) return TURN_LEFT; // TURNLEFT
        if (Left_Obstacle && !Right_Obstacle) return TURN_RIGHT; //TURNRIGHT
        if(Left_Obstacle && Right_Obstacle) return MOVE_BACKWARD; // MOVEBACKWARD 유지
    } else {
        if (!Front_Obstacle) return MOVE_FORWARD; // MOVEFORWARD 
        if (Front_Obstacle && !Left_Obstacle) return TURN_LEFT; // TURNLEFT
        if (Front_Obstacle && Left_Obstacle && !Right_Obstacle) return TURN_RIGHT; // TURNRIGHT
        if(Front_Obstacle && Left_Obstacle && Right_Obstacle) return MOVE_BACKWARD;  // MOVEBACKWARD
    }
}
//o
    int Determine_Dust_Existence(FILE* file, int line) {
    return Dust_Sensor_Interface(file, line);
}

void Move_Forward(int Enable_Or_Disable, struct Moter_Status *moterStatus){
    if(Enable_Or_Disable == ENABLE) Moter_Command = MOVE_FORWARD;
    else Moter_Command = MOVE_FORWARD_DISABLE;
    Moter_Interface(Moter_Command, moterStatus);
};
void Move_Backward(int Enable_Or_Disable, struct Moter_Status *moterStatus){
    if(Enable_Or_Disable == ENABLE) Moter_Command = MOVE_BACKWARD;
    else Moter_Command = MOVE_BACKWARD_DISABLE;
    Moter_Interface(Moter_Command, moterStatus);
};
void Turn_Left(struct Moter_Status *moterStatus){
    Moter_Command = TURN_LEFT;
    Moter_Interface(Moter_Command, moterStatus);
};
void Turn_Right(struct Moter_Status *moterStatus){
    Moter_Command = TURN_RIGHT;
    Moter_Interface(Moter_Command, moterStatus);
};

void Power_On(struct Cleaner_Status *cleanerStatus){
    Cleaner_Command = POWER_ON;
    Cleaner_Interface(Cleaner_Command, cleanerStatus);
};
void Power_Off(struct Cleaner_Status *cleanerStatus){
    Cleaner_Command = POWER_OFF;
    Cleaner_Interface(Cleaner_Command, cleanerStatus);
};
void Power_Up(struct Cleaner_Status *cleanerStatus){
    Cleaner_Command = POWER_UP;
    Cleaner_Interface(Cleaner_Command,cleanerStatus);
};

void Moter_Interface(int command, struct Moter_Status *moterStatus){
    switch (command) {
        case MOVE_FORWARD:
            moterStatus->MoveForward = MOVE_FORWARD;
            break;
        case MOVE_FORWARD_DISABLE:
            moterStatus->MoveForward = MOVE_FORWARD_DISABLE;
            break;
        case MOVE_BACKWARD:
            moterStatus->MoveBackward = MOVE_BACKWARD;
            break;
        case MOVE_BACKWARD_DISABLE:
            moterStatus->MoveBackward = MOVE_BACKWARD_DISABLE;
            break;
        case TURN_LEFT:
            moterStatus->Turn = TURN_LEFT;
            break;
        case TURN_RIGHT:
            moterStatus->Turn = TURN_RIGHT;
            break;
    }
};
void Cleaner_Interface(int command, struct Cleaner_Status *cleanerStatus){
     switch (command) {
         case POWER_ON:
             cleanerStatus->Power = POWER_ON;
             break;
         case POWER_UP:
             cleanerStatus->Power = POWER_UP;
             break;
         case POWER_OFF:
             cleanerStatus->Power = POWER_OFF;
             break;
     }
};

int Moter_Control(int Obstacle_Location, int Dust_Existence, struct Moter_Status *moterStatus){
    if(Dust_Existence) {
        Move_Forward(DISABLE,moterStatus);
        Prev_Moter_Command = MOVE_FORWARD;
        return MOVE_FORWARD_DISABLE;
    }
    switch (Obstacle_Location)
    {
        case MOVE_FORWARD:
            Move_Forward(ENABLE, moterStatus);
            Prev_Moter_Command = MOVE_FORWARD;
            return MOVE_FORWARD;

        case MOVE_BACKWARD:
            if(Prev_Moter_Command == MOVE_FORWARD)
            Move_Forward(DISABLE,moterStatus);
            Move_Backward(ENABLE,moterStatus);
            Prev_Moter_Command = MOVE_BACKWARD;
            return MOVE_BACKWARD;

        case TURN_LEFT:
            if (Prev_Moter_Command == MOVE_FORWARD){
                Move_Forward(DISABLE,moterStatus);
            }
            else if (Prev_Moter_Command == MOVE_BACKWARD){
                Move_Backward(DISABLE, moterStatus);
            }
            Prev_Moter_Command = TURN_LEFT;
            Turn_Left(moterStatus);
            return TURN_LEFT;

        case TURN_RIGHT:
            if (Prev_Moter_Command == MOVE_FORWARD) {
                Move_Forward(DISABLE,moterStatus);
            }
            else if (Prev_Moter_Command == MOVE_BACKWARD){
                Move_Backward(DISABLE,moterStatus);
            }
            Prev_Moter_Command = TURN_RIGHT;
            Turn_Right(moterStatus);
            return TURN_RIGHT;
    }
}

int Cleaner_Control(int Obstacle_Location, int Dust_Existence, struct Cleaner_Status *cleanerStatus){
    switch (Obstacle_Location)
    {
        case MOVE_FORWARD:
            Power_On(cleanerStatus);
            if (Dust_Existence){
                Power_Up(cleanerStatus);
                return POWER_UP;
            }
            return POWER_ON;

        case MOVE_BACKWARD:
        case TURN_LEFT:
        case TURN_RIGHT:
            Power_Off(cleanerStatus);
            return POWER_OFF;
    }
}

//Iteration 1번 제대로 동작하는지
void run(const char* Obstacle_file, const char* Dust_file, struct Moter_Status *moterStatus, struct Cleaner_Status *cleanerStatus, int Obstacle_line, int Dust_line){

    FILE* Obstacle_Location_File = fopen(Obstacle_file, "r");
    FILE* Dust_Exist_File = fopen(Dust_file, "r");

    Obstacle_Location = Determine_Obstacle_Location(Obstacle_Location_File,Obstacle_line);
    Dust_Existence = Determine_Dust_Existence(Dust_Exist_File,Dust_line);
    Moter_Control(Obstacle_Location, Dust_Existence, moterStatus);
    Cleaner_Control(Obstacle_Location, Dust_Existence, cleanerStatus);

    fclose(Obstacle_Location_File);
    fclose(Dust_Exist_File);
}



