#include <gtest/gtest.h>

#include "ElectricalTrain.hpp"

TEST(ELECTRICAL_TRAIN_TEST, test_check_make_ticket_should_give_correct_infor){
    ElectricalTrain electricalTrain = ElectricalTrain(100,40,TrainType::Local,1937,100);

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

TEST(ELECTRICAL_TRAIN_TEST, test_check_make_ticket_should_can_set_power_correct){
    ElectricalTrain electricalTrain = ElectricalTrain(0,40,TrainType::Limited,1937,100);

    int pL = electricalTrain.GetPowerLimit();
    ASSERT_EQ(pL,0);

    electricalTrain.SetPowerLimit(50);
    ASSERT_EQ(electricalTrain.GetPowerLimit(),50);

    ASSERT_THROW(electricalTrain.SetPowerLimit(-1),std::invalid_argument);
    ASSERT_THROW(electricalTrain.SetPowerLimit(127),std::invalid_argument);
    ASSERT_EQ(electricalTrain.GetType(),TrainType::Limited);
}

TEST(ELECTRICAL_TRAIN_TEST, test_check_make_ticket_should_can_set_seat_correct){
    ElectricalTrain electricalTrain = ElectricalTrain(0,40,TrainType::Express,1937,100);

    int s = electricalTrain.GetSeat();
    ASSERT_EQ(s,0);

    for(int i=0;i<40;i++){
        electricalTrain.AddSeat();
        ASSERT_EQ(electricalTrain.GetSeat(),i+1);
    }

    ASSERT_THROW(electricalTrain.AddSeat(),std::invalid_argument);
}

TEST(ELECTRICAL_TRAIN_TEST, test_check_make_ticket_should_can_speedUp_and_speedDown_correct){
    ElectricalTrain electricalTrain = ElectricalTrain(100,40,TrainType::Express,1937,170);

    electricalTrain.Charge(5);
    ASSERT_EQ(electricalTrain.GetPower(),100);
    ASSERT_EQ(electricalTrain.GetSpeed(),0);
    electricalTrain.PowerUp();
    ASSERT_EQ(electricalTrain.GetPower(),99);

    electricalTrain.SpeedUp();
    ASSERT_EQ(electricalTrain.GetPower(),96);
    ASSERT_EQ(electricalTrain.GetSpeed(),12);

    electricalTrain.SpeedUp();
    ASSERT_EQ(electricalTrain.GetPower(),93);
    ASSERT_EQ(electricalTrain.GetSpeed(),24);
    for(int i=0;i<31;i++){
        electricalTrain.SpeedUp();
    }
    ASSERT_EQ(electricalTrain.GetSpeed(),170);

    ASSERT_THROW(electricalTrain.SpeedUp(),std::invalid_argument);

    electricalTrain.Charge(5);
    electricalTrain.SpeedDown();
    ASSERT_EQ(electricalTrain.GetSpeed(),158);
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

TEST(ELECTRICAL_TRAIN_TEST, test_check_powerUp_should_throw_when_power_is_zero){
    ElectricalTrain electricalTrain = ElectricalTrain(100,40,TrainType::Express,1937,170);

    ASSERT_EQ(electricalTrain.GetPower(),0);
    ASSERT_THROW(electricalTrain.PowerUp(),std::invalid_argument);
    ASSERT_EQ(electricalTrain.IsOpen(),false);
    ASSERT_EQ(electricalTrain.GetPower(),0);
}

TEST(ELECTRICAL_TRAIN_TEST, test_check_speedUp_and_speedDown_should_throw_when_not_open){
    ElectricalTrain train = ElectricalTrain(100,40,TrainType::Express,1937,170);
    train.Charge(1);

    ASSERT_THROW(train.SpeedUp(),std::invalid_argument);
    ASSERT_THROW(train.SpeedDown(),std::invalid_argument);
    ASSERT_EQ(train.GetSpeed(),0);
}

TEST(ELECTRICAL_TRAIN_TEST, test_check_speedUp_and_speedDown_should_throw_when_power_is_not_enough){
    ElectricalTrain train = ElectricalTrain(3,40,TrainType::Express,1937,170);

    ASSERT_THROW(train.PowerUp(),std::invalid_argument);
    train.Charge(1);
    train.PowerUp();
    ASSERT_EQ(train.GetPower(),2);
    ASSERT_THROW(train.SpeedUp(),std::invalid_argument);
    ASSERT_EQ(train.GetSpeed(),0);
    ASSERT_EQ(train.GetPower(),2);
}
