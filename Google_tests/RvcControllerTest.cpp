//
// Created by user on 2023-11-24.
//
#include "gtest/gtest.h"
#include "RvcController.h"
#include <cstdio>

extern int Prev_Moter_Command;
extern int Front_Obstacle, Left_Obstacle, Right_Obstacle;
extern int Obstacle_Location;
extern int Dust_Existence;
extern int Moter_Command, Cleaner_Command;


class MyTestFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        const char* Obstacle_Location_File = "C:\\Users\\user\\CLionProjects\\gtest-1\\Google_tests\\obstacle.txt";
        const char* Dust_Exist_File = "C:\\Users\\user\\CLionProjects\\gtest-1\\Google_tests\\dust.txt";
        obstacle_file = fopen(Obstacle_Location_File, "r");
        dust_file = fopen(Dust_Exist_File, "r");
    }

    virtual void TearDown() {
        fclose(obstacle_file);
        fclose(dust_file);
    }

    FILE * obstacle_file;
    FILE * dust_file;
};

TEST_F(MyTestFixture, Front_Sensor_Interface_1){
    //전방에 장애물이 있는 경우
    int line_num = 5;
    EXPECT_EQ(Front_Sensor_Interface(obstacle_file, line_num), 1);
}
TEST_F(MyTestFixture, Front_Sensor_Interface_2){
    //전방에 장애물이 없는 경우
    int line_num = 1;
    EXPECT_EQ(Front_Sensor_Interface(obstacle_file, line_num), 0);
}

TEST_F(MyTestFixture, Left_Sensor_Interface_1){
    //좌측에 장애물이 있는 경우
    int line_num = 3;
    Front_Sensor_Interface(obstacle_file, line_num);
    EXPECT_EQ(Left_Sensor_Interface(obstacle_file), 1);
}
TEST_F(MyTestFixture, Left_Sensor_Interface_2){
    //좌측에 장애물이 없는 경우
    int line_num = 2;
    Front_Sensor_Interface(obstacle_file, line_num);
    EXPECT_EQ(Left_Sensor_Interface(obstacle_file), 0);
}

TEST_F(MyTestFixture, Right_Sensor_Interface_1){
    //우측에 장애물이 있는 경우
    int line_num = 2;
    Front_Sensor_Interface(obstacle_file, line_num);
    Left_Sensor_Interface(obstacle_file);
    EXPECT_EQ(Right_Sensor_Interface(obstacle_file), 1);
}

TEST_F(MyTestFixture,Right_Sensor_Interface_2){
    //우측에 장애물이 없는 경우
    int line_num = 3;
    Front_Sensor_Interface(obstacle_file, line_num);
    Left_Sensor_Interface(obstacle_file);
    EXPECT_EQ(Right_Sensor_Interface(obstacle_file), 0);
}

TEST_F(MyTestFixture, Determine_Obstacle_Location_1){
    // 직진하던 중, obstacle (front, left, right) : (0, 0, 0)인 경우
    int line_num = 1;
    Prev_Moter_Command = MOVE_FORWARD;
    EXPECT_EQ(Determine_Obstacle_Location(obstacle_file,line_num), MOVE_FORWARD);
}
TEST_F(MyTestFixture, Determine_Obstacle_Location_2){
    // 직진하던 중, obstacle (front, left, right) : (0, 0, 1)인 경우
    int line_num = 2;
    Prev_Moter_Command = MOVE_FORWARD;
    EXPECT_EQ(Determine_Obstacle_Location(obstacle_file,line_num), MOVE_FORWARD);
}
TEST_F(MyTestFixture, Determine_Obstacle_Location_3){
    // 직진하던 중, obstacle (front, left, right) : (0, 1, 0)인 경우
    int line_num = 3;
    Prev_Moter_Command = MOVE_FORWARD;
    EXPECT_EQ(Determine_Obstacle_Location(obstacle_file,line_num), MOVE_FORWARD);
}
TEST_F(MyTestFixture, Determine_Obstacle_Location_4){
    // 직진하던 중, obstacle (front, left, right) : (0, 1, 1)인 경우
    int line_num = 4;
    Prev_Moter_Command = MOVE_FORWARD;
    EXPECT_EQ(Determine_Obstacle_Location(obstacle_file,line_num), MOVE_FORWARD);
}
TEST_F(MyTestFixture, Determine_Obstacle_Location_5){
    // 직진하던 중, obstacle (front, left, right) : (1, 0, 0)인 경우
    int line_num = 5;
    Prev_Moter_Command = MOVE_FORWARD;
    EXPECT_EQ(Determine_Obstacle_Location(obstacle_file,line_num), TURN_LEFT);
}
TEST_F(MyTestFixture, Determine_Obstacle_Location_6){
    // 직진하던 중, obstacle (front, left, right) : (1, 0, 1)인 경우
    int line_num = 6;
    Prev_Moter_Command = MOVE_FORWARD;
    EXPECT_EQ(Determine_Obstacle_Location(obstacle_file,line_num), TURN_LEFT);
}
TEST_F(MyTestFixture, Determine_Obstacle_Location_7){
    // 직진하던 중, obstacle (front, left, right) : (1, 1, 0)인 경우
    int line_num = 7;
    Prev_Moter_Command = MOVE_FORWARD;
    EXPECT_EQ(Determine_Obstacle_Location(obstacle_file,line_num), TURN_RIGHT);
}
TEST_F(MyTestFixture, Determine_Obstacle_Location_8){
    // 직진하던 중, obstacle (front, left, right) : (1, 1, 1)인 경우
    int line_num = 8;
    Prev_Moter_Command = MOVE_FORWARD;
    EXPECT_EQ(Determine_Obstacle_Location(obstacle_file,line_num), MOVE_BACKWARD);
}

TEST_F(MyTestFixture, Determine_Obstacle_Location_9){
    // 후진하던 중, obstacle (front, left, right) : (0, 0, 0)인 경우
    int line_num = 1;
    Prev_Moter_Command = MOVE_BACKWARD;
    EXPECT_EQ(Determine_Obstacle_Location(obstacle_file, line_num), TURN_LEFT);
}
TEST_F(MyTestFixture, Determine_Obstacle_Location_10){
    // 후진하던 중, obstacle (front, left, right) : (0, 0, 1)인 경우
    int line_num = 2;
    Prev_Moter_Command = MOVE_BACKWARD;
    EXPECT_EQ(Determine_Obstacle_Location(obstacle_file, line_num), TURN_LEFT);
}
TEST_F(MyTestFixture, Determine_Obstacle_Location_11){
    // 후진하던 중, obstacle (front, left, right) : (0, 1, 0)인 경우
    int line_num = 3;
    Prev_Moter_Command = MOVE_BACKWARD;
    EXPECT_EQ(Determine_Obstacle_Location(obstacle_file, line_num), TURN_RIGHT);
}
TEST_F(MyTestFixture, Determine_Obstacle_Location_12){
    // 후진하던 중, obstacle (front, left, right) : (0, 1, 1)인 경우
    int line_num = 4;
    Prev_Moter_Command = MOVE_BACKWARD;
    EXPECT_EQ(Determine_Obstacle_Location(obstacle_file, line_num), MOVE_BACKWARD);
}
TEST_F(MyTestFixture, Determine_Obstacle_Location_13){
    // 후진하던 중, obstacle (front, left, right) : (1, 0, 0)인 경우
    int line_num = 5;
    Prev_Moter_Command = MOVE_BACKWARD;
    EXPECT_EQ(Determine_Obstacle_Location(obstacle_file, line_num), TURN_LEFT);
}
TEST_F(MyTestFixture, Determine_Obstacle_Location_14){
    // 후진하던 중, obstacle (front, left, right) : (1, 0, 1)인 경우
    int line_num = 6;
    Prev_Moter_Command = MOVE_BACKWARD;
    EXPECT_EQ(Determine_Obstacle_Location(obstacle_file, line_num), TURN_LEFT);
}
TEST_F(MyTestFixture, Determine_Obstacle_Location_15){
    // 후진하던 중, obstacle (front, left, right) : (1, 1, 0)인 경우
    int line_num = 7;
    Prev_Moter_Command = MOVE_BACKWARD;
    EXPECT_EQ(Determine_Obstacle_Location(obstacle_file, line_num), TURN_RIGHT);
}
TEST_F(MyTestFixture, Determine_Obstacle_Location_16){
    // 후진하던 중, obstacle (front, left, right) : (1, 1, 1)인 경우
    int line_num = 8;
    Prev_Moter_Command = MOVE_BACKWARD;
    EXPECT_EQ(Determine_Obstacle_Location(obstacle_file,line_num), MOVE_BACKWARD);
}

TEST_F(MyTestFixture, Moter_Interface_1){
    struct Moter_Status moterStatus;
    int command = MOVE_FORWARD;
    Moter_Interface(command, &moterStatus);
    EXPECT_EQ(moterStatus.MoveForward,MOVE_FORWARD);
}

TEST_F(MyTestFixture, Moter_Interface_2){
    struct Moter_Status moterStatus;
    int command = MOVE_FORWARD_DISABLE;
    Moter_Interface(command, &moterStatus);
    EXPECT_EQ(moterStatus.MoveForward,MOVE_FORWARD_DISABLE);
}
// 전진과 후진 로직이 거의 같으므로 전진만 test함.

TEST_F(MyTestFixture, Moter_Interface_5){
    struct Moter_Status moterStatus;
    int command = TURN_LEFT;
    Moter_Interface(command, &moterStatus);
    EXPECT_EQ(moterStatus.Turn,TURN_LEFT);
}
// 좌,우 로직이 거의 같으므로 좌만 test함.

TEST_F(MyTestFixture, Cleaner_Interface_1){
    struct Cleaner_Status cleanerStatus;
    int command = POWER_ON;
    Cleaner_Interface(command, &cleanerStatus);
    EXPECT_EQ(cleanerStatus.Power,POWER_ON);
}
// POWER ON,UP,OFF 로직이 거의 같으므로 ON만 test함.


/**
 void Move_Forward(int Enable_Or_Disable, struct Moter_Status *moterStatus){
    int command;
    if(Enable_Or_Disable == ENABLE) command = MOVE_FORWARD;
    else command = MOVE_FORWARD_DISABLE;
    Moter_Interface(command, moterStatus);
};
**/

TEST_F(MyTestFixture, MOVE_FORWARD_1){
    struct Moter_Status moterStatus;
    Move_Forward(ENABLE,&moterStatus);
    EXPECT_EQ(Moter_Command,MOVE_FORWARD);
    //command가 잘 작동하는지
    EXPECT_EQ(moterStatus.MoveForward,MOVE_FORWARD);
    //Moter Interface를 잘 호출하는지
}


TEST_F(MyTestFixture, MOVE_BACKWARD_2){
    struct Moter_Status moterStatus;
    Move_Backward(DISABLE,&moterStatus);
    EXPECT_EQ(Moter_Command,MOVE_BACKWARD_DISABLE);
    //command가 잘 작동하는지
    EXPECT_EQ(moterStatus.MoveBackward,MOVE_BACKWARD_DISABLE);
    //Moter Interface를 잘 호출하는지
}
TEST_F(MyTestFixture, TURN_LEFT_1){
    struct Moter_Status moterStatus;
    Turn_Left(&moterStatus);
    EXPECT_EQ(Moter_Command,TURN_LEFT);
    //command가 잘 작동하는지
    EXPECT_EQ(moterStatus.Turn,TURN_LEFT);
    //Moter Interface를 잘 호출하는지
}

TEST_F(MyTestFixture, POWER_UP_1){
    struct Cleaner_Status cleanerStatus;
    Power_Up(&cleanerStatus);
    EXPECT_EQ(Cleaner_Command,POWER_UP);
    //command가 잘 작동하는지
    EXPECT_EQ(cleanerStatus.Power,POWER_UP);
    //Cleaner Interface를 잘 호출하는지
}

/**
    struct Moter_Status moterStatus;
    Dust_Existence = true;
    Obstacle_Location = MOVE_FORWARD;
    Prev_Moter_Command = MOVE_FORWARD;
 */

TEST_F(MyTestFixture, Moter_Control_1){
    struct Moter_Status moterStatus;
    Dust_Existence = true;
    Obstacle_Location = MOVE_FORWARD;
    Prev_Moter_Command = MOVE_FORWARD;

    EXPECT_EQ(Moter_Control(Obstacle_Location,Dust_Existence,&moterStatus),MOVE_FORWARD_DISABLE);
    //return값
    EXPECT_EQ(Prev_Moter_Command,MOVE_FORWARD);
    //Prev_Moter_Command 값
    EXPECT_EQ(Moter_Command,MOVE_FORWARD_DISABLE);
    //command가 잘 작동하는지
    EXPECT_EQ(moterStatus.MoveForward,MOVE_FORWARD_DISABLE);
    //Moter Interface를 잘 호출하는지
}


TEST_F(MyTestFixture, Moter_Control_2){
    struct Moter_Status moterStatus;
    Dust_Existence = false;
    Obstacle_Location = MOVE_FORWARD;
    Prev_Moter_Command = TURN_LEFT;

    EXPECT_EQ(Moter_Control(Obstacle_Location,Dust_Existence,&moterStatus),MOVE_FORWARD);
    //return값
    EXPECT_EQ(Prev_Moter_Command,MOVE_FORWARD);
    //Prev_Moter_Command 값
    EXPECT_EQ(moterStatus.MoveForward,MOVE_FORWARD);
    //Moter Interface를 잘 호출하는지
}

TEST_F(MyTestFixture, Moter_Control_3){
    struct Moter_Status moterStatus;
    Dust_Existence = false;
    Obstacle_Location = MOVE_BACKWARD;
    Prev_Moter_Command = MOVE_FORWARD;

    EXPECT_EQ(Moter_Control(Obstacle_Location,Dust_Existence,&moterStatus),MOVE_BACKWARD);
    //return값
    EXPECT_EQ(Prev_Moter_Command,MOVE_BACKWARD);
    //Prev_Moter_Command 값
    EXPECT_EQ(moterStatus.MoveForward,MOVE_FORWARD_DISABLE);
    //Moter Interface를 잘 호출하는지
    EXPECT_EQ(moterStatus.MoveBackward,MOVE_BACKWARD);
    //Moter Interface를 잘 호출하는지
}
TEST_F(MyTestFixture, Moter_Control_4){
    struct Moter_Status moterStatus;
    Dust_Existence = false;
    Obstacle_Location = TURN_LEFT;
    Prev_Moter_Command = MOVE_BACKWARD;

    EXPECT_EQ(Moter_Control(Obstacle_Location,Dust_Existence,&moterStatus),TURN_LEFT);
    //return값
    EXPECT_EQ(Prev_Moter_Command,TURN_LEFT);
    //Prev_Moter_Command 값
    EXPECT_EQ(moterStatus.Turn,TURN_LEFT);
    //Moter Interface를 잘 호출하는지
    EXPECT_EQ(moterStatus.MoveBackward,MOVE_BACKWARD_DISABLE);
    //Moter Interface를 잘 호출하는지
}
TEST_F(MyTestFixture, Cleaner_Control_1){
    struct Cleaner_Status cleanerStatus;
    Dust_Existence = false;
    Obstacle_Location = MOVE_FORWARD;

    EXPECT_EQ(Cleaner_Control(Obstacle_Location,Dust_Existence,&cleanerStatus),POWER_ON);
    //return값
    EXPECT_EQ(cleanerStatus.Power,POWER_ON);
    //Power Interface를 잘 호출하는지
}
TEST_F(MyTestFixture, Cleaner_Control_2){
    struct Cleaner_Status cleanerStatus;
    Dust_Existence = true;
    Obstacle_Location = MOVE_FORWARD;

    EXPECT_EQ(Cleaner_Control(Obstacle_Location,Dust_Existence,&cleanerStatus),POWER_UP);
    //return값
    EXPECT_EQ(cleanerStatus.Power,POWER_UP);
    //Power Interface를 잘 호출하는지
}
TEST_F(MyTestFixture, Cleaner_Control_3){
    struct Cleaner_Status cleanerStatus;
    Dust_Existence = false;
    Obstacle_Location = TURN_LEFT;

    EXPECT_EQ(Cleaner_Control(Obstacle_Location,Dust_Existence,&cleanerStatus),POWER_OFF);
    //return값
    EXPECT_EQ(cleanerStatus.Power,POWER_OFF);
    //Power Interface를 잘 호출하는지
}
TEST(Simulation, run_1){
    struct Moter_Status moterStatus;
    struct Cleaner_Status cleanerStatus;
    const char* Obstacle_Location_File = "C:\\Users\\user\\CLionProjects\\gtest-1\\Google_tests\\obstacle.txt";
    const char* Dust_Exist_File = "C:\\Users\\user\\CLionProjects\\gtest-1\\Google_tests\\dust.txt";
    run(Obstacle_Location_File,Dust_Exist_File,&moterStatus, &cleanerStatus, 5,1);
    // 100 / 0
    EXPECT_EQ(moterStatus.Turn,TURN_LEFT);
    EXPECT_EQ(cleanerStatus.Power, POWER_OFF);

}

TEST(Simulation, run_2){
    struct Moter_Status moterStatus;
    struct Cleaner_Status cleanerStatus;
    const char* Obstacle_Location_File = "C:\\Users\\user\\CLionProjects\\gtest-1\\Google_tests\\obstacle.txt";
    const char* Dust_Exist_File = "C:\\Users\\user\\CLionProjects\\gtest-1\\Google_tests\\dust.txt";

    run(Obstacle_Location_File,Dust_Exist_File,&moterStatus, &cleanerStatus, 5,1);
    // 100 / 0
    EXPECT_EQ(moterStatus.Turn,TURN_LEFT);
    EXPECT_EQ(cleanerStatus.Power, POWER_OFF);
    run(Obstacle_Location_File,Dust_Exist_File,&moterStatus, &cleanerStatus, 4,2);
    // 011 / 1
    EXPECT_EQ(Dust_Existence,true);
    EXPECT_EQ(Obstacle_Location, MOVE_FORWARD);
    EXPECT_EQ(Prev_Moter_Command, MOVE_FORWARD);
    EXPECT_EQ(moterStatus.MoveForward,MOVE_FORWARD_DISABLE);
    EXPECT_EQ(cleanerStatus.Power, POWER_UP);

}
TEST(Simulation, run_3){
    struct Moter_Status moterStatus;
    struct Cleaner_Status cleanerStatus;
    const char* Obstacle_Location_File = "C:\\Users\\user\\CLionProjects\\gtest-1\\Google_tests\\obstacle.txt";
    const char* Dust_Exist_File = "C:\\Users\\user\\CLionProjects\\gtest-1\\Google_tests\\dust.txt";

    run(Obstacle_Location_File,Dust_Exist_File,&moterStatus, &cleanerStatus, 5,1);
    // 100 / 0
    EXPECT_EQ(moterStatus.Turn,TURN_LEFT);
    EXPECT_EQ(cleanerStatus.Power, POWER_OFF);
    run(Obstacle_Location_File,Dust_Exist_File,&moterStatus, &cleanerStatus, 4,2);
    // 011 / 1
    EXPECT_EQ(Dust_Existence,true);
    EXPECT_EQ(Obstacle_Location, MOVE_FORWARD);
    EXPECT_EQ(Prev_Moter_Command, MOVE_FORWARD);
    EXPECT_EQ(moterStatus.MoveForward,MOVE_FORWARD_DISABLE);
    EXPECT_EQ(cleanerStatus.Power, POWER_UP);
    run(Obstacle_Location_File,Dust_Exist_File,&moterStatus, &cleanerStatus, 4,1);
    // 011 / 0
    EXPECT_EQ(moterStatus.MoveForward,MOVE_FORWARD);
    EXPECT_EQ(cleanerStatus.Power, POWER_ON);
    run(Obstacle_Location_File,Dust_Exist_File,&moterStatus, &cleanerStatus, 6,1);
    // 101 / 0
    EXPECT_EQ(Obstacle_Location, TURN_LEFT);
    EXPECT_EQ(moterStatus.MoveForward,MOVE_FORWARD_DISABLE);
    EXPECT_EQ(moterStatus.Turn,TURN_LEFT);
    EXPECT_EQ(cleanerStatus.Power, POWER_OFF);
    run(Obstacle_Location_File,Dust_Exist_File,&moterStatus, &cleanerStatus, 7,1);
    // 110 / 0
    EXPECT_EQ(moterStatus.Turn,TURN_RIGHT);
    EXPECT_EQ(cleanerStatus.Power, POWER_OFF);
}

int main(int argc, char **argv) {
	    ::testing::InitGoogleTest(&argc, argv);
	        return RUN_ALL_TESTS();
}

