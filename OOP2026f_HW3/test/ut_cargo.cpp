#include <gtest/gtest.h>

#include "CargoTrain.hpp"

TEST(CARGO_TRAIN_TEST, test_check_make_ticket_should_give_correct_infor){
    CargoTrain electricalTrain = CargoTrain(100,40,TrainType::Cargo,1937,100);

    int pL = electricalTrain.GetFuelLimit();
    int p = electricalTrain.GetFuel();
    int sL = electricalTrain.GetCargoLimit();
    int s = electricalTrain.GetCargo();
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
    ASSERT_EQ(type,TrainType::Cargo);
}

TEST(CARGO_TRAIN_TEST, test_check_make_ticket_should_can_set_power_correct){
    CargoTrain electricalTrain = CargoTrain(0,40,TrainType::Cargo,1937,100);

    int pL = electricalTrain.GetFuelLimit();
    ASSERT_EQ(pL,0);

    electricalTrain.SetFuelLimit(50);
    ASSERT_EQ(electricalTrain.GetFuelLimit(),50);

    ASSERT_THROW(electricalTrain.SetFuelLimit(-1),std::invalid_argument);
    ASSERT_THROW(electricalTrain.SetFuelLimit(1207),std::invalid_argument);
    ASSERT_EQ(electricalTrain.GetType(),TrainType::Cargo);
}

TEST(CARGO_TRAIN_TEST, test_check_make_ticket_should_can_set_seat_correct){
    CargoTrain electricalTrain = CargoTrain(0,40,TrainType::Cargo,1937,100);

    int s = electricalTrain.GetCargo();
    ASSERT_EQ(s,0);

    for(int i=0;i<40;i++){
        electricalTrain.AddCargo(1);
    }

    ASSERT_THROW(electricalTrain.AddCargo(1),std::invalid_argument);
}

TEST(CARGO_TRAIN_TEST, test_check_make_ticket_should_can_speedUp_and_speedDown_correct){
    CargoTrain electricalTrain = CargoTrain(1000,100,TrainType::Cargo,1937,120);

    electricalTrain.AddFuel(995);
    ASSERT_EQ(electricalTrain.GetFuel(),995);
    ASSERT_EQ(electricalTrain.GetSpeed(),0);
    electricalTrain.PowerUp();
    ASSERT_EQ(electricalTrain.GetFuel(),990);

    electricalTrain.SpeedUp();
    ASSERT_EQ(electricalTrain.GetFuel(),980);
    ASSERT_EQ(electricalTrain.GetSpeed(),15);

    electricalTrain.SpeedUp();
    ASSERT_EQ(electricalTrain.GetFuel(),970);
    ASSERT_EQ(electricalTrain.GetSpeed(),30);

    electricalTrain.AddCargo(20);
    electricalTrain.SpeedUp();
    ASSERT_EQ(electricalTrain.GetFuel(),960);
    ASSERT_EQ(electricalTrain.GetSpeed(),46);

    electricalTrain.AddCargo(30);
    electricalTrain.SpeedUp();
    ASSERT_EQ(electricalTrain.GetFuel(),950);
    ASSERT_EQ(electricalTrain.GetSpeed(),62);

    electricalTrain.AddCargo(30);
    electricalTrain.SpeedUp();
    ASSERT_EQ(electricalTrain.GetFuel(),940);
    ASSERT_EQ(electricalTrain.GetSpeed(),79);

    for(int i=0;i<94;i++){
        electricalTrain.SpeedUp();
    }
    ASSERT_EQ(electricalTrain.GetSpeed(),120);

    ASSERT_THROW(electricalTrain.SpeedUp(),std::invalid_argument);


    electricalTrain.AddFuel(999);
    electricalTrain.SpeedDown();
    ASSERT_EQ(electricalTrain.GetSpeed(),105);
    for(int i=0;i<99;i++){
        electricalTrain.SpeedDown();
        electricalTrain.SpeedUp();
    }
    for(int i=0;i<70;i++){
        electricalTrain.SpeedDown();
    }
    ASSERT_EQ(electricalTrain.GetSpeed(),0);
    ASSERT_EQ(electricalTrain.GetFuel(),9);
    ASSERT_THROW(electricalTrain.SpeedUp(),std::invalid_argument);
    ASSERT_EQ(electricalTrain.GetSpeed(),0);
}

TEST(CARGO_TRAIN_TEST, test_check_speedUp_and_speedDown_should_throw_when_not_open){
    CargoTrain train = CargoTrain(1000,1000,TrainType::Cargo,1937,120);
    train.AddFuel(100);

    ASSERT_THROW(train.SpeedUp(),std::invalid_argument);
    ASSERT_THROW(train.SpeedDown(),std::invalid_argument);
    ASSERT_EQ(train.GetSpeed(),0);
}

TEST(CARGO_TRAIN_TEST, test_check_powerUp_should_throw_when_fuel_is_not_enough){
    CargoTrain train = CargoTrain(1000,100,TrainType::Cargo,1937,120);

    ASSERT_THROW(train.PowerUp(),std::invalid_argument);
    train.AddFuel(4);
    ASSERT_THROW(train.PowerUp(),std::invalid_argument);
    ASSERT_EQ(train.IsOpen(),false);
    ASSERT_EQ(train.GetFuel(),4);

    train.AddFuel(1);
    train.PowerUp();
    ASSERT_EQ(train.IsOpen(),true);
    ASSERT_EQ(train.GetFuel(),0);
    ASSERT_THROW(train.SpeedDown(),std::invalid_argument);
}

TEST(CARGO_TRAIN_TEST, test_check_speedUp_should_throw_when_fuel_is_less_than_10){
    CargoTrain train = CargoTrain(1000,100,TrainType::Cargo,1937,120);

    train.AddFuel(14);
    train.PowerUp();
    ASSERT_EQ(train.GetFuel(),9);
    ASSERT_THROW(train.SpeedUp(),std::invalid_argument);
    ASSERT_EQ(train.GetSpeed(),0);
    ASSERT_EQ(train.GetFuel(),9);
}
