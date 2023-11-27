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
        obstacle_file = fopen("/Users/chilledpi/Documents/dev/C:C++/SoftwareEngineering/Google_tests/obstacle.txt", "r");
        dust_file = fopen("/Users/chilledpi/Documents/dev/C:C++/SoftwareEngineering/Google_tests/dust.txt", "r");
    }

    virtual void TearDown() {
        fclose(obstacle_file);
        fclose(dust_file);
    }

    FILE * obstacle_file;
    FILE * dust_file;
};

TEST_F(MyTestFixture,FSI_TRUE){
    EXPECT_EQ(Front_Sensor_Interface(obstacle_file, 5), 1);
}
TEST_F(MyTestFixture, FSI_FALSE){
    EXPECT_EQ(Front_Sensor_Interface(obstacle_file, 1), 0);
}

TEST_F(MyTestFixture,FLI_TRUE){
    Front_Sensor_Interface(obstacle_file, 3);
    EXPECT_EQ(Left_Sensor_Interface(obstacle_file), 1);
}
TEST_F(MyTestFixture,FLI_FALSE){
    Front_Sensor_Interface(obstacle_file, 1);
    EXPECT_EQ(Left_Sensor_Interface(obstacle_file), 0);
}

TEST_F(MyTestFixture,TRUE){
    Front_Sensor_Interface(obstacle_file, 2);
    Left_Sensor_Interface(obstacle_file);
    EXPECT_EQ(Right_Sensor_Interface(obstacle_file), 1);
}

TEST_F(MyTestFixture,FALSE){
    Front_Sensor_Interface(obstacle_file, 1);
    Left_Sensor_Interface(obstacle_file);
    EXPECT_EQ(Right_Sensor_Interface(obstacle_file), 0);
}

TEST(DOL_MOVE_FORWARD, FFF){
    Prev_Moter_Command = MOVE_FORWARD;
    EXPECT_EQ(Determine_Obstacle_Location(1), MOVE_FORWARD);
}
TEST(DOL_MOVE_FORWARD, FFT){
    Prev_Moter_Command = MOVE_FORWARD;
    EXPECT_EQ(Determine_Obstacle_Location(2), MOVE_FORWARD);
}
TEST(DOL_MOVE_FORWARD, FTF){
    Prev_Moter_Command = MOVE_FORWARD;
    EXPECT_EQ(Determine_Obstacle_Location(3), MOVE_FORWARD);
}
TEST(DOL_MOVE_FORWARD, FTT){
    Prev_Moter_Command = MOVE_FORWARD;
    EXPECT_EQ(Determine_Obstacle_Location(4), MOVE_FORWARD);
}
TEST(DOL_MOVE_FORWARD, TFF){
    Prev_Moter_Command = MOVE_FORWARD;
    EXPECT_EQ(Determine_Obstacle_Location(5), TURN_LEFT);
}
TEST(DOL_MOVE_FORWARD, TFT){
    Prev_Moter_Command = MOVE_FORWARD;
    EXPECT_EQ(Determine_Obstacle_Location(6), TURN_LEFT);
}
TEST(DOL_MOVE_FORWARD, TTF){
    Prev_Moter_Command = MOVE_FORWARD;
    EXPECT_EQ(Determine_Obstacle_Location(7), TURN_RIGHT);
}
TEST(DOL_MOVE_FORWARD, TTT){
    Prev_Moter_Command = MOVE_FORWARD;
    EXPECT_EQ(Determine_Obstacle_Location(8), MOVE_BACKWARD);
}

TEST(DOL_MOVE_BACKWARD, FFF){
    Prev_Moter_Command = MOVE_BACKWARD;
    EXPECT_EQ(Determine_Obstacle_Location(1), TURN_LEFT);
}
TEST(DOL_MOVE_BACKWARD, FFT){
    Prev_Moter_Command = MOVE_BACKWARD;
    EXPECT_EQ(Determine_Obstacle_Location(2), TURN_LEFT);
}
TEST(DOL_MOVE_BACKWARD, FTF){
    Prev_Moter_Command = MOVE_BACKWARD;
    EXPECT_EQ(Determine_Obstacle_Location(3), TURN_RIGHT);
}
TEST(DOL_MOVE_BACKWARD, FTT){
    Prev_Moter_Command = MOVE_BACKWARD;
    EXPECT_EQ(Determine_Obstacle_Location(4), MOVE_BACKWARD);
}
TEST(DOL_MOVE_BACKWARD, TFF){
    Prev_Moter_Command = MOVE_BACKWARD;
    EXPECT_EQ(Determine_Obstacle_Location(5), TURN_LEFT);
}
TEST(DOL_MOVE_BACKWARD, TFT){
    Prev_Moter_Command = MOVE_BACKWARD;
    EXPECT_EQ(Determine_Obstacle_Location(6), TURN_LEFT);
}
TEST(DOL_MOVE_BACKWARD, TTF){
    Prev_Moter_Command = MOVE_BACKWARD;
    EXPECT_EQ(Determine_Obstacle_Location(7), TURN_RIGHT);
}
TEST(DOL_MOVE_BACKWARD, TTT){
    Prev_Moter_Command = MOVE_BACKWARD;
    EXPECT_EQ(Determine_Obstacle_Location(8), MOVE_BACKWARD);
}







int main(int argc, char **argv) {
	    ::testing::InitGoogleTest(&argc, argv);
	        return RUN_ALL_TESTS();
}

