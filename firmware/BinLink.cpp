#include "BinLink.h"

BinLink::BinLink(std::string path) {
    this -> path = path;
}

void BinLink::activate() {
    updateFromFS(SD, this -> path);
    rebootEspWithReason(this -> path + " uploaded!");
}

void BinLink::draw() {
    
}

void BinLink::update() {

}