//
// Created by zhabkazhaba on 2/29/24.
//

#ifndef PHYS_LAB_1_TESTLIST_H
#define PHYS_LAB_1_TESTLIST_H
#include <vector>

class testList {
private:
    constexpr static float g_acceleration = 9.8;
    std::vector<float> time_values;
    float av_time_value;
    float height;
    float mass;
    float radius;

    float inertia;
public:
    testList();
    testList(testList& o);
    ~testList() = default;
    std::size_t getSize();
    float getHeight() const;
    float getMass() const;
    float getRadius() const;
    float getMinTime() const;
    float getMaxTime() const;
    const std::vector<float>& getTimes();
    void setHeight(float h);
    void setMass(float m);
    void setRadius(float r);
    void addTimeValue(float time);
    std::pair<int, float> deleteTimeValue(std::size_t index);
    void clearTimeValues();
    float calculateAvTime();
    std::pair<int, float> calculateInertia();
    std::pair<int, double> calculateAbsoluteError();
    /**
     * @brief Overloaded operator that returns sum of inertia of two testList objects
     */
    float operator +(testList &o) const;
};


#endif //PHYS_LAB_1_TESTLIST_H
