#ifndef _COMMON_INSTALLER_H_
#define _COMMON_INSTALLER_H_

#include <vector>
#include <string>
#include <gctypes.h>
#include <sstream>
#include <Libwiisys/Object.h>
#include <Libwiisys/threading/ProgressEvent.h>

class Installer : public Libwiisys::Object
{
  private:
    std::string _options;
    std::vector<u32> _regions;
    std::vector<s32> _ignoredExceptions;

  protected:
    virtual void OnProgress(const std::string& message, f32 value);
    virtual void OnWarning(const std::string& message, f32 value);
  public:
    std::string Options();
    void Options(const std::string& options);

    std::vector<u32>& Region();
    void Region(std::string regions);

    std::vector<s32>& IgnoredExceptions();
    void IgnoredExceptions(const std::string& exceptionsList);

    virtual void SendToLog();

    virtual bool Prepare() = 0;
    virtual void Install() = 0;
    Libwiisys::Threading::ProgressEvent Progressing;
    Libwiisys::Threading::ProgressEvent Warning;
    virtual ~Installer();
};

#endif
