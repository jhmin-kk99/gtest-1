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
extern int Moter_Command, Clean_Command;

class MyTestFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        obstacle_file = fopen("C:\\Users\\user\\CLionProjects\\gtest-1\\Google_tests\\obstacle.txt", "r");
        dust_file = fopen("C:\\Users\\user\\CLionProjects\\gtest-1\\Google_tests\\dust.txt", "r");
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



int main(int argc, char **argv) {
	    ::testing::InitGoogleTest(&argc, argv);
	        return RUN_ALL_TESTS();
}

