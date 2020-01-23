#include "macpuffinsversion.h"
#include "util.h"
#include "clientversion.h"

#include <stdexcept>

void MacpuffinsVersion::checkInitialization()
{
    if(major < 0 || minor < 0 || revision < 0 || build < 0)
        throw std::runtime_error("MacpuffinsVersion object is not initialized.");
}

MacpuffinsVersion::MacpuffinsVersion(int Major, int Minor, int Revision, int Build)
{
    major = Major;
    minor = Minor;
    revision = Revision;
    build = Build;
}

bool MacpuffinsVersion::operator>(const MacpuffinsVersion &rhs)
{
    checkInitialization();
    if(this->major > rhs.major)
        return true;
    else if(this->major < rhs.major)
        return false;

    if(this->minor > rhs.minor)
        return true;
    else if(this->minor < rhs.minor)
        return false;

    if(this->revision > rhs.revision)
        return true;
    else if(this->revision < rhs.revision)
        return false;

    if(this->build > rhs.build)
        return true;
    else if(this->build < rhs.build)
        return false;

    return false;
}

bool MacpuffinsVersion::operator<(const MacpuffinsVersion &rhs)
{
    return (!(*this > rhs) && !(*this == rhs));
}

bool MacpuffinsVersion::operator>=(const MacpuffinsVersion &rhs)
{
    return !(*this < rhs);
}

bool MacpuffinsVersion::operator<=(const MacpuffinsVersion &rhs)
{
    return !(*this > rhs);
}

bool MacpuffinsVersion::operator==(const MacpuffinsVersion &rhs)
{
    return (major    == rhs.major &&
            minor    == rhs.minor &&
            revision == rhs.revision &&
            build    == rhs.build);
}

bool MacpuffinsVersion::operator!=(const MacpuffinsVersion &rhs)
{
    return !(*this == rhs);
}

std::string MacpuffinsVersion::toString()
{
    return ToString(major)    + "." +
           ToString(minor)    + "." +
           ToString(revision) + "." +
           ToString(build);

}

void MacpuffinsVersion::clear()
{
    *this = NeblioVersion();
}

void MacpuffinsVersion::setMajor(int value)
{
    major = value;
}

void MacpuffinsVersion::setMinor(int value)
{
    minor = value;
}

void MacpuffinsVersion::setRevision(int value)
{
    revision = value;
}

void MacpuffinsVersion::setBuild(int value)
{
    build = value;
}

int MacpuffinsVersion::getMajor() const
{
    return major;
}

int MacpuffinsVersion::getMinor() const
{
    return minor;
}

int MacpuffinsVersion::getRevision() const
{
    return revision;
}

int MacpuffinsVersion::getBuild() const
{
    return build;
}

MacpuffinsVersion MacpuffinsVersion::GetCurrentMacpuffinsVersion()
{
    return MacpuffinsVersion(CLIENT_VERSION_MAJOR,
                         CLIENT_VERSION_MINOR,
                         CLIENT_VERSION_REVISION,
                         CLIENT_VERSION_BUILD);
}
