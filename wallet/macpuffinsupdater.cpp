#include "macpuffinsupdater.h"
#include "util.h"

#include <iostream>
#include <vector>
#include <boost/regex.hpp>
#include <sstream>
#include <boost/algorithm/string.hpp>

const std::string MacpuffinsUpdater::ClientVersionSrcFileLink  = "https://raw.githubusercontent.com/macpuffin/macpuffins/master/src/clientversion.h";
const std::string MacpuffinsUpdater::ReleasesInfoURL = "https://api.github.com/repos/macpuffin/macpuffins/releases";
const std::string MacpuffinsUpdater::LatestReleaseURL = "https://github.com/macpuffin/macpuffins/releases/latest";

void MacpuffinsUpdater::checkIfUpdateIsAvailable(boost::promise<bool> &updateIsAvailablePromise, MacpuffinsReleaseInfo& lastRelease)
{
    MacpuffinsReleaseInfo remoteRelease;
    MacpuffinsVersion localVersion;
    std::string releaseData;
    std::vector<MacpuffinsReleaseInfo> macpuffinsReleases;
    try {
        releaseData = cURLTools::GetFileFromHTTPS(ReleasesInfoURL, 30, 0);
        macpuffinsReleases = MacpuffinsReleaseInfo::ParseAllReleaseDataFromJSON(releaseData);

        // remove prerelease versions
        macpuffinsReleases.erase(std::remove_if(macpuffinsReleases.begin(), macpuffinsReleases.end(),
                RemovePreReleaseFunctor()), macpuffinsReleases.end());
//        std::for_each(macpuffinsReleases.begin(), macpuffinsReleases.end(), [](const MacpuffinsReleaseInfo& v) {std::cout<<v.versionStr<<std::endl;});
        // sort in descending order
        std::sort(macpuffinsReleases.begin(), macpuffinsReleases.end(), MacpuffinsReleaseVersionGreaterComparator());
//        std::for_each(macpuffinsReleases.begin(), macpuffinsReleases.end(), [](const MacpuffinsReleaseInfo& v) {std::cout<<v.versionStr<<std::endl;});
        if(macpuffinsReleases.size() <= 0) {
            throw std::length_error("The list of releases retrieved is empty.");
        }
    } catch (std::exception& ex) {
        std::string msg("Unable to download update file: " + std::string(ex.what()) + "\n");
        printf("%s", msg.c_str());
        updateIsAvailablePromise.set_exception(boost::current_exception());
        return;
    }

    try {
        remoteRelease = macpuffinsReleases[0]; // get highest version
        localVersion  = MacpuffinsVersion::GetCurrentMacpuffinsVersion();
    } catch (std::exception& ex) {
        std::stringstream msg;
        msg << "Unable to parse version data during update check: " << ex.what() << std::endl;
        printf("%s", msg.str().c_str());
        updateIsAvailablePromise.set_exception(boost::current_exception());
        return;
    }
    lastRelease = remoteRelease;
    updateIsAvailablePromise.set_value(remoteRelease.getVersion() > localVersion);
}

MacpuffinsVersion MacpuffinsUpdater::ParseVersion(const std::string &versionFile)
{
    int majorVersion    = FromString<int>(GetDefineFromCFile(versionFile, "CLIENT_VERSION_MAJOR"));
    int minorVersion    = FromString<int>(GetDefineFromCFile(versionFile, "CLIENT_VERSION_MINOR"));
    int revisionVersion = FromString<int>(GetDefineFromCFile(versionFile, "CLIENT_VERSION_REVISION"));
    int buildVersion    = FromString<int>(GetDefineFromCFile(versionFile, "CLIENT_VERSION_BUILD"));
    return MacpuffinsVersion(majorVersion, minorVersion, revisionVersion, buildVersion);
}

std::string MacpuffinsUpdater::GetDefineFromCFile(const std::string &fileData, const std::string& fieldName)
{
    //regex of define in one or multiple lines
    const std::string regex_str = ".*\\s*#define\\s+" + fieldName + "\\s+[\\s*|(\\n)]+([^\\s]+)\\s*.*";
    boost::regex pieces_regex(regex_str);
    boost::smatch pieces_match;
    std::string piece;
    bool match_found = boost::regex_match(fileData, pieces_match, pieces_regex);
    if (match_found) {
        piece = pieces_match[1];
    } else {
        std::string error = "Unable to find match for " + fieldName + " in the downloaded file.";
        throw std::runtime_error(error.c_str());
    }
    return piece;
}

std::string MacpuffinsUpdater::RemoveCFileComments(const std::string &fileData)
{
    std::string result = fileData;

    //remove carriage return, as they could hinder detecting new lines
    std::string carriage_return_regex_str("\\r", boost::match_not_dot_newline);
    boost::regex carriage_return_regex(carriage_return_regex_str);
    result = boost::regex_replace(result, carriage_return_regex, "");

    //remove single line comments (//)
    std::string line_comments_regex_str("\\/\\/.*\\n");
    boost::regex line_comments_regex(line_comments_regex_str);
    result = boost::regex_replace(result, line_comments_regex, "", boost::match_not_dot_newline);

    //remove multi-line comments (/* */)
    std::string multiline_comments_regex_str("/\\*(.*?)\\*/"); // The "?" is to turn off greediness
    boost::regex multiline_comments_regex(multiline_comments_regex_str);
    result = boost::regex_replace(result, multiline_comments_regex, "");

    return result;
}
