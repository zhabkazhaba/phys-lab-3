#ifndef PHYS_LAB_2_EXPERIMENTLIST_HPP
#define PHYS_LAB_2_EXPERIMENTLIST_HPP

#include <vector>
#include <tuple>

const long KELVINS = 273;

const double S = 0.0000112;

const double B_CONSTANT = 2.897771955e-3;

class experimentList {
 public:
    using measureTuple = std::tuple<long, double, double, long>;
    using measureVec = std::vector<measureTuple>;
 private:
    std::vector<measureTuple> measure_list;
    std::vector<double> result_list;
 public:
    experimentList() = default;
    ~experimentList() = default;
    void addMeasurement(measureTuple m) {
        std::get<3>(m) = std::get<0>(m) + KELVINS;
        std::get<2>(m) = std::get<1>(m) / (6 / 0.9);
        measure_list.push_back(m);
        result_list.push_back(-1);
    }

    measureTuple deleteMeasurement(std::size_t index) {
        if (index >= measure_list.size()) {
            return std::make_tuple(-1, 0, 0, 0);
        }
        auto tmp = measure_list[index];
        measure_list.erase(measure_list.begin() + index);
        result_list.erase(result_list.begin() + index);
        return tmp;
    }

    std::size_t getSize() const {
        return measure_list.size();
    }

    measureVec getMeasurementList() {
        return measure_list;
    }

    std::vector<double> getResultList() {
        return result_list;
    }

    template <typename Tuple>
    double getTupleElement(const Tuple& tup, std::size_t index) {
        if (index == 0) return static_cast<double>(std::get<0>(tup));
        if (index == 1) return static_cast<double>(std::get<1>(tup));
        if (index == 2) return static_cast<double>(std::get<2>(tup));
        if (index == 3) return static_cast<double>(std::get<3>(tup));
        throw std::out_of_range("Index out of range");
    }

    double getAvFromTuple(std::size_t index) {
        std::size_t measure_count = measure_list.size();
        double sum = 0;
        for (std::size_t i = 0; i < measure_count; ++i)
            sum += getTupleElement(measure_list[i], index);
        return (double) sum / measure_count;
    }

    void calculate() {
        for (std::size_t i = 0; i < measure_list.size(); ++i) {
            result_list[i] = std::get<2>(measure_list[i]) / (S * std::pow(std::get<3>(measure_list[i]), 4)) * std::pow(10, 8);
        }
    }

    double getAvResult() {
        double sum = 0;
        for (std::size_t i = 0; i < result_list.size(); ++i)
            sum += result_list[i];
        return (double) sum / result_list.size();
    }

    size_t clearMeasurements() {
        size_t tmp = measure_list.size();
        measure_list.clear();
        result_list.clear();
        return tmp;
    }

    std::vector<double> getLambdaMaxList() {
        std::vector<double> lambda_max;
        for (const auto& measurement : measure_list) {
            long T = std::get<3>(measurement);
            if (T > 0) {
                lambda_max.push_back(B_CONSTANT / static_cast<double>(T));
            } else {
                lambda_max.push_back(0.0);
            }
        }
        return lambda_max;
    }

    std::vector<double> getTemperatureList() const {
        std::vector<double> temperatures;
        for (const auto& measurement : measure_list) {
            temperatures.push_back(static_cast<double>(std::get<3>(measurement)));
        }
        return temperatures;
    }

    std::vector<double> generateTheoreticalLambdaMax(double T_min, double T_max, std::size_t num_points = 100) const {
        std::vector<double> theoretical_temperatures;
        std::vector<double> theoretical_lambda_max;
        double step = (T_max - T_min) / static_cast<double>(num_points - 1);
        for (std::size_t i = 0; i < num_points; ++i) {
            double T = T_min + step * i;
            theoretical_temperatures.push_back(T);
            if (T > 0)
                theoretical_lambda_max.push_back(B_CONSTANT / T);
            else
                theoretical_lambda_max.push_back(0.0);
        }
        return theoretical_lambda_max;
    }

    std::vector<double> getTheoreticalTemperatureList(double T_min, double T_max, std::size_t num_points = 100) const {
        std::vector<double> theoretical_temperatures;
        double step = (T_max - T_min) / static_cast<double>(num_points - 1);
        for (std::size_t i = 0; i < num_points; ++i) {
            double T = T_min + step * i;
            theoretical_temperatures.push_back(T);
        }
        return theoretical_temperatures;
    }
};


#endif //PHYS_LAB_2_EXPERIMENTLIST_HPP
