#ifndef PHYS_LAB_1_MEASURELIST_H
#define PHYS_LAB_1_MEASURELIST_H


#include <vector>

constexpr static float dh = 0.1f; // IN CM

class measureList {
 private:
    std::vector<std::pair<double, double>> height;
    std::vector<double> x;
    std::vector<double> y;
    double av_x;
    double av_y;
    std::vector<double> dev_x;
    double av_dev_x;
    double y_err;
 public:
    measureList();
    measureList(measureList& o);
    ~measureList() = default;

    std::size_t getSize();
    const std::vector<std::pair<double, double>>& getHeight();
    const std::vector<double>& getX();
    const std::vector<double>& getY();
    double getAvX() const;
    double getAvY() const;
    const std::vector<double>& getDevX();
    double getAvDevX() const;
    double getYErr() const;

    double getMinX() const;
    double getMaxX() const;

    void addHeight(std::pair<double, double> h);
    std::pair<int, float> deleteHeight(std::size_t index);
    void clearHeight();

    void calculateByIndex(std::size_t index);
    int calculate();
};


#endif //PHYS_LAB_1_MEASURELIST_H
