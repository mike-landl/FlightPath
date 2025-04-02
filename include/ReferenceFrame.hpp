#pragma once

#include <format>

#include "Position.hpp"
#include "Attitude.hpp"
#include "Mat4.hpp"
#include "Vec3.hpp"
#include "Units.hpp"

namespace FlightData
{
    /**
     * @class ReferenceFrame
     * @brief Represents a geodetic reference frame with position and orientation on Earth.
     *
     * The ReferenceFrame class manages transformations between geographic and body-fixed
     * coordinate systems. It encapsulates a 4x4 transformation matrix that combines
     * translation and rotation relative to Earth's surface, based on a given geodetic position
     * and orientation (attitude).
     *
     * Features:
     * - Initialization from identity, position, or external transformation matrix.
     * - Position and attitude setting.
     * - Rotation and translation operations.
     * - Matrix orthonormalization for precision.
     * - Computation of frame errors.
     * - Printing and retrieval of position and orientation.
     */
    class ReferenceFrame
    {
    public:
        /**
         * @brief Constructs a reference frame at the equator and prime meridian with default altitude.
         */
        ReferenceFrame();


        /**
         * @brief Constructs a reference frame from an existing transformation matrix.
         * @param frame A 4x4 matrix representing the transformation.
         */
        ReferenceFrame(const Mat4<double> frame);

        /**
         * @brief Constructs a reference frame from a geographic position.
         * @param position The geodetic position (longitude, latitude, altitude).
         */
        ReferenceFrame(const Position position);

        /* @brief Default destructor */
        ~ReferenceFrame() = default;

        /**
         * @brief Sets the geographic position of the reference frame.
         * @param position The geodetic position to use.
         */
        auto SetPosition(const Position position) -> void;

        /**
         * @brief Sets the orientation (attitude) of the reference frame.
         * @param attitude The orientation in heading, pitch, and roll.
         */
        auto SetAttitude(const Attitude attitude) -> void;
        
        /**
         * @brief Gets the geodetic position represented by the current transformation matrix.
         * @return The current position.
         */
        auto GetPosition() const -> Position;

        /**
         * @brief Gets the attitude (heading, pitch, roll) from the current transformation matrix.
         * @param positive_heading If true, heading is wrapped to [0, 2*PI); otherwise, can be negative.
         * @return The current attitude.
         */
        auto GetAttitude(const bool positive_heading = true) const -> Attitude;

        /**
         * @brief Prints the current position to the logging system.
         */
        auto PrintPosition() const -> void;

        /**
         * @brief Prints the current attitude to the logging system.
         */
        auto PrintAttitude() const -> void;

        /**
         * @brief Prints a given position to the logging system.
         * @param position The position to print.
         */
        auto PrintPosition(const Position position) const -> void;

        /**
         * @brief Prints a given attitude to the logging system.
         * @param attitude The attitude to print.
         */
        auto PrintAttitude(const Attitude attitude) const -> void;

        /**
         * @brief Applies a translation to the reference frame.
         * @param t A vector representing the translation.
         */
        auto Translate(const Vec3<double> t) -> void;

        /**
         * @brief Applies a rotation around the X-axis.
         * @param angle Angle in radians.
         */
        auto RotateX(const double angle) -> void;

        /**
         * @brief Applies a rotation around the Y-axis.
         * @param angle Angle in radians.
         */
        auto RotateY(const double angle) -> void;

        /**
         * @brief Applies a rotation around the Z-axis.
         * @param angle Angle in radians.
         */
        auto RotateZ(const double angle) -> void;

        /**
         * @brief Multiplies the current frame by another transformation matrix.
         * @param other Another 4x4 transformation matrix.
         */
        auto Dot(const Mat4<double> &other) -> void;

        /**
         * @brief Orthonormalizes the rotation part of the transformation matrix to reduce numerical drift.
         */
        auto Orthonormalize() -> void;

        /**
         * @brief Computes the orthogonality error of the frame's rotation matrix.
         * @return A root-mean-square value of the orthogonal error.
         */
        auto GetOrthogonalError() -> double;
        
        /**
         * @brief Computes the error in the lengths of the rotation matrix's axes from unit length.
         * @return A root-mean-square error of axis length deviation.
         */
        auto GetLengthError() -> double;

    private:
        /**
         * @brief Computes the transformation matrix from the Earth-fixed frame to a local geodetic frame.
         *
         * This matrix converts vectors from an Earth-centered, Earth-fixed (ECEF) coordinate system 
         * to a local tangent (East-North-Up) geodetic frame located at the specified position.
         *
         * @param position The reference geodetic position (longitude, latitude, altitude).
         * @return A 4x4 transformation matrix from Earth-fixed to geodetic coordinates.
         */
        auto GetEarth2GeodeticMatrix(const Position position) const -> Mat4<double>;

        /**
         * @brief Computes the transformation matrix from a geodetic frame to the Earth-fixed frame.
         *
         * This matrix is the inverse of the Earth2Geodetic transformation. It converts vectors 
         * from a local East-North-Up (ENU) geodetic frame to Earth-centered, Earth-fixed (ECEF) coordinates.
         *
         * @param position The reference geodetic position (longitude, latitude, altitude).
         * @return A 4x4 transformation matrix from geodetic to Earth-fixed coordinates.
         */
        auto GetGeodetic2EarthMatrix(const Position position) const -> Mat4<double>;

        /**
         * @brief Computes the transformation matrix from a geodetic frame to the current body-fixed frame.
         *
         * This method combines the geodetic-to-Earth and Earth-to-body-fixed transformations to convert 
         * vectors or positions from a geodetic (ENU) frame to the reference frame managed by this instance.
         *
         * @param position The reference geodetic position (longitude, latitude, altitude).
         * @return A 4x4 transformation matrix from geodetic to body-fixed coordinates.
         */
        auto GetGeodetic2BodyfixedMatrix(const Position position) const -> Mat4<double>;

    private:
        static constexpr double earth_radius_ = 6'366'707.0_m; ///< Mean Earth radius in meters.
        Mat4<double> frame_;              ///< Full transformation matrix (rotation + translation).
                                          
        Mat4<double> rotation_matrix_;    ///< Reusable rotation matrix
        Mat4<double> translation_matrix_; ///< Reuseable translation matrix
    };
}

