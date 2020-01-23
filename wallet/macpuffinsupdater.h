#ifndef MACPUFFINSUPDATER_H
#define MACPUFFINSUPDATER_H

#include <string>
#include <boost/thread/future.hpp>

#include "version.h"
#include "clientversion.h"
#include "macpuffinsversion.h"
#include "macpuffinsreleaseinfo.h"

#include "curltools.h"

class MacpuffinsUpdater
{

public:
    static const std::string ClientVersionSrcFileLink;
    static const std::string ReleasesInfoURL;
    static const std::string LatestReleaseURL;

    MacpuffinsUpdater() = default;
    void checkIfUpdateIsAvailable(boost::promise<bool> &updateIsAvailablePromise, MacpuffinsReleaseInfo &lastRelease);

    static MacpuffinsVersion ParseVersion(const std::string& versionFile);
    static std::string GetDefineFromCFile(const std::string& fileData, const std::string &fieldName);
    static std::string RemoveCFileComments(const std::string& fileData);
};

struct RemovePreReleaseFunctor
{
    bool operator() (const NeblioReleaseInfo& r)
    {
        return r.getIsPreRelease();
    }
};

struct MacpuffinsReleaseVersionGreaterComparator
{
    bool operator() (const MacpuffinsReleaseInfo& r1, const MacpuffinsReleaseInfo& r2)
    {
        return r1.getVersion() > r2.getVersion();
    }
};


#endif // MACPUFFINSUPDATER_H
