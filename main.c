#include <stdio.h>
#include <stdlib.h>
#include "RvcController.h"
extern int Prev_Moter_Command;
extern int Front_Obstacle, Left_Obstacle, Right_Obstacle;
extern int Obstacle_Location;
extern int Dust_Existence;
extern int Moter_Command, Cleaner_Command;

int main() {
    //파일 절대경로 -> 수정해야 함 (절대경로)
    const char* obstacle_Location_file = "C:\\Users\\user\\CLionProjects\\gtest-1\\Google_tests\\obstacle.txt";
    const char* dust_Location_file = "C:\\Users\\user\\CLionProjects\\gtest-1\\Google_tests\\dust.txt";

    struct Moter_Status moterStatus;
    moterStatus.MoveForward = -1;
    moterStatus.MoveBackward = -1;
    moterStatus.Turn = -1;
    //  MOVE_FORWARD, MOVE_BACKWARD, TURN_LEFT, TURN_RIGHT, MOVE_FORWARD_DISABLE, MOVE_BACKWARD_DISABLE
    struct Cleaner_Status cleanerStatus;
    cleanerStatus.Power = -1;
    // POWER_ON, POWER_OFF, POWER_UP

    Prev_Moter_Command = -1;
    // MOVE_FORWARD, MOVE_BACKWARD, TURN_LEFT, TURN_RIGHT

    int obstacle_line=0;
    int dust_line=0;

    while(1){
        if(Prev_Moter_Command == TURN_LEFT || Prev_Moter_Command == TURN_RIGHT){
            while((obstacle_line = (int)(rand() % 8) + 1) > 4); // 5~8
            // 좌,우회전을 한다면, 더이상 후진을 하지 않을 때까지 적당히 후진 한다고 가정
        }else if(Prev_Moter_Command == MOVE_BACKWARD){
            while((obstacle_line = (int)(rand() % 8) + 1) == 8); // 1~7
            // 후진을 한다면, 더이상 후진을 하지 않을 때까지 적당히 후진 한다고 가정
        }else (obstacle_line = (int)(rand() % 8) + 1); // 1~8

        dust_line = (int)(rand() % 2) + 1; //1~2
        printf("\nPrev_Moter_Command : %d\n",Prev_Moter_Command);

        Controller(obstacle_Location_file,dust_Location_file,&moterStatus, &cleanerStatus,obstacle_line,dust_line);
        printf("Front,Left,Right Obstacle : %d%d%d -> Obstacle_Location : %d , Dust_Existence : %d \n",
                   Front_Obstacle,Left_Obstacle,Right_Obstacle,Obstacle_Location,Dust_Existence);

        printf("\nController -> \n");
        printf("Moter_Interface -> MOVE_FORWARD : %d, MOVE_BACKWARD : %d, TURN : %d\n",moterStatus.MoveForward,moterStatus.MoveBackward,moterStatus.Turn);
        printf("Cleaner_Interface -> POWER : %d\n",cleanerStatus.Power);

        //동작 초기화
        moterStatus.MoveForward = -1;
        moterStatus.MoveBackward = -1;
        moterStatus.Turn = -1;
        cleanerStatus.Power = -1;
    }

    return 0;
}