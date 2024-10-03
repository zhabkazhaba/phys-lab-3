#include <numeric>
#include "testList.h"
#include "utilityFuncs.hpp"
#include <stdexcept>
#include <algorithm>

testList::testList() {
    mass = 0.0f;
    radius = 0.0f;
    height = 0.0f;
    av_time_value = 0.0f;
    inertia = 0.0f;
}

testList::testList(testList &o) {
    mass = o.mass;
    radius = o.radius;
    height = o.height;
    av_time_value = o.av_time_value;
    inertia = o.inertia;
}

size_t testList::getSize() {
    return time_values.size();
}

float testList::getHeight() const {
    return height;
}

float testList::getMass() const {
    return mass;
}

float testList::getRadius() const {
    return radius;
}

float testList::getMinTime() const {
    auto tmp = std::min_element(time_values.begin(), time_values.end());
    if (tmp == time_values.end())
        return 0;
    return *tmp;
}

float testList::getMaxTime() const {
    auto tmp = std::max_element(time_values.begin(), time_values.end());
    if (tmp == time_values.end())
        return 0;
    return *tmp;
}

const std::vector<float> &testList::getTimes() {
    return time_values;
}

void testList::setHeight(float h) {
    if (h < 0)
        throw std::runtime_error("Height is negative");
    height = h;
}

void testList::setMass(float m) {
    if (m < 0)
        throw std::runtime_error("Mass is negative");
    mass = m;
}

void testList::setRadius(float r) {
    if (r < 0)
        throw std::runtime_error("Radius is negative");
    radius = r;
}

void testList::addTimeValue(float time) {
    if (time < 0)
        throw std::runtime_error("Time value is negative");
    time_values.push_back(time);
}

std::pair<int,float> testList::deleteTimeValue(std::size_t index) {
    if (index >= time_values.size()) {
        return {1, 0.0f}; // Error code 1: index out of range
    }
    float tmp = time_values[index];
    time_values.erase(time_values.begin() + index);
    return {0, tmp};
}

void testList::clearTimeValues() {
    time_values.clear();
}

float testList::calculateAvTime() {
    if (time_values.empty())
        return 0.0f;
    av_time_value = std::accumulate(time_values.begin(), time_values.end(), 0.0f) / (float) (time_values.size());
    return av_time_value;
}

std::pair<int,float> testList::calculateInertia() {
    if (time_values.empty())
        return {1, 0}; // Error code 1: no time values
    if (mass == 0)
        return {2, 0}; // Error code 2: mass is 0
    float tmp_impulse;
    calculateAvTime();
    tmp_impulse = (mass * radius * radius * (g_acceleration * av_time_value * av_time_value - 2 * height))
                  / (2 * height);
    inertia = tmp_impulse;
    return {0, tmp_impulse};
}

std::pair<int, double> testList::calculateAbsoluteError() {
    if (time_values.empty() || mass == 0 || radius == 0 || height == 0) {
        return {1, 0}; // Error code 1: Not enough data
    }
    calculateAvTime();
    double absolute_error = (0.001/mass) + (0.1/util::convertMetersToMillimeters(radius)) + (0.01/av_time_value) + (0.0005/height); //NOLINT
    return {0, absolute_error};
}

float testList::operator+(testList &o) const {
    return inertia + o.inertia;
}