#ifndef _FCITX5_MINIMAL_H_
#define _FCITX5_MINIMAL_H_

#include <fcitx-utils/inputbuffer.h>
#include <fcitx/addonfactory.h>
#include <fcitx/addonmanager.h>
#include <fcitx/inputcontext.h>
#include <fcitx/inputcontextproperty.h>
#include <fcitx/inputmethodengine.h>
#include <fcitx/inputpanel.h>
#include <fcitx/instance.h>
#include <iconv.h>

class MinCandidateWord : public fcitx::CandidateWord
{
public:
  MinCandidateWord()
  {

  }

  void select(fcitx::InputContext* inputCtx) const override
  {

  }
};

#endif // _FCITX5_MINIMAL_H_