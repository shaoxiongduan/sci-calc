#include "Slider.h"

Slider::Slider(std::string name, int startVal, int endVal) : UIElement() {
    this -> name = name;
    this -> value = startVal;
    this -> startVal = startVal;
    this -> endVal = endVal;
    this -> stepVal = 1;
    this -> linkVal = nullptr;
    this -> progressBar = ProgressBar(70, 30, 116, 0);
}

Slider::Slider(std::string name, int* linkValue, int startVal, int endVal) : UIElement() {
    this -> name = name;
    this -> value = startVal;
    this -> startVal = startVal;
    this -> endVal = endVal;
    this -> stepVal = 1;
    this -> linkVal = linkVal;
    this -> progressBar = ProgressBar(70, 30, 116, 0);
}

Slider::Slider(std::string name, int x, int y, int* linkValue, int startVal, int endVal) : UIElement(x, y) {
    this -> name = name;
    this -> x = x;
    this -> y = y;
    this -> value = startVal;
    this -> startVal = startVal;
    this -> endVal = endVal;
    this -> stepVal = 1;
    this -> linkVal = linkVal;
    this -> progressBar = ProgressBar(70, 30, 116, 0);
}

void Slider::init() {
    this -> width = this -> targetWidth = u8g2.getStrWidth(this -> name.c_str());
    this -> height = this -> targetHeight = 10;
}

void Slider::activate() {
    currentElement = this;
}

void Slider::incrementValue() {
    this -> value = min(this -> endVal, this -> value + this -> stepVal);
    this -> progressBar.setLen(int(this -> progressBar.getTotalLen() * ((this -> value * 1.0) / (this -> endVal - this -> startVal))));
    if (this -> linkVal == nullptr) return;
    *(this -> linkVal) = this -> value;
    //Serial.println(int(this -> progressBar.getTotalLen() * ((this -> value * 1.0) / (this -> endVal - this -> startVal))));
    //this -> progressBar.setLen(50);
}

void Slider::decrementValue() {
    this -> value = max(this -> startVal, this -> value - this -> stepVal);
    this -> progressBar.setLen(int(this -> progressBar.getTotalLen() * ((this -> value * 1.0) / (this -> endVal - this -> startVal))));
    if (this -> linkVal == nullptr) return;
    *(this -> linkVal) = this -> value;
    //Serial.println(int(this -> progressBar.getTotalLen() * ((this -> value * 1.0) / (this -> endVal - this -> startVal))));
}

void Slider::incrementStep() {
    this -> stepVal++;
}

void Slider::decrementStep() {
    this -> stepVal--;
}

void Slider::draw() {
    u8g2.drawStr(this -> x, this -> y, (this -> name.substr(0, min(int(this -> name.size()), this -> width / 5)) + ": " + (numToStr(this -> value))).c_str());
}

void Slider::drawUpdated() {
    u8g2.drawFrame(64, 10, 128, 44);
    u8g2.drawStr(70, 20, (this -> name + ": " + numToStr(this -> value)).c_str());
    u8g2.drawStr(150, 20, ("Step: " + numToStr(this -> stepVal)).c_str());
    u8g2.drawStr(70, 45, "up/down:step, l/r:value");
    this -> progressBar.draw();
}


void Slider::update() {
    drawUpdated();
    if (kb.getRisingEdgeKey() == std::make_pair(1, 1)) {
        //Serial.printf("UP\n");
        incrementStep();
    }
    if (kb.getRisingEdgeKey() == std::make_pair(3, 1)) {
        //Serial.printf("down\n");
        decrementStep();
    }
    if (kb.getRisingEdgeKey() == std::make_pair(2, 0)) {
        //Serial.printf("UP\n");
        decrementValue();
    }
    if (kb.getRisingEdgeKey() == std::make_pair(2, 2)) {
        //Serial.printf("down\n");
        incrementValue();
    }
    if (kb.getRisingEdgeKey() == std::make_pair(0, 0)) {
        goBack();
    }
}