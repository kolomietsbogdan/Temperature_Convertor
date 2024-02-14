#include <iostream>
#include <sstream>
#include <vector>

class Observer
{
public:
	virtual void update() = 0;
};

class Observable
{
public:
	void addObserver(Observer *observer)
	{
		_observers.push_back(observer);
	}

	void notifyUpdate()
	{
		int size = _observers.size();
		for (int i = 0; i < size; i++)
		{
			_observers[i]->update();
		}
	}
private:
	std::vector<Observer*> _observers;
};

class TemperatureModel : public Observable
{
public:
	float getF()
	{
		return _temperatureF;
	}

	float getC()
	{
		return (_temperatureF - 32.0) * 5.0 / 9.0;
	}

	void setF(float tempF)
	{
		_temperatureF - tempF;
		notifyUpdate();
	}

	void setC(float tempC)
	{
		_temperatureF = tempC * 9.0 / 5.0 + 32.0;
		notifyUpdate();
	}

private:
	float _temperatureF;
};

class ConsoleView : public Observer
{
public:
	ConsoleView(TemperatureModel *model)
	{
		_model = model;
		_model->addObserver(this);
	}

	virtual void update()
	{
		system("cls");
		printf("Temperature in Celsius: %.2f\n", _model->getC());
		printf("Temperature in Farenheit: %.2f\n", _model->getF());
		printf("Input temperature in Celsius: ");
	}
private:
	TemperatureModel *_model;
};

class Controller
{
public:
	Controller(TemperatureModel *model)
	{
		_model = model;
	}

	void start()
	{
		_model->setC(0);

		float temp;
		std::string input;
		do
		{
			std::cout << "Input temperature in celsius: ";
			std::getline(std::cin, input);
			std::istringstream iss(input);
			if (iss >> temp)
			{
				_model->setC(temp);
			}
			else
			{
				std::cout << "Invalid input. Please enter a valid number." << std::endl;
			}
		} while (true);

		//здесь прерывает программу, если было введено некорректное значение
		/*do 
		{
			printf("Input temperature in Celsius: ");
			std::getline(std::cin, input);
			std::istringstream iss(input);
			if (iss >> temp)
			{
				_model->setC(temp);
			}
			else
			{
				std::cout << "Invalid input. Please enter a valid number." << std::endl;
			}
		} while (temp != 0);*/
	}
private:
	TemperatureModel *_model;
};

int main()
{
	TemperatureModel model;
	ConsoleView view(&model);
	Controller controller(&model);
	controller.start();

	return 0;
}