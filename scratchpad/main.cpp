
#include <iostream>
#include <vector>
#include <memory>

// Strategy pattern includes
#include "SimUDuck.h"
#include "DuckCall.h"

// Observer pattern includes
#include "WeatherData.h"
#include "Display.h"

// Helper functions
void printToConsole(const char* str);

// Example runner functions
static void strategyPatternExample();
static void observerPatternExample();

int main(void)
{
	std::cout << "Application started.\n\n";

	strategyPatternExample();
	observerPatternExample();
}

// Helper functions
void printToConsole(const char* str)
{
	std::cout << str << std::endl;
}

// Private functions

/*
The Strategy Pattern defines a family of algorithms,
encapsulates each one, and makes them interchangeable.
Strategy lets the algorithm vary independently from
clients that use it.
*/
static void strategyPatternExample()
{
	std::vector<std::shared_ptr<Duck>> ducks;

	ducks.push_back(std::make_unique<Duck>(std::make_unique<Quack>(), std::make_unique<FlyWithWings>()));
	ducks.push_back(std::make_unique<MallardDuck>(std::make_unique<Quack>(), std::make_unique<FlyWithWings>()));
	ducks.push_back(std::make_unique<ReadheadDuck>(std::make_unique<Quack>(), std::make_unique<FlyWithWings>()));
	ducks.push_back(std::make_unique<RubberDuck>(std::make_unique<QuackSqueek>(), std::make_unique<FlyNoWay>()));
	ducks.push_back(std::make_unique<WoodenDuck>(std::make_unique<QuackStaySilent>(), std::make_unique<FlyNoWay>()));

	for (std::shared_ptr<Duck> duck : ducks)
	{
		duck->display();
		duck->fly();
		duck->quack();
		printToConsole("\n");
	}

	// Making a "duck call" hunter's device
	DuckCall huntersDuckCall;
	huntersDuckCall.mimic();
}

/* 
The Observer Pattern defines a one - to - many
dependency between objects so that when one
object changes state, all of its dependents are
notified and updated automatically.
*/
void observerPatternExample()
{
	WeatherData* weatherData = new WeatherData();

	IDisplay* displayCurrentConditions = new DisplayCurrentConditions(weatherData);
	IDisplay* displaySimpleForecast = new DisplaySimpleForecast(weatherData);
	IDisplay* displayWeatherStats = new DisplayWeatherStats(weatherData);

	weatherData->setMeasurements(10, 0.4f, 2.0f);
	weatherData->setMeasurements(13, 1, 2.0f);
	weatherData->setMeasurements(12, 0.4f, 1.7f);
	weatherData->setMeasurements(12, 0.9f, 2.1f);
}
