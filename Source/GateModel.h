/*
  ==============================================================================

    GateModel.h
    Created: 13 Apr 2024 11:49:53pm
    Author:  Piotrek

  ==============================================================================
*/

#pragma once
#include <vector>

class GateModel:public ActionBroadcaster {
public:
    size_t size();
    bool isEmpty();
    double getValue(int pos);
    void setValue(int pos,double value);
    void addStep();
    void removeStep();
    void setResolution(int res);
    int getResolution();
    inline static const String MSG_ADD = "add";
    inline static const String MSG_REMOVE = "remove";
    inline static const String MSG_RES = "resolution";

private:
    std::vector<double> steps = { 1,0,1,0,1,0,1,0 };
    char resolution=5;
};