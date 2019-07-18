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

    MOCK_METHOD1(SetCupSize, void(int));
    MOCK_METHOD2(AddWater, void(int, int));
    MOCK_METHOD1(AddSugar, void(int));
    MOCK_METHOD1(AddCoffee, void(int));
    MOCK_METHOD1(AddMilk, void(int));
    MOCK_METHOD1(AddMilkFoam, void(int));
    MOCK_METHOD1(AddChocolate, void(int));
    MOCK_METHOD1(AddCream, void(int));
};

TEST(CoffeeMachine, setCupSize100) {
    CoffeeMachine *cm = new CoffeeMachine();
    EXPECT_CALL(*cm, SetCupSize(100))
        .Times(1)
        .WillRepeatedly(testing::Assign(&cm->cupSize, 100));
    cm->SetCupSize(100);
//        .WillOnce(testing::InvokeWithoutArgs(&cm, ));
    ASSERT_EQ(cm->cupSize, 100);
    testing::Mock::VerifyAndClearExpectations(cm);
}



