
namespace FlightData {
namespace KML {

static const char* Header = R"(<?xml version='1.0' encoding='UTF-8'?>
<kml xmlns='http://www.opengis.net/kml/2.2'>
<Document>
<Style id="yellowLineGreenPoly">
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
    <name>Original Flight Simulation</name>
    <visibility>1</visibility>
    <description>Original Flight Data</description>
    <styleUrl>#yellowLineGreenPoly</styleUrl>
    <LineString>
        <extrude>1</extrude>
        <altitudeMode>absolute</altitudeMode>
        <coordinates>
)";

static const char* OpenReconstructedDataset = R"(<Placemark>
    <name>Reconstructed Flight Simulation</name>
    <visibility>1</visibility>
    <description>Reconstructed Flight Data</description>
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
