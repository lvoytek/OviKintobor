using System;
using SharpDX.XInput;

namespace Knuckles
{
	class ControllerInput
	{
        Controller XboxController;
       
        public ControllerInput()
        {
            XboxController = new Controller(UserIndex.One);
        }

        public String Update()
        {
            State ControllerState = XboxController.GetState();

            string command = "";
            string state = ControllerState.Gamepad.Buttons.ToString().Trim();

            switch (state)
            {
                case "A":
                    command = "up";
                    break;
                case "B":
                    command = "down";
                    break;
                case "DPadUp":
                    command = "fwd";
                    break;
                case "DPadDown":
                    command = "back";
                    break;
                case "DPadLeft":
                    command = "left";
                    break;
                case "DPadRight":
                    command = "right";
                    break;
                case "LeftShoulder, RightShoulder":
                    command = "land";
                    break;
                default:
                    command = "";
                    break;
            }

            return command;
        }
    }
}
