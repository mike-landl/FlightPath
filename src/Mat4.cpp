#include "Mat4.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

namespace FlightData
{
    TEST_CASE("[Mat4] Matrix Matrix Multiplication - 1x Identity", "[Mat4]")
    {
        // Setup test data
        Mat4<double> A({
             1.0,  2.0,  3.0,  4.0,
             5.0,  6.0,  7.0,  8.0,
             9.0, 10.0, 11.0, 12.0,
            13.0, 14.0, 15.0, 16.0,
        });

        Mat4<double> B({
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0,
        });

        // Matrix Matrix Multiplication
        auto C = A * B;

        for (int row = 0; row < C.rows(); ++row)
        for (int col = 0; col < C.cols(); ++col)
        {
            const auto value = C(row, col);
            const auto expected_value = A(row, col);
            INFO("Mismatch at (" << row << ", " << col << "): "
                << "value = " << value << ", expected = " << expected_value);

            REQUIRE_THAT(value, Catch::Matchers::WithinRel(expected_value, std::numeric_limits<double>::epsilon() * 1));
        }
    }

    TEST_CASE("[Mat4] Matrix Matrix Multiplication - 2x Quadratic", "[Mat4]")
    {
        // Setup test data
        Mat4<double> A({
                4.2543255324080747,    35.3988720463896414,     4.3986877044241481,   -31.6435228050765005,
              -98.6444501511946470,    74.1474575110778176,   -31.9339915742543781,   -89.6116840316522314,
               -7.5112442746066819,    -7.8281338688930049,    99.6781928366176828,   -20.1687457333878086,
              -59.6783127286815400,    97.6550060192435865,    71.9255054120984880,   -86.9865247458301241,
        });

        Mat4<double> B({
              -63.9409923465784829,   -43.9846358181276855,   -51.8463719869277853,   -23.7986330792180780,
               69.7866280656346873,   -12.1271148721767048,    45.0584897523513064,   -36.8386645187420285,
               -7.0778761064568272,   -76.9999489584365193,    19.1116783786232247,   -31.8496900594998920,
               11.9399006843988076,   -33.5714903719825912,    46.9218036475198801,   -81.4228964658384768,
        });

        Mat4<double> Expected({
             1789.3882349367968345,   107.2103456146923008,   -26.2564898403290954,  1031.1161371135481204,
            10637.9952999355718930,  8906.9589896055531426,  3640.2752924410042397,  7929.6403673225595412,
            -1012.3453744791618192, -6572.8088848629467975,   995.3705107714353062, -1065.3865079781851364,
             9083.2138387062786933, -1177.3375917715547985,  4787.3435818193029263,  2614.6720056526783083,
        });

        // Matrix Matrix Multiplication
        auto C = A * B;

        for (int row = 0; row < C.rows(); ++row)
        for (int col = 0; col < C.cols(); ++col)
        {
            const auto value = C(row, col);
            const auto expected_value = Expected(row, col);
            INFO("Mismatch at (" << row << ", " << col << "): "
                << "value = " << value << ", expected = " << expected_value);

            REQUIRE_THAT(value, Catch::Matchers::WithinRel(expected_value, std::numeric_limits<double>::epsilon() * 1));
        }
    }
}
