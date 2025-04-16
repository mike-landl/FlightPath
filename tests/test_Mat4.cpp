#include "Mat4.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/catch_template_test_macros.hpp>

namespace FlightPath
{
    TEMPLATE_TEST_CASE("[Mat4] Matrix Matrix Multiplication - 1x Identity", "[Mat4]", float, double)
    {
        // Setup test data
        Mat4<TestType> A({
            TestType( 1.0), TestType( 2.0), TestType( 3.0), TestType( 4.0),
            TestType( 5.0), TestType( 6.0), TestType( 7.0), TestType( 8.0),
            TestType( 9.0), TestType(10.0), TestType(11.0), TestType(12.0),
            TestType(13.0), TestType(14.0), TestType(15.0), TestType(16.0),
        });

        Mat4<TestType> B({
            TestType(1.0), TestType(0.0), TestType(0.0), TestType(0.0),
            TestType(0.0), TestType(1.0), TestType(0.0), TestType(0.0),
            TestType(0.0), TestType(0.0), TestType(1.0), TestType(0.0),
            TestType(0.0), TestType(0.0), TestType(0.0), TestType(1.0),
        });

        // Matrix Matrix Multiplication
        auto C = A * B;

        for (size_t row = 0; row < C.rows(); ++row)
        for (size_t col = 0; col < C.cols(); ++col)
        {
            const auto value = C(row, col);
            const auto expected_value = A(row, col);
            INFO("Mismatch at (" << row << ", " << col << "): "
                << "value = " << value << ", expected = " << expected_value);

            REQUIRE_THAT(value, Catch::Matchers::WithinRel(expected_value, std::numeric_limits<TestType>::epsilon() * 1));
        }
    }

    TEMPLATE_TEST_CASE("[Mat4] Matrix Matrix Multiplication - 2x Quadratic", "[Mat4]", float, double)
    {
        // Setup test data
        Mat4<TestType> A({
            TestType(  4.2543255324080747), TestType(35.3988720463896414), TestType(  4.3986877044241481), TestType(-31.6435228050765005),
            TestType(-98.6444501511946470), TestType(74.1474575110778176), TestType(-31.9339915742543781), TestType(-89.6116840316522314),
            TestType( -7.5112442746066819), TestType(-7.8281338688930049), TestType( 99.6781928366176828), TestType(-20.1687457333878086),
            TestType(-59.6783127286815400), TestType(97.6550060192435865), TestType( 71.9255054120984880), TestType(-86.9865247458301241),
        });

        Mat4<TestType> B({
            TestType(-63.9409923465784829), TestType(-43.9846358181276855), TestType(-51.8463719869277853), TestType(-23.7986330792180780),
            TestType( 69.7866280656346873), TestType(-12.1271148721767048), TestType( 45.0584897523513064), TestType(-36.8386645187420285),
            TestType( -7.0778761064568272), TestType(-76.9999489584365193), TestType( 19.1116783786232247), TestType(-31.8496900594998920),
            TestType( 11.9399006843988076), TestType(-33.5714903719825912), TestType( 46.9218036475198801), TestType(-81.4228964658384768),
        });

        Mat4<TestType> Expected({
            TestType( 1789.3882349367968345), TestType(  107.2103456146923008), TestType( -26.2564898403290954), TestType( 1031.1161371135481204),
            TestType(10637.9952999355718930), TestType( 8906.9589896055531426), TestType(3640.2752924410042397), TestType( 7929.6403673225595412),
            TestType(-1012.3453744791618192), TestType(-6572.8088848629467975), TestType( 995.3705107714353062), TestType(-1065.3865079781851364),
            TestType( 9083.2138387062786933), TestType(-1177.3375917715547985), TestType(4787.3435818193029263), TestType( 2614.6720056526783083),
        });

        // Matrix Matrix Multiplication
        auto C = A * B;

        for (size_t row = 0; row < C.rows(); ++row)
        for (size_t col = 0; col < C.cols(); ++col)
        {
            const auto value = C(row, col);
            const auto expected_value = Expected(row, col);
            INFO("Mismatch at (" << row << ", " << col << "): "
                << "value = " << value << ", expected = " << expected_value);

            REQUIRE_THAT(value, Catch::Matchers::WithinRel(expected_value, std::numeric_limits<TestType>::epsilon() * TestType(100)));
        }
    }
}
