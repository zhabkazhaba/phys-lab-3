#include <numeric>
#include <algorithm>
#include <random>
#include <iostream>
#include "measureList.h"

measureList::measureList() {
    av_x = 0.0f;
    av_y = 0.0f;
    av_dev_x = 0.0f;
    y_err = 0.0f;
}

measureList::measureList(measureList &o) {
    height = o.height;
    x = o.x;
    y = o.y;
    av_x = o.av_x;
    av_y = o.av_y;
    dev_x = o.dev_x;
    av_dev_x = o.av_dev_x;
    y_err = o.y_err;
}

std::size_t measureList::getSize() {
    return height.size();
}

const std::vector<std::pair<double, double>> &measureList::getHeight() {
    return height;
}

const std::vector<double> &measureList::getX() {
    return x;
}

const std::vector<double> &measureList::getY() {
    return y;
}

double measureList::getAvX() const {
    return av_x;
}

double measureList::getAvY() const {
    return av_y;
}

const std::vector<double> &measureList::getDevX() {
    return dev_x;
}

double measureList::getAvDevX() const {
    return av_dev_x;
}

double measureList::getYErr() const {
    return y_err;
}

double measureList::getMinX() const {
    auto tmp = std::min_element(x.begin(), x.end());
    if (tmp == x.end())
        return 0;
    return *tmp;
}

double measureList::getMaxX() const {
    auto tmp = std::max_element(x.begin(), x.end());
    if (tmp == x.end())
        return 0;
    return *tmp;
}

void measureList::addHeight(std::pair<double, double> h) {
    height.push_back(h);
    x.resize(height.size());
    y.resize(height.size());
    dev_x.resize(height.size());
}

std::pair<int, float> measureList::deleteHeight(std::size_t index) {
    if (index >= height.size())
        return std::make_pair(-1, 0.0f);
    auto tmp = height[index];
    height.erase(height.begin() + index);
    return std::make_pair(0, tmp.first);
}

void measureList::clearHeight() { height.clear(); }

void measureList::calculateByIndex(std::size_t index) {
    if (height.empty())
        return;
    if (index >= height.size())
        return;
    y[index] = height[index].first / (height[index].first - height[index].second);
    x[index] = height[index].second / height[index].first;
    dev_x[index] = std::abs((x[index] - av_x));
}

int measureList::calculate() {
    if (height.empty())
        return -1;
    for (unsigned int i = 0; i < height.size(); ++i) {
        y[i] = height[i].first / (height[i].first - height[i].second);
        x[i] = height[i].second / height[i].first;
    }
    av_x = std::accumulate(x.begin(), x.end(), 0.0) / x.size();
    av_y = std::accumulate(y.begin(), y.end(), 0.0) / y.size();
    for (unsigned int i = 0; i < height.size(); ++i) {
        dev_x[i] = std::abs((x[i] - av_x));
    }
    av_dev_x = std::accumulate(dev_x.begin(), dev_x.end(), 0.0) / dev_x.size();

    int random_index = std::rand() % height.size();
    y_err = (dh / std::pow((1 - x[random_index]), 2));
}