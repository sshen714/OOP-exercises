#include <gtest/gtest.h>

#include "MaglevTrain.hpp"

TEST(MAGLEV_TRAIN_TEST, test_check_make_ticket_should_give_correct_infor){
    MaglevTrain electricalTrain = MaglevTrain(100,40,TrainType::Local,1937,100);

    int pL = electricalTrain.GetPowerLimit();
    int p = electricalTrain.GetPower();
    int sL = electricalTrain.GetSeatLimit();
    int s = electricalTrain.GetSeat();
    int tN = electricalTrain.GetTrainNumber();
    int spL = electricalTrain.GetSpeedLimit();
    int sp = electricalTrain.GetSpeed();
    bool op = electricalTrain.IsOpen();
    TrainType type = electricalTrain.GetType();

    ASSERT_EQ(pL,100);
    ASSERT_EQ(p,0);
    ASSERT_EQ(sL,40);
    ASSERT_EQ(s,0);
    ASSERT_EQ(tN,1937);
    ASSERT_EQ(spL,100);
    ASSERT_EQ(sp,0);
    ASSERT_EQ(op, false);
    ASSERT_EQ(type,TrainType::Local);
}

TEST(MAGLEV_TRAIN_TEST, test_check_make_ticket_should_can_set_power_correct){
    MaglevTrain electricalTrain = MaglevTrain(0,40,TrainType::Limited,1937,100);

    int pL = electricalTrain.GetPowerLimit();
    ASSERT_EQ(pL,0);

    electricalTrain.SetPowerLimit(50);
    ASSERT_EQ(electricalTrain.GetPowerLimit(),50);

    ASSERT_THROW(electricalTrain.SetPowerLimit(-1),std::invalid_argument);
    ASSERT_THROW(electricalTrain.SetPowerLimit(127),std::invalid_argument);
    ASSERT_EQ(electricalTrain.GetType(),TrainType::Limited);
}

TEST(MAGLEV_TRAIN_TEST, test_check_make_ticket_should_can_set_seat_correct){
    MaglevTrain electricalTrain = MaglevTrain(0,40,TrainType::Express,1937,100);

    int s = electricalTrain.GetSeat();
    ASSERT_EQ(s,0);

    for(int i=0;i<40;i++){
        electricalTrain.AddSeat();
        ASSERT_EQ(electricalTrain.GetSeat(),i+1);
    }

    ASSERT_THROW(electricalTrain.AddSeat(),std::invalid_argument);
}

TEST(MAGLEV_TRAIN_TEST, test_check_make_ticket_should_can_speedUp_and_speedDown_correct){
    MaglevTrain electricalTrain = MaglevTrain(100,40,TrainType::Express,1937,500);

    electricalTrain.Charge(7);
    ASSERT_EQ(electricalTrain.GetPower(),100);
    ASSERT_EQ(electricalTrain.GetSpeed(),0);
    electricalTrain.PowerUp();
    ASSERT_EQ(electricalTrain.GetPower(),99);
    electricalTrain.SpeedUp();
    ASSERT_EQ(electricalTrain.GetPower(),96);
    ASSERT_EQ(electricalTrain.GetSpeed(),25);
    electricalTrain.SpeedUp();
    ASSERT_EQ(electricalTrain.GetPower(),93);
    ASSERT_EQ(electricalTrain.GetSpeed(),51);
    for(int i=0;i<31;i++){
        electricalTrain.SpeedUp();
    }
    ASSERT_EQ(electricalTrain.GetSpeed(),500);

    ASSERT_THROW(electricalTrain.SpeedUp(),std::invalid_argument);

    electricalTrain.Charge(7);
    electricalTrain.SpeedDown();
    ASSERT_EQ(electricalTrain.GetSpeed(),475);
    for(int i=0;i<33;i++){
        electricalTrain.SpeedDown();
        electricalTrain.SpeedUp();
    }
    for(int i=0;i<70;i++){
        electricalTrain.SpeedDown();
    }
    ASSERT_EQ(electricalTrain.GetSpeed(),0);
    ASSERT_EQ(electricalTrain.GetPower(),1);
    ASSERT_THROW(electricalTrain.SpeedUp(),std::invalid_argument);
    ASSERT_EQ(electricalTrain.GetSpeed(),0);
}

TEST(MAGLEV_TRAIN_TEST, test_check_powerUp_should_throw_when_power_is_zero){
    MaglevTrain electricalTrain = MaglevTrain(100,40,TrainType::Express,1937,170);

    ASSERT_EQ(electricalTrain.GetPower(),0);
    ASSERT_THROW(electricalTrain.PowerUp(),std::invalid_argument);
    ASSERT_EQ(electricalTrain.IsOpen(),false);
    ASSERT_EQ(electricalTrain.GetPower(),0);
}

TEST(MAGLEV_TRAIN_TEST, test_check_speedUp_and_speedDown_should_throw_when_not_open){
    MaglevTrain train = MaglevTrain(100,40,TrainType::Express,1937,500);
    train.Charge(1);

    ASSERT_THROW(train.SpeedUp(),std::invalid_argument);
    ASSERT_THROW(train.SpeedDown(),std::invalid_argument);
    ASSERT_EQ(train.GetSpeed(),0);
}

TEST(MAGLEV_TRAIN_TEST, test_check_speedUp_and_speedDown_should_throw_when_power_is_not_enough){
    MaglevTrain train = MaglevTrain(3,40,TrainType::Express,1937,170);

    ASSERT_THROW(train.PowerUp(),std::invalid_argument);
    train.Charge(1);
    train.PowerUp();
    ASSERT_EQ(train.GetPower(),2);
    ASSERT_THROW(train.SpeedUp(),std::invalid_argument);
    ASSERT_EQ(train.GetSpeed(),0);
    ASSERT_EQ(train.GetPower(),2);
}
