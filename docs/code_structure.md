# Code Structure

The source code for the sci-calc is structured as follows

Folders:
```
Animation
Calculator
Macropad
Stopwatch
UIElements
Utils
```
Files:
```
main.cpp/main.h
Sidebar.cpp/Sidebar.h
UIMain.cpp/UIMain.h
```

Now we will go into each part:
## Animation

The animation engine for the SCI-CALC works like this:

When you insert an animation, for instance this one:
```c++
insertAnimation(new Animation(subElements[i], BOUNCE, subElements[i] -> getX(), cnt * 12 + 12, 100));
```

The animation engine inserts the animation into the two pools depending on what you are animating (one for animating UIElements, one for animating variables)

```cpp
// An element might have multiple animations added to it at once, this mapping procedure makes sure that only the latest animation gets animated

void insertAnimation(Animation* animation) {
	if (animation -> getTargetElement() != nullptr) {
		animationsUI[animation -> getTargetElement()] = animation;
	}
	else {
		 nimationsInt[animation -> getTargetVal()] = animation;
	}
}
```

The animation scheduler then manages and updates the animations based on their duration and positions. This is done by calling their respective animation update functions based on their animation types.

See the code for more stuff.

## Calculator

The calculator folder contains all the regular and RPN calculator codes.

```Calculator.cpp/Calculator.h```: The UI Element for the scientific calculator. It wraps up the logic stuff to display the UI.

```Expression.cpp/Expression.h```
```Node.cpp/Node.h```
: This is where the calculations happen. The Expression class handles the tokenizing, tree-building, and evaluating of the expressions. The calculation module first takes in the input string from the Calculator UI's input box, and then parses it into mathematical tokens. It then uses the shunting-yard algorithm to build an abstract syntax tree (AST), which is used to do the actual calculations.


```ExpressionBlock.cpp/ExpressionBlock.h```
This is the UIElement for displaying the expressions in the history menu.

```CalculatorRPN.cpp/CalculatorRPN.h```
```EvaluatorRPN.cpp/EvaluatorRPN.h```
These classes are the UIElement components and the calculation part for the RPN calculator.

The RPN calculator has 5 registers: x, y, z, t, and a store register which is hidden. It supports basic stack manipulation operations like swap (x, y), push, and pop. I mainly referenced the HP RPN calculators and http://www.alcula.com/calculators/rpn/ when coding this.
