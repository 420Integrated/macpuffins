#ifndef MACPUFFINSORELEASEINFO_H
#define MACPUFFINSRELEASEINFO_H

#include "json_spirit.h"
#include "macpuffinsversion.h"

#include <string>

class MacpuffinsReleaseInfo
{
    std::string versionStr;
    MacpuffinsVersion version;
    std::string htmlURL;
    std::string bodyText;
    bool isPreRelease;

    static std::string GetStrField(const json_spirit::Object& data, const std::string& fieldName);
    static bool GetBoolField(const json_spirit::Object &data, const std::string &fieldName);
    static MacpuffinsVersion VersionTagStrToObj(std::string VersionStr);
    static MacpuffinsReleaseInfo ParseSingleReleaseData(const json_spirit::Object& data);

public:
    MacpuffinsReleaseInfo();

    static std::vector<MacpuffinsReleaseInfo> ParseAllReleaseDataFromJSON(const std::string& data);
    bool getIsPreRelease() const;
    MacpuffinsVersion getVersion() const;
    std::string getUpdateDescription() const;
    std::string getDownloadLink() const;
    void clear();
};


#endif // MACPUFFINSRELEASEINFO_H
