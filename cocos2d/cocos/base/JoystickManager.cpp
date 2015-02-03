#include "base/JoystickManager.h"
#include "base/EventJoystick.h"
#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"
#include "glfw3.h"

NS_CC_BEGIN

std::unique_ptr<JoystickManager> JoystickManager::instance_ = nullptr;

JoystickManager& JoystickManager::Instance()
{
	if(!instance_)
		instance_ = std::make_unique<JoystickManager>(private_structure{});
	return *instance_;
}

void JoystickManager::Kill() 
{
    if (instance_)
		instance_ = nullptr;
}

JoystickManager::JoystickManager(const private_structure &) 
{
	/*std::array<int, 9U> microsoft;
	microsoft[static_cast<std::size_t>(Joystick::Button::BUTTON_A)] = 0;
	microsoft[static_cast<std::size_t>(Joystick::Button::BUTTON_B)] = 1;
	microsoft[static_cast<std::size_t>(Joystick::Button::BUTTON_START)] = 7;
	microsoft[static_cast<std::size_t>(Joystick::Button::POV_UP)] = 10;
	microsoft[static_cast<std::size_t>(Joystick::Button::POV_RIGHT)] = 11;
	microsoft[static_cast<std::size_t>(Joystick::Button::POV_DOWN)] = 12;
	microsoft[static_cast<std::size_t>(Joystick::Button::POV_LEFT)] = 13;
	microsoft[static_cast<std::size_t>(Joystick::Button::BUTTON_L)] = 4;
	microsoft[static_cast<std::size_t>(Joystick::Button::BUTTON_R)] = 5;

	button_mappings["Pilote de joystick PC Microsoft"] = microsoft;
	button_mappings["Default"] = microsoft;*/
}

void JoystickManager::PollEvents()
{
	for(int i = 0; i < 16; ++i)
	{
		bool present = glfwJoystickPresent(i);
		if(present && joysticks[i]==nullptr)
		{
			//Adds the Joystick to the array
			joysticks[i] = std::make_shared<Joystick>();

			//Raw datas
			joysticks[i]->id_ = i;
			joysticks[i]->name_ = glfwGetJoystickName(i);
			UpdateRawDatas(i);

			//Initializes button states and repetition clocks
			joysticks[i]->Init();

			//Sends event
			EventJoystick event { joysticks[i].get(), EventJoystick::Type::CONNECT };
			Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
		}
		else if(!present && joysticks[i])
		{
			//Sends event
			EventJoystick event { joysticks[i].get(), EventJoystick::Type::DISCONNECT };
			Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);

			//Removes the Joystick from the array
			joysticks[i].reset();
		}
		else if(present)
		{
			//Raw datas
			UpdateRawDatas(i);

			//Updates button states and sends events (also: repetition effect handling)
			std::vector<bool>& button_states { joysticks[i]->button_states };
			for(std::size_t j = 0U, end_j = button_states.size(); j < end_j; ++j)
			{
				if(button_states[j] && !joysticks[i]->button_values_[j])
				{
					button_states[j] = false;//being released
					joysticks[i]->repetition_clocks_[j].Stop();
					EventButtonJoystick event { joysticks[i].get(), EventJoystick::Type::BUTTON_RELEASED, j };
					Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
				}
				else if(joysticks[i]->button_values_[j])
				{
					if(!button_states[j])//being pressed for the first time
					{
						button_states[j] = true;

						//Starts the clock for repetition effect
						joysticks[i]->repetition_clocks_[j].Start(clock_.now());

						EventButtonJoystick event { joysticks[i].get(), EventJoystick::Type::BUTTON_PRESSED, j };
						Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
					}
					else if(button_states[j] && joysticks[i]->repetition_clocks_[j].ConsiderInput(clock_.now()))//being pressed later on with repetition effect
					{
						EventButtonJoystick event { joysticks[i].get(), EventJoystick::Type::BUTTON_PRESSED, j };
						Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
					}
				}
			}

			//Updates axes and sends events
			std::vector<JoystickAxe>& axes { joysticks[i]->axes };
			for(std::size_t j = 0U, end_j = axes.size(); j < end_j; ++j)
			{
				axes[j].value = joysticks[i]->axes_[j];
				if(axes[j].HasInput())
				{
					EventAxeJoystick event { joysticks[i].get(), EventJoystick::Type::AXE_MOVED, j };
					Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
				}
			}
		}
	}
}

void JoystickManager::UpdateRawDatas(int i /*index_joystick */)
{
	joysticks[i]->button_values_ = glfwGetJoystickButtons(i, &(joysticks[i]->button_values_count_));
	joysticks[i]->axes_ = glfwGetJoystickAxes(i, &(joysticks[i]->axes_count_));
}


NS_CC_END