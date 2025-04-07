#pragma once

/** 
 * @namespace FlightPath::KML
 * @brief Contains KML export constants for flight path visualization.
 */
namespace FlightPath {
namespace KML {

/// @brief XML header for KML documents used in FlightPath export
static const char* Header = R"(<?xml version='1.0' encoding='UTF-8'?>
<kml xmlns='http://www.opengis.net/kml/2.2'>
<Document>
<Style id="cyanLineGreenPoly">
    <LineStyle>
        <color>7f00ffff</color>
        <width>2</width>
    </LineStyle>
    <PolyStyle>
        <color>7f00ff00</color>
    </PolyStyle>
</Style>
<Style id="purpleLineGreenPoly">
    <LineStyle>
        <color>7fff00ff</color>
        <width>2</width>
    </LineStyle>
    <PolyStyle>
        <color>7f00ff00</color>
    </PolyStyle>
</Style>
)";

/// @brief XML footer for closing KML documents
static const char* Footer = R"(</Document>
</kml>
)";

/// @brief Opening tag for the original flight path placemark in a KML file.
/// @details This string contains the XML fragment that begins the definition
/// of the "Original Flight Path" in the KML output, using the cyan style.
static const char* OpenOriginalDataset = R"(<Placemark>
    <name>Original Flight Path</name>
    <visibility>1</visibility>
    <description>Original Flight Path</description>
    <styleUrl>#cyanLineGreenPoly</styleUrl>
    <LineString>
        <extrude>1</extrude>
        <altitudeMode>absolute</altitudeMode>
        <coordinates>
)";

/// @brief Opening tag for the reconstructed flight path placemark in a KML file.
/// @details This string contains the XML fragment that begins the definition
/// of the "Reconstructed Flight Path" in the KML output, using the purple style.
static const char* OpenReconstructedDataset = R"(<Placemark>
    <name>Reconstructed Flight Path</name>
    <visibility>1</visibility>
    <description>Reconstructed Flight Path</description>
    <styleUrl>#purpleLineGreenPoly</styleUrl>
    <LineString>
        <extrude>1</extrude>
        <altitudeMode>absolute</altitudeMode>
        <coordinates>
)";

/// @brief Closing tag for both original and reconstructed flight path placemarks in a KML file.
/// @details This XML fragment properly closes the `<coordinates>`, `<LineString>`,
/// and `<Placemark>` tags used to describe flight paths.
static const char* CloseDataset = R"(        </coordinates>
        </LineString>
    </Placemark>
)";

}}
