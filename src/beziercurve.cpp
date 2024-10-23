#include "interception/beziercurve.h"

#include <functional>
#include <random>

namespace interception
{
    namespace
    {
        int64_t factorial(const int n)
        {
            int64_t result = 1;
            for (int i = 2; i <= n; ++i) {
                result *= i;
            }
            return result;
        }

        double binomial(const int n, const int k)
        {
            return static_cast<double>(factorial(n)) / (factorial(k) * factorial(n - k));
        }

        double bernstein_polynomial_point(const double x, const int i, const int n)
        {
            return binomial(n, i) * std::pow(x, i) * std::pow(1 - x, n - i);
        }

        std::function<point(double)> bernstein_polynomial(const std::vector<point>& vec)
        {
            return [vec](const double t) {
                const size_t n = vec.size() - 1;
                double x = 0, y = 0;
                for (int i = 0; i <= n; ++i) {
                    const double bern = bernstein_polynomial_point(t, i, n);
                    x += vec[i].x * bern;
                    y += vec[i].y * bern;
                }
                return point{static_cast<int32_t>(x), static_cast<int32_t>(y)};
            };
        }

        std::vector<point> make_points(const int32_t n, const bezier_curve_t& points)
        {
            bezier_curve_t ret;
            const std::function<point(double)> bernstein = bernstein_polynomial(points);
            for (int i = 0; i < n; ++i) {
                const double t = static_cast<double>(i) / (n - 1);
                ret.push_back(bernstein(t));
            }
            return ret;
        }

        std::vector<point> make_knots(const point& from, const point& to, const int32_t n)
        {
            static std::random_device rd;
            static std::mt19937 gen(rd());

            std::vector<point> ret;

            std::uniform_int_distribution x_distribution(
                std::min(from.x, to.x), std::max(from.x, to.x));
            std::uniform_int_distribution y_distribution(
                std::min(from.y, to.y), std::max(from.y, to.y));

            for (int32_t i = 0; i < n; i++) {
                ret.emplace_back(x_distribution(gen), y_distribution(gen));
            }

            return ret;
        }

        void distort_points(bezier_curve_t& curve, const float mean_distortion,
                            const float stdev_distortion,
                            const float frequency)
        {
            static std::random_device rd;
            static std::mt19937 gen(rd());

            std::normal_distribution<> normal_dist(mean_distortion, stdev_distortion);
            std::uniform_real_distribution<> uniform_dist(0.0, 1.0);

            for (size_t i = 1; i < curve.size() - 1; i++) {
                auto& [x, y] = curve.at(i);
                y += (uniform_dist(gen) < frequency) ? normal_dist(gen) : 0.0;
            }
        }
    }

    bezier_curve_t generate_curve(const point& from, const point& to,
                                  const bezier_curve_parameters& params)
    {
        std::vector<point> knots = make_knots(from, to, params.knots);
        knots.insert(knots.begin(), from);
        knots.push_back(to);

        bezier_curve_t curve = make_points(params.points, knots);
        distort_points(curve, params.mean_distortion, params.stdev_distortion,
                       params.distortion_frequency);
        return curve;
    }
}
