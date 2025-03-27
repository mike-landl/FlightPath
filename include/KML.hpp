#pragma once

namespace FlightData {
namespace KML {

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

static const char* Footer = R"(</Document>
</kml>
)";

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

static const char* CloseDataset = R"(        </coordinates>
        </LineString>
    </Placemark>
)";

}}
