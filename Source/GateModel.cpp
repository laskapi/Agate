/*
  ==============================================================================

	GateModel.cpp
	Created: 13 Apr 2024 11:49:53pm
	Author:  Piotrek

  ==============================================================================
*/
#include <JuceHeader.h>
#include "GateModel.h"

bool GateModel::isEmpty() {
	return steps.empty();
}
size_t GateModel::size() {
	return steps.size();
}
double GateModel::getValue(int pos) {

	return (pos<steps.size())?steps[pos]:steps[0];
}
void GateModel::setValue(int pos, double value) {
	steps.at(pos) = value;
	DBG("value at pos " << pos << " :: " << steps.at(pos));
}
void GateModel::addStep() {
	steps.push_back(1.f);
	sendActionMessage(GateModel::MSG_ADD);
}
void GateModel::removeStep() {
	if (!isEmpty()) {
		steps.pop_back();
		sendActionMessage(GateModel::MSG_REMOVE);
	}

}

void GateModel::setResolution(int res)
{
	resolution = res;
	sendActionMessage(GateModel::MSG_RES);
}

int GateModel::getResolution()
{
	return resolution;
}

