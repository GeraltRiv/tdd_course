/*
We have to develop a coffee machine with TDD. The machine uses the automated source of ingredients, which implements the interface ISourceOfIngredients.

Our machine should be able to produce the coffee accordingly to the next receipts:
- americano: water & coffee 1:2 or 1:3. Water temp 60C
- cappuccino - milk & coffee & milk foam 1:3, 1:3, 1:3. Water temp 80C
- latte - milk & coffee & milk foam 1:4, 1:2, 1:4. Water temp 90C
- marochino - chocolate & coffee & milk foam, 1:4, 1:4, 1:4 and 1:4 is empty

We have 2 possible sizes of the cup:
- little 100 gram
- big 140 gram

Implement worked coffee machine using ISourceOfIngredients to controll the process of coffee production.
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>
//Test list
// - setCupSize 100g CoffeMachine.getCupsize = 100g
// - add water 100g 60C  CofeeMachin.getWaterSize = 100g CofeeMachine.getTemp = 60C
// - tests for all ingridients
// .....................................................................................
// Americano: water & coffee 1:2 or 1:3. Water temp 60C
// Cappuccino: milk & coffee & milk foam 1:3, 1:3, 1:3. Water temp 80C
// Latte: milk & coffee & milk foam 1:4, 1:2, 1:4. Water temp 90C
// Marochino: chocolate & coffee & milk foam, 1:4, 1:4, 1:4 and 1:4 is empty

class ISourceOfIngredients
{
public:
    virtual ~ISourceOfIngredients() {}
    virtual void SetCupSize(int gram) = 0;
    virtual void AddWater(int gram, int temperature) = 0;
    virtual void AddSugar(int gram) = 0;
    virtual void AddCoffee(int gram) = 0;
    virtual void AddMilk(int gram) = 0;
    virtual void AddMilkFoam(int gram) = 0;
    virtual void AddChocolate(int gram) = 0;
    virtual void AddCream(int gram) = 0;
};

class CoffeeMachine: ISourceOfIngredients {
public:
    CoffeeMachine() {

    }
public:
        int cupSize = 0;
        int waterTemp = 0;
        int waterSize = 0;
        int milk = 0;
        int sugar = 0;
        int coffee = 0;
        int milkFoam = 0;
        int chocolate = 0;
        int cream = 0;

    MOCK_METHOD1(SetCupSize, void(int));
//    MOCK_METHOD2(AddWater, void(int, int));
    MOCK_METHOD1(AddSugar, void(int));
    MOCK_METHOD1(AddCoffee, void(int));
    MOCK_METHOD1(AddMilk, void(int));
    MOCK_METHOD1(AddMilkFoam, void(int));
    MOCK_METHOD1(AddChocolate, void(int));
    MOCK_METHOD1(AddCream, void(int));
    void AddWater(int gram, int waterTemp) {
        waterSize = gram;
        this->waterTemp = waterTemp;
    }

    void makeAmericano() {
        this->SetCupSize(100);
        this->AddWater(75, 60);
        this->AddCoffee(25);
    }
    void makeCappuccino() {
        this->SetCupSize(140);
        this->AddCoffee(25);
        this->AddMilk(75);
        this->AddMilkFoam(40);
    }
};

TEST(CoffeeMachine, setCupSize100) {
    CoffeeMachine *cm = new CoffeeMachine();
    EXPECT_CALL(*cm, SetCupSize(100))
        .Times(1)
        .WillRepeatedly(testing::Assign(&cm->cupSize, 100));
    cm->SetCupSize(100);
    ASSERT_EQ(cm->cupSize, 100);
    testing::Mock::VerifyAndClearExpectations(cm);
}

TEST(CoffeeMachine, addWater100g60c) {
    CoffeeMachine *cm = new CoffeeMachine();

    cm->AddWater(100, 60);
    ASSERT_EQ(cm->waterTemp, 60);
    ASSERT_EQ(cm->waterSize, 100);
    testing::Mock::VerifyAndClearExpectations(cm);
}

TEST(CoffeeMachine, addAllIngridients) {
    CoffeeMachine *cm = new CoffeeMachine();
    EXPECT_CALL(*cm, AddSugar(20))
        .Times(1)
        .WillRepeatedly(testing::Assign(&cm->sugar, 20));
    EXPECT_CALL(*cm, AddCoffee(20))
        .Times(1)
        .WillRepeatedly(testing::Assign(&cm->coffee, 20));
    EXPECT_CALL(*cm, AddMilk(20))
        .Times(1)
        .WillRepeatedly(testing::Assign(&cm->milk, 20));
    EXPECT_CALL(*cm, AddMilkFoam(20))
        .Times(1)
        .WillRepeatedly(testing::Assign(&cm->milkFoam, 20));
    EXPECT_CALL(*cm, AddChocolate(20))
        .Times(1)
        .WillRepeatedly(testing::Assign(&cm->chocolate, 20));
    EXPECT_CALL(*cm, AddCream(20))
        .Times(1)
        .WillRepeatedly(testing::Assign(&cm->cream, 20));
    cm->AddCream(20);
    cm->AddMilk(20);
    cm->AddSugar(20);
    cm->AddMilkFoam(20);
    cm->AddChocolate(20);
    cm->AddCoffee(20);

    ASSERT_EQ(cm->sugar, 20);
    ASSERT_EQ(cm->milk, 20);
    ASSERT_EQ(cm->milkFoam, 20);
    ASSERT_EQ(cm->chocolate, 20);
    ASSERT_EQ(cm->cream, 20);
    ASSERT_EQ(cm->coffee, 20);
    testing::Mock::VerifyAndClearExpectations(cm);
}

TEST(CoffeeMachine, makeAmericano) {
    CoffeeMachine *cm = new CoffeeMachine();
    EXPECT_CALL(*cm, AddCoffee(25))
        .Times(1)
        .WillRepeatedly(testing::Assign(&cm->coffee, 25));
    EXPECT_CALL(*cm, SetCupSize(100))
        .Times(1)
        .WillRepeatedly(testing::Assign(&cm->cupSize, 100));
    cm->makeAmericano();
    ASSERT_EQ(cm->cupSize, 100);
    ASSERT_EQ(cm->waterTemp, 60);
    ASSERT_EQ(cm->waterSize, 75);
    ASSERT_EQ(cm->coffee, 25);
    testing::Mock::VerifyAndClearExpectations(cm);
}

// Cappuccino: milk & coffee & milk foam 1:3, 1:3, 1:3. Water temp 80C
// Latte: milk & coffee & milk foam 1:4, 1:2, 1:4. Water temp 90C
// Marochino: chocolate & coffee & milk foam, 1:4, 1:4, 1:4 and 1:4 is empty

TEST(CoffeeMachine, makeCappuccino) {
    CoffeeMachine *cm = new CoffeeMachine();
    EXPECT_CALL(*cm, AddCoffee(25))
        .Times(1)
        .WillRepeatedly(testing::Assign(&cm->coffee, 25));
    EXPECT_CALL(*cm, SetCupSize(140))
        .Times(1)
        .WillRepeatedly(testing::Assign(&cm->cupSize, 140));
    EXPECT_CALL(*cm, AddMilk(75))
        .Times(1)
        .WillRepeatedly(testing::Assign(&cm->milk, 75));
    EXPECT_CALL(*cm, AddMilkFoam(40))
        .Times(1)
        .WillRepeatedly(testing::Assign(&cm->milkFoam, 40));
    cm->makeCappuccino();
    ASSERT_EQ(cm->cupSize, 140);
    ASSERT_EQ(cm->milkFoam, 40);
    ASSERT_EQ(cm->milk, 75);
    ASSERT_EQ(cm->coffee, 25);
    testing::Mock::VerifyAndClearExpectations(cm);
}
